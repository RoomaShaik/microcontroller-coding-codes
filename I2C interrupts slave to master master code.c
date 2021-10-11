/*
 * main.c
 *
 * Created: 10/2/2021 12:41:17 PM
 *  Author: ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <avr/interrupt.h>

#define FOSC 2000000 //ClockSpeed
#define BAUD 9600

void I2C_MasterInit(void)
{
	DDRE = 0xFF;
	sei();
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWIE);
}
ISR(TWI_vect)
{
	if((TWSR & 0xF8) == 0x08)
	{
		TWDR = 0x11;
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);
	}
	if((TWSR & 0xF8) == 0x40)
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);
	}
	if((TWSR & 0xF8) == 0x58)
	{
		PORTE = TWDR;
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO)|(1<<TWIE);
	}
}
int main(void)
{
	I2C_MasterInit();
	while(1);
}