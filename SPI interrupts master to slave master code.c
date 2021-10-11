/*
 * main.c
 *
 * Created: 9/22/2021 11:36:04 PM
 *  Author: ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

#define FOSC 2000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<SPR0);
	SPSR = (1<<SPIF);
	sei();
}
int main(void)
{
	SPI_MasterInit();
	SPDR = 'R';
	while(1);
}