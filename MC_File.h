#ifndef _MC_FILE_
#define _MC_FILE_
//#define _CRT_SECURE_NO_WARNINGS update in project properties

#include <stdio.h>
#include "Ministry_Of_Communication.h"


typedef unsigned char BYTE;

int initMC(Ministry_Of_Communication* pManager, const char* fpB, const char* fpT);
int saveMCToTextFile(const Ministry_Of_Communication* mc, const char* fileName);
int	initMCFromTextFile(Ministry_Of_Communication* pManager, const char* fileName);
int initCompsFromBFile(Ministry_Of_Communication* pManager, const char* fileName);
int saveMCToBFile(const Ministry_Of_Communication* pManager, const char* fileName);

//write B file
int writeCompArrToBFile(const char* fileName, const Ministry_Of_Communication* st);
int writeCompToBFile(FILE* f, const Company* p);
int writeEmpArrToBFile(FILE* fp,const Company* p);
int writeEmpToBFile(FILE* fp, NODE* vo);
int writeUserToBfile(FILE* fp, User* u);
int writePackArrToBFile(FILE* fp, const Company* p);
int writeChannelArrToBFile(FILE* fp, Package* p);
int saveBankToBinaryFileCompressed(const Bank_Leumi* b, FILE* fp);

//read B file
int readCompArrFromBFile(const char* f, Ministry_Of_Communication* pManager);
int readCompFromBFile(FILE* fp, Company* p);
int readEmployeeArrFromBfile(FILE* fp, Company* p);
int readEmployeeFromBFile(FILE* fp, Employee* e);
int readPackFromBfile(FILE* fp, Package* p);
int readUserFromBFile(FILE* fp, User* u);
int readBankFromBinaryFileCompressed(Bank_Leumi* b, FILE* fp);

//write T file
int writeCompArrToTextFile(const char* fileName, const Ministry_Of_Communication* mc, int countComps);
int writeCompToTextFile(FILE* fp, Company* p);
int writeUserFromTextFile(FILE* fp, User* u);
int writePackToTextFile(FILE* fp, Package* p);
void writeChannelToTextFile(FILE* fp, Channel* c);
void writeEmployeeArrToTextFile(FILE* fp, LIST* stArr, int empCount);
void writeEmpToTextFile(FILE* fp, NODE* v);

//read T file
int readCompArrFromTextFile(const char* fileName, Ministry_Of_Communication* mc);
int readCompFromTextFile(FILE* fp, Company* p);
int readUserFromTextFile(FILE* fp, User* u);
LIST* readEmployeeArrFromTextFile(FILE* fp, Company* p);
int readEmployeeFromTextFile(FILE* fp, NODE* vo);
int readChannelFromTextFile(FILE* fp, Channel* c);





#endif