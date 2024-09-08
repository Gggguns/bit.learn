#pragma once
#include "Common.h"

//单例模式
class CentralCache
{
public:
	//获取单例
	static CentralCache* GetInstance()
	{
		return &_sInst;
	}

	//获取一个非空的span
	Span* GetOneSpan(SpanList& list, size_t size);

	//从中心缓存获取一定数量的对象给thread cache
	size_t FetchRangeObj(void*& start, void*& end, size_t batchNum, size_t size);

	//将一定数量的对象释放到span跨度
	void ReleaseListToSpans(void* start, size_t size);

private:
	SpanList _spanLists[NFREELIST];//tread cache有208个桶，它也有208个桶

	//禁掉构造函数
	CentralCache(){}
	CentralCache(const CentralCache&) = delete;
	static CentralCache _sInst;
};