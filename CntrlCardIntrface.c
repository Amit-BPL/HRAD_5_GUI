#include "GenrtrIntrfce.h"

/*	This function is to maintain ALL XRAY PARAMETERS with in the safe Power band With Respect To 	
Argument received and return the status of power band. if return zero, power/Time limit is not with in limit.*/
/**\Arguments
0x00 	:	Normalise parameter if mAs is being updated
0x01	:	Normalise parameter if mA is being updated
0x02	:	Normalise parameter if KV is being updated
0x03	:	Normalise parameter if Time is being updated
*/
char Normalise_XrayParamtr(unsigned char WRT_Paramtr)
{
	unsigned short TempVar_mA = 0,TempVar_mASx10 = 0, TempVar_Count1mS = 0, TempVar_KV = 0;
	unsigned short ArrayRowAdrsOfset = 0, ArrayColAdrsOfset =0;
	unsigned char Settable_mAMAX = 0, Settable_mAMIN = 0;
	unsigned int TempProtPower = 0;
	float PresmAsTime = 0.0;
	
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
	switch(WRT_Paramtr)
	{
		case 0x00:																	//	mAS is varying and need to normalise mA and time
		{
			TempVar_KV = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV;
			TempVar_mASx10 = StdmAsValues[CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt];
//			TempVar_mA = KvmAs_mA_Table[CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - 40][CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mASPTR_LIST_MIN];
			ArrayRowAdrsOfset = (CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - KV_MIN_LIMIT)*mASPTR_LIST_MAX;
			ArrayColAdrsOfset = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mASPTR_LIST_MIN;
			Present_mA_Ptr = KvmAs_mA_Table_Ptr + ArrayRowAdrsOfset + ArrayColAdrsOfset;
			TempVar_mA = *Present_mA_Ptr;
			if(TempVar_mA == 0)	{
				return FALSEE;
			}			
			CntrlPrmtrs.PresentSetmAsx10 = TempVar_mASx10;
			CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = FndOrdinalNumOfShortArr(StationsOfmA,mAPTR_LIST_MAX+1,TempVar_mA);
			CntrlPrmtrs.PresentSetmA = StationsOfmA[CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt];
			TempVar_Count1mS = (unsigned short)((TempVar_mASx10 * 100)/TempVar_mA);				//Here 100 is used as multiplier since saved mAs is 10x
			if(TempVar_Count1mS > 5000)			{					//	5000 = 5000mS = 5 Second as per AERB
				TempVar_Count1mS = 5000;
			}
			CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = TempVar_Count1mS;
		} break;
		case 0x01:																	//	mA is varying and need to normalise mAs and time
		{
			if((LowPowerModeLockVar == LOWPWR_MODE_LOCK_VALUE)||(CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV >= mA_ADJ_MAX_KV)||(CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV <= mA_ADJ_MIN_KV))	{
				return FALSEE;
			}
			else	{
				TempVar_mASx10 = StdmAsValues[CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt];
				ArrayRowAdrsOfset = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - KV_MIN_LIMIT;
				ArrayColAdrsOfset = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mASPTR_LIST_MIN;
				Settable_mAMAX = KvmAs_mAMax_Table[ArrayRowAdrsOfset][ArrayColAdrsOfset];
				Settable_mAMIN = KvmAs_mAMin_Table[ArrayRowAdrsOfset][ArrayColAdrsOfset];
				TempVar_mA = StationsOfmA[CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt];
				if((TempVar_mA > Settable_mAMAX)||(TempVar_mA < Settable_mAMIN))	{
					return FALSEE;
				}
				PresmAsTime = (TempVar_mASx10 * 100)/TempVar_mA;
				TempVar_Count1mS = (unsigned short)PresmAsTime;
				if((TempVar_Count1mS > TUBE_DURATION_5000mS)||(TempVar_Count1mS < TUBE_MIN_DURATION_10mS)||(TempVar_mA < 20))	{		//	(TempVar_mA < 20) is for restricting 15mA only above 99kv
					return FALSEE;
				}
				else	{
					CntrlPrmtrs.PresentSetmA = StationsOfmA[CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt];
					CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = TempVar_Count1mS;
				}				
			}
		} break;
		case 0x02:			//	KV is varying and need to normalise mAs and time
		{
			TempVar_KV = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - KV_MIN_LIMIT;
			ArrayRowAdrsOfset = TempVar_KV * mASPTR_LIST_MAX;
			ArrayColAdrsOfset = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mASPTR_LIST_MIN;
			Present_mA_Ptr = KvmAs_mA_Table_Ptr + ArrayRowAdrsOfset + ArrayColAdrsOfset;
			while((*Present_mA_Ptr == 0)&&((CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mASPTR_LIST_MIN) >= 14))	{
				CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt--;
				Present_mA_Ptr--;
			};
			TempVar_mASx10 = StdmAsValues[CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt];
			CntrlPrmtrs.PresentSetmAsx10 = TempVar_mASx10;
			TempVar_mA = *Present_mA_Ptr;
			CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = FndOrdinalNumOfShortArr(StationsOfmA,mAPTR_LIST_MAX+1,TempVar_mA);
			CntrlPrmtrs.PresentSetmA = StationsOfmA[CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt];	
			TempVar_Count1mS = (unsigned short)((TempVar_mASx10 * 100)/TempVar_mA);				//Here 100 is used as multiplier since saved mAs is 10x
			if(TempVar_Count1mS > 5000)			
			{					//	5000 = 5000mS = 5 Second as per AERB
				TempVar_Count1mS = 5000;
			}
			CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = TempVar_Count1mS;			
			if(TempVar_mA == 0)	
			{
				return FALSEE;
			}		
		}		break;
	}
	return TRUEE;
}

