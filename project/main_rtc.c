#include"header.h"
#include <lpc214x.h>



#ifndef RTCLK
#define RTCLK
struct RTCCLK
{
  unsigned int sec;
  unsigned int min;
  unsigned int hour;
  unsigned int weekDay;
  unsigned int date;
  unsigned int month;
  unsigned short int year;  
};

#endif

struct RTCCLK rtc = {0,0,12,6,1,1,2000};
char s_buffer[25];


int main()
{

	uart0_init(9600);
	RTC_Init(&rtc);
//	 rtc.hour = 10; //  10:40:20 am
//    rtc.min =  40;
//    rtc.sec =  0;

//    rtc.date = 1; //1st Jan 2016
//    rtc.month = 1;
//    rtc.year = 2016;
//    rtc.weekDay = 5; // Friday: 5th day of week considering monday as first day.   

	
	RTC_SetDateTime(&rtc);
	delay_ms(100);
	
	while(1)
	{
	RTC_GetDateTime(&rtc);
	sprintf(s_buffer,"  %02d:%02d:%02d  \r\n",HOUR,MIN,SEC);
	uart_strings(s_buffer);
	delay_ms(100);
	}

}
