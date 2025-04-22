/*	@PROJECT	: BPL-HRAD50																																//
	@SUB PART	: HRAD50 CONTROL CARD																													//
	@FIRMWARE No: 417_FW_01 control Card Firmware																						//
	@REVISION	: R0xA																																				//
	@FILE 		: States.h																																		//
	@SCHEMATIC	: 417-S-001 Rev01																														//
	@AUTHER		: BABURAJ C.G.																																//
	@CODING START DATE	:25 MAY 2018																												//
	@LAST UPDATE DATE	:																																			//
																																													//
	@AIM OF FIRMWARE: This project is intended to produce X-RAY having the variable 				//
				exposure parameters, as given below:																							//
				Tube Current	:	10mA to 600mA	(50kW Radiography)																	//
				Tube Voltage	:	40kv to 150kv 																										//
				The Duties of Control Card is listed below:																				//
				*	Send and Receive CAN command between GUI card																		//
				*	Act as supervisor and mediator between GUI and Generator												//
				*	Check	Faults in all cards	and control card it self															//
				*	Turn ON/OFF Inverter, Relay and contactors of Bucky															//
	@AIM OF FILE: This file contains the source code for Mains functions and interrupts			//
*/																				//
////////////////////////////////////////////////////////////////////////////////////////////




//#include "LPC23xx.h"                        /* LPC23xx/24xx definitions */
#include "GUICMain.h"
#include <stdio.h>


int main()
{
	ConfigSystm();
	ConfigPorts();
	ConfigInterrupt();
	ConfigPeripherals();
	lcd_init();
	eUc_States = INIT_STATE;
	eLastUc_States = INIT_STATE;
	while(1)
	{
		switch(eUc_States)	{
			case INIT_STATE:    {   
				if(SystemSleepTmr2 >= TMR2_100MS_30MINUTES)	{
					SleepModeFn();
				}
				InitStateFn();
				break;
			}
			case STANDBY_STATE:{
				StandbyStateFn();				//Call statnd by state
				break;
			}
			case ENABLE_STATE:{
				EnableStateFn();				//Call Menu set state
				break;
			}
			case EXPOSURE_STATE:{
				ExposureStateFn();			//Call RampUp state
				break;
			}
			case COOLING_STATE:{
				CoolingStateFn();				//State when Current
				break;									//limit happen
			}
			case WARNING_STATE:{
				WarningStateFn();				//State when Current
				break;									//limit happen
			}
			case FAULT_STATE:{
				FaultStateFn();					//call fault state on
				break;									//error
			}            
			case CALIB_STATE:{
				CalibStateFn();					//call calib state on
				break;									//calibration
			}
			default:{
				FaultStateFn();					//ned state error
				break;
			}			
		}		
	};	
}


void SleepModeFn()	{
	DWORD TempVar = 0, TempLcdRefresh = 0;
	unsigned char  TempStsLedVar=0;
	signed char TempVarSc = 10;
	SleepScreenLCD(0x00);
	InvRlyPwrOnDlayTmr2 = 0;
	CntrlPrmtrs.ErrFlds.all = 0x00;
	LcdRefreshTmr2 = 0;
	while(SystemSleepTmr2 >= TMR2_100MS_30MINUTES)
	{
		SystemSleepTmr2 = TMR2_100MS_30MINUTES + 1;
		//At every 100 Ms Check
		if(TempVar != InitSteTmr2)	
		{				//For animation in the LCD
			CntrlPrmtrs.AnalogData.Field.LcdContrastDacLodNo += (signed char)TempVarSc;
			/* At After first 450 sec  go to if condition and display*/ 
			if(CntrlPrmtrs.AnalogData.Field.LcdContrastDacLodNo > 1500)	
			{
				TempVarSc = -10;
				if(TempLcdRefresh == 0xFF)	
				{	
					SleepScreenLCD(0xFF);            // Display the message "Restart the machine to boot up"
				}
			}
			else if(CntrlPrmtrs.AnalogData.Field.LcdContrastDacLodNo < 600)	{
				TempVarSc = 10;
			}
			TempVar = InitSteTmr2;
		}
//		if(TempLcdRefresh == 0xFF)	{		//This block of code is required if sleep mode exit on any key press situation
//			ScanKeyPadMatrix();
//			ScanIndpndntKeys();
//		}
		Rs485TxDataFn();     // call Rs485 Communication transmission
		Rs485RxDataFn();     // call RS485 communication and received values are arranged the correct variables
		UpdtRs485Txdata();   // call Rs485 Communication if any changes occurs by users update and save it
		if(Rs485RxFrame.PACK_2.Field.PtcBypassRelySts == DISABLE) {
			POWER_SHUTDOWN_UC_Dat(LLOW);					//HIGH:Turn ON contactor;	LOW:Turn OFF contactor
			if((TempLcdRefresh == 0)&&(LcdRefreshTmr2 > TMR2_100MS_2000MS))	{	// This timer variable is for avoiding noise while contactor switching.
				SleepScreenLCD(0xFF);
				TempLcdRefresh = 0xFF;
			}
		}
		else	{
			LcdRefreshTmr2 = 0;			// This timer variable is for avoiding noise while contactor switching.
		}
		DacLoadScheduler();
		
	}
	
	LcdRefreshTmr2 = TMR2_LCD_REFRESH_TME + 2;
	if(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME)	{
			lcd_clear();									//This is required for clearing Initialising screen
			CntrlPrmtrs.IntraSysCtrlDat.all |= 0xFF; 	//For refreshing LCD normal screen		
			DispStatusLineLCD(TempStsLedVar);
			LcdRefreshTmr2 = 0;
		}
}

