// hw1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>

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

void pushBack(Node* &first, int data) //*& променя подадения списък (без него няма да се запази промяната по подадения списък)
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

bool has_cycle(Node* &first) {
	if (first == nullptr) {
		throw std::runtime_error("Empty list");
	}
	Node* slowP = first, *fastP = first;
	while (slowP && fastP && fastP->next) {
		slowP = slowP->next;
		fastP = fastP->next->next;
		if (slowP == fastP) {
			return true;
		}
	}
	return false;
}

bool matchingBrackets(char br1, char br2) {
	return (br1 == '[' && br2 == ']' ||
		br1 == '(' && br2 == ')' ||
		br1 == '{' && br2 == '}');
}

bool checkBrackets(std::string str) {
	std::stack<char> s;
	for (int i = 0; i < str.length(); ++i) {

		if (str[i] == '(' || str[i] == '[' || str[i] == '{' )
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

int main()
{
	const char* str1 = "(){}[][][]", *str2 = "{[(])}", *str3 = "{{[[(())]]}}";
	std::cout << checkBrackets(str1) << std::endl << checkBrackets(str2) << std::endl << checkBrackets(str3) << std::endl;
    return 0;
}

