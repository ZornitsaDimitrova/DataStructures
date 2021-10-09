// doublyllBasicOperations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

template <typename T>
struct Node {
	T data;
	Node* next;
	Node* prev;
	Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr) : data(data), next(next), prev(prev) {}
};

template <typename T>
void pushBack(Node<T>* &first, T data) {
	
	Node<T>* newNode = new Node<T>(data);
	if (first == nullptr) {
		first = newNode;
	}
	else {
		Node<T>* current = first;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
		newNode->prev = current;
	}

}

template <typename T>
void pushFront(Node<T>* &first, T data) {
	Node<T>* newNode = new Node<T>(data);
	if (first != nullptr) {
		newNode->next = first;
		first->prev = newNode;
	}
	first = newNode;
}

template <typename T>
void pushBefore(Node<T>* &first, T data, T beforeData)
{
	if (first == nullptr)
	{
		return;
	}

	Node<T>* newNode = new Node<T>(data);
	Node<T>* current = first;

	while (current != nullptr && current->data != beforeData) // Стигаме до елемента, преди който искаме да добавим
	{
		current = current->next;
	}

	if (current->data != beforeData) {
		if (current->prev == nullptr) // Ако искаме да добавим елемент в началото на списъка
		{
			newNode->next = current;
			current->prev = newNode;
			first = newNode;
		}
		else
		{
			newNode->next = current;
			newNode->prev = current->prev;
			current->prev->next = newNode;
			current->prev = newNode;
		}
	}
}

template <typename T>
void pushAfter(Node<T>* &first, T data, T afterData) {
	Node<T>* newNode = new Node<T>(data);
	if (first == nullptr) {
		return;
	}
	
	Node<T>* current = first;
	while (current != nullptr && current->data!=afterData) {
		current = current->next;
	}
	if (current->data = afterData)
	{
		if (current->next == nullptr) {
			current->next = newNode;
			newNode->prev = current;
		}
		else {
			newNode->prev = current;
			newNode->next = current->next;
			current->next->prev = newNode;
			current->next = newNode;
		}
	}
}
template <typename T>
void popFirst(Node<T>* &first)
{
	if (first == nullptr) return;
	Node<T>* temp = first->next;
	//first->next->prev = nullptr;
	delete first;
	first = temp;
}

template <typename T>
void popLast(Node<T>* &first)
{
	if (first == nullptr) return;
	Node<T>* current = first;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->prev->next = nullptr;
	delete current;
}

template <typename T>
void popByKey(Node<T>* &first, T data) {
	if (first == nullptr) {
		return;
	}
	Node<T>* current = first;
	while (current != nullptr && current->data != data) {
		current = current->next;
	}
	if (current->data == data) {
		if (current->prev == nullptr) {
			current->next->prev == nullptr;
			first = current->next; 

		}
		else if (current->next == nullptr) {
			current->prev->next = nullptr;
		}
		else {
			current->next->prev = current->prev;
			current->prev->next = current->next;
		}
		delete current;
	}
}
template <typename T>
void print(Node<T>* first) {
	Node<T>* current = first;
	while (current != nullptr) {
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

template <typename T>
void popAtPos(Node<T>* &first, int pos) {
	if (first == nullptr) return;
	Node<T>* current = first;
	for (pos; (pos > 0) && (current != nullptr); --pos) {
		current = current->next;
	}
	if (pos == 0) {
		if (current->prev == nullptr) {
			current->next->prev == nullptr;
			first = current->next; 

		}
		else if (current->next == nullptr) {
			current->prev->next = nullptr;
		}
		else {
			current->next->prev = current->prev;
			current->prev->next = current->next;
		}
		delete current;
	}

}

int main()
{
	Node<int>* first = new Node<int>(1);
	pushBack(first, 2);
	pushBack(first, 4);
	pushBack(first, 4);
	pushBack(first, 5);
	pushFront(first, 10);
	print(first);
	popAtPos(first, 2);
	print(first);
    return 0;
}

