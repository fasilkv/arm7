
#include <lpc214x.h>
//#include "header.h"

#define SBIT_CLKEN            0     
#define SBIT_CLKSRC           4     

typedef struct
{
  unsigned int sec;
  unsigned int min;
  unsigned int hour;
  unsigned int weekDay;
  unsigned int date;
  unsigned int month;
  unsigned short int year;  
}rtc_t;

void RTC_Init(void)
{
   
    CCR = ((1<<SBIT_CLKEN ) | (1<<SBIT_CLKSRC));
}

void RTC_SetDateTime(rtc_t *rtc)
{

     SEC   =  rtc->sec;       // Update sec value
     MIN   =  rtc->min;       // Update min value
     HOUR    =  rtc->hour;       // Update hour value 
     DOW    =  rtc->weekDay;   // Update day value 
     DOM    =  rtc->date;       // Update date value 
     MONTH =  rtc->month;       // Update month value
     YEAR  =  rtc->year;       // Update year value

}

void RTC_GetDateTime(rtc_t *rtc)
{
     rtc->sec     = SEC ;       // Read sec value
     rtc->min     = MIN ;       // Read min value
     rtc->hour    = HOUR;       // Read hour value 
     rtc->weekDay = DOW;      // Read day value 
     rtc->date    = DOM;       // Read date value 
     rtc->month   = MONTH;       // Read month value
     rtc->year    = YEAR;       // Read year value

}

