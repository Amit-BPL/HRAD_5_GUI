/*****************************************************************************
 *   irq.c: Interrupt handler C file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.07.13  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "LPC24xx.h"			/* LPC23XX/24xx Peripheral Registers */
#include "type.h"
#include "irq.h"

/******************************************************************************
** Function name:		FIQ_Handler
**
** Descriptions:		FIQ interrupt handler called in startup
** parameters:			 
**					
** Returned value:		
** 
******************************************************************************/
void FIQ_Handler( void ) __irq
{
#if FIQ
  if ( VICFIQStatus & (0x1<<4) && VICIntEnable & (0x1<<4) )
  {
		Timr0_Intrupt_Handler();
  }
  return;
#endif 
}

/* Initialize the interrupt controller */
/******************************************************************************
** Function name:		init_VIC
**
** Descriptions:		Initialize VIC interrupt controller.
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void init_VIC(void) 
{
    DWORD i = 0;
    DWORD *vect_addr, *vect_prio;
   	
    /* initialize VIC*/
    VICIntEnClr = 0xffffffff;
    VICVectAddr = 0;
    VICIntSelect = 0;

    /* set all the vector and vector control register to 0 */
    for ( i = 0; i < VIC_SIZE; i++ )
    {
		vect_addr = (DWORD *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
		vect_prio = (DWORD *)(VIC_BASE_ADDR + VECT_PRIO_INDEX + i*4);
		*vect_addr = 0x0;	
		*vect_prio = 0xF;
    }
    return;
}

/******************************************************************************
** Function name:		install_irq
**
** Descriptions:		Install interrupt handler
** parameters:			Interrupt number, interrupt handler address, 
**						interrupt priority
** Returned value:		true or false, return false if IntNum is out of range
** 
******************************************************************************/
BYTE install_irq( DWORD IntNumber, void *HandlerAddr, DWORD Priority )
{
    DWORD *vect_addr;
    DWORD *vect_prio;
      
    VICIntEnClr = 1 << IntNumber;	/* Disable Interrupt */
    if ( IntNumber >= VIC_SIZE )
    {
		return ( FALSE );
    }
    else
    {
		/* find first un-assigned VIC address for the handler */
		vect_addr = (DWORD *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + IntNumber*4);
		vect_prio = (DWORD *)(VIC_BASE_ADDR + VECT_PRIO_INDEX + IntNumber*4);
		*vect_addr = (DWORD)HandlerAddr;	/* set interrupt vector */
		*vect_prio = Priority;
		VICIntEnable = 1 << IntNumber;	/* Enable Interrupt */
		return( TRUE );
    }
}


void ConfigInterrupt()
{
//	unsigned char Temp1 = 0;
	init_VIC();
#if FIQ
//	Timer 0 Interrupt configuration	
	VICIntSelect |= (0x1<<4);																							//	Timer0 is configured as Fast Interrupt
	VICIntEnable = (0x1<<4);																							// 	Enable Timer0 interrupt
#else
	install_irq(TIMER0_INT, (void *)Timr0_Intrupt_Handler, 0);
#endif
	install_irq(TIMER1_INT, (void *)Timr1_Intrupt_Handler, 1);
	install_irq(TIMER2_INT, (void *)Timr2_Intrupt_Handler, 3);	
}





/******************************************************************************
**                            End Of File
******************************************************************************/
