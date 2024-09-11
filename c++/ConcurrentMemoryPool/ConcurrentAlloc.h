#pragma once
#include "Common.h"
#include "ThreadCache.h"
#include "PageCache.h"


//��static���κ�����������.cpp�ļ�����ͬһ��.hʱ���ᵼ�����Ӵ���
static void* ConcurrentAlloc(size_t size)
{
	if (size > MAX_BYTES)
	{
		//����
		size_t alignSize = SizeClass::RoundUp(size);
		//ȷ��ҳ��
		size_t kpage = alignSize >> PAGE_SHIFT;

		//����kҳ
		PageCache::GetInstance()->_pageMtx.lock();
		Span* span = PageCache::GetInstance()->NewSpan(kpage);
		span->_objSize = size;
		PageCache::GetInstance()->_pageMtx.unlock();

		void* ptr = (void*)(span->_pageId << PAGE_SHIFT);
		return ptr;
	}
	else
	{
		//ͨ��TLS ÿ���߳������Ļ�ȡ�Լ�ר����ThreadCache����
		if (pTLSthreadCache == nullptr)
		{
			static ObjectPool<ThreadCache> tcPool;
			//pTLSthreadCache = new ThreadCache;
			tcPool._oPoolMtx.lock();
			pTLSthreadCache = tcPool.New();
			tcPool._oPoolMtx.unlock();
		}
		//debug
		//std::cout << std::this_thread::get_id() << ": " << pTLSthreadCache << std::endl;

		return pTLSthreadCache->Allocate(size);//�����뵽�Ŀռ䷵��
	}
}
static void ConcurrentFree(void* ptr)
{
	//PageCache::GetInstance()->_pageMtx.lock();
	//��ӳ��
	Span* span = PageCache::GetInstance()->MapObjectToSpan(ptr);
	//PageCache::GetInstance()->_pageMtx.unlock();
	//��ȡ�����С
	size_t size = span->_objSize;
	if (size > MAX_BYTES) 
	{
		PageCache::GetInstance()->_pageMtx.lock();
		PageCache::GetInstance()->ReleaseSpanToPageCache(span);
		PageCache::GetInstance()->_pageMtx.unlock();

	}
	else
	{
		assert(pTLSthreadCache);
		//���տռ�
		pTLSthreadCache->DeAllocate(ptr, size);
	}
}