#ifndef LCDINTRFACE_H_
#define LCDINTRFACE_H_

#include "CcAbstLayer.h"
#include "LCD.h"
#include <stdlib.h>

#define NO_OF_KV_DIGITS 3
#define NO_OF_mA_DIGITS 3
#define NO_OF_TmAS_DIGITS 5

#define PRSNT_STS_CAP_CHARGE 1
#define PRSNT_STS_FAULT 2
#define PRSNT_STS_FIL_BOOST 3
#define PRSNT_STS_COOLING 4
#define PRSNT_STS_WARNING 5
#define PRSNT_STS_PHASE_VOLT 6
#define PRSNT_STS_LIMIT_EXEED 7
#define PRSNT_STS_SAVD_MSG 8
#define PRSNT_STS_CHEK_IP_MSG 9
#define PRSNT_STS_EXPOSE 10


const unsigned char SleepMod_Line1[] = "MACHINE IN";
const unsigned char SleepMod_Line2[] = "--<SLEEP MODE>--";
const unsigned char SleepMod_Line3[] = "RESTART THE MACHINE";
const unsigned char SleepMod_Line4[] = "TO BOOT UP";


const unsigned char CompanyName[]="        BPL         ";
const unsigned char CompanySubName[]="Medical Technologies";
const unsigned char StatusBooting[]="Booting  ";
#if MRAD3K6W
	const unsigned char ProductName[]="M-RAD 3.6+ Machine";
#elif MRAD4K4W
	const unsigned char ProductName[]="M-RAD 4.5 Machine";
#elif MRAD5K0W
	const unsigned char ProductName[]="H-RAD 5.0 Machine";
#endif
const unsigned char Blank_9Space[]="         ";						//9 white spaces
const unsigned char Blank_5Space[]="     ";								//5 white spaces
const unsigned char Blank_3Space[]="   ";									//3 white spaces
/*------------------------------ Body Parts ---------------------------------*/
/*https://radiopaedia.org/articles/radiographic-positioning-terminology*/
/*	Reference:	POSKOM APR CHART	*/
const unsigned char Bp_Skull[]="SKULL    ";
const unsigned char Bp_C_Spine[]="C-SPINE  ";
const unsigned char Bp_Chest[]="CHEST    ";
const unsigned char Bp_T_Spine[]="T-SPINE  ";
const unsigned char Bp_Rib[]="RIB      ";
const unsigned char Bp_Abdomen[]="ABDOMEN  ";
const unsigned char Bp_L_Spine[]="L-SPINE  ";
const unsigned char Bp_Up_Extrimity[]="UPPER-EXT";
const unsigned char Bp_Lowr_Extrimity[]="LOWER-EXT";
/*-----------------------------------------------------------------------------*/
/*------------------------------ Positioning View ---------------------------------*/
const unsigned char Pv_Pa[]="       PA";
const unsigned char Pv_Lat[]="      LAT";
const unsigned char Pv_Towne[]="    TOWNE";							//Skull
const unsigned char Pv_Ap[]="       AP";
const unsigned char Pv_Oblique[]="  OBLIQUE";
const unsigned char Pv_Supine_Ap[]="SUPINE-AP";
const unsigned char Pv_Supine_Lat[]="SUPINE-LA";
const unsigned char Pv_Sternum_Pa[]="STERNM-PA";
const unsigned char Pv_Sternum_Lat[]="STERNM-LA";
const unsigned char Pv_Thorax_Ap[]="THORAX-AP";
const unsigned char Pv_Thorax_Lat[]="THORAX-LA";
const unsigned char Pv_Abdomen_Ap[]=" ABDMN-AP";
const unsigned char Pv_Abdomen_Lat[]="ABDMN-LAT";
const unsigned char Pv_Prone_Ap[]=" PRONE-AP";
const unsigned char Pv_Prone_Lat[]="PRONE-LAT";
const unsigned char Pv_Stand_Ap[]=" STAND-AP";
const unsigned char Pv_Stand_Lat[]="STAND-LAT";
const unsigned char Pv_Pelvis[]="   PELVIS";
const unsigned char Pv_Shoulder[]=" SHOULDER";
const unsigned char Pv_Humerus[]="  HUMERUS";
const unsigned char Pv_ForeArm[]=" FORE-ARM";
const unsigned char Pv_HandRing[]="HAND-RING";
const unsigned char Pv_Femur[]="    FEMUR";
const unsigned char Pv_Knee[]="     KNEE";
const unsigned char Pv_Ankle[]="    ANKLE";
const unsigned char Pv_FootToe[]="FOOT-TOES";
const unsigned char Pv_SpareLoc[]="SPARE-LOC";
/*-----------------------------------------------------------------------------*/
/*------------------------------ Patient Types --------------------------------*/
const unsigned char Pt_Child[]=" CHILDREN";
const unsigned char Pt_TeenAge[]=" TEEN-AGE";
const unsigned char Pt_Adult_Small[]="  ADULT-S";
const unsigned char Pt_Adult_Mediam[]="  ADULT-M";
const unsigned char Pt_Adult_Large[]="  ADULT-L";
const unsigned char Pt_Adult_XLarge[]=" ADULT-XL";
/*-----------------------------------------------------------------------------*/
/*------------------------------ Operating Modes ------------------------------*/
const unsigned char Om_Manual[]="MNUL-MODE           ";
const unsigned char Om_Apr[]="APR-MODE ";
const unsigned char Om_Calibration[]="CALIBRATION-MODE";
/*-----------------------------------------------------------------------------*/
/*------------------------------ Status Messages ------------------------------*/
const unsigned char StatusBarBlankMsg[]="                    ";
const unsigned char CapChrgingMsg[]="Capacitor Charging  ";
const unsigned char ErrMsg[]="Error-";
const unsigned char FilBoostMsg[]="Filamnt Boosting";
const unsigned char CoolingMsg[]="Cooling";
const unsigned char WarningMsg[]="WARNING-";
const unsigned char PhVoltMsg[]="Phase Voltage:";
const unsigned char LimitOvrMsg[]="Oops!Thats the Limit";
const unsigned char DataSavedMsg[]="-->> Data Saved <<--";
const unsigned char CheckIPVMsg[]="Check PowerPCB Input";
const unsigned char ExposingMsg[]="EXPOSING";
const unsigned char LoPwrMsg[]="LP-Stage";
/*-----------------------------------------------------------------------------*/
/*------------------------------ Calibration Output Messages ------------------------------*/
const unsigned char OutPutKvMsg[]="OP_KV:";
const unsigned char OutPutmAMsg[]="OP_mA:";
const unsigned char LineResMsg[]="Line Resistance:";
#if MRAD3K6W
	const unsigned char LowPowrModMsg[]="Low Power Mode 2.5KW";
	const unsigned char HighPowrModMsg[]="HighPower Mode 3.6KW";
