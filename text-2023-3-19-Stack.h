#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
typedef char STDataType;
typedef struct Stack
{
	STDataType* data;
	int size;
	int capacity;
}Stack;
//ջ֡��ʼ��
void STInit(Stack* ST);

//ջ֡������
void STDestroy(Stack* ST);

//ջ֡��ѹջ
void STPush(Stack* ST,STDataType x);

//ջ֡�ĳ�ջ
void STPop(Stack* ST);

//ջ֡��ջ��
STDataType STTop(Stack* ST);

