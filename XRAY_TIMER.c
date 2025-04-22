#include <lpc24xx.h>
#include <stdio.h>
#include "KEYPAD.h"
#include "main.h"
#include "LCD.h"
#include "timer.h"
#include "irq.h"

#define EINT0		0x00000001
#define EINT0_EDGE	0x00000005
#define I_Bit			0x80
#define F_Bit			0x40

unsigned char  wait_start=0,wait=0,flash_start=0; 
unsigned int  wait_counter=0,flash_counter=0,xray_start=0;
unsigned int  key_debonce=0,flash=0;

/************************************************************************
Function Name		: timer_isr(void) __irq
Input				: None
Return Value		: None
Usage				: TO Define GPIO's 
***********************************************************************/
void Timer0Handler (void) __irq 
{	
	T0IR = 1;
	if(xray_flag==1)
	  xray_start++;
	if(xray_start==1500)
	{
		start_chk++;
		xray_start=0;
	}		
	if(debounce == 1) 
	   key_debonce++;
	if(key_debonce>5000)
	{
	   debounce_on = 0;
	   debounce = 0;
	   key_debonce=0;
	}
	if(wait_start==1)
	  wait_counter++;
	if(wait_counter>1500)
	{
		wait++;
		wait_counter=0;
	}		
	
	if(patient_screen==1)	
	  flash_counter++;
	else
		flash_counter=0;

	if(anatomy_screen==1)	
	  flash++;
	else
		flash=0;	

	VICVectAddr = 0;
}
/************************************************************************
Function Name		: timerInit
Input				: None
Return Value		: None
Usage				: TO Define GPIO's 
***********************************************************************/
void timerInit(void)
{
	T0MR0 = 1443;			// for 5msec...		//for 12MHz//15360;//for 256usec//2340;							//175000;//5msec//80000; 5msec
	T0MCR = 3;
	T0TCR = 1;															 	

	//VICVectAddr0= (unsigned long)Timer0Handler;//timer_isr;
	//VICVectCntl0= 0x20 | 4;
	//VICIntSelect |= (0x1<<4);
	install_irq( TIMER0_INT, (void *)Timer0Handler, HIGHEST_PRIORITY );
	VICIntEnable = 0x00000010;
}



