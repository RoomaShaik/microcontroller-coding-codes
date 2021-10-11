/*
 * main.c
 *
 * Created: 9/25/2021 5:07:57 PM
 *  Author: ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <avr/interrupt.h>

#define FOSC 2000000 //ClockSpeed
#define BAUD 9600

void I2C_MasterInit(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWIE);
	sei();
}

ISR(TWI_vect)
{
	if((TWSR & 0xF8) == 0x08)
	{
		TWDR = 0x10;
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);
	} 	
	if((TWSR & 0xF8) == 0x18) 	
	{
		TWDR = 'R';
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE); 	
	}
}

int main(void)
{
	I2C_MasterInit();
	while(1);
}
