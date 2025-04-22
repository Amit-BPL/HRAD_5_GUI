#include "ConfigureUc.h"


/**
* \brief This function is used to set the functioning of each PIN 
* The functions called inside this function SET the operating function of respective PIN
* Each PIN function receives 0-3;ie., 4 options in every PIN.
* \param none
* \return none
*/
void PinFunctnSel()	{
	GuicPinNo_94_Fn(1);					//CAN
	GuicPinNo_96_Fn(1);					//CAN
	GuicPinNo_164_Fn(2);				//SPI1
	GuicPinNo_162_Fn(2);				//SPI1
	GuicPinNo_158_Fn(2);				//SPI1
	GuicPinNo_41_Fn(3);					//ADC0
	GuicPinNo_69_Fn(0);
	GuicPinNo_120_Fn(0);				//UART1 DIRECTION CONTROL but GPIO
	GuicPinNo_177_Fn(0);
	GuicPinNo_171_Fn(0);
	GuicPinNo_188_Fn(0);
	GuicPinNo_186_Fn(0);
	GuicPinNo_163_Fn(0);
	GuicPinNo_184_Fn(0);
	GuicPinNo_182_Fn(0);
	GuicPinNo_180_Fn(0);
	GuicPinNo_178_Fn(0);
	GuicPinNo_70_Fn(0);
	GuicPinNo_42_Fn(0);
	GuicPinNo_40_Fn(0);
	GuicPinNo_187_Fn(0);
	GuicPinNo_111_Fn(0);
	GuicPinNo_105_Fn(0);
	GuicPinNo_159_Fn(0);
	GuicPinNo_155_Fn(0);
	GuicPinNo_149_Fn(0);
	GuicPinNo_145_Fn(0);
	GuicPinNo_135_Fn(0);
	GuicPinNo_131_Fn(0);
	GuicPinNo_127_Fn(0);
	GuicPinNo_121_Fn(0);
	GuicPinNo_107_Fn(0);
	GuicPinNo_97_Fn(0);
	GuicPinNo_83_Fn(0);
	GuicPinNo_25_Fn(0);
	GuicPinNo_19_Fn(0);
	GuicPinNo_28_Fn(0);
	GuicPinNo_21_Fn(0);
	GuicPinNo_7_Fn(0);
	GuicPinNo_1_Fn(0);
	GuicPinNo_208_Fn(0);
	GuicPinNo_205_Fn(0);
	GuicPinNo_199_Fn(0);
	GuicPinNo_191_Fn(0);
	GuicPinNo_27_Fn(0);
	GuicPinNo_23_Fn(0);
	GuicPinNo_17_Fn(0);
	GuicPinNo_13_Fn(0);
	GuicPinNo_3_Fn(0);
	GuicPinNo_207_Fn(0);
	GuicPinNo_201_Fn(0);
	GuicPinNo_197_Fn(0);
	GuicPinNo_110_Fn(0);
	GuicPinNo_152_Fn(2);					//UART1
	GuicPinNo_154_Fn(2);					//UART1
}

