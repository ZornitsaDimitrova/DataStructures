// practice2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

template <typename T>
struct Node {
	T data;
	Node<T> *left;
	Node<T> *right;
};

template <typename T>
int height(Node<T> *root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return 1 + std::max(height(root->left), height(root->right));
}

void testHeight()
{
	Node<int>* tree = new Node<int>{ 8,
	new Node<int>{3,
	new Node<int>{9, nullptr, nullptr},
	new Node<int>{6,
	new Node<int>{4, nullptr, nullptr},
	new Node<int>{7, nullptr, nullptr}}},
	new Node<int>{2,
	new Node<int>{7, nullptr, nullptr},
	new Node<int>{5, nullptr, nullptr}} };

	assert(height(tree) == 4);
}

template <typename T>
int findLevelHelper(Node<T>* tree, Node<T> *nodeToFind, int level)
{
	if (tree == nullptr)
	{
		return 0;
	}
	if (tree->data == nodeToFind->data)
	{
		return level;
	}
	int leftLevel = findLevelHelper(tree->left, nodeToFind, level + 1);
	if (leftLevel != 0)
	{
		return leftLevel;
	}
	return findLevelHelper(tree->right, nodeToFind, level + 1);
}

template <typename T>
int findNodeLevel(Node<T>* tree, Node<T>* nodeToFind)
{
	if (tree == nullptr)
	{
		assert(false);
	}
	int level = 1;
	return findLevelHelper(tree, nodeToFind, level);
}

void testFindLevel()
{
	Node<int>* tree = new Node<int>{ 8,
		new Node<int>{ 3,
		new Node<int>{ 9, nullptr, nullptr },
		new Node<int>{ 6,
		new Node<int>{ 4, nullptr, nullptr },
		new Node<int>{ 7, nullptr, nullptr } } },
		new Node<int>{ 2,
		new Node<int>{ 7, nullptr, nullptr },
		new Node<int>{ 5, nullptr, nullptr } } };

	assert(findNodeLevel(tree, tree->left->right) == 3);
}

int innerNodesCount(Node<int> *tree) {
	if (tree == nullptr)
	{
		return 0;
	}
	if (tree->left == nullptr || tree->right == nullptr)
	{
		return 0;
	}
	return 1 + innerNodesCount(tree->left) + innerNodesCount(tree->right);
}

void testInnerNodesCount()
{
	Node<int>* tree = new Node<int>{ 8,
		new Node<int>{ 3,
		new Node<int>{ 9, nullptr, nullptr },
		new Node<int>{ 6,
		new Node<int>{ 4, nullptr, nullptr },
		new Node<int>{ 7, nullptr, nullptr } } },
		new Node<int>{ 2,
		new Node<int>{ 7, nullptr, nullptr },
		new Node<int>{ 5, nullptr, nullptr } } };

	assert(innerNodesCount(tree) == 4);
}

template <typename T>
void printPath(std::vector<T> path)
{
	for (int i = 0; i < path.size(); i++)
	{
		std::cout << path[i] << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void printAllPathsHelper(Node<T> *tree, std::vector<T> path)
{
	if (tree == nullptr)
	{
		return;  
	}
	path.push_back(tree->data);
	if (tree->left == nullptr && tree->right == nullptr)
	{
		printPath(path);
		return;
	}

	printAllPathsHelper(tree->left, path);
	printAllPathsHelper(tree->right, path);
}

template <typename T>
void printAllPaths(Node<T> *tree)
{
	std::vector<T> v;
	printAllPathsHelper(tree, v);
}

int main()
{
	testInnerNodesCount();
	Node<int>* t = new Node<int>{ 8,
	new Node<int>{3,
	new Node<int>{9, nullptr, nullptr},
	new Node <int>{6,
	new Node <int>{4,
	new Node <int>{10, nullptr, nullptr},
	nullptr},
	new Node <int>{7, nullptr, nullptr}}},
	new Node<int>{2,
	new Node<int>{1, nullptr, nullptr},
	new Node<int>{5, nullptr, nullptr}} };
	printAllPaths(t);
    return 0;
}

