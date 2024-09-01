#ifndef _DATE_
#define _DATE_
//#define _CRT_SECURE_NO_WARNINGS update in project properties


#define MIN_YEAR 2024

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void	getCorrectDate(Date* pDate);
int		checkDate(char* date, Date* pDate);
void	printDate(const Date* pDate);

#endif
