#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
typedef char BTDataType;

typedef struct BinaryTreeNode
{
	BTDataType val;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;

//ǰ��������鹹��������
BTNode* BinaryTreeCreate(BTDataType* str, int* pi);

//������������
void BinaryTreeDestroy(BTNode* root);

//�������Ľڵ����
int BinaryTreeSize(BTNode* root);

//������Ҷ�ڵ�ĸ���
int BinaryTreeLeafSize(BTNode* root);

//��������k��Ľڵ����
int BinaryTreeLevelKSize(BTNode* root, int k);

//����������ֵΪxd�Ľڵ�
BTNode* BinaryTreeFind(BTNode* root, BTDataType x);

//������ǰ�����
void BinaryTreePrevOrder(BTNode* root);

//�������������
void BinaryTreeInOrder(BTNode* root);

//�������������
void BinaryTreePostOrder(BTNode* root);

//�������������
void BinaryTreeLevelOrder(BTNode* root);

//�ж��ǲ�����ȫ������
bool BinaryTreeComplete(BTNode* root);