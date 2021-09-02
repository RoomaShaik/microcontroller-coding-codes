/*
 * SPI master to slave slave code.c
 *
 * Created: 9/2/2021 8:45:29 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>

#define FOSC 2000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDRB = (1<<DDB3);
	/* Enable SPI */
	SPCR = (1<<SPE);
}
char SPI_SlaveReceive(char data)
{
	SPDR = data;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return data register */
	return SPDR;
}
int main(void)
{
	SPI_SlaveInit();
	while(1)
	{
	    char data = SPI_SlaveReceive(' ');
	    PORTD = data;
		_delay_ms(100);
	}
}

