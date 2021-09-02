/*
 * spi master to slave master code 2.c
 *
 * Created: 9/2/2021 9:05:42 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <string.h>

#define FOSC 2000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
char SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
int main(void)
{
	SPI_MasterInit();
	const char *string = "ROOMA";
	int y=0;
	while(y< strlen(string))
	{
		SPI_MasterTransmit(string[y]);
		_delay_ms(100);
		y++;
	}
}



