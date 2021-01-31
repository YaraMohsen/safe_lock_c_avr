/*
 * DIO.c

 *
 *  Created on: Dec 12, 2020
 *      Author: Yara Mohsen
 */

#include"DIO_Reg.h"
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO.h"


/*************************************************************************
* DIO_Init :
* ********
* take void and return void
*
* use the DIO_Pinconfig[last_pin] array of DIO_Config.c .
* loop on the array to write on each DDR port - bit by bit- .
*
* REG[8]:is array of pointers contain the address of ports
* *************************************************************************/

void DIO_Init(void )
{
	DDR_type status;
	uint8 port;
	uint8 pin;

	uint8* REG[8]={0x3A,0x37,0x34,0x31,0x3B,0x38,0x35,0x32};

	DIO_ENUM_CH i;

	for(i=portA0;i<last_pin;i++)
		 {
		    status=DIO_Pinconfig[i];
		     port =i/8;
			 pin=i%8;

	switch(status)
	    {
		  case OUTPUT:
			  SET_BIT(*REG[port],pin);
			  break;
		  case INPULLUP:
			  CLEAR_BIT(*REG[port],pin);
			  SET_BIT(*REG[port+4],pin);
			  break;
		case INPUT:
			  CLEAR_BIT(*REG[port],pin);
			  CLEAR_BIT(*REG[port+4],pin);
			  break;
	    }
		 }
}


/*************************************************************************
* DIO_Write_Channel :
* *****************
*
* input : 1- pin number of type enum DIO_ENUM_CH on DIO.h file
*         2- the value of volt to be written in pin of type enum Volt_type
*         (HIGH or LOW) on DIO.h file.
*
* write a HIGH or LOW volt on a pin
*
*
* *************************************************************************/


void DIO_Write_Channel(DIO_ENUM_CH pin, Volt_type volt){
	switch (pin){
	   case portA0:
		   WRITE_BIT(PORTA_REG,0,volt);
		   break;
	   case portA1:
		   WRITE_BIT(PORTA_REG,1,volt);
		   break;
	   case portA2:
		   WRITE_BIT(PORTA_REG,2,volt);
		   break;
	   case portA3:
		   WRITE_BIT(PORTA_REG,3,volt);
		   break;
	   case portA4:
		   WRITE_BIT(PORTA_REG,4,volt);
		   break;
	   case portA5:
		   WRITE_BIT(PORTA_REG,5,volt);
		   break;
	   case portA6:
		   WRITE_BIT(PORTA_REG,6,volt);
		   break;
	   case portA7:
		   WRITE_BIT(PORTA_REG,7,volt);
		   break;

	   case portB0:
		   WRITE_BIT(PORTB_REG,0,volt);
		   break;
	   case portB1:
		   WRITE_BIT(PORTB_REG,1,volt);
		   break;
	   case portB2:
		   WRITE_BIT(PORTB_REG,2,volt);
		   break;
	   case portB3:
		   WRITE_BIT(PORTB_REG,3,volt);
		   break;
	   case portB4:
		   WRITE_BIT(PORTB_REG,4,volt);
		   break;
	   case portB5:
		   WRITE_BIT(PORTB_REG,5,volt);
		   break;
	   case portB6:
		   WRITE_BIT(PORTB_REG,6,volt);
		   break;
	   case portB7:
		   WRITE_BIT(PORTB_REG,7,volt);
		   break;

	   case portC0:
		   WRITE_BIT(PORTC_REG,0,volt);
		   break;
	   case portC1:
		   WRITE_BIT(PORTC_REG,1,volt);
		   break;
	   case portC2:
		   WRITE_BIT(PORTC_REG,2,volt);
		   break;
	   case portC3:
		   WRITE_BIT(PORTC_REG,3,volt);
		   break;
	   case portC4:
		   WRITE_BIT(PORTC_REG,4,volt);
		   break;
	   case portC5:
		   WRITE_BIT(PORTC_REG,5,volt);
		   break;
	   case portC6:
		   WRITE_BIT(PORTC_REG,6,volt);
		   break;
	   case portC7:
		   WRITE_BIT(PORTC_REG,7,volt);
		   break;

	   case portD0:
		   WRITE_BIT(PORTD_REG,0,volt);
		   break;
	   case portD1:
		   WRITE_BIT(PORTD_REG,1,volt);
		   break;
	   case portD2:
		   WRITE_BIT(PORTD_REG,2,volt);
		   break;
	   case portD3:
		   WRITE_BIT(PORTD_REG,3,volt);
		   break;
	   case portD4:
		   WRITE_BIT(PORTD_REG,4,volt);
		   break;
	   case portD5:
		   WRITE_BIT(PORTD_REG,5,volt);
		   break;
	   case portD6:
		   WRITE_BIT(PORTD_REG,6,volt);
		   break;
	   case portD7:
		   WRITE_BIT(PORTD_REG,7,volt);
		   break;

	   default :
		   break;
	}

}

/*************************************************************************
* DIO_Read_Channel :
* *****************
*
* input  :  pin number to read of type enum DIO_ENUM_CH.
*
* output :  the value of volt on pin of type enum Volt_type
*           (HIGH or LOW or invalid) on DIO.h file.
*
* *** invalid return is for debugging
* *************************************************************************/

Volt_type DIO_Read_Channel(DIO_ENUM_CH Pin){

	uint8 Pin_Num=Pin%8;
	PORTS_type Port=Pin/8;
	uint8 val;
		switch (Port)
		{
			case PORTA:
			val= GET_BIT(PINA_REG,Pin_Num);
			break;
			case PORTB:
				val= GET_BIT(PINB_REG,Pin_Num);
			break;
			case PORTC:
				val= GET_BIT(PINC_REG,Pin_Num);
			break;
			case PORTD:
				val= GET_BIT(PIND_REG,Pin_Num);
			break;
		}
		if(val==0){
			return LOW;
		}
		if(val==1){
			return HIGH;
		}
}


/*************************************************************************
* DIO_WRITE_PORT :
* ***************
*
* input : 1- port number of type enum PORTS_type on DIO.h file
*         2- uint8 value to be written in port.
*
* write on all port.
*
*
* *************************************************************************/


void DIO_WRITE_PORT(PORTS_type PORT ,uint8  value  ){

	switch(PORT){

			case PORTA:
			     PORTA_REG=value;
			     break;

			case PORTB:
				 PORTB_REG=value;
				 break;

			case PORTC:
				PORTC_REG=value;
				break;

			case PORTD:
				PORTD_REG=value;
				break;
	}
	}

/*************************************************************************
* DIO_Read_Channel :
* *****************
*
* input  :  port number to be read of type enum PORTS_type.
*
* output :  uint8 refer to the port value
*
* *************************************************************************/

uint8 DIO_READ_PORT (PORTS_type PORT){

	switch(PORT){

		case PORTA:
			return PORTA_REG;
			break;

		case PORTB:
			return PORTB_REG;
			break;

		case PORTC:
			return PORTC_REG;
			break;

		case PORTD:
			return PORTD_REG;
			break;

		default :break;
		}
return 1;

}


