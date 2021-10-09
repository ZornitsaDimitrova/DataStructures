// singlyllTasks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct Node {
	int data;
	Node *next;
    
	Node(int data, Node *next = nullptr) :data(data), next(next) {}
};

void pushBack(Node* &first, int data) {
	Node* newNode = new Node(data);
	if (!first) {
		first = newNode;
		return;
	}
	else
	{
		Node*current = first;
		while (current->next) {
			current = current->next;
		}
		current->next = newNode;
	}
}
void print(Node *first) {
	Node *current = first;
	while (current) {
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

/*
Чрез директно използване на възлите на едносвързан списък,
да се дефинира функцията void swapSecond(Node*& first, int element) ,
която намира подадената стойност в списъка и я разменя със стойността на елемента,
намиращ се на две позиции напред в списъка (ако е възможно). Ако списъкът не съдържа
подадената стойност се извежда съобщение, че не е възможна размяна.*/
/*
Пример:
Входен списък:
first: 1 -> 2 -> 3 -> 4 -> 5
Резултат:
swapWithSecond(first,3): 1 -> 2 -> 5 -> 4 -> 3
*/

void swapSecond(Node*& first, int element) {
	
	if (!first) {
		std::cout << "Empty list" << std::endl;
		return;
	}
	Node* current = first;
	bool swaped = false;
	while (current) {
		if (current->data == element&&current->next->next) {
			int temp = current->next->next->data;
			current->next->next->data = current->data;
			current->data = temp;
			swaped = true;
			current = current->next->next;
		}
		current = current->next;
	}
	if (!swaped) {
		std::cout << "Impossible opration" << std::endl;
	}
}
/*
Чрез директно използване на възлите на едносвързан списък,
да се дефинира функцията void splitList(Node* &first),
която разделя подадения свързан списък по средата и принтира новополучените списъци.*/
/*
Пример:
Входен списък:
first: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
Резултат:
splitList(first):
1 -> 2 -> 3 -> 4 -> 5
6 -> 7 -> 8 -> 9 -> 10
*/
int countOfNodes(Node* first) {
	Node* current = first;
	int count = 0;
	while (current) {
		count++;
		current = current->next;
	}
	return count;
}

void splitList(Node* &first) {
	int middle = countOfNodes(first) / 2;
	Node*current = first;
	for (int i = 0; i < middle - 1; i++) {
		current = current->next;
	}
	Node*second = current->next;
	current->next = nullptr;
	print(first);
	print(second);
}
/*
Чрез директно използване на възлите на едносвързан списък, да се дефинира функцията void rearrangeList(Node* &first),
която разделя подадения свързан списък по средата и разменя местата на първата и втората му половина (за удобство приемаме,
че списъка се състои от четен брой елементи).*/
/*
Пример:
Входен списък:
first: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
Резултат:
rearrangeList(first): 6 -> 7 -> 8 -> 9 -> 10 -> 1 -> 2 -> 3 -> 4 -> 5
*/
void rearrangeList(Node* &first) {
	if (!first) {
		return;
	}
	Node*current = first;
	size_t middle = countOfNodes(first)/2;
	for (int i = 0; i < middle - 1; i++) {
		current = current->next;
	}
	Node* second = current->next;
	current->next = nullptr; // разделяме списъка на две части

	Node* secondCurr = second;
	while (secondCurr->next != nullptr) // обхождаме втората част от списъка
	{
		secondCurr = secondCurr->next;
	}
	secondCurr->next = first; // закачаме втората част от списъка за първата
	first = second;
}

int main()
{
	Node* first = nullptr;
	pushBack(first, 1);
	pushBack(first, 2);
	pushBack(first, 3);
	pushBack(first, 4);
	pushBack(first, 5);
	pushBack(first, 6);
	print(first);
	swapSecond(first, 2);
	print(first);
	rearrangeList(first);
	print(first);

	
}

