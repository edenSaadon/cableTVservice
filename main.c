#include <stdio.h>
#include <stdlib.h>
#include  "main.h"
//#include <crtdbg.h>
#include "mc_file.h"
//#define _CRT_SECURE_NO_WARNINGS

int main() {

   // int first = -1;
	Ministry_Of_Communication mc;

	/* if (first == -1)//activated in first time of program in order to create the data base 
	{
		if (!firstTime(&mc))
			return 0;
		//Text
		if (!writeCompArrToTextFile(MC_FILE_TEXT, &mc, 2))
			return 0;
		//BIN
		for (int i = 0; i < 2; i++) {
			if (!saveMCToBFile(&mc, MC_FILE_BIN))
				return 0;
		}
		
	}*/
	

	int choice = initMC(&mc, MC_FILE_BIN, MC_FILE_TEXT);

	if (choice != 1 && choice != 2)
	{
		printf("error init");
		return 0;
	}

	int option;
	int stop = 0;

	do
		{
					option = menu();
					switch (option)
					{
					case eShowAll://mc
						    printMC(&mc);
						break;

					case eShowComp://one comp
		
						if (!chooseCompId(&mc,(int)eShowComp))
							printf("Error \n");
						break;

					case eShowU://all users from one comp
						if (!chooseCompId(&mc,(int)eShowU))
							printf("Error \n");
						break;

					case eShowEmp://all emps from one comp
						if (!chooseCompId(&mc, (int)eShowEmp))
							printf("Error \n");
						break;
					case eShowBank://all emps from one comp
						if (!chooseCompId(&mc, (int)eShowBank))
							printf("Error \n");
						break;
					case eAddComp://mc add comp
						if(!addComp(&mc))
							printf("Error \n");
						break;

					case eAddPack://comp or user
						if (!chooseCompId(&mc, (int)eAddPack))
							printf("\n");
						break;
					case eAddUser://comp add user
						if (!chooseCompId(&mc, (int)eAddUser))
							printf("Error \n");
						break;
					case eAddEmp://comp add emp
						if (!chooseCompId(&mc, (int)eAddEmp))
							printf("Error \n");
						break;
					case eAddArea://mc add area to comp 
						if (!chooseCompId(&mc, (int)eAddArea))
							printf("Error \n");
						break;
					case eSortU://for one comp
						if (!chooseCompId(&mc, (int)eSortU))
							printf("Error \n");
						break;
					case eFindU://for one comp
						if (!chooseCompId(&mc, (int)eFindU))
							printf("Error \n");
						break;
					case eGetTax://mc get from comp
						if (!chargeCompanies(&mc))
							printf("Error \n");
						break;
					case eGetCharge://comp get from user
						if (!chooseCompId(&mc, (int)eGetCharge))
							printf("Error \n");
						break;
					case eSetEmpSalary://comp set emp account
						if (!chooseCompId(&mc, (int)eSetEmpSalary))
							printf("Error \n");
						break;
					case eAdv://comp set emp account
						printAd(&mc);
						break;
					case EXIT:
						printf("Bye bye\n");
						stop = 1;
						break;
					default:
						printf("Wrong option\n");
						break;
					}
				} while (!stop);

				saveMCToBFile(&mc, MC_FILE_BIN);
				saveMCToTextFile(&mc, MC_FILE_TEXT);
				freeMC(&mc);

				//printf("before dump\n");
				//_CrtDumpMemoryLeaks();
				return 1;
			}

		
			int menu() {
				int option;
				printf("\n\n");
				printf("Please choose one of the following options\n");

				const char* lightYellow = "\033[1;33m"; // Light Yellow

				for (int i = 0; i < eNofOps; i++) {
					printf("%s%d - %s\033[0m\n", lightYellow, i, str[i]);
				}
				printf("%s%d - Quit\033[0m\n", lightYellow, EXIT); // Using the same color for Quit option
				printf("Enter your choice: ");
				scanf("%d", &option);

				// Clean buffer
				char tav;
				scanf("%c", &tav);

				return option;
			}