void InitStateFn()	{
	unsigned char ContactrOnLockVar = 0 , TempStsLedVar = 0;
	static unsigned char FullFlashPopFinish = 0;
	DWORD TempVar = 0;
	lcd_init();
	InitVariables();
	PopCorseCalibGain();
	DispInitScreenLCD();
	LcdRefreshTmr2 = TMR2_LCD_REFRESH_TME - 4;
	if(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME)	{
			lcd_clear();									//This is required for clearing Initialising screen
			CntrlPrmtrs.IntraSysCtrlDat.all |= 0xFF; 	//For refreshing LCD normal screen		
			DispStatusLineLCD(TempStsLedVar);
			LcdRefreshTmr2 = 0;
		}
	DispInitScreenLCD();
		
	if(eLastUc_States != INIT_STATE)	{		//This is to avoid the booting message hanging while return from sleep mode
		ConfigPeripherals();
	}
	InitSteTmr2 = 0;
	InvRlyPwrOnDlayTmr2 = 0;
	CntrlPrmtrs.ErrFlds.all = 0x00;
	while(eUc_States == INIT_STATE)
	{
		SystemSleepTmr2 = 0;
		if(TempVar != InitSteTmr2)	{				//For animation in the LCD
			ShowWaitStsLcd(4,11,4);						//Starting Location and number of dots
			TempVar = InitSteTmr2;
		}
		ScanKeyPadMatrix();
		Rs485TxDataFn();     // call Rs485 Communication transmission
		Rs485RxDataFn();     // call RS485 communication and received values are arranged the correct variables
		UpdtRs485Txdata();   // call Rs485 Communication if any changes occurs by users update and save it
		if(Rs485RxFrame.PACK_2.Field.PtcBypassRelySts == DISABLE) {
			POWER_SHUTDOWN_UC_Dat(HHIGH);					//HIGH:Turn ON contactor;	LOW:Turn OFF contactor
			ContactrOnLockVar = 0xff;
		}
		else if(ContactrOnLockVar == 0)	{
			InvRlyPwrOnDlayTmr2 = 0;
			InitSteTmr2 = 0;
		}
		if((FullFlashPopFinish == 0x00)&&(InitSteTmr2 > TMR2_100MS_500MS))	{	//To ensure only in Power up, this function will be called
			FullFlashPopFinish = PushPopAPRValues();
		}
		UpdateXrayPeripherals();
		UpdateLED();
		SlctInAdcChNdSOC();
		DacLoadScheduler();
		
		if((InitSteTmr2 >= TMR2_100MS_2000MS)&&(Rs485RxFrame.PACK_2.Field.PtcBypassRelySts == DISABLE)&&\
			(FullFlashPopFinish == 0xff))	eUc_States = STANDBY_STATE;
	}

	lcd_clear();									//This is required for clearing Initialising screen
	eLastUc_States = INIT_STATE;
}


