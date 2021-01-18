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

extern uint8_t ok_but,scroll_but,index_v;
extern uint8_t flag,parent,child;
extern uint8_t t_hr,t_min,t_sec;
extern struct RTCCLK rtc;

void oled_home_win(void)
{
	char s[25];
	uart_strings("\r\n");
	uart_strings("\r\n");
	while(ok_but==0){
	sprintf(s,"     %02d:%02d:%02d \r\n",HOUR,MIN,SEC);
	uart_strings(s);
	uart_strings("    01-01-2021    \r\n");
	uart_strings("       MON        \r\n");
	uart_strings("\r\n \r\n");
	}
	}

void oled_menu_win(void)
{
	uint8_t temp = index_v;
	if(ok_but==1)
	{
		child=index_v;
		flag=1;
		index_v=1;
		ok_but=0;
		return;
	}
	
	uart_strings("oled menu window:\r\n");
	uart_strings("-----------------\r\n");
	uart_strings("       TIME      \r\n");
	uart_strings("       DATE      \r\n");
	uart_strings("       TIMER     \r\n");
	uart_strings("       ALARM     \r\n");
	uart_strings("       REMIDER   \r\n");
	uart_strings("       Back      \r\n");
	uart_strings("\r\n \r\n");
	
	switch(index_v)
	{
		case 1:uart_strings("TIME      \r\n");break;
		case 2:uart_strings("date      \r\n");break;
		case 3:uart_strings("timer      \r\n");break;
		case 4:uart_strings("alarm     \r\n");break;
		case 5:uart_strings("reminder     \r\n");break;
		case 6:uart_strings("back      \r\n");
					break;
	}

}

void oled_time_win(void)
{
	if(ok_but==1 && index_v==1) 
		{	
			ok_but=0;
			while(ok_but==0)
				{
				if(scroll_but==1)
					{
						scroll_but=0;
						rtc.hour++;
						if(rtc.hour>12)
							rtc.hour=1;
					}
				uart_integer(rtc.hour);
				}
			uart_strings("hr set by : ");
			uart_integer(rtc.hour);
			index_v = 1;
			ok_but=0;
		}

	if(ok_but==1 && index_v==2) 
		{
			ok_but=0;
			while(ok_but==0)
				{
					if(scroll_but==1)
						{
						scroll_but=0;
						rtc.min++;
						if(rtc.min>59)
						rtc.min =0;
						}
					uart_integer(rtc.min);
				}
				uart_strings("min set by : ");
				uart_integer(rtc.min);
				index_v = 1;
				ok_but=0;
			}
	if(ok_but==1 && index_v==3) 
		{	
			ok_but=0;
			while(ok_but==0)
				{
					if(scroll_but==1)
					{
						scroll_but=0;
						rtc.sec++;
						if(rtc.sec>59)
						rtc.sec	=10;
					}
					uart_integer(rtc.sec);
				}
			uart_strings("sec set by : ");
			uart_integer(rtc.sec);
			index_v = 1;
			ok_but=0;
		}
			
	if(ok_but==1 && index_v==4) 
		{
			parent=1;
			child = 0;
			index_v=1;
			ok_but=0;
			flag=1;
			return;
		}
	if(ok_but==1 && index_v==5) 
		{
			parent=0;
			child = 0;
			index_v=1;
			ok_but=0;
			flag=1;
			return;
		}
	
	RTC_SetDateTime(&rtc);
	
	uart_strings("oled time window:\r\n");
	uart_strings("-----------------\r\n");
	uart_strings("\r\n \r\n");
	uart_strings("       HOUR     : ");
	uart_integer(rtc.hour);
	uart_strings("       MINITE   : ");
	uart_integer(rtc.min);
	uart_strings("       SECONDS  : ");
	uart_integer(rtc.sec);
	uart_strings("       back      \r\n");
	uart_strings("       exits    \r\n");
	uart_strings("\r\n \r\n");
	switch(index_v)
		{
			case 1:uart_strings("hour      \r\n");break;
			case 2:uart_strings("mini      \r\n");break;
			case 3:uart_strings("second      \r\n");break;
			case 4:uart_strings("back      \r\n");break;
			case 5:uart_strings("exit      \r\n");break;
		}

	}

void oled_date_win(void)
{
	if(ok_but==1 && index_v==1) 
		{	
			ok_but=0;
			while(ok_but==0)
				{
				if(scroll_but==1)
					{
						scroll_but=0;
						rtc.date++;
						if(rtc.date>31)
							rtc.date=1;
					}
				uart_integer(rtc.date);
				}
			uart_strings("date set by : ");
			uart_integer(rtc.date);
			index_v = 1;
			ok_but=0;
		}

	if(ok_but==1 && index_v==2) 
		{
			ok_but=0;
			while(ok_but==0)
				{
					if(scroll_but==1)
						{
						scroll_but=0;
						rtc.month++;
						if(rtc.month>12)
						rtc.month =0;
						}
					uart_integer(rtc.month);
				}
				uart_strings("month set by : ");
				uart_integer(rtc.month);
				index_v = 1;
				ok_but=0;
			}
	if(ok_but==1 && index_v==3) 
		{	
			ok_but=0;
			while(ok_but==0)
				{
					if(scroll_but==1)
					{
						scroll_but=0;
						rtc.year++;
						if(rtc.year>2030)
						rtc.year	=2000;
					}
					uart_integer(rtc.year);
				}
			uart_strings("year set by : ");
			uart_integer(rtc.year);
			index_v = 1;
			ok_but=0;
		}
			
	if(ok_but==1 && index_v==4) 
		{
			parent=1;
			child = 0;
			index_v=2;
			ok_but=0;
			flag=1;
			return;
		}
	if(ok_but==1 && index_v==5) 
		{
			parent=0;
			child = 0;
			index_v=1;
			ok_but=0;
			flag=1;
			return;
		}
	
	RTC_SetDateTime(&rtc);
	
	uart_strings("oled date window:\r\n");
	uart_strings("-----------------\r\n");
	uart_strings("\r\n \r\n");
	uart_strings("       DAY     : ");
	uart_integer(rtc.date);
	uart_strings("       MONTH   : ");
	uart_integer(rtc.month);
	uart_strings("       YEAR  : ");
	uart_integer(rtc.year);
	uart_strings("       back      \r\n");
	uart_strings("       exits    \r\n");
	uart_strings("\r\n \r\n");
	switch(index_v)
		{
			case 1:uart_strings("day      \r\n");break;
			case 2:uart_strings("month      \r\n");break;
			case 3:uart_strings("year      \r\n");break;
			case 4:uart_strings("back      \r\n");break;
			case 5:uart_strings("exit      \r\n");break;
		}

}

void oled_timer_win(void)
{

}

void oled_alarm_win(void)
{

}

void oled_remider_win(void)
{

}

