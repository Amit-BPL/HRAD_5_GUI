#ifndef CCABSTLAYER_H_
#define CCABSTLAYER_H_

#include "CcLpc24xxPhLayer.h"
#include  "type.h"

//////////*******////			Start of predirectives		//////////********//////////////////
#if MRAD3K6W
	#define FIRMWARE_REV 15
#elif MRAD4K4W
	#define FIRMWARE_REV 11
#elif MRAD5K0W
	#define FIRMWARE_REV 11
#endif

//	Logic Levels
#ifndef TRUEE
#define TRUEE 1
#endif
#ifndef FALSEE
#define FALSEE 0
#endif
#ifndef ENABLE
#define ENABLE 1
#endif
#ifndef DISABLE
#define DISABLE 0
#endif
#ifndef LLOW
#define LLOW 0
#endif
#ifndef HHIGH
#define HHIGH 1
#endif


/************************** GLOBAL/PUBLIC MACRO DEFINITIONS *********************************/

#ifdef  DEBUG
/*******************************************************************************
* @brief		The CHECK_PARAM macro is used for function's parameters check.
* 				It is used only if the library is compiled in DEBUG mode.
* @param[in]	expr - If expr is false, it calls check_failed() function
*                    	which reports the name of the source file and the source
*                    	line number of the call that failed.
*                    - If expr is true, it returns no value.
* @return		None
*******************************************************************************/
#define CHECK_PARAM(expr) ((expr) ? (void)0 : check_failed((uint8_t *)__FILE__, __LINE__))
#else
#define CHECK_PARAM(expr)
#endif /* DEBUG */





//	NVM PAge Dresses
#define MANUAL_DATA_PAGE_ADRS 0x01					//@@@@@@@@@@
#define CALBRTE_DATA_PAGE_ADRS 0x02					//@@@@@@@@@@
#define APR_DATA_PATIENTYPE_PAGE1_ADRS 0x04		//@@@@@@@@@@
#define APR_DATA_PATIENTYPE_PAGE10_ADRS 0x0F	//@@@@@@@@@@
#define SYS_LOG_DATA_START_ADRS 0x10					//@@@@@@@@@@

//	End of NVM Page addresses


/*			Constants */
#define NOT_A_FIRST_BOOT_ACK 0x40							//@@@@@@@@@@
#define FIRST_BOOT_ACK 0x23										//@@@@@@@@@@
#define APR_INDEPENT_MA_FETCH 0
#define APR_INDEPENT_TYM_FETCH 0

