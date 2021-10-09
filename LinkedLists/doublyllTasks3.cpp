// doublyllTasks3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct Node
{
	char data;
	Node *next, *prev;

	Node(char data, Node* prev = nullptr, Node* next = nullptr)
	{
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
};

void pushBack(Node*& first, char data)
{
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

	Node* newNode = new Node(data, cur);
	cur->next = newNode;
}

/*
������ 1:
���� �������� ���������� �� ������� �� ���������� ������:

-�������� �������, ����� ��������� ��� ������� ���� ������� ����� ��� #

������: T->H->I->N->K      S->M->I->L->E

�������: T->H->I->N->K->#->S->M->I->L->E
-�������� �������, ����� �� ����� ������ ��� ������� �� ���������� ���� ��������� � # ���� �� �� ������� ����,
�� ���� ���� �������� �� ���������� ����� �� �������������� �� ������� � ������� ����� �� ����������
(��� ������ �� ���� ��� �������� False)

������: T->H->I->N->K->#->S->M->I->L->E->#->K->N->O->W->#->E->A->T     �������: True

������: T->H->I->N->K->#->S->M->I->L->E->#->O->L->D       �������: False
*/



void mergeList(Node*& firstList, Node*& secondList)
{
	Node* cur = firstList;
	Node* newNode = new Node('#');

	while (cur->next != nullptr)
	{
		cur = cur->next;
	}

	cur->next = newNode;
	newNode->prev = cur;
	newNode->next = secondList;
	secondList->prev = newNode;
	secondList = nullptr;
}

bool haveDublicate(Node*& first)
{
	if (first == nullptr || first->next == nullptr)
	{
		return false;
	}

	Node* cur = first;
	Node* nextCur = nullptr;

	while (cur->next != nullptr)
	{
		if (cur->data != '#')
		{
			cur = cur->next;
		}

		char element = cur->prev->data;
		if (cur->next != nullptr && element == cur->next->data)
		{
			return true;
		}

		nextCur = cur->next;
		while (nextCur->next != nullptr)
		{
			if (nextCur->data == '#' && nextCur->next != nullptr && nextCur->next->data == element)
			{
				return true;
			}

			nextCur = nextCur->next;
		}

		cur = cur->next;
	}

	return false;
}

/*

������ 2:
���� �������� ���������� �� ������� �� ���������� ������, ��� �������������� ���������� �� ��� �������� � �������, 
���������� ������ �� ���������� ��������� ��.

������: 1->2->3->3->3->4

�������: 1->2->3->3->4

������: 1->2->3->3->3->3->4

�������: 1->2->3->3->4
*/
void removeFirstElement(Node*& first)
{
	Node* cur = first;
	int count = 0;

	while (cur->next != nullptr)
	{
		if (cur->next->data == cur->data)
		{
			++count;
			if (count == 2)
			{
				Node* removeNode = new Node(cur->prev->data);
				cur->prev->prev->next = cur;
				cur->prev = cur->prev->prev;

				delete removeNode;
				count = 0;
				continue;
			}
		}
		cur = cur->next;
	}
}

/*

������ 3:
���� �������� ���������� �� ������� �� ���������� ������, �������� �������, ����� ������ ������� � ������� ��� � ������� �� ����� ����� ����� �� ������� �� �������.

������: '1'->'2'->'3'

�������: '6'->'3'->'2'->'1'
�������...
*/
void reverseSum(Node*& first)
{
	Node* cur = first;
	Node* copy = nullptr;

	int sum = 0;

	while (cur != nullptr)
	{
		sum += cur->data - '0';

		copy = cur->prev;
		cur->prev = cur->next;
		cur->next = copy;
		cur = cur->prev;
	}

	if (copy != nullptr)
	{
		first = copy->prev;
	}

	Node* temp = new Node(sum + '0', nullptr, first);
	first->prev = temp;
	first = temp;
}
int main()
{
	Node* first = nullptr;

	pushBack(first, '6');
	pushBack(first, '1');
	pushBack(first, '5');
	pushBack(first, '7');
	pushBack(first, '4');

	Node* second = nullptr;

	pushBack(second, '4');
	pushBack(second, '8');
	pushBack(second, '9');
	pushBack(second, '#');
	pushBack(second, '9');
	pushBack(second, '7');

	mergeList(first, second);

	std::cout << haveDublicate(first) << std::endl;
	pushBack(first, '1');
	pushBack(first, '2');
	pushBack(first, '3');
	pushBack(first, '3');
	pushBack(first, '3');
	pushBack(first, '4');

	removeFirstElement(first);

	print(first);

	reverseSum(first);

	print(first);

	return 0;
}

