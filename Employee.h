#ifndef __EMPLOYEE__
#define __EMPLOYEE__


#include "Address.h"
#include "Bank.h"
#include "General.h"
#include "list.h"
#define TEL 10

static const int KINDEMP[4] = { 10,5,2,1 };//prices of channels by content

typedef enum { eCS, eTS, eHR, eCEO, eNofTypes } EmployeeType;

static const char* typeTitLe[eNofTypes] = { "CS", "TS", "HR", "CEO" };

typedef struct
{
	char*	name;
	EmployeeType type;
	int phoneNumber;
	Bank_Leumi details;
	Address ads;
	
}Employee;

EmployeeType	getEmpType();
void getMoney(Employee* pEmp, int sum);
void initEmployee(Employee* pEmp, int type, int phone);
void printEmployee(const Employee* v);
void freeEmployee(Employee* pEmp);
void freeEmpV(void* val);
#endif
