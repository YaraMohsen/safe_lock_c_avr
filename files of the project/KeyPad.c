/*

 * KeyPad.c
 *
 *  Created on: Dec 25, 2020
 *      Author: yara mohsen
 */

#include "DIO_Reg.h"
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "key_pad.h"

#include<util/delay.h>
#define F_CPU 8000000

	uint8 c=0,r=0;
	uint8 the_key='%';
KEYPAD_USE_TYPE keypad_use =ASCII_CODE_USE;

uint8 keypad_pins_colum[4]={//output
		portD2,
		portD3,
		portD4,
		portD5};

uint8 keypad_pins_row[4]= //inpull
{       portB4,
		portB5,
		portB6,
		portB7,};

uint8 key_seven_seg_display[4][4]={{0x07,0xff,0xef,0xf7},{0x66,0x6d,0x7d,0xfc},{0x06,0x5b,0x4f,0xb9},{0xf1,0x3f,0xf9,0xde}};

uint8 key_ascii[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'c','0','#','+'}};


uint8 pressed_key(void){

	    the_key='%';
	    DIO_Write_Channel(portD2,LOW);
		DIO_Write_Channel(portD3,HIGH);
		DIO_Write_Channel(portD4,HIGH);
		DIO_Write_Channel(portD5,HIGH);

			for(c=0;c<4;c++){

		DIO_Write_Channel(portD2+c,LOW);

		for(r=0;r<4;r++){

			if(!DIO_Read_Channel(portB4+r)){

				// to return ascii
                  if(keypad_use == ASCII_CODE_USE)
                  {
                	  the_key=key_ascii[r][c];
                  }
                  //to return the binary for seven seg in kit
                  else if(keypad_use == SEVEN_SEG_USE)

                  {
                	  the_key=key_seven_seg_display[r][c];
                  }



			   while(DIO_Read_Channel( portB4+r)==LOW);

				return the_key;
			}

			}
			DIO_Write_Channel(portD2+c,HIGH);


	}
	return the_key;
	}
