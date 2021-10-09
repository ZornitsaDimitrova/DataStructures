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
Задача 1:
Чрез директно използване на възлите на двусвързан списък:

-напишете функция, която обединява два списъка като поставя между тях #

Пример: T->H->I->N->K      S->M->I->L->E

Решение: T->H->I->N->K->#->S->M->I->L->E
-напишете функция, която ви връща истина ако списъка от въведените думи разделени с # може да се подреди така,
че поне една поредица от последната буква на предшественика да съвпада с първата буква на наследника
(Ако думите са само две изведете False)

Пример: T->H->I->N->K->#->S->M->I->L->E->#->K->N->O->W->#->E->A->T     Решение: True

Пример: T->H->I->N->K->#->S->M->I->L->E->#->O->L->D       Решение: False
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

Задача 2:
Чрез директно използване на възлите на двусвързан списък, при последователно повторение на три елемента в списъка, 
премахнете първия от поредицата повтарящи се.

Пример: 1->2->3->3->3->4

Решение: 1->2->3->3->4

Пример: 1->2->3->3->3->3->4

Решение: 1->2->3->3->4
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

Задача 3:
Чрез директно използване на възлите на двусвързан списък, напишете функция, която обръща списъка в обратен ред и поставя на първо място сбора от числата на списъка.

Пример: '1'->'2'->'3'

Решение: '6'->'3'->'2'->'1'
Решение...
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

