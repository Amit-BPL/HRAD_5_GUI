
/*----------------------------------------------------------------------------
 *      Name:    LCD_4bit.c
 *      Purpose: LCD Functions for 2 line 16 character Text LCD, with 4-bit interface
 *      Version: V1.10
 *----------------------------------------------------------------------------
 *      This file is part of the uVision/ARM development tools.
 *      This software may only be used under the terms of a valid, current,
 *      end user licence from KEIL for a compatible version of KEIL software
 *      development tools. Nothing else gives you the right to use it.
 *
 *      Copyright (c) 2005-2006 Keil Software.
 *---------------------------------------------------------------------------*/

#include "CcAbstLayer.h"
#include "LCD.h"

/*********************** Hardware specific configuration **********************/

/*------------------------- Speed dependant settings -------------------------*/

/* If processor works on high frequency delay has to be increased, it can be 
   increased by factor 2^N by this constant                                   */
#define DELAY_2N     0

/*------------------------- Text LCD size definitions ------------------------*/

#define LineLen     20                  /* Width (in characters)              */
#define NumLines     4                  /* Hight (in lines)                   */

/*-------------------- LCD interface hardware definitions --------------------*/

/* PINS: 
   - DB4 = P1.24
   - DB5 = P1.25
   - DB6 = P1.26
   - DB7 = P1.27
   - E   = P1.31 (for V1 P1.30)
   - RW  = P1.29
   - RS  = P1.28                                                              */

void waitMS(unsigned int);
int del;

#define WASTE               waste_lcd()
#define DELAY               for (del = 0; del < 16; del++)
void waste_lcd(void)
{
}

//void waitMS(unsigned int b)
//{
//unsigned long c;
//	for (c = 1; c<=b; c++);
//}


//#define MCB2300_V1                      /* First version of MCB2300          */

#define PIN_E                 0x00000200//0x00000400
#define PIN_RW                0x00000100//0x00200000//0x00000200
#define PIN_RS                0x00000080//0x00100000//0x00000100
#define PINS_CTRL             0x00000380//0x00B00000//0x00000700
#define PINS_DATA             0x00003C00//0x000000F0

//#define PIN_E                 0x00800000//0x00000400SAAA
//#define PIN_RW                0x00200000//0x00000200
//#define PIN_RS                0x00100000//0x00000100
//#define PINS_CTRL             0x00B00000//0x00000700
//#define PINS_DATA             0x0F000000//0x000000F0

#ifdef  MCB2300_V1
  #undef  PIN_E
  #define PIN_E               0xC0000000
  #undef  PINS_CTRL
  #define PINS_CTRL           0xF0000000
#endif

#define LCD_E(x)              ((x) ? (FIO4SET = PIN_E)  : (FIO4CLR = PIN_E) );

/* pin RW setting to 0 or 1                                                   */
#define LCD_RW(x)             ((x) ? (FIO4SET = PIN_RW) : (FIO4CLR = PIN_RW));

/* pin RS setting to 0 or 1                                                   */
#define LCD_RS(x)             ((x) ? (FIO4SET = PIN_RS) : (FIO4CLR = PIN_RS));

/* Reading DATA pins                                                          */
#define LCD_DATA_IN           ((FIO4PIN >> 10) & 0xF)

/* Writing value to DATA pins                                                 */
#define LCD_DATA_OUT(x)       FIO4CLR = PINS_DATA; FIO4SET = (x & 0xF) << 10;

/* Setting all pins to output mode                                            */
#define LCD_ALL_DIR_OUT       FIO4DIR  |=  PINS_CTRL | PINS_DATA;

/* Setting DATA pins to input mode                                            */
#define LCD_DATA_DIR_IN       FIO4DIR &= ~PINS_DATA;     

/* Setting DATA pins to output mode                                           */
#define LCD_DATA_DIR_OUT      FIO4DIR |=  PINS_DATA;