#if MRAD3K6W
	#define CALIB20mAFIL_PTR 3
	#define CALIB25mAFIL_PTR 4
	#define CALIB32mAFIL_PTR 5
	#define CALIB40mAFIL_PTR 6
	#define CALIB50mAFIL_PTR 7
	#define CALIB70mAFIL_PTR 8
	#define CALIB_KVLOOP_PTR 9
	#define CALIB_mALOOP_PTR 10
	#define CALIB_KV_OVRSHUT_ADJ_TIMER_PTR 11
	#define CALIB_FDBK_ADJST_PTR 12
	#define CALIB_mAS_TYM_ADJ_TIMER_PTR 13
	#define CALIB_IPVOLT_DISPADJ_PTR 14
	#define CALIB_COLIMTR_TMEADJ_PTR 15
	#define CALIBmAFIL_STATION1_PTR CALIB20mAFIL_PTR
	#define CALIBmAFIL_STATION2_PTR CALIB25mAFIL_PTR
	#define CALIBmAFIL_STATION3_PTR CALIB32mAFIL_PTR
	#define CALIBmAFIL_STATION4_PTR CALIB40mAFIL_PTR
	#define CALIBmAFIL_STATION5_PTR CALIB50mAFIL_PTR
	#define CALIBmAFIL_STATION6_PTR CALIB70mAFIL_PTR

	#define mA_ADJ_MIN_KV 40
	#define mA_ADJ_MAX_KV 100
	#define MIN_KV_SET 40
	#define MAX_KV_SET 110
	#define TOTAL_mA_STATIONS 6
	#define NUM_OF_OPMODES 2
	#define NUM_OF_PATIENT_TYPES 6
	#define NUM_OF_ANATOMY_TYPES 9
	#define NUM_OF_VIEWS_PER_ANATOMY 4
	#define KV_MAX_LIMIT 110
	#define KV_MIN_LIMIT 40
	#define mAPTR_LIST_MIN 4							//4 dummy values need to be added in the value array
	#define mAPTR_LIST_MAX (TOTAL_mA_STATIONS + mAPTR_LIST_MIN)
	#define mASPTR_LIST_MIN 4							//4 dummy values need to be added in the value array
	#define mASPTR_LIST_MAX (26 + mASPTR_LIST_MIN)	
	#define CAL_POINTER_MIN 0
	#define CAL_POINTER_MAX 0x47
	#define mAS_TYM_ADJST_PTR CALIB_mAS_TYM_ADJ_TIMER_PTR
	#define IPVOLT_DISPADJ_PTR CALIB_IPVOLT_DISPADJ_PTR
	#define FIRMWARE_REV_PTR 0x41
	#define SUP_FIRMWARE_REV_PTR 0x42
	#define TUHD_FIRMWARE_REV_PTR 0x43
	#define LINE_RESISTANCE_PTR 0x44
	#define LINE_LOWPWR_PTR1 0x45						// To enter Low power Mode, gain at this pointer: -1
	#define LINE_LOWPWR_PTR2 0x46						// To enter Low power Mode, gain at this pointer: 0
	#define LINE_LOWPWR_PTR3 0x47						// To enter Low power Mode, gain at this pointer: 1
	#define LOWPWR_MODE_LOCK_VALUE 0XAA			// If PTR1:-1; PTR2:0; and PTR3:1 satisfy then LowPowerModeLockVar load with 0xAA
	#define EEPROM_CORSE_CALIB_PTR_LOLIMIT 0x03
	#define EEPROM_CORSE_CALIB_PTR_HILIMIT 0x0F
	#define EEPROM_CORSE_CALIB_PTR_SUPRVSR_HILIMIT CALIB_FDBK_ADJST_PTR
	#define EEPROM_FINE_CALIB_PTR_LOLIMIT 0x15
	#define EEPROM_FINE_CALIB_PTR_HILIMIT 0x3E
	#define EEPROM_CORSE_CALIB_GAIN_LOLIMIT -5
	#define EEPROM_CORSE_CALIB_GAIN_HILIMIT 5
	#define EEPROM_CORSE_CALIB_CONSOL_GAIN_LOLIMIT -15
	#define EEPROM_CORSE_CALIB_CONSOL_GAIN_HILIMIT 15
	#define EEPROM_FINE_CALIB_GAIN_LOLIMIT -2
	#define EEPROM_FINE_CALIB_GAIN_HILIMIT 2
	#define NoOf_CORSE_CALIB_PTR ((EEPROM_CORSE_CALIB_PTR_HILIMIT-EEPROM_CORSE_CALIB_PTR_LOLIMIT)+1)
	#define NoOf_FINE_CALIB_PTR ((EEPROM_FINE_CALIB_PTR_HILIMIT-EEPROM_FINE_CALIB_PTR_LOLIMIT)+1)
	#define EEPROM_LOCARR_COLUMN TOTAL_mA_STATIONS
	#define EEPROM_LOCARR_ROW NoOf_FINE_CALIB_PTR/TOTAL_mA_STATIONS
	#define FINEFIL_ARR_ROW EEPROM_LOCARR_ROW