void StandbyStateFn()	{
	unsigned char TempStsLedVar = 0, ReadySwRlsIntrLocVar = 0;
	SystemSleepTmr2 = 0;
	XRAY_ON_CMD_uC_Dat(0);						//HIGH:X Ray ON;	LOW:X Ray OFF
	BEEP_TOUCH_Dat(0);								//HIGH:Buzzer ON;	LOW:Buzzer OFF
	CONSOLE_STS_uC_Dat(1);						//HIGH:Console Normal;	LOW:Console in Fault state
	HV_85_PRCNT_LED_Uc_Dat(LLOW);				//LLOW:if KV is not rised to 85%;	HHIGH:if KV is rised to 85%
	POWER_SHUTDOWN_UC_Dat(1);					//HIGH:Turn ON contactor;	LOW:Turn OFF contactor
	POWER_SW_LED_uC_Dat(0);						//HIGH:Turn ON Power LED;	LOW:Turn OFF Power LED
	XRAY_READY_uC_Dat(0);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
	FAULT_LED_uC_Dat(0);							//HIGH:Fault Condition;	LOW:Normal Condition	(LED on PCB)
	STATUS_LED_uC_Dat(1);							//HIGH:Normal Condition;	LOW:Fault Condition (LED on PCB)
	lcd_init();
	CntrlPrmtrs.IntraSysCtrlDat.Field.ErrorLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = FALSEE;
	if(CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrTmrEn == TRUEE)	{
		CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = FALSEE;
		CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = FALSEE;
	}
	else	{
		CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = TRUEE;
		CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = TRUEE;
	}
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.CapBankChrgDne = FALSEE;
	CntrlPrmtrs.ErrFlds.all = 0x00;
	if(eLastUc_States != INIT_STATE)	{
		InvRlyPwrOnDlayTmr2 = TMR2_100MS_20SEC + 1;
	}
	else {
		InvRlyPwrOnDlayTmr2 =0x00;
		StndbySteTmr2 = 0x00;
	}
	DispLineFltTkn = 1;     //Used to show message "SUP Err" in standby state in case of line status update from supervisor
	LcdRefreshTmr2 = TMR2_LCD_REFRESH_TME - 1;
	
	while(eUc_States == STANDBY_STATE)
	{
		ScanKeyPadMatrix();
		Rs485TxDataFn();     // call Rs485 Communication transmission
		Rs485RxDataFn();     // call RS485 communication and received values are arranged the correct variables
		UpdtRs485Txdata();   // call Rs485 Communication if any changes occurs by users update and save it
		UpdateXrayPeripherals();
		DispNormalScreenLCD();
		UpdateLED();
		AutoShutDownColimtr();			//This function should be called after Peripheral and LED update functions
		SlctInAdcChNdSOC();
		ScanIndpndntKeys();
		CheckErr();
		DispStatusLineLCD(TempStsLedVar);
		if(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME)	{
			lcd_clear();									//This is required for clearing Initialising screen
			CntrlPrmtrs.IntraSysCtrlDat.all |= 0xFF; 	//For refreshing LCD normal screen		
			DispStatusLineLCD(TempStsLedVar);
			LcdRefreshTmr2 = 0;
		}
		if(StatusLedTmr2 >= (TMR2_100MS_500MS << CntrlPrmtrs.IntraSysCtrlDat.Field.CapBankChrgDne))	{
			TempStsLedVar = TempStsLedVar ^ 0x01;					//For Toggling
			STATUS_LED_uC_Dat(TempStsLedVar);
			StatusLedTmr2 = 0;
		}	
		
		if(InvRlyPwrOnDlayTmr2 >= TMR2_100MS_20SEC)  {
			if(Rs485RxFrame.PACK_2.Field.PtcBypassRelySts == ENABLE)    {
				CntrlPrmtrs.IntraSysCtrlDat.Field.CapBankChrgDne = TRUEE;
				POWER_SW_LED_uC_Dat(LLOW);
			}
			else if(CntrlPrmtrs.IntraSysCtrlDat.Field.CapBankChrgDne != ENABLE) {	
				POWER_SW_LED_uC_Dat(TempStsLedVar);
				BEEP_TOUCH_Dat(TempStsLedVar);
			}
			InvRlyPwrOnDlayTmr2 = TMR2_100MS_20SEC + 1;
			if(Rs485RxFrame.PACK_2.Field.LineFltSts == TRUEE)   {
				DispLineFltTkn = 1;     //Used to show message "SUP Err" in standby state in case of line status update from supervisor
			}   
			else    {
				DispLineFltTkn = 0;     //Used to withdraw "SUP Err" message.
			}
		}
		else {	
			POWER_SW_LED_uC_Dat(TempStsLedVar);
			BEEP_TOUCH_Dat(TempStsLedVar);
		}
		
		if((CntrlPrmtrs.KeyPadSwGp2Sts.Field.Enable_SwPrs == FALSEE)&&(X_RAY_SW_uC == LLOW))	{
			ReadySwRlsIntrLocVar = 0xFF;				// This is to ensure the User has released the hand switch for next exposure.
		}
//	Non relavent error masking
		if(StndbySteTmr2 < TMR2_100MS_5000MS)	{
			CntrlPrmtrs.ErrFlds.all &= STNDBY_ERR_MSK; // error disable in intial time
		}
		else 	{
			if((LowPowerModeLockVar == LOWPWR_MODE_LOCK_VALUE)||(LineVoltChekAbort == 0xFF))	{
				CntrlPrmtrs.ErrFlds.all &= LPM_ENABLE_ERR_MSK; //Enable Buggy board error's and in low power mode, input lower cutoff need not be checked
				StndbySteTmr2 = TMR2_100MS_5000MS + 1;    //wait and watch the Buggy board error's untill the xray ready switch pressing
			}
			else {
				CntrlPrmtrs.ErrFlds.all &= ENABLE_ERR_MSK; //Enable Buggy board error's
				StndbySteTmr2 = TMR2_100MS_5000MS + 1;    //wait and watch the Buggy board error's untill the xray ready switch pressing 
			}
		}
//	State Termination Condition check		
		if((CntrlPrmtrs.KeyPadSwGp2Sts.Field.Enable_SwPrs == TRUEE)&&(CntrlPrmtrs.IntraSysCtrlDat.Field.CapBankChrgDne == TRUEE)&&\
			(DispLineFltTkn == 0)&&(ReadySwRlsIntrLocVar == 0xFF))	eUc_States = ENABLE_STATE;
		else if(CntrlPrmtrs.ErrFlds.all & 0x1F)	eUc_States = FAULT_STATE;
		else if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.V_BucySwLngPrs == TRUEE)&&\
			(CntrlPrmtrs.KeyPadSwGp1IntLok.Field.CollimtrSwLngPrs == TRUEE)&&\
			(CntrlPrmtrs.IntraSysCtrlDat.Field.CapBankChrgDne == TRUEE))	eUc_States = CALIB_STATE;
		else if(SystemSleepTmr2 >= TMR2_100MS_30MINUTES)	eUc_States = INIT_STATE;
	}	
	eLastUc_States = STANDBY_STATE;
}

