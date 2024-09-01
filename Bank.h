#ifndef __BANK__
#define __BANK__
#define MIN_BC 100000
#define MIN_BU 10000
#define MIN_BE 1000
#define  MAX_DEBIT 1000// the MC decided that this is the max price for package 


#define CHECK_NULL_FREE_CLOSE_RETURN(ptr, file) do { \
    if (!(ptr)) { \
        free(ptr); \
        fclose(file); \
        return 0; \
    } \
} while(0)

#define  CHECK_NULL_FREE_RETURN(p, a, message, freeFunc) do { \
    if (!(p)) { \
        printf("%s", (message)); \
        freeFunc(a); \
        return 0; \
    } \
} while(0)
#define  CHECK_NULL_RETURN(p, message) do { \
    if (!(p)) { \
        printf("%s", (message)); \
        return 0; \
    } \
} while(0)


#define CHECK_AND_FREE(p) do { \
    if (!(p)) { \
        free(p); \
        return 0; \
    } \
} while(0)


typedef  enum { FALSE, TRUE } BOOL;


typedef struct
{
	BOOL blockCard;
	int directDebit;
	int	generalSum;

} Bank_Leumi;


void	initBankC(Bank_Leumi* b);
void	initBankU(Bank_Leumi* b);
void	initBankE(Bank_Leumi* b);
void	printBank(const Bank_Leumi* b);
BOOL    addSalary(Bank_Leumi* b, int salary);
int	    blockCard(Bank_Leumi* b, int debit, int sign);
BOOL    updateDirectDebit(Bank_Leumi* b, int debit,int sign);

#endif 

