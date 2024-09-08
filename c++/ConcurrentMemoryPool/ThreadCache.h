#pragma once
#include "Common.h"

class ThreadCache
{
public:
	//������ͷ��ڴ���� 
	void* Allocate(size_t size);
	void DeAllocate(void* ptr, size_t size);

	//�����Ļ����ȡ����
	void* FetchFromCentralCache(size_t index, size_t size);

	//�ͷ��ڴ�ʱ���������ʱ�������ڴ�ص����Ļ���
	void ListTooLong(FreeList& list, size_t size);
private:
	FreeList _freeLists[NFREELIST];//��С��δȷ��
};

//TLS thread local stroage
static _declspec(thread) ThreadCache* pTLSthreadCache = nullptr;