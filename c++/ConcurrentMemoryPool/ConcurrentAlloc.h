#pragma once
#include "Common.h"
#include "ThreadCache.h"

//��static���κ�����������.cpp�ļ�����ͬһ��.hʱ���ᵼ�����Ӵ���
static void* ConcurrentAlloc(size_t size)
{
	//ͨ��TLS ÿ���߳������Ļ�ȡ�Լ�ר����ThreadCache����
	if (pTLSthreadCache == nullptr)
	{
		pTLSthreadCache = new ThreadCache;
	}
	//debug
	std::cout << std::this_thread::get_id() << ": " << pTLSthreadCache << std::endl;
	
	return pTLSthreadCache->Allocate(size);//�����뵽�Ŀռ䷵��
}
static void ConcurrentFree(void* ptr, size_t size)
{
	assert(pTLSthreadCache);
	//���տռ�
	pTLSthreadCache->DeAllocate(ptr, size);
}