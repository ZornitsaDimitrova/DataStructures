#include "stdafx.h"

#include "queue.h"

Queue::Queue() :first(nullptr), rear(nullptr), size(0)
{}

Queue::Queue(size_t size) : size(0)
{
	QNode *front = new (std::nothrow) QNode();

	if (!front) {
		throw std::bad_alloc();
	}

	QNode *current = first;

	for (int i = 0; i < size; i++) {
		QNode *new_node = new (std::nothrow) QNode();

		if (!new_node) {
			QNode *curr = first;
			QNode *toDel = first;
			for (int j = 0; j < i; j++) {
				curr = curr->next;
				delete toDel;
				toDel = curr;
			}
			throw std::bad_alloc();
		}
		current->next = new_node;
		current = new_node;
	}
	first = front;
	rear = current;
}

Queue::Queue(const Queue &rhs)
{
	this->size = rhs.size;
	QNode* current = rhs.first;
	do {
		this->enqueue(current->row, current->col, current->pathLength);
		current = current->next;
	} while (current != rhs.rear);
}

Queue::~Queue()
{
	QNode *toDelete = first, *current = first;
	do {
		current = current->next;
		delete toDelete;
		toDelete = current;
	} while (current != nullptr);
	size = 0;
	first = nullptr;
	rear = nullptr;
}

bool Queue::empty() const
{
	return length() == 0;
}

size_t Queue::length() const
{
	return size;
}

QNode* Queue::front() const
{
	if (first == nullptr) {
		throw std::runtime_error("Empty queue");
	}
	return first;
}

void Queue::enqueue(int row, int col, int pathLength)
{
	QNode *new_node = new (std::nothrow) QNode(row, col, pathLength);

	if (new_node == nullptr) {
		throw std::bad_alloc();
	}

	if (first == nullptr) {
		first = new_node;
		rear = new_node;
		size++;
		return;
	}

	rear->next = new_node;
	rear = new_node;
	size++;
}

int Queue::dequeue()
{
	if (empty()) {
		throw std::runtime_error("Trying to delete an empty queue!");
	}

	if (first == rear) {
		int toReturn = first->pathLength;
		delete first;
		first = rear = nullptr;
		size = 0;
		return toReturn;
	}

	QNode *toRemove = first;
	first = first->next;
	int toReturn = toRemove->pathLength;
	delete toRemove;
	size--;

	return toReturn;
}

void Queue::display()
{
	if (empty()) return;
	QNode *current = first;
	do {
		std::cout << "(" << current->row << ", "<< current->col <<", "<<current->pathLength<<")";
		current = current->next;
	} while (current != nullptr);
	std::cout << std::endl;
}