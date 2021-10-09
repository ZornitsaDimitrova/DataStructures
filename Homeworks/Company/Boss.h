#pragma once

#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include "Employee.h"

class Boss : public Employee
{
private:
	int businessTrips;
public:
	Boss();
	Boss(const char* name, double baseSalary,double percent, double overtimeHours, double overtimeWage, int businessTrips);

	void setBusinessTrips(int _businessTrips);

	int getBusinessTrips() const;

	Boss* clone() const;
	double accruals() const;
	void showEmployees() const;
	
};


#endif // BOSS_H_INCLUDED
