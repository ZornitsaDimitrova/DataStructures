// QueueLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "queue_ll.h"

int main()
{
	Queue queue = Queue();
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	queue.enqueue(4);
	queue.enqueue(5);
	queue.enqueue(6);
	queue.display();
	std::cout << queue.dequeue() << std::endl;
	queue.display();
    return 0;
}

