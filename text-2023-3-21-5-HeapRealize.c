#define _CRT_SECURE_NO_WARNINGS
#include"text-2023-3-21-5-Heap.h"
//�ѵĹ���
void HeapCreate(Heap* php)
{
	assert(php);
	HeapDataType* ptr = (HeapDataType*)malloc(sizeof(HeapDataType) * 4);
	if (ptr)
	{
		php->data = ptr;
		php->capacity = 4;
		php->size = 0;
	}
	else
	{
		perror("HeapCreate malloc fail");
		return;
	}
}

//�ѵ�����
void HeapDestory(Heap* php)
{
	free(php->data);
	php->data = NULL;
}

//�ѵ�����
bool HeapFull(Heap* php)
{
	return php->capacity == php->size;
}

//�ѵ��п�
bool HeapEmpty(Heap* php)
{
	return php->size == 0;
}

//�ѵ�����
void HeapExpandCapacity(Heap* php)
{
	HeapDataType* ptr = (HeapDataType*)realloc(php->data, sizeof(HeapDataType) * php->capacity * 2);
	if (ptr)
	{
		php->data = ptr;
		php->capacity = php->capacity * 2;
	}
	else
	{
		perror("HeapExpendCapacity realloc fail");
		return;
	}
}

//�ѵĲ���
void HeapPush(Heap* php,HeapDataType x)
{
	if (HeapFull(php))
		HeapExpandCapacity(php);
	php->data[php->size] = x;
	LargeHeapAdjustUp(php,php->size);
	php->size++;
}

//�ѵ�ɾ��
void HeapPop(Heap* php)
{
	if(!HeapEmpty(php))
	php->size--;
}

//ȡ�Ѷ�Ԫ��
HeapDataType HeapTop(Heap* php)
{
	assert(php->size > 0);
	return php->data[0];
}

//���Ľ���
void Swap(HeapDataType* p1, HeapDataType* p2)
{
	HeapDataType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//��ѵ����ϵ���
void LargeHeapAdjustUp(Heap* php, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (php->data[child] > php->data[parent])
		{
			Swap(&php->data[child], &php->data[parent]);
		}
		child = parent;
		parent = (child - 1) / 2;
	}
}

//��ѵ����µ���
void LargeHeapAdjustDown(Heap* php, int parent)
{
	int child = parent * 2 + 1;
	while (child < php->size)
	{
		if ((child + 1) < php->size && php->data[child] < php->data[child + 1])
			child++;
		if (php->data[child] > php->data[parent])
			Swap(&php->data[child], &php->data[parent]);
		parent = child;
		child = parent * 2 + 1;
	}
}

//��ӡ�ѵ�ǰk��Ԫ��
void HeapPrintfTopk(Heap* php,int k)
{
	while (k--)
	{
		printf("%d ", php->data[0]);
		Swap(&php->data[0], &php->data[php->size - 1]);
		php->size--;
		LargeHeapAdjustDown(php, 0);
	}
}