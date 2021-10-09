#pragma once
// ������������� �� ���������� ������ � �������� ��� ��������� �������

struct Node // ����������� �� ����� �� �������
{
	int data; // �������� �� ������
	Node* next; // ��������, ����� ���� ������ ��� ��������� ������� 
	Node* prev; // ��������, ����� ���� ������ ��� ��������� ������� 

	Node(int data, Node* next = nullptr, Node* prev = nullptr)
	{
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
};

class DoublyLinkedList
{
public:
	// ������������
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& otherList);
	DoublyLinkedList& operator=(const DoublyLinkedList& otherList);
	~DoublyLinkedList();

	// �������� �� ��� ������� � �������
	void pushFront(int data);
	void pushBack(int data);

	// ��������� �� ������� �� �������
	void removeByKey(int data);
	void removeByNode(Node* toRemove);

	int count(int x);
	// ���������� �� ����������
	void print() const;

private:
	Node* first; // ��������, ����� ���� ������ ��� ������ ������� � �������
	Node* last; // ��������, ����� ���� ������ ��� ��������� ������� � �������
			
	// ������� ������� �� ������ � ��������������
	void copy(const DoublyLinkedList& otherList);
	void clear();
};

