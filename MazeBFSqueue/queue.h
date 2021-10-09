#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cassert>

struct QNode {
	int row, col, pathLength;
	QNode *next;

	QNode() : next(nullptr), row(0), col(0), pathLength(0) {}
	QNode(int row, int col, int pathLength) : next(nullptr), row(row), col(col), pathLength(pathLength) {}
};

class Queue {
public:
	Queue();
	Queue(size_t);
	Queue(const Queue&);
	~Queue();

	bool empty() const;
	size_t length() const;

	QNode* front() const;
	void enqueue(int, int, int);
	int dequeue();

	void display();

private:
	size_t size;
	QNode *first;
	QNode *rear;
};
#endif QUEUE_H