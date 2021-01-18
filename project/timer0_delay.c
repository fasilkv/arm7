#include<lpc214x.h>
#include"header.h"

void delay_sec(uint32_t sec)
{
	T0PR = 15000000 -1;
	T0PC = T0TC = 0;
	T0TCR = 0x01;
	while(T0TC<sec)
	{
	}
	T0TCR = 0x00;
}

void delay_ms(uint32_t ms)
{
	T0PR = 15000 -1;
	T0PC = T0TC = 0;
	T0TCR = 0x01;
	while(T0TC<ms)
	{
	}
	T0TCR = 0x00;
}

