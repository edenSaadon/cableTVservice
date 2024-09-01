#ifndef __COMPANY__
#define __COMPANY__
//#define _CRT_SECURE_NO_WARNINGS update in project properties

#include "list.h"
#include "User.h"
#include "employee.h"
#include "Communication_Infrastructure.h"
#include "General.h"
#define MAX_ID 3
#define basicSalary 1000
#define limitOfPack 3
#define MIN_BUDGET 50000
#define MIN_EUC 1
#define ADD_SAL_TS 200
#define ADD_SAL_HR 150
#define ADD_SAL_CEO 1000




typedef enum { startDate, kindOfPack, id, Nosorted, eNofOptions } SortOp;
static const char* kindOfP[eNofOptions] = { "StartDate", "kindOfPack", "id" ,"noSorted" };


typedef struct
{
	char identifierComp[MAX_ID +1];
	char* nameComp;
	int countOfPackage;
	Package** packageArr;
	int countUser;
	User* userArr;
	int countEmployee;
	LIST* employeeArr;
	CI* loc;
	Bank_Leumi details;
	int option;


}Company;

void printCentered(char* text, int width);
void printPackageTv(const Company* p, int type);
void printCompToAdv(const Company* pComp, int type);
void freeUserArr(User* userArr, int countUser);
void freeEmps(Company* p);
int findByUser(const Company* pComp);
int findByPack(const Company* pComp);
int findByDate(const Company* pComp);
int checkTypeEmp(int type,const Company* p);
int addPackU(Company* pComp);
int findUserLoc(const Company* pComp, int id);
int addAll(Company* p);
int	initComp(Company* pComp);
int checkCompany(Company* s, int sum);
void sortUser(Company* pComp);
int findUser(const Company* pComp);
int compareStartDateQ(const void* a, const void* b);
int compareStartDateB(const void* a, const void* b);
int compareKindOfQ(const void* a, const void* b);
int compareKindOfB(const void* a, const void* b);
int compareIdQ(const void* a, const void* b);
int compareIdB(const void* a, const void* b);
int	addUser(Company* pComp);
int	addPackC(Company* pComp);
int     addEmployee(Company* pComp);
void    enterAreaToComp(Company* p, int num);
void    paymentMonthlyMethodUserArr(Company* pComp);
void    updateAccountEmp(Company* pComp);
void    generalArrayFunction(void* arr, int sizeByte, int numof, void f(void* element));
int     getExactSalary(Employee* emp);
void	printCompany(const Company* pComp);
void	printUserArr(const Company* arr);
void    printEmps(const Company* c);
void	printPackageArr(const Company* arr);
void	freePackageArr(Package** arr, int numOf);
void	freeCompany(Company* pComp);
void    getIdentifierCode(char* code);
int     checkPackType(const Company* pComp, int type);
int     getUserId(Company* pComp,int* id);
User*   getUser(int id, Company* p);
Employee* getEmp(Company* p, int* num);

#endif