#elif (MRAD4K4W || MRAD5K0W)
	#define CALIB20mAFIL_PTR 3
	#define CALIB32mAFIL_PTR 4
	#define CALIB40mAFIL_PTR 5
	#define CALIB50mAFIL_PTR 6
	#define CALIB70mAFIL_PTR 7
	#define CALIB100mAFIL_PTR 8	
	#define CALIB_KVLOOP_PTR 9
	#define CALIB_mALOOP_PTR 10
	#define CALIB_KV_OVRSHUT_ADJ_TIMER_PTR 11
	#define CALIB_FDBK_ADJST_PTR 12
	#define CALIB_mAS_TYM_ADJ_TIMER_PTR 13
	#define CALIB_IPVOLT_DISPADJ_PTR 14
	#define CALIB_COLIMTR_TMEADJ_PTR 15
	#define CALIBmAFIL_STATION1_PTR CALIB20mAFIL_PTR
	#define CALIBmAFIL_STATION2_PTR CALIB32mAFIL_PTR
	#define CALIBmAFIL_STATION3_PTR CALIB40mAFIL_PTR
	#define CALIBmAFIL_STATION4_PTR CALIB50mAFIL_PTR
	#define CALIBmAFIL_STATION5_PTR CALIB70mAFIL_PTR
	#define CALIBmAFIL_STATION6_PTR CALIB100mAFIL_PTR

	#define mA_ADJ_MIN_KV 42
	#define mA_ADJ_MAX_KV 100
	#define MIN_KV_SET 40
	#define MAX_KV_SET 110
	#define TOTAL_mA_STATIONS 6
	#define NUM_OF_OPMODES 2
	#define NUM_OF_PATIENT_TYPES 6
	#define NUM_OF_ANATOMY_TYPES 9
	#define NUM_OF_VIEWS_PER_ANATOMY 4
	#define KV_MAX_LIMIT 110
	#define KV_MIN_LIMIT 40
	#define mAPTR_LIST_MIN 4							//4 dummy values need to be added in the value array
	#define mAPTR_LIST_MAX (TOTAL_mA_STATIONS + mAPTR_LIST_MIN)
	#define mASPTR_LIST_MIN 4							//4 dummy values need to be added in the value array
#if MRAD5K0IDR_ENABLE	
	#define mASPTR_LIST_MAX (25 + mASPTR_LIST_MIN + 7)	
#else
	#define mASPTR_LIST_MAX (25 + mASPTR_LIST_MIN)
#endif
	#define CAL_POINTER_MIN 0
	#define CAL_POINTER_MAX 0x53
	#define mAS_TYM_ADJST_PTR CALIB_mAS_TYM_ADJ_TIMER_PTR
	#define IPVOLT_DISPADJ_PTR CALIB_IPVOLT_DISPADJ_PTR
	#define FIRMWARE_REV_PTR 0x4D
	#define SUP_FIRMWARE_REV_PTR 0x4E
	#define TUHD_FIRMWARE_REV_PTR 0x4F
	#define LINE_RESISTANCE_PTR 0x50
	#define LINE_LOWPWR_PTR1 0x51						// To enter Low power Mode, gain at this pointer: -1
	#define LINE_LOWPWR_PTR2 0x52						// To enter Low power Mode, gain at this pointer: 0
	#define LINE_LOWPWR_PTR3 0x53						// To enter Low power Mode, gain at this pointer: 1
	#define LOWPWR_MODE_LOCK_VALUE 0XAA			// If PTR1:-1; PTR2:0; and PTR3:1 satisfy then LowPowerModeLockVar load with 0xAA
	#define EEPROM_CORSE_CALIB_PTR_LOLIMIT 0x03
	#define EEPROM_CORSE_CALIB_PTR_HILIMIT 0x0F
	#define EEPROM_CORSE_CALIB_PTR_SUPRVSR_HILIMIT CALIB_FDBK_ADJST_PTR
	#define EEPROM_FINE_CALIB_PTR_LOLIMIT 0x15
	#define EEPROM_FINE_CALIB_PTR_HILIMIT 0x44
	#define EEPROM_CORSE_CALIB_GAIN_LOLIMIT -5
	#define EEPROM_CORSE_CALIB_GAIN_HILIMIT 5
	#define EEPROM_CORSE_CALIB_CONSOL_GAIN_LOLIMIT -15
	#define EEPROM_CORSE_CALIB_CONSOL_GAIN_HILIMIT 15
	#define EEPROM_FINE_CALIB_GAIN_LOLIMIT -2
	#define EEPROM_FINE_CALIB_GAIN_HILIMIT 2
	#define NoOf_CORSE_CALIB_PTR ((EEPROM_CORSE_CALIB_PTR_HILIMIT-EEPROM_CORSE_CALIB_PTR_LOLIMIT)+1)
	#define NoOf_FINE_CALIB_PTR ((EEPROM_FINE_CALIB_PTR_HILIMIT-EEPROM_FINE_CALIB_PTR_LOLIMIT)+1)
	#define EEPROM_LOCARR_COLUMN TOTAL_mA_STATIONS
	#define EEPROM_LOCARR_ROW NoOf_FINE_CALIB_PTR/TOTAL_mA_STATIONS
	#define FINEFIL_ARR_ROW EEPROM_LOCARR_ROW
