//#define _CRT_SECURE_NO_WARNINGS - this is update in our project in visual
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "MC_file.h"

int initMC(Ministry_Of_Communication* pManager, const char* fpB, const char* fpT) {

	int choice;

	do {
		printf("\nPlease choose how do you want upload System?\n");
		printf("1 - Upload the System from Binary file\n");
		printf("2 - Upload the System from Text file\n");
		scanf("%d", &choice);

		if (choice == 1)
		{
			if (initCompsFromBFile(pManager, fpB))
				return choice;
			return 3;

		}
		else if (choice == 2) {

			if (initMCFromTextFile(pManager, fpT))
				return choice;
			return 3;

		}
		else
			printf("Invalid choice, try again\n");

	} while (choice < 1 || choice > 2);
	return 3;

}
int initCompsFromBFile(Ministry_Of_Communication* pManager, const char* fileName)
{
	if (!readCompArrFromBFile(fileName, pManager))
		return 0;

	return 1;
}
int saveMCToBFile(const Ministry_Of_Communication* pManager, const char* fileName)
{
	if (!writeCompArrToBFile(fileName, pManager))
		return 0;
	return 1;
}
int saveMCToTextFile(const Ministry_Of_Communication* mc, const char* fileName)
{
	if (writeCompArrToTextFile(fileName, mc, mc->countComps) == 0)
		return 0;
	return 1;

}
int	initMCFromTextFile(Ministry_Of_Communication* pManager, const char* fileName)
{

	if (!readCompArrFromTextFile(fileName, pManager))
		return 0;


	return 1;
}

//write to B file

