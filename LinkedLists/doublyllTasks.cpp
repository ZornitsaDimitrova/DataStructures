// doublyllTasks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

template <typename T>
struct Node {
	T data;
	Node* next;
	Node* prev;
	Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr) : data(data), next(next), prev(prev) {}
};

template <typename T>
void pushBack(Node<T>* &first, T data) {

	Node<T>* newNode = new Node<T>(data);
	if (first == nullptr) {
		first = newNode;
	}
	else {
		Node<T>* current = first;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
		newNode->prev = current;
	}

}

template <typename T>
void print(Node<T>* first) {
	Node<T>* current = first;
	while (current != nullptr) {
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

/*
���� �������� ���������� �� ������� �� ���������� ������, �� �� �������� ���������
void swapNode(Node*& first, int element) , ����� ������ ���������� �������� � ������� � � ������� ���
���������� �� ��������, ������� �� �� ��� ������� ������ � ������� (��� � ��������). ��� �������� �� ������� 
���������� �������� �� ������� ���������, �� �� � �������� �������.
*/
template <typename T>
void swapNode(Node<T>*& first, T element) {
	if (first == nullptr) return;
	Node<T>* current = first;
	while (current != nullptr) {
		if (current->data == element) {
			if (current->next->next == nullptr) {
				std::cout << "Impossible swap" << std::endl;
				return;
			}
			T temp = current->data;
			current->data = current->next->next->data;
			current->next->next->data = temp;
			return;
		}
		current = current->next;
	}
}

/*���� �������� ���������� �� ������� �� ���������� ������ :
-�������� �������, ����� ��������� ��� ������� ���� ������� ����� ��� #*/

void concat(Node<char>*& first, Node<char>*& second) {
	Node<char>*current = first;
	while (current->next != nullptr) {
		current = current->next;
	}
	Node<char>* newNode = new Node<char>('#');
	current->next = newNode;
	newNode->prev = current;
	current = current->next;
	current->next = second;
	second->prev = current;
}

/* -�������� �������, ����� �� ����� ������ ��� ������� �� ���������� ���� ��������� � # ���� �� �� ������� ����, �� ���� 
���� �������� �� ���������� ����� �� �������������� �� ������� � ������� ����� �� ����������(��� ������ �� ���� ��� �������� False)*/

bool match(Node<char>* first) {
	if (first == nullptr) return false;
	Node<char>* current = first;
	while (current != nullptr) {
		if (current->data == '#') {
			char check = current->prev->data;
			Node<char>* iterator = current;
			while (iterator->next != nullptr) {
				if (iterator->data == '#') {
					if (iterator->next->data == check) return true;
				}
				iterator = iterator->next;
			}
		}
		current = current->next;
	}
	return false;

}

/*���� �������� ���������� �� ������� �� ���������� ������, 
��� �������������� ���������� �� ��� �������� � �������, ���������� ������ �� ���������� ��������� ��.*/

void removeIfThree(Node<int>* &first) {
	if (first == nullptr) {
		return;
	}
	Node<int>* current = first;
	while (current!= nullptr && current->next->next != nullptr) {
		Node<int>* holder = current->next;
		if (current->data == current->next->data && current->data == current->next->next->data) {
			if (current->prev == nullptr) {
				current->next->prev = nullptr;
				first = current->next;
			}
			else if (current->next == nullptr) {
				current->prev->next = nullptr;
			}
			else {
				current->next->prev = current->prev;
				current->prev->next = current->next;
			}
			delete current;
		}
		current = holder;
	}
}

/*���� �������� ���������� �� ������� �� ���������� ������, �������� �������, ����� ������ ������� � ������� ��� �
������� �� ����� ����� ����� �� ������� �� �������.*/

int sum(Node<int>* first) {
	int sum = 0;;
	if (first == nullptr) {
		return 0;
	}
	Node<int>* current = first;
	while (current != nullptr) {
		sum += current->data;
		current = current->next;
	}
	return sum;

}

template<typename T>
void pushFront(Node<T>* &first, T data) {
	Node<T>* newNode = new Node<T>(data);
	if (first != nullptr) {
		newNode->next = first;
		first->prev = newNode;
	}
	first = newNode;
}

void reverseAndSum(Node<int>* &first) {
	Node<int>* reversed = nullptr;
	Node<int>* current = first;
	if (first == nullptr) return;
	while (current != nullptr) {
		pushFront(reversed, current->data);
		current = current->next;
	}
	pushFront(reversed, sum(first));
	first = reversed;
}

/*�������� ��������, ����� ������� ����� n � ���� ���� ������� �� ���� �����. �������� �� � ���������� ������. 
���������� ������� � ���� ���� �� ��������� ����, �� ������ ��������� �� �������� �� ����� �������� � ��� �������� - 
������� �� ������� ���� �� ��������� ��������, ������� �� ����� �������.*/

Node<int>* fromArr(int arr[], int n) {
	for (int i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array  
		int min = i;
		for (int j = i + 1; j < n; j++)
			if (arr[j] < arr[min])
			{
				min = j;
			}

		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}

	Node<int> *result = nullptr;
	int counter;
	for (int i = 0; i < n; i++) {
		counter = 1;
		while (arr[i] == arr[i + 1]) {
			counter++;
			i++;
		}
		pushBack(result, counter);
		pushBack(result, arr[i]);
	}
	return result;

}
void execute() {
	int n;
	std::cin >> n;
	int arr[100];
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] <<" ";
	}
	std::cout << std::endl;

	Node<int>* listFromArr = fromArr(arr, n);
	print(listFromArr);
}

int main()
{
	/*
	Node<int>* first = new Node<int>(1);
	pushBack(first, 2);
	pushBack(first, 3);
	pushBack(first, 4);
	pushBack(first, 5);
	pushBack(first, 6);
	pushBack(first, 7);
	pushBack(first, 8);
	print(first);
	swapNode(first, 1);
	print(first);
	*/

	/*
	Node<char>* chFirst = new Node<char>('H');
	pushBack(chFirst, 'F');
	pushBack(chFirst, 'S');
	pushBack(chFirst, 'D');
	pushBack(chFirst, 'F');
	pushBack(chFirst, 'T');
	Node<char>* chSecond = new Node<char>('Y');
	pushBack(chSecond, 'U');
	pushBack(chSecond, 'O');
	pushBack(chSecond, 'P');
	pushBack(chSecond, 'W');
	pushBack(chSecond, 'E');

	print(chFirst);
	concat(chFirst, chSecond);
	print(chFirst);
	*/
	/*
	Node<char>* words = new Node<char>('T');
	pushBack(words, 'H');
	pushBack(words, 'I');
	pushBack(words, 'N');
	pushBack(words, 'K');
	pushBack(words, '#');
	pushBack(words, 'S');
	pushBack(words, 'M');
	pushBack(words, 'I');
	pushBack(words, 'L');
	pushBack(words, 'E');
	pushBack(words, '#');
	//pushBack(words, 'K');
	//pushBack(words, 'N');
	//pushBack(words, 'O');
	//pushBack(words, 'W');
	//pushBack(words, '#');
	pushBack(words, 'O');
	pushBack(words, 'L');
	pushBack(words, 'D');
	std::cout << match(words)<<std::endl;
	*/
	/*
	Node<int>* first = new Node<int>(5);
	pushBack(first, 1);
	pushBack(first, 7);
	pushBack(first, 1);
	pushBack(first, 8);
	pushBack(first, 8);
	pushBack(first, 8);
	pushBack(first, 8);
	print(first);
	reverseAndSum(first);
	print(first);
	*/
	execute();
    return 0;
}

