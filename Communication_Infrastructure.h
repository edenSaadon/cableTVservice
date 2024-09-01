#ifndef __COMMUNICATION_INFRASTRUCTURE__
#define __COMMUNICATION_INFRASTRUCTURE__

#define limitCompPerArea 3
#define MAX_AREA 15


typedef struct
{
	int countAreas;
	int locAreaArr[MAX_AREA];
} CI;

void initCI(CI* c);
int checkIfExistAreaG(const CI* c, int area);
void freeCI(CI* c);
void printCI(const void* ci);
#endif 
