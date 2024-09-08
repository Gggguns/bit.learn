#define _CRT_SECURE_NO_WARNINGS
#include "ThreadCache.h"
#include "CentralCache.h"


void* ThreadCache::Allocate(size_t size)
{
	//���ȣ��ж������Ƿ�С��254KB
	assert(size <= MAX_BYTES);
	//���������
	size_t alignSize = SizeClass::RoundUp(size);
	//��ӳ��λ��
	size_t index = SizeClass::Index(alignSize);

	//�������л�ȡ
	if (!_freeLists[index].Empty())
	{
		return _freeLists[index].Pop();
	}
	else
	{
		//����Ϊ�գ���central cache����
		return FetchFromCentralCache(index, alignSize);
	}
}

void ThreadCache::DeAllocate(void* ptr, size_t size)
{
	assert(ptr);
	assert(size <= MAX_BYTES);

	//�Ҷ�ӳ����������Ͱ�������ȥ
	size_t index = SizeClass::Index(size);
	_freeLists[index].Push(ptr);

	//�������ȴ���һ������������ڴ�ʱ���Ϳ�ʼ��һ��list��central cache
	if (_freeLists[index].Size() >= _freeLists[index].MaxSize())
	{
		ListTooLong(_freeLists[index], size);
	}
}

void* ThreadCache::FetchFromCentralCache(size_t index, size_t size)
{
	//���˵������һ��������ֱ�Ӹ���50�����������ò��꣬����˷ѡ�
	//����ʼ���������㷨
	//1.�ʼ����һ����central cacheһ������Ҫ̫�࣬��Ϊ̫���˿����ò���
	//2.������������size��С�ڴ�������ôbatch�ͻ᲻��������ֱ������
	//3.sizeԽ��һ����central cacheҪ��batch��ԽС
	//4.sizeԽС��һ����central cacheҪ��batch��Խ��
	//windowns����һ��min�ĺ��algorithmͷ�ļ����min��ͻ�ˣ���������ʹ�ú꣬�����Ͳ��ᱨ����
	size_t batchNum = min(_freeLists[index].MaxSize(), SizeClass::NumMoveSize(size));

	if (_freeLists[index].MaxSize() == batchNum)
	{
		_freeLists[index].MaxSize() += 1;
	}

	//��ȡ�����������ڴ�
	void* start = nullptr;
	void* end = nullptr;

	//�����ʵ�ʵõ��Ĳ�һ�����
	size_t actualNum = CentralCache::GetInstance()->FetchRangeObj(start, end, batchNum, size);

	assert(actualNum > 0);

	if (actualNum == 1)
	{
		//ֻ���뵽һ�������Ƿ��ؼ���
		assert(start == end);
		return start;
	}
	else
	{
		//���뵽���С���ڴ棬���Ƿ��ص�һ����ʣ�µ�ͷ�嵽������
		_freeLists[index].PushRange(NextObj(start), end, actualNum - 1);
		return start;
	}

}

void ThreadCache::ListTooLong(FreeList& list, size_t size)
{
	void* start = nullptr;
	void* end = nullptr;

	//ȡ��һ��������л���
	list.PopRange(start,end,list.MaxSize());

	//�黹����Ӧ��span
	CentralCache::GetInstance()->ReleaseListToSpans(start, size);
}