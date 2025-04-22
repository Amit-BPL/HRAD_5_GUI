#include "CcAbstLayer.h"
#include "irq.h"
#include "XRAY_CAN.h"
#include <stdlib.h>

#define DAC_DATA_INITIATED 1
#define DAC_DATA_FINISHED 2

#define ADC_DONE 0x80000000
#define ADC_OVERRUN 0x40000000
#define ADC_NUM 8
#define ADC_OFFSET		0x10						// Base Adress is 0xE003 4000 and Data Register starts from 0xE003 4010
#define ADC_INDEX		4

#define PHASE_VOLT_CONVRT_FACTOR 1.674			//For 24V transformer: 2.1586; For 6V Txmr: 1.591 when R147:1K; R148:5K

unsigned short PhaseVoltAdcAvgBfr[4] = {0,0,0,0}, PhaseVoltDispVal = 0;

extern unsigned char OutputKvLastExpos, OutputmALastExpos, LineResx10, NvmWriteDelayTmr1;
extern CONTROL_PARAMETER CntrlPrmtrs;
extern InAdc_Num eInAdc_Num, eInAdc_NumNxt;		//ENUM Variable for ADC Channel
extern Dac_Num eDac_Num_NextTx;
extern Uc_States eUc_States;
extern const unsigned char InAdc_ChNo[];			//ADC channel numbers in the order given in "InAdc_Num"
extern unsigned char InvRlyPwrOnDlayTmr2, LcdRefreshTmr2;
extern unsigned short ExpTmeCountTmr0, CoolSteTmr1, LineV_Bfor_Expos, LineV_Aftr_Expos, ColimatorTmr2, ColimatorTmeSetVar;
extern signed char CorseCalibValus[];
extern unsigned short SystemSleepTmr2;

#if FIQ
/**
* \brief This function is used to handle timer0 interrupt subroutine.
* 
*	
* \param none
* \return none
*/
void Timr0_Intrupt_Handler(void)				// This is a Fast Interrupt subroutine. It is called in FIQ_Handler()
{
	T0IR = 1;			/* clear interrupt flag for MR0 match iterrupt	*/
	CanScheduleTmr0++;
	AdcReadLockEscTmr0++;
}

#else

/**
* \brief This function is used to handle timer0 interrupt sub routine
* 
*	
* \param none
* \return none
*/
void Timr0_Intrupt_Handler(void) __irq
{
	T0IR = 1;			/* clear interrupt flag for MR0 match iterrupt	*/
	IENABLE;
/*	Application code to describe below.*/ 
	AdcReadLockEscTmr0++;
	ExpTmeCountTmr0++;
/*	Application code to describe untill here.*/ 
	IDISABLE;
	/*	Vector address register. When an IRQ interrupt occurs, the
	Vector Address Register (VICVectAddr) holds the address of the currently
	active interrupt This need to be cleared to acknowledge interrupt	*/
  VICVectAddr = 0;	/* Acknowledge Interrupt */
}

#endif

void Timr1_Intrupt_Handler(void) __irq								// Timer for 5mS
{
	T1IR = 1;			/* clear interrupt flag */
	IENABLE;
/*	Application code to describe below.*/ 
	EnbleSwReleseTmr1++;	EnbleSwPrsTmr1++;	DacUpdatingTmr1++;
	AdcSamplingTmr1++;	WarngSteTmr1++;	PreHitTmr1++;	NvmWriteDelayTmr1++;
	KeyPadScanTmr1++;	CoolSteTmr1++;
/*	Application code to describe untill here.*/ 
	IDISABLE;
	/*	Vector address register. When an IRQ interrupt occurs, the
	Vector Address Register (VICVectAddr) holds the address of the currently
	active interrupt This need to be cleared to acknowledge interrupt	*/
  VICVectAddr = 0;	/* Acknowledge Interrupt */
}