#elif MRAD4K4W
	const unsigned char LowPowrModMsg[]="Low Power Mode 3.0KW";
	const unsigned char HighPowrModMsg[]="HighPower Mode 4.5KW";
#elif MRAD5K0W
	const unsigned char LowPowrModMsg[]="Low Power Mode 3.0KW";
	const unsigned char HighPowrModMsg[]="HighPower Mode 5.0KW";
#endif
/*-----------------------------------------------------------------------------*/
/*------------------------------ Errorcode Explanations ------------------------------*/
const unsigned char ExplnErrCod001[]="Filament Boosting LOW detected by ADC - Check F201 in TUHD; Check M201,M202&M203 are ok in TUHD; Check connection from TUHD to sealing PCB filament connection; Otherwise replace TUHD PCB; Otherwise replace monobloc";
const unsigned char ExplnErrCod002[]="Anode side over KV detected by ADC reading; Check TUHD to Sealing FRC Cable; Replace TUHD first then Monoblocif required";
const unsigned char ExplnErrCod003[]="Cathode side over KV detected by ADC reading; Check TUHD to Sealing FRC Cable; Replace TUHD first then Monoblocif required";
const unsigned char ExplnErrCod004[]="Over tube current detected by ADC reading; Calibrate the machine; Otherwise Replace TUHD first then Monobloc if required";
const unsigned char ExplnErrCod005[]="Oil temperature HIGH error; Allow Monobloc to cool for 2 hours; Otherwise replace monobloc";
const unsigned char ExplnErrCod006[]="KV Unbalance error; Check TUHD to Sealing FRC Cable; Replace TUHD first then Monobloc";
const unsigned char ExplnErrCod007[]="Sealing Board connectivity error; Check TUHD to Sealing FRC Cable is connected; Replace cable otherwise";
const unsigned char ExplnErrCod008[]="Over KV error-detected by Hardware; Calibrate the machine; Replace the TUHD first then Supervisor if required";
const unsigned char ExplnErrCod009[]="Tube current over error detected by Hardware; Calibrate the machine; Otherwise Replace TUHD first then Monobloc if required";
const unsigned char ExplnErrCod010[]="Tube Arcing error; Shake Monobloc in different orientation; Replace monobloc if ARCing repeat";
const unsigned char ExplnErrCod011[]="Filament Boosting HIGH error detected by Hardware; Check filament cable connectors; Calibrate machine; Replace TUHD/Monobloc otherwise";
const unsigned char ExplnErrCod012[]="Filament Boosting HIGH error detected by ADC reading; Check filament cable connectors; Calibrate machine; Replace TUHD/Monobloc otherwise";
const unsigned char ExplnErrCod050[]="Inverter Current High Error; Check Inverter resonant inductor; Replace Power board";
const unsigned char ExplnErrCod051[]="Inverter DC BUS Error; Check input cable is connected to power board; Check PFC inductor; Replace power board otherwise";
const unsigned char ExplnErrCod052[]="Communication between boards fails; Check connection between TUHD-Supervisor-Console; Replace all control cards one by one";
const unsigned char ExplnErrCod053[]="Inverter Heat sink Over temperature error; Replace Power PCB";
const unsigned char ExplnErrCod054[]="Inverter Time out error: if exceed 5 seconds in single exposure";
const unsigned char ExplnErrCod055[]="KV Build up delay error; Check supervisor to Power PCB connection; Check inverter to Monobloc connection; Check Power PCB input is connected";
const unsigned char ExplnErrCod100[]="Line voltage Higher than 260V; Measure Input voltage using Multimeter; Do needful to reduce input supply below 260V; Replace Console Card otherwise";
const unsigned char ExplnErrCod101[]="Line voltage Lower than 200V; Measure Input voltage using Multimeter; Do needful to Increase input supply above 200V; Replace Console Card otherwise";
/*-----------------------------------------------------------------------------*/

