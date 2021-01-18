
#include<stdio.h>
#include"lpc214x.h"
#include<stdio.h>

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short int uint16_t;
typedef signed short int int16_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned long int uint64_t;
typedef signed long int int64_t;
typedef float f_32;

#define PORT0 0
#define PORT1 1
#define OUTPUT 1
#define INPUT 0
#define SET 1
#define CLEAR 0

void delay_sec(uint32_t sec);
void delay_ms(uint32_t ms);

void gpio_dir(uint8_t port,uint8_t pin,uint8_t dir);
int8_t gpio_read(uint8_t port,uint8_t pin);
void gpio_write(uint8_t port,uint8_t pin,uint8_t val);

void uart0_init(uint32_t baud);
void uart0_tx(uint8_t byte);
void uart_strings(char *ptr);
void uart_integer(uint32_t num);

void i2c_init(void);
void waitforsi (void); //Wait till I2C0 block sets SI
void i2c_start(void);
void i2c_stop(void);
void i2c_write(char data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
void i2c_write_frame(uint8_t sa,uint8_t mr,uint8_t data);
uint8_t i2c_read_frame(uint8_t sa,uint8_t mr);


void oled_Command(char DATA); /* Function for sending command to oled */
void oled_init(void); /* Function for initializing oled */
void oled_print(char *DATA); /* Function for sending data to oled */
void oled_setXY(char col_start, char col_end, char page_start, char page_end); /* Function for setting cursor for writing data */  
void oled_clear(void); /* Function for clearing oled */   

void oled_printxy2(char *s);
void oled_putxy2(char c);
void oled_gotoxy2(uint8_t x, uint8_t y);

extern void cofig_vic(void);
extern void config_eint0(void);

#ifndef RTCLK
#define RTCLK
struct RTCCLK
{
  unsigned int sec;
  unsigned int min;
  unsigned int hour;
  unsigned int weekDay;
  unsigned int date;
  unsigned int month;
  unsigned short int year;  
};

#endif

extern void RTC_Init();
extern void RTC_SetDateTime(struct RTCCLK *rtc);
void RTC_GetDateTime(struct RTCCLK *rtc);

