#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h >
#include "Communication_Infrastructure.h"

const int AREA_RANGE[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

void initCI(CI* c) 
{
	int arr[MAX_AREA] = { 0 };
	c->countAreas = 0;
	memcpy(c->locAreaArr, arr, sizeof(arr));//all the members in c->locAreaArr are 0
	
}
int checkIfExistAreaG(const CI* c, int area)
{
	for (int i = 0; i < c->countAreas; i++)
	{
		if (c->locAreaArr[i] == area)
		{
			return 0;
		}
	}
	return 1;

}
void printCI(const void* ci) 
{
	CI* c = (CI*)ci;
	
	printf("This company has: %d areas \n",c->countAreas);

	printf("The areas of this company are: ");
	for (int i = 0; i < c->countAreas; i++)
	{
		printf("%d ", c->locAreaArr[i]);
		printf(" ");
    }
	printf("\n");
}
void freeCI(CI* c)
{
	free(c);
}