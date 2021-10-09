// doublyllBasicOperations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct Node
{
	int data;
	Node* next;
	Node* prev;

	Node(int data, Node* next = nullptr, Node* prev = nullptr)
	{
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
};

// �������� �� ������� � �������� �� �������
void pushFront(Node* &first, int data)
{
	Node* newNode = new Node(data); // ��������� �� ��� ����� � ���������� ��������

	if (first != nullptr)
	{
		newNode->next = first;
		first->prev = newNode;
	}

	first = newNode;
}

// �������� �� ������� � ���� �� �������
void pushBack(Node* &first, int data)
{
	Node* newNode = new Node(data); // ��������� �� ��� ����� � ���������� ��������

	if (first == nullptr)
	{
		first = newNode;
	}
	else
	{
		Node* current = first;
		while (current->next != nullptr) // ������� �� ��������� ������� �� �������
		{
			current = current->next;
		}
		current->next = newNode; // �������� �������������� �����
		newNode->prev = current;
	}
}

// �������� �� ������� ����� ���������� ��������
void pushBefore(Node* &first, int data, int beforeData)
{
	if (first == nullptr)
	{
		return;
	}

	Node* newNode = new Node(data);
	Node* current = first;

	while (current != nullptr && current->data != beforeData) // ������� �� ��������, ����� ����� ������ �� �������
	{
		current = current->next;
	}

	if (current->prev == nullptr) // ��� ������ �� ������� ������� � �������� �� �������
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

// �������� �� ������� ���� ���������� ��������
void pushAfter(Node* &first, int data, int afterData)
{
	if (first == nullptr)
	{
		return;
	}

	Node* newNode = new Node(data);
	Node* current = first;

	while (current != nullptr && current->data != afterData)
	{
		current = current->next;
	}

	if (current->next == nullptr) // ��� ������ �� ������� ������� � ���� �� �������
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
}

// ��������� �� ������ ������� �� �������
void popFirst(Node* &first)
{
	if (first == nullptr)
	{
		return;
	}

	Node* holder = first->next;
	delete first;
	first = holder;
}

// ��������� �� ��������� ������� �� �������
void popLast(Node* &first)
{
	if (first == nullptr)
	{
		return;
	}

	Node* current = first;
	while (current->next != nullptr)
	{
		current = current->next;
	}

	current->prev->next = nullptr;
	delete current;
}

// ��������� �� ������� �� �������� ��������
void popByKey(Node* &first, int data)
{
	if (first == nullptr)
	{
		return;
	}

	Node* current = first;
	while (current != nullptr && current->data != data) // ������� �� ��������, ����� ������ �� �������
	{
		current = current->next;
	}

	if (current->prev == nullptr) // ��� ������ �� ������� ������ ������� �� �������
	{
		current->next->prev = nullptr;
		first = current->next;
	}
	else if (current->next == nullptr) // ��� ������ �� ������� ��������� ������� �� ������� 
	{
		current->prev->next = nullptr;
	}
	else // ��� ������ �� ������� ������� �� ������� �� �������
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}

	delete current;
}

// ��������� �� ������� �� �������� �������
void popAtPos(Node* &first, int pos)
{
	if (first == nullptr)
	{
		return;
	}

	Node* current = first;
	for (int i = 0; i < pos; i++) // ������� �� ���������� �������
	{
		current = current->next;
	}

	if (current->prev == nullptr) // ��� ������ �� ������� ������ ������� �� �������
	{
		current->next->prev = nullptr;
		first = current->next;
	}
	else if (current->next == nullptr) // ��� ������ �� ������� ��������� ������� �� ������� 
	{
		current->prev->next = nullptr;
	}
	else // ��� ������ �� ������� ������� �� ������� �� �������
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}

	delete current;
}

void print(Node* &first)
{
	Node* current = first;
	while (current != nullptr)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << "\n";
}

int main()
{
	Node* first = nullptr;

	pushFront(first, 1);
	pushFront(first, 2);
	pushFront(first, 3);
	pushBack(first, 4);
	pushBack(first, 5);
	pushBack(first, 6);

	print(first);
	pushBefore(first, 10, 4);
	print(first);
	pushAfter(first, 11, 4);
	print(first);
	popLast(first);
	print(first);
	popByKey(first, 4);
	print(first);
	popAtPos(first, 2);
	print(first);

	return 0;
}
