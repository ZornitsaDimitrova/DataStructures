#pragma once

#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#include "Employee.h"

class Worker : public Employee
{
private:
	
public:
	Worker();
	Worker(const char* name, double baseSalary,double percent, int overtimeHours, double overtimeWage);



	Worker* clone() const;
	
	double accruals() const;
	void showEmployees() const;
};

#endif // WORKER_H_INCLUDED
