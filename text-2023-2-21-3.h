#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#define N 10
typedef int SLDateType;
typedef struct SList
{
	SLDateType* s;
	int size;
	int capacity;
}SqeList;

SqeList s;

//�������
void CheckSqeListCapacity(SqeList* ps);

//˳���ĳ�ʼ��
void SqeListInit(SqeList* ps);

//˳���Ĵݻ�
void SqeListDestory(SqeList* ps);

//˳���Ĵ�ӡ
void SqeListPrintf(SqeList* ps);

//˳����ͷ��
void SqeListPushFront(SqeList* ps);

//˳����β��
void SqeListPushBack(SqeList* ps);

//˳����βɾ
void SqeListPopBack(SqeList* ps);

//˳����ͷɾ
void SqeListPopFront(SqeList* ps);