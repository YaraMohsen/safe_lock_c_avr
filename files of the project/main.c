/*
 * main.c

 *
 *  Created on: Jan 20, 2021
 *      Author: SOUQ COMPUTER
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_Reg.h"
#include "DIO.h"
#include"key_pad.h"
#include"LCD.h"
#include"lock.h"

int main(){
DIO_Init();
LCD_Init();
	while(1){

		safe_lock();

	}
	return 0;
}
