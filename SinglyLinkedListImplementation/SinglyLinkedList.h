#pragma once

// ������������� �� ����������� ������

class SinglyLinkedList
{
public:
	// ������������
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList& other);
	SinglyLinkedList& operator=(const SinglyLinkedList& other);
	~SinglyLinkedList();

	// �������� �� ��� ������� � �������
	void pushBack(int data);
	void pushFront(int data);

	// ������������ ������
	size_t getSize() const;
	bool contains(int data) const;
	void print() const;

private:
	struct Node // ����������� �� ����� �� �������
	{
		int data; // �������� �� ������
		Node* next; // ��������, ����� ���� ������ ��� ��������� ������� � �������

		Node(int data, Node* next = nullptr)
		{
			this->data = data;
			this->next = next;
		}
	};

private:
	Node* first; // ��������, ����� ���� ������ ��� ������ ������� � �������
	size_t size; // ����� ������� �� ������� (��� � ����������)

				 // ������� ������� �� ������ � ��������������
	void copy(const SinglyLinkedList& other);
	void clear();
};