//	Check error condition
void CheckErr()
{
	unsigned char temp_loop_var = 0,temp_hilo = 0;
	unsigned int Temp_PhV_valu = 0;
	Temp_PhV_valu = PhaseVoltDispVal;
	if(Temp_PhV_valu > LINE_VOLT_260)
	{
		CntrlPrmtrs.ErrFlds.Field.LinVoltHiErr = TRUEE;
	}
	else if(Temp_PhV_valu < LINE_VOLT_200)	{
		CntrlPrmtrs.ErrFlds.Field.LinVoltLoErr = TRUEE;
	}
	
	if(GEN_FAULT_uC == LLOW)
	{
		for(temp_loop_var = 0; temp_loop_var < 4; temp_loop_var++)
		{
			if(GEN_FAULT_uC == LLOW) temp_hilo++;
			else temp_hilo = 0;
			if(temp_hilo >= 4)	CntrlPrmtrs.ErrFlds.Field.ControlCardErr = TRUEE;
		}	
	}		
}

/*
//BPL SONIC - All error codes
//	Error code 01 to 50:	Belongs to TUHD
//	Error code 51 to 100:	Belongs to Supervisor
	INV_CRNT_ERR_CODE 50		//	Inverter current error
	DC_BUS_ERR_CODE 51			//	Over or under DC Bus error
	RS485_CMNCTN_ERR_CODE 52	//	RS485 communication error code
//	Error code 101 to 120:	Belongs to Control Panel/System
*/
void DcodeErr()
{
	if(CntrlPrmtrs.ErrFlds.Field.ControlCardErr == TRUEE)	{	
		CntrlPrmtrs.ErrFlds.Field.ErrorCode = Rs485RxFrame.PACK_2.Field.ErrorSts;		//Error code comes from supervisor
	}	
	else if(CntrlPrmtrs.ErrFlds.Field.LinVoltHiErr == TRUEE)	{	
		CntrlPrmtrs.ErrFlds.Field.ErrorCode = PHASEVOLT_HI_ERR_CODE;
	}
	else if(CntrlPrmtrs.ErrFlds.Field.LinVoltLoErr == TRUEE)	{
		CntrlPrmtrs.ErrFlds.Field.ErrorCode = PHASEVOLT_LO_ERR_CODE;
	}
}	

