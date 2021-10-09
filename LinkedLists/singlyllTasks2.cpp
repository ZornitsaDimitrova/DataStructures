// singlyllTasks2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


struct Node
{
	int data;
	Node* next;

	Node(const int& data, Node* next = nullptr)
	{
		this->data = data;
		this->next = next;
	}
};

void pushBack(Node* &first, int data) //*& ������� ��������� ������ (��� ���� ���� �� �� ������ ��������� �� ��������� ������)
{
	Node* newNode = new Node(data);
	if (first == nullptr)
	{
		first = new Node(data);
		return;
	}

	Node* cur = first;
	while (cur->next != nullptr)
	{
		cur = cur->next;
	}
	cur->next = newNode;
}

void print(Node* &first)
{
	Node* cur = first;
	while (cur != nullptr)
	{
		std::cout << cur->data << " ";
		cur = cur->next;
	}
	std::cout << "\n";
}

/*
���� �������� ���������� �� ������� �� ����������� ������,
�� �� �������� ��������� void swapSecond(Node*& first, int element) ,
����� ������ ���������� �������� � ������� � � ������� ��� ���������� �� ��������,
������� �� �� ��� ������� ������ � ������� (��� � ��������). ��� �������� �� �������
���������� �������� �� ������� ���������, �� �� � �������� �������.*/
/*
������:
������ ������:
first: 1 -> 2 -> 3 -> 4 -> 5
��������:
swapWithSecond(first,3): 1 -> 2 -> 5 -> 4 -> 3
*/

void swapSecond(Node*& first, int element)
{
	if (first == nullptr)
	{
		return;
	}

	Node* cur = first;
	while (cur->next != nullptr)
	{
		if (cur->data == element && cur->next->next != nullptr)
		{
			int tempData = cur->data;
			cur->data = cur->next->next->data;
			cur->next->next->data = tempData;
		}

		cur = cur->next;
	}
}

/*
���� �������� ���������� �� ������� �� ����������� ������,
�� �� �������� ��������� void splitList(Node* &first), 
����� ������� ��������� ������� ������ �� ������� � �������� �������������� �������.*/
/*
������:
������ ������:
first: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
��������:
splitList(first):
1 -> 2 -> 3 -> 4 -> 5
6 -> 7 -> 8 -> 9 -> 10
*/

int countOfNodes(Node* &first)
{
	Node* current = first;
	int count = 0;
	while (current != nullptr)
	{
		count++;
		current = current->next;
	}
	return count;
}

void splitList(Node* &first)
{
	int middle = countOfNodes(first) / 2;
	Node* current = first;

	for (int i = 0; i < middle - 1; i++)
	{
		current = current->next;
	}

	Node* second = current->next;
	current->next = nullptr; // ��������� ������� �� ��� �����

	print(first);
	print(second);
}

/*
���� �������� ���������� �� ������� �� ����������� ������, �� �� �������� ��������� void rearrangeList(Node* &first), 
����� ������� ��������� ������� ������ �� ������� � ������� ������� �� ������� � ������� �� �������� (�� �������� ��������, 
�� ������� �� ������ �� ����� ���� ��������).*/
/*
������:
������ ������:
first: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
��������:
rearrangeList(first): 6 -> 7 -> 8 -> 9 -> 10 -> 1 -> 2 -> 3 -> 4 -> 5
*/

void rearrangeList(Node* &first)
{
	int middlePos = countOfNodes(first) / 2;
	Node* current = first;
	for (int i = 0; i < middlePos - 1; i++)
	{
		current = current->next;
	}

	Node* second = current->next;
	current->next = nullptr; // ��������� ������� �� ��� �����

	Node* secondCurr = second;
	while (secondCurr->next != nullptr) // ��������� ������� ���� �� �������
	{
		secondCurr = secondCurr->next;
	}
	secondCurr->next = first; // �������� ������� ���� �� ������� �� �������
	first = second;
}

/*
����������� ��������� Node* constructList(Node* &first, int n), ����� ������ N-��� ������� �� �������� � �� ���� �� ��������� 
������ � ����� ��� ������, ������� �� �� ����������, �������� �� ����� ���.*/
/*
������:
������ ������:
first: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
��������:
constructList(first,3): 4 -> 5 -> 6 -> 7
*/

Node* constructList(Node* &first, int n)
{
	Node* current = first;
	Node* newList = nullptr;

	int size = countOfNodes(first);
	int lastN = size - n + 1;

	for (int i = 1; i <= size; i++)
	{
		if (i > n && i < lastN)
		{
			pushBack(newList, current->data);
		}

		current = current->next;
	}
	return newList;
}

int main()
{
	Node* first = nullptr;
	pushBack(first, 1);
	pushBack(first, 2);
	pushBack(first, 3);
	pushBack(first, 4);

	print(first);
	std::cout << std::endl;
	swapSecond(first, 2);
	print(first);
	splitList(first);
	rearrangeList(first);
	print(first);

	Node* first2 = nullptr;

	pushBack(first2, 1);
	pushBack(first2, 2);
	pushBack(first2, 3);
	pushBack(first2, 4);
	pushBack(first2, 5);
	pushBack(first2, 6);
	pushBack(first2, 7);
	pushBack(first2, 8);
	pushBack(first2, 9);
	pushBack(first2, 10);

	print(first2);
	Node* result = constructList(first2, 3);
	print(result);

    return 0;
}

