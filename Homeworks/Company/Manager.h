#pragma once

#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include "Employee.h"

class Manager : public Employee
{
private:
	char* team;
	int teamMembers;
public:
	Manager();
	Manager(const char* name, double baseSalary, double percent, int overtimeHours,double overtimeWage, const char* team, int teamMembers);
	Manager(const Manager& other);
	Manager& operator=(const Manager& other);
	~Manager();


	void setTeam(const char* _team);
	void setTeamMembers(int _teamMembers);

	const char* getTeam() const;
	int getTeamMembers() const;

	Manager* clone() const;
	void showEmployees() const;
	double accruals() const;
};

#endif // MANAGER_H_INCLUDED