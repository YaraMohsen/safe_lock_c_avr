/*
 * LCD.c

 *
 *  Created on: Dec 25, 2020
 *      Author: yara
 */
#include"DIO_Reg.h"
#include "STD_Types.h"
#include "BIT_MATH.h"
#include"DIO.h"
#include"LCD.h"

#define F_CPU 8000000
#include<util/delay.h>



void LCD_Init(void)
{

	_delay_ms(50);
		LCD_WriteCommand(0x02);
		_delay_ms(1);
		LCD_WriteCommand(0x28);
		_delay_ms(1);
		LCD_WriteCommand(0x01);
		_delay_ms(3);
		LCD_WriteCommand(0x0C);
		_delay_ms(1);
		LCD_WriteCommand(0x06);
	    _delay_ms(1);
}

void LCD_WriteCommand(uint8 command)
{
	DIO_Write_Channel(RS,LOW);
	DIO_Write_Channel(D7,GET_BIT(command,7));
	DIO_Write_Channel(D6,GET_BIT(command,6));
	DIO_Write_Channel(D5,GET_BIT(command,5));
	DIO_Write_Channel(D4,GET_BIT(command,4));

	DIO_Write_Channel(En,HIGH);
	_delay_ms(2);
	DIO_Write_Channel(En,LOW);
	_delay_ms(2);
	//DIO_WritePort(LCD_PORT,(command<<1));
	DIO_Write_Channel(D7,GET_BIT(command,3));
	DIO_Write_Channel(D6,GET_BIT(command,2));
	DIO_Write_Channel(D5,GET_BIT(command,1));
	DIO_Write_Channel(D4,GET_BIT(command,0));
	DIO_Write_Channel(En,HIGH);
	_delay_ms(2);
	DIO_Write_Channel(En,LOW);
	_delay_ms(2);
}

void LCD_WriteData(uint8 data)
{

	 DIO_Write_Channel(RS,HIGH);
	 DIO_Write_Channel(D7,GET_BIT(data,7));
	 DIO_Write_Channel(D6,GET_BIT(data,6));
	 DIO_Write_Channel(D5,GET_BIT(data,5));
	 DIO_Write_Channel(D4,GET_BIT(data,4));

	 DIO_Write_Channel(En,HIGH);
	 _delay_ms(1);
	 DIO_Write_Channel(En,LOW);
	 _delay_ms(1);
	 DIO_Write_Channel(D7,GET_BIT(data,3));
	 DIO_Write_Channel(D6,GET_BIT(data,2));
	 DIO_Write_Channel(D5,GET_BIT(data,1));
	 DIO_Write_Channel(D4,GET_BIT(data,0));
	 DIO_Write_Channel(En,HIGH);
	_delay_ms(2);
	DIO_Write_Channel(En,LOW);
	_delay_ms(2);
}

void LCD_GoTo(uint8 x, uint8 y)
{
	if(0 == y)
	{
		if (x>=0 && x <=15)
		{
			LCD_WriteCommand(0x80 + x);
		}
	}
	else if (1 == y)
	{
		if (x>=0 && x <=15)
		{
			LCD_WriteCommand(0xC0 + x);
		}
	}
}

void LCD_voidClear(void)
{

	 	LCD_WriteCommand(0x01);

}


void LCD_WriteNumber16(uint16 num){


	LCD_WriteData((num%1000)/100+'0');
	LCD_WriteData((num%100)/10+'0');
	LCD_WriteData((num%10)+'0');

}


void LCD_WriteNumber64(uint64 num){


		if(num==0){
			LCD_WriteData('0');
		}

		else{

			uint8 i=0,j,arr[16]={0};

	while(num){

		arr[i]=((num%10)+'0');
		i++;
		num=num/10;

	}
	for(j=i;j>0;j--){

		LCD_WriteData(arr[j-1]);
	}
}
		}

void LCD_WriteString(uint8 *str){

	uint8 i;
	for(i=0;str[i]!='\0';i++){
	LCD_WriteData(str[i]);
	}

}
/*
void Numtostr5digit(uint32 num ,uint8 *arr)
{
	uint8 count=0;
	uint16 var=10000;

	while(count<5)
	{
		arr[count]= (num/var)%10+'0';

		var/=10;
		count++;
	}
	arr[count]='\0';
}
STD_RETURN_Type Numtostr(uint32 num ,uint8 *arr)// any number
{uint8 index=0;
if(num==0)
{
	arr[0]='0';
}

else{
	while(num)
	{
		{
			arr[index]=num/10+'0';
			index++;
		}


	arr[index]='\0';
	}

return E_OK;
}
}

void reverse_array_ofstring(uint8 *ptr,uint8 size)//take string with null
{
	uint8 index=0,temp=0;
	for(index=0;index<size-1;index++)
	{
		temp=ptr[index];
		ptr[index]=ptr[size-index-1];
		ptr[size-index-1]=temp;

	}


*/
