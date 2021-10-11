/*
 * UART interrupts2.c
 *
 * Created: 9/22/2021 9:00:30 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

#define FOSC 2000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void UART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<TXCIE0)|(1<<UDRIE0)|(1<<RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (3<<UCSZ00)|(2<<UPM00)|(0<<UMSEL0)|(0<<USBS0);
	sei();
	UCSR0A = (1<<TXC0)|(1<<RXC0);
}
ISR(USART0_UDRE_vect)
{
	UDR0 = 'R';
}
ISR(USART0_RX_vect)
{
	char data = UDR0;
	PORTB = data;
}
int main( void )
{
	UART_Init ( MYUBRR );
}

