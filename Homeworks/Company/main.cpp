

#include "stdafx.h"
#include <iostream>
#include "Employee.h"
#include "Worker.h"
#include "Boss.h"
#include "Manager.h"
#include "Company.h"
using namespace std;
/*Company mergeCompanies(const Company & company1, const Company & company2) 
{
	return company1 + company2;
}*/
int main()
{
	Worker  w1("Ivan", 700.50, 10.2, 12, 5.7),
		    w2("Georgi", 800, 10, 0, 2);
	Manager m1("Stefan", 1000.6, 10.7, 20, 1.6, "Turgovski otdel", 10),
		    m2("Grigor", 2000, 20, 2, 1, "otdel proizvodstvo", 8);
	Boss    b1("Hristo", 3000, 10, 20, 3, 10);

	Company company("First","Sofia",8);
	Company company2("Second","Plovdiv",8);
	company.addEmployee(w1);
	company2.addEmployee(w2);
	company.addEmployee(m1);
	company2.addEmployee(m2);
	company.addEmployee(b1);
	company.addEmployee(m1);
	company.addEmployee(b1);
	
	cout << "Name:" << company.getName() << ", location:" << company.getLocation()<<endl;
	company.showEmployees();
	cout << "With raised salary:" << endl;
	company.raiseSalary();
	company.showEmployees();
	company.getExtreme();


	cout << "Sum of payments:" << company.getPaymentsSum() << "lv., Sum of taxes:" << company.getTaxes() <<"lv."<< endl;

	/*cout << "Merged Company:" << mergeCompanies(company, company2).getName()<<", location:"<< mergeCompanies(company, company2).getLocation()<< endl;
	mergeCompanies(company, company2).showEmployees();*/
	return 0;
}
