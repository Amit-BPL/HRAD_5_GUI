#ifndef GUICMAIN_H_
#define GUICMAIN_H_

#include "CcAbstLayer.h"
#include "LCD.h"

#define LR_CALC_SAMPLE_COLECT_INTRVL 1800		//1000mS = 2000 timer-0 interrupts.

#if MRAD3K6W
	////////////////////////////////	Error Masks		///////////////////////////

	#define STNDBY_ERR_MSK 0xFFE0		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define ENABLE_ERR_MSK 0xFFFF		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define LPM_ENABLE_ERR_MSK 0xFFF6		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define EXPSUR_ERR_MSK 0xFFF0		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define COOLNG_ERR_MSK 0xFFF0		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define WARNNG_ERR_MSK 0xFFF0		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error
	////////////////////////////////	End of Error Masks		///////////////////////////
#elif (MRAD4K4W||MRAD5K0W)
	////////////////////////////////	Error Masks		///////////////////////////

	#define STNDBY_ERR_MSK 0xFFE0		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define ENABLE_ERR_MSK 0xFFFF		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define LPM_ENABLE_ERR_MSK 0xFFF6		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define EXPSUR_ERR_MSK 0xFFF0		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define COOLNG_ERR_MSK 0xFFF0		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error

	#define WARNNG_ERR_MSK 0xFFF0		//bit0: Line Volt LO; bit1: Connection; bit2: Ambient temperature; bit3: Line Volt HI; bit4: Supervisor Error
	////////////////////////////////	End of Error Masks		///////////////////////////

#endif
void InitStateFn(void);
void StandbyStateFn(void);
void EnableStateFn(void);
void ExposureStateFn(void);
void CoolingStateFn(void);
void WarningStateFn(void);
void FaultStateFn(void);
void CalibStateFn(void);
void SleepModeFn(void);

extern void SleepScreenLCD(unsigned char);
extern void DispNormalScreenLCD(void);
extern void DispInitScreenLCD(void);
extern void ConfigPorts(void);
extern void ConfigPeripherals(void);
extern void ConfigSystm(void);
extern void SlctInAdcChNdSOC(void);
extern void ConfigInterrupt(void);
extern void ScanKeyPadMatrix(void);
extern void FaultSteScanKeyPadMatrix(void);
extern void ScanKeyPadMatrix_CalibSte(void);
extern void UpdateXrayPeripherals(void);
extern void UpdateLED(void);
extern void InitVariables(void);
extern void ScanIndpndntKeys(void);
extern void DacLoadScheduler(void);
extern void ShowWaitStsLcd(unsigned char,unsigned char,unsigned char);
extern void	Rs485TxDataFn(void);     // call Rs485 Communication transmission
extern void	Rs485RxDataFn(void);     // call RS485 communication and received values are arranged the correct variables
extern void	UpdtRs485Txdata(void);   // call Rs485 Communication if any changes occurs by users update and save it
extern void CheckErr(void);
extern void DcodeErr(void);
extern void DispStatusLineLCD(unsigned char);
extern void PushLastExposeProtocol(void);
extern void FetchCalDltaTuhdEeprm(void);
extern void ChekSelProtocolAbrtCndtn(void);     //  This function is to show "Abt" when user select protocol which is higher than inverter capacity on calibration mode
extern void SaveCalibRefAdjstVal(void);
extern void PopCorseCalibGain(void);
//extern void PopFineCalibGain(void);
extern void SendPreCalibData(void);
extern void ShowCalibScreen(void);
extern void ShowCalibResult(unsigned char);
extern void SavPresetExposeProtocol(void);
extern void PushCalibExposeProtocol(void);
extern void PopAPRdataToRAM(unsigned char, unsigned char, unsigned char);	//@@@@@@@@@@@@@@@@
extern unsigned char PushPopAPRValues(void);
extern void RefreshLcdFrame(void);
extern void AutoShutDownColimtr(void);

unsigned char LcdRefreshTmr2;
unsigned char DispLineFltTkn, LowPowerModeLockVar, FaultExplainRequest, LineVoltChekAbort;
unsigned char gBeepSoundTmr2, KvDecSwPrsTmr2, KvIncSwPrsTmr2, TmAsIncSwPrsTmr2, TmAsDecSwPrsTmr2, mAIncSwPrsTmr2, mADecSwPrsTmr2;
unsigned char ModeSwPrsTmr2, PatientSwPrsTmr2, HBukySwPrsTmr2, VBukySwPrsTmr2, ColmtrSwPrsTmr2, BdyPrtSelSwPrsTmr2, PresetSwPrsTmr2;
unsigned char SaveSwPrsTmr2, ViewSwPrsTmr2, EnbleSwPrsTmr1, EnbleSwReleseTmr1, AdcSamplingTmr1, AdcReadLockEscTmr0, DacUpdatingTmr1;
unsigned char InitSteTmr2, StatusLedTmr2, FaultLedTmr2, EnablLedTmr2, KeyPadScanTmr1, InvRlyPwrOnDlayTmr2, LimitExeedMsgTmr2;
unsigned short EnablSteTmr2, PreHitTmr1, WarngSteTmr1, ExpTmeCountTmr0, CoolSteTmr1, StndbySteTmr2, LineV_Bfor_Expos, LineV_Aftr_Expos;
unsigned short SystemSleepTmr2, ColimatorTmeSetVar, ColimatorTmr2;
CONTROL_PARAMETER CntrlPrmtrs;
Uc_States eUc_States, eLastUc_States, eSupUc_States;

extern RS485_PANL_TXF1 Rs485TxFrame1;		//Structure variable
extern RS485_PANL_RX Rs485RxFrame;
extern unsigned char WarnStsChkTokn;
extern unsigned short PhaseVoltDispVal;
extern unsigned char OutputKvLastExpos, OutputmALastExpos, LineResx10;
extern signed char InvExposDelay;

#endif
