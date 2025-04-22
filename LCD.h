#ifndef LCD_H_
#define LCD_H_

/*----------------------------------------------------------------------------
 *      Name:    LCD.H
 *      Purpose: LCD function prototypes
 *      Version: V1.10
 *----------------------------------------------------------------------------
 *      This file is part of the uVision/ARM development tools.
 *      This software may only be used under the terms of a valid, current,
 *      end user licence from KEIL for a compatible version of KEIL software
 *      development tools. Nothing else gives you the right to use it.
 *
 *      Copyright (c) 2005-2006 Keil Software.
 *---------------------------------------------------------------------------*/
extern void lcd_putchar (char);
extern void lcd_init(void);
extern void LCD_SetCursor (char, char);
extern void lcd_clear (void);
extern void lcd_printS (unsigned char const*);
extern void Delay_100nSec(unsigned char);
extern void Delay_1uSec(unsigned int);
/******************************************************************************/

#endif