/**
* \brief This function is used to set Mode of each PIN 
* The functions called inside this function SET the Pullup/Pulldown of each pin
* Each PIN function receives 0-3;ie., 4 options in every PIN.
*	0-Pullup;	1-Reserved;	2-Pin without Pull/Down;	3-Pulldown
* \param none
* \return none
*/
void PinModeSel()	{
	GuicPinNo94_Mod(0);
	GuicPinNo96_Mod(0);
	GuicPinNo164_Mod(0);
	GuicPinNo162_Mod(0);
	GuicPinNo158_Mod(0);
	GuicPinNo41_Mod(0);
	GuicPinNo69_Mod(0);
	GuicPinNo120_Mod(0);
	GuicPinNo177_Mod(0);
	GuicPinNo171_Mod(0);
	GuicPinNo188_Mod(0);
	GuicPinNo186_Mod(0);
	GuicPinNo163_Mod(0);
	GuicPinNo184_Mod(0);
	GuicPinNo182_Mod(0);
	GuicPinNo180_Mod(0);
	GuicPinNo178_Mod(0);
	GuicPinNo70_Mod(0);
	GuicPinNo42_Mod(0);
	GuicPinNo40_Mod(0);
	GuicPinNo187_Mod(0);
	GuicPinNo111_Mod(0);
	GuicPinNo105_Mod(0);
	GuicPinNo159_Mod(0);
	GuicPinNo155_Mod(0);
	GuicPinNo149_Mod(0);
	GuicPinNo145_Mod(0);
	GuicPinNo135_Mod(0);
	GuicPinNo131_Mod(0);
	GuicPinNo127_Mod(0);
	GuicPinNo121_Mod(0);
	GuicPinNo107_Mod(0);
	GuicPinNo97_Mod(0);
	GuicPinNo83_Mod(0);
	GuicPinNo25_Mod(0);
	GuicPinNo19_Mod(0);
	GuicPinNo28_Mod(0);
	GuicPinNo21_Mod(0);
	GuicPinNo7_Mod(0);
	GuicPinNo1_Mod(0);
	GuicPinNo208_Mod(0);
	GuicPinNo205_Mod(0);
	GuicPinNo199_Mod(0);
	GuicPinNo191_Mod(0);
	GuicPinNo27_Mod(0);
	GuicPinNo23_Mod(0);
	GuicPinNo17_Mod(0);
	GuicPinNo13_Mod(0);
	GuicPinNo3_Mod(0);
	GuicPinNo207_Mod(0);
	GuicPinNo201_Mod(0);
	GuicPinNo197_Mod(0);
	GuicPinNo110_Mod(0);
	GuicPinNo152_Mod(0);
	GuicPinNo154_Mod(0);
}

/**
* \brief This function is used to set the direction and other configurations
* The functions called inside this function SET the direction of respective PIN
* Each PIN function receives 0-1;ie., 2 options in every PIN.
*	0- Input and 1- Output
* \param none
* \return none
*/
void ConfigGPIO()	{
	GuicPinNo94_Dir(0);
	GuicPinNo96_Dir(1);
	GuicPinNo164_Dir(1);
	GuicPinNo162_Dir(1);
	GuicPinNo158_Dir(1);
	GuicPinNo41_Dir(0);
	GuicPinNo69_Dir(1);
	GuicPinNo120_Dir(1);
	GuicPinNo177_Dir(1);
	GuicPinNo171_Dir(1);
	GuicPinNo188_Dir(0);
	GuicPinNo186_Dir(0);
	GuicPinNo163_Dir(1);
	GuicPinNo184_Dir(1);
	GuicPinNo182_Dir(1);
	GuicPinNo180_Dir(1);
	GuicPinNo178_Dir(1);
	GuicPinNo70_Dir(1);
	GuicPinNo42_Dir(0);
	GuicPinNo40_Dir(0);
	GuicPinNo187_Dir(1);
	GuicPinNo111_Dir(0);
	GuicPinNo105_Dir(0);
	GuicPinNo159_Dir(1);
	GuicPinNo155_Dir(1);
	GuicPinNo149_Dir(1);
	GuicPinNo145_Dir(1);
	GuicPinNo135_Dir(1);
	GuicPinNo131_Dir(1);
	GuicPinNo127_Dir(1);
	GuicPinNo121_Dir(1);
	GuicPinNo107_Dir(1);
	GuicPinNo97_Dir(1);
	GuicPinNo83_Dir(1);
	GuicPinNo25_Dir(0);
	GuicPinNo19_Dir(0);
	GuicPinNo28_Dir(1);
	GuicPinNo21_Dir(1);
	GuicPinNo7_Dir(1);
	GuicPinNo1_Dir(1);
	GuicPinNo208_Dir(1);
	GuicPinNo205_Dir(1);
	GuicPinNo199_Dir(1);
	GuicPinNo191_Dir(1);
	GuicPinNo27_Dir(1);
	GuicPinNo23_Dir(1);
	GuicPinNo17_Dir(1);
	GuicPinNo13_Dir(1);
	GuicPinNo3_Dir(0);
	GuicPinNo207_Dir(0);
	GuicPinNo201_Dir(0);
	GuicPinNo197_Dir(0);
	GuicPinNo110_Dir(0);
	GuicPinNo152_Dir(0);
	GuicPinNo154_Dir(1);
}

