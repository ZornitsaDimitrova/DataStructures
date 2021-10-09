// practice3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct TreeNode
{
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int data, TreeNode* left = nullptr, TreeNode* right = nullptr)
	{
		this->data = data;
		this->left = left;
		this->right = right;
	}
};

int findLeftBoundSum(TreeNode* root)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		return root->data;
	}

	if (root->left != nullptr)
	{
		return root->data + findLeftBoundSum(root->left);
	}
	else
	{
		return root->data + findLeftBoundSum(root->right);
	}
}

int findRightBoundSum(TreeNode* root)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		return root->data;
	}

	if (root->right != nullptr)
	{
		return root->data + findRightBoundSum(root->right);
	}
	else
	{
		return root->data + findRightBoundSum(root->left);
	}
}

int findBoundsSum(TreeNode* root)
{
	int leftSum = 0, rightSum = 0;
	if (root->left != nullptr)
	{
		leftSum = findLeftBoundSum(root->left);
	}
	if (root->right != nullptr)
	{
		rightSum = findRightBoundSum(root->right);
	}
	return root->data + leftSum + rightSum;
}

int sumAllNodes(TreeNode* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return root->data + sumAllNodes(root->left) + sumAllNodes(root->right);
}

bool hasSameSum(TreeNode* &root)
{
	int boundsSum = findBoundsSum(root);
	int innerNodesSum = sumAllNodes(root) - boundsSum;
	return boundsSum == innerNodesSum;
}

int main()
{
    return 0;
}

