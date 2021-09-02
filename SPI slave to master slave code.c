/*
 * SPI slave to master slave code.c
 *
 * Created: 9/2/2021 9:39:51 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L

#define FOSC 2000000 //Clock Speed
#define BAUD 9600

void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDRB = (1<<DDB3);
	/* Enable SPI */
	SPCR = (1<<SPE);
}
void SPI_SlaveTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}
int main(void)
{
	SPI_SlaveInit();
	SPI_SlaveTransmit('R');
}

