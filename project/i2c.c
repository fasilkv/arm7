#include<lpc214x.h>
#include"i2c.h"
#include<stdbool.h>

#define I2EN (1<<6) //Enable/Disable bit
#define STA  (1<<5) //Start Set/Clear bit
#define STO  (1<<4) //Stop bit
#define SI   (1<<3) //Serial Interrupt Flag Clear bit
#define AA   (1<<2) //Assert Acknowledge Set/Clear bit

void i2c_init(void)
{
	PINSEL0 |= (0<<7)|(1<<6)|(0<<5)|(1<<4); //Select SCL0(P0.2) and SDA0(P0.3)
	I2C0SCLL = 300;
	I2C0SCLH = 300; //I2C0 @ 100Khz, given PCLK @ 60Mhz
	I2C0CONCLR = STA | STO | SI | AA; //Clear these bits
	I2C0CONSET = I2EN; //Enable I2C0
	//After this we are ready to communicate with any other device connected to the same bus.
}


bool I2C0WaitForSI(void) //Wait till I2C0 block sets SI
{
	int timeout = 0;
	while ( !(I2C0CONSET & SI) ) //Wait till SI bit is set. This is important!
	{
		timeout++;
		if (timeout > 10000) return false; //In case we have some error on bus
	}
 return true; //SI has been set
}

void i2c_start(void)
{
	I2C0CONCLR = STA | STO | SI | AA; //Clear everything
	I2C0CONSET = STA; //Set start bit to send a start condition
	I2C0WaitForSI(); //Wait till the SI bit is set}
}

void i2c_stop(void)
{
	int timeout = 0;
	I2C0CONSET = STO ; //Set stop bit to send a stop condition
	I2C0CONCLR = SI;
	while (I2C0CONSET & STO) //Wait till STOP is send. This is important!
	{
		timeout++;
		if (timeout > 10000) //In case we have some error on bus
		{
	//		printf("STOP timeout!\n");
			return;
		}
	}
}


void i2c_write(char data)
{
 	I2C0DAT = data;
	I2C0CONCLR = STA | STO | SI; //Clear These to TX data
	I2C0WaitForSI(); //wait till TX is finished
}

uint8_t i2c_read(bool isLast)
{
	if(isLast) I2C0CONCLR = AA; //Send NACK to stop; I2C block will send a STOP automatically, so no need to send STOP thereafter.
	else 	     I2C0CONSET = AA; //Send ACK to continue
	I2C0CONCLR = SI; //Clear SI to Start RX
	I2C0WaitForSI(); //wait till RX is finished
	return I2C0DAT;
}

void i2c_write_frame(uint8_t sa,uint8_t mr,uint8_t data)
{
	i2c_start();
	uart_strings("start\r\n");
	i2c_write(sa);
	uart_strings("write sa\r\n");
	i2c_write(mr);
	uart_strings("write mr\r\n");
	i2c_write(data);
	uart_strings("wr data\r\n");
	i2c_stop();
	uart_strings("stop\r\n");
}

uint8_t i2c_read_frame(uint8_t sa,uint8_t mr)
{
	uint8_t temp;
	i2c_start();
	i2c_write(sa);
	i2c_write(mr);
	i2c_start();
	i2c_write(sa|1);
	temp = i2c_read(false);
	i2c_stop();
	return temp;
}

