#define _CRT_SECURE_NO_WARNINGS
#include"text-2023-3-21-Queue.h"
//���еĳ�ʼ��
void QueueInit(Queue* pq)
{
	pq->head = NULL;
	pq->tail = NULL;
	pq->size = 0;
}

//���еĴݻ�
void QueueDestroy(Queue* pq)
{
	assert(pq);
	Queue* cur;
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
void QueuePush(Queue* pq, QueueDataType x)
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
void QueuePop(Queue* pq)
{
	Queue* cur;
	cur = pq->head;
	if (!QueueEmpty(pq))
	{
		pq->head = pq->head->next;
		free(cur);
		pq->size--;
	}
}

//�����Ƿ�Ϊ��
bool QueueEmpty(Queue* pq)
{
	return pq->size == 0;
}

//���еĳ���
int QueueSize(Queue* pq)
{
	return pq->size;
}

//���е�����Ԫ��
QueueDataType QueueFront(Queue* pq)
{
	assert(pq);
	assert(pq->head);
	return pq->head->data;
}

//���е���βԪ��
QueueDataType QueueTail(Queue* pq)
{
	assert(pq);
	assert(pq->head);
	return pq->tail->data;
}