/*
 * UART protocol.c
 *
 * Created: 9/2/2021 7:06:47 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <string.h>

#define FOSC 2000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void UART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (3<<UCSZ00)|(2<<UPM00)|(0<<UMSEL0)|(0<<USBS0);
}
void UART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
unsigned char UART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR0;
}
int main( void )
{
	UART_Init ( MYUBRR );
    const char *string = "ROOMA";
	int y = 0;
	while (y < strlen(string))
	{
		UART_Transmit(string[y]);
		y++;
	}
}

