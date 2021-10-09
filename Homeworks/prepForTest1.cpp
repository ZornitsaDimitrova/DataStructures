// test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <stack>
#include <cmath>

//task1

template <typename T>
struct Node {
	T data;
	Node* next;
	Node(T data, Node<T>* next = nullptr) :data(data), next(next) {};
};

template <typename T>
void pushBack(Node<T>* &first, T data)
{
	Node<T>* newNode = new Node<T>(data);
	if (first == nullptr)
	{
		first = newNode;
	}
	Node<T>* current = first;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	current->next = newNode;
}

template <typename T>
T reduce(Node<T>* &first, T(*F) (const T&, const T&)) {
	if (first == nullptr)
	{
		throw std::runtime_error("The list is empty!");
	}
	if (first->next == nullptr) {
		return first->data;
	}
	Node<T>* current = first;
	T temp;
	while (current != nullptr && current->next != nullptr) {
		temp = F(current->data, current->next->data);
		current = current->next;
		current->data = temp;
	}
	return current->data;
}

int div(const int &x, const int &y) 
{
	return x / y;
}

template <typename T>
void print(Node<T>* first) {
	if (first == nullptr) return;
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

//task 2

void reduceStack(Node<std::stack<int>>* &first, void(*F) (std::stack<int>&, std::stack<int>&)) {
	if (first == nullptr)
	{
		throw std::runtime_error("The list is empty!");
	}
	if (first->next == nullptr) {
		return;
	}
	Node<std::stack<int>>* current = first;
	Node<std::stack<int>>* temp;
	while (current != nullptr && current->next != nullptr)
	{
		temp = current->next;
		while (temp != nullptr)
		{
			F(current->data, temp->data);
			temp = temp->next;
		}
		current = current->next;
	}

}


void equalize(std::stack<int>& s1, std::stack<int>& s2)
{
		while (std::abs((int)s1.size() - (int)s2.size()) > 1)
		{
			if (s1.size() > s2.size())
			{
				s2.push(s1.top());
				s1.pop();
			}
			else
			{
				s1.push(s2.top());
				s2.pop();
			}
		}
}

void printStackSizes(Node<std::stack<int>>* first) {
	if (first == nullptr) return;
	while (first != nullptr) 
	{
		std::cout << first->data.size() << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

//task3
template<typename T>
struct DLLNode {
	T data;
	DLLNode* next;
	DLLNode* prev;
	DLLNode(T data, DLLNode<T>* next = nullptr, DLLNode<T>* prev = nullptr) :data(data), next(next), prev(prev) {};
};

template<typename T>
void pushBackDLL(DLLNode<T>* &first, T data) 
{
	DLLNode<T>* newNode = new DLLNode<T>(data);
	if (first == nullptr)
	{
		first = newNode;
	}
	DLLNode<T>* current = first;
	while (current->next != nullptr) 
	{
		current = current->next;
	}
	current->next = newNode;
	newNode->prev = current;
}


template<typename T>
int countNodes(DLLNode<T>* first)
{
	if (first == nullptr)
	{
		return 0;
	}
	int count = 0;
	while (first != nullptr) 
	{
		++count;
		first = first->next;
	}
	return count;
}

template<typename T>
void shuffle(DLLNode<T>* &first) 
{
	if (first == nullptr || first->next == nullptr) 
	{
		return;
	}
	DLLNode<T>* current = first;
	int size = countNodes(first);
	int middle = ((size % 2) == 0 ) ? (size / 2) : (size / 2 + 1);
	while (middle)
	{
		current = current->next;
		middle--;
	}
	while (current != nullptr) {
		DLLNode<T>* temp = current->next;
		if (current->next == nullptr) {
			current->prev->next = nullptr;
			current->next = first;
			first->prev = current;
			first = current;
		}
		else
		{
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current->prev = nullptr;
			current->next = first;
			first->prev = current;
			first = current;
		}
		current = temp;
	}
}

template<typename T>
void printDLL(DLLNode<T>* first) {
	if (first == nullptr)
	{
		return;
	}
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

int main()
{
	/*TASK1
	Node<int>* first = new Node<int>(1024);
	pushBack(first, 16);
	pushBack(first, 4);
	pushBack(first, 2);
	print(first);
	std::cout << reduce(first, div);
	*/

	//TASK2
	std::stack<int> s1, s2, s3, s4;
	s1.push(5);
	s1.push(4);
	s1.push(3);
	s1.push(2);
	s1.push(1);
	s2.push(7);
	s2.push(6);
	s3.push(11);
	s3.push(10);
	s3.push(9);
	s3.push(8);
	s4.push(12);
	s4.push(10);
	s4.push(17);
	
	Node<std::stack<int>>* first = new Node<std::stack<int>>(s1);
	pushBack(first, s2);
	pushBack(first, s3);
	pushBack(first, s4);
	reduceStack(first, equalize);
	printStackSizes(first);
	

	/*TASK3
	DLLNode<int>* first = new DLLNode<int>(1);
	pushBackDLL(first, 2);
	pushBackDLL(first, 3);
	pushBackDLL(first, 4);
	pushBackDLL(first, 5);
	printDLL(first);
	shuffle(first);
	printDLL(first);
	*/
    return 0;
}

