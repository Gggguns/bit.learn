#define _CRT_SECURE_NO_WARNINGS
#include"text-2023-3-29-1-1-Queue.h"

//ǰ��������鹹��������
BTNode* BinaryTreeCreate(BTDataType* str, int* pi)
{
	if (str[*pi] == '#')
	{
		(*pi)++;
		return NULL;
	}
	BTNode* root = (BTNode*)malloc(sizeof(BTNode));
	if(root)
		root->val = str[(*pi)++];
	else
	{
		perror("malloc fail");
		return NULL;
	}
	root->left = BinaryTreeCreate(str, pi);
	root->right = BinaryTreeCreate(str, pi);
	return root;
}

//������������
void BinaryTreeDestroy(BTNode* root)
{
	if (root == NULL)
		return;
	BinaryTreeDestroy(root->left);
	BinaryTreeDestroy(root->right);
	free(root);
}

//�������Ľڵ����
int BinaryTreeSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	return BinaryTreeSize(root->left) + 1 + BinaryTreeSize(root->right);
}

//������Ҷ�ڵ�ĸ���
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	int left = BinaryTreeLeafSize(root->left);
	int right = BinaryTreeLeafSize(root->right);
	if (right + left == 0)
		return 1;
	return right + left;
}

//��������k��Ľڵ����
int BinaryTreeLevelKSize(BTNode* root,int k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->right, k - 1);
	}

//����������ֵΪx�Ľڵ�
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	if (root == NULL)
		return NULL;
	if (root->val == x)
		return root;
	BTNode* pleft = BinaryTreeFind(root->left, x);
	if (pleft)
		return pleft;
	BTNode* pright = BinaryTreeFind(root->right, x);
	if (pright)
		return pright;
	return NULL;
}

//������ǰ�����
void BinaryTreePrevOrder(BTNode* root)
{
	if (root == NULL)
		return;
	printf("%c ", root->val);
	BinaryTreePrevOrder(root->left);
	BinaryTreePrevOrder(root->right);
}

//�������������
void BinaryTreeInOrder(BTNode* root)
{
	if (root == NULL)
		return;
	BinaryTreeInOrder(root->left);
	printf("%c ", root->val);
	BinaryTreeInOrder(root->right);
}

//�������������
void BinaryTreePostOrder(BTNode* root)
{
	if (root == NULL)
		return;
	BinaryTreePostOrder(root->left);
	BinaryTreePostOrder(root->right);
	printf("%c ", root->val);
}

//�������������
void BinaryTreeLevelOrder(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root)
		QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		printf("%c ", front->val);

		if (front->left)
			QueuePush(&q, front->left);
		if (front->right)
			QueuePush(&q, front->right);	
	}
	QueueDestroy(&q);
}

//�ж��ǲ�����ȫ������
bool BinaryTreeComplete(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root)
		QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front)
		{
			QueuePush(&q, front->left);
			QueuePush(&q, front->right);
		}
		else
		{
			break;
		}
	}
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front)
		{
			QueueDestroy(&q);
			return false;
		}
	}
	QueueDestroy(&q);
	return true;
}