void Timr2_Intrupt_Handler(void) __irq								// Timer for 100mS
{
	T2IR = 1;			/* clear interrupt flag */
//	IENABLE;
/*	Application code to describe below.*/ 
	EnablSteTmr2++;	InvRlyPwrOnDlayTmr2++;	StndbySteTmr2++;	LimitExeedMsgTmr2++;
	KvDecSwPrsTmr2++;	gBeepSoundTmr2++; KvIncSwPrsTmr2++; TmAsIncSwPrsTmr2++; TmAsDecSwPrsTmr2++; mAIncSwPrsTmr2++; mADecSwPrsTmr2++;
	ModeSwPrsTmr2++; PatientSwPrsTmr2++; HBukySwPrsTmr2++; VBukySwPrsTmr2++; ColmtrSwPrsTmr2++; BdyPrtSelSwPrsTmr2++; PresetSwPrsTmr2++;
	SaveSwPrsTmr2++; ViewSwPrsTmr2++; InitSteTmr2++; StatusLedTmr2++; FaultLedTmr2++; EnablLedTmr2++;
	SystemSleepTmr2++;	LcdRefreshTmr2++;	ColimatorTmr2++;
/*	Application code to describe untill here.*/ 
//	IDISABLE;
	/*	Vector address register. When an IRQ interrupt occurs, the
	Vector Address Register (VICVectAddr) holds the address of the currently
	active interrupt This need to be cleared to acknowledge interrupt	*/
  VICVectAddr = 0;	/* Acknowledge Interrupt */
}


/*	The function wait for number of microseconds received through function argument	*/
void Delay_1uSec(unsigned int No_of_1uS)
{
	unsigned long LoopCount;
	LoopCount = No_of_1uS * (unsigned char)Delay_1uS_Cvnt;
	while(LoopCount--);
}

/*	The function wait for number of 100x nanoseconds received through function argument	*/
void Delay_100nSec(unsigned char No_of_100nS)
{
	float LoopCount_flot=0;
	unsigned int LoopCount;
	LoopCount_flot = No_of_100nS * (float)Delay_100nS_Cvnt;
	LoopCount = (unsigned int)LoopCount_flot;
	while(LoopCount--);
}

/*****************************************************************************
** Function name:		ADC0Read
**
** Descriptions:		Read ADC0 channel
**
** parameters:			Channel number
** Returned value:		Value read, if interrupt driven, return channel #
** 
*****************************************************************************/
DWORD ADC0Read( BYTE channelNum )
{
  DWORD regVal, ADC_Data;
	AdcReadLockEscTmr0 = 0;

  /* channel number is 0 through 7 */
  if ( channelNum >= ADC_NUM )
  {
	channelNum = 0;		/* reset channel number to 0 */
  }
  AD0CR &= 0xFFFFFF00;
  AD0CR |= (1 << 24) | (1 << channelNum);	
				/* switch channel,start A/D convert */

  while ( AdcReadLockEscTmr0 < TMR0_500uS_2MS )			/* This is to avoid dead lock condition happens*/
  {
		regVal = *(volatile unsigned long *)(AD0_BASE_ADDR 
				+ ADC_OFFSET + ADC_INDEX * channelNum);
		/* read result of A/D conversion */
		if ( regVal & ADC_DONE )
		{
			break;
		}
  }	
        
  AD0CR &= 0xF8FFFFFF;	/* stop ADC now */    
  if (( regVal & ADC_OVERRUN )||(AdcReadLockEscTmr0 >= TMR0_500uS_2MS))	/* save data when it's not overrun, otherwise, return zero */
  {
		return ( 0 );
  }
  ADC_Data = ( regVal >> 6 ) & 0x3FF;
  return ( ADC_Data );	/* return A/D conversion value */
}


