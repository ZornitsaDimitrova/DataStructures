// practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <vector>

template<typename T>
struct Node {
	T data;
	Node<T>* left;
	Node<T>* right;
};

bool isBSTHelp(Node<int> *root, int left, int right)
{
	if (root == nullptr)
	{
		return true;
	}
	if (root->data > left && root->data <= right)
	{
		return isBSTHelp(root->left, left, root->data) &&
			isBSTHelp(root->right, root->data, right);
	}
	return false;
}

bool isBST(Node<int>* root)
{
	return isBSTHelp(root, INT_MIN, INT_MAX);
}


template <typename T>
int countNodes(Node<T>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return 1 + countNodes(root->left) + countNodes(root->right);
}

int calculateSum(Node<int>* numbers, Node<char>* ops)
{
	
	if (numbers == nullptr)
	{
		return 0;
	}

	int currentNodeCalc = 0;
	switch (ops->data)
	{
	case '+':
		currentNodeCalc = numbers->data + countNodes(numbers);
		break;
	case '-':
		currentNodeCalc = numbers->data - countNodes(numbers);
		break;
	case '*':
		currentNodeCalc = numbers->data * countNodes(numbers);
		break;
	default: 
		assert(false);
	}

	return currentNodeCalc + calculateSum(numbers->left, ops->left) + calculateSum(numbers->right, ops->right);
}

template <typename T>
bool parralelTreesHelper(Node<T> * left, Node<T> * right)
{
	if (left == nullptr && right == nullptr)
	{
		return true;
	}
	if (left == nullptr || right == nullptr)
	{
		return false;
	}
	if (left->data == right->data)
	{
		return parralelTreesHelper(left->left, right->right) && parralelTreesHelper(left->right, right->left);
	}
	return false;

}

template <typename T>
bool parralelTree(Node<T> * root)
{
	if (root == nullptr)
	{
		return true;
	}
	return parralelTreesHelper(root->left, root->right);

}

template <typename T>
bool isPalindrome(std::vector<T> elementsAtLevel)
{
	size_t size = elementsAtLevel.size();
	for (int i = 0; i < size / 2; i++)
	{
		if( elementsAtLevel[i] != elementsAtLevel[size - i - 1])
			return false;
	}
	return true;
}

template <typename T>
void palindromeAtLevelHelper(Node<T> *root, int k, std::vector<T> &elementsAtLevel)
{
	if (root == nullptr)
	{
		return;
	}
	if (k == 0)
	{
		elementsAtLevel.push_back(root->data);
	}
	palindromeAtLevelHelper(root->left, k - 1, elementsAtLevel);
	palindromeAtLevelHelper(root->right, k - 1, elementsAtLevel);
}

template <typename T>
bool palindromeAtLevel(Node<T> *root, int k)
{
	if (root == nullptr || k == 0)
	{
		return true;
	}
	std::vector<T> elementsAtLevel;
	palindromeAtLevelHelper(root, k, elementsAtLevel);
	return  isPalindrome(elementsAtLevel);
}

void testPalindromeAtLevel()
{
	Node<int> *t = new Node<int>{ 1,
		new Node<int>{ 3,
		new Node<int>{ 1, nullptr, nullptr },
		new Node<int>{ 2, nullptr, nullptr}},
		new Node<int>{ 7,
		new Node<int>{ 2, nullptr, nullptr},
		new Node<int>{ 1, nullptr, nullptr}} };

	assert(palindromeAtLevel(t, 2));
	assert(palindromeAtLevel(t, 1)==false);


}

template<typename T>
bool isSubtree(Node<T> * tree, Node<T> *subtree)
{
	if (subtree == nullptr)
	{
		return true;
	}
	if (tree == nullptr && subtree != nullptr)
	{
		return false;
	}
	if (tree->data != subtree->data)
	{
		return isSubtree(tree->left, subtree) || isSubtree(tree->right, subtree);
	}
	else
	{
		return isSubtree(tree->left, subtree->left) && isSubtree(tree->right, subtree->right);
	}
}

void testIsSubtree() {
	Node<int> *tree = new Node<int>{1,
	    new Node<int>{2,
	    new Node<int>{7, nullptr, nullptr},
	    new Node<int>{8, nullptr, nullptr}},
	    new Node<int>{6, nullptr, nullptr}};

	Node<int> *subtree = new Node<int>{ 2,
		new Node<int>{ 7, nullptr, nullptr },
		new Node<int>{ 8, nullptr, nullptr } };

	assert(isSubtree(tree, subtree));
}

int main()
{
	testIsSubtree();
    return 0;
}

