// practice1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <vector>
/*
//whether the parentheses match
template <typename T>
struct Node
{
	T data;
	Node* next;
	Node(T data, Node<T>* next = nullptr) :data(data), next(next) {};
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
}

template <typename T>
void print(Node<T>* first) {
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

template <typename T>
bool match(Node<T>* first, bool(*F) (T))
{
	if (first == nullptr)
	{
		return false;
	}

	bool flag = true;
	while (first != nullptr) {
		flag = F(first->data);
		if (flag == false)
		{
			return false;
		}
		first = first->next;
	}
	return flag;
}
bool matchingBrackets(char br1, char br2) {
	return (br1 == '[' && br2 == ']' ||
		br1 == '(' && br2 == ')' ||
		br1 == '{' && br2 == '}');
}

bool checkBrackets(std::string str) {
	std::stack<char> s;
	for (int i = 0; i < str.length(); ++i) {

		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			s.push(str[i]);

		}
		if (str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			if (!matchingBrackets(s.top(), str[i]) || s.empty()) return false;
			s.pop();

		}

	}
	return s.empty();
}
*/
template<typename T>
bool isPalindrome(std::vector<T>& vector)
{
	size_t size = vector.size();
	for (size_t i = 0; i < size / 2; i++)
	{
		if (elementsAtLevel[i] != elementsAtLevel[size - i - 1])
		{
			return false;
		}
	}
	return true;
}

template <typename T>
struct Node {
	T data;
	Node* next;
	Node* prev;
	Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr) :data(data), next(next), prev(prev) {};
};

template <typename T>
void pushBack(Node<T>* &first, T data)
{
	Node<T>* newNode = new Node<T>(data);
	if (first == nullptr)
	{
		first = newNode;
		return;
	}
	Node<T>* current = first;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = newNode;
	newNode->prev = current;
}

template <typename T>
void print(Node<T>* first)
{
	if (first == nullptr)
	{
		return;
	}
	while (first != nullptr)
	{
		std::cout << first->data << " ";
		first = first->next;

	}
	std::cout << std::endl;
}

template <typename T>
int count(Node<T>* first) {
	int count = 0;
	if (first == nullptr)
	{
		return 0;
	}
	while (first != nullptr)
	{
		++count;
		first = first->next;
	}
	return count;
}

template <typename T>
bool isPalindrome(Node<T> *first)
{
	if (first == nullptr || first->next == nullptr)
	{
		return true;
	}

	Node<T>* current = first;
	int middle = count(first) / 2;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	while (middle)
	{
		if (first->data != current->data)
		{
			return false;
		}
		--middle;
		current = current->prev;
		first = first->next;
	}
	return true;
}

double average(double x, double y) {
	return (x + y) / 2;
}

void deleteAverage(Node<double>* &first)
{
	if (first == nullptr || first->next == nullptr || first->next->next == nullptr)
	{
		return;
	}
	Node<double>* current = first;
	while (current != nullptr && current->next != nullptr && current->next->next != nullptr)
	{
		Node<double>* temp = current->next;
		if (current->data == average(current->next->data, current->next->next->data)) {
			if (current->prev == nullptr) {
				current->next->prev = nullptr;
				first = current->next;
			}
			else
			{
				current->next->prev = current->prev;
				current->prev->next = current ->next;
			}
			delete current;
		}
		current = temp;
	}
}

int diff(Node<int>* & first)
{
	if (first == nullptr || first->next == nullptr)
	{
		throw std::runtime_error("Empty list!");
	}
	int max = first->data, min = first->data;
	Node<int>* current = first->next;
	while (current != nullptr)
	{
		if (current->data > max)
		{
			max = current->data;
		}
		if (current->data < min)
		{
			min = current->data;
		}
		current = current->next;
	}
	return max - min;
}