void SendPreCalibData()
{
	unsigned char TempVarUC = 0;
	
	if((CntrlPrmtrs.KeyPadSwGp2Sts.Field.Enable_SwPrs == HHIGH)||(CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts == ENABLE))    
	{
		if(CntrlPrmtrs.CalSts.Field.CalibPointer == 0x00)  			
		{
			PreCalibSendEn = 0x00;  //This Variable is to Use in Serial data framing function 0x00 for sending user set Calibration Pointer 0xff for Pre Calibration Pointer to send
		}
		else if(CntrlPrmtrs.CalSts.Field.CalibPointer == 0x01)   
		{
			if(PreHitTmr1 < TMR1_5MS_3000MS)	
			{
				if(StatusLedTmr2 >= TMR2_100MS_200MS)	
				{
					CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = ~CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED;			//This is for LED to toggle
					CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
					StatusLedTmr2 = 0;
				}
			}
			else
			{
				PreCalibSendEn = 0xff;  //This Variable is to Use in Serial data framing function 0x00 for sending user set Calibration Pointer 0xff for Pre Calibration Pointer to send
				CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = ENABLE;  //xray Ready system Led Activated
				CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts = ENABLE;    //xray-ready  system Enable Command activated
				CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
				XRAY_READY_uC_Dat(1);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
				PreHitTmr1 = 0;
				PreCalibPointer++;
				if(PreCalibPointer < EEPROM_CORSE_CALIB_PTR_LOLIMIT)    {
					PreCalibPointer = EEPROM_CORSE_CALIB_PTR_LOLIMIT;
				}
				else if(PreCalibPointer > EEPROM_CORSE_CALIB_PTR_HILIMIT)    {
					CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts = DISABLE;    //xray-ready  system Enable Command deactivated
					PreCalibPointer = EEPROM_CORSE_CALIB_PTR_HILIMIT;
					PreCalibPointer--;
					PreCalibSendEn = 0x00;  //This Variable is to Use in Serial data framing function 0x00 for sending user set Calibration Pointer 0xff for Pre Calibration Pointer to send
					CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;     //This is for showing limit reached message
					CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;     //This is for showing limit reached message
					PreHitTmr1 = TMR1_5MS_3000MS + 1;
					XRAY_READY_uC_Dat(0);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
				}
				TempVarUC = PreCalibPointer - EEPROM_CORSE_CALIB_PTR_LOLIMIT;
				PreCalibGain = CorseCalibValus[TempVarUC];
			}
		}
		else    
		{
			if((Rs485RxFrame.PACK_2.Field.CalibAbort == FALSEE)&&(CntrlPrmtrs.KeyPadSwGp2Sts.Field.Enable_SwPrs == HHIGH))    {
					eUc_States = ENABLE_STATE;	//Go to enable state
			}
			CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts = DISABLE;    //xray-ready  THIS flag should be set after pre-heat time in enable state for C03 onwards
			PreCalibSendEn = 0x00;                                  //This Variable is to Use in Serial data framing function
		}
	}
	else 
	{
		CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts = DISABLE;    //xray-ready  system Enable Command activated
		CntrlPrmtrs.IntraSysCtrlDat.Field.ReadyLED = DISABLE;  //xray Ready system Led Activated
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag = TRUEE;
		PreCalibSendEn = 0x00;                                  //This Variable is to Use in Serial data framing function
		PreCalibPointer = EEPROM_CORSE_CALIB_PTR_LOLIMIT - 1;
		XRAY_READY_uC_Dat(0);							//HIGH:Ready condition satisfy;	LOW:Ready condition Not satisfy
		PreHitTmr1 = TMR1_5MS_2000MS + 1;
	}
}
 
