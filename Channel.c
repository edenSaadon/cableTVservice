#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Channel.h"
#include "stdlib.h"
//#define _CRT_SECURE_NO_WARNINGS 

const int CHANNEL_CONTENT[7] = { 3,5,10,15,20,25,30 };//prices of channels by content
const int CHANNEL_RANGE[14] = { 1,5,6,15,16,25,26,31,32,37,38,50,51,60 };//numbers of channels

int getPriceChannel(int type) {

	return CHANNEL_CONTENT[type];

}
void	initChannel(Channel* pChannel, Channel* ChannelArr, int ChannelCount)
{
	printChannelRange(ChannelArr);
	pChannel->serialNum = getChannelSN(ChannelArr, ChannelCount);
	pChannel->type = getChannelType(pChannel->serialNum);
	pChannel->rating = enterRNumsToChannel();
}

int enterRNumsToChannel()
{

	return MIN_RATING + (rand() % (MAX_RATING - MIN_RATING + 1));

}

void printChannelRange(const Channel* ChannelArr)
{
	int len =sizeof(CHANNEL_RANGE) / sizeof(int);
	printf("\n");
	int j = 0;

		 for (int i = 0; i <= len - 2; i++)
		{
			printf("%d - %d is %s channels\n", CHANNEL_RANGE[i], CHANNEL_RANGE[i + 1], ChannelStr[j]);
			i++;
			j++;
		}
		 printf("\n");

}

eChannelType	getChannelType(int num) 
{
	int option = 0;
	int len = sizeof(CHANNEL_RANGE) / sizeof(int);
	int j = 0;
	for (int i = 0; i <= len - 2; i++)
	{
		if( num>=CHANNEL_RANGE[i] && num<=CHANNEL_RANGE[i + 1])
			return j;
		i++;
		j++;
	}
	return  eNofChannels;
}

int	getChannelSN(const Channel* ChannelArr, int ChannelCount) {
	int num;
	int unique = 0;
	do {
		printf("Enter Channel number - between %d to %d\n", MIN_SN, MAX_SN);
		scanf("%d", &num);
		if (num >= MIN_SN && num <= MAX_SN)
			unique = isSerialNumUnique(ChannelArr, ChannelCount, num);
	} while (!unique);
	return num;
}

int	isSerialNumUnique(const Channel* ChannelArr, int ChannelCount, int num) {
	for (int i = 0; i < ChannelCount; i++)
	{
		if (ChannelArr[i].serialNum == num)
			return 0;
	}
	return 1;
}

void	printChannel(const void* c) {
	Channel* pChannel = (Channel*)c;

	printf("~ Channel ~ number:%d, type: %s, rating: %d%%\n", pChannel->serialNum, ChannelStr[pChannel->type], pChannel->rating);
}














