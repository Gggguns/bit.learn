#define _CRT_SECURE_NO_WARNINGS
#include"text-2023-3-29-1-1-Queue.h"
int main()
{
	char arr[] = "ABC##DE###FG#H##I##";
	int len = strlen(arr);
	int i=0;
	BTNode*root=BinaryTreeCreate(arr,&i);

	//�������ڵ�
	int size=BinaryTreeSize(root);
	printf("TreeSize=%d\n", size);

	//k��ڵ�Ĳ���
	int sizek = BinaryTreeLevelKSize(root, 6);
	printf("TreeLevelkSize=%d\n", sizek);

	//Ҷ�ڵ�Ĳ���
	int LeafSize = BinaryTreeLeafSize(root);
	printf("LeafSize=%d\n", LeafSize);

	//ǰ�����
	BinaryTreePrevOrder(root);
	printf("\n");

	//�������
	BinaryTreeInOrder(root);
	printf("\n");

	//�������
	BinaryTreePostOrder(root);
	printf("\n");

	//�������
	BinaryTreeLevelOrder(root);
	printf("\n");

	BinaryTreeDestroy(root);
	return 0;
}