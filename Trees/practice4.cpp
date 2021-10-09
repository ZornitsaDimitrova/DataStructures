// practice4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <vector>

template <typename T>
struct Node
{
	T data;
	Node *left;
	Node *right;
};

bool isBinOrderedTreeHelper(int left, int right, Node<int> *current)
{
	if (current == nullptr)
	{
		return true;
	}

	if (left < current->data && current->data <= right)
	{
		return isBinOrderedTreeHelper(left, current->data, current->left) &&
			isBinOrderedTreeHelper(current->data, right, current->right);
	}
	return false;
}

bool isBinOrderedTree(Node<int> *root)
{
	return isBinOrderedTreeHelper(INT_MIN, INT_MAX, root);
}

void testTask1() {
	Node<int> * t = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 70,nullptr,nullptr } };
	assert(isBinOrderedTree(t));
}

template<typename T>
size_t cntNodes(Node<T>* current)
{
	if (current == nullptr)
	{
		return 0;
	}
	return 1 + cntNodes(current->left) + cntNodes(current->right);
}

template<typename T>
T sumTrees(Node<T>* numbers, Node<char>* operators)
{
	if (numbers == nullptr && operators == nullptr)
	{
		return 0;
	}
	T currentNodeCalc;
	switch (operators->data)
	{
	case '+':
		currentNodeCalc = numbers->data + cntNodes(numbers);
		break;
	case '-':
		currentNodeCalc = numbers->data - cntNodes(numbers);
		break;
	case '*':
		currentNodeCalc = numbers->data * cntNodes(numbers);
		break;
	default:
		assert(false);
	}

	return currentNodeCalc + sumTrees(numbers->left, operators->left) +
		sumTrees(numbers->right, operators->right);

}

void testTask2() {
	Node<int> * t = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 70,nullptr,nullptr } };
	Node<char> * t1 = new Node<char>{ '+',
		new Node<char>{ '-',
		new Node<char>{ '*',nullptr,nullptr },
		new Node<char>{ '+',nullptr,nullptr } },
		new Node<char>{ '+',nullptr,nullptr } };
	//(10+5) + (5-3) + (2*1) + (7+1) + (70+1) = 15 + 2 + 2 + 8 + 71 = 98 
	assert(sumTrees(t, t1) == 98);
}

template <class T>
bool parralelTreesHelper(Node<T>* leftSubtree, Node<T>* rightSubtree) {
	if (leftSubtree == nullptr && rightSubtree == nullptr)
	{
		return true;
	}
	if (leftSubtree == nullptr || rightSubtree == nullptr)
	{
		return false;
	}
	return leftSubtree->data == rightSubtree->data
		&& parralelTreesHelper(leftSubtree->left, rightSubtree->right)
		&& parralelTreesHelper(leftSubtree->right, rightSubtree->left);
}

template<typename T>
bool parralelTrees(Node<T>* current)
{
	if (current == nullptr)
	{
		return true;
	}
	return parralelTreesHelper(current->left, current->right);
}

void testTask3() {
	Node<int> * t = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 70,nullptr,nullptr } };
	assert(parralelTrees(t) == false);
	Node<int> * t2 = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 5,
		new Node<int>{ 7,nullptr,nullptr },
		new Node<int>{ 2,nullptr,nullptr } } };
	assert(parralelTrees(t2));
}

template<typename T>
void palindromeTreesHelper(Node<T>* current, size_t level, std::vector<T>& nodes)
{
	if (current == nullptr)
	{
		return;
	}
	if (level == 0 && current != nullptr)
	{
		nodes.push_back(current->data);
		return;
	}
	palindromeTreesHelper(current->left, level - 1, nodes);
	palindromeTreesHelper(current->right, level - 1, nodes);
}

template<typename T>
bool isPalindrome(std::vector<T>& elementsAtLevel)
{
	size_t size = elementsAtLevel.size();
	for (size_t i = 0; i < size / 2; i++)
	{
		if (elementsAtLevel[i] != elementsAtLevel[size - i - 1])
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool palindromeTrees(Node<T>* current, size_t level)
{
	if (current == nullptr || level == 0)
	{
		return true;
	}

	std::vector<T> elementsAtLevel;
	palindromeTreesHelper(current, level, elementsAtLevel);
	return isPalindrome(elementsAtLevel);
}

void testTask4()
{
	Node<int> * t = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 5,nullptr,nullptr } };
	assert(palindromeTrees(t, 1));
	Node<int> * t2 = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 60,
		new Node<int>{ 7,nullptr,nullptr },
		new Node<int>{ 2,nullptr,nullptr } } };
	assert(palindromeTrees(t2, 2));
	assert(palindromeTrees(t2, 1) == false);
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

void testIsSubtree() {
	Node<int> * t = new Node<int>{ 10,
		new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } },
		new Node<int>{ 5,nullptr,nullptr } };
	Node<int> * subtree = new Node<int>{ 5,
		new Node<int>{ 2,nullptr,nullptr },
		new Node<int>{ 7,nullptr,nullptr } };
	assert(isSubtree(t, subtree));
}
int main()
{
	testIsSubtree();
	return 0;
}