// treesPractice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>

struct Node {
	int data;
	Node* left;
	Node* right;
};

int findHeight(Node *root) {
	if (root == nullptr) {
		return 0;
	}
	int leftHeight = findHeight(root->left);
	int rightHeight = findHeight(root->right);

	return 1 + std::max(leftHeight, rightHeight);
}

int findLevelHelper(Node *root, Node* toFind, int level) {
	if (root == nullptr) {
		return 0;
	}
	if (root == toFind) {
		return level;
	}
	int leftLevel = findLevelHelper(root->left, toFind, level + 1);
	if (leftLevel != 0)
	{
		return leftLevel;
	}
	return findLevelHelper(root->right, toFind, level + 1);
}

int findLevel(Node *root, Node* toFind) {
	int level = 1;
	return findLevelHelper(root, toFind, level);
}

int findSum(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	return root->data + findSum(root->left) + findSum(root->right);
}

int findCount(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	return 1 + findCount(root->left) + findCount(root->right);
}

int findInnerCount(Node* root) {
	if (root == nullptr || root->left == nullptr && root->right == nullptr) {
		return 0;
	}
	return 1 + findInnerCount(root->left) + findInnerCount(root->right);
}

/*
За дадено двоично дърво намерете:

Всички възможни пътища

Пътя от корена на дървото до даден възел

Сумата на най-дългия път*/
// 1. Всички възможни пътища

void printArrPath(int* arrPath, int plen)
{
	for (int i = 0; i < plen; i++)
	{
		std::cout << arrPath[i] << " ";
	}
	std::cout << "\n";
}

void printAllPathsHelp(Node* &root, int* arrPath, int plen)
{
	if (root == nullptr)
	{
		return;
	}

	arrPath[plen++] = root->data;

	if (root->left == nullptr && root->right == nullptr)
	{
		printArrPath(arrPath, plen);
		return;
	}

	printAllPathsHelp(root->left, arrPath, plen);
	printAllPathsHelp(root->right, arrPath, plen);
}

void printAllPaths(Node* &root)
{
	int path[1000];
	printAllPathsHelp(root, path, 0);
}

// 2. Пътя от корена на дървото до даден възел

bool pathFromRootToNode(Node* &root, Node* &node, int* arr, int index)
{
	if (root == nullptr)
	{
		return false;
	}

	arr[index++] = root->data;

	if (root == node)
	{
		printArrPath(arr, index);
		return true;
	}

	if (pathFromRootToNode(root->left, node, arr, index) ||
		pathFromRootToNode(root->right, node, arr, index))
	{
		return true;
	}
	return false;
}

bool findPath(Node* &root, Node* &node)
{
	int arr[1000];
	return pathFromRootToNode(root, node, arr, 0);
}

// Сумата на най-дългия път
void findSumHelp(Node* &root, int sum, int length, int &maxSum, int &maxLength)
{
	if (root == nullptr)
	{
		if (length > maxLength)
		{
			maxLength = length;
			maxSum = sum;
		}
		else if (length == maxLength && sum > maxSum)
		{
			maxSum = sum;
		}
		return;
	}

	sum += root->data;

	findSumHelp(root->left, sum, length + 1, maxSum, maxLength);
	findSumHelp(root->right, sum, length + 1, maxSum, maxLength);
}

int findLongestSum(Node* &root)
{
	if (root == nullptr)
	{
		return 0;
	}

	int maxSum = INT_MIN, maxLength = 0;
	findSumHelp(root, 0, 1, maxSum, maxLength);
	return maxSum;
}

/*
Напишете функция, която проверява дали всеки възел от двоично дърво е равен на:
Cумата от лявото и дясното му дете
Cумата от лявото и дясното му поддърво
*/
bool checkChildrenSum(Node* root) {
	if (root == nullptr)
	{
		return true;
	}

	if (root->right != nullptr && root->left == nullptr && root->data != root->right->data)
	{
		return false;
	}
	else if (root->left != nullptr && root->right == nullptr && root->data != root->left->data)
	{
		return false;
	}
	else if (root->right != nullptr && root->left != nullptr && root->data != root->right->data + root->left->data)
	{
		return false;
	}

	return checkChildrenSum(root->left) && checkChildrenSum(root->right);
}

// дали всеки възел от двоично дърво е равен на сумата от лявото и дясното му поддърво

int sum(Node* &root)
{
	if (root == nullptr)
	{
		return 0;
	}

	return root->data + sum(root->left) + sum(root->right);
}

bool check(Node* &root)
{
	if (root == nullptr || (root->left == nullptr && root->right == nullptr))
	{
		return true;
	}

	if (root->data != sum(root->left) + sum(root->right))
	{
		return false;
	}

	return check(root->left) && check(root->right);
}

/*
За дадено двоично дърво проверете дали сумата на покритите и непокритите му възли е равна. 
(непокрити са възлите, намиращи се на лявата и дясната грaница на дървото, а покрити са оставащите възли)
*/
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
	Node* t = new Node{ 8,
		new Node{ 3,
		new Node{ 9 },
		new Node{ 6, new Node{ 4 }, new Node{ 7 } } },
		new Node{ 2, new Node{ 7 }, new Node{ 5 } } };
	Node* t2 = new Node{ 10,
					   new Node{7,
							   new Node{6},
							   new Node{1}},
						new Node{3, new Node{3}, nullptr} };
	std::cout << findHeight(t)<<std::endl;
	std::cout << findLevel(t, t->left->right)<<std::endl;
	std::cout << findSum(t) << std::endl;
	std::cout << findCount(t) << std::endl;
	std::cout << findInnerCount(t) << std::endl;

	std::cout << checkChildrenSum(t2);
    return 0;
}

