#ifndef __USER__
#define __USER__
//#define LEN 20

#include "Address.h"
#include "Bank.h"
#include "Date.h"
#include "Package.h"
#define TEL 10
#define TAZ 8


typedef struct
{
	char*	name;
	char* compName;
	Address ads;
	Bank_Leumi details;
	Package* pack;
	int phoneNum;
	int id;
	Date d;

} User;

int getSumDigits(int phoneNumber, int sign);
void	initUser(User* u,char* compName);
int     checkReduction(User* u, int price);
int	isSameUser(int id1, const User* u2);
void	printUser(const void* u);
void	freeUser(User* u);


#endif 