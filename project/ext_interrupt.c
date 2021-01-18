#include<lpc214x.h>
#include"header.h"

uint8_t ok_but=0,scroll_but=0,index_v=1;
extern uint8_t flag,parent,child;
extern uint8_t timeout_clk;
void EINT0_HANDLER (void) __irq
{ /// ok_but
	timeout_clk = 0;
	
	flag=1;
	ok_but=1;
	EXTINT = 0x01;				//clear int flag
	VICVectAddr = 0x00;		//to finish isr
	if(parent==0)
	{
	index_v=1;
	parent++;
	child = 0;
	ok_but=0;
	}
}
void EINT1_HANDLER (void) __irq
{
	///scroll button
	timeout_clk = 0;

	flag = 1;
	scroll_but =1;
	index_v ++;
	EXTINT = 0x02;				//clear int flag
	VICVectAddr = 0x00;		//to finish isr
	if(index_v==7 && child == 0)
		index_v=1;
	else if(index_v==6 && child == 1)
		index_v=1;
}


void config_vic(void)
{
	VICIntSelect = 0x0; //eint0 is type of irq
	
	VICVectCntl0 = 14 | (1<<5); //int number for eint0 = 14	
	VICVectAddr0 = (uint32_t)EINT0_HANDLER;
	
	VICVectCntl1 = 15 | (1<<5); //int number for eint1 = 15 | enabel irq slot 
	VICVectAddr1 = (uint32_t)EINT1_HANDLER;
	
	VICIntEnable = (1<<14) | (1<<15) ; //enable eint0 and eint1
}

void config_eint(void)
{
	PINSEL1 |= 0x01; //P0.16 eint0
	EXTMODE = 0x01;
	
	PINSEL0 |= (1<<29); //P0.14 eint1
	EXTMODE |= 0x02;
	
	
	EXTPOLAR = 0x00;
}