const unsigned char *AntmyToVewLcdDataPtr[NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY] = {
	{Pv_Pa, 				Pv_Lat, 				Pv_Towne, 			Pv_SpareLoc},									//	Views for SKULL
	{Pv_Ap, 				Pv_Lat, 				Pv_Oblique, 		Pv_SpareLoc},								//	Views for C-SPINE
	{Pv_Pa, 				Pv_Lat, 				Pv_Supine_Ap, 	Pv_Supine_Lat},							//	Views for CHEST
	{Pv_Ap, 				Pv_Lat, 				Pv_Sternum_Pa, 	Pv_Sternum_Lat},						//	Views for T-SPINE
	{Pv_Thorax_Ap, 	Pv_Thorax_Lat, 	Pv_Abdomen_Ap, 	Pv_Abdomen_Lat},						//	Views for RIB
	{Pv_Prone_Ap, 	Pv_Prone_Lat, 	Pv_Stand_Ap, 		Pv_Stand_Lat},							//	Views for ABDOMEN
	{Pv_Ap, 				Pv_Lat, 				Pv_Oblique, 		Pv_Pelvis},									//	Views for L-SPINE
	{Pv_Shoulder, 	Pv_Humerus, 		Pv_ForeArm, 		Pv_HandRing},								//	Views for UPPER EXTRIMITIES
	{Pv_Femur, 			Pv_Knee, 				Pv_Ankle, 			Pv_FootToe}									//	Views for LOWER EXTRIMITIES
};

const unsigned char *AnatmyLcdDataPtr[NUM_OF_ANATOMY_TYPES] = {
	Bp_Skull,	Bp_C_Spine, Bp_Chest, Bp_T_Spine, Bp_Rib, Bp_Abdomen, Bp_L_Spine, Bp_Up_Extrimity, Bp_Lowr_Extrimity 
};

const unsigned char *PatientTypLcdDataPtr[NUM_OF_PATIENT_TYPES] = {
	Pt_Adult_XLarge, Pt_Adult_Large, Pt_Adult_Mediam, Pt_Adult_Small, Pt_TeenAge, Pt_Child
};

const unsigned char *OpModeLcdDataPtr[NUM_OF_OPMODES] = {
	Om_Manual,	Om_Apr
};

unsigned char KvValStringBufr[5] = "     ";						//Buffer to save KV ASCII value.
unsigned char mAValStringBufr[5] = "     ";						//Buffer to save mA ASCII value.
unsigned char TmASValStringBufr[8] = "        ";			//Buffer to save mAs/Time ASCII value.

unsigned char OutputKvLastExpos, OutputmALastExpos, LineResx10;

extern void Delay_100nSec(unsigned char);
extern void Delay_1uSec(unsigned int);
extern void PushLowPowerModeKey(void);
extern void PushHiPowerModeKey(void);
extern void CalculateLineRes(void);
extern void DispStatusLineLCD(unsigned char);

extern unsigned char PreCalibPointer, PreCalibSendEn, LowPowerModeLockVar, FaultExplainRequest;
extern signed char LowPowrModeEntryBfr[];
extern signed char CorseCalibValus[];
extern signed char PreCalibGain, InvExposDelay;
extern CONTROL_PARAMETER CntrlPrmtrs;
extern Uc_States eUc_States;
extern unsigned short PhaseVoltDispVal;
extern short StationsOfmA[], StdmAsValues[];
extern unsigned char NewCalibPtrSel, DispLineFltTkn, LcdRefreshTmr2;
extern RS485_PANL_TXF1 Rs485TxFrame1;		//Structure variable
extern RS485_PANL_RX Rs485RxFrame;
#endif
