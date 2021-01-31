/*
 * DIO_Reg.h
 *
 *  Created on: Dec 11, 2020
 *      Author: SOUQ COMPUTER
 */

#ifndef DIO_REG_H_
#define DIO_REG_H_



#define INT0_vect			__vector_1
/* External Interrupt Request 1 */
#define INT1_vect			__vector_2

# define sei()  __asm__ __volatile__ ("sei" ::)


#include "STD_Types.h"
#define PINA_REG  *((volatile uint8 *)0x39)
#define DDRA_REG  *((volatile uint8 *)0x3A)
#define PORTA_REG  *((volatile uint8 *)0x3B)


#define PINB_REG  *((volatile uint8 *)0x36)
#define DDRB_REG  *((volatile uint8 *)0x37)
#define PORTB_REG  *((volatile uint8 *)0x38)


#define PINC_REG  *((volatile uint8 *)0x33)
#define DDRC_REG  *((volatile uint8 *)0x34)
#define PORTC_REG  *((volatile uint8 *)0x35)


#define PIND_REG  *((volatile uint8 *)0x30)
#define DDRD_REG  *((volatile uint8 *)0x31)
#define PORTD_REG  *((volatile uint8 *)0x32)


/*External Interrupt */
#define MCUCSR   (*(volatile unsigned char*)0x54)
#define ISC2 6

#define MCUCR   (*(volatile unsigned char*)0x55)
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define GICR     (*(volatile unsigned char*)0x5B)
#define INT1 7
#define INT0 6
#define INT2 5

#define GIFR    (*(volatile unsigned char*)0x5A)
#define INTF1 7
#define INTF0 6
#define INTF2 5


#define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)

#endif /* DIO_REG_H_ */