void SaveCalibRefAdjstVal()
{
	unsigned char LoopVar = 0, LoopVar1 = 0;
	unsigned char TempVar1U8 = 0;
	signed char TempVar1S8 = 0, TempVarIncBy3 = 0, TempVarMulBy3 =0;
	
	TempVar1U8 = CntrlPrmtrs.CalSts.Field.CalibPointer;
	TempVar1S8 = CntrlPrmtrs.CalSts.Field.DeltaCalibVal;

	if((TempVar1U8 >= EEPROM_CORSE_CALIB_PTR_LOLIMIT)&&(TempVar1U8 <= EEPROM_CORSE_CALIB_PTR_HILIMIT))   
	{
		LoopVar1 = NoOf_CORSE_CALIB_PTR;

		if(TempVar1U8 > EEPROM_CORSE_CALIB_PTR_SUPRVSR_HILIMIT)	
		{
			if(TempVar1S8 <= EEPROM_CORSE_CALIB_CONSOL_GAIN_LOLIMIT)    
			{
					TempVar1S8 = EEPROM_CORSE_CALIB_CONSOL_GAIN_LOLIMIT;
			}
			else if(TempVar1S8 >= EEPROM_CORSE_CALIB_CONSOL_GAIN_HILIMIT)   
			{
					TempVar1S8 = EEPROM_CORSE_CALIB_CONSOL_GAIN_HILIMIT;
			}
		}
		else	
		{
			if(TempVar1S8 <= EEPROM_CORSE_CALIB_GAIN_LOLIMIT)    
			{
					TempVar1S8 = EEPROM_CORSE_CALIB_GAIN_LOLIMIT;
			}
			else if(TempVar1S8 >= EEPROM_CORSE_CALIB_GAIN_HILIMIT)  
			{
					TempVar1S8 = EEPROM_CORSE_CALIB_GAIN_HILIMIT;
			}
		}

		for(LoopVar = 0; LoopVar < LoopVar1; LoopVar++)   
		{
			if(CorseCalibPtrsInit[LoopVar].PtrNo == TempVar1U8) 
			{
				TempVarIncBy3 = TempVar1S8 + 3;
				TempVarMulBy3 = TempVar1S8 * 3;
				NvmSendDat.DataLen = 5;
				NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
				NvmSendDat.StartAdrs.Field.PageAdrs = CALBRTE_DATA_PAGE_ADRS;
				NvmSendDat.StartAdrs.Field.ByteLoc = (unsigned char)CorseCalibPtrsInit[LoopVar].EpromLoc1;
				NVM_Data_Array[0] = NVM_Data_Array[1] = NVM_Data_Array[2] = TempVar1S8;
				NVM_Data_Array[3] = TempVarIncBy3;
				NVM_Data_Array[4] = TempVarMulBy3;
				Write_NVM(&NvmSendDat);
				CorseCalibValus[LoopVar] = TempVar1S8;
				if(TempVar1U8 == CALIB_mAS_TYM_ADJ_TIMER_PTR)	
				{
					InvExposDelay = INV_EXPOS_TIME_DELAY + TempVar1S8;
				}
				break;
			}
		}
	}

//    else if((TempVar1U8 >= EEPROM_FINE_CALIB_PTR_LOLIMIT)&&(TempVar1U8 <= EEPROM_FINE_CALIB_PTR_HILIMIT))
//    {
//        if(TempVar1S8 <= EEPROM_FINE_CALIB_GAIN_LOLIMIT)    {
//            TempVar1S8 = EEPROM_FINE_CALIB_GAIN_LOLIMIT;
//        }
//        else if(TempVar1S8 >= EEPROM_FINE_CALIB_GAIN_HILIMIT)   {
//            TempVar1S8 = EEPROM_FINE_CALIB_GAIN_HILIMIT;
//        }
//        TempVar4U8 = TempVar1U8 - EEPROM_FINE_CALIB_PTR_LOLIMIT;
//        TempVar2U8 = TempVar4U8 / EEPROM_LOCARR_COLUMN;   //  Array ROW : Each ROW is 10KV difference
//        TempVar3U8 = TempVar4U8 % EEPROM_LOCARR_COLUMN;   //  Array column
//        LocVar = FlmntRefDltaSavEEPROMLoc[TempVar2U8][TempVar3U8];
//        EEPROM_WRITE(LocVar,TempVar1S8);
//        FilFinCalibVal[TempVar2U8][TempVar3U8] = TempVar1S8;
//    }
}

