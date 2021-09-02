/*
 * I2C master to slave slave code.c
 *
 * Created: 9/2/2021 10:12:29 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L

#define FOSC 2000000
#define BAUD 9600

void Slave_Init(void)
{
	DDRE = 0xFF;
	TWAR = 0x10;
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}
char Slave_Receive()
{
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}
int main(void)
{
	Slave_Init();
	char data = Slave_Receive();
	PORTE = data;
}

