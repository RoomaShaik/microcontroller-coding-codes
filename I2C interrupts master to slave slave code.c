/*
 * main.c
 *
 * Created: 9/27/2021 1:47:12 PM
 *  Author: ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <avr/interrupt.h>

#define FOSC 2000000
#define BAUD 9600

void Slave_Init(void)
{
	DDRE = 0xFF;
	TWAR = 0x10;
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
	sei();
}
ISR(TWI_vect)
{
	if((TWSR & 0xF8) == 0x60)
	{
		TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
	}
	if((TWSR & 0xF8) == 0x80)
	{
		TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
		PORTE = TWDR;
	}
}
int main(void)
{
	Slave_Init();
	while(1);
}