signed char PopCorseCalibVal(unsigned char CorseCalibPtr)
{
	unsigned char TempVar = 0, UpdateEeprom = 0;
	signed char AtLoc1 = 0, AtLoc2 = 0, AtLoc3 = 0, AtLoc4 = 0, AtLoc5 = 0, AtLocInc3 = 0, AtLocx3 =0, RetrnVal = 0;
	
	if((CorseCalibPtr >= EEPROM_CORSE_CALIB_PTR_LOLIMIT)&&(CorseCalibPtr <= EEPROM_CORSE_CALIB_PTR_HILIMIT))
	{
		TempVar = CorseCalibPtr - EEPROM_CORSE_CALIB_PTR_LOLIMIT;
		NvmReadDat.DataLen = 5;	//2 for KV, 2 for mA, 2 for mAs
		NvmReadDat.NvmBufrAdrs = NVM_Data_Array;
		NvmReadDat.StartAdrs.Field.PageAdrs = CALBRTE_DATA_PAGE_ADRS;
		NvmReadDat.StartAdrs.Field.ByteLoc = CorseCalibPtrsInit[TempVar].EpromLoc1;
		Read_NVM(&NvmReadDat);
		AtLoc1 = (signed char)NVM_Data_Array[0];
		AtLoc2 = (signed char)NVM_Data_Array[1];
		AtLoc3 = (signed char)NVM_Data_Array[2];
		AtLocInc3 = (signed char)NVM_Data_Array[3];
		AtLoc4 = AtLocInc3 - 3;
		AtLocx3 = (signed char)NVM_Data_Array[4];
		AtLoc5 = AtLocx3/3;

		if(AtLoc1 == (AtLoc1 & AtLoc2 & AtLoc3 & AtLoc4 & AtLoc5))  
		{   //Checking Multi Variable Equality
				RetrnVal = AtLoc1;
				UpdateEeprom = FALSEE;
//				UpdateEeprom = TRUEE;
		}
		else if(AtLoc1 == (AtLoc1 & AtLoc2 & AtLoc3))  {                //Checking Multi Variable Equality
				RetrnVal = AtLoc1;
				UpdateEeprom = TRUEE;
		}
		else if(AtLoc1 == (AtLoc1 & AtLoc4 & AtLoc5))                   //Checking Multi Variable Equality
		{
				RetrnVal = AtLoc1;
				UpdateEeprom = TRUEE;
		}
		else if(AtLoc2 == (AtLoc2 & AtLoc4 & AtLoc5))                   //Checking Multi Variable Equality
		{
				RetrnVal = AtLoc2;
				UpdateEeprom = TRUEE;
		}
		else if(AtLoc3 == (AtLoc3 & AtLoc4 & AtLoc5))                   //Checking Multi Variable Equality
		{
				RetrnVal = AtLoc3;
				UpdateEeprom = TRUEE;
		}
		else if((AtLoc1 == AtLoc4)||(AtLoc1 == AtLoc5))
		{
				RetrnVal = AtLoc1;
				UpdateEeprom = TRUEE;
		}
		else if((AtLoc2 == AtLoc4)||(AtLoc2 == AtLoc5))
		{
				RetrnVal = AtLoc2;
				UpdateEeprom = TRUEE;
		}
		else if((AtLoc3 == AtLoc4)||(AtLoc3 == AtLoc5))
		{
				RetrnVal = AtLoc3;
				UpdateEeprom = TRUEE;
		}        
		else    {
				RetrnVal = 0;
				UpdateEeprom = FALSEE;
		}
		
		if(CorseCalibPtr > EEPROM_CORSE_CALIB_PTR_SUPRVSR_HILIMIT)	{
			if(RetrnVal <= EEPROM_CORSE_CALIB_CONSOL_GAIN_LOLIMIT)    {
					RetrnVal = EEPROM_CORSE_CALIB_CONSOL_GAIN_LOLIMIT;
			}
			else if(RetrnVal >= EEPROM_CORSE_CALIB_CONSOL_GAIN_HILIMIT)   {
					RetrnVal = EEPROM_CORSE_CALIB_CONSOL_GAIN_HILIMIT;
			}
		}
		else	{
			if(RetrnVal <= EEPROM_CORSE_CALIB_GAIN_LOLIMIT)    {
					RetrnVal = EEPROM_CORSE_CALIB_GAIN_LOLIMIT;
			}
			else if(RetrnVal >= EEPROM_CORSE_CALIB_GAIN_HILIMIT)   {
					RetrnVal = EEPROM_CORSE_CALIB_GAIN_HILIMIT;
			}
		}
		
		if(UpdateEeprom == TRUEE)    {
				EpromSelfCorctnRqst = EpromSelfCorctnRqst | (1 << TempVar);
		}
	}
	return RetrnVal;
}

