#include"header.h"
#include<stdio.h>
char *text = "000\0";     // '\0' is the string terminator
short int i=0;
int main()
{
	uart0_init(9600);
	i2c_init();
	delay_ms(100);
	
	oled_init();
  uart_strings("init oled complte\r\n");
	delay_ms(10);
	
	oled_clear();
	uart_strings("oled clear\r\n");	
	oled_gotoxy2(3,1);
  oled_printxy2("MENU");
	oled_gotoxy2(1,2);
  oled_printxy2("-------");
	oled_gotoxy2(3,3);
  oled_printxy2("Time");
	oled_gotoxy2(3,4);
  oled_printxy2("Date");
	oled_gotoxy2(3,5);
  oled_printxy2("Alarm");
	oled_gotoxy2(3,6);
  oled_printxy2("Timer");
	oled_gotoxy2(3,7);
  oled_printxy2("Reminde");
	oled_gotoxy2(3,8);
  oled_printxy2("Stop");
delay_ms(500);

	
//  oled_setXY(0x31, 0x7F, 0x02, 0x04);
//  oled_print("Time");
//	oled_setXY(0x31, 0x7F, 0x03, 0x05);
//  oled_print("Date");
//	oled_setXY(0x31, 0x7F, 0x04, 0x06);
//  oled_print("Alarm");
//	oled_setXY(0x31, 0x7F, 0x05, 0x07);
//  oled_print("Timer");
//	oled_setXY(0x31, 0x7F, 0x06, 0x08);
//  oled_print("Reminder");
//	oled_setXY(0x31, 0x7F, 0x07, 0x09);
//  oled_print("Exit");
	uart_strings("complete\r\n");
	

	
}
