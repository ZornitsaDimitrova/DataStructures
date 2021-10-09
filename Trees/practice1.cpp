// practice1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <vector>

template <typename T>
struct Node {
	T data;
	Node<T> * left;
	Node<T> * right;
};

template <typename T>
int countNodes(Node<T>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return 1 + countNodes(root->left) + countNodes(root->right);
}

int sumTrees(Node<int> * numbers, Node<char> *operators)
{
	if (numbers == nullptr && operators == nullptr)
	{
		return 0;
	}
	if (numbers == nullptr || operators == nullptr)
	{
		assert(false);
	}
	int currentNodeCalc = 0;

	switch (operators->data)
	{
	case'+':
		currentNodeCalc = numbers->data + countNodes(numbers);
	case'-':
		currentNodeCalc = numbers->data - countNodes(numbers);
	case'*':
		currentNodeCalc = numbers->data * countNodes(numbers);
	default:
		assert(false);
	}

	return currentNodeCalc + sumTrees(numbers->left, operators->left) + sumTrees(numbers->right, operators->right);
}

template<typename T>
bool parralelTreeHelper(Node<T>* left, Node<T>* right)
{
	if (left == nullptr && right == nullptr)
	{
		return true;
	}
	if (left == nullptr || right == nullptr)
	{
		return false;
	}
	//return left->data == right->data &&
	//parralelTreeHelper(left->left, right->right) && 
	//parralelTreeHelper(left->right, right->left);
	if (left->data == right->data)
	{
		return parralelTreeHelper(left->left, right->right) && parralelTreeHelper(left->right, right->left);
	}
	return false;
}

template<typename T>
bool parralelTree(Node<T> *root)
{
	if (root == nullptr)
	{
		return true;
	}
	return parralelTreeHelper(root->left, root->right);
}

void testTask3() {
	Node<int> * t = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 70,nullptr,nullptr } };
	assert(parralelTree(t) == false);
	Node<int> * t2 = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 5,
		new Node<int>{ 7,nullptr,nullptr },
		new Node<int>{ 2,nullptr,nullptr } } };
	assert(parralelTree(t2));
}

template <typename T>
bool isPalindrome(std::vector<T> elementsAtLevel) {
	size_t size = elementsAtLevel.size();
	for (int i = 0; i < size / 2; i++) {
		if (elementsAtLevel[i] != elementsAtLevel[size - i -1])
		{
			return false;
		}
	}
	return true;
}

template <typename T>
void palindromeAtLevelHelper(Node<T> *root, int level, std::vector<T> &elementsAtLevel)
{
	if (root == nullptr) {
		return;
	}
	if (level == 0 && root != nullptr) {
		elementsAtLevel.push_back(root->data);
		return;
	}
	palindromeAtLevelHelper(root->left, level - 1, elementsAtLevel);
	palindromeAtLevelHelper(root->right, level - 1, elementsAtLevel);
}

template <typename T>
bool palindromeAtLevel(Node<T> *root, int level) {
	if (root == nullptr || level ==0)
	{
		return true;
	}
	std::vector<T> elementsAtLevel;
	palindromeAtLevelHelper(root, level, elementsAtLevel);
	return isPalindrome(elementsAtLevel);
}

void testTask4()
{
	Node<int> * t = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 5,nullptr,nullptr } };
	assert(palindromeAtLevel(t, 1));
	Node<int> * t2 = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 60,
		new Node<int>{ 7,nullptr,nullptr },
		new Node<int>{ 2,nullptr,nullptr } } };
	assert(palindromeAtLevel(t2, 2));
	assert(palindromeAtLevel(t2, 1) == false);
}

template<typename T>
bool isSubtree(Node<T>* current, Node<T>* sub)
{
	if (current == nullptr && sub == nullptr) {
		return true;
	}
	if (current == nullptr || sub == nullptr) {
		return false;
	}

	if (current->data == sub->data)
	{
		return isSubtree(current->left, sub->left) && isSubtree(current->right, sub->right);
	}
	else
	{
		return isSubtree(current->left, sub) || isSubtree(current->right, sub);
	}

}

int main()
{
	testTask4();
    return 0;
}

