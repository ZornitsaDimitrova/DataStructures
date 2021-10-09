#include "stdafx.h"
#include<iostream>
#include "SinglyLinkedList.h"

using namespace std;

int main()
{
	SinglyLinkedList s;
	s.pushBack(2);
	s.pushBack(5);
	s.pushBack(8);
	s.print();

	return 0;
}