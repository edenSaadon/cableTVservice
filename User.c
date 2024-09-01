#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"


void	initUser(User* u,char* nameComp)
{
	u->name = getStrExactName("Please enter user name:");
	u->compName = nameComp;
	initAddress(&u->ads);
	initBankU(&u->details);
	do
	{
		printf("Please enter user phone number: ");
		scanf("%d", &u->phoneNum);
	} while (getSumDigits(u->phoneNum, 0)==0);
	getCorrectDate(&u->d);
}
int getSumDigits(int phoneNumber, int sign)
{
	int count = 0;
	int originalNumber = phoneNumber;

	// Count the digits and calculate the sum
	while (originalNumber > 0) 
	{
		originalNumber /= 10; // Remove the last digit
		count++; // Increment the digit count
	}

	if (sign == 1) //user id
	{
		if (count < TAZ || count > TAZ + 1) 
		{
			printf("NOT VALID ID\n");
			return 0;
		}
		return 1;
	}

	// Check if the original number had exactly 9 digits
	if (count == TEL-1)
		return count + 1;
	printf("This is not a phone number\n");
	return 0; // Return 0 if not exactly 9 digits
}
int checkReduction(User* u, int red)
{

	if (!blockCard(&u->details, red,1))
	{
		if (!updateDirectDebit(&u->details, red,1))
			return 0;
		return 1;
	}

	return 0;
}
int	isSameUser(int id1, const User* u2)
{
	if (!u2)
		return 0;
	if (id1 == u2->id)
		return 0;
	return 1;
}
void	printUser(const void* v)
{
	const User* u = (const User*)v;
	printf("\nUser name:%s ,Phone number: 0%d, id: %d \n", u->name, u->phoneNum, u->id);
	printf("User joined in ");
	printDate(&u->d);
	printf("\nUser Package is:\n");
	printPackageU(u->pack);
	printAddress(&u->ads);
	printf("User Bank is private.\n\n");
}
void	freeUser(User* u)
{
	if (u != NULL) 
	{
		free(u->name);
		freeAddress(&u->ads);
		free(u->compName);
		if (u->pack != NULL)
			freePackageU(u->pack);
	
	}
	
	
}


