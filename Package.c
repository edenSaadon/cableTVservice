#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Package.h"
//#define _CRT_SECURE_NO_WARNINGS - this is update in our project in visual



void initPackage(Package* p,int type)
{
		
	p->type=type;
	int num;

	do 
	{
		printf("How much channels you want to add\n");
		printf("For Basic package: 1-15 maximum number of channels\n");
		printf("For Premium package: 1-30 maximum number of channels\n");
		printf("For Deluxe package: 1-50 maximum number of channels\n");
		scanf("%d", &num);
		if(!checkNum(type, num))
			printf("Invalid choice, try again\n");

	} while (!checkNum(type,num));

	for (int i = 0; i < num; i++)
	{
		addChannel(p);
	}
	calculatePrice(p);
}

int checkNum(int type, int num)
{

	if (num < 1)
		return 0;

	if (type - 1 == (int)eBasic) 
	{
		if (num > MAX_PAC[eBasic])
			return 0;
	}
	else if (type - 1 == (int)ePremium)
	{
		if (num > MAX_PAC[ePremium])
			return 0;
	}
	else if (type - 1 == (int)eDeluxe)
	{
		if (num > MAX_PAC[eDeluxe])
			return 0;
	}

	return 1;

}

void calculatePrice(Package* p)
{

	for (int i = 0; i < p->countChannels; i++) 
	{
		p->price += getPriceChannel(p->channelsArr[i].type);
	}

	printf("The price is: %d\n" , p->price);
}


int getPackageType() 
{
	int option;
	printf("Choose one of the following numbers:\n");
	printf("1: Basic\n");
	printf("2: Premium\n");
	printf("3: Deluxe\n");
	scanf("%d", &option);
	return option-1;

}
int		isPackTypeInComp(const Package* p, int t)
{
	if ((int)p->type == t)
		return 0;
	return 1;
}

int addChannel(Package* p)
{

	Channel pChannel;

	initChannel(&pChannel, p->channelsArr, p->countChannels);

	Channel* arr = (Channel*)realloc(p->channelsArr, (p->countChannels + 1) * sizeof(Channel));

	if (!arr)
	{
		free(arr);
		return 0;
	}
	p->channelsArr = arr;
	p->channelsArr[p->countChannels] = pChannel;
	p->countChannels++;


	return 1;
	
}

int findLocChannel(const Package* p, int num)
{
    
	for (int i = 0; i < p->countChannels; i++) {
		if (p->channelsArr[i].serialNum == num)
			return i;
	}
	return -1;
}
void	freePackPtr(void* pack)
{
	Package* p = *( Package**)pack;
		free(p->channelsArr);
		free(p);
	
}

void freePackageU(Package* p)

{
	free(p->channelsArr);

	free(p);

}

void printPackage(const void* pack)
{

	const Package* p = *(const Package**)pack;

;
	printf("\nPackage: price: %d, type:%s \n", p->price, PackageStr[p->type]);
	printf("\n");
	printf("this package has: %d channels\n", p->countChannels);
	printf("\n");
	
	for (int i = 0; i < p->countChannels; i++) 
	{
		printChannel(&p->channelsArr[i]);
		printf("\n");
	}
	
	
}

void printPackageU(const Package* p)
{

	printf("Package: type:%s, price: %d", PackageStr[p->type], p->price);
	printf("\n");

	for (int i = 0; i < p->countChannels; i++)
	{
		printChannel(&p->channelsArr[i]);
		printf("\n");
	}


}

