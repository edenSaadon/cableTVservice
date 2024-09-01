#ifndef __PACKAGE__
#define __PACKAGE__
//#define _CRT_SECURE_NO_WARNINGS update in project properties

#include "Channel.h"
#include "General.h"
static const int MAX_PAC[3] = { 15,30,50 };
typedef enum {
	eBasic, ePremium, eDeluxe, eNofPackge
} ePackgeType;

static const char* PackageStr[eNofPackge]
= { "Basic","Premium","Deluxe" };

typedef struct
{
	int price;
	int countChannels;
	Channel* channelsArr;
	ePackgeType type;

}Package;

void	freePackPtr(void* pack);
void printPackageU(const Package* p);
int checkNum(int type, int num);
void initPackage(Package* p, int type);
void calculatePrice(Package* p);
int getPackageType();
int addChannel(Package* p);
int		isPackTypeInComp(const Package* p, int t);
int findLocChannel(const Package* p, int num);
void freePackageU(Package* p);
void printPackage(const void* pack);


#endif
