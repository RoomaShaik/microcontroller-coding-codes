/*
 * I2C slave to master slave code.c
 *
 * Created: 9/2/2021 9:45:06 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L

#define FOSC 2000000 //Clock Speed
#define BAUD 9600

void I2C_SlaveInit(void)
{
	TWAR = 0x11;
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
void I2C_SlaveTransmit(char data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
int main(void)
{
	I2C_SlaveInit();
	I2C_SlaveTransmit('R');
}

