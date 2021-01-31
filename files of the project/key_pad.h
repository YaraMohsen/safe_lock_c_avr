/*
 * key_pad.h
 *
 *  Created on: Dec 25, 2020
 *      Author: SOUQ COMPUTER
 */

#ifndef KEY_PAD_H_
#define KEY_PAD_H_


typedef enum{
	ASCII_CODE_USE=0,
	SEVEN_SEG_USE=1
}KEYPAD_USE_TYPE;



extern void key_init(void);
extern uint8 pressed_key(void);

#endif /* KEY_PAD_H_ */
