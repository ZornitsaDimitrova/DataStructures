#include "stdafx.h"
#include "DoublyLinkedList.h"
#include <iostream>

void DoublyLinkedList::copy(const DoublyLinkedList& otherList)
{
	Node* copyFirst = new Node(otherList.first->data);
	this->first = copyFirst;

	Node* copyCurrent = this->first;
	Node* otherCurrent = otherList.first;
	Node* newNode = nullptr;

	while (otherCurrent->next != nullptr)
	{
		newNode = new Node(otherCurrent->next->data);
		copyCurrent->next = newNode;
		newNode->prev = copyCurrent;

		copyCurrent = copyCurrent->next;
		otherCurrent = otherCurrent->next;
	}
	this->last = copyCurrent;
}

void DoublyLinkedList::clear()
{
	Node* holder = nullptr;
	while (this->first != nullptr)
	{
		holder = this->first->next;
		delete this->first;
		this->first = holder;
	}
	this->last = nullptr;
}

DoublyLinkedList::DoublyLinkedList()
{
	this->first = nullptr;
	this->last = nullptr;
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& otherList)
{
	this->copy(otherList);
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& otherList)
{
	if (this != &otherList)
	{
		this->clear();
		this->copy(otherList);
	}
	return *this;
}

DoublyLinkedList::~DoublyLinkedList()
{
	this->clear();
}

void DoublyLinkedList::pushFront(int data)
{
	Node* newNode = new Node(data);
	newNode->next = this->first;

	if (this->first == nullptr) // ��� ������� � ������
	{
		this->last = newNode;
	}
	else
	{
		this->first->prev = newNode;
	}
	this->first = newNode; // ������������� ����� ����� ����� ������� � �������
}

void DoublyLinkedList::pushBack(int data)
{
	Node* newNode = new Node(data);
	newNode->prev = this->last;

	if (this->last == nullptr) // ��� ������� � ������
	{
		this->first = newNode;
	}
	else
	{
		this->last->next = newNode;
	}
	this->last = newNode; // ������������� ����� � ��������� ������� �� �������
}

void DoublyLinkedList::removeByKey(int data)
{
	Node* current = this->first;
	while (current != nullptr && current->data != data) // ������� �� ��������, ����� ������ �� �������
	{
		current = current->next;
	}

	if (current->prev == nullptr) // ��� ������ �� ������� ������ ������� �� �������
	{
		current->next->prev = nullptr;
		this->first = current->next;
	}
	else if (current->next == nullptr) // ��� ������ �� ������� ��������� ������� �� ������� 
	{
		current->prev->next = nullptr;
		this->last = current->prev;
	}
	else // ��� ������ �� ������� ������� �� ������� �� �������
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	delete current;
}

void DoublyLinkedList::removeByNode(Node* toRemove)
{
	if (toRemove->prev == nullptr)
	{
		toRemove->next->prev = nullptr;
		this->first = toRemove->next;
	}
	else if (toRemove->next == nullptr)
	{
		toRemove->prev->next = nullptr;
		this->last = toRemove->prev;
	}
	else
	{
		toRemove->prev->next = toRemove->next;
		toRemove->next->prev = toRemove->prev;
	}
	delete toRemove;
}

int DoublyLinkedList::count(int x)
{
	int counter = 0;
	Node* current = first;
	while (current != nullptr) {
		if (current->data == x) ++counter;
		current = current->next;
	}
	return counter;
}

void DoublyLinkedList::print() const
{
	Node* current = this->first;
	while (current != nullptr)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << "\n";
}
