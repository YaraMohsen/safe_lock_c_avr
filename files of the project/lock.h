/*

 * lock.h

 *
 *  Created on: Jan 11, 2021
 *      Author: YARA
 */

#ifndef LOCK_H_
#define LOCK_H_

#define MASTER_KEY 1991

#define first_digit_static_password 0
#define last_digit_static_password 3

#define first_digit_entered_password 4
#define last_digit_entered_password 7

#define first_index_lcd 3

typedef enum{
	FAIL,
	SUCCCESSFUL

}State;


typedef enum{
	TURN0,
	TURN1
}TURN;


typedef enum{
NOT_SAME,
SAME

}ComparePassword;

typedef enum{

ENTER_NEW_PASSWORD,
ENTER_CURRENT_PASSWORD,
ENTER_MASTER_KEY


}ACTION_TYPE;



extern void lock_init(void);
extern void safe_lock(void);
extern State Get_char(void);
extern void Check_char(void);

extern void save_Password(void);
extern ComparePassword Compare_two_Passwords(void);
extern void compare_action(void);


extern void save_number(uint64*num);
extern void clear(void);

extern  void close_stepper(void);
extern void open_stepper(TURN turns);

extern void print_astrecs(void);

#endif /* LOCK_H_ */
