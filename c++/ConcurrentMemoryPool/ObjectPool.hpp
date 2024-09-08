#pragma once
#include "Common.h"
//����ϵͳ��Windows��Linux���֣���Ҫ��������
#ifdef _WIN32
	#include<windows.h>
#else
	//Linux����
#endif


//�����ڴ��
 
////�����͵�ģ�����
//template<size_t N>//�����N��ʾ�ڴ��һ������Ŀռ��С
//class ObjectPool {
//};

////ֱ��ȥ���ϣ���ҳ����ռ�
//inline static void* SystemAlloc(size_t kpage) 
//{
//#ifdef _WIN32
//	void* ptr = VirtualAlloc(0, kpage << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);//kpage << 13��kpage*8*1024�ȼ�
//#else
//	//Linux�� brk mmap��
//#endif
//
//	if (ptr == nullptr)
//	{
//		throw std::bad_alloc();
//	}
//}
template<class T>
class ObjectPool 
{
public:
	T* New() 
	{
		T* obj;
		//���Ȱѻ��������ڴ��������ظ�����
		if (_freeList)
		{
			//ͷɾ
			void* next = *((void**)_freeList);
			obj = (T*)_freeList;
			_freeList = next;
		}
		else
		{
			//ʣ���ڴ治��һ�������Сʱ�������¿��ٴ���ڴ�
			if (_remainBytes < sizeof(T))
			{
				_remainBytes = 128 * 1024;
				//_memory = (char*)malloc(_remainBytes);
				_memory = (char*)SystemAlloc(_remainBytes >> 13);//��ҳ������ȥ
				
				if (_memory == nullptr)
				{
					throw std::bad_alloc();//���쳣
				}
			}
			obj = (T*)_memory;
			size_t objSize = sizeof(T) > sizeof(void*) ? sizeof(T) : sizeof(void*);
			_memory += objSize;
			_remainBytes -= objSize;
		}
		//��λnew����ʾ����T�Ĺ��캯����ʼ��
		new(obj)T;

		return obj;
	}
	void Delete(T* obj) 
	{
		//��ʾ�������������������
		obj->~T();
		//ͷ��
		//����Ϊʲô����Ҫʹ��void**�أ�
		//������Ϊ32λ��ϵͳָ���С��4�ֽڣ�64λ����8�ֽڡ��������������͵�˫ָ��
		*(void**)obj = _freeList;
		_freeList = (void*)obj;
	}
private:
	char* _memory = nullptr;// ֻ�����ڴ��ָ��
	size_t _remainBytes = 0;// ����ڴ��зֹ���ʣ����ֽ���
	void* _freeList = nullptr;// ���տռ�����е����������ͷ�ڵ�
};
struct TreeNode
{
	int _val;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode()
		:_val(0)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

void TestObjectPool()
{
	// �����ͷŵ��ִ�
	const size_t Rounds = 5;

	// ÿ�������ͷŶ��ٴ�
	const size_t N = 100000;

	std::vector<TreeNode*> v1;
	v1.reserve(N);

	size_t begin1 = clock();
	for (size_t j = 0; j < Rounds; ++j)
	{
		for (int i = 0; i < N; ++i)
		{
			v1.push_back(new TreeNode);
		}
		for (int i = 0; i < N; ++i)
		{
			delete v1[i];
		}
		v1.clear();
	}

	size_t end1 = clock();

	std::vector<TreeNode*> v2;
	v2.reserve(N);

	ObjectPool<TreeNode> TNPool;
	size_t begin2 = clock();
	for (size_t j = 0; j < Rounds; ++j)
	{
		for (int i = 0; i < N; ++i)
		{
			v2.push_back(TNPool.New());
		}
		for (int i = 0; i < N; ++i)
		{
			TNPool.Delete(v2[i]);
		}
		v2.clear();
	}
	size_t end2 = clock();

	std::cout << "new cost time:" << end1 - begin1 << std::endl;
	std::cout << "object pool cost time:" << end2 - begin2 << std::endl;
}