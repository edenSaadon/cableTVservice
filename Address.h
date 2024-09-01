#ifndef __ADDRESS__
#define __ADDRESS__

typedef struct
{
	char* street;
	char* city;
	int	building;
	int	apartment;

} Address;

void   initAddress(Address* pAd);
void   printAddress(const Address* pAd);
void   freeAddress(Address* pAd);
int getIntFromUser(const char* prompt);

#endif

