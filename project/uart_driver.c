#include<lpc214x.h>
#include<stdio.h>
#include"header.h"

void uart0_init(uint32_t baud)
{
	PINSEL0 |= 0x05;         //P0.0,P0.1
	U0LCR = 0x83;
	switch(baud)
	{
		case 9600: 		U0DLL = 97;	break;
		case 57600: 	U0DLL = 16;	break;
		case 115200: 	U0DLL = 8;	break;
		case 921600: 	U0DLL = 1;	break;
	}
	U0LCR = 0x03;
}

void uart0_tx(uint8_t byte)
{
	U0THR = byte;
	while(((U0LSR>>5)&1)==0)
	{
	}
}
uint8_t uart0_rx(void)
{
	while((U0LSR&1)==0)
	{
	}
	return U0RBR;
}

void uart_strings(char *ptr)
{
	while(*ptr)
	{
		U0THR = *ptr;
		while(((U0LSR>>5)&1)==0)
		{
		}
		ptr++;
	}
}

void uart_integer(uint32_t num)
{
	char temp[20];
	sprintf(temp,"%d \r\n",num);
	uart_strings(temp);
}

