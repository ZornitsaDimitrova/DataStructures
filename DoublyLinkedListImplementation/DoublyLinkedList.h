#pragma once

// ������������� �� ���������� ������

class DoublyLinkedList
{
public:
	// ������������
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& other);
	DoublyLinkedList& operator=(const DoublyLinkedList& other);
	~DoublyLinkedList();

	// �������� �� ��� ������� � �������
	void pushFront(int data);
	void pushBack(int data);

	void popFront();

	// ���������� �� ����������
	void print() const;

private:
	struct Node  // ����������� �� ����� �� �������
	{
		int data; // �������� �� ������
		Node* next; // ��������, ����� ���� ������ ��� ��������� ������� � �������
		Node* prev; // ��������, ����� ���� ������ ��� ��������� ������� � �������

		Node(int data, Node* next = nullptr, Node* prev = nullptr)
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
	};

private:
	Node* first; // ��������, ����� ���� ������ ��� ������ ������� � �������
	size_t size; // ����� ������� �� ������� (��� � ����������)

				 // ������� ������� �� ������ � ��������������
	void copy(const DoublyLinkedList& other);
	void clear();
};