#endif

#define APR_SAVE_EN TRUEE							// if this predirective is true, then APR value need to be saved in EEPROM
#define INV_EXPOS_TIME_DELAY 43

/*	----------------	Timer count related	---------------------*/
#define TMR0_500uS_1MS 2
#define TMR0_500uS_2MS 4
#define TMR0_500uS_5MS 10
#define TMR0_500uS_10MS 20
#define TMR0_500uS_20MS 40
#define TMR0_500uS_100MS 200
#define TMR0_500uS_1000MS 2000

#define TMR1_5MS_5MS 1
#define TMR1_5MS_10MS 2
#define TMR1_5MS_15MS 3
#define TMR1_5MS_20MS 4
#define TMR1_5MS_25MS 5
#define TMR1_5MS_35MS 7
#define TMR1_5MS_50MS 10
#define TMR1_5MS_75MS 15
#define TMR1_5MS_100MS 20
#define TMR1_5MS_1500MS 300
#define TMR1_5MS_2000MS 400
#define TMR1_5MS_2500MS 500
#define TMR1_5MS_3000MS 600

#define TMR2_100MS_100MS 1
#define TMR2_100MS_200MS 2
#define TMR2_100MS_500MS 5
#define TMR2_100MS_1000MS 10
#define TMR2_100MS_2000MS 20
#define TMR2_100MS_5000MS 50
#define TMR2_100MS_6000MS 60
#define TMR2_100MS_10SEC 100
#define TMR2_100MS_14SEC 140
#define TMR2_100MS_16SEC 160
#define TMR2_100MS_20SEC 200
#define TMR2_100MS_22SEC 220
#define TMR2_100MS_30SEC 300
#define TMR2_100MS_45SEC 450
#define TMR2_100MS_60SEC 600
#define TMR2_100MS_30MINUTES 18000
#define TMR2_LCD_REFRESH_TME TMR2_100MS_16SEC
#define COLLIMATOR_DEFAULT_TMR TMR2_100MS_45SEC

////////////////////////		END OF PREDIRECTIVES		////////////////////////////////////

//@Note: 	char 	- 8bit
//				short - 16bit
//				long	- 32bit
//				int 	- 32bit
//				long long	-	64bits
//////////*******////	Start of Frames used for RS485 Transmission		////////////////////////////
struct TxF1_Half_L
{
	unsigned char FrameAdrs:5;
	unsigned char FrameType:3;
	unsigned char SetKiloVt:8;
	unsigned char SetMilliA:8;                
	unsigned char UcState:3;
	unsigned char TimeMSB5:5;                
};

union TxF1_Pack1
{
	unsigned long all;
	struct TxF1_Half_L Field;
};

struct TxF1_Half_H
{
	unsigned char PlsExpRt:4;
	unsigned char ErrRcovr:2;
	unsigned char EnblmAs:2;
	unsigned char TimeLSB8:8;
	unsigned char ExpoMode:4;
	unsigned char XRayEnbl:2;
	unsigned char XRayOnOf:2;
	unsigned char EndOfFrme:8;
};

union TxF1_Pack2
{
	unsigned long all;
	struct TxF1_Half_H Field;
};

typedef struct
{
	union TxF1_Pack1 PACK_1;
	union TxF1_Pack2 PACK_2;
}RS485_PANL_TXF1;
//---------------------------------------------------------------------------------------------

struct Rx_Half_L
{
	unsigned char FrameAdrs:5;
	unsigned char FrameType:3;
	unsigned char OutputKV:8;
	unsigned char OutputMA:8;
	unsigned char TubeTemp:8;
};

union Rx_Pack1
{
	unsigned long all;
	struct Rx_Half_L Field;
};

struct Rx_Half_H
{
	unsigned char ErrorSts:7;
  unsigned char TuhdRdySts:1;
	unsigned char MotrSpeedLSB8:8;
	unsigned char WarngSts:2;
  unsigned char LineFltSts:1;
	unsigned char UcState:3;
	unsigned char CalibAbort:1;     //At the selected KV and mA  (From Cxx code) the calibration can not be done
  unsigned char PtcBypassRelySts:1;
	unsigned char EndOfFrme:8;
};

