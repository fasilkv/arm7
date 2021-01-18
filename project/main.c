#include"header.h"

#ifndef RTCLK
#define RTCLK
struct RTCCLK{
  unsigned int sec;
  unsigned int min;
  unsigned int hour;
  unsigned int weekDay;
  unsigned int date;
  unsigned int month;
  unsigned short int year;  
};
#endif

#define timeout 10

void rtc_update();

uint8_t parent = 0,child = 0;
uint8_t flag = 0;
uint8_t t_hr=12,t_min=0,t_sec=0;
uint8_t timeout_clk = 0;

struct RTCCLK rtc = {10,30,12,6,1,1,2000};
char time_buf[15];
char date_buf[15];
char week[7][10] = {"SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATDAY"}; 


int main()
{
	//////initialisation/////////
	uart0_init(9600);             //uart
	config_eint();								// ext0 and ext1
	config_vic();
	
	RTC_Init();
	RTC_SetDateTime(&rtc);
	
	i2c_init();
	delay_ms(100);
	oled_init();
  uart_strings("init oled complte\r\n");
	delay_ms(10);
//	oled_clear();
	while(1)
	{
		if(flag == 1)
		{				
			if(parent == 1 && child == 0)
			{
				///menu window
				oled_menu_win();
		
			}
			else if(parent == 1 && child == 1)
			{
				///time window
				oled_time_win();
			}
			else if(parent == 1 && child == 2)
			{
				///date window
				oled_date_win();
				
			}
			else if(parent == 1 && child == 3)
			{
				//timer
			}
			else if(parent == 1 && child == 4)
			{
				//alarm
			}
			else if(parent == 1 && child == 5)
			{
				//remider
			}
			
			timeout_clk++;
			if(timeout_clk>timeout)
			{
				parent=0;
				child = 0;
				flag=0;
			}

		}
		else
		{
			rtc_update();
		}
		delay_ms(10);
		
	}

}

void rtc_update()
{
		RTC_GetDateTime(&rtc);
		
		sprintf(time_buf,"%02d:%02d:%02d\r\n",rtc.hour,rtc.min,rtc.sec);
//		oled_gotoxy2(0,1);
//		oled_printxy2("             ");
//		oled_gotoxy2(3,1);
//		oled_printxy2(time_buf);
		uart_strings(time_buf);
		
		sprintf(date_buf,"%02d:%02d:%04d\r\n",rtc.date,rtc.month,rtc.year);
//		oled_gotoxy2(3,2);
//		oled_printxy2(date_buf);
		uart_strings(date_buf);
		
		uart_strings(week[rtc.weekDay]);
//		oled_gotoxy2(3,3);
//		oled_printxy2(week[rtc.weekDay]);
		uart_strings("\r\n");

}



//////////////////////////////////////////////

//		if(flag == 1)
//		{
//			flag = 0;
//			if(parent == 0 && child == 0)
//			{
//				oled_home_win();
//			}
//			else if(parent == 1 && child == 0)
//			{
//				///menu window
//				oled_menu_win();
//		
//			}
//			else if(parent == 1 && child == 1)
//			{
//				///time window
//				oled_time_win();
//			}
//			else if(parent == 1 && child == 2)
//			{
//				///date window
//				oled_date_win();
//				
//			}
//			else if(parent == 1 && child == 3)
//			{
//				//timer
//			}
//			else if(parent == 1 && child == 4)
//			{
//				//alarm
//			}
//			else if(parent == 1 && child == 5)
//			{
//				//remider
//			}
//			else if(parent == 1 && child == 6)
//			{
//				parent=0;
//				child =0;
//				flag=1;
//			}
//		}
//		