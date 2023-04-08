#define _CRT_SECURE_NO_WARNINGS
#include"text-2023-3-29-1-1-BinaryTree.h"

//ǰ��������鹹��������
BTNode* BinaryTreeCreate(BTDataType* str, int size, int* pi)
{
	BTNode root;
	int i = 0;
	BinaryTreePrevOrder(&root,str,&i);

}

//������������
void BinaryTreeDestory(BTNode* root);

//�������Ľڵ����
int BinaryTreeSize(BTNode* root);

//������Ҷ�ڵ�ĸ���
int BinaryTreeLeafSize(BTNode* root);

//��������k��Ľڵ����
int BinaryTreeLevelKSize(BTNode* root��(int k));

//����������ֵΪxd�Ľڵ�
BTNode* BinaryTreeFind(BTNode* root, BTDataType x);

//������ǰ�����
void BinaryTreePrevOrder(BTNode* root,BTDataType*str,int*pi)
{
	if (str[*pi] == '#')
		root = NULL;
	root->val = str[*pi++];
	BinaryTreePrevOrder(root->left,str,pi);
	BinaryTreePrevOrder(root->right,str,pi);
}

//�������������
void BinaryTreeInOrder(BTNode* root, BTDataType* str, int* pi)
{
	if (root == NULL)
		return;
	BinaryTreeInOrder(root->left,str,pi);
	printf("%c ", root->val);
	BinaryTreeInOrder(root->right,str,pi);
}

//�������������
void BinaryTreePostOrder(BTNode* root, BTDataType* str, int* pi)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	BinaryTreePostOrder(root->left,str,pi);
	BinaryTreePostOrder(root->right,str,pi);
	printf("%c ", root->val);
}

//�������������
void BinaryTreeLevelOrder(BTNode* root);

//�ж��ǲ�����ȫ������
bool BinaryTreeComplete(BTNode* root);