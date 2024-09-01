#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include  "Ministry_of_Communication.h"
/*int firstTime(Ministry_Of_Communication* pManager)//activated in first time of program in order to create the data base 
{
	pManager->companyarr = NULL;
	pManager->countComps = 0;
	for (int i = 0; i < 2; i++) {
		if (addComp(pManager)) {
			if (!addAll(pManager->companyarr[i]))
			return 0;
			if (!addAreaM(pManager, pManager->companyarr[i]->identifierComp))
				return 0;
		}
		else
		return 0;
		
	}	
	return 1;
}*/

int    addAreaM(Ministry_Of_Communication* pManager, char* a)
{
	int num;
	printf("Which area you want to add 1-15?\n");
	scanf("%d", &num);

	Company* c = getComp(a, pManager);
	if (num > MAX_AREA)
	{
		printf("This area NOT in range\n");
		return 0;
	}
	if (!checkIfExistAreaG(c->loc, num)) 
	{
		printf("This area already exists\n");
		return 0;
	}
	
	if (checkOverLapArea(pManager, a, num) >= limitCompPerArea)
	{
		printf("This area has max companies\n");
		return 0;
	}
	
	enterAreaToComp(c, num);
	
	return 1;

}

Company* getComp(char* id,const Ministry_Of_Communication* pManager)
{

	for (int i = 0; i < pManager->countComps; i++) 
	{
		if (strcmp(pManager->companyarr[i]->identifierComp, id) == 0)
			return pManager->companyarr[i];
	}
	return NULL;

}

int checkOverLapArea(const Ministry_Of_Communication* pManager, char* id, int num)
{
	int count = 0;

	for (int i = 0; i < pManager->countComps; i++)
	{

			if ((checkIfExistAreaG(pManager->companyarr[i]->loc,num)==0) && (strcmp(pManager->companyarr[i]->identifierComp,id)!=0))
				count++;
	}
	return count;
}

BOOL chargeCompanies(Ministry_Of_Communication* pManager)
{
	if (pManager->countComps < MIN_EUC)
		return FALSE;

	for (int i = 0; i < pManager->countComps; i++)
	{
		if (pManager->companyarr[i]->loc->countAreas == 0)
		{
			printf("%s company NOT connected yet to communication infrastructure. Add Area first.", pManager->companyarr[i]->nameComp);
		}
		else if (!checkCompany(pManager->companyarr[i], tax))
		{
			printf("Call %s company is NOT charged\n", pManager->companyarr[i]->nameComp);
		}
		else
		printf("%s company charge has been completed\n", pManager->companyarr[i]->nameComp);

	}
	return TRUE;
}

int addComp( Ministry_Of_Communication* pManager)
{
	char a[MAX_ID + 1] = { 0 };
	char* temp = a;
	
	Company* comp = (Company*)calloc(1, sizeof(Package));
	CHECK_AND_FREE(comp);
	getIdentifierCode(temp);
	CHECK_NULL_FREE_RETURN(checkCompId(temp, pManager), comp, "This company is already exists ", free);
	
	strcpy(comp->identifierComp, a);

	initComp(comp);
	
	Company** arr = (Company**)realloc(pManager->companyarr, (pManager->countComps + 1) * sizeof(Company*));
	CHECK_AND_FREE(arr);
	
	pManager->companyarr = arr;
	pManager->companyarr[pManager->countComps] = comp;
	pManager->countComps++;

	return 1;

}

int checkCompId(char* id, Ministry_Of_Communication* pManager)
{
	Company** arr = pManager->companyarr;
	for (int i = 0; i < pManager->countComps; i++)
	{
		Company* p = arr[i];
		char* str = p->identifierComp;
		if (strcmp(id,str)==0)
			return 0;
		
	}
	return 1;
}

void	printMC(const Ministry_Of_Communication* pManager) 
{
	printf("Ministry Of Communication");
	printf("\n -------- Has %d companies\n", pManager->countComps);

	for (int i = 0; i < pManager->countComps; i++)
	{
		printCompany(pManager->companyarr[i]);
		printf("\n");
		printf("--------------------------------------------------------------------------------\n");
	}
}

void	freeMC(Ministry_Of_Communication* pManager) 
{	
  
	for (int i = 0; i < pManager->countComps; i++) 
	{
		freeCompany(pManager->companyarr[i]);
	}

	free(pManager->companyarr);
	
}