void EnableStateFn()	{
	unsigned char TempStsLedVar = 0;
	SystemSleepTmr2 = 0;
	XRAY_ON_CMD_uC_Dat(0);						//HIGH:X Ray ON;	LOW:X Ray OFF
	BEEP_TOUCH_Dat(0);								//HIGH:Buzzer ON;	LOW:Buzzer OFF
	CONSOLE_STS_uC_Dat(1);						//HIGH:Console Normal;	LOW:Console in Fault state
	HV_85_PRCNT_LED_Uc_Dat(LLOW);				//LLOW:if KV is not rised to 85%;	HHIGH:if KV is rised to 85%
	POWER_SHUTDOWN_UC_Dat(1);					//HIGH:Turn ON contactor;	LOW:Turn OFF contactor
	POWER_SW_LED_uC_Dat(0);						//HIGH:Turn ON Power LED;	LOW:Turn OFF Power LED
	XRAY_READY_uC_Dat(1);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
	FAULT_LED_uC_Dat(0);							//HIGH:Fault Condition;	LOW:Normal Condition	(LED on PCB)
	STATUS_LED_uC_Dat(1);							//HIGH:Normal Condition;	LOW:Fault Condition (LED on PCB)	
	CntrlPrmtrs.IntraSysCtrlDat.Field.ErrorLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = FALSEE;
	CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = FALSEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
	PreHitTmr1 = 0;		EnablSteTmr2 = 0;					//Initialising timer variable
	CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts = FALSEE;
	CntrlPrmtrs.ErrFlds.all = 0x00;
	LcdRefreshTmr2 = TMR2_LCD_REFRESH_TME + 2;
	while(eUc_States == ENABLE_STATE)
	{
//		ScanKeyPadMatrix();
		Rs485TxDataFn();     // call Rs485 Communication transmission
		Rs485RxDataFn();     // call RS485 communication and received values are arranged the correct variables
		UpdtRs485Txdata();   // call Rs485 Communication if any changes occurs by users update and save it
		UpdateXrayPeripherals();
		DispNormalScreenLCD();
		UpdateLED();
		SlctInAdcChNdSOC();
		ScanIndpndntKeys();
		CheckErr();

		if(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME)	{
			lcd_init();
			lcd_clear();									//This is required for clearing Initialising screen
			CntrlPrmtrs.IntraSysCtrlDat.all |= 0xFF; 	//For refreshing LCD normal screen		
			DispStatusLineLCD(TempStsLedVar);
			LcdRefreshTmr2 = 0;
		}		
		DispStatusLineLCD(StatusLedTmr2);
//		if(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME)	{
//			DispStatusLineLCD(TempStsLedVar);
//			LcdRefreshTmr2 = 0;
//		}
		if(StatusLedTmr2 >= TMR2_100MS_500MS)	{
			TempStsLedVar = TempStsLedVar ^ 0x01;					//For Toggling
			STATUS_LED_uC_Dat(TempStsLedVar);
			StatusLedTmr2 = 0;
		}
		if((PreHitTmr1 >= TMR1_5MS_2500MS)&&(Rs485RxFrame.PACK_2.Field.TuhdRdySts == TRUEE))	{
			CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts = TRUEE;
		}
		else {
			CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = TempStsLedVar;			//This is for LED to toggle
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts = FALSEE;
		}	
		
		if((LowPowerModeLockVar == LOWPWR_MODE_LOCK_VALUE)||(LineVoltChekAbort == 0xFF))	{
			CntrlPrmtrs.ErrFlds.all &= LPM_ENABLE_ERR_MSK; //Enable Buggy board error's and in low power mode, input lower cutoff need not be checked
		}
		else {
			CntrlPrmtrs.ErrFlds.all &= ENABLE_ERR_MSK; //Enable Buggy board error's
		}
		
//	State Termination Condition check		
		if((CntrlPrmtrs.KeyPadSwGp2Sts.Field.Enable_SwPrs == FALSEE)||\
			(EnablSteTmr2 > TMR2_100MS_30SEC))	{
			if(CntrlPrmtrs.IntraSysCtrlDat.Field.CalibEnDisabl == ENABLE)	{
				eUc_States = CALIB_STATE;
			}
			else	{
				eUc_States = STANDBY_STATE;
			}			
		}
		else if((CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts == TRUEE)&&(X_RAY_SW_uC == HHIGH))	eUc_States = EXPOSURE_STATE;
		else if(CntrlPrmtrs.ErrFlds.all & 0x1F)	eUc_States = FAULT_STATE;
	}	
	eLastUc_States = ENABLE_STATE;	
}


