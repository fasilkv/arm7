#include<stdbool.h>

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

void i2c_init(void);
bool I2C0WaitForSI(void); //Wait till I2C0 block sets SI

void i2c_start(void);

void i2c_stop(void);

void i2c_write(char data);

uint8_t i2c_read(bool isLast);

void i2c_write_frame(uint8_t sa,uint8_t mr,uint8_t data);

uint8_t i2c_read_frame(uint8_t sa,uint8_t mr);