union Rx_Pack2
{
	unsigned long all;
	struct Rx_Half_H Field;
};

typedef struct
{
	union Rx_Pack1 PACK_1;
	union Rx_Pack2 PACK_2;
}RS485_PANL_RX;
//////////*******////	Start of Variables used for General Purpose	//////////********//////////////////
typedef enum {
    INIT_STATE = 0,
    STANDBY_STATE,
    ENABLE_STATE,
    EXPOSURE_STATE,
		COOLING_STATE,
    WARNING_STATE,
    FAULT_STATE,
    CALIB_STATE
} Uc_States;

typedef enum {
    SET_LCD_CNTRAST = 0,
    END_OF_REF
} Dac_Num;

typedef enum {
    TEMPTR_ADC = 0,					//Temperature Sensor
    LINEV_ADC,							//Line Voltage
    END_OF_INADC
} InAdc_Num;

//	Structures for Control Parameters
struct Error_field {
    unsigned char LinVoltLoErr : 1;
    unsigned char ConctErr : 1;
	  unsigned char AmbTempErr : 1;
    unsigned char LinVoltHiErr : 1;
    unsigned char ControlCardErr : 1;
		unsigned char ErrorCode : 7;
    unsigned char WarningCode : 3;
    unsigned char EscErrSte : 1;
};

union Pack_Error_field {
    unsigned short all;
    struct Error_field Field;
};

struct GUICardDataSetA {
		unsigned long CollimtrSwPrs : 1;											//Simple Press Status
		unsigned long CollimtrSwLngPrs : 1;										//Long Press Status
		unsigned long H_BucySwPrs : 1;												//Horizontal Bucky Simple Press Status
		unsigned long H_BucySwLngPrs : 1;											//Horizontal Bucky Long Press Status
		unsigned long V_BucySwPrs : 1;												//Vertical Bucky Simple Press Status
		unsigned long V_BucySwLngPrs : 1;											//Vertical Bucky Long Press Status
		unsigned long PresetSwPrs : 1;												//Simple Press Status
		unsigned long PresetSwLngPrs : 1;											//Long Press Status
		unsigned long SaveSwPrs : 1;													//Simple Press Status
		unsigned long SaveSwLngPrs : 1;												//Long Press Status
		unsigned long KvIncSwPrs : 1;													//Simple Press Status
		unsigned long KvIncSwLngPrs : 1;												//Long Press Status
		unsigned long KvDecSwPrs : 1;														//Simple Press Status
		unsigned long KvDecSwLngPrs : 1;												//Long Press Status
		unsigned long mA_Inc_SwPrs : 1;													//Simple Press Status
		unsigned long mA_Inc_SwLngPrs : 1;											//Long Press Status
		unsigned long mA_Dec_SwPrs : 1;													//Simple Press Status
		unsigned long mA_Dec_SwLngPrs : 1;											//Long Press Status
		unsigned long TmAsInc_SwPrs : 1;												//Simple Press Status
		unsigned long TmAsInc_SwLngPrs : 1;											//Long Press Status
		unsigned long TmAsDec_SwPrs : 1;												//Simple Press Status
		unsigned long TmAsDec_SwLngPrs : 1;											//Long Press Status
		unsigned long Spare:10;
};

struct ControlCardDataSetB {															//Updated for GUI Card
    unsigned long LineVAdcResult : 10;
    unsigned long LcdContrastDacLodNo : 12;	
		unsigned long TemptrAdcResult:10;											//Temperature sensor
};

struct GUICardDataSetC {															//Updted for GUI Card
	unsigned long OpratngMode : 2;
	unsigned long PatientType : 4;
	unsigned long Anatomy : 5;
	unsigned long AnatmyView : 3;
	unsigned long Std_mAsPtrCnt : 6;
	unsigned long mA_StationPtrCnt : 6;
	unsigned long AEC_Select : 1;
	unsigned long AEC_ChCombSel : 3;
	unsigned long PreSetSts : 1;
	unsigned long SaveSts : 1;
};