void ExposureStateFn()	{
	unsigned short ReqrdExposDurtion = 0;
	XRAY_ON_CMD_uC_Dat(HHIGH);						//HIGH:X Ray ON;	LOW:X Ray OFF
	BEEP_TOUCH_Dat(HHIGH);								//HIGH:Buzzer ON;	LOW:Buzzer OFF
	CONSOLE_STS_uC_Dat(1);						//HIGH:Console Normal;	LOW:Console in Fault state
	HV_85_PRCNT_LED_Uc_Dat(LLOW);				//LLOW:if KV is not rised to 85%;	HHIGH:if KV is rised to 85%
	POWER_SHUTDOWN_UC_Dat(1);					//HIGH:Turn ON contactor;	LOW:Turn OFF contactor
	POWER_SW_LED_uC_Dat(0);						//HIGH:Turn ON Power LED;	LOW:Turn OFF Power LED
	XRAY_READY_uC_Dat(HHIGH);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
	FAULT_LED_uC_Dat(0);							//HIGH:Fault Condition;	LOW:Normal Condition	(LED on PCB)
	STATUS_LED_uC_Dat(1);							//HIGH:Normal Condition;	LOW:Fault Condition (LED on PCB)
	CntrlPrmtrs.IntraSysCtrlDat.Field.ErrorLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ExposeLED = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = FALSEE;
	CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = FALSEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
	ReqrdExposDurtion = CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS * 2;	//Because timer-0 is 500uS
	ReqrdExposDurtion += 200;		//This is for taking care the some delay in supervisor to turn ON exposure/Timer missmatch etc.
	CntrlPrmtrs.ErrFlds.all = 0x00;
	ExpTmeCountTmr0 = 0;
	LineV_Bfor_Expos = LineV_Aftr_Expos = 0x00;
	OutputKvLastExpos = OutputmALastExpos = 0x00;
	LineResx10 = 0x00;
	LineV_Bfor_Expos = PhaseVoltDispVal;
	LcdRefreshTmr2 = 0;
	while(eUc_States == EXPOSURE_STATE)
	{
		Rs485TxDataFn();     // call Rs485 Communication transmission
		Rs485RxDataFn();     // call RS485 communication and received values are arranged the correct variables
		UpdtRs485Txdata();   // call Rs485 Communication if any changes occurs by users update and save it
		UpdateXrayPeripherals();
		DispNormalScreenLCD();
		UpdateLED();
		SlctInAdcChNdSOC();
		ScanIndpndntKeys();
		DispStatusLineLCD(StatusLedTmr2);
		CheckErr();	
		if(HV_85_PRCNT_uC == HHIGH)	{
			HV_85_PRCNT_LED_Uc_Dat(HHIGH);				//LLOW:if KV is not rised to 85%;	HHIGH:if KV is rised to 85%
//			if(ExpTmeCountTmr0 > LR_CALC_SAMPLE_COLECT_INTRVL)	{					//This is for taking line voltage sample while exposing. 1Sec will be required to dip input voltage
//				LineV_Aftr_Expos = PhaseVoltDispVal;
//			}
		}
		if(ExpTmeCountTmr0 > LR_CALC_SAMPLE_COLECT_INTRVL)	{					//This is for taking line voltage sample while exposing. 1Sec will be required to dip input voltage
			LineV_Aftr_Expos = PhaseVoltDispVal;
		}
		CntrlPrmtrs.ErrFlds.all &= EXPSUR_ERR_MSK; //Enable Buggy board error's
//	State Termination Condition check		
		if(X_RAY_SW_uC == LLOW)	{
			if(ReqrdExposDurtion > ExpTmeCountTmr0)	{
				eUc_States = WARNING_STATE;
				CntrlPrmtrs.ErrFlds.Field.WarningCode = 1;		//Pre mature Exposure warning.
			}
			else eUc_States = COOLING_STATE;
		}
		else if(ReqrdExposDurtion <= ExpTmeCountTmr0)	{
			eUc_States = COOLING_STATE;	
		}
		else if(CntrlPrmtrs.ErrFlds.all & 0x1F)	eUc_States = FAULT_STATE;
	}	
	
	if(CntrlPrmtrs.IntraSysCtrlDat.Field.CalibEnDisabl == ENABLE)	{
		ShowCalibResult(1);		//0: To show calibration results; 1: Match calibration pointers;
	}
	
	RefreshLcdFrame();	//This is to Clear any Errornimous values displayed due to Noise after exposure.
	
	WarnStsChkTokn = 0x00;          // This token is to check the warning from supervisor to check only after exposure. This is to avoid CAU4 issue.
	eLastUc_States = EXPOSURE_STATE;		
}


