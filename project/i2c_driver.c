#include<lpc214x.h>
#include"header.h"

#define I2EN (1<<6) //Enable/Disable bit
#define STA  (1<<5) //Start Set/Clear bit
#define STO  (1<<4) //Stop bit
#define SI   (1<<3) //Serial Interrupt Flag Clear bit
#define AA   (1<<2) //Assert Acknowledge Set/Clear bit

void waitforsi (void)
{
	int timeout = 0;
	while (!(I2C0CONSET & SI))  //while interrupt in not set /wait till SI goes 1
	{
		timeout++;
		if (timeout > 10000) break; //In case we have some error on bus
	}		
}

void i2c_init(void)
{
	PINSEL0 |= (1<<4)|(1<<6);  // for i2c line
	I2C0SCLH = 75;  // 15MHz/150 = 100000 speed i2c
	I2C0SCLL = 75;
	I2C0CONCLR = STA|STO|AA|SI;  // clear all bits
	I2C0CONSET = I2EN;  // enable bit set

}


void i2c_start(void)
{
	I2C0CONSET = STA;  // set start bit
	waitforsi();  //wait for interrupt to set it will transmit previous condition
	
	//I2C1CONCLR = 0x28; 			//clear i2c flag start bit
}

void i2c_stop(void)
{
	I2C0CONCLR = AA|SI;  // clear ack and interrupt
	I2C0CONSET = STO;  // send stop
}

void i2c_write(char data)
{
	I2C0DAT = data;  // load data
	I2C0CONCLR = SI|STA|AA;  //clear interrupt, start, ack
	waitforsi ();  // wait for condition  to transmit
}

uint8_t i2c_read_ack(void)
{
	I2C0CONSET = 0xAA;							//enable i2c with ack
	I2C0CONCLR = SI;							// clear flag and ack bit;
	waitforsi ();  // wait for condition  to transmit	
	return I2C0DAT;
}

uint8_t i2c_read_nack(void)
{
	//I2C0CONSET = 0xAA;							//enable i2c with ack
	I2C0CONCLR = 0xAA;
	I2C0CONCLR = SI;							// clear flag and ack bit;
	waitforsi ();  // wait for condition  to transmit	
	return I2C0DAT;
}

void i2c_write_frame(uint8_t sa,uint8_t mr,uint8_t data)
{
	i2c_start();
	i2c_write(sa);
	i2c_write(mr);
	i2c_write(data);
	i2c_stop();
}


uint8_t i2c_read_frame(uint8_t sa,uint8_t mr)
{
	uint8_t temp;
	i2c_start();
	i2c_write(sa);
	i2c_write(mr);
	i2c_start();
	i2c_write(sa|1);
	temp = i2c_read_nack();
	i2c_stop();
	return temp;
}

