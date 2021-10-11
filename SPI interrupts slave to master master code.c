/*
 * main.c
 *
 * Created: 9/25/2021 3:59:21 PM
 *  Author: ROOMA
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000L

#define FOSC 2000000 //Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void SPI_MasterInit(void)
{
	DDRE = 0xFF;
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<SPR0);
	SPSR = (1<<SPIF);
	sei();
}
ISR(SPI_STC_vect)
{
	char data = SPDR;
	PORTE = data;
}
int main(void)
{
	SPI_MasterInit();
	SPDR = 'S';
	while(1);
}

