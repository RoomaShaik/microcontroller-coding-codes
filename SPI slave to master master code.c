/*
 * SPI slave to master master code.c
 *
 * Created: 9/2/2021 9:38:36 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L

#define FOSC 2000000 //Clock Speed
#define BAUD 9600

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
char SPI_MasterReceive(char data)
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
	SPI_MasterInit();
	char data = SPI_MasterReceive(' ');
	PORTD = data;
}



