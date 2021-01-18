#include<lpc214x.h>
#include"header.h"

void gpio_dir(uint8_t port,uint8_t pin,uint8_t dir)
{

switch(port)
{
	case PORT0:
						if(dir== OUTPUT)
							IODIR0 |= (1<<pin);
						else
							IODIR0 &= ~(1<<pin);
						break;
	case PORT1:
						if(dir== OUTPUT)
							IODIR1 |= (1<<pin);
						else
							IODIR1 &= ~(1<<pin);
						break;
}
}

void gpio_write(uint8_t port,uint8_t pin,uint8_t val)
{

switch(port)
{
	case PORT0:
						if(val== 1)
							IOSET0 |= (1<<pin);
						else
							IOCLR0 |= (1<<pin);
						break;
	case PORT1:
						if(val== 1)
							IOSET1 |= (1<<pin);
						else
							IOCLR1 |= (1<<pin);
						break;
}
}

int8_t gpio_read(uint8_t port,uint8_t pin)
{
uint8_t status;
if(port>1)
{
	return -1;
}
if(pin>31)
{
	return -1;
}

switch(port)
{
	case PORT0:
		status = ((IOPIN0>>pin)&1)?1:0;
		break;
	case PORT1:
		status = ((IOPIN1>>pin)&1)?1:0;
		break;
}
return status;
}


