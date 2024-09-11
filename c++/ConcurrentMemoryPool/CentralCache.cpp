#define _CRT_SECURE_NO_WARNINGS
#include "CentralCache.h"
#include "PageCache.h"

//������Ҫ��.cpp�У����壬��������
CentralCache CentralCache::_sInst;

//�����Ļ����ȡһ�������Ķ����thread cache
size_t CentralCache::FetchRangeObj(void*& start, void*& end, size_t batchNum, size_t size)
{
	//�Ҷ�ӳ��λ��
	size_t index = SizeClass::Index(size);

	//����
	_spanLists[index]._mtx.lock();

	//�ҷǿյ�span
	Span* span = GetOneSpan(_spanLists[index], size);
	assert(span);
	assert(span->_freeList);

	start = span->_freeList;
	end = start;

	//��span�л�ȡbatchNum������
	//�������batchNum�����ж����ö��ٸ�
	size_t i = 0;
	size_t actualNum = 1;
	while (i + 1 < batchNum && NextObj(end) != nullptr)
	{
		end = NextObj(end);
		++i;
		++actualNum;
	}

	//����������Ϣ
	span->_freeList = NextObj(end);
	NextObj(end) = nullptr;
	span->_useCount += actualNum;

	//����
	_spanLists[index]._mtx.unlock();

	return actualNum;
}

//��ȡһ���ǿյ�span
Span* CentralCache::GetOneSpan(SpanList& list, size_t size) 
{
	//�鿴��ǰ��spanlist���Ƿ��л�δ��������span
	Span* it = list.Begin();
	while (it != list.End())
	{
		if (it->_freeList != nullptr)
		{
			return it;
		}
		else
		{
			it = it->_next;
		}
	}

	//�Ȱ�central cache��Ͱ�������������������߳��ͷ��ڴ�����������������
	list._mtx.unlock();

	//�ߵ�����˵��û�п���span�ˣ�ֻ����page cacheҪ
	//����Ҫ����ҳ�أ�������SizeClass���У���һ��NumMovePage������ʵ��
	PageCache::GetInstance()->_pageMtx.lock();
	Span* span = PageCache::GetInstance()->NewSpan(SizeClass::NumMovePage(size));
	span->_isUse = true;
	span->_objSize = size;
	PageCache::GetInstance()->_pageMtx.unlock();
	
	//�Ի�ȡSpan�����з֣�����Ҫ��������Ϊ��������̷߳��ʲ������span

	//����span�Ĵ���ڴ����ʼ��ַ�ʹ���ڴ�Ĵ�С���ֽ�����
	char* start = (char*)(span->_pageId << PAGE_SHIFT);//ʹ��char*���ӱ��ڲ���
	size_t bytes = span->_n << PAGE_SHIFT;//<<PAGE_SHIFT�൱�ڳ���һ��ҳ�Ĵ�С
	char* end = start + bytes;

	//�Ѵ���ڴ��г�����������������
	//1.����һ��������ͷ������β��
	//β�壬�������ӵ������ڵ�ַ����������
	span->_freeList = start;
	start += size;
	void* tail = span->_freeList;

	size_t i = 1;
	while (start < end)
	{
		NextObj(tail) = start;
		tail = NextObj(tail);//��tail=start�ȼ�
		start += size;
		i++;
	}

	//β��ָ���
	NextObj(tail) = nullptr;

	//std::cout << i << std::endl;
	//�к�span�Ժ���Ҫ��span�ҵ�Ͱ����ȥ��ʱ���ټ���
	list._mtx.lock();
	//��span�����ϣͰ
	list.PushFront(span);
	
	return span;
}

void CentralCache::ReleaseListToSpans(void* start, size_t size)
{
	//�ҹ黹Ͱ
	size_t index = SizeClass::Index(size);

	_spanLists[index]._mtx.lock();
	while (start)
	{
		void* next = NextObj(start);
		//PageCache::GetInstance()->_pageMtx.lock();
		Span* span = PageCache::GetInstance()->MapObjectToSpan(start);
		//PageCache::GetInstance()->_pageMtx.unlock();
		//ͷ��黹
		NextObj(start) = span->_freeList;
		span->_freeList = start;
		span->_useCount--;

		//˵��span�зֳ�ȥ������С���ڴ涼������
		//���span�Ϳ����ٻ��ո�page cache,page cache���Գ���ȥ��ǰ��ҳ�ĺϲ�
		if (span->_useCount == 0)
		{
			_spanLists[index].Erase(span);
			span->_freeList = nullptr;
			span->_next = nullptr;
			span->_prev = nullptr;

			//�ͷ�span��page cacheʱ��ʹ��page cache�����Ϳ�����
			//��ʱ��Ͱ�����
			_spanLists[index]._mtx.unlock();

			PageCache::GetInstance()->_pageMtx.lock();
			PageCache::GetInstance()->ReleaseSpanToPageCache(span);
			PageCache::GetInstance()->_pageMtx.unlock();

			_spanLists[index]._mtx.lock();
		}

		start = next;
	}

	_spanLists[index]._mtx.unlock();

}