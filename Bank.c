//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "bank.h"


void	initBankC(Bank_Leumi* b)
{
	b->blockCard = FALSE;
	b->directDebit = 0;
	b->generalSum = MIN_BC;//Minmum for add company 
}

void	initBankU(Bank_Leumi* b)
{
	b->blockCard = FALSE;
	b->directDebit = 0;
	b->generalSum = MIN_BU;//minmum for add user 
}

void	initBankE(Bank_Leumi* b)
{
	b->blockCard = FALSE;
	b->directDebit = 0;
	b->generalSum = MIN_BE;//minmum for add employee 
}

int	blockCard(Bank_Leumi* b, int red, int sign)
{
	if (sign == 1) 
	{//check just for user
		if (red > MAX_DEBIT)
		{
			b->blockCard = TRUE;
			return 1;
		}
	}
	if (b->generalSum < red )//continue check for user or company
	{
		b->blockCard = TRUE;
		return 1;
	}

	return 0;
}

void	printBank(const Bank_Leumi* b) 
{
	printf("The general sum of your account is: %d\n", b->generalSum);
	printf("The card is: %s\n", b->blockCard ? "Blocked" : "Not Blocked");
	printf("The direct debit is: %d\n", b->directDebit);
}

BOOL addSalary(Bank_Leumi* b, int salary) 
{
	b->generalSum = +salary;
	return TRUE;
}

BOOL updateDirectDebit(Bank_Leumi* b, int debit, int sign)
{
	if (sign == 1) {//check just for user
		if (debit > MAX_DEBIT)
		{
			return FALSE;
		}
	}

	b->directDebit = debit;
	return TRUE;
	
	
}



