#pragma once
#include "Common.h"

class PageCache
{
public:
	static PageCache* GetInstance()
	{
		return &_sInst;
	}

	//获取从对象到span的映射
	Span* MapObjectToSpan(void* obj);

	//获取一个K页的span
	Span* NewSpan(size_t k);

	//释放空闲span回到Pagecache，并合并相邻的span
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