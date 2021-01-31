/*

 * lock.c
 *
 *  Created on: Jan 11, 2021
 *      Author: SOUQ COMPUTER
 */


/*

 * LOCK.c
 *
 *   Created on: Jan 11, 2021
 *      Author: yara mohsen
 */

#include "DIO_Reg.h"
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "key_pad.h"
#include"LCD.h"
#include"lock.h"

/*************************************************************************
* Initialization of variables :
* ********
*
* *************************************************************************/
uint64 password_static =0;
uint64 password_entered=0;

uint8 char_input='%';
uint8 compare_res_flag=1;
uint8 number_of_tries=0;

uint8 enter_new_pass=0;
uint8 lcd_index=3;
uint8 counter=0;
ACTION_TYPE action = ENTER_NEW_PASSWORD;


/*****
 * important strings
 */

uint8 enter_pass_string[]={"Enter new Password"};
uint8 confirm_password_string[]={"cofirm password"};
uint8 enter_old_string[]={"Enter old Password"};


#define F_CPU 8000000
#include<util/delay.h>
/*************************************************************************
*
* *************************************************************************/


void safe_lock(void)
{
	lock_init();
while(1){

	if(Get_char()==SUCCCESSFUL)
	{
		Check_char();

	}
 }
}

/*************************************************************************
* Get_char :
* **********
*
* input  : void
* output : return the state of enum "calculator_return_state"
*
* use the keypad files to gets the input and saves it into variable
* "char_input" and check if a key is pressed return "SUCCCESSFUL"
* if no key pressed return "FAIL"
*
* *************************************************************************/


State Get_char(void)
{

    State value;

    char_input = pressed_key();

    if(char_input!='%')
    {
        value= SUCCCESSFUL;
    }

    else
    {
        value= FAIL;

    }

 return value;
}

/*************************************************************************
* Check_char :
* ************
*
* *************************************************************************/


void Check_char(void)
{
switch (action){

	case ENTER_NEW_PASSWORD:

			if((char_input >='0') && (char_input <='9'))
				{

				save_Password();
									}

			else if (char_input=='c'){
				//rest lcd
				lcd_index=3;
				clear();

				//rest variables
				if(counter<4){
					password_static=0;
					counter=0;
				}
				else if(counter>=4){
					password_entered=0;
					counter=4;
				}
				     }
	break;

	case ENTER_CURRENT_PASSWORD:

		if((char_input >='0') && (char_input <='9'))
			{
			save_Password();
				}


		else if (char_input=='c'){
			password_entered=0;
			counter=4;
			lcd_index=3;
			clear();
			}

			else if (char_input=='#'){
				enter_new_pass=1;
				LCD_voidClear();
				password_entered=0;
				counter=4;
				lcd_index=3;
				LCD_WriteString(enter_old_string);
				}
		break;

	case ENTER_MASTER_KEY:
		if((char_input >='0') && (char_input <='9'))
			{

			save_Password();

						}

		if (char_input=='c'){
					password_entered=0;
					counter=4;
					lcd_index=3;
					clear();
					}

			break;
    }
}



void save_Password(void)
{
	if(counter<4)
	{
		    save_number(&password_static);
		    print_astrecs();

		    if(counter==3){
		    LCD_voidClear();
		    LCD_GoTo(0,0);
		    LCD_WriteString(confirm_password_string);
		    lcd_index=3;


		    }

	}

	else if(counter<8)
	{
		     save_number(&password_entered);
		     print_astrecs();

	}

	counter++;

// if set 4 bit for new enter and 4 bit for the confirm then compare
	if(counter==8){
		compare();
	}
}

void compare(void)
{

	LCD_voidClear();
    LCD_GoTo(0,0);
	lcd_index=3;

		switch (action){

			case ENTER_NEW_PASSWORD:
					if(Compare_two_Passwords()== SAME)
					 {
						 action=ENTER_CURRENT_PASSWORD;

						 password_entered=0;
						 counter=4;

						 LCD_WriteString(enter_old_string);

					 }
					else{

						password_static=0;
						password_entered=0;
						counter=0;

						LCD_WriteString(enter_pass_string);


					}
			break;

	case ENTER_CURRENT_PASSWORD:

					if(Compare_two_Passwords()== SAME && enter_new_pass==0)
					  {
						open_stepper(TURN1);

						 close_stepper();
						 password_entered=0;
						 counter=4;
						 LCD_voidClear();
						 LCD_GoTo(0,0);
						 lcd_index=3;
						 LCD_WriteString(enter_old_string);
						 number_of_tries=0;
						}
					else if(Compare_two_Passwords()==SAME && enter_new_pass==1)
					  {
                       action =ENTER_NEW_PASSWORD;
                       password_static=0;
                       password_entered=0;
                       counter=0;
                       enter_new_pass=0;
                       LCD_WriteString(enter_pass_string);

						}

					else{

						 if(number_of_tries==2)
						 	{
						 	 action=ENTER_MASTER_KEY;
						 	 password_static=MASTER_KEY;
						 	LCD_WriteString("enter master key..");

						 		  }
						 else
						 {
						 	 LCD_WriteString("try again..");
						 		}

						 password_entered=0;
						 counter=4;
						 number_of_tries++;
						}

			break;
	case ENTER_MASTER_KEY:

		if(Compare_two_Passwords()== SAME)
			{
			 lock_init();
			 number_of_tries=0;
				 }
		else{ LCD_WriteString("enter master key..");}

		break;


	  }



}

void print_astrecs(void)
{
	LCD_GoTo(lcd_index,1);
	LCD_WriteData('*');
	lcd_index++;
}

void open_stepper(TURN turn)
{

	LCD_voidClear();
    LCD_GoTo(0,0);
    LCD_WriteString("open motor..wait");
    _delay_ms(5000);

}
void close_stepper(void){

	LCD_voidClear();
    LCD_GoTo(0,0);
	LCD_WriteString("close motor");
	_delay_ms(3000);
}
ComparePassword Compare_two_Passwords(void)
{
	compare_res_flag = password_static^password_entered;

	if(compare_res_flag==0){
		return SAME;
	}
	else if (compare_res_flag!=0){
		return NOT_SAME;
	}

}

void save_number(uint64 *num)
{
    (*num)=(uint64)((*num)*10+(char_input-'0'));
}

void lock_init(void)
{

    action=ENTER_NEW_PASSWORD;
   	password_static=0;
   	password_entered=0;
   	counter=0;
    lcd_index=3;
    LCD_WriteString(enter_pass_string);

}

void clear(void)
{
	LCD_GoTo(0,1);
	LCD_WriteString("              ");
	LCD_GoTo(0,1);
}
