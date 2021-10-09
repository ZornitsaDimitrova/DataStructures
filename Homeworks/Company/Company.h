#pragma once
#ifndef COMPANY_H_INCLUDED
#define COMPANY_H_INCLUDED

#include "Employee.h"

class Company
{

public:

	Company();
	Company(const char* name, const char* location, unsigned int capacity);
	Company(const Company& other);
	Company& operator=(const Company& other);
	~Company();

	bool isFull() const;

	void addEmployee(const Employee& _employee);
	void removeEmployee(const Employee& _employee);

	void setName(const char* newName);
	void setLocation(const char* newLocation);



	const char* getName() const;
	const char* getLocation() const;
	int getCapacity() const;
	int getSize() const;
	Employee** getEmployee() const;
	double getPaymentsSum() const;
	double getTaxes() const;
	void getExtreme() const;
	void raiseSalaryOf(const Employee& employee) const;
	void raiseSalary() const;
	void showEmployees() const;
	Company operator+(const Company& other) const;
private:
	char* name;
	char* location;
	int capacity;
	int size;
	Employee** employee;


	void resizeUp();
	void resizeDown();
	void copyOther(const Company& other);
	void destroy();

};



#endif // COMPANY_H_INCLUDED