/******************************************************************************/


/* 8 user defined characters to be loaded into CGRAM (used for bargraph)      */
//const unsigned char UserFont[8][8] = {
//  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
//  { 0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10 },
//  { 0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18 },
//  { 0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C },
//  { 0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E },
//  { 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F },
//  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
//  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
//};

//#define	LCD_EN_uC_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xFD) | (x << 1))
//#define	LCD_RW_uC_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xFE) | (x << 0))
//#define	LCD_RS_uC_Dat(x)	FIO4PIN0 =((FIO4PIN0 & 0x7F) | (x << 7))
/************************ Global function definitions *************************/


/*******************************************************************************
* Delay in while loop cycles                                                   *
*   Parameter:    cnt:    number of while cycles to delay                      *
*   Return:                                                                    *
*******************************************************************************/

void delay (int cnt)
{
  cnt <<= DELAY_2N;

  while (cnt--);
}


/*******************************************************************************
* Read status of LCD controller                                                *
*   Parameter:    none                                                         *
*   Return:       Status byte contains busy flag and address pointer           *
*******************************************************************************/

static unsigned char lcd_read_status (void)
{
  unsigned char status;

  LCD_DATA_DIR_IN
	LCD_RS_uC_Dat(0);
	LCD_RW_uC_Dat(1);
	Delay_100nSec(1);				// Value of function argument x 100nS
	LCD_EN_uC_Dat(1);
	Delay_100nSec(2);				// Value of function argument x 100nS
	status  = LCD_DATA_IN << 4;
	Delay_100nSec(2);				// Value of function argument x 100nS
	LCD_EN_uC_Dat(0);
	Delay_100nSec(3);				// Value of function argument x 100nS
	LCD_EN_uC_Dat(1);
	Delay_100nSec(2);				// Value of function argument x 100nS
	status  |= LCD_DATA_IN;
	Delay_100nSec(2);				// Value of function argument x 100nS
	LCD_EN_uC_Dat(0);
	Delay_100nSec(1);				// Value of function argument x 100nS
//  LCD_RS(0)
//  LCD_RW(1)
//  delay(10);
//  LCD_E(1)
//  delay(10);
//  status  = LCD_DATA_IN << 4;
//  LCD_E(0)
//  delay(10);
//  LCD_E(1)
//  delay(10);
//  status |= LCD_DATA_IN;
//  LCD_E(0)
  LCD_DATA_DIR_OUT
  return (status);
}


/*******************************************************************************
* Wait until LCD controller busy flag is 0                                     *
*   Parameter:                                                                 *
*   Return:       Status byte of LCD controller (busy + address)               *
*******************************************************************************/

static unsigned char wait_while_busy (void)
{
  unsigned char status;

  do  {
    status = lcd_read_status();
  }  while (status & 0x80);             /* Wait for busy flag                 */

  return (status);
}


/*******************************************************************************
* Write 4-bits to LCD controller                                               *
*   Parameter:    c:      command to be written                                *
*   Return:                                                                    *
*******************************************************************************/

void lcd_write_4bit (unsigned char c)
{
	Delay_100nSec(1);				// Value of function argument x 100nS
	LCD_EN_uC_Dat(1);
	Delay_100nSec(3);				// Value of function argument x 100nS
	LCD_D0_D3_uC_Dat(c);
	Delay_100nSec(1);				// Value of function argument x 100nS
	LCD_EN_uC_Dat(0);
	Delay_100nSec(2);				// Value of function argument x 100nS	
}


/*******************************************************************************
* Write command to LCD controller                                              *
*   Parameter:    c:      command to be written                                *
*   Return:                                                                    *
*******************************************************************************/

void lcd_write_cmd (unsigned char c)
{
	Delay_1uSec(1);
	LCD_RW_uC_Dat(0);
	LCD_RS_uC_Dat(0);
	Delay_100nSec(3);				// Value of function argument x 100nS
  lcd_write_4bit (c>>4);
  Delay_1uSec(1);
  lcd_write_4bit (c);
  Delay_1uSec(1);
}


