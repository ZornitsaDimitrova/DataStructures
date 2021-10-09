// bookshop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Company.h"
#include <cstring>
using namespace std;

void Company::resizeUp()
{
	capacity *= 2;
	Employee** temp = new Employee*[capacity];
	for (int i = 0; i < size; i++)
	{
		temp[i] = employee[i];
	}
	delete[] employee;
	employee = temp;
}

void Company::resizeDown()
{
	capacity /= 2;
	Employee** temp = new Employee* [capacity];
	for (int i = 0; i < size; i++)
	{
		temp[i] = employee[i];
	}
	delete[] employee;
	employee = temp;
}

void Company::copyOther(const Company& other)
{
	setName(other.name);
	setLocation(other.location);
	size = other.size;
	capacity = other.capacity;
	employee = new Employee*[other.capacity];
	for (int i = 0; i < size; i++)
	{
		employee[i] = other.employee[i]->clone();
	}

}

void Company::destroy()
{
	for (int i = 0; i < size; i++)
	{
		delete employee[i];
	}
	delete[] employee;
}


Company::Company() : Company("Default","Default",4)
{
}

Company::Company(const char*name, const char* location, unsigned int capacity):name(nullptr),location(nullptr)
{
	setName(name);
	setLocation(location);
	this->size = 0;
	this->capacity = (capacity >= 4) ? capacity : 4;
	this->employee = new Employee*[this->capacity];
}

Company::Company(const Company & other)
{
   copyOther(other);
}

Company & Company::operator=(const Company & other)
{
	if (this != &other)
	{
		destroy();
		copyOther(other);
	}
	return *this;
}

Company::~Company()
{
	destroy();
	delete[] name;
	delete[] location;
}

bool Company::isFull() const
{
	return size == capacity;
}

void Company::addEmployee(const Employee & _employee)
{
	if (isFull())
	{
		resizeUp();
	}

	employee[size++] = _employee.clone();
}

void Company::removeEmployee(const Employee & _employee)
{
	for (int i = 0; i < size; ++i) 
	{
		if (*(employee[i]) == _employee) 
		{
			delete employee[i];

			employee[i] = employee[size - 1];
			size--;

			if (size < capacity / 2)
			{
				resizeDown();
			}
			break;
		}
	}
}

void Company::setName(const char * newName)
{
     if (newName != nullptr)
	{
		delete[] this->name;
		this->name = new char[strlen(newName) + 1];
		strcpy_s(this->name, strlen(newName) + 1, newName);
	}
}

void Company::setLocation(const char * newLocation)
{
	if (newLocation != nullptr)
	{
		delete[] this->location;
		this->location = new char[strlen(newLocation) + 1];
		strcpy_s(this->location, strlen(newLocation) + 1, newLocation);
	}
}


const char * Company::getName() const
{
	return this->name;
}

const char * Company::getLocation() const
{
	return this->location;
}

int Company::getCapacity() const
{
	return this->capacity;
}

int Company::getSize() const
{
	return this->size;
}

Employee ** Company::getEmployee() const
{
	return employee;
}




double Company::getPaymentsSum() const
{
    double payments = 0;

	for (int i = 0; i < size; ++i) 
	{
		payments += employee[i]->finalSalary();
	}

	return payments;
}

double Company::getTaxes() const
{
	double taxes = 0;

	for (int i = 0; i < size; ++i) 
	{
		taxes += employee[i]->deductions();
	}

	return taxes;
}

void Company::getExtreme() const
{
	cout << "The highest paid employee is: " << endl;
	for (int i = 0; i < this->size - 1; i++)
	{
		for (int j = 0; j < this->size - 1; j++)
		{

			if (employee[j] < employee[j + 1])
			{
				Employee* temp = employee[j];
				employee[j] = employee[j + 1];
				employee[j + 1] = temp;
			}
		}
	}
	employee[0]->showEmployees();
}

void Company::raiseSalaryOf(const Employee & _employee) const
{// увеличава заплатата на определен служител с 5 %
	for (int i = 0; i < size; i++) 
	{
		if (*(employee[i]) == _employee) 
		{
			employee[i]->setBaseSalary(employee[i]->getBaseSalary() + employee[i]->getBaseSalary()*0.05);
			return;
		}
	}
}

void Company::raiseSalary() const
{
	//увеличава заплатата на всички служители с 2%
	for (int i = 0; i < size; i++) 
	{
		employee[i]->setBaseSalary(employee[i]->getBaseSalary() + employee[i]->getBaseSalary()*0.02);	
	}
}

void Company::showEmployees() const
{
	for (int i = 0; i < size; i++)
	{
		employee[i]->showEmployees();
	}
}
Company Company::operator+(const Company & other) const
{
	Company result;
	result.destroy();
	delete[] result.name;
	delete[] result.location;
	result.setName("Merged");
	result.setLocation("Merged");
	result.size = this->size + other.size;
	result.capacity = this->capacity + other.capacity;
	result.employee = new Employee*[result.capacity];

	for (int i = 0; i < this->size; i++)
	{
		result.employee[i] = this->employee[i]->clone();
	}
	for (int i = this->size,j=0; i < result.size,j< other.size; i++,j++)
	{
		result.employee[i] = other.employee[j]->clone();
	}
	return result;
}