void deleteSum(Node<int>* &first)
{
	if (first == nullptr || first->next == nullptr || first->next->next == nullptr)
	{
		return;
	}
	int value = diff(first);
	Node<int>* current = first;
	while (current != nullptr)
	{
		Node<int>* temp = current->next;
		if (current->data == value)
		{
			if (current->prev == nullptr)
			{
				current->next->prev = nullptr;
				first = current->next;
			}
			else if (current->next == nullptr)
			{
				current->prev->next = nullptr;

			}
			else
			{
				current->next->prev = current->prev;
				current->prev->next = current->next;
			}
			delete current;
		}
		current = temp;
	}
}


void reverseFirstK(Node<int>* &first, int k)
{
	if (first == nullptr || first->next == nullptr)
	{
		return;
	}
	int counter = k;
	Node<int>* current = first;
	while (counter)
	{
		current = current->next;
		--counter;
	}
	counter = k;
	while (counter)
	{
		Node<int>* holder = current->prev;
		if (current->prev == nullptr)
		{
			first = current;
		}
		else
		{
			current->next->prev = current->prev;
			current->prev->next = current->next;
			current->prev = nullptr;
			current->next = first;
			first = current;
		}
		current = holder;
		--counter;
	}
}

// remove all repeating digits leaving only one of them
void removeDuplicates(Node<int>* &first)
{
	if (first == nullptr || first->next == nullptr)
	{
		return;
	}
	Node<int>* current = first;
	Node<int>* temp;
	while (current != nullptr && current->next != nullptr)
	{
		temp = current->next;
		while (temp != nullptr)
		{
			Node<int>* holder = temp->next;
			if (current->data == temp->data)
			{
				if (temp->next == nullptr)
				{
					temp->prev->next = nullptr;
				}
				else
				{
					temp->next->prev = temp->prev;
					temp->prev->next = temp->next;
				}
				delete temp;
			}
			temp = holder;
		}
		current = current->next;
	}

}

// remove all repeating digits
void removeAllDuplicates(Node<int>* &first)
{
	if (first == nullptr || first->next == nullptr)
	{
		return;
	}
	Node<int>* current = first;
	Node<int>* temp;
	bool duplicated = false;
	while (current != nullptr && current->next != nullptr)
	{
		temp = current->next;
		while (temp != nullptr)
		{
			Node<int>* holder = temp->next;
			if (current->data == temp->data)
			{
				if (temp->next == nullptr)
				{
					temp->prev->next = nullptr;
				}
				else
				{
					temp->next->prev = temp->prev;
					temp->prev->next = temp->next;
				}
				delete temp;
				duplicated = true;
			}
			temp = holder;
		}
		Node<int>* holder = current->next;
		if (duplicated) {
			if (current->prev == nullptr)
			{
				current->next->prev = nullptr;
				first = current->next;
			}
			else if (current->next == nullptr)
			{
				current->prev->next = nullptr;
			}
			else
			{
				current->next->prev = current->prev;
				current->prev->next = current->next;
			}
			delete current;
		}
		current = holder;
		duplicated = false;
	}

}
int main()
{


	/*
	std::string s1 = "((())){}{}{()}";
	std::string s2 = "((())){}{}{()}";
	std::string s3 = "((())){}{}";
	Node<std::string>* first = new Node<std::string>(s1);
	pushBack(first, s2);
	pushBack(first, s3);
	std::cout << match(first, checkBrackets);
	*/
	Node<int>* first = new Node<int>(1);
	pushBack(first, 1);
	pushBack(first, 6);
	pushBack(first, 7);
	pushBack(first, 5);
	pushBack(first, 5);
	print(first);
	removeAllDuplicates(first);
	//deleteSum(first);
	print(first);
	//std::cout << isPalindrome(first);
	/*
	Node<double>* list = new Node<double>((double)5);
	pushBack(list, (double)3);
	pushBack(list, (double)7);
	pushBack(list, (double)3.5);
	pushBack(list, (double)2);
	pushBack(list, (double)5);
	pushBack(list, (double)4.5);
	pushBack(list, (double)3);
	pushBack(list, (double)6);
	pushBack(list, (double)8);
	pushBack(list, (double)4);
	print(list);
	deleteAverage(list);
	print(list);
	*/
    return 0;
}

