// prepForTest2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>

template <typename T>
struct Node
{
	int data;
	Node<T>* next;
	Node<T>* prev;

	Node(int data, Node<T>* next = nullptr, Node<T>* prev = nullptr)
	{
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
};

template <typename T>
void pushBack(Node<T>* &first, T data)
{
	Node<T>* newNode = new Node<T>(data);
	if (first == nullptr)
	{
		first = newNode;
	}
	else
	{
		Node<T>* current = first;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = newNode;
		newNode->prev = current;
	}
}

template <typename T>
void print(Node<T>* first)
{
	if (first == nullptr)
	{
		std::cout << "Empty list!" << std::endl;
		return;
	}
	while (first != nullptr)
	{
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << "\n";
}


template <typename T>
void swapNodes(Node<T>*& first, T element)
{
	if (first == nullptr || first->next == nullptr || first->next->next == nullptr)
	{
		std::cout << "Cannot swap elements\n";
		return;
	}
	bool found = false;
	T temp;
	Node<T>* current = first;

	while (current != nullptr)
	{
		if (current->data == element && current->prev->prev != nullptr)
		{
			found = true;
			temp = current->data;
			current->data = current->prev->prev->data;
			current->prev->prev->data = temp;
		}
		current = current->next;
	}

	if (!found)
	{
		std::cout << "Cannot swap elements\n";
	}
}

template <typename T>
void addAfter(Node<T>* &first, T afterElement, T addElement)
{
	if (first == nullptr)
	{
		return;
	}
	Node<T>*current = first;
	while (current != nullptr)
	{
		if (current->data == afterElement)
		{
			Node<T>* newNode = new Node<T>(addElement);
			if (current->next == nullptr)
			{
				current->next = newNode;
				newNode->prev = current;
			}
			else
			{
				current->next->prev = newNode;
				newNode->prev = current;
				newNode->next = current->next;
				current->next = newNode;
			}
		}
		current = current->next;
	}
}

template <typename T>
void moveLast(Node<T>* &first)
{
	if (first == nullptr)
	{
		return;
	}
	if (first->next == nullptr)
	{
		return;
	}
	Node<T>* current = first;
	while (current->next != nullptr)
	{
		current = current->next;
	}

	current->prev->next = nullptr;
	current->prev = nullptr;
	current->next = first;
	first->prev = current;
	first = current;

}
template <typename T>
void addElement(Node<T>* &first, int N, T element)
{
	Node<T>* current = first;
	int count = 1;
	Node<T>* newNode = nullptr;

	while (current != nullptr)
	{
		if (count == N - 1)
		{
			newNode = new Node<T>(element);
			if (current->next == nullptr)
			{
				current->next = newNode;
				newNode->prev = current;
			}
			else
			{
				newNode->next = current->next;
				newNode->prev = current;
				current->next->prev = newNode;
				current->next = newNode;
			}
			current = newNode;
			count = 0;
		}

		count++;
		current = current->next;
	}
}
int main()
{
	Node<int>* first = nullptr;

	pushBack(first, 1);
	pushBack(first, 2);
	pushBack(first, 3);
	pushBack(first, 4);
	pushBack(first, 5);

	print(first);
	swapNodes(first, 4);
	print(first);

	addAfter(first, 1, 10);
	print(first);
	moveLast(first);
	print(first);
	addElement(first, 2, 12);
	print(first);
    return 0;
}