/**
* \brief This function is used to set Initial logic levels of output GPIO
* The functions called inside this function SET the value of respective PIN
* 
*	
* \param none
* \return none
*/
void InitCcGPIO()	{
	DAC_SSEL1_Dat(1);
	DAC_LDAC_Dat(1);
	RS485_RE_TE_Dat(0);
	XRAY_ON_CMD_uC_Dat(0);
	BEEP_TOUCH_Dat(0);
	CONSOLE_STS_uC_Dat(1);
	HV_85_PRCNT_LED_Uc_Dat(1);
	VERTICAL_BUCKY_uC_Dat(0);
	HORIZ_BUCKY_uC_Dat(0);
	COLLIMATOR_uC_Dat(0);
	POWER_SHUTDOWN_UC_Dat(0);
	POWER_SW_LED_uC_Dat(1);
	LCD_LSIC_EN_Dat(1);
	LCD_D3_uC_Dat(0);
	LCD_D2_uC_Dat(0);
	LCD_D1_uC_Dat(0);
	LCD_D0_uC_Dat(0);
	LCD_EN_uC_Dat(0);
	LCD_RW_uC_Dat(0);
	LCD_RS_uC_Dat(1);
	XRAY_READY_uC_Dat(0);
	FAULT_LED_uC_Dat(0);
	STATUS_LED_uC_Dat(1);
	PRESEL_LED_uC(1);
	ERROR_LED_uC(1);
	COLIM_LED_uC(1);
	VBUKY_LED_uC(1);
	HBUKY_LED_uC(1);
	EXPOS_LED_uC(1);
	READY_LED_uC(1);
	SPARE_LED_uC(1);
	KYPAD_COLMN3_uC(1);
	KYPAD_COLMN2_uC(1);
	KYPAD_COLMN1_uC(1);
	KYPAD_COLMN0_uC(1);
//	KYPAD_COLMN_uC(0x0F);
	LED_PORT_uC	= 0xFF;
}

/**
* \brief This function is used to configure GPIO and hardware PINs
* This function calls the functions which sets pin function, GPIO configurations
* Pin mode selections and initialisation of GPIOs.
*	
* \param none
* \return none
*/
void ConfigPorts(void)	{
	SCS |= 0x01;	/* This statement is required to enable Fast GPIO in Port0 and 1 */
	PinFunctnSel();
	ConfigGPIO();
	PinModeSel();
	InitCcGPIO();
}

/**
* \brief This function is used to configure ADC
* 
*	
* \param none
* \return none
*/
void ConfigADC()	{
	PCONP |= (1 << 12);	// Enable clock to the peripheral
	Delay_1uSec(1);
	AD0CR |= (1 << 21);
	
#if (Fpclk / (Fcclk / 4)) == 1		/* PCLK is 1/4 CCLK */
	AD0CR |= 0xB00;		//1MHz Clock; No Burst mode; 10bit data selected; Software intiate convertion
#elif (Fpclk / (Fcclk / 4)) == 2	/* PCLK is 1/2 CCLK */
	AD0CR |= 0x1700;		//1MHz Clock; No Burst mode; 10bit data selected; Software intiate convertion
#elif (Fpclk / (Fcclk / 4)) == 4	/* PCLK is the same as CCLK */
	AD0CR |= 0x2F00;		//1MHz Clock; No Burst mode; 10bit data selected; Software intiate convertion
#elif ((Fcclk / 4)/Fpclk) == 2		/* PCLK is 1/8 CCLK */
	AD0CR |= 0x500;		//1MHz Clock; No Burst mode; 10bit data selected; Software intiate convertion
#endif	
	AD0GDR = 0x00;
	AD0STAT = 0x00;
//	AD0INTEN = 0x100;				// Global DONE bit enables the Interrupt.
//	AD0DR3 = 0x00;
//	AD0DR6 = 0x00;
}

