#include "stdafx.h"
#include <iostream>
#include "Employee.h"
using namespace std;

Employee::Employee() : Employee("Default", 0, 0, 0, 0)
{
}

Employee::Employee(const char * name, double baseSalary, double percent, int overtimeHours, double overtimeWage) : name (nullptr)
{
	setName(name);
	setBaseSalary(baseSalary);
	setPercent(percent);
	setOvertimeHours(overtimeHours);
	setOvertimeWage(overtimeWage);
}

Employee::Employee(const Employee & other) : Employee(other.name, other.baseSalary,other.percent,other.overtimeHours,other.overtimeWage)
{}

Employee & Employee::operator=(const Employee & other)
{
	if (this != &other)
	{
		setName(other.name);
		setBaseSalary(other.baseSalary);
		setPercent(other.percent);
		setOvertimeHours(other.overtimeHours);
		setOvertimeWage(other.overtimeWage);
	}
	return *this;
}

Employee::~Employee()
{
	delete[] name;
}

const char * Employee::getName() const
{
	return this->name;
}

double Employee::getBaseSalary() const
{
	return this->baseSalary;
}

double Employee::getPercent() const
{
	return this->percent;
}

int Employee::getOvertimeHours() const
{
	return this->overtimeHours;
}

double Employee::getOvertimeWage() const
{
	return overtimeWage;
}

void Employee::setName(const char * newName)
{
	if (newName != nullptr)
	{
		delete[] this->name;
		this->name = new char[strlen(newName) + 1];
		strcpy_s(this->name, strlen(newName) + 1, newName);
	}
}

void Employee::setBaseSalary(double newBaseSalary)
{
	baseSalary = newBaseSalary;
}

void Employee::setPercent(double newPercent)
{
	percent = newPercent;
}

void Employee::setOvertimeHours(int newOvertimeHours)
{
	overtimeHours = newOvertimeHours;
}

void Employee::setOvertimeWage(double newOvertimeWage)
{
	overtimeWage = newOvertimeWage;
}

double Employee::bonus()const
{
	return (getBaseSalary()+(((double)getOvertimeHours())*getOvertimeWage()))*(getPercent() / 100.0);
}

double Employee::deductions() const
{
	return (22.0/100.0)*accruals();
}

double Employee::finalSalary() const
{
	return accruals() - deductions();
}

bool Employee::operator==(const Employee & other) const
{
	return strcmp(this->name, other.name) == 0;
}

bool Employee::operator<(const Employee & other) const
{
	return this->finalSalary() < other.finalSalary();
}
