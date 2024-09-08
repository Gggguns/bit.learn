#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <thread>
#include <mutex>
#include <cassert>
#include <algorithm>
#include <unordered_map>

//������Ҫ���ж�_WIN64��64�����¼���_WIN32��Ҳ��_WIN64��32�����£�ֻ��_WIN32
#ifdef _WIN64
	typedef unsigned long long PAGE_ID;
#elif _WIN32
	typedef size_t PAGE_ID;
#else
	//Linux
#endif


static const size_t MAX_BYTES = 254 * 1024;//thread cache���������ռ�
static const size_t NFREELIST = 208;//thread cache��central cache�Ĺ�ϣͰ����
static const size_t NPAGES = 129;//page cache�Ĺ�ϣͰ���������±�Ϊ���λ�ÿճ�������
static const size_t PAGE_SHIFT = 13;//һ��ҳ�Ĵ�С

//����ϵͳ��Windows��Linux���֣���Ҫ��������
#ifdef _WIN32
#include<windows.h>
#else
	//Linux����
#endif

//ֱ��ȥ���ϣ���ҳ����ռ�
inline static void* SystemAlloc(size_t kpage)
{
#ifdef _WIN32
	void* ptr = VirtualAlloc(0, kpage << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);//kpage << 13��kpage*8*1024�ȼ�
#else
	//Linux�� brk mmap��
#endif

	if (ptr == nullptr)
	{
		throw std::bad_alloc();
	}
}

static void*& NextObj(void* obj)
{
	return *(void**)obj;
}

//�����зֺõ�С�������������
class FreeList
{
public:
	void Push(void* obj) {
		assert(obj);
		//ͷ��
		//*(void**)obj = _freeList;
		NextObj(obj) = _freeList;
		_freeList = obj;
		_size++;
	}
	
	void PushRange(void* start, void* end,size_t n)
	{
		//ͷ��һ������
		NextObj(end) = _freeList;
		_freeList = start;
		_size += n;
	}

	void PopRange(void*& start, void*& end, size_t n)
	{
		assert(n >= _size);
		start = _freeList;
		end = start;

		for (size_t i = 0;i < n - 1;i++)
		{
			end = NextObj(end);
		}

		_freeList = NextObj(end);
		NextObj(end) = nullptr;
		_size -= n;
	}

	void* Pop() {
		assert(_freeList);
		//ͷɾ
		void* obj = _freeList;
		//_freeList = *(void**)_freeList;
		_freeList = NextObj(obj);
		_size--;
		return obj;
	}
	//�п�
	bool Empty()
	{
		return _freeList == nullptr;
	}
	size_t& MaxSize()
	{
		return _maxSize;
	}
	size_t Size()
	{
		return _size;
	}
private:
	void* _freeList = nullptr;
	size_t _maxSize = 1;
	size_t _size;
};

//��������С�Ķ���ӳ�����
class SizeClass
{

	// ������������10%���ҵ�����Ƭ�˷�
	// [1,128]					8byte����	    freelist[0,16)
	// [128+1,1024]				16byte����	    freelist[16,72)
	// [1024+1,8*1024]			128byte����	    freelist[72,128)
	// [8*1024+1,64*1024]		1024byte����     freelist[128,184)
	// [64*1024+1,256*1024]		8*1024byte����   freelist[184,208)
	
	//����һ���������Ĵ�С�������㴫125�����践��128
	//��һ������������ռ��С���ڶ����Ƕ�����
	//size_t RoundUp(size_t size, size_t alignNum)
	//{
	//	size_t alignSize = 0;
	//	if (size % alignNum != 0)
	//	{
	//		//��size =7 �� alignNum = 8Ϊ�� ����8 ��7/8+1*8=8            
	//		alignSize = (size / alignNum + 1) * alignNum;
	//	}
	//	else
	//	{
	//		alignSize = size;
	//	}
	//	return alignSize;
	//}
public:
	//���������
	static inline size_t _RoundUp(size_t bytes, size_t alignNum)
	{
		//�����������֣�ɾ����������
		return (bytes + alignNum - 1) & ~(alignNum - 1);
	}

	static inline size_t RoundUp(size_t size)
	{
		if (size <= 128)
		{
			return _RoundUp(size, 8);
		}
		else if (size <= 1024)
		{
			return _RoundUp(size, 16);
		}
		else if (size <= 8*1024)
		{
			return _RoundUp(size, 128);
		}
		else if (size <= 64 * 1024)
		{
			return _RoundUp(size, 1024);
		}
		else if (size <= 256 * 1024)
		{
			return _RoundUp(size, 8 * 1024);
		}
		else
		{
			assert(false);
		}
		return -1;
	}

