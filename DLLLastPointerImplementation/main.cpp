// week1DoublyLinkedListLastPointerImplementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DoublyLinkedList.h"
#include <iostream>



int main()
{
	DoublyLinkedList d = DoublyLinkedList();
	d.pushBack(5);
	d.pushBack(5);
	d.pushBack(5);
	d.print();
	std::cout << d.count(5);
    return 0;
}

