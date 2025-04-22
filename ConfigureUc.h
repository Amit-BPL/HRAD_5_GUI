#ifndef CONFIGUREUC_H_
#define CONFIGUREUC_H_
#include "CcAbstLayer.h"

#if (Fpclk / (Fcclk / 4)) == 1		/* PCLK is 1/4 CCLK */	
	#define TIMER0_PRSET_COUNT 1000
	#define TIMER0_MATCHSET_COUNT 5					// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer0 meant for 500uS
	#define TIMER1_PRSET_COUNT 1000
	#define TIMER1_MATCHSET_COUNT 59				// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer1 meant for 5mS
	#define TIMER2_PRSET_COUNT 6000
	#define TIMER2_MATCHSET_COUNT 199					// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer2 meant for 100mS
#elif (Fpclk / (Fcclk / 4)) == 2	/* PCLK is 1/2 CCLK */
	#define TIMER0_PRSET_COUNT 1000
	#define TIMER0_MATCHSET_COUNT 11					// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer0 meant for 500uS
	#define TIMER1_PRSET_COUNT 1000
	#define TIMER1_MATCHSET_COUNT 119				// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer1 meant for 5mS
	#define TIMER2_PRSET_COUNT 6000
	#define TIMER2_MATCHSET_COUNT 399					// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer2 meant for 100mS
#elif (Fpclk / (Fcclk / 4)) == 4	/* PCLK is the same as CCLK */
	#define TIMER0_PRSET_COUNT 1000
	#define TIMER0_MATCHSET_COUNT 23					// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer0 meant for 500uS
	#define TIMER1_PRSET_COUNT 1000
	#define TIMER1_MATCHSET_COUNT 239				// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer1 meant for 5mS
	#define TIMER2_PRSET_COUNT 6000
	#define TIMER2_MATCHSET_COUNT 799					// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer2 meant for 100mS
#elif ((Fcclk / 4)/Fpclk) == 2		/* PCLK is 1/8 CCLK */
	#define TIMER0_PRSET_COUNT 1000
	#define TIMER0_MATCHSET_COUNT 3					// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer0 meant for 500uS
	#define TIMER1_PRSET_COUNT 1000
	#define TIMER1_MATCHSET_COUNT 30				// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer1 meant for 5mS
	#define TIMER2_PRSET_COUNT 6000
	#define TIMER2_MATCHSET_COUNT 100					// (Required Time/(Tpclk x TIMERn_PRSET_COUNT))-1;	//Timer2 meant for 100mS
#endif	

#define RS485_CH1_BAUDRATE 9600

unsigned char FirstBootRegstr;

extern Uc_States eUc_States, eLastUc_States, eSupUc_States;
extern CONTROL_PARAMETER CntrlPrmtrs;
extern RS485_PANL_RX Rs485RxFrame;
extern unsigned char FndOrdinalNumOfShortArr(const unsigned short*, unsigned char, unsigned short);
extern const unsigned short StationsOfmA[];
extern const unsigned short StdmAsValues[];
extern volatile unsigned char Rs485RxBuffr[],Rs485TxBuffr[];
extern volatile unsigned char *Rs485RxBuffPtr,*Rs485TxBuffPtr;
extern unsigned char LowPowerModeLockVar, LineVoltChekAbort;
extern void Delay_1uSec(unsigned int);
extern void PopLastExposeProtocol(void);
extern void InitFlashSsp(void);
extern void CheckLowPwrModeKey(void);
extern void PopPowerModeKey(void);
extern void PopLastCalibPointer(void);
extern unsigned char CheckFirstBoot(void);

#endif