	//Index���Ӻ���
	static inline size_t _Index(size_t bytes, size_t align_shift) 
	{
		//��ô��⣬�͸ոյ�RoundUp��ԭ���е�����
		//�����������8��Ҳ����2��3�η���align_shift����3
		//��align_shift=3Ϊ����1 << align_shift��1������3λ����8
		//>>align_shift����ģ��8����˼������������ȥ��������
		return ((bytes + (1 << align_shift) - 1) >> align_shift) - 1;
	}

	//����ӳ�䵽��һ����������Ͱ
	static inline size_t Index(size_t bytes)
	{
		//�ж��Ƿ�С��254KB
		assert(bytes <= MAX_BYTES);
		//����һ��ʼ�Ĺ��򣬸���ÿ�������ж��ٸ���
		static int group_array[] = { 16,56,56,56 };
		if (bytes <= 128)
		{
			return _Index(bytes, 3);
		}
		else if (bytes <= 1024)
		{
			//ǰ��128�ֽ��ǰ�8����
			return _Index(bytes - 128, 4) + group_array[0];
		}
		else if (bytes <= 8 * 1024)
		{
			return _Index(bytes - 1024, 7) + group_array[1] + group_array[0];
		}
		else if (bytes <= 64*1024)
		{
			return _Index(bytes - 8 * 1024, 10) + group_array[2] + group_array[1] + group_array[0];
		}
		else if (bytes <= 256 * 1024)
		{
			return _Index(bytes - 64 * 1024, 13) + group_array[3] + group_array[2] + group_array[1] + group_array[0];
		}
		else
		{
			assert(false);
		}
		return -1;
	}

	//һ��thread cache�����Ļ����ȡ���ٸ�
	static size_t NumMoveSize(size_t size)
	{
		if (size == 0)
			return 0;

		//[2,512]��һ�������ƶ����ٸ�����ģ���������������ֵ
		//С����һ���������޸�
		//С����һ���������޵�
		int num = MAX_BYTES / size;
		if (num < 2)
			num = 2;

		if (num > 512)
			num = 512;

		return num;
	}

	//����һ����ϵͳ��ȡ����ҳ
	//�������� 8byte
	//....
	//��������256KB
	static size_t NumMovePage(size_t size)
	{
		//����Ҫ��ȡ���ٸ�
		size_t num = NumMoveSize(size);
		size_t npage = num * size;

		//����һ��ҳ�Ĵ�С
		npage >>= PAGE_SHIFT;//����һ��ҳ�Ĵ�С��8KB��Ҳ����2��13�η���PAGE_SHIFT����Ϊ13

		//����һҳ����һҳ
		if (npage == 0)
		{
			npage = 1;
		}
		return npage;
	}
};

//����������ҳ����ڴ��Ƚṹ
struct Span
{
	PAGE_ID _pageId = 0;   //����ڴ���ʼҳ��ҳ��
	size_t _n = 0;         //ҳ������

	//����˫����ṹ��������ɾ
	Span* _next = nullptr;
	Span* _prev = nullptr;

	size_t _useCount = 0; //�к�С���ڴ棬�������thread cache�ļ���
	void* _freeList = nullptr;  //�кõ�С���ڴ����������

	bool _isUse = false; //�Ƿ��ڱ�ʹ��
};

//��ͷ˫��ѭ������
class SpanList
{
public:
	SpanList()
	{
		_head = new Span;
		_head->_next = _head;
		_head->_prev = _head;
	}

	Span* Begin()
	{
		return _head->_next;
	}
	Span* End()
	{
		return _head;
	}
	
	//�����п�
	bool Empty()
	{
		return _head->_next == _head;
	}

	//ͷɾ
	Span* PopFront()
	{
		Span* front = _head->_next;
		Erase(front);
		return front;
	}

	//ͷ��span
	void PushFront(Span* span)
	{
		Insert(Begin(), span);
	}

	//prev newSpan pos
	void Insert(Span* pos, Span* newSpan)
	{
		assert(pos);
		assert(newSpan);

		Span* prev = pos->_prev;
		prev->_next = newSpan;
		newSpan->_prev = prev;
		newSpan->_next = pos;
		pos->_prev = newSpan;
	}

	void Erase(Span* pos)
	{
		assert(pos);
		assert(pos != _head);

		Span* prev = pos->_prev;
		Span* next = pos->_next;

		prev->_next = next;
		next->_prev = prev;
	}
private:
	Span* _head;
public:
	std::mutex _mtx; //Ͱ��
};