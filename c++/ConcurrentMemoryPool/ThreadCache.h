#pragma once
#include "Common.h"

class ThreadCache
{
public:
	//申请和释放内存对象 
	void* Allocate(size_t size);
	void DeAllocate(void* ptr, size_t size);

	//从中心缓存获取对象
	void* FetchFromCentralCache(size_t index, size_t size);

	//释放内存时，链表过长时，回收内存回到中心缓存
	void ListTooLong(FreeList& list, size_t size);
private:
	FreeList _freeLists[NFREELIST];//大小还未确定
};

//TLS thread local stroage
static _declspec(thread) ThreadCache* pTLSthreadCache = nullptr;