struct GUICardDataSetD	{
		unsigned long UserSetKV : 8;
		unsigned long UsrSetTme1mS : 14;								//User Set time in number of 1mS.
		unsigned long DensitySts : 4;
		unsigned long FlmTypeSts : 2;
		unsigned long CollimatorSts : 1;
		unsigned long H_BuckySts : 1;
		unsigned long V_BuckySts : 1;
		unsigned long UpdtNrmliztn:1;
};

struct GUICardDataSetE {
    unsigned short Enable_SwPrs : 1;												//Simple Press Status
		unsigned short Expose_SwPrs : 1;											//Simple Press Status
		unsigned short ModeSwPrs : 1;													//Simple Press Status
		unsigned short PatientSwPrs : 1;											//Simple Press Status
		unsigned short AnatomySwPrs : 1;											//Simple Press Status
		unsigned short ViewSwPrs : 1;													//Simple Press Status
/*---------------------	For Future Enhancement	-----------------------------*/		
		unsigned short DensityIncSwPrs : 1;										//Simple Press Status
		unsigned short DensityDecSwPrs : 1;										//Simple Press Status
		unsigned short AecSelectSwPrs : 1;										//Simple Press Status
		unsigned short AecChamberSwPrs : 1;										//Simple Press Status
		unsigned short FilmSpeedSwPrs : 1;										//Simple Press Status
		unsigned short gLimitExeedBit : 1;
		unsigned short gDataSavedBit:1;
		unsigned short Global_Climtr_HVBky_Flag:1;			//If any collimator switch/ Buckyswitch activities happened, this bit need to be updated with '1'
		unsigned short GlobalLEDFlag:1;									//If any LED update need to be done, this bit need to be updated with '1'
		unsigned short GlobalSwFlag:1;									//If any Keypad update is done, this bit need to be updated with '1'
};

union Pack_GUICDataE {
    unsigned short all;
    struct GUICardDataSetE Field;
};

struct GUICardDataSetF {
    unsigned long LcdGloblUpdtReqFlag : 1;												//Flag to indicate data need to be updated in LCD. following flags give which field to update 
		unsigned long LcdUpdtModReqFlag : 1;
		unsigned long LcdUpdtAntmyReqFlag : 1;
		unsigned long LcdUpdtPatientReqFlag : 1;
		unsigned long LcdUpdtViewReqFlag : 1;
		unsigned long LcdUpdtKVReqFlag : 1;
		unsigned long LcdUpdtmAReqFlag : 1;
		unsigned long LcdUpdtTmAsReqFlag : 1;
		unsigned long LcdUpdtAecStsReqFlag : 1;
		unsigned long LcdUpdtAecChmbrReqFlag : 1;
		unsigned long LcdUpdtDenctReqFlag : 1;
		unsigned long LcdUpdtFilmSpeedReqFlag : 1;
		unsigned long CalibEnDisabl : 1;
		unsigned long Rs485TxEnable : 1;
		unsigned long ReadySts : 1;											//After receive pre Heat time acknowledge from control card, this flag need to be SET.
		unsigned long BuzzerStats : 1;
		unsigned long SpareLED : 1;								//Lock this position(17th bit) LED LSB
		unsigned long ReadyLED : 1;
		unsigned long ExposeLED : 1;
		unsigned long HBukyLED : 1;
		unsigned long VBukyLED : 1;
		unsigned long ColimtrLED : 1;
		unsigned long ErrorLED : 1;
		unsigned long PreSetLED : 1;							//Lock this position(24th bit) LED MSB
		unsigned long Rs485TxFrmOvr : 1;
		unsigned long Rs485RxEnable : 1;
		unsigned long Rs485RxFrmOvr : 1;
		unsigned long CapBankChrgDne : 1;
		unsigned long Rs485TxAdrsOvr : 1;
		unsigned long WaitForTuhdEeprom:1;
		unsigned long CalibPtrAbortTokn:1;
		unsigned long ColimtrTmrEn:1;
};

union Pack_GUICDataF {
    unsigned long all;
    struct GUICardDataSetF Field;
};

union Pack_GUICDataA {
    unsigned long all;
    struct GUICardDataSetA Field;
};

union Pack_CCDataB {
    unsigned long all;
    struct ControlCardDataSetB Field;
};

union Pack_GUICDataC {
    unsigned long all;
    struct GUICardDataSetC Field;
};

union Pack_GUIDataD {
    unsigned long all;
    struct GUICardDataSetD Field;
};

