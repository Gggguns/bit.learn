#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//���ڵ�
struct TreeNode
{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

//������Ҷ֮��
int sumOfLeftLeaves(struct TreeNode* root)
{
    if (root == NULL)
        return 0;
    if (root->left && root->left->left == NULL && root->left->right == NULL)
        return root->left->val + sumOfLeftLeaves(root->right);
    return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}

int main()
{
	return 0;
}