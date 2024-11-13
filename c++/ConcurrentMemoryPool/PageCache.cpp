#define _CRT_SECURE_NO_WARNINGS
#include "PageCache.h"

//ͬ���ģ��ñ���ֻ����.cpp�ж��壬�����.h�ж������������
PageCache PageCache::_sInst;

//��ȡһ��k��ҳ��span
Span* PageCache::NewSpan(size_t k)
{
	assert(k > 0);

	//����128 page ֱ���������
	if (k > NPAGES - 1)
	{
		void* ptr = SystemAlloc(k);

		//Span* span = new Span;
		Span* span = _spanPool.New();

		span->_pageId = (PAGE_ID)ptr >> PAGE_SHIFT;
		span->_n = k;

		//_idSpanMap[span->_pageId] = span;
		_idSpanMap.set(span->_pageId, span);

		return span;
	}

	//�ȼ���k��Ͱ������û��span
	if (!_spanLists[k].Empty())
	{
		Span* kSpan = _spanLists[k].PopFront();
		//����id��span��ӳ�䣬����central cache����С���ڴ�ʱ�����Ҷ�Ӧ��span
		for (PAGE_ID i = 0;i < kSpan->_n;i++)
		{
			//_idSpanMap[kSpan->_pageId + i] = kSpan;
			_idSpanMap.set(kSpan->_pageId + i, kSpan);
		}

		return kSpan;
	}

	//���һ�º����Ͱ������û��span������п��԰��������з�
	for (size_t i = k + 1;i < NPAGES;i++)
	{
		if (!_spanLists[i].Empty())
		{
			Span* nSpan = _spanLists[i].PopFront();
			//Span* kSpan = new Span;
			Span* kSpan = _spanPool.New();

			//��nSpan��ͷ������һ��kҳ����
			//kҳspan����
			//nSpan�ٹҵ���Ӧӳ���λ��
			kSpan->_pageId = nSpan->_pageId;
			kSpan->_n = k;

			nSpan->_pageId += k;
			nSpan->_n -= k;

			//n-k�ķ����Ӧ�Ĺ�ϣͰ��
			_spanLists[nSpan->_n].PushFront(nSpan);
			
			//�洢nSpan����βҳ�ź�nSpanӳ�䣬����page cache�����ڴ�ʱ
			//���еĺϲ�����
			/*_idSpanMap[nSpan->_pageId] = nSpan;
			_idSpanMap[nSpan->_pageId + nSpan->_n - 1] = nSpan;*/
			_idSpanMap.set(nSpan->_pageId, nSpan);
			_idSpanMap.set(nSpan->_pageId + nSpan->_n - 1, nSpan);

			//����id��span��ӳ�䣬����central cache����С���ڴ�ʱ�����Ҷ�Ӧ��span
			for (PAGE_ID i = 0;i < kSpan->_n;i++)
			{
				/*_idSpanMap[kSpan->_pageId + i] = kSpan;*/
				_idSpanMap.set(kSpan->_pageId + i, kSpan);
			}

			return kSpan;
		}
	}


	//�ߵ����λ�þ�˵������û�д�ҳ��span��
	//��ʱ��ȥ�Ҷ�Ҫһ��128ҳ��span
	//Span* bigSpan = new Span;
	Span* bigSpan = _spanPool.New();

	void* ptr = SystemAlloc(NPAGES - 1);
	bigSpan->_pageId = (PAGE_ID)ptr >> PAGE_SHIFT;
	bigSpan->_n = NPAGES - 1;

	_spanLists[bigSpan->_n].PushFront(bigSpan);

	//����ݹ������ô���
	return NewSpan(k);
}

Span* PageCache::MapObjectToSpan(void* obj)
{
	//����ҳ��
	PAGE_ID id = ((PAGE_ID)obj >> PAGE_SHIFT);

	//std::unique_lock<std::mutex> lock(_pageMtx);

	//auto ret = _idSpanMap.find(id);
	

	/*if (ret != _idSpanMap.end())
	{
		return ret->second;
	}
	else
	{
		assert(false);
		return nullptr;
	}*/

	auto ret = (Span*)_idSpanMap.get(id);
	assert(ret != nullptr);
	return ret;
}

void PageCache::ReleaseSpanToPageCache(Span* span)
{
	//����128 page��ֱ�ӻ�����
	if (span->_n > NPAGES - 1)
	{
		void* ptr = (void*)(span->_pageId << PAGE_SHIFT);
		SystemFree(ptr);

		//delete(span);
		_spanPool.Delete(span);
		return;
	}

	//��spanǰ���ҳ�����Խ��кϲ��������ڴ���Ƭ����
	//��ǰ�ϲ�
	while (1)
	{
		PAGE_ID prevId = span->_pageId - 1;
		//auto ret = _idSpanMap.find(prevId);
		auto ret = (Span*)_idSpanMap.get(prevId);
		//ǰ���ҳ��û�У����ϲ���
		if (ret == nullptr)
		{
			break;
		}
		
		//ǰ�����ڵ�ҳ��ʹ�ã����ϲ���
		//Span* prevSpan = ret->second;
		Span* prevSpan = ret;
		if (prevSpan->_isUse == true)
		{
			break;
		}

		//�ϲ�������128ҳ��spanû�취���������ϲ���
		if (prevSpan->_n + span->_n > NPAGES - 1)
		{
			break;
		}

		//�ϲ�span��prevSpan
		span->_pageId = prevSpan->_pageId;
		span->_n += prevSpan->_n;

		//����prevSpan
		_spanLists[prevSpan->_n].Erase(prevSpan);
		//delete(prevSpan);
		_spanPool.Delete(prevSpan);
	}
	
	//���ϲ�
	while (1)
	{
		PAGE_ID nextId = span->_pageId + span->_n;
		//auto ret = _idSpanMap.find(nextId);
		auto ret = (Span*)_idSpanMap.get(nextId);
		//�����ҳ��û�У����ϲ�
		if (ret == nullptr)
		{
			break;
		}
		//�������ڵ�ҳ��ʹ�ã����ϲ�
		//auto nextSpan = ret->second;
		auto nextSpan = ret;
		if (nextSpan->_isUse == true)
		{
			break;
		}

		//�ϲ�����128ҳ��spanû�취���������ϲ�
		if (nextSpan->_n + span->_n > NPAGES - 1)
		{
			break;
		}

		//�ϲ�
		span->_n += nextSpan->_n;

		//���nextSpan
		_spanLists[nextSpan->_n].Erase(nextSpan);
		//delete(nextSpan);
		_spanPool.Delete(nextSpan);
	}

	//����page cache�е���Ϣ
	_spanLists[span->_n].PushFront(span);
	span->_isUse = false;
	/*_idSpanMap[span->_pageId] = span;
	_idSpanMap[span->_pageId + span->_n - 1] = span;*/
	_idSpanMap.set(span->_pageId, span);
	_idSpanMap.set(span->_pageId + span->_n - 1, span);
}