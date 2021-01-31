/*
 * LCD.h

 *
 *  Created on: Dec 25, 2020
 *      Author: yara
 */



#ifndef LCD_H_
#define LCD_H_

#define RS  portA1
#define En  portA2



#define D4  portA3
#define D5  portA4
#define D6  portA5
#define D7  portA6


typedef enum
{
E_OK,
E_NOK
}STD_RETURN_Type;

extern void LCD_Init(void);
extern void LCD_WriteCommand(uint8 command);
extern void LCD_WriteData(uint8 data);
extern void LCD_GoTo(uint8 x, uint8 y);
extern void LCD_voidClear(void);
extern void LCD_WriteNumber16(uint16 num);
extern void LCD_WriteNumber64(uint64 num);
extern void LCD_WriteString(uint8 *str);



#endif /* LCD_H_ */
