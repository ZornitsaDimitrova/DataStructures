// NextGreaterElement.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>

void nextGreater(int arr[], int length) {

	std::stack<int> s;

	for (int i = 0; i < length; ++i) {
		while (!s.empty() && arr[i] > s.top()) {
			std::cout << s.top() << " -> " << arr[i] << "\n";
			s.pop();
		}
		s.push(arr[i]);
	}

	while (!s.empty()) {
		std::cout << s.top() << " -> " << "-1\n";
		s.pop();
	}
}

int main() {
	int arr[] = { 4,5,2,25 };
	size_t sz = sizeof(arr) / sizeof(int);

	nextGreater(arr, sz);
	return 0;
}

