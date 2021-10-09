// DoublyLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "DoublyLinkedList.h"


int main()
{
	DoublyLinkedList dll;
	dll.pushBack(3);
	dll.pushBack(5);
	dll.pushBack(7);
	dll.pushBack(8);
	dll.print();
	dll.popFront();
	dll.print();
    return 0;
}

