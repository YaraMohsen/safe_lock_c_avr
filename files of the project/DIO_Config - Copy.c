/*
 * DIO_Config.c
 *
 *  Created on: Dec 12, 2020
 *      Author: SOUQ COMPUTER
 */

#include "DIO_Reg.h"
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO.h"



DDR_type DIO_Pinconfig[32]={

INPUT,     //A0
OUTPUT,       // A1
OUTPUT,       //A2
OUTPUT,     //A3
OUTPUT,       //A4
OUTPUT,
OUTPUT,
OUTPUT,     //A7

INPULLUP,//B0
INPULLUP,//B1
INPULLUP,//B2
INPULLUP,//B3
INPULLUP,
INPULLUP,
INPULLUP,
INPULLUP,

OUTPUT,//C0
OUTPUT,
OUTPUT,
OUTPUT,
OUTPUT,
OUTPUT,
OUTPUT,
OUTPUT, //C7

OUTPUT,//D0
OUTPUT,
OUTPUT,
OUTPUT,
OUTPUT,
OUTPUT,
OUTPUT,
OUTPUT//D7




};