struct FilamentChartData	{
	unsigned short PrsntFilDacDat:12;
	unsigned short Spare1:2;
	unsigned short PowrOverFlag:1;
	unsigned short FilmntSelFlag:1;
};

typedef union  {
    unsigned short all;
    struct FilamentChartData Field;
}FilmntChrtDat;

struct CalibrationStatus
{
    unsigned char CalibPointer:8;
    signed char DeltaCalibVal:8;
};

union Pack_CalibSts
{
	unsigned int all;
	struct CalibrationStatus Field;
};

typedef struct {
    union Pack_Error_field ErrFlds;
    union Pack_GUICDataA KeyPadSwGp1Sts;								//Group of switches have Long press functionality
		union Pack_GUICDataA KeyPadSwGp1IntLok;							//Group of switches have Long press functionality
		union Pack_GUICDataE KeyPadSwGp2Sts;								//Group of switches have only simple press functionality
		union Pack_GUICDataE KeyPadSwGp2IntLok;							//Group of switches have only simple press functionality
    union Pack_CCDataB AnalogData;
    union Pack_GUICDataC KeyPadFn1Sts;									//Updted for GUI Card
		union Pack_GUIDataD KeyPadFn2Sts;
		union Pack_GUICDataF IntraSysCtrlDat;
		FilmntChrtDat PrcntFilChDat;
		union Pack_CalibSts CalSts;
		unsigned short PresentSetmA;
		unsigned short PresentSetmAsx10;
} CONTROL_PARAMETER;
/*------------------------------------------------------------------------------------------------------------------*/
struct NvmAdresingStruct{
	unsigned int ByteLoc:10;
	unsigned int PageAdrs:12;
	unsigned int DummyBits:2;
	unsigned int NvmOpCode:8;
};

typedef union	{
	struct NvmAdresingStruct Field;
	unsigned int all;
}NVM_ADRS_FORMAT;

typedef struct	{
	NVM_ADRS_FORMAT StartAdrs;
	unsigned char *NvmBufrAdrs;
	unsigned char DataLen;
}NVM_DATA_STRUCT;
//------------------------------- END OF NVM RELATED STRUCTURE	------------------------------------
extern unsigned char gBeepSoundTmr2, KvDecSwPrsTmr2, KvIncSwPrsTmr2, TmAsIncSwPrsTmr2, TmAsDecSwPrsTmr2, mAIncSwPrsTmr2, mADecSwPrsTmr2;
extern unsigned char ModeSwPrsTmr2, PatientSwPrsTmr2, HBukySwPrsTmr2, VBukySwPrsTmr2, ColmtrSwPrsTmr2, BdyPrtSelSwPrsTmr2, PresetSwPrsTmr2;
extern unsigned char SaveSwPrsTmr2, ViewSwPrsTmr2, EnbleSwPrsTmr1, EnbleSwReleseTmr1, AdcSamplingTmr1, AdcReadLockEscTmr0, DacUpdatingTmr1;
extern unsigned char InitSteTmr2, StatusLedTmr2, FaultLedTmr2, EnablLedTmr2, KeyPadScanTmr1, LimitExeedMsgTmr2;
extern unsigned short EnablSteTmr2, PreHitTmr1, WarngSteTmr1, StndbySteTmr2;
#if MRAD3K6W
	extern const unsigned char KvmAs_mA_Table[71][mASPTR_LIST_MAX],KvmAs_mA_Table_LPMode[71][mASPTR_LIST_MAX];
#elif (MRAD4K4W || MRAD5K0W)
	extern const unsigned char KvmAs_mA_Table[71][mASPTR_LIST_MAX],KvmAs_mA_Table_LPMode[71][mASPTR_LIST_MAX];
#endif
extern const unsigned char *KvmAs_mA_Table_Ptr, *Present_mA_Ptr;
extern const unsigned char Delay_1uS_Cvnt;	// Number of machine cycles to have 1uS delay	
extern const float Delay_100nS_Cvnt;				// Number of machine cycles to have 1uS delay
unsigned char WriteDAC(Dac_Num eDac_Num);
void DacLoadScheduler(void);

#endif


/**
* \RevisionHistory **************
* \Rev 1.1: Bucky operation is updated
*/