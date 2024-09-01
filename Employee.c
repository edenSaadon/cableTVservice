#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "employee.h"



void getMoney(Employee* pEmp, int sum)
{
	pEmp->details.generalSum += sum;
}
void initEmployee(Employee* pEmp, int type, int phone)
{
	pEmp->name = getStrExactName("Please enter employee name");
	pEmp->type = type;
	pEmp->phoneNumber = phone;
	initBankE(&pEmp->details);
	initAddress(&pEmp->ads);
}
EmployeeType	getEmpType() 
{
	int option;
	printf("\n\n");
	do 
	{
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofTypes; i++)
			printf("%d for %s\n", i, typeTitLe[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofTypes);

	return (EmployeeType)option;
}
void printEmployee(const Employee* e)
{
	printf("Employee name:%s ,Phone number: 0%d, type: %s  \n",e->name, e->phoneNumber, typeTitLe[e->type]);
	printAddress(&e->ads);
	printf("Employee Bank is private.\n\n");
}
void freeEmployee(Employee* pEmp) 
{
		free(pEmp->name);
		freeAddress(&pEmp->ads);
		free(pEmp);

}
void	freeEmpV(void* val)
{
	freeEmployee((Employee*)val);
}