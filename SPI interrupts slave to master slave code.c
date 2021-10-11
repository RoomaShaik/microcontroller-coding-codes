/*
 * main.c
 *
 * Created: 9/25/2021 4:15:43 PM
 *  Author: ROOMA
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000L

#define FOSC 2000000 //Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void SPI_SlaveInit(void)
{
	DDRE = 0xFF;
	/* Set MISO output, all others input */
	DDRB = (1<<DDB3);
	sei();
	/* Enable SPI */
	SPCR = (1<<SPIE)|(1<<SPE);
	SPSR = (1<<SPIF);
}
ISR(SPI_STC_vect)
{
	PORTE = SPDR;
}
int main(void)
{
	SPI_SlaveInit();
	SPDR = 'R';
	while(1);
}

