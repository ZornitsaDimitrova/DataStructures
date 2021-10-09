#include "stdafx.h"
#include <iostream>
#include "Worker.h"
using namespace std;

Worker::Worker() : Worker("Default",0,0,0,0)
{}

Worker::Worker(const char * name, double baseSalary, double percent, int overtimeHours, double overtimeWage):Employee(name, baseSalary, percent, overtimeHours, overtimeWage)
{}

Worker * Worker::clone() const
{
	return new Worker(*this);
}

double Worker::accruals() const
{
	return getBaseSalary() + (((double)getOvertimeHours())*getOvertimeWage()) + bonus();
}

void Worker::showEmployees() const
{
	cout << "WORKER" << endl;
	cout << "Name:" << getName() << endl << "Base salary:" << getBaseSalary() << "lv." << endl << "Percent:" << getPercent() <<"%"<< endl
		<< "Overtime:" << getOvertimeHours()*getOvertimeWage() << "lv." << endl << "Bonus:" << bonus() << "lv." << endl << "Accruals:" << accruals()
		<< "lv." << endl << "Deductions:" << deductions() << "lv." << endl << "Final salary:"<<finalSalary()<< "lv." << endl;

}
