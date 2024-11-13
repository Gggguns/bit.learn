#pragma once
#include "Common.h"
#include "ObjectPool.h"
#include "PageMap.h"

class PageCache
{
public:
	static PageCache* GetInstance()
	{
		return &_sInst;
	}

	//��ȡ�Ӷ���span��ӳ��
	Span* MapObjectToSpan(void* obj);

	//��ȡһ��Kҳ��span
	Span* NewSpan(size_t k);

	//�ͷſ���span�ص�Pagecache�����ϲ����ڵ�span
	void ReleaseSpanToPageCache(Span* span);

	std::mutex _pageMtx;

private:
	
	SpanList _spanLists[NPAGES];
	//span�ڴ��
	ObjectPool<Span> _spanPool;
	
	//std::unordered_map<PAGE_ID, Span*> _idSpanMap;
	//��������ֱ��д����
	TCMalloc_PageMap1<32 - PAGE_SHIFT> _idSpanMap;

	PageCache()
	{}
	PageCache(const PageCache&) = delete;
	static PageCache _sInst;

};