void LoadEepromSelfCorctDat()
{
	signed char AtLoc1 = 0, AtLocInc3 = 0, AtLocx3 =0;
	unsigned char LoopVar = 0;
	unsigned int ShiftVar = 0;
	
	if(EpromSelfCorctnRqst != 0x00) {
		for(LoopVar = 0; LoopVar < NoOf_CORSE_CALIB_PTR; LoopVar++) {
			ShiftVar = EpromSelfCorctnRqst >> LoopVar;
			if(ShiftVar & 0x01)    {
				AtLoc1 = CorseCalibValus[LoopVar];
				AtLocx3 = CorseCalibValus[LoopVar]*3;
				AtLocInc3 = CorseCalibValus[LoopVar]+3;					
				NvmSendDat.DataLen = 5;
				NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
				NvmSendDat.StartAdrs.Field.PageAdrs = CALBRTE_DATA_PAGE_ADRS;
				NvmSendDat.StartAdrs.Field.ByteLoc = (unsigned char)CorseCalibPtrsInit[LoopVar].EpromLoc1;
				NVM_Data_Array[0] = NVM_Data_Array[1] = NVM_Data_Array[2] = AtLoc1;
				NVM_Data_Array[3] = AtLocInc3;
				NVM_Data_Array[4] = AtLocx3;
				Write_NVM(&NvmSendDat);							
			}
		}
	}
}

void PopCorseCalibGain()
{
//  Filament Corse Calibration values
    CorseCalibValus[0] = PopCorseCalibVal(CALIBmAFIL_STATION1_PTR);
    CorseCalibValus[1] = PopCorseCalibVal(CALIBmAFIL_STATION2_PTR);
    CorseCalibValus[2] = PopCorseCalibVal(CALIBmAFIL_STATION3_PTR);
    CorseCalibValus[3] = PopCorseCalibVal(CALIBmAFIL_STATION4_PTR);
    CorseCalibValus[4] = PopCorseCalibVal(CALIBmAFIL_STATION5_PTR);
    CorseCalibValus[5] = PopCorseCalibVal(CALIBmAFIL_STATION6_PTR);
//  KV, mA Offset Calibration
    CorseCalibValus[6] = PopCorseCalibVal(CALIB_KVLOOP_PTR);
    CorseCalibValus[7] = PopCorseCalibVal(CALIB_mALOOP_PTR);
    //  Inverter Delay for adjusting KV Overshoot value popping   
    CorseCalibValus[8] = PopCorseCalibVal(CALIB_KV_OVRSHUT_ADJ_TIMER_PTR);	//between supervisor and TUHD
		CorseCalibValus[9] = PopCorseCalibVal(CALIB_FDBK_ADJST_PTR);						//KV mA feedback display value adjust
		CorseCalibValus[10] = 	PopCorseCalibVal(CALIB_mAS_TYM_ADJ_TIMER_PTR);	//between supervisor and Console
		InvExposDelay = INV_EXPOS_TIME_DELAY + CorseCalibValus[10];
		CorseCalibValus[11] = PopCorseCalibVal(CALIB_IPVOLT_DISPADJ_PTR);						//Line voltage display value calibrate
		CorseCalibValus[12] = PopCorseCalibVal(CALIB_COLIMTR_TMEADJ_PTR);						//Collimator timer Adjustment
		if(CorseCalibValus[12] != 0x00)	{
			CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrTmrEn = TRUEE;
			ColimatorTmeSetVar = COLLIMATOR_DEFAULT_TMR + (signed short)(CorseCalibValus[12] * 10);
		}
		else	{
			CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrTmrEn = FALSEE;
		}
//  End of Inverter Delay adjust value popping
    Delay_1uSec(100);
//  Load EEPROM Self correction data
    LoadEepromSelfCorctDat();   //This function is to correct the corrupted EEPROM locations of CORSE CALIBRATION VALUES with Predicted data
}
