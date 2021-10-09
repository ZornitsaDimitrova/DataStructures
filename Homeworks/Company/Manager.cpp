#include "stdafx.h"
#include <iostream>
#include "Manager.h"
using namespace std;

Manager::Manager() : Manager("Default",0,0,0,0,"Default",0)
{}

Manager::Manager(const char * name, double baseSalary, double percent, int overtimeHours, double overtimeWage, const char * team, int teamMembers) : Employee(name, baseSalary, percent,overtimeHours,overtimeWage)
{
	setTeam(team);
	setTeamMembers(teamMembers);
}

Manager::Manager(const Manager & other) : Manager(other.name, other.baseSalary,other.percent,other.overtimeHours,other.overtimeWage,other.team,other.teamMembers)
{
}

Manager & Manager::operator=(const Manager & other)
{
	if (this != &other)
	{
		setName(other.name);
		setBaseSalary(other.baseSalary);
		setPercent(other.percent);
		setOvertimeHours(other.overtimeHours);
		setOvertimeWage(other.overtimeWage);
		setTeam(other.team);
		setTeamMembers(other.teamMembers);
	}
	return *this;
}

Manager::~Manager()
{
	delete[] team;
}

void Manager::setTeam(const char * _team)
{
	if (_team != nullptr)
	{
		delete[] team;
		team = new char[strlen(_team) + 1];
		strcpy_s(team, strlen(_team) + 1, _team);
	}
}

void Manager::setTeamMembers(int _teamMembers)
{
	teamMembers = _teamMembers;
}

const char * Manager::getTeam() const
{
	return team;
}

int Manager::getTeamMembers() const
{
	return teamMembers;
}

Manager * Manager::clone() const
{
	return new Manager(*this);
}

void Manager::showEmployees() const
{
	cout << "MANAGER" << endl;
	cout << "Name:" << getName() << endl<<"Team:"<<getTeam()<<endl<<"Team members:"<<getTeamMembers()<<endl << "Base salary:" 
		<< getBaseSalary() << "lv." << endl << "Percent:" << getPercent() << "%" << endl << "Overtime:" << getOvertimeHours()*getOvertimeWage()
		<< "lv." << endl << "Bonus:" << bonus() << "lv." << endl << "Accruals:" << accruals() << "lv." << endl << "Deductions:" << deductions()
		<< "lv." << endl << "Final salary:" << finalSalary() << "lv." << endl;

}

double Manager::accruals() const
{
	return getBaseSalary() + bonus() + getTeamMembers()*20;
}
