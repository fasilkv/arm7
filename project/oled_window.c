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
						t_hr++;
						if(t_hr>12)
						t_hr =1;
					}
					uart_integer(t_hr);
				}
				uart_strings("hr set by : ");
				uart_integer(t_hr);
				index_v = 1;
				ok_but=0;
				flag=1;
				//return;
			}
			
			if(ok_but==1 && index_v==2) 
			{	
				ok_but=0;
				while(ok_but==0)
				{
					if(scroll_but==1)
					{
						scroll_but=0;
						t_min++;
						if(t_min>59)
						t_min =0;
					}
					uart_integer(t_min);
				}
				uart_strings("min set by : ");
				uart_integer(t_min);
				index_v = 1;
				ok_but=0;
				flag=0;
				//return;
			}
					if(ok_but==1 && index_v==1) 
			{	
				ok_but=0;
				while(ok_but==0)
				{
					if(scroll_but==1)
					{
						scroll_but=0;
						t_sec++;
						if(t_sec>59)
						t_sec	=10;
					}
					uart_integer(t_sec);
				}
				uart_strings("sec set by : ");
				uart_integer(t_sec);
				index_v = 1;
				ok_but=0;
				flag=0;
				//return;
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

	uart_strings("oled time window:\r\n");
	uart_strings("-----------------\r\n");
	uart_strings("\r\n \r\n");
	uart_strings("       HOUR     : ");
	uart_integer(t_hr);
	uart_strings("       MINITE   : ");
	uart_integer(t_min);
	uart_strings("       SECONDS  : ");
	uart_integer(t_sec);
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
	uart_strings("oled date window:\r\n");
	uart_strings("-----------------\r\n");
	uart_strings("\r\n \r\n");
	uart_strings("       DATE      \r\n");
	uart_strings("\r\n \r\n");
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