int writeCompArrToBFile(const char* fileName, const Ministry_Of_Communication* st)
{
	FILE* f = fopen(fileName, "wb");
	if (!f)
		return 0;

	if (fwrite(&st->countComps, sizeof(int), 1, f) != 1)
		return 0;

	for (int i = 0; i < st->countComps; i++) {
		if (!writeCompToBFile(f, st->companyarr[i]))
			return 0;
	}

	fclose(f);
	return 1;
}
int writeCompToBFile(FILE* f,const Company* p) {
	int len = MAX_ID+ 1;
	if (fwrite(&len, sizeof(int), 1, f) != 1)
		return 0;
	if (fwrite(p->identifierComp, sizeof(char), len, f) != len)
		return 0;

	int len1 = (int)strlen(p->nameComp) + 1;
	if (fwrite(&len1, sizeof(int), 1, f) != 1)
		return 0;
	if (fwrite(p->nameComp, sizeof(char), len1, f) != len1)
		return 0;

	if (fwrite(&p->countOfPackage, sizeof(int), 1, f) != 1)
		return 0;

	if (writePackArrToBFile(f, p) == 0)
	{
		fclose(f);
		return 0;
	}

	//user
	if (fwrite(&p->countUser, sizeof(int), 1, f) != 1)
		return 0;

	for (int i = 0; i < p->countUser; i++)
	{
		if (writeUserToBfile(f, &p->userArr[i]) == 0)
			return 0;
	}

	//emp
	if (fwrite(&p->countEmployee, sizeof(int), 1, f) != 1)
		return 0;

	if (writeEmpArrToBFile(f, p) == 0)
		return 0;

	//ci
		
		// Write countAreas
		if (fwrite(&p->loc->countAreas, sizeof(int), 1, f) != 1) {
			return 0;  // Error writing countAreas
		}

		// Write locAreaArr elements up to countAreas
		if (p->loc->countAreas > 0) {
			if (fwrite(p->loc->locAreaArr, sizeof(int), p->loc->countAreas, f) != p->loc->countAreas) {
				return 0;  // Error writing locAreaArr
			}
		}
	
	//bank
	if (saveBankToBinaryFileCompressed(&p->details, f) == 0)
		return 0;
	//op
	if (fwrite(&p->option, sizeof(int), 1, f) != 1)
		return 0;
	

	return 1;
	
}
int writeEmpArrToBFile(FILE* fp,const Company* p) {


	NODE* tmp = NULL;
	LIST* list = p->employeeArr;

	if (fwrite(&p->countEmployee, sizeof(int), 1, fp) != 1)
		return 0;

	tmp = list->head.next;
	int count = p->countEmployee;

	while (count != 0) // OR: (ch != EOF)

	{
		if (!writeEmpToBFile(fp, tmp))
		{
			return 0;
		}
		count--;
		tmp = tmp->next;
	}

	return 1;

}
int writeEmpToBFile(FILE* fp, NODE* vo) {

	// Cast the void* pointer to Employee* so we can access its fields
	Employee* emp = (Employee*)vo->key;


	int len = (int)strlen(emp->name) + 1;
	if (fwrite(&len, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(emp->name, sizeof(char), len, fp) != len)
		return 0;
	if (fwrite(&emp->type, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&emp->phoneNumber, sizeof(int), 1, fp) != 1)
		return 0;
	//Bank_Leumi details;

	if (saveBankToBinaryFileCompressed(&emp->details, fp) == 0)
		return 0;

	//ads

	int len2 = (int)strlen(emp->ads.street) + 1;
	if (fwrite(&len2, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(emp->ads.street, sizeof(char), len2, fp) != len2)
		return 0;

	int len3 = (int)strlen(emp->ads.city) + 1;
	if (fwrite(&len3, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(emp->ads.city, sizeof(char), len3, fp) != len3)
		return 0;
	if (fwrite(&emp->ads.building, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&emp->ads.apartment, sizeof(int), 1, fp) != 1)
		return 0;

	return 1;



 }
int writeUserToBfile(FILE* fp, User* u) {

	
	int len = (int)strlen(u->name) + 1;
	if (fwrite(&len, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(u->name, sizeof(char), len, fp) != len)
		return 0;

	int len1 = (int)strlen(u->compName) + 1;
	if (fwrite(&len1, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(u->compName, sizeof(char), len1, fp) != len1)
		return 0;
	//ads


	int len2 = (int)strlen(u->ads.street) + 1;
	if (fwrite(&len2, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(u->ads.street, sizeof(char), len2, fp) != len2)
		return 0;

	int len3 = (int)strlen(u->ads.city) + 1;
	if (fwrite(&len3, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(u->ads.city, sizeof(char), len3, fp) != len3)
		return 0;
	if (fwrite(&u->ads.building, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&u->ads.apartment, sizeof(int), 1, fp) != 1)
		return 0;
	//bank
	if (saveBankToBinaryFileCompressed(&u->details, fp) == 0)
		return 0;
	//pack

	Package* a = u->pack;

	if (fwrite(&a->price, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&a->countChannels, sizeof(int), 1, fp) != 1)
		return 0;

	if (writeChannelArrToBFile(fp, a) == 0)
		return 0;

	if (fwrite(&a->type, sizeof(int), 1, fp) != 1)
		return 0;


	if (fwrite(&u->phoneNum, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&u->id, sizeof(int), 1, fp) != 1)
		return 0;

	//date
	if (fwrite(&u->d.day, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&u->d.month, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&u->d.year, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}
int writePackArrToBFile(FILE* fp, const Company* p) 
{
	

	for (int i = 0; i < p->countOfPackage; i++)
	{
		Package* a = p->packageArr[i];

		if (fwrite(&a->price, sizeof(int), 1, fp) != 1)
			return 0;
		if (fwrite(&a->countChannels, sizeof(int), 1, fp) != 1)
			return 0;

		if (writeChannelArrToBFile(fp, a) == 0)
			return 0;

		if (fwrite(&a->type, sizeof(int), 1, fp) != 1)
			return 0;
	}

	return 1;

}
int writeChannelArrToBFile(FILE* fp, Package* p) {


	for (int i = 0; i < p->countChannels; i++) {
		Channel* c = &p->channelsArr[i];

		if (fwrite(&c->serialNum, sizeof(int), 1, fp) != 1)
			return 0;
		if (fwrite(&c->rating, sizeof(int), 1, fp) != 1)
			return 0;
		if (fwrite(&c->type, sizeof(int), 1, fp) != 1)
			return 0;
	}

	return 1;
}
int saveBankToBinaryFileCompressed(const Bank_Leumi* pBl, FILE* fp) {
	if (!pBl || !fp) {
		// Invalid input
		return 0;
	}

	// Allocate 4 bytes for data
	unsigned char data[4] = { 0 };
	// Pack the data
	data[0] = (pBl->blockCard << 7) | ((pBl->directDebit >> 3) & 0x7F);
	data[1] = ((pBl->directDebit & 0x07) << 5) | ((pBl->generalSum >> 16) & 0x1F); // Use 5 bits for the high part of generalSum
	data[2] = (pBl->generalSum >> 8) & 0xFF; // Use all 8 bits for the middle part of generalSum
	data[3] = pBl->generalSum & 0xFF; // Use all 8 bits for the low part of generalSum

	// Write the packed data to the file
	if (fwrite(data, sizeof(unsigned char), 4, fp) != 4) {
		// Error writing to file
		return 0;
	}

	return 1; // Success
}

//read from B file
int readCompArrFromBFile(const char* f, Ministry_Of_Communication* pManager)
{
	FILE* fp = fopen(f, "rb");
	if (!fp)
		return 0;
	
	
	if (fread(&pManager->countComps, sizeof(int), 1, fp) != 1)
		return 0;


	pManager->companyarr = (Company**)malloc(pManager->countComps * sizeof(Company*));
	CHECK_NULL_FREE_CLOSE_RETURN(pManager->companyarr, fp);

	
	for (int i = 0; i < pManager->countComps; i++)
	{
		pManager->companyarr[i]= (Company*)malloc(sizeof(Company));
		CHECK_NULL_FREE_CLOSE_RETURN(pManager->companyarr[i], fp);

		if (!readCompFromBFile(fp, pManager->companyarr[i]))
		{
			fclose(fp);
			return 0;

		}
	}
		
	fclose(fp);
	return 1;
}
int readCompFromBFile(FILE* fp,  Company* p)
{
	int lenId = MAX_ID+1;
	if (fread(&lenId, sizeof(int), 1, fp) != 1)
		return 0;
	if (fread(p->identifierComp, sizeof(char), MAX_ID + 1, fp) != lenId)
		return 0;
	p->identifierComp[lenId] = '\0';

	int len;
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	p->nameComp = (char*)malloc(len * sizeof(char));
	CHECK_AND_FREE(p->nameComp);
	
	if (fread(p->nameComp, sizeof(char), len, fp) != len)
	{
		free(p->nameComp);
		return 0;
	}

	if (fread(&p->countOfPackage, sizeof(int), 1, fp) != 1)
		return 0;

	p->packageArr = (Package**)malloc(p->countOfPackage * sizeof(Package*));
	CHECK_AND_FREE(p->packageArr);

	for (int i = 0; i < p->countOfPackage; i++)
	{
		Package* f = (Package*)malloc(sizeof(Package));
		CHECK_AND_FREE(f);
		p->packageArr[i] = f;

		if (readPackFromBfile(fp,p->packageArr[i]) == 0)
			return 0;

	}

	if (fread(&p->countUser, sizeof(int), 1, fp) != 1)
		return 0;

	User* u = (User*)malloc(p->countUser * sizeof(User));
	CHECK_AND_FREE(u);
	p->userArr = u;

	for (int k= 0; k < p->countUser; k++)
	{
		if (!readUserFromBFile(fp, &p->userArr[k]))
			return 0;

	}
	if (fread(&p->countEmployee, sizeof(int), 1, fp) != 1)
		return 0;

	if (readEmployeeArrFromBfile(fp, p) == 0)
		return 0;

		p->loc = malloc(sizeof(CI));
		CHECK_AND_FREE(p->loc);

		// Read countAreas
		if (fread(&p->loc->countAreas, sizeof(int), 1, fp) != 1) {
			return 0;  // Error reading countAreas
		}
		
		// Ensure countAreas does not exceed MAX_AREA
		if (p->loc->countAreas > MAX_AREA) {
			return 0;  // Error: countAreas exceeds MAX_AREA
		}
		
		// Read locAreaArr elements up to countAreas
		if (p->loc->countAreas > 0) {
			int count = p->loc->countAreas;
			if (fread(p->loc->locAreaArr, sizeof(int),count, fp) != p->loc->countAreas) {
				return 0;  // Error reading locAreaArr
			}
		}

	//	Bank_Leumi details;

	if (readBankFromBinaryFileCompressed(&p->details, fp) == 0)
		return 0;


	if (fread(&p->option, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;

	
}
int readEmployeeArrFromBfile(FILE* fp, Company* p) {
	// Allocate and initialize the list
	LIST* list = (LIST*)malloc(sizeof(LIST));
	CHECK_AND_FREE(list);
	list->head.next = NULL;  // Initialize the list's head

	// Read the number of employees
	if (fread(&p->countEmployee, sizeof(int), 1, fp) != 1)
	{
		free(list);
		return 0;
	}

	// Temporary pointer for keeping track of the last node (start with the head)
	NODE* lastNode = &list->head;

	for (int count = p->countEmployee; count > 0; --count) 
	{
		// Allocate a new Employee
		Employee* emp = (Employee*)malloc(sizeof(Employee));
		CHECK_NULL_FREE_RETURN(emp, list, "Error in read employee from binary file", free);
		// Read an Employee from the binary file
		if (!readEmployeeFromBFile(fp, emp)) {
			free(emp);
			free(list);
			return 0;  // Return error if reading Employee failed
		}

		// Insert the new Employee into the list
		NODE* newNode = L_insert_NEW(lastNode, emp);
		if (!newNode) {
			freeEmployee(emp);  // Assuming freeEmployee properly frees an Employee structure
			free(list);
			return 0;  // Return error if insertion failed
		}
	}
	// Assign the populated list to the company structure
	p->employeeArr = list;

	return 1;  // Success
}
int readEmployeeFromBFile(FILE* fp, Employee* emp)
{
	int len;
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	emp->name = (char*)malloc(len * sizeof(char));
	CHECK_AND_FREE(emp->name);
	
	if (fread(emp->name, sizeof(char), len, fp) != len)
	{
		free(emp->name);
		return 0;
	}

	if (fread(&emp->type, sizeof(int), 1, fp) != 1)
		return 0;
	if (fread(&emp->phoneNumber, sizeof(int), 1, fp) != 1)
		return 0;

	//Bank_Leumi details
	if (readBankFromBinaryFileCompressed(&emp->details, fp) == 0)
		return 0;

	//ads
	int len3;
	if (fread(&len3, sizeof(int), 1, fp) != 1)
		return 0;
	emp->ads.street = (char*)malloc(len3 * sizeof(char));
	CHECK_AND_FREE(emp->ads.street);
	if (fread(emp->ads.street, sizeof(char), len3, fp) != len3)
	{
		free(emp->name);
		return 0;
	}

	int len4;
	if (fread(&len4, sizeof(int), 1, fp) != 1)
		return 0;
	emp->ads.city = (char*)malloc(len4 * sizeof(char));
	CHECK_AND_FREE(emp->ads.city);
	
	if (fread(emp->ads.city, sizeof(char), len4, fp) != len4)
	{
		free(emp->ads.city);
		return 0;
	}
	if (fread(&emp->ads.building, sizeof(int), 1, fp) != 1)
		return 0;

	if (fread(&emp->ads.apartment, sizeof(int), 1, fp) != 1)
		return 0;

	return 1;
}
int readPackFromBfile(FILE* fp,Package* p) {

	if (fread(&p->price, sizeof(int), 1, fp) != 1)
		return 0;
	if (fread(&p->countChannels, sizeof(int), 1, fp) != 1)
		return 0;

	Channel* a = (Channel*)malloc(p->countChannels * sizeof(Channel));
	CHECK_AND_FREE(a);
	p->channelsArr = a;

	for (int j = 0; j < p->countChannels; j++)
	{

		if (fread(&p->channelsArr[j].serialNum, sizeof(int), 1, fp) != 1)
			return 0;
		if (fread(&p->channelsArr[j].rating, sizeof(int), 1, fp) != 1)
			return 0;
		if (fread(&p->channelsArr[j].type, sizeof(int), 1, fp) != 1)
			return 0;

	}

	if (fread(&p->type, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}
int readUserFromBFile(FILE* fp, User* u) 
{
	int len;
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	u->name = (char*)malloc(len * sizeof(char));
	CHECK_AND_FREE(u->name);
	
	if (fread(u->name, sizeof(char), len, fp) != len)
	{
		free(u->name);
		return 0;
	}

	int len1;
	if (fread(&len1, sizeof(int), 1, fp) != 1)
		return 0;
	u->compName = (char*)malloc(len1 * sizeof(char));
	CHECK_AND_FREE(u->compName);
	if (fread(u->compName, sizeof(char), len1, fp) != len1)
	{
		free(u->compName);
		return 0;
	}

	//ads
	int len3;
	if (fread(&len3, sizeof(int), 1, fp) != 1)
		return 0;
	u->ads.street = (char*)malloc(len3 * sizeof(char));
	CHECK_AND_FREE(u->ads.street);

	if (fread(u->ads.street, sizeof(char), len3, fp) != len3)
	{
		free(u->name);
		return 0;
	}

	int len4;
	if (fread(&len4, sizeof(int), 1, fp) != 1)
		return 0;
	u->ads.city = (char*)malloc(len4 * sizeof(char));
	CHECK_AND_FREE(u->ads.city);

	if (fread(u->ads.city, sizeof(char), len4, fp) != len4)
	{
		free(u->ads.city);
		return 0;
	}
	if (fread(&u->ads.building, sizeof(int), 1, fp) != 1)
		return 0;

	if (fread(&u->ads.apartment, sizeof(int), 1, fp) != 1)
		return 0;

     //bank
	if (readBankFromBinaryFileCompressed(&u->details, fp) == 0)
		return 0;

	//pack
	Package* f = (Package*)malloc(sizeof(Package));
	CHECK_AND_FREE(f);

	u->pack = f;

	if (readPackFromBfile(fp,u->pack) == 0)
		return 0;

	if (fread(&u->phoneNum, sizeof(int), 1, fp) != 1)
		return 0;

	if (fread(&u->id, sizeof(int), 1, fp) != 1)
		return 0;

	//Date
	if (fread(&u->d.day, sizeof(int), 1, fp) != 1)
		return 0;
	if (fread(&u->d.month, sizeof(int), 1, fp) != 1)
		return 0;
	if (fread(&u->d.year, sizeof(int), 1, fp) != 1)
		return 0;

	return 1;

}
int readBankFromBinaryFileCompressed(Bank_Leumi* pBl, FILE* fp) {
	if (!pBl || !fp) {
		// Invalid input
		return 0;
	}

	unsigned char data[4];

	// Read 4 bytes from the file
	if (fread(data, sizeof(unsigned char), 4, fp) != 4) {
		// Error reading from file
		return 0;
	}
	// Unpack the data
	pBl->blockCard = (data[0] >> 7) & 0x01;
	pBl->directDebit = ((data[0] & 0x7F) << 3) | ((data[1] >> 5) & 0x07);
	pBl->generalSum = ((data[1] & 0x1F) << 16) | (data[2] << 8) | data[3]; // Combine all parts of generalSum
	
	return 1; // Success
}

//write to text file

int writeCompArrToTextFile(const char* fileName, const Ministry_Of_Communication* mc, int countComps)
{
	FILE* fp;
	fp = fopen(fileName, "w");
	if (!fp)
		return 0;

	Company** arr = mc->companyarr;

	fprintf(fp, "%d\n", countComps);

	while (countComps > 0)
	{
		Company* p = *(Company**)arr;
		writeCompToTextFile(fp, p);
		countComps--;
		arr++;
	}

	fclose(fp);
	return 1;
}
int writeCompToTextFile(FILE* fp, Company* p) 
{

	fprintf(fp, "%s\n%s\n", p->identifierComp, p->nameComp);
	//packs
	fprintf(fp, "%d\n", p->countOfPackage);

	
	for(int i = 0; i < p->countOfPackage; i++)
	{
		if (writePackToTextFile(fp, p->packageArr[i])==0)
			return 0;

	}
	//users
	fprintf(fp, "%d\n", p->countUser);


	for (int i = 0; i < p->countUser; i++)
	{
		if (writeUserFromTextFile(fp, &p->userArr[i]) == 0)
			return 0;
	}
	//emps
	writeEmployeeArrToTextFile(fp, p->employeeArr, p->countEmployee);

	//ci 
	
		// Write countAreas
		fprintf(fp, "%d\n", p->loc->countAreas);

		// Write locAreaArr elements up to countAreas, each on a new line
		for (int i = 0; i < p->loc->countAreas; i++) {
			fprintf(fp, "%d\n", p->loc->locAreaArr[i]);
		}

	//bank
	fprintf(fp, "%d\n%d\n%d\n", p->details.blockCard, p->details.directDebit, p->details.generalSum);

	fprintf(fp, "%d\n", p->option);

	return 1;
	
}
int writeUserFromTextFile(FILE* fp, User* u) {

	fprintf(fp, "%s\n%s\n", u->name, u->compName);
	//	Address ads;

	fprintf(fp, "%s\n%s\n", u->ads.street, u->ads.city);
	fprintf(fp, "%d\n%d\n", u->ads.building, u->ads.apartment);

	//Bank_Leumi details
	fprintf(fp, "%d\n%d\n%d\n", u->details.blockCard, u->details.directDebit, u->details.generalSum);

	//PACK
	if (writePackToTextFile(fp, u->pack) == 0)
		return 0;
	fprintf(fp, "%d\n", u->phoneNum);

	fprintf(fp, "%d\n", u->id);

	//date
	fprintf(fp, "%d\n%d\n%d\n", u->d.day, u->d.month, u->d.year);

	return 1;
}
int writePackToTextFile(FILE* fp, Package* p) {

	fprintf(fp, "%d\n", p->price);
	fprintf(fp, "%d\n", p->countChannels);

	for (int i = 0; i < p->countChannels; i++)
	{
		writeChannelToTextFile(fp, &p->channelsArr[i]);
	}
	fprintf(fp, " %d\n", p->type);
	return 1;
}
void writeChannelToTextFile(FILE* fp, Channel* c)
{
	fprintf(fp, "%d\n%d\n%d\n",c->serialNum,c->rating,c->type);
}
void writeEmployeeArrToTextFile(FILE* fp, LIST* stArr, int empCount)
{

	NODE* tmp = stArr->head.next;

	fprintf(fp, "%d\n", empCount);

	while (tmp != NULL)
	{
		writeEmpToTextFile(fp, tmp);
		tmp = tmp->next;

	}

}
void writeEmpToTextFile(FILE* fp, NODE* v)

{
	// Cast the void* pointer to Employee* so we can access its fields
	
	Employee* employee = (Employee*)v->key;

	fprintf(fp, "%s\n%d\n%d\n", employee->name, employee->type, employee->phoneNumber);
	fprintf(fp, "%d\n%d\n%d\n", employee->details.blockCard, employee->details.directDebit, employee->details.generalSum);
	fprintf(fp, "%s\n%s\n", employee->ads.street, employee->ads.city);
	fprintf(fp, "%d\n%d\n", employee->ads.building, employee->ads.apartment);


}

//read from text file

int readCompArrFromTextFile(const char* fileName, Ministry_Of_Communication* mc)
{
	FILE* fp = fopen(fileName, "r");
	if (!fp)
		return 0;
	
	if (fscanf(fp, "%d", &mc->countComps) != 1)
		return 0;
	int i = 0;
	int count = mc->countComps;

	Company** c = (Company**)malloc(count * sizeof(Company*));
	CHECK_NULL_FREE_CLOSE_RETURN(c,fp);

	mc->companyarr = c;

	while (count != 0) // OR: (ch != EOF)

	{
		Company* comp = (Company*)malloc(sizeof(Company));
		CHECK_NULL_FREE_CLOSE_RETURN(comp, fp);

		mc->companyarr[i] = comp;
		if (!readCompFromTextFile(fp, mc->companyarr[i]))
		{
			fclose(fp);
			return 0;
		}
		count--;
		i++;

	}
	fclose(fp);
	
	return 1;
}
int readCompFromTextFile(FILE* fp, Company* p)
{

	char temp[MAX_STR_LEN] = { 0 };
	char* a = temp;
	char temp2[MAX_STR_LEN];
	char* b = temp2;//name
	
	
	a = myGetsFile(a, MAX_STR_LEN, fp);
	strcpy(p->identifierComp, a);

	myGetsF(b, MAX_STR_LEN, fp);
	p->nameComp = getDynStr(b);


	if (fscanf(fp, "%d", &p->countOfPackage) != 1)
		return 0;

	p->packageArr= (Package**)malloc(p->countOfPackage*sizeof(Package*));
	CHECK_AND_FREE(p->packageArr);

	for (int i = 0; i < p->countOfPackage; i++)
	{

		Package* f = (Package*)malloc(sizeof(Package));
		CHECK_AND_FREE(f);

		p->packageArr[i] = f;

		if (fscanf(fp, "%d", &p->packageArr[i]->price) != 1)
			return 0;
		if (fscanf(fp, "%d", &p->packageArr[i]->countChannels) != 1)
			return 0;

		Channel* a = (Channel*)malloc(p->packageArr[i]->countChannels * sizeof(Channel));
		CHECK_AND_FREE(a);
		p->packageArr[i]->channelsArr = a;

		for (int j = 0; j < p->packageArr[i]->countChannels; j++)
		{

			if (readChannelFromTextFile(fp, &p->packageArr[i]->channelsArr[j]) == 0)
				return 0;
		}
		if (fscanf(fp, "%d", &p->packageArr[i]->type) != 1)
			return 0;
		
	}


	if (fscanf(fp, "%d", &p->countUser) != 1)
		return 0;

	User* u = (User*)malloc(p->countUser * sizeof(User));
	CHECK_AND_FREE(u);
	p->userArr= u;

	for (int i = 0; i < p->countUser; i++)
	{
		if (readUserFromTextFile(fp, &p->userArr[i]) == 0)
			return 0;
	}

	LIST* L = readEmployeeArrFromTextFile(fp, p);
	p->employeeArr = L;

	CI* ci = (CI*)malloc(sizeof(CI));
	CHECK_AND_FREE(ci);

	p->loc = ci;
		// Read countAreas
		if (fscanf(fp, "%d", &p->loc->countAreas) != 1) {
			return 0; // Error reading countAreas
		}

		// Ensure countAreas does not exceed MAX_AREA
		if (p->loc->countAreas > MAX_AREA) {
			return 0;
		}// Error: countAreas exceeds MAX_AREA
		int loCarr[MAX_AREA] = { 0 };
		CHECK_AND_FREE(loCarr);

		for (int i = 0; i < MAX_AREA; i++) {
			p->loc->locAreaArr[i] = loCarr[i];
		}
		// Read locAreaArr elements up to countAreas
		for (int i = 0; i < p->loc->countAreas; i++) {
			if (fscanf(fp, "%d", &p->loc->locAreaArr[i]) != 1) {
				return 0; // Error reading locAreaArr element
			}
		}
    //bank
	if (fscanf(fp, "%d", &p->details.blockCard) != 1)
			return 0;
	if (fscanf(fp, "%d", &p->details.directDebit) != 1)
		return 0;
	if (fscanf(fp, "%d", &p->details.generalSum) != 1)
		return 0;


	if (fscanf(fp, "%d", &p->option) != 1)
		return 0;
	return 1;
}
int readUserFromTextFile(FILE* fp, User* u)
{
	char temp2[MAX_STR_LEN];
	char* name = temp2;
	char temp1[MAX_STR_LEN];
	char* nameComp = temp1;
	char temp3[MAX_STR_LEN];
	char* street = temp3;
	char temp4[MAX_STR_LEN];
	char* city = temp4;



	myGetsF(temp2, MAX_STR_LEN, fp);
	u->name = getDynStr(temp2);

	myGetsF(temp1, MAX_STR_LEN, fp);
	u->compName = getDynStr(temp1);
	
	//ads
	myGetsF(temp3, MAX_STR_LEN, fp);
	u->ads.street = getDynStr(temp3);

	myGetsF(temp4, MAX_STR_LEN, fp);
	u->ads.city = getDynStr(temp4);
	

	
	if (fscanf(fp, "%d", &u->ads.building) != 1)
		return 0;
	if (fscanf(fp, "%d", &u->ads.apartment) != 1)
		return 0;
	//bank
	if (fscanf(fp, "%d", &u->details.blockCard) != 1)
		return 0;
	if (fscanf(fp, "%d", &u->details.directDebit) != 1)
		return 0;
	if (fscanf(fp, "%d", &u->details.generalSum) != 1)
		return 0;
	//package
	Package* f = (Package*)malloc(sizeof(Package));
	CHECK_AND_FREE(f);
	u->pack= f;

	if (fscanf(fp, "%d", &u->pack->price) != 1)
		return 0;
	if (fscanf(fp, "%d", &u->pack->countChannels) != 1)
		return 0;

	Channel* a = (Channel*)malloc(u->pack->countChannels *sizeof(Channel));
	CHECK_AND_FREE(a);
	u->pack->channelsArr = a;

	for (int j = 0; j < u->pack->countChannels; j++)
	{
		if (readChannelFromTextFile(fp, &u->pack->channelsArr[j]) == 0)
			return 0;
	}

	if (fscanf(fp, "%d", &u->pack->type) != 1)
		return 0;

	if (fscanf(fp, "%d", &u->phoneNum) != 1)
		return 0;

	if (fscanf(fp, "%d", &u->id) != 1)
		return 0;

	//date
	if (fscanf(fp, "%d", &u->d.day) != 1)
		return 0;
	if (fscanf(fp, "%d", &u->d.month) != 1)
		return 0;
	if (fscanf(fp, "%d", &u->d.year) != 1)
		return 0;
	return 1;

}
LIST* readEmployeeArrFromTextFile(FILE* fp,Company* p)
{
	NODE* tmp = NULL;
	LIST* list = (LIST*)malloc(sizeof(LIST));

	if (!list)
	{
		free(list);
		return NULL;
	}
	L_init(list);


	if (fscanf(fp, "%d", &p->countEmployee) != 1)
		return 0;

	int count = p->countEmployee;

	while (count != 0) // OR: (ch != EOF)

	{
		tmp = (NODE*)malloc(sizeof(NODE));
		if (!tmp)
		{
			fclose(fp);
			return NULL;
		}
		
		if (!readEmployeeFromTextFile(fp, tmp))
		{
			if (!L_delete(tmp, freeEmployee))
			{
				fclose(fp);
				return NULL;

			}
			fclose(fp);
			return NULL;
		}

		NODE* update = L_insert_NEW(&list->head, tmp->key);
		if (!update) {
			if (!L_delete(tmp, freeEmployee))
			{
				fclose(fp);
				return NULL;

			}
			fclose(fp);
			return NULL;
		}
		count--;

	}
	
	return list;
}
int readEmployeeFromTextFile(FILE* fp, NODE* vo)
{
	char temp[MAX_STR_LEN] = { 0 };
	char* name = temp;
	char temp3[MAX_STR_LEN];
	char* street = temp3;
	char temp4[MAX_STR_LEN];
	char* city = temp4;
	
	vo->key = (Employee*)malloc(sizeof(Employee));
	CHECK_AND_FREE(vo->key);
	
	// Cast the void* pointer to Employee* so we can access its fields
	Employee* employee = (Employee*)vo->key;

	myGetsF(name, MAX_STR_LEN, fp);
	employee->name = getDynStr(name);
	
	if (!employee->name)
		return 0;

	if (fscanf(fp, "%d", &employee->type) != 1)
		return 0;
	if (fscanf(fp, "%d", &employee->phoneNumber) != 1)
		return 0;
	
	//bank
	if (fscanf(fp, "%d", &employee->details.blockCard) != 1)
		return 0;
	if (fscanf(fp, "%d", &employee->details.directDebit) != 1)
		return 0;
	if (fscanf(fp, "%d", &employee->details.generalSum) != 1)
		return 0;
	//ads
	myGetsF(temp3, MAX_STR_LEN, fp);
	employee->ads.street = getDynStr(temp3);
	
	myGetsF(temp4, MAX_STR_LEN, fp);
	employee->ads.city = getDynStr(temp4);
	
	if (fscanf(fp, "%d", &employee->ads.building) != 1)
		return 0;
	if (fscanf(fp, "%d", &employee->ads.apartment) != 1)
		return 0;

	return 1;
}
int readChannelFromTextFile(FILE* fp, Channel* c) {

	if (fscanf(fp, "%d", &c->serialNum) != 1)
		return 0;

	if (fscanf(fp, "%d", &c->rating) != 1)
		return 0;

	if (fscanf(fp, "%d", &c->type) != 1)
		return 0;

	return 1;
}
