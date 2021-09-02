/*
 * I2C slave to master master code.c
 *
 * Created: 9/2/2021 9:43:45 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L

#define FOSC 2000000 //ClockSpeed
#define BAUD 9600

void I2C_MasterInit(void)
{
	DDRE = 0xFF;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
void I2C_MasterTransmitaddress(char data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
char I2C_MasterReceive()
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}
void I2C_MasterStop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
int main(void)
{
	I2C_MasterInit();
	I2C_MasterTransmitaddress(0x11);
	char data = I2C_MasterReceive(' ');
	PORTE = data;
	I2C_MasterStop();
}