void CoolingStateFn()	{
	unsigned char TempStsLedVar = 0;
	XRAY_ON_CMD_uC_Dat(0);						//HIGH:X Ray ON;	LOW:X Ray OFF
	BEEP_TOUCH_Dat(0);								//HIGH:Buzzer ON;	LOW:Buzzer OFF
	CONSOLE_STS_uC_Dat(1);						//HIGH:Console Normal;	LOW:Console in Fault state
	HV_85_PRCNT_LED_Uc_Dat(LLOW);			//LLOW:if KV is not rised to 85%;	HHIGH:if KV is rised to 85%
	POWER_SHUTDOWN_UC_Dat(1);					//HIGH:Turn ON contactor;	LOW:Turn OFF contactor
	POWER_SW_LED_uC_Dat(1);						//HIGH:Turn ON Power LED;	LOW:Turn OFF Power LED
	XRAY_READY_uC_Dat(0);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
	FAULT_LED_uC_Dat(0);							//HIGH:Fault Condition;	LOW:Normal Condition	(LED on PCB)
	STATUS_LED_uC_Dat(1);							//HIGH:Normal Condition;	LOW:Fault Condition (LED on PCB)
	if(CntrlPrmtrs.IntraSysCtrlDat.Field.CalibEnDisabl == ENABLE)	{
		PushCalibExposeProtocol();					//This is to save last exposed Calibration protocol to EEPROM/Flash.
	}
	else	{
		PushLastExposeProtocol();					//This is to save last exposed protocol to EEPROM.
	}
	CntrlPrmtrs.IntraSysCtrlDat.Field.ErrorLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ExposeLED =FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = FALSEE;
	CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = FALSEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
	CntrlPrmtrs.ErrFlds.all &= 0xFFE0;
	CoolSteTmr1 = 0;					//Initialising timer variable
	LcdRefreshTmr2 = TMR2_LCD_REFRESH_TME + 2;
	while(eUc_States == COOLING_STATE)
	{
//		ScanKeyPadMatrix();
		Rs485TxDataFn();     // call Rs485 Communication transmission
		Rs485RxDataFn();     // call RS485 communication and received values are arranged the correct variables
		UpdtRs485Txdata();   // call Rs485 Communication if any changes occurs by users update and save it
		UpdateXrayPeripherals();
		DispNormalScreenLCD();
		UpdateLED();
		SlctInAdcChNdSOC();
		ScanIndpndntKeys();	
		DacLoadScheduler();
		if(CoolSteTmr1 <= TMR1_5MS_1500MS)	{						// This condition is to copy value only when supervisor is in cooling state
			OutputKvLastExpos = Rs485RxFrame.PACK_1.Field.OutputKV;
			OutputmALastExpos = Rs485RxFrame.PACK_1.Field.OutputMA;
		}
		
		
			if(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME)	{
			lcd_init();
			lcd_clear();									//This is required for clearing Initialising screen
			CntrlPrmtrs.IntraSysCtrlDat.all |= 0xFF; 	//For refreshing LCD normal screen		
			DispStatusLineLCD(TempStsLedVar);
			LcdRefreshTmr2 = 0;
		}
		
		if(StatusLedTmr2 >= TMR2_100MS_500MS)	{
			TempStsLedVar = TempStsLedVar ^ 0x01;					//For Toggling
			STATUS_LED_uC_Dat(TempStsLedVar);
			FAULT_LED_uC_Dat(TempStsLedVar);							//HIGH:Fault Condition;	LOW:Normal Condition	(LED on PCB)
			StatusLedTmr2 = 0;
		}
		DispStatusLineLCD(StatusLedTmr2);
		CheckErr();
		CntrlPrmtrs.ErrFlds.all &= COOLNG_ERR_MSK; //Enable Buggy board error's
//	State Termination Condition check	
		if(CoolSteTmr1 >= TMR1_5MS_3000MS)	{
			if(CntrlPrmtrs.IntraSysCtrlDat.Field.CalibEnDisabl == ENABLE)	{
				eUc_States = CALIB_STATE;
			}
			else	{
				eUc_States = STANDBY_STATE;
			}
		}
		else if((Rs485RxFrame.PACK_2.Field.WarngSts != 0x00)&&(WarnStsChkTokn == 0xff))	{
			eUc_States = WARNING_STATE;
			CntrlPrmtrs.ErrFlds.Field.WarningCode = Rs485RxFrame.PACK_2.Field.WarngSts;
		}
		else if(CntrlPrmtrs.ErrFlds.all & 0x1F)	eUc_States = FAULT_STATE;
	}	
	if(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME)	{
			lcd_init();
			lcd_clear();									//This is required for clearing Initialising screen
			CntrlPrmtrs.IntraSysCtrlDat.all |= 0xFF; 	//For refreshing LCD normal screen		
			DispStatusLineLCD(TempStsLedVar);
			LcdRefreshTmr2 = 0;
		}	
	
	lcd_init();
	RefreshLcdFrame();	//This is to Clear any Errornimous values displayed due to Noise.
	eLastUc_States = COOLING_STATE;		
}


