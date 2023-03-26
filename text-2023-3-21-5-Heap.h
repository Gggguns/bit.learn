#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int HeapDataType;

typedef struct Heap
{
	HeapDataType* data;
	int size;
	int capacity;
}Heap;

//�ѵĹ���
void HeapCreate(Heap* php);

//�ѵĲ���
void HeapPush(Heap* php,HeapDataType x);

//�ѵ�ɾ��
void HeapPop(Heap* php);

//�ѵ�����
void HeapDestory(Heap* php);

//ȡ�Ѷ�Ԫ��
HeapDataType HeapTop(Heap* php);

//�ѵ����ݸ���
int HeapSize(Heap* php);

//�ѵ��п�
bool HeapEmpty(Heap* php);

//��ӡ�ѵ�ǰk��Ԫ��
void HeapPrintfTopk(Heap* php,int k);

//�ѵ�����
bool HeapFull(Heap* php);

//�ѵ�����
void HeapExpandCapacity(Heap* php);

//���Ľ���
void Swap(HeapDataType* p1, HeapDataType* p2);

//��ѵ����ϵ���
void LargeHeapAdjustUp(Heap* php, int child);

//��ѵ����µ���
void LargeHeapAdjustDown(Heap* php, int parent);