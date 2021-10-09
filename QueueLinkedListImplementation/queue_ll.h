#ifndef QUEUE_LINKED_LIST
#define QUEUE_LINKED_LIST
#include <iostream>
#include <cassert>

struct QNode{
	int data;
	QNode *next;
	QNode() : next(nullptr), data(0) {}
	QNode(int data): next(nullptr), data(data){}
};

class Queue {
public:
	Queue();
	Queue(size_t);
	Queue(const Queue&);
	~Queue();

	bool empty() const;
	size_t length() const;

	int front() const;
	void enqueue(int);
	int dequeue();

	void display();

private:
	size_t size;
	QNode *first;
	QNode *rear;
};
#endif QUEUE_LINKED_LIST