void WarningStateFn()	{
	unsigned char TempStsLedVar = 0;
	XRAY_ON_CMD_uC_Dat(0);						//HIGH:X Ray ON;	LOW:X Ray OFF
	BEEP_TOUCH_Dat(HHIGH);								//HIGH:Buzzer ON;	LOW:Buzzer OFF
	CONSOLE_STS_uC_Dat(1);						//HIGH:Console Normal;	LOW:Console in Fault state
	HV_85_PRCNT_LED_Uc_Dat(LLOW);				//LLOW:if KV is not rised to 85%;	HHIGH:if KV is rised to 85%
	POWER_SHUTDOWN_UC_Dat(1);					//HIGH:Turn ON contactor;	LOW:Turn OFF contactor
	POWER_SW_LED_uC_Dat(1);						//HIGH:Turn ON Power LED;	LOW:Turn OFF Power LED
	XRAY_READY_uC_Dat(0);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
	FAULT_LED_uC_Dat(1);							//HIGH:Fault Condition;	LOW:Normal Condition	(LED on PCB)
	STATUS_LED_uC_Dat(1);							//HIGH:Normal Condition;	LOW:Fault Condition (LED on PCB)
	CntrlPrmtrs.IntraSysCtrlDat.Field.ErrorLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ExposeLED =FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = FALSEE;
	CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = FALSEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
	WarngSteTmr1 = 0;					//Initialising timer variable
	CntrlPrmtrs.ErrFlds.all &= 0xFFE0;
	
	RefreshLcdFrame();		//This is to Clear any Errornimous values displayed due to Noise.
	
	while(eUc_States == WARNING_STATE)
	{
		Rs485TxDataFn();     // call Rs485 Communication transmission
		Rs485RxDataFn();     // call RS485 communication and received values are arranged the correct variables
		UpdtRs485Txdata();   // call Rs485 Communication if any changes occurs by users update and save it
		UpdateXrayPeripherals();
		DispNormalScreenLCD();
		UpdateLED();
		SlctInAdcChNdSOC();
		ScanIndpndntKeys();
		DispStatusLineLCD(0);
		if(StatusLedTmr2 >= TMR2_100MS_500MS)	{
			TempStsLedVar = TempStsLedVar ^ 0x01;					//For Toggling
			CntrlPrmtrs.IntraSysCtrlDat.Field.ErrorLED = TempStsLedVar;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
			BEEP_TOUCH_Dat(TempStsLedVar);
			FAULT_LED_uC_Dat(TempStsLedVar);							//HIGH:Fault Condition;	LOW:Normal Condition	(LED on PCB)
			StatusLedTmr2 = 0;
		}
		DacLoadScheduler();
		CheckErr();
		CntrlPrmtrs.ErrFlds.all &= WARNNG_ERR_MSK; //Enable Buggy board error's
//	State Termination Condition check	
		if(WarngSteTmr1 >= TMR1_5MS_3000MS)	{
			eUc_States = COOLING_STATE;	//Go to Cooling state
		}
		else if(CntrlPrmtrs.ErrFlds.all & 0x1F)	eUc_States = FAULT_STATE;
	}	
	
	eLastUc_States = WARNING_STATE;			
}


void FaultStateFn()	{
	unsigned char TempVar = 0;
	XRAY_ON_CMD_uC_Dat(0);						//HIGH:X Ray ON;	LOW:X Ray OFF
	BEEP_TOUCH_Dat(0);								//HIGH:Buzzer ON;	LOW:Buzzer OFF
	CONSOLE_STS_uC_Dat(0);						//HIGH:Console Normal;	LOW:Console in Fault state
	HV_85_PRCNT_LED_Uc_Dat(LLOW);				//LLOW:if KV is not rised to 85%;	HHIGH:if KV is rised to 85%
	POWER_SHUTDOWN_UC_Dat(1);					//HIGH:Turn ON contactor;	LOW:Turn OFF contactor
	POWER_SW_LED_uC_Dat(0);						//HIGH:Turn ON Power LED;	LOW:Turn OFF Power LED
	XRAY_READY_uC_Dat(0);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
	FAULT_LED_uC_Dat(1);							//HIGH:Fault Condition;	LOW:Normal Condition	(LED on PCB)
	STATUS_LED_uC_Dat(0);							//HIGH:Normal Condition;	LOW:Fault Condition (LED on PCB)
	CntrlPrmtrs.IntraSysCtrlDat.Field.ErrorLED = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ExposeLED =FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = FALSEE;
	CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = FALSEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
	RefreshLcdFrame();		//This is to Clear any Errornimous values displayed due to Noise.
	LcdRefreshTmr2 = TMR2_100MS_14SEC;		//This is for reset LCD incase LCD controller lost power due to ARCing and need re-initialising
	while(eUc_States == FAULT_STATE)
	{
		FaultSteScanKeyPadMatrix();
		Rs485TxDataFn();     // call Rs485 Communication transmission
		Rs485RxDataFn();     // call RS485 communication and received values are arranged the correct variables
		UpdtRs485Txdata();   // call Rs485 Communication if any changes occurs by users update and save it
		UpdateXrayPeripherals();
		DispNormalScreenLCD();
		UpdateLED();
		SlctInAdcChNdSOC();
		ScanIndpndntKeys();
		DcodeErr();
		DispStatusLineLCD(CntrlPrmtrs.ErrFlds.Field.ErrorCode);
		if(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME)	{			//This is for reset LCD incase LCD controller lost power due to ARCing and need re-initialising
			if(TempVar == 0x00)	{
				lcd_init();
				TempVar = 0xFF;
			}
			DacLoadScheduler();
			lcd_clear();									//This is required for clearing Initialising screen
			CntrlPrmtrs.IntraSysCtrlDat.all |= 0xFF; 	//For refreshing LCD normal screen		
			DispStatusLineLCD(0x00);
			DispStatusLineLCD(CntrlPrmtrs.ErrFlds.Field.ErrorCode);
			LcdRefreshTmr2 = 0;
		}		
		
//	State Termination Condition check	
		if(CntrlPrmtrs.ErrFlds.Field.EscErrSte == TRUEE)	eUc_States = INIT_STATE;
	}	
	eLastUc_States = FAULT_STATE;		
}


