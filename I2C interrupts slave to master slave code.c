/*
 * main.c
 *
 * Created: 10/2/2021 11:28:51 AM
 *  Author: ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <avr/interrupt.h>

#define FOSC 2000000 //Clock Speed
#define BAUD 9600

void I2C_SlaveInit(void)
{
	TWAR = 0x11;
	sei();
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
}
ISR(TWI_vect)
{
	if((TWSR & 0xF8) == 0xA8)
	{
		TWDR = 'R';	
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);
	}
}
int main(void)
{
	I2C_SlaveInit();
	while(1);
}