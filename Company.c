#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Company.h"
//#define _CRT_SECURE_NO_WARNINGS 

int addAll(Company* p) {//activated in first time of program in order to create the data base 

	for (int i = 0; i < 3; i++) {
		if (!addPackC(p))
			return 0;
	}

	for (int i = 0; i < 2; i++) {
		if (!addUser(p))
			return 0;
	}

	for (int i = 0; i < 4; i++) {
		if (!addEmployee(p))
			return 0;
	}
	return 1;

}

void paymentMonthlyMethodUserArr(Company* pComp)
{
	if (pComp->countUser < MIN_EUC)
	{
		printf("There is no users to charge\n");
		return;
	}
	int sum = 0;
	for (int i = 0; i < pComp->countUser; i++)
	{

		User* a = &pComp->userArr[i];
		if (checkReduction(a, a->pack->price)==0)
		{
			printf("The card of this user is block: \n");
			printUser(a);
			printf("\n");	
		}
		else 
		{
			sum += a->pack->price;
			a->details.generalSum -= a->pack->price;;
			printf("User id:%d has been charged\n",a->id);

		}
		

	}
	printf("%s Users monthly charge has been completed\n", pComp->nameComp);

	pComp->details.generalSum+=sum;
}
void updateAccountEmp(Company* pComp)
{
	if (pComp->countEmployee < MIN_EUC)
	{
		printf("There is no employees to pay them\n");
		return;
	}
	NODE* a = NULL;

	a= pComp->employeeArr->head.next;
	
	int salary = 0;

	for (int i = 0; i < pComp->countEmployee; i++)
	{
		Employee* emp = (Employee*)a->key;
		salary = getExactSalary(emp);
		getMoney(emp, salary);
		pComp->details.generalSum -= salary;
		printf("The salary to employee %s has been transferred\n", emp->name);
		a = a->next;
	}
	printf("All the employees got their salaries\n");
}
int getExactSalary(Employee* emp) 
{
	if (emp->type == eCS)
		return basicSalary;
	else if (emp->type == eTS)
		return basicSalary+ ADD_SAL_TS;
	else if (emp->type == eHR)
		return basicSalary + ADD_SAL_HR;
	else if (emp->type == eCEO)
		return basicSalary + ADD_SAL_CEO;

	return 0;
}
void sortUser(Company* pComp)
{
	if (pComp->countUser < MIN_EUC)
	{
		printf("There is no users in this company\n");
		return;
	}
	int number;
	printf("\nBase on what field do you want to sort?\n");

	do {

		printf("Enter 1 for Start Date \n");
		printf("Enter 2 for Kind of Package\n");
		printf("Enter 3 for id\n");
		scanf("%d", &number);
		printf("\n");

	} while (number < (int)startDate + 1 || number>(int)Nosorted);


	if (number - 1 == (int)startDate)
	{
		qsort(pComp->userArr, pComp->countUser, sizeof(User), compareStartDateQ);
		pComp->option = (int)startDate;
	}
	else if (number - 1 == (int)kindOfPack)
	{
		qsort(pComp->userArr, pComp->countUser, sizeof(User), compareKindOfQ);
		pComp->option = (int)kindOfPack;
	}
	else if (number - 1 == (int)id)
	{
		qsort(pComp->userArr, pComp->countUser, sizeof(User), compareIdQ);
		pComp->option = (int)id;
	}
}
int findUser(const Company* pComp)
{
	if (pComp->option == (int)Nosorted)
	{
		printf("The search cannot be performed, array not sorted\n");
		return 0;
	}
	int value = 0;
	int num = (int)pComp->option;

	 if (num == (int)startDate)
	 {
		return findByDate(pComp);

	 }

	else if (num == (int)kindOfPack)	 
	{
		 return findByPack(pComp);
		  
	}
	
	else if (num == (int)id) {
		 return findByUser(pComp);
		 
	}
	 return 0;
}
int findByDate(const Company* pComp) 
{
	printf("The sort based on Start Date , please enter the date:\n");
	Date* p = NULL;
	p = (Date*)malloc(sizeof(Date));
	CHECK_AND_FREE(p);
	User a;
	p = &a.d;
	getCorrectDate(p);
	a.d.day = p->day;
	a.d.month = p->month;
	a.d.year = p->year;
	User* s = (User*)bsearch(&a, pComp->userArr, pComp->countUser, sizeof(User), compareStartDateB);
	CHECK_NULL_FREE_RETURN(s, p, "User was not found\n", free);
	printf("User found\n");
	printUser(s);
	return 1;
}
int findByUser(const Company* pComp)
{
	int id1;
	User b = { 0 };

	printf("The sort based on user id\n");
	printf("Please enter user id\n");
	scanf("%d", &id1);
	b.id = id1;
	User* s = (User*)bsearch(&b, pComp->userArr, pComp->countUser, sizeof(User), compareIdB);
	CHECK_NULL_RETURN(s,"User NOT found\n");
	printf("User found\n");
	printUser(s);
	return 1;
}
int findByPack(const Company* pComp)
{
	int val;
	User b = { 0 };

	printf("The sort based on kind of package\n");
	printPackageArr(pComp);
	printf("Choose number of package\n");
	scanf("%d", &val);

	b.pack = (Package*)malloc(sizeof(Package));
	CHECK_AND_FREE(b.pack);
	b.pack->type = val - 1;

	User* s = (User*)bsearch(&b, pComp->userArr, pComp->countUser, sizeof(User), compareKindOfB);
	CHECK_NULL_FREE_RETURN(s, b.pack, "User NOT found", free);
	printf("User found\n");
	printUser(s);//the first user 
	
	return 1;
}
int compareStartDateQ(const void* a, const void* b)
{

	const User* a1 = (const User*)a;
	const User* b1 = (const User*)b;

	const Date* d = &a1->d;
	const Date* d1 = &b1->d;

	if (d->year == d1->year)
	{
		if (d->month == d1->month)
		{
			if (d->day == d1->day)
				return 0;
			else if (d->day < d1->day)
				return -1;
			return 1;
		}
		else if (d->month < d1->month)
			return -1;
		return 1;

	}
	else if (d->year < d1->year)
		return -1;
	return 1;

}
int compareStartDateB(const void* a, const void* b)
{

	const User* a1 = (const User*)a;
	const User* b1 = (const User*)b;

	const Date* d = &a1->d;
	const Date* d1 = &b1->d;

	if (d->year == d1->year)
	{
		if (d->month == d1->month)
		{
			if (d->day == d1->day)
				return 0;
			else if (d->day < d1->day)
				return -1;
			return 1;
		}
		else if (d->month < d1->month)
			return -1;
		return 1;

	}
	else if (d->year < d1->year)
		return -1;
	return 1;
}
int compareKindOfQ(const void* a, const void* b)
{
	const User* a1 = (const User*)a;
	const User* b1 = (const User*)b;

	return strcmp(PackageStr[a1->pack->type], PackageStr[b1->pack->type]);
}
int compareKindOfB(const void* a, const void* b)
{
	const User* a1 = (const User*)a;
	const User* b1 = (const User*)b;

	return strcmp(PackageStr[a1->pack->type], PackageStr[b1->pack->type]);
}
int compareIdQ(const void* a, const void* b)
{
	const User* a1 = (const User*)a;
	const User* b1 = (const User*)b;

	return (a1->id - b1->id);
}
int compareIdB(const void* a, const void* b)
{
	const User* a1 = (const User*)a;
	const User* b1 = (const User*)b;

	return (a1->id - b1->id);
}
int checkCompany(Company* s,int sum) {

	if (blockCard(&s->details, sum, 0)) {
		printf("Call this company, there is no option to get tax.Company card is blocked\n");
		return 0;
	}
		
	s->details.generalSum -= sum;

	if (!updateDirectDebit(&s->details, sum, 0))
		return 0;

	return 1;
}
int addPackC(Company* pComp)
{
	if (pComp->loc->countAreas < MIN_EUC)
	{
		printf("The company NOT connected yet to communication infrastructure. Add Area first.");
		return 0;
	}
	if (pComp->countOfPackage == limitOfPack)
	{
		printf("The package arr is full\n");
		return 0;
	}

	Package* p = (Package*)calloc(1, sizeof(Package));
	CHECK_AND_FREE(p);
	int type = getPackageType();

	if (!checkPackType(pComp, type)) 
	{
		printf("This kind of package already exists\n");
		free(p);
		return 0;
	}

	initPackage(p, type);
	
	Package** arr = (Package**)realloc(pComp->packageArr, (pComp->countOfPackage + 1) * sizeof(Package*));
	CHECK_AND_FREE(arr);

	pComp->packageArr = arr;
	pComp->packageArr[pComp->countOfPackage] = p;
	pComp->countOfPackage++;

	return 1;

}
int addPackU(Company* pComp)
{   int num;
	int id;

	if (pComp->countOfPackage < MIN_EUC)
	{
		printf("There are not packages in this company yet.Please call customers services company.\n");
		return 0;
	}

	printf("Please enter user id again:\n");
	scanf("%d", &id);
	int locUser = findUserLoc(pComp, id);

	if (locUser == -1) 
    {
		printf("User Not Found\n");
		return 0;
	}
		
	printPackageArr(pComp);
	printf("Choose number of package: \n");
	scanf("%d", &num);

	if (num > sizeof(MAX_PAC) / sizeof(int) || num < 0|| checkPackType(pComp, num-1))
	{
		printf("Package NOT exists\n");
		return 0;
	}

	pComp->userArr[locUser].pack= (Package*)malloc(sizeof(Package));
	CHECK_AND_FREE(pComp->userArr[locUser].pack);
	pComp->userArr[locUser].pack = pComp->packageArr[num-1];
	if (!updateDirectDebit(&pComp->userArr[locUser].details, pComp->userArr[locUser].pack->price, 1))
	{
		free(pComp->userArr[locUser].pack);
		return 0;
	}
	printf("Package change. You will see the charge in the end of the month\n");
	return 1;
}
int findUserLoc(const Company* pComp, int id) 
{
	for (int i = 0; i < pComp->countUser; i++) {
		if (id == pComp->userArr[i].id)
			return i;
	}
	return -1;
}
int	addUser(Company* pComp) 
{
	if (pComp->countEmployee<MIN_EUC) 
	{
		printf("There is NO enough employees in this company.Add one\n");
		return 0;
	}

	if (pComp->loc->countAreas < MIN_EUC)
	{
		printf("The company NOT connected yet to communication infrastructure. Add Area first.");
		return 0;
	}
	User b;
	User* arr = pComp->userArr;
	User* a = (User*)realloc(pComp->userArr, (pComp->countUser + 1) * sizeof(User));
	CHECK_AND_FREE(a);
	pComp->userArr = a;
	int id1 = 0;
	id1 =getUserId(pComp, &id1);
	if (id1 == 0) 
	{
		free(a);
		return 0;
	}

	char* str = pComp->nameComp;
	initUser(&b, str);
	b.id = id1;
	pComp->userArr[pComp->countUser] = b;

	pComp->countUser++;
	if (!addPackU(pComp)) {
		free(a);
		return 0;
	}
	return 1;

}
int addEmployee(Company* pComp)
{
	if (pComp->loc->countAreas < MIN_EUC)
	{
		printf("The company NOT connected yet to communication infrastructure. Add Area first.");
		return 0;
	}

	Employee* a = malloc(sizeof(Employee));
	CHECK_AND_FREE(a);
	int num = 0;
	Employee* b = getEmp(pComp, &num);
	if (b != NULL) 
	{
		printf("this employee already exists\n");
		free(a);
		return 0;
	}
	int type =(int)getEmpType();
	if (!checkTypeEmp(type, pComp)) 
	{
		free(a);
		return 0;
	}
	initEmployee(a,type,num);
	
	// Initialize newEmployee as needed
	NODE* head = &pComp->employeeArr->head;/* Assume this is an existing node in your linked list */;
	NODE* newNode = L_insert_NEW(head, (void*)a); // Cast newEmployee to void*	
	CHECK_NULL_FREE_RETURN(newNode,a,"Employee Not inserted\n",freeEmployee);
	pComp->countEmployee++;

	return 1;
}
int checkTypeEmp(int type,const Company* p) {

	NODE* a = p->employeeArr->head.next;
	int count = 0;
	for (int i = 0; i < p->countEmployee; i++) {
		Employee* e = (Employee*)a->key;
		if ((int)e->type == type)
			count++;
		a = a->next;
	}
	int num = KINDEMP[type];
	if (count < num)
		return 1;
	printf("There is no place for this job\n");
	return 0;

}
int getUserId(Company* pComp, int* id) {

	int id1;
	do {
		printf("Please enter user id: ");
		scanf("%d", &id1);\
	} while (!getSumDigits(id1, 1));

	for (int i = 0; i < pComp->countUser; i++) {
		if (!isSameUser(id1, &pComp->userArr[i])) {
			printf("This user is already exists\n");
			*id = id1;
			return 0;
		}
	}

	return id1;
}
User*     getUser(int id, Company* p) {

	for (int i = 0; i < p->countUser; i++) {
		if (p->userArr[i].id - id == 0)
			return &p->userArr[i];
	}
	return NULL;
}
Employee* getEmp(Company* p, int* num)
{
	int n = 0;
	NODE* tmp = p->employeeArr->head.next;
	do {
		printf("Please enter employee phone number\n");
		scanf("%d", &n);
	} while (getSumDigits(n,0) != TEL);

	for (int i = 0; i < p->countEmployee; i++) {
		Employee* emp = (Employee*)tmp->key;
		if (emp->phoneNumber - n == 0)
			return emp;
		tmp = tmp->next;
	}
	*num = n;
	return NULL;
}
void    enterAreaToComp(Company* p, int num)
{
	p->loc->locAreaArr[p->loc->countAreas] = num;
	p->loc->countAreas++;
	printf("This area entered successfully\n");


}
int	    initComp(Company* pComp)
{
	pComp->option = (int)Nosorted;
	char a[MAX_ID+1] = { 0 };
	char* temp = a;
	printf("-----------  Init Company\n");
	pComp->nameComp= getStrExactName("Enter Company name: ");
	pComp->packageArr = NULL;
	pComp->countOfPackage = 0;
	pComp->userArr = NULL;
	pComp->countUser = 0;
	LIST* s= (LIST*)malloc(sizeof(LIST));
	CHECK_AND_FREE(s);
	pComp->employeeArr = s;
	CHECK_NULL_FREE_RETURN(L_init(pComp->employeeArr), s, "The initialization is failed\n", free);
	pComp-> countEmployee= 0;
	CI* c = (CI*)malloc(sizeof(CI));
	//CHECK_AND_FREE(c);
	if (c == NULL) {
		free(pComp->employeeArr); // Free LIST if CI allocation fails
		return 0; // Fail to allocate CI
	}
	pComp->loc = c;
	initCI(pComp->loc);
	initBankC(&pComp->details);
	return 1;
}
void    generalArrayFunction(void* arr, int sizeByte, int numOf, void f(void* element))
{

	for (int i = 0; i < numOf; i++)
	{
		printf("\n%d:\n", i+1);
		f((char*)arr + i * sizeByte);
		printf("\n");
	}

}
void    printPackageArr(const Company* arr)
{
	generalArrayFunction(arr->packageArr, sizeof(Package*), arr->countOfPackage, printPackage);

}
void	printUserArr(const Company* arr)
{
	generalArrayFunction(arr->userArr, sizeof(User), arr->countUser, printUser);

}
void	freePackageArr(Package** arr, int numOf)
{

	generalArrayFunction(arr, sizeof(Package*), numOf, freePackPtr);

}
void    printCompany(const Company* pComp)
{
	printf("Company name : %s\n", pComp->nameComp);
	printf("\n -------- Has %d users\n", pComp->countUser);
	printUserArr(pComp);
	printf("\n -------- Has %d Employees\n", pComp->countEmployee);
	printEmps(pComp);
	printf("\n\n -------- Has %d Packages\n", pComp->countOfPackage);
	printPackageArr(pComp);
	CI* c = pComp->loc;
	printf("\n -------- %s active in %d areas\n", pComp->nameComp, c->countAreas);
	if (c->countAreas< 1)
		return;
	printCI(c);
	
}
void    printCompToAdv(const Company* pComp, int type)
{
	char buffer[100];
	 // Buffer to hold formatted strings for printing

	// Format the company name with blue bold text
	sprintf(buffer, "\033[1;34mCompany name : %s\033[0m", pComp->nameComp);

	// Print the formatted string centered
	printCentered(buffer, 10);
	printPackageTv(pComp, type);
	
}
void printCentered(char* text, int width) {
	int len = (int)strlen(text);
	int padding = (width - len) / 2;
	for (int i = 0; i < padding; i++) printf(" ");  // Print spaces before the text
	printf("%s\n", text);  // Print the text
	
}
void printPackageTv(const Company* p, int type) {
	char buffer[100];  // Buffer to hold strings for printing

		sprintf(buffer, "\033[1;35mPackage: %s\033[0m", PackageStr[p->packageArr[type]->type]);
		printCentered(buffer, 35);

		// Print the number of channels centered and highlighted
		sprintf(buffer, "\033[1;36mNumber of Channels: %d\033[0m", p->packageArr[type]->countChannels);
		printCentered(buffer, 45);

		// Print "Channels Details:" centered and highlighted
		sprintf(buffer, "\033[1;35mChannels Details:\033[0m\n");
		printCentered(buffer, 50);

		// Print each channel's name and rating with % before the rating centered
		for (int j = 0; j < p->packageArr[type]->countChannels; j++) {
			sprintf(buffer, "- %s: %%%d", ChannelStr[p->packageArr[type]->channelsArr[j].type], p->packageArr[type]->channelsArr[j].rating);
			printCentered(buffer, 40);
		}
		printf("\n");
		
}
void    printEmps(const Company* c)
{

	NODE* tmp = c->employeeArr->head.next;

	int count = c->countEmployee;

	while (count != 0) {
		Employee* emp = (Employee*)tmp->key;  // Directly use Employee* stored in key
		printEmployee(emp);
		tmp = tmp->next;
		count--;
	}
}
void	freeCompany(Company* pComp)
{
		free(pComp->nameComp);
		freeUserArr(pComp->userArr, pComp->countUser);
		freePackageArr(pComp->packageArr, pComp->countOfPackage);
		free(pComp->packageArr);
		freeEmps(pComp);
		freeCI(pComp->loc);
		free(pComp);	
		
}
void    getIdentifierCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter company identifier  - %d UPPER CASE letters\t",MAX_ID);
		myGets(temp, MAX_STR_LEN);
		if (strlen(temp) != MAX_ID)
		{
			printf("id should be %d letters\n", MAX_ID);
			ok = 0;
		}
		else {
			for (int i = 0; i < MAX_ID; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Need to be upper case letter\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);
	printf("\n");
	strcpy(code, temp);


}
void    freeUserArr(User* userArr, int countUser)
{
		if (userArr != NULL) {
			for (int i = 0; i < countUser; ++i) {
				freeUser(&userArr[i]);
			}
			free(userArr);
		}
}
int     checkPackType(const Company* pComp, int type)
{
	for (int i = 0; i < pComp->countOfPackage; i++)
	{
		if (!isPackTypeInComp(pComp->packageArr[i], type))
			return 0;
	}

	return 1;
}
void    freeEmps(Company* p) 
{

	if (!L_free(p->employeeArr, freeEmpV)) 
	{
		printf("The list is NULL\n");
	}
	
	free(p->employeeArr);
}































