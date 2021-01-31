/*
 * BIT_MATH.h

 *
 *  Created on: Dec 11, 2020
 *      Author: yara mohsen
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(Reg,bit) Reg|=(1<<bit)
#define CLEAR_BIT(Reg,bit) Reg=(Reg&(~(1<<bit)))

#define TOOGLE_BIT(Reg,bit) Reg^=(1<<bit)

#define GET_BIT(Reg,bit) ((Reg>>bit)&1)

#define WRITE_BIT(byte,bit,value)  byte=((byte&(~(1<<bit)))|(value<<bit))

#endif /* BIT_MATH_H_ */
