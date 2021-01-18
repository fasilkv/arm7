#include"header.h"

#define led 1

int main()
{
	
	gpio_dir(PORT0,led,OUTPUT);
	uart0_init(9600);
	while(1)
	{
		gpio_write(PORT0,led,SET);
		uart_strings("Led on\r\n");
		delay_ms(100);
		gpio_write(PORT0,led,CLEAR);
		uart_strings("Led off\r\n");
		delay_ms(100);
	}

}
