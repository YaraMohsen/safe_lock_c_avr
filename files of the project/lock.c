
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
* password_static  : static password hold the password of the system
* password_entered : dynamic password hold the input password from the
*                    user
*
* counter : from 0 to 3 the system will save on the password_static
*           from 4 to 7 the system will save on the password_entered
*
* enter_new_pass_flag : if 1 then the user press '#' char "enter new password
*
*
* ****************************************************************************/
uint64 password_static =0;
uint64 password_entered=0;

uint8 char_input='%';
uint8 compare_res_flag=1;
uint8 number_of_tries=0;

uint8 enter_new_pass_flag=0;
uint8 lcd_index=first_index_lcd;
uint8 counter=first_digit_static_password;
ACTION_TYPE action = ENTER_NEW_PASSWORD;


/*********************
 * important strings
 ********************/

uint8 enter_pass_string[]= {"Enter new Password"};
uint8 confirm_password_string[]= {"cofirm password"};
uint8 enter_old_string[]= {"Enter old Password"};


#define F_CPU 8000000
#include<util/delay.h>
/*************************************************************************
*
* *************************************************************************/


void safe_lock(void)
{
    lock_init();

    while(1)
    {

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
* input  : void
* output : void
*
* contain switch cases for 3 states " ENTER_NEW_PASSWORD
*                                     ENTER_CURRENT_PASSWORD
*                                     ENTER_MASTER_KEY "
*
* 1  ENTER_NEW_PASSWORD :
*    ******************
*   check if the input numbers save them .
*   char 'c' to clear the lcd numbers and clear the corresponding variables.
*
*
* 2 ENTER_CURRENT_PASSWORD
*   **********************
*   check if the input numbers save them .
*   char 'c' to clear the lcd numbers and clear the corresponding variables.
*   char '#' to change to ENTER_NEW_PASSWORD case to set new password.
*
*
* 3 ENTER_MASTER_KEY
*   ****************
*   check if the input numbers save them .
*   char 'c' to clear the lcd numbers and clear the corresponding variables.
*
* *************************************************************************/


void Check_char(void)
{
    switch (action)
    {

/***** 1  ENTER_NEW_PASSWORD ******/

    case ENTER_NEW_PASSWORD:

        if((char_input >='0') && (char_input <='9'))
        {

            save_Password();
        }

        else if (char_input=='c')
        {
            //rest lcd
            clear_number();

            //rest variables
            if(counter<(last_digit_static_password+1))
            {
                password_static=0;
                counter=first_digit_static_password;
            }

            else if(counter>=(first_digit_entered_password))
            {
                password_entered=0;
                counter=first_digit_entered_password;
            }
        }
        break;

  /***** 2  ENTER_CURRENT_PASSWORD ******/

    case ENTER_CURRENT_PASSWORD:

        if((char_input >='0') && (char_input <='9'))
        {
            save_Password();
        }


        else if (char_input=='c')
        {
            password_entered=0;
            counter=first_digit_entered_password;
            clear_number();
        }

        else if (char_input=='#')
        {
        	enter_new_pass_flag=1;// flag to change the old password

        	LCD_voidClear();

            password_entered=0;
            counter=first_digit_entered_password;
            lcd_index=first_index_lcd;
            LCD_WriteString(enter_old_string);
        }
        break;

  /***** 2  ENTER_MASTER_KEY ******/

    case ENTER_MASTER_KEY:

        if((char_input >='0') && (char_input <='9'))
        {
            save_Password();
        }

        else if (char_input=='c')
        {
            password_entered=0;
            counter=first_digit_entered_password;
            lcd_index=first_index_lcd;
            clear_number();
        }

        break;
    }
}

/*************************************************************************
* save_password:
* ************
*
* input  : void
*
* output : void
*
* the counter variable has 3 conditions:
* *************************************
*
* 1) counter < last_digit_static_password+1
*  then the user didn't enter 4 digits of the static password yet.
*  so it will save it in "password_static"
*
* 2) counter < (last_digit_entered_password+1)
*    then the user didn't enter 4 digits of the entered password yet.
*    so it will save it in "password_entered"
*
* 3) counter==last_digit_entered_password+1
*    this mean that the user enter the 2 passwords
*    the static and the entere and it is already to compare.
* *************************************************************************/

void save_Password(void)
{
    if(counter <(last_digit_static_password+1))
    {
        save_number(&password_static);
        print_astrecs();

        if(counter==last_digit_static_password)
        {
            LCD_voidClear();
            LCD_GoTo(0,0);
            LCD_WriteString(confirm_password_string);
            lcd_index=first_index_lcd;
        }

    }

    else if(counter< (last_digit_entered_password+1))
    {
        save_number(&password_entered);
        print_astrecs();

    }

    counter++;


    if(counter==(last_digit_entered_password+1))   // if set 4 bit for new enter and 4 bit for the confirm then compare
    {
    	compare_action();
    }
}

/*************************************************************************
* compare :
* ************
* input  : void
* output : void
*
* contain switch cases for 3 states " ENTER_NEW_PASSWORD
*                                     ENTER_CURRENT_PASSWORD
*                                     ENTER_MASTER_KEY "
*
* 1  ENTER_NEW_PASSWORD :
*    ******************
*   check if (password_static == password_entered)
*   move to "ENTER_CURRENT_PASSWORD" state
*
*
* 2 ENTER_CURRENT_PASSWORD
*   **********************
*   check if (password_static == password_entered)->
*   if enter_new_pass_flag==1 then change the old password
*   if enter_new_pass_flag==0 then open the door
*
*   check if (password_static != password_entered)->
*   handle the 3 tries
*
*
*
* 3 ENTER_MASTER_KEY
*   ****************
*   password_static = MASTER_KEY;
*   check if (password_static == password_entered)
*
* *************************************************************************/

void compare_action(void)
{

    LCD_voidClear();
    LCD_GoTo(0,0);
    lcd_index=first_index_lcd;

    switch (action)
    {

    case ENTER_NEW_PASSWORD:

        if(Compare_two_Passwords()== SAME)
        {
        	open_stepper(TURN0);
            action=ENTER_CURRENT_PASSWORD;
            password_entered=0;
            counter=first_digit_entered_password;

            LCD_WriteString(enter_old_string);

        }
        else
        {
            password_static=0;
            password_entered=0;
            counter=first_digit_static_password;

            LCD_WriteString(enter_pass_string);
        }
        break;

    case ENTER_CURRENT_PASSWORD:

        if(Compare_two_Passwords()== SAME && enter_new_pass_flag==0)
        {
            open_stepper(TURN1);

            password_entered=0;
            counter=first_digit_entered_password;

            LCD_voidClear();
            LCD_GoTo(0,0);
            lcd_index=first_index_lcd;

            LCD_WriteString(enter_old_string);
            number_of_tries=0;
        }
        else if(Compare_two_Passwords()==SAME && enter_new_pass_flag==1)
        {
            action =ENTER_NEW_PASSWORD;
            password_static=0;
            password_entered=0;
            counter=first_digit_static_password;
            enter_new_pass_flag=0;
            LCD_WriteString(enter_pass_string);

        }

        else
        {
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
            counter=first_digit_entered_password;
            number_of_tries++;
        }

        break;

    case ENTER_MASTER_KEY:

        if(Compare_two_Passwords()== SAME)
        {
            lock_init();
            number_of_tries=0;
        }
        else
        {
            LCD_WriteString("enter master key..");
        }

        break;
    }
}


/*************************************************************************
* Compare_two_Passwords:
* *********************
*
* input  :  void
*
* output : typedef form emun ComparePassword " SAME -NOT_SAME"
*
* it is compare just 2 variables " password_static and password_entered "
* then return same=1 or not_same=0
*
* *************************************************************************/
ComparePassword Compare_two_Passwords(void)
{
    compare_res_flag = password_static ^ password_entered;

    if(compare_res_flag==0)
    {
        return SAME;
    }
    else if (compare_res_flag!=0)
    {
        return NOT_SAME;
    }

}

/*************************************************************************
* save_number:
* ************
*
* input  : take pointer to uint64 : take address of number and save digits on it
*
* output : void
*
* *************************************************************************/

void save_number(uint64* num)
{
    (*num)=(uint64)((*num)*10+(char_input-'0'));
}

/*************************************************************************
* print astrecs:
* ************
*
* input  : void
*
* output : void
*
* every time we call it -> print '*'
* *************************************************************************/
void print_astrecs(void)
{
    LCD_GoTo(lcd_index,1);
    LCD_WriteData('*');
    lcd_index++;
}

/*************************************************************************
* open_stepper:
* ************
*
* input  : enum type TRUN "TURN0,TURN1"
*          turn0 for small turn - turn1 for open the motor
*
* output : void
*
* *************************************************************************/
void open_stepper(TURN turn)
{

    LCD_voidClear();
    LCD_GoTo(0,0);
    LCD_WriteString("open motor..wait");

    if(turn==TURN0)
    {
    	_delay_ms(1000);
    	close_stepper();
    }
    else
    {
    _delay_ms(5000);
    close_stepper();
    }
}

/*************************************************************************
* close_stepper:
* ************
*
* input  : void
*
* output : void
*
* *************************************************************************/
void close_stepper(void)
{

    LCD_voidClear();
    LCD_GoTo(0,0);
    LCD_WriteString("close motor");
    _delay_ms(3000);
}


/*************************************************************************
* lock_init:
* *****
*
* input  : void
*
* output : void
*
* initalize all variables
* *************************************************************************/
void lock_init(void)
{

    action=ENTER_NEW_PASSWORD;
    password_static=0;
    password_entered=0;
    counter=first_digit_static_password;
    lcd_index=first_index_lcd;
    LCD_WriteString(enter_pass_string);

}


/*************************************************************************
* clear_number:
* ************
*
* input  : void
*
* output : void
*
* just clear the number places
* *************************************************************************/
void clear_number(void)
{
    LCD_GoTo(0,1);
    LCD_WriteString("              ");
    LCD_GoTo(0,1);
    lcd_index=first_index_lcd;
}
