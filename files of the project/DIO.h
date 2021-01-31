/*
 * DIO.h
 *
 *  Created on: Dec 12, 2020
 *      Author: SOUQ COMPUTER
 */

#ifndef DIO_H_
#define DIO_H_


typedef enum{

	portA0=0,
	portA1,
	portA2,
	portA3,
	portA4,
	portA5,
	portA6,
	portA7,

	portB0,
	portB1,
	portB2,
	portB3,
	portB4,
	portB5,
	portB6,
	portB7,

	portC0,
	portC1,
	portC2,
	portC3,
	portC4,
	portC5,
	portC6,
	portC7,

	portD0,
	portD1,
	portD2,
	portD3,
	portD4,
	portD5,
	portD6,
	portD7,
last_pin

}DIO_ENUM_CH;

typedef enum{
	LOW=0,
	HIGH=1,
	INVALID
}Volt_type;

typedef enum{
	PORTA=0,
	PORTB=1,
	PORTC,
	PORTD
}PORTS_type;

typedef enum{
	INPUT=0,
	OUTPUT=1,
	INPULLUP=2
}DDR_type;

/* array of size [32] contain the*/
extern  DDR_type DIO_Pinconfig[32];


extern void DIO_Init(void);
extern void DIO_WRITE_PORT(PORTS_type PORT ,uint8  value );
extern uint8 DIO_READ_PORT (PORTS_type PORT);
extern Volt_type DIO_Read_Channel(DIO_ENUM_CH pin);
extern void DIO_Write_Channel(DIO_ENUM_CH pin, Volt_type volt);

#endif /* DIO_H_ */
