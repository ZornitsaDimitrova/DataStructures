#include "stdafx.h"
#include <iostream>
#include "Boss.h"
using namespace std;

Boss::Boss():Boss("Default",0,0,0,0,0)
{}

Boss::Boss(const char * name, double baseSalary, double percent, double overtimeHours, double overtimeWage, int businessTrips) : Employee(name,baseSalary,percent,overtimeHours,overtimeWage)
{
	setBusinessTrips(businessTrips);
}

void Boss::setBusinessTrips(int _businessTrips)
{
	businessTrips = _businessTrips;
}

int Boss::getBusinessTrips() const
{
	return businessTrips;
}

Boss * Boss::clone() const
{
	return new Boss(*this);
}

double Boss::accruals() const
{
	return getBaseSalary() + ((double)(getOvertimeHours()+(8*getBusinessTrips())))*getOvertimeWage() + bonus();
}

void Boss::showEmployees() const
{
	cout << "BOSS" << endl;
	cout << "Name:" << getName() << endl << "Base salary:" << getBaseSalary() <<"lv."<< endl << "Percent:" << getPercent() << "%" << endl
		<< "Overtime:" << getOvertimeHours()*getOvertimeWage() << "lv." << endl << "Bonus:" << bonus() << "lv." << endl <<"Business trips:"
		<<getBusinessTrips()<<endl<< "Accruals:" << accruals()<< "lv." << endl << "Deductions:" << deductions() << "lv." << endl << "Final salary:"
		<< finalSalary() << "lv." << endl;

}