void SlctInAdcChNdSOC()	{	
	static unsigned char LVReadTmr = 0;
	static unsigned int TmptrReadTmr = 0;
	unsigned int TempVar1 = 0, LoopVar = 0, TempVar2 = 0;
	unsigned short AvgPhaseVoltAdc = 0;
	
	if(AdcSamplingTmr1 >= TMR1_5MS_5MS)	{
		eInAdc_Num = eInAdc_NumNxt;
		switch(eInAdc_Num)	{
			case TEMPTR_ADC:	{	
				if(TmptrReadTmr >= TMR1_5MS_100MS)	{						//This timer is for controlling samples per second for each channel
					TempVar1 = ADC0Read((BYTE)InAdc_ChNo[eInAdc_Num]);
					if(TempVar1 != 0x00)	{
						CntrlPrmtrs.AnalogData.Field.TemptrAdcResult = TempVar1;
					}
					TmptrReadTmr = 0;							
				} 
				eInAdc_NumNxt = LINEV_ADC;
			}break;
			
			case LINEV_ADC:	{												//This timer is for controlling samples per second for each channel
				if(LVReadTmr >= TMR1_5MS_20MS)	{
					TempVar1 = ADC0Read((BYTE)InAdc_ChNo[eInAdc_Num]);
					if(TempVar1 != 0x00)	{
						CntrlPrmtrs.AnalogData.Field.LineVAdcResult = TempVar1;
						for(LoopVar = 0; LoopVar < 3; LoopVar++)	{
							PhaseVoltAdcAvgBfr[LoopVar] = PhaseVoltAdcAvgBfr[LoopVar + 1];											//Shifting old samples to add new sample
							TempVar2 += PhaseVoltAdcAvgBfr[LoopVar];																		//Adding sample to the sum
							PhaseVoltAdcAvgBfr[LoopVar + 1] = CntrlPrmtrs.AnalogData.Field.LineVAdcResult;		//Collecting new sample value; this can avoid one if loop
						}
						TempVar2 += PhaseVoltAdcAvgBfr[LoopVar];					//Adding new sample to the sum
						AvgPhaseVoltAdc = TempVar2 >> 2;								//Divide by 4 as 4 saples are used for averaging
						PhaseVoltAdcAvgBfr[LoopVar] = AvgPhaseVoltAdc;
						PhaseVoltDispVal = AvgPhaseVoltAdc/PHASE_VOLT_CONVRT_FACTOR;
						PhaseVoltDispVal = PhaseVoltDispVal + CorseCalibValus[IPVOLT_DISPADJ_PTR - CALIBmAFIL_STATION1_PTR];
					}
					LVReadTmr = 0;	
				}
				eInAdc_NumNxt = END_OF_INADC;
			} break;			
			
			case END_OF_INADC:	{	
				LVReadTmr++;
				TmptrReadTmr++;	
				AdcSamplingTmr1 = 0;
				eInAdc_NumNxt = TEMPTR_ADC;
			} break;
			
			default:	{
				eInAdc_NumNxt = TEMPTR_ADC;
			}break;
		}
	}
}

/*	The function is used to update the DAC in virtual poling methode	*/
unsigned char WriteDAC(Dac_Num eDac_Num)	{
	static unsigned int dac_val=0,Dac_byte_Sts = DAC_DATA_FINISHED;
	
	/* Move on only if NOT busy and TX FIFO is empty. */
	if(((SSP1SR & (SSPSR_TFE|SSPSR_BSY)) == SSPSR_TFE )&&(Dac_byte_Sts == DAC_DATA_FINISHED))	{
		switch(eDac_Num)		{
			case SET_LCD_CNTRAST: {
						DAC_SSEL1_Dat(LLOW);
						DAC_LDAC_Dat(HHIGH);
						dac_val = LCDC_DAC_CW | CntrlPrmtrs.AnalogData.Field.LcdContrastDacLodNo;
						SSP1DR = dac_val;
			} break;
//			case SET_KV_REF: {
//						DAC_SSEL1(LLOW);
//						DAC_SSEL2(HHIGH);
//						DAC_LDAC(HHIGH);
//						dac_val = KV_DAC_CW | CntrlPrmtrs.CcDtC.Field.KvRefDacLodNo;
//						SSP1DR = dac_val;
//			} break;
//			case SET_mA_REF: {
//						DAC_SSEL1(HHIGH);
//						DAC_SSEL2(LLOW);
//						DAC_LDAC(HHIGH);
//						dac_val = mA_DAC_CW | CntrlPrmtrs.CcDtC.Field.mARefDacLodNo;
//						SSP1DR = dac_val;
//			} break;
		}
		Dac_byte_Sts = DAC_DATA_INITIATED;
	}
	/* this else part is to do transitions in the chip select and DAC load values	*/
	else {
		if((Dac_byte_Sts == DAC_DATA_INITIATED) && ((SSP1SR & (SSPSR_TFE|SSPSR_BSY)) == SSPSR_TFE))	{
			DAC_SSEL1_Dat(HHIGH);
			DAC_LDAC_Dat(LLOW);
			Delay_1uSec(1);			//Wait for 1uS; The Function argument can receive 1 to 255.
			DAC_LDAC_Dat(HHIGH);
			Dac_byte_Sts = DAC_DATA_FINISHED;		//Indicating that transfer activities of last data is finished.
		}		
	}
	return Dac_byte_Sts;
}


