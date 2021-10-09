// doublyllTasks2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

template <typename T>
struct Node {
	T data;
	Node* next;
	Node* prev;
	Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr) :data(data), next(next), prev(prev) {}
};

template <typename T>
void pushBack(Node<T>* &first, T data) {
	Node<T>* newNode = new Node<T>(data);
	if (first == nullptr) {
		first = newNode;
	}
	Node<T>* current = first;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = newNode;
	newNode->prev = current;
}

template <typename T>
void print(Node<T>* &first) {
	if (first == nullptr) return;
	Node<T>* current = first;
	while (current != nullptr) {
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

/*Дефинирайте функцията void swapNodes(Node* &first, int element) , която намира подадената стойност в списъка и я 
разменя със стойността на елемента, намиращ се на две позиции назад в списъка (ако е възможно). Ако списъкът не съдържа 
подадената стойност се извежда съобщение, че не е възможна размяна.*/
void swapNodes(Node<int>* &first, int element) {
	if (first == nullptr) return;
	Node<int>* current = first;
	while (current != nullptr)
	{
		if (current->data == element) {
			if (current->prev->prev == nullptr) {
				return;
			}
			int temp = current->data;
			current->data = current->prev->prev->data;
			current->prev->prev->data = temp;
		}
		current = current->next;
	}
}

void addAfterHelper(Node<int>* &first, int afterElement, int addElement)
{
	if (first == nullptr)
	{
		return;
	}

	Node<int>* newNode = new Node<int>(addElement);
	Node<int>* current = first;

	while (current != nullptr && current->data != afterElement) // Стигаме до елемента след който искаме да добавим
	{
		current = current->next;
	}

	if (current->next == nullptr) // Ако елемента след който искаме да добавим (afterElement) е последния елемент от списъка
	{
		current->next = newNode;
		newNode->prev = current;
	}
	else // Ако afterElement е между другите елементи на списъка 
	{
		newNode->next = current->next;
		newNode->prev = current;
		current->next->prev = newNode;
		current->next = newNode;
	}
}
//da raboti ako imame povtarqne na afterElement
void addAfter(Node<int>* &first, int afterElement, int addElement)
{
	if (first == nullptr)
	{
		return;
	}
	Node<int>* newNode = new Node<int>(addElement);
	Node<int>* current = first;
	while (current != nullptr) {
		if (current->data == afterElement)
		{
			addAfterHelper(current, afterElement, addElement);
			
		
		}
		current = current->next;
	}

}
/*
Дефинирайте функцията void moveLast(Node* &first), която мести последния елемент на списъка на първа позиция.
*/

void moveLast(Node<int>* &first)
{
	if (first == nullptr||first->next==nullptr)
	{
		return;
	}

	Node<int>* current = first;
	while (current->next != nullptr) // Стигаме до последния възел
	{
		current = current->next;
	}

	current->prev->next = nullptr;
	current->prev = nullptr;
	current->next = first;
	first->prev = current;
	first = current;
}

/*Дефинирайте функцията void addElement(Node* &first, int N, int element), 
която добавя подадения елемент на всяка N-та позиция в списъка.*/

void addElement(Node<int>* &first, int n, int element)
{
	Node<int>* current = first;
	int count = 1;
	Node<int>* newNode = nullptr;

	while (current != nullptr)
	{
		if (count == n - 1)
		{
			newNode = new Node<int>(element);
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

//четните отпред, нечетните отзад

void rearange(Node<int>* &first) {
	if (first == nullptr) {
		return;
	}
	Node<int>* current = first;
	while (current != nullptr) {
		Node<int>* temp = current->next;
		if (current->data % 2 == 0) {
			if (current->prev == nullptr) {
				current = temp;
				continue;
			}
			if (current->next == nullptr) {
				current->prev->next = nullptr;
				current->next = first;
				current->prev = nullptr;
				first->prev = current;
				first = current;
			}
			else
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;
				current->next = first;
				current->prev = nullptr;
				first->prev = current;
				first = current;
			}
		}
		current = temp;
	}
}
int counter(Node<int>* first) {
	int count = 0;
	if (first == nullptr) {
		return 0;
	}
	while (first != nullptr) {
		++count;
		first = first->next;
	}
	return count;
}
void rearangeOrdered(Node<int>* &first) {
	if (first == nullptr) {
		return;
	}
	Node<int>* current = first;
	while (current->next != nullptr) {
		current = current->next;
	}
	int size = counter(first);
	while (size) {
		Node<int>* temp = current->prev;
		if (current->data % 2 == 0) {
			if (current->prev == nullptr) {
				current = temp;
				continue;
			}
			if (current->next == nullptr) {
				current->prev->next = nullptr;
				current->next = first;
				current->prev = nullptr;
				first->prev = current;
				first = current;
			}
			else
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;
				current->next = first;
				current->prev = nullptr;
				first->prev = current;
				first = current;
			}
		}
		current = temp;
		size--;
	}
}
int main()
{
	Node<int>* first = new Node<int>(1);
	pushBack(first, 2);
	pushBack(first, 3);
	pushBack(first, 4);
	pushBack(first, 6);
	print(first);
	rearangeOrdered(first);
	print(first);
    return 0;
}