void CalibStateFn()	{
	unsigned char TempStsLedVar = 0, ReadySwRlsIntrLocVar = 0;
	XRAY_ON_CMD_uC_Dat(0);						//HIGH:X Ray ON;	LOW:X Ray OFF
	BEEP_TOUCH_Dat(0);								//HIGH:Buzzer ON;	LOW:Buzzer OFF
	CONSOLE_STS_uC_Dat(1);						//HIGH:Console Normal;	LOW:Console in Fault state
	HV_85_PRCNT_LED_Uc_Dat(LLOW);				//LLOW:if KV is not rised to 85%;	HHIGH:if KV is rised to 85%
	POWER_SHUTDOWN_UC_Dat(1);					//HIGH:Turn ON contactor;	LOW:Turn OFF contactor
	POWER_SW_LED_uC_Dat(0);						//HIGH:Turn ON Power LED;	LOW:Turn OFF Power LED
	XRAY_READY_uC_Dat(0);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
	FAULT_LED_uC_Dat(0);							//HIGH:Fault Condition;	LOW:Normal Condition	(LED on PCB)
	STATUS_LED_uC_Dat(1);							//HIGH:Normal Condition;	LOW:Fault Condition (LED on PCB)
	CntrlPrmtrs.IntraSysCtrlDat.Field.ErrorLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.ExposeLED =FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = FALSEE;
	
	CntrlPrmtrs.KeyPadFn2Sts.Field.V_BuckySts = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.VBukyLED = CntrlPrmtrs.KeyPadFn2Sts.Field.V_BuckySts;
	CntrlPrmtrs.KeyPadSwGp1Sts.Field.H_BucySwPrs = FALSEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.HBukyLED = CntrlPrmtrs.KeyPadFn2Sts.Field.H_BuckySts;
	
	if(CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrTmrEn == TRUEE)	{
		CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = FALSEE;
		CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = FALSEE;
	}
	else	{
		CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = TRUEE;
		CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = TRUEE;
	}		
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
	CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
	CntrlPrmtrs.ErrFlds.all = 0x00;
	if(CntrlPrmtrs.IntraSysCtrlDat.Field.CalibEnDisabl == DISABLE)	{
		CntrlPrmtrs.IntraSysCtrlDat.Field.CalibEnDisabl = ENABLE;
	}
	ShowCalibScreen();
	StndbySteTmr2 = 0;
//  Only 100mS exposure is required in calibration mode
	CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = 100 + InvExposDelay;
  while(eUc_States == CALIB_STATE)
	{
		ScanKeyPadMatrix_CalibSte();
		Rs485TxDataFn();     // call Rs485 Communication transmission
		Rs485RxDataFn();     // call RS485 communication and received values are arranged the correct variables
		UpdtRs485Txdata();   // call Rs485 Communication if any changes occurs by users update and save it
		UpdateXrayPeripherals();
		DispNormalScreenLCD();
		ShowCalibResult(0);		//0: To show calibration results; 1: Match calibration pointers;
		UpdateLED();
		AutoShutDownColimtr();			//This function should be called after Peripheral and LED update functions
		SlctInAdcChNdSOC();
		ScanIndpndntKeys();
		DispStatusLineLCD(TempStsLedVar);
		FetchCalDltaTuhdEeprm();
		ChekSelProtocolAbrtCndtn();     //  This function is to show "Abt" when user select protocol which is higher than inverter capacity on calibration mode

		if(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME)	{
			DispStatusLineLCD(TempStsLedVar);
			LcdRefreshTmr2 = 0;
		}
		
		if(StatusLedTmr2 >= TMR2_100MS_2000MS)	{
			TempStsLedVar = TempStsLedVar ^ 0x01;					//For Toggling
			STATUS_LED_uC_Dat(TempStsLedVar);
			StatusLedTmr2 = 0;
		}	
		
		if((CntrlPrmtrs.KeyPadSwGp2Sts.Field.Enable_SwPrs == FALSEE)&&(X_RAY_SW_uC == LLOW))	{
			ReadySwRlsIntrLocVar = 0xFF;				// This is to ensure the User has released the hand switch for next exposure.
		}		
		CheckErr();
		if(StndbySteTmr2 < TMR2_100MS_5000MS)	{
			CntrlPrmtrs.ErrFlds.all &= STNDBY_ERR_MSK; // error disable in intial time
		}else 	{
			CntrlPrmtrs.ErrFlds.all &= ENABLE_ERR_MSK; //Enable Buggy board error's
			StndbySteTmr2 = TMR2_100MS_5000MS + 1;    //wait and watch the Buggy board error's untill the xray ready switch pressing 
		}
	//  Start Checking condition to exit
		SendPreCalibData();
		if(ReadySwRlsIntrLocVar != 0xFF)	{
			eUc_States = CALIB_STATE;					// This is to ensure user release the switch before next exposure
		}
		if(CntrlPrmtrs.ErrFlds.all & 0x1F)   {
				eUc_States = FAULT_STATE;       //Go to Fault state
		}   
	}
	SaveCalibRefAdjstVal();
	eLastUc_States = CALIB_STATE;   // It can be useful in some cases	
}


/*	#######################################				History of the Project				#########################################	//
	@TO DO NEXT	:																																																						//
	@BUGS HERE	:																																																						//
	@Rev 0XA: 																																																							//
																																																													//
##############################################		----END----				######################################################*/
