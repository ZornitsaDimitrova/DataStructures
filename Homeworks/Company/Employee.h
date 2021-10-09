#pragma once


#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

class Employee
{
protected:
	char* name;
	double baseSalary;
	double percent;
	int overtimeHours;
	double overtimeWage;
	
public:
	Employee();
	Employee(const char* name, double baseSalary, double percent, int overtimeHours, double overtimeWage);
	Employee(const Employee& other);
	Employee& operator=(const Employee& other);
	virtual ~Employee();

	const char* getName() const;
	double getBaseSalary() const;
	double getPercent() const;
	int getOvertimeHours() const;
	double getOvertimeWage() const;

	void setName(const char* newName);
	void setBaseSalary(double newBaseSalary);
	void setPercent(double newPercent);
	void setOvertimeHours(int newOvertimeHours);
	void setOvertimeWage(double newOvertimeWage);

	virtual Employee* clone() const = 0;


	double bonus() const;
	virtual double accruals() const=0;//nachisleniq
	double deductions() const;//udrujki

	double finalSalary() const;
	virtual void showEmployees() const = 0;

	bool operator==(const Employee& other) const;
	bool operator < (const Employee& other) const;
};

#endif // EMPLOYEE_H_INCLUDED