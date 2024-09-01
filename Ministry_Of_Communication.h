#ifndef _MINISTRY_OF_COMMUNICATION_
#define _MINISTRY_OF_COMMUNICATION_
//#define _CRT_SECURE_NO_WARNINGS update in project properties

#include "Company.h"

#define tax 1700

		// Define an array of ANSI color codes
static const char* colors[] = {
        "\033[1;33m", // Bright Yellow
};
typedef struct
{
	int countComps;
	Company** companyarr;
	

} Ministry_Of_Communication;

void comparePrices(Ministry_Of_Communication* pManager);
void printAd(Ministry_Of_Communication* pManager);
int addPackMenu(char* b, Ministry_Of_Communication* pManager);
int printBankOp(char* b, const Ministry_Of_Communication* pManager);
int firstTime(Ministry_Of_Communication* pManager);
int chooseCompId(Ministry_Of_Communication* pManager, int option);
void printCompIds(const Ministry_Of_Communication* pManager);
int    addAreaM(Ministry_Of_Communication* pManager, char* a);
Company* getComp(char* id, const Ministry_Of_Communication* pManager);
int checkOverLapArea(const Ministry_Of_Communication* pManager, char* id, int num);
BOOL chargeCompanies(Ministry_Of_Communication* pManager);
int checkCompId(char* id,  Ministry_Of_Communication* pManager);
void	printMC(const Ministry_Of_Communication* pManager);
int     addComp(Ministry_Of_Communication* pManager);
void	freeMC(Ministry_Of_Communication* pManager);


#endif

