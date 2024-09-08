#pragma once
#include "Common.h"

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
	
	std::unordered_map<PAGE_ID, Span*> _idSpanMap;

	PageCache()
	{}
	PageCache(const PageCache&) = delete;
	static PageCache _sInst;

};