/**
* \brief This function is used to configure SPI1 module
* 
*	
* \param none
* \return none
*/
void ConfigSPI1()	{
#if (Fpclk / (Fcclk / 4)) == 1		/* PCLK is 1/4 CCLK */	
	SSP1CPSR = 0x02;							//Clock Prescale Register for 3MHz
	SSP1CR0 = ((1 << 8)| 0x0f);			//Control Register 0; 16 bit communication; 3MHz clock; SPI; LOW to HIGH clock
#elif (Fpclk / (Fcclk / 4)) == 2	/* PCLK is 1/2 CCLK */
	SSP1CPSR = 0x02;							//Clock Prescale Register for 3MHz
	SSP1CR0 = ((3 << 8)| 0x0f);			//Control Register 0; 16 bit communication; 3MHz clock; SPI; LOW to HIGH clock	
#elif (Fpclk / (Fcclk / 4)) == 4	/* PCLK is the same as CCLK */
	SSP1CPSR = 0x04;							//Clock Prescale Register for 3MHz
	SSP1CR0 = ((3 << 8)| 0x0f);			//Control Register 0; 16 bit communication; 3MHz clock; SPI; LOW to HIGH clock
#elif ((Fcclk / 4)/Fpclk) == 2		/* PCLK is 1/8 CCLK */
	SSP1CPSR = 0x02;							//Clock Prescale Register for 3MHz
	SSP1CR0 = ((0 << 8)| 0x0f);			//Control Register 0; 16 bit communication; 3MHz clock; SPI; LOW to HIGH clock
#endif	

	SSP1DR = 0x00;								//Data Register
//	SSP1SR = 0x00;								//Status Register	- Read Only	
//	SSP1IMSC = 0x00;							//Interrupt Mask Set/Clear Register 
//	SSP1RIS  = 0x00;							//Raw Interrupt Status Register
//	SSP1MIS = 0x00;								//Masked Interrupt Status Register
//	SSP1ICR = 0x00;								//Interrupt Clear Register
//	SSP1DMACR = 0x00;							//DMA Control Register	
//	Following register need to be loaded after all other configurations
	SSP1CR1 = 0x02;								//Control Register 1; bit0 loop back mode; bit1 SSE enable; Bit2 Master(0)/slave(1) select; 
}

/**
* \brief This function is used to configure Timer0 module
* 
*	
* \param none
* \return none
*/
void ConfigTimer0()
{
	T0PR = TIMER0_PRSET_COUNT;
	T0MR0 = TIMER0_MATCHSET_COUNT;
	T0MR1 = TIMER0_MATCHSET_COUNT;
	T0MCR = 0x011;									//	Timer0 reset on match with T0MR1 and generate interrupt on match with T0MR0
	T0TCR = 0x01;										//	Enable Timer0	
}

/**
* \brief This function is used to configure Timer1 module
* 
*	
* \param none
* \return none
*/
void ConfigTimer1()
{
	T1PR = TIMER1_PRSET_COUNT;
	T1MR0 = TIMER1_MATCHSET_COUNT;
	T1MR1 = TIMER1_MATCHSET_COUNT;
	T1MCR = 0x011;									//	Timer1 reset on match with T1MR1 and generate interrupt on match with T1MR0
	T1TCR = 0x01;										//	Enable Timer1
}

/**
* \brief This function is used to configure Timer2 module
* 
*	
* \param none
* \return none
*/
void ConfigTimer2()
{
	PCONP |= (1 << 22);	// Enable clock to the peripheral
	T2PR = TIMER2_PRSET_COUNT;
	T2MR0 = TIMER2_MATCHSET_COUNT;
	T2MR1 = TIMER2_MATCHSET_COUNT;
	T2MCR = 0x011;									//	Timer2 reset on match with T2MR1 and generate interrupt on match with T2MR0
	T2TCR = 0x01;										//	Enable Timer2		
}


/**
* \brief This function is used to configure UART1 module for RS485 communication
* 
*	
* \param none
* \return none
*/
void ConfigRs485()
{
	unsigned int v_regValue_u32;
	
	U1LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit,DLAB = 1 */
//	Set Baud Rate
	v_regValue_u32 = Fpclk/(16*RS485_CH1_BAUDRATE);
	U1DLL = v_regValue_u32 & 0xff;            /* Lower 8bit baud rate generator value*/
	U1DLM = (v_regValue_u32 >> 0x08) & 0xff;  /* Higher 8bit baud rate generator value*/
//	End of Set Baud Rate
	U1LCR = 0x2B;                   /* DLAB = 0 ; Enable 9th bit as Address bit (STICK 1 PARITY is used)*/
//		U1LCR = 0x03;                   /* DLAB = 0 ; Enable 9th bit as Address bit (STICK 1 PARITY is used)*/
	U1FCR = 0x07;
	U1TER = 0x00;					//19Y07M02D
}

