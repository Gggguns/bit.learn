#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
typedef int QueueDataType;
typedef struct QueueNode
{
	QueueDataType data;
	struct QueueNode* next;
}QNode;
typedef struct QueueList {
	QNode* head;
	QNode* tail;
	int size;
}QList;
typedef struct {
	QList Queue1;
	QList Queue2;
} MyStack;

//�����Ƿ�Ϊ��
bool QueueEmpty(QList* pq)
{
	return pq->size == 0;
}
//���еĳ�ʼ��
void QueueInit(QList* pq)
{
	pq->head = NULL;
	pq->tail = NULL;
	pq->size = 0;
}

//���еĴݻ�
void QueueDestroy(QList* pq)
{
	assert(pq);
	QNode* cur;
	cur = pq->head;
	while (cur)
	{
		pq->head = pq->head->next;
		free(cur);
		cur = pq->head;
	}
	cur = NULL;
	pq->head = NULL;
	pq->tail = NULL;
	pq->size = 0;
}

//���е�����
void QueuePush(QList* pq, QueueDataType x)
{
	assert(pq);
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return;
	}
	newnode->data = x;
	newnode->next = NULL;
	if (QueueEmpty(pq))
		pq->head = pq->tail = newnode;
	else
	{
		pq->tail->next = newnode;
		pq->tail = newnode;
	}
	pq->size++;
}

//���еĳ���
void QueuePop(QList* pq)
{
	QNode* cur;
	cur = pq->head;
	if (!QueueEmpty(pq))
	{
		pq->head = pq->head->next;
		free(cur);
		pq->size--;
	}
}


//���еĳ���
int QueueSize(QList* pq)
{
	return pq->size;
}

//���е�����Ԫ��
QueueDataType QueueFront(QList* pq)
{
	assert(pq);
	assert(pq->head);
	return pq->head->data;
}

//���е���βԪ��
QueueDataType QueueTail(QList* pq)
{
	assert(pq);
	assert(pq->head);
	return pq->tail->data;
}
MyStack* myStackCreate() {
	MyStack* ST = (MyStack*)malloc(sizeof(MyStack));
	if (ST)
	{
		QueueInit(&ST->Queue1);
		QueueInit(&ST->Queue2);
		return ST;
	}
	else
	{
		perror("myStackCreate malloc fail");
		return NULL;
	}
}
void myStackPush(MyStack* obj, int x) {
	if (!QueueEmpty(&obj->Queue1))
		QueuePush(&obj->Queue1, x);
	else
		QueuePush(&obj->Queue2, x);

}

int myStackPop(MyStack* obj) {
	QList* Empty = &obj->Queue1;
	QList* NonEmpty = &obj->Queue2;
	if (QueueEmpty(&obj->Queue2))
	{
		Empty = &obj->Queue2;
		NonEmpty = &obj->Queue1;
	}
	//������
	while (QueueSize(NonEmpty) > 1)
	{
		QueuePush(Empty, QueueFront(NonEmpty));
		QueuePop(NonEmpty);
	}
	int Top = QueueFront(NonEmpty);
	QueuePop(NonEmpty);
	return Top;
}

int myStackTop(MyStack* obj) {
	if (QueueEmpty(&obj->Queue1))
		return QueueTail(&obj->Queue2);
	else
		return QueueTail(&obj->Queue1);
}

bool myStackEmpty(MyStack* obj) {
	return QueueEmpty(&obj->Queue1) && QueueEmpty(&obj->Queue2);
}

void myStackFree(MyStack* obj) {
	QueueDestroy(&obj->Queue1);
	QueueDestroy(&obj->Queue2);
}
int main()
{
	return 0;
}