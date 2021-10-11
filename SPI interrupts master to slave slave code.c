/*
 * main.c
 *
 * Created: 9/22/2021 11:50:34 PM
 *  Author: ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <avr/interrupt.h>

#define FOSC 2000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void SPI_SlaveInit(void)
{
	DDRF = 0xFF;
	/* Set MISO output, all others input */
	DDRB = (1<<DDB3);
	/* Enable SPI */
	SPCR = (1<<SPIE)|(1<<SPE);
	SPSR = (1<<SPIF);
	sei();
}
ISR(SPI_STC_vect)
{
	char data = SPDR;
	PORTF = data;
}
int main(void)
{
	SPI_SlaveInit();
	while(1);
}