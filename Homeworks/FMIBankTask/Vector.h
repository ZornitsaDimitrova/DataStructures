#pragma once

#include <iostream>

template<class T> class Vector
{
public:
	Vector();
	explicit Vector(size_t _size);
	Vector(const Vector& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

	void reserve(int newmalloc);
	void resize(int newsize, T val = T());

	bool isEmpty() const;
	size_t getCapacity() const;
	size_t getSize() const;

	void push_back(const T& other);
	void pop_back();
	void remove(const T& other);

	T& operator[](size_t i);
	const T& operator[](size_t i) const;

private:
	size_t	size;
	T*		elements;
	size_t	capacity;
};


template<class T>
Vector<T>::Vector()
	:size(0), elements(0), capacity(0)
{}

template<class T>
inline Vector<T>::Vector(size_t _size)
	: size(_size), elements(new T[_size]), capacity(_size)
{
	for (size_t i = 0; i < size; i++)
		elements[i] = T();
}

template<class T>
inline Vector<T>::Vector(const Vector & other)
	:size(other.size), elements(new T[other.size])
{
	for (size_t i = 0; i < other.size; i++)
		elements[i] = other.elements[i];
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this == &other) return *this;


	if (other.size <= capacity)
	{
		for (size_t i = 0; i < other.size; i++)
		{
			elements[i] = other.elements[i];
			size = other.size;
			return *this;
		}
	}

	T* p = new T[other.capacity];

	for (size_t i = 0; i < other.size; i++)
		p[i] = pther.elements[i];

	delete[] elements;
	size = other.size;
	capacity = other.capacity;
	elements = p;
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	delete[] elements;
}

template<class T>
inline bool Vector<T>::isEmpty() const
{
	return (size == 0);
}

template<class T>
inline size_t Vector<T>::getCapacity() const
{
	return capacity;
}

template<class T>
inline void Vector<T>::reserve(int newalloc)
{
	if (newalloc <= capacity) return;

	T* p = new T[newalloc];

	for (size_t i = 0; i < size; i++)
		p[i] = elements[i];

	delete[] elements;

	elements = p;

	capacity = newalloc;
}

template<class T>
inline void Vector<T>::resize(int newsize, T val)
{
	reserve(newsize);

	for (size_t i = size; i < newsize; i++)
		elements[i] = T();

	size = newsize;
}

template<class T>
inline size_t Vector<T>::getSize() const
{
	return size;
}

template<class T>
inline void Vector<T>::push_back(const T& other)
{
	if (capacity == 0)
		reserve(8);
	else if (size == capacity)
		reserve(2 * capacity);

	elements[size++] = other;
}

template<class T>
inline void Vector<T>::pop_back()
{
	size--;
}

template<class T>
inline void Vector<T>::remove(const T & other)
{
	for (size_t i = 0; i < size; i++)
	{
		if (elements[i] == other)
		{
			elements[i] = elements[size - 1];
			size--;

			break;
		}
	}
}

template<class T>
inline T & Vector<T>::operator[](size_t i)
{
	return elements[i];
}

template<class T>
inline const T & Vector<T>::operator[](size_t i) const
{
	return elements[i];
}