/*******************************************************************************
* Write data to LCD controller                                                 *
*   Parameter:    c:      data to be written                                   *
*   Return:                                                                    *
*******************************************************************************/

static void lcd_write_data (unsigned char c)
{
  //wait_while_busy();
	Delay_1uSec(1);
	LCD_RW_uC_Dat(0);
	LCD_RS_uC_Dat(1);
	Delay_100nSec(3);				// Value of function argument x 100nS
  lcd_write_4bit (c>>4);
  Delay_1uSec(1);
  lcd_write_4bit (c);
	Delay_1uSec(1);
}

/*******************************************************************************
* Print Character to current cursor position                                   *
*   Parameter:    c:      character to be printed                              *
*   Return:                                                                    *
*******************************************************************************/
void lcd_putchar (char c)
{ 
  lcd_write_data (c);
}

/*******************************************************************************
* Initialize the LCD controller                                                *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

void lcd_init(void)
{ 
  /* Set all pins for LCD as outputs                                          */
//  LCD_ALL_DIR_OUT

  Delay_1uSec(15000);
  LCD_RS_uC_Dat(0);
	Delay_1uSec(1);
  lcd_write_4bit (0x3);                 
  Delay_1uSec(5000);
  lcd_write_4bit (0x3);
  Delay_1uSec(1000);
//  lcd_write_4bit (0x3);
//	Delay_1uSec(5000);
//  delay (5);
  lcd_write_4bit (0x2);									//Select 4-bit interface             
  Delay_1uSec(50);
/*-------------	LCD enter in to 4 bit mode and commands can be passed----------------*/	
  lcd_write_cmd (0x2C);                 /* 2 lines, 5x10 character matrix      */
	Delay_1uSec(5);
  lcd_write_cmd (0x0C);                 /* Display ctrl:Disp=ON,Curs/Blnk=OFF */
	Delay_1uSec(5);
  lcd_write_cmd (0x06);                 /* Entry mode: Move right, no shift   */
	Delay_1uSec(5);
	lcd_write_cmd(0x80);                  /* Set DDRAM address counter to 0     */
	Delay_1uSec(5);
}

/*******************************************************************************
* Set cursor position on LCD display                                           *
*   Parameter:    column: column position                                      *
*                 row:   line position                                        *
*   Return:                                                                    *
*******************************************************************************/
void LCD_SetCursor (char row, char column)
{
	switch (row) {
		case 1: lcd_write_cmd(0x80 + (column - 1));
			break;
		case 2: lcd_write_cmd(0xC0 + (column - 1));
			break;
		case 3: lcd_write_cmd(0x94 + (column - 1));
			break;
		case 4: lcd_write_cmd(0xD4 + (column - 1));
			break;   //0xd4
	}
	LCD_RS_uC_Dat(1);
	LCD_RW_uC_Dat(0);	
	Delay_1uSec(1);
}

/*******************************************************************************
* Clear the LCD display                                                        *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/
void lcd_clear(void)
{
  lcd_write_cmd(0x01);                  /* Display clear                      */
	Delay_1uSec(100);
//  LCD_SetCursor(0, 0);					//xxxxxxxxxxxxxxx	This may not be required. Check while testing	xxxxxxxxxxxxx
	Delay_1uSec(300);
//	Delay_1uSec(100);
}

/*******************************************************************************
* Print sting to LCD display                                                   *
*   Parameter:    string: pointer to output string                             *
*   Return:                                                                    *
*******************************************************************************/

void lcd_printS (unsigned char const *string)
{
  while (*string)  {
    lcd_putchar (*string++);
  }
//	Delay_1uSec(5);
//  lcd_write_cmd (0x0C);                 /* Display ctrl:Disp=ON,Curs/Blnk=OFF */
}