/**
* \brief This function is used to call functions which configures
*  the peripherals used in this firmware. It is called from mains()
*	
* \param none
* \return none
*/
void ConfigPeripherals(void)	{
	ConfigADC();
	ConfigSPI1();
	InitFlashSsp();
	ConfigTimer0();
	ConfigTimer1();
	ConfigTimer2();
	ConfigRs485();
}

/******************************************************************************
** Function name:		ConfigurePLL
**
** Descriptions:		Configure PLL switching to main OSC instead of IRC
**						at power up and wake up from power down. 
**						This routine is used in TargetResetInit() and those
**						examples using power down and wake up such as
**						USB suspend to resume, ethernet WOL, and power management
**						example
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void ConfigurePLL ( void )
{
  DWORD MValue, NValue;

  if ( PLLSTAT & (1 << 25) )
  {
	PLLCON = 1;			/* Enable PLL, disconnected */
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
  }

  PLLCON = 0;				/* Disable PLL, disconnected */
  PLLFEED = 0xaa;
  PLLFEED = 0x55;
    
  SCS |= 0x20;			/* Enable main OSC */
  while( !(SCS & 0x40) );	/* Wait until main OSC is usable */

  CLKSRCSEL = 0x1;		/* select main OSC, 12MHz, as the PLL clock source */

  PLLCFG = PLL_MValue | (PLL_NValue << 16);
  PLLFEED = 0xaa;
  PLLFEED = 0x55;
      
  PLLCON = 1;				/* Enable PLL, disconnected */
  PLLFEED = 0xaa;
  PLLFEED = 0x55;

  CCLKCFG = CCLKDivValue;	/* Set clock divider */
#if USE_USB
  USBCLKCFG = USBCLKDivValue;		/* usbclk = 288 MHz/6 = 48 MHz */
#endif

  while ( ((PLLSTAT & (1 << 26)) == 0) );	/* Check lock bit status */
    
  MValue = PLLSTAT & 0x00007FFF;
  NValue = (PLLSTAT & 0x00FF0000) >> 16;
  while ((MValue != PLL_MValue) && ( NValue != PLL_NValue) );

  PLLCON = 3;				/* enable and connect */
  PLLFEED = 0xaa;
  PLLFEED = 0x55;
  while ( ((PLLSTAT & (1 << 25)) == 0) );	/* Check connect bit status */
  return;
}

void ConfigPerphClk()
{
	  /* Set system timers for each component */
#if (Fpclk / (Fcclk / 4)) == 1
  PCLKSEL0 = 0x00000000;	/* PCLK is 1/4 CCLK */
  PCLKSEL1 = 0x00000000;
//#endif
#elif (Fpclk / (Fcclk / 4)) == 2
  PCLKSEL0 = 0xAAAAAAAA;	/* PCLK is 1/2 CCLK */
  PCLKSEL1 = 0xAAAAAAAA;	 
//#endif
#elif (Fpclk / (Fcclk / 4)) == 4
  PCLKSEL0 = 0x55555555;	/* PCLK is the same as CCLK */
  PCLKSEL1 = 0x55555555;	
#elif ((Fcclk / 4)/Fpclk) == 2
	PCLKSEL0 = 0xFFFFFFFF;	/* PCLK is 1/8 CCLK */
  PCLKSEL1 = 0xFFFFFFFF;
#endif	
}


void ConfigSystm(void)
{
	ConfigurePLL();	
	ConfigPerphClk();
}

