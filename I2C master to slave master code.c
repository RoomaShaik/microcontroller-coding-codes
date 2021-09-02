/*
 * I2C master to slave master code.c
 *
 * Created: 9/2/2021 10:10:55 PM
 * Author : ROOMA
 */ 

#include <avr/io.h>
#define F_CPU 16000000L

#define FOSC 2000000 //ClockSpeed
#define BAUD 9600

void I2C_MasterInit(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}
void I2C_MasterTransmitaddress(char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}
void I2C_MasterTransmit(char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
}
int main(void)
{
	I2C_MasterInit();
	I2C_MasterTransmitaddress(0x10);
	I2C_MasterTransmit('R');
}