void DacLoadScheduler()
{
	static unsigned char LastDataSts = DAC_DATA_FINISHED;
	
	if(DacUpdatingTmr1 >= TMR1_5MS_100MS)	{
		LastDataSts = WriteDAC(eDac_Num_NextTx);		
		if(LastDataSts == DAC_DATA_FINISHED)	{
			eDac_Num_NextTx++;
			if(eDac_Num_NextTx >= END_OF_REF) {	
				eDac_Num_NextTx = SET_LCD_CNTRAST;	
				DacUpdatingTmr1 = 0;
			}
		}
	}	
}


/*	Update Collimator, Horizontal Bucky and Vertical Bucky	*/
void	UpdateXrayPeripherals(void)
{
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag == TRUEE)
	{
		if(CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts == HHIGH)	{
			COLLIMATOR_uC_Dat(HHIGH);
			ColimatorTmr2 = 0;
		}
		else	{
			COLLIMATOR_uC_Dat(LLOW);
		}
		if((CntrlPrmtrs.KeyPadFn2Sts.Field.V_BuckySts == HHIGH)&&((eUc_States == ENABLE_STATE)||(eUc_States == EXPOSURE_STATE)))	{
			VERTICAL_BUCKY_uC_Dat(HHIGH);
		}
		else	{
			VERTICAL_BUCKY_uC_Dat(LLOW);
		}
		if((CntrlPrmtrs.KeyPadFn2Sts.Field.H_BuckySts == HHIGH)&&((eUc_States == ENABLE_STATE)||(eUc_States == EXPOSURE_STATE)))	{
			HORIZ_BUCKY_uC_Dat(HHIGH);
		}
		else	{
			HORIZ_BUCKY_uC_Dat(LLOW);
		}		
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = FALSEE;
	}
}

/*	Update LEDs in the systems	*/
void UpdateLED(void)
{
	unsigned char TempVar = 0;
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag == TRUEE)
	{
		TempVar = ((CntrlPrmtrs.IntraSysCtrlDat.all >> 16)&0xff);
		LED_PORT_uC = ~TempVar;																						//LOW to ON LED
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = FALSEE;
	}	
}

void CalculateLineRes()
{
	unsigned short ExposdOutPower = 0;
	char DeltaInputV = 0;
	float LineResistance = 0, InputCurrent = 0;
	
	if((LineV_Aftr_Expos != 0x00)&&(OutputKvLastExpos != 0x00)&&(OutputmALastExpos != 0x00))	{
		DeltaInputV = abs(LineV_Bfor_Expos - LineV_Aftr_Expos);
		ExposdOutPower = OutputKvLastExpos * OutputmALastExpos;
		InputCurrent = ExposdOutPower / LineV_Aftr_Expos;
		LineResistance = (float)DeltaInputV / InputCurrent;
		LineResx10 = (unsigned char)(LineResistance * 10);
	}
}

void AutoShutDownColimtr()
{
	if(CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrTmrEn == TRUEE)	{
		if(ColimatorTmeSetVar < ColimatorTmr2)	{
			CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = FALSEE;
			CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = FALSEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
		}
	}
}