int chooseCompId(Ministry_Of_Communication* pManager,int option)
{
	
	char temp[MAX_STR_LEN] = { 0 };
	char* b = temp;
	
	do{
		printf("\nPlease choose one company ,write id\n");
		printCompIds(pManager);
		getIdentifierCode(b);
		if(checkCompId(b, pManager))
		printf("Invalid choice, try again\n");

	} while (checkCompId(b, pManager));

	if (option == 1)
	{
		printCompany(getComp(b, pManager));
		return 1;
	}
	else if (option == 2)
	{
		printUserArr(getComp(b, pManager));
		return 1;

	}
	else if (option == 3)
	{
		printEmps(getComp(b, pManager));
		return 1;

	}	
	else if (option == 4)
	{
		CHECK_NULL_RETURN(printBankOp(b, pManager), "\nInvalid number\n");
		return 1;
	}
	else if (option == 6)
	{
		CHECK_NULL_RETURN(addPackMenu(b, pManager), "Error");
		return 1;

	}
	else if (option == 7)
	{
		if (!addUser(getComp(b, pManager)))
			return 0;
		return 1;

	}
	else if (option == 8)
	{
		if (!addEmployee(getComp(b, pManager)))
			return 0;
		return 1;
	}
	else if (option == 9)
	{
		if (!addAreaM(pManager,b))
			return 0;
		return 1;
	}
	else if (option == 10)
	{
		sortUser(getComp(b, pManager));
		return 1;
	}
	else if (option == 11)
	{
		if (!findUser(getComp(b, pManager)))
			return 0;
		return 1;
	}
	else if (option == 13)
	{
		paymentMonthlyMethodUserArr(getComp(b, pManager));
		return 1;
	}
	else if (option == 14)
	{
		updateAccountEmp(getComp(b, pManager));
		return 1;
	}
	
	
	return 0;

}

void printAd(Ministry_Of_Communication* pManager)
{
	char buffer[100];
	sprintf(buffer, "\033[1;5;31m%s\033[0m","~~~TV-Advertising~~~"); // Bold and blinking red text
	printCentered(buffer, 60);
	comparePrices(pManager);
}

void comparePrices(Ministry_Of_Communication* pManager)
{
	
	int loc = 0;
	int sumB = pManager->companyarr[0]->packageArr[eBasic]->price;
	int sumP =pManager->companyarr[0]->packageArr[ePremium]->price;
	int sumD = pManager->companyarr[0]->packageArr[eDeluxe]->price;

	int b = 0;
	int p = 0;
	int d = 0;

	for (int i = 1 ; i < pManager->countComps; i++)
	{
		if (pManager->companyarr[i]->countOfPackage == 3) 
		{

			if (pManager->companyarr[i]->packageArr[eBasic]->price < sumB)
			{
				sumB = pManager->companyarr[i]->packageArr[eBasic]->price;
				b = i;
			}
			if (pManager->companyarr[i]->packageArr[ePremium]->price < sumP)
			{
				sumB = pManager->companyarr[i]->packageArr[ePremium]->price;
				p = i;
			}
			if (pManager->companyarr[i]->packageArr[eDeluxe]->price < sumD)
			{
				sumB = pManager->companyarr[i]->packageArr[eDeluxe]->price;
				d = i;
			}
		}
	}
	printf("\033[5;1;37mThe cable company with the cheapest Basic package:\033[0m\n");
	printCompToAdv(pManager->companyarr[b], 0);
	printf("\033[5;1;37mThe cable company with the cheapest Premium package:\033[0m\n");
	printCompToAdv(pManager->companyarr[p], 1);
	printf("\033[5;1;37mThe cable company with the cheapest Deluxe package:\033[0m\n");
	printCompToAdv(pManager->companyarr[d], 2);

	
}

int addPackMenu(char* b, Ministry_Of_Communication* pManager)
{
	int num;
	printf("Press 1 for add new package for Company\n");
	printf("Press 2 for change package to exists User\n");
	scanf("%d", &num);
	if (num == 1)
	{
		if (!addPackC(getComp(b, pManager)))
			return 0;
		return 1;
	}
	else
	{

		if (!addPackU(getComp(b, pManager)))
			return 0;
		return 1;
	}
	printf("Invalid number\n");
	return 0;
}

int printBankOp(char* b,const  Ministry_Of_Communication* pManager)
{
	Company* c = getComp(b, pManager);
	if (!c)
		return 0;
	int num;
	printf("Press 1 for Company\n");
	printf("Press 2 for User\n");
	printf("Press 3 for Employee\n");
	scanf("%d", &num);
	if (num == 1)//company
	{
		printBank(&c->details);
		return 1;
	}
	else if (num == 2)//user
	{
		int id = 0;
		int val = getUserId(c, &id);

		if (val != 0) {
			printf("this user is not exists");
			return 0;
		}
		User* u = getUser(id, c);
		if (!u)
			return 0;
		printBank(&u->details);
		return 1;

	}
	else if (num == 3)
	{
		int n = 1;
		Employee* e = getEmp(c, &n);
		if (!e)
			return 0;
		printBank(&e->details);
		return 1;
	}
	return 0;
}

void printCompIds(const Ministry_Of_Communication* pManager)
{
		int numColors = sizeof(colors) / sizeof(colors[0]); // Number of colors available

		for (int i = 0; i < pManager->countComps; i++) 
		{
			// Select color for this iteration
			const char* color = colors[i % numColors];

			// Print company name and ID in selected color
			printf("%sCompany name: %s\t, Company ID: %s\033[0m\n", color, pManager->companyarr[i]->nameComp, pManager->companyarr[i]->identifierComp);
			
		}
		

}