void InitVariables()
{
	unsigned short TempVar = 0, TempVar_KV = 0;
	unsigned short ArrayRowAdrsOfset = 0, ArrayColAdrsOfset =0;
//	All Categories Reset
	CntrlPrmtrs.ErrFlds.all = 0x00;
	CntrlPrmtrs.AnalogData.all = 0x00;
	CntrlPrmtrs.KeyPadFn1Sts.all = 0x00;		//Operating mode Manual, Adult XL, Skull, PA_view, Preset disabled
	CntrlPrmtrs.KeyPadFn2Sts.all = 0x00;		//Disable Collimator and bucky, Film type and density reset to zero.
	CntrlPrmtrs.IntraSysCtrlDat.all = 0x00;	//All LEDs status are off condition.	
	CntrlPrmtrs.KeyPadSwGp1IntLok.all = 0x00;
	CntrlPrmtrs.KeyPadSwGp1Sts.all = 0x00;
	CntrlPrmtrs.KeyPadSwGp2IntLok.all = 0x00;
	CntrlPrmtrs.KeyPadSwGp2Sts.all = 0x00;
	
	EnbleSwReleseTmr1 = 0;	EnbleSwPrsTmr1 = 0;
	KvDecSwPrsTmr2 = 0;	gBeepSoundTmr2 = 0; KvIncSwPrsTmr2 = 0; TmAsIncSwPrsTmr2 = 0; TmAsDecSwPrsTmr2 = 0; mAIncSwPrsTmr2 = 0; mADecSwPrsTmr2 = 0;
	ModeSwPrsTmr2 = 0; PatientSwPrsTmr2 = 0; HBukySwPrsTmr2 = 0; VBukySwPrsTmr2 = 0; ColmtrSwPrsTmr2 = 0; BdyPrtSelSwPrsTmr2 = 0; PresetSwPrsTmr2 = 0;
	SaveSwPrsTmr2 = 0; ViewSwPrsTmr2 = 0;		
	PopPowerModeKey();
	CheckLowPwrModeKey();
	if(LowPowerModeLockVar == LOWPWR_MODE_LOCK_VALUE)	{
		KvmAs_mA_Table_Ptr = (unsigned char*)KvmAs_mA_Table_LPMode;
	}
	else {
		KvmAs_mA_Table_Ptr = (unsigned char*)KvmAs_mA_Table;
	}
	
	PopLastCalibPointer();
	PopLastExposeProtocol();
	FirstBootRegstr = CheckFirstBoot();					//@@@@@@@@@@@@@@@@
	if(LowPowerModeLockVar == LOWPWR_MODE_LOCK_VALUE)	{			//21Y09M25D
//	This block of code is to avoid showing 000 in mA field when enter from full power mode to LP stage.	
		TempVar_KV = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - KV_MIN_LIMIT;
		ArrayRowAdrsOfset = TempVar_KV * mASPTR_LIST_MAX;
		ArrayColAdrsOfset = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mASPTR_LIST_MIN;
		Present_mA_Ptr = KvmAs_mA_Table_Ptr + ArrayRowAdrsOfset + ArrayColAdrsOfset;
		while(*Present_mA_Ptr == 0)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt--;
			Present_mA_Ptr--;
		};
	}	
	CntrlPrmtrs.PresentSetmAsx10 = StdmAsValues[CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt];	//Initialise 12.5mAs
	ArrayRowAdrsOfset = (CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - KV_MIN_LIMIT)*mASPTR_LIST_MAX;
	ArrayColAdrsOfset = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mAPTR_LIST_MIN;
	Present_mA_Ptr = KvmAs_mA_Table_Ptr + ArrayRowAdrsOfset + ArrayColAdrsOfset;
	TempVar = *Present_mA_Ptr;
//	TempVar = KvmAs_mA_Table[CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - KV_MIN_LIMIT][CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mAPTR_LIST_MIN];
	CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = FndOrdinalNumOfShortArr(StationsOfmA,mAPTR_LIST_MAX+1,TempVar);
	CntrlPrmtrs.PresentSetmA = StationsOfmA[CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt];		//Initialise mA as 500mA.
	CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = ((CntrlPrmtrs.PresentSetmAsx10 *100) / CntrlPrmtrs.PresentSetmA);
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
	
//	LCD Related
	CntrlPrmtrs.AnalogData.Field.LcdContrastDacLodNo = 700;			//Initialising LCD Contrast value. 1 count = 1mV
	CntrlPrmtrs.IntraSysCtrlDat.all |= 0xff ;										//This is to update all the LCD fields in APR mode	
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
	
//	LED Related	
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag =TRUEE;
//	RS485 Related
	CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxFrmOvr = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxFrmOvr = TRUEE;	
	Rs485RxBuffPtr = Rs485RxBuffr;	//Load the Buffer Base Address to the pointer
	Rs485TxBuffPtr = Rs485TxBuffr;	//Load the Buffer Base Address to the pointer
	Rs485RxFrame.PACK_2.Field.PtcBypassRelySts = ENABLE;	//This is to assign untill first frame is received from supervisor.
	
	if((DIP_SW2_uC == LLOW)&&(DIP_SW1_uC == LLOW))	{
		LineVoltChekAbort = 0xFF;
	}
	else	{
		LineVoltChekAbort = 0x00;
	}
}


