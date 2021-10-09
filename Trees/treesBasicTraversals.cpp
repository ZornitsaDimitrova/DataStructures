// treesBasicTraversals.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>


struct TreeNode // Предсавяне на възел от дървото
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

// Preorder (Root, Left, Right) : 1 2 4 5 3 6
// първо посещаваме текущия възел, след това съответно лявото и дясното му поддърво
void preorderTraversal(TreeNode* &root)
{
	if (root == nullptr)
	{
		return;
	}

	std::cout << root->data << " ";
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

// Inorder (Left, Root, Right) : 4 2 5 1 6 3
// първо посещаваме лявото поддърво на възела, след това самия него и накрая дясното му поддърво
void inorderTraversal(TreeNode* &root)
{
	if (root == nullptr)
	{
		return;
	}

	inorderTraversal(root->left);
	std::cout << root->data << " ";
	inorderTraversal(root->right);
}

// Postorder (Left, Right, Root) : 4 5 2 6 3 1
// първо посещаваме лявото и дясното поддърво на възела и накрая - самия него
void postorderTraversal(TreeNode* &root)
{
	if (root == nullptr)
	{
		return;
	}

	postorderTraversal(root->left);
	postorderTraversal(root->right);
	std::cout << root->data << " ";
}
//Напишете функция, която за дадено двоично дърво намира :

//Височината му - Височина на дърво наричаме дължината(в брой върхове) на най - дългия път от корена до кое да е листо на дървото

//Нивото на което се намира даден възел от дървото

//Сумата на всички възли

//Броя на всички възли

//Броя на всички вътрешни възли - Вътрешни възли наричаме възли, които не са листа
int findHeight(TreeNode* &root)
{
	if (root == nullptr)
	{
		return 0;
	}
	int leftHeight = findHeight(root->left);
	int rightHeight = findHeight(root->right);

	return 1 + std::max(leftHeight, rightHeight);
}
int findLevelHelper(TreeNode* &root, TreeNode* &nodeToFind, int level)
{
	if (root == nullptr)
	{
		return 0;
	}

	if (root == nodeToFind)
	{
		return level;
	}

	int leftLevel = findLevelHelper(root->left, nodeToFind, level + 1);
	if (leftLevel != 0)
	{
		return leftLevel;
	}
	return findLevelHelper(root->right, nodeToFind, level + 1);
}

int findLevel(TreeNode* &root, TreeNode* &nodeToFind)
{
	int level = 1;
	return findLevelHelper(root, nodeToFind, level);
}

int main()
{
	TreeNode* root = new TreeNode(8);
	root->left = new TreeNode(3);
	root->left->left = new TreeNode(9);
	root->left->right = new TreeNode(6);
	root->left->right->left = new TreeNode(4);
	root->left->right->right = new TreeNode(7);
	root->right = new TreeNode(2);
	root->right->right = new TreeNode(5);
	root->right->left = new TreeNode(7);

	std::cout << findHeight(root) << "\n";
	std::cout << findLevel(root, root->left->right) << "\n";
    return 0;
}

