#ifndef __CHANNEL__
#define __CHANNEL__
#define MIN_SN 1
#define MAX_SN 60
#define MIN_RATING 1
#define MAX_RATING 99

//#define _CRT_SECURE_NO_WARNINGS 

typedef enum {
	eNews, eSport, eMovies, eKids, eScience, eEntertainment, eMusic, eNofChannels
} eChannelType;

static const char* ChannelStr[eNofChannels]
= { "News","Sport","Movies", "Kids","Science","Entertainment","Music" };


typedef struct
{
	int			serialNum;
	int            rating;
	eChannelType	 type;
}Channel;


void printChannelRange(const Channel* ChannelArr);
int getPriceChannel(int type);
void			initChannel(Channel* pChannel, Channel* ChannelArr, int ChannelCount);
eChannelType		getChannelType(int num);
int				getChannelSN(const Channel* ChannelArr, int Channel);
int				isSerialNumUnique(const Channel* ChannelArr, int ChannelCount, int num);
void	printChannel(const void* c);
int enterRNumsToChannel();


#endif