#ifndef __GENERAL__
#define __GENERAL__
//#define _CRT_SECURE_NO_WARNINGS 

#define MAX_STR_LEN 255


char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size);
char* getDynStr(char* str);
char* myGetsFile(char* buffer, int size, FILE* fp);
char* myGetsF(char* buffer, int size, FILE* source);

#endif
