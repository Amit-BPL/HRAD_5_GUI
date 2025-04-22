#include "KeypadIntrFace.h"

void ComnDutyEvryKeyPrs()
{
	BEEP_TOUCH_Dat(ENABLE);
	CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = ENABLE;
	gBeepSoundTmr2 = 0;
}

void ScanColumn1()	//	Check Column1
{
	Delay_100nSec(2);				//Nano seconds to discharge 10pF capacitor.
	KYPAD_COLMN_uC(0x0E);
	Delay_100nSec(2);				//Nano seconds to discharge 10pF capacitor.
//	Scan "KV INCREMENT" Switch
	if(KYPAD_ROW0_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.KvIncSwPrs == FALSEE)&&(KvIncSwPrsTmr2 >= TMR2_100MS_100MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvIncSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.KvIncSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if(KvIncSwPrsTmr2 > TMR2_100MS_2000MS)	{
			KvIncSwPrsTmr2 = TMR2_100MS_2000MS - TMR2_100MS_200MS;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvIncSwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}

	//	Scan "mAs INCREMENT" Switch
	if(KYPAD_ROW1_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.TmAsInc_SwPrs == FALSEE)&&(TmAsIncSwPrsTmr2 >= TMR2_100MS_100MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsInc_SwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.TmAsInc_SwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if(TmAsIncSwPrsTmr2 > TMR2_100MS_2000MS)	{
			TmAsIncSwPrsTmr2 = TMR2_100MS_2000MS - TMR2_100MS_200MS;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsInc_SwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
	
	//	Scan "mA INCREMENT" Switch
	if(KYPAD_ROW2_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.mA_Inc_SwPrs == FALSEE)&&(mAIncSwPrsTmr2 >= TMR2_100MS_100MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Inc_SwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.mA_Inc_SwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if(mAIncSwPrsTmr2 > TMR2_100MS_2000MS)	{
			mAIncSwPrsTmr2 = TMR2_100MS_2000MS - TMR2_100MS_200MS;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Inc_SwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
	
//	Scan "Mode Select" Switch
	if(KYPAD_ROW3_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp2IntLok.Field.ModeSwPrs == FALSEE)&&(ModeSwPrsTmr2 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.ModeSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2IntLok.Field.ModeSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
}

void ScanColumn2()	//	Check Column2
{
	Delay_100nSec(2);				//Nano seconds to discharge 10pF capacitor.
	KYPAD_COLMN_uC(0x0D);
	Delay_100nSec(2);				//Nano seconds to discharge 10pF capacitor.
//	Scan "KV DECREMENT" Switch
	if(KYPAD_ROW0_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.KvDecSwPrs == FALSEE)&&(KvDecSwPrsTmr2 >= TMR2_100MS_100MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvDecSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.KvDecSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if(KvDecSwPrsTmr2 > TMR2_100MS_2000MS)	{
			KvDecSwPrsTmr2 = TMR2_100MS_2000MS - TMR2_100MS_200MS;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvDecSwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}

	//	Scan "mAs DECREMENT" Switch
	if(KYPAD_ROW1_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.TmAsDec_SwPrs == FALSEE)&&(TmAsDecSwPrsTmr2 >= TMR2_100MS_100MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsDec_SwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.TmAsDec_SwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if(TmAsDecSwPrsTmr2 > TMR2_100MS_2000MS)	{
			TmAsDecSwPrsTmr2 = TMR2_100MS_2000MS - TMR2_100MS_200MS;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsDec_SwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
	
	//	Scan "mA DECREMENT" Switch
	if(KYPAD_ROW2_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.mA_Dec_SwPrs == FALSEE)&&(mADecSwPrsTmr2 >= TMR2_100MS_100MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Dec_SwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.mA_Dec_SwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if(mADecSwPrsTmr2 > TMR2_100MS_2000MS)	{
			mADecSwPrsTmr2 = TMR2_100MS_2000MS - TMR2_100MS_200MS;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Dec_SwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
	
//	Scan "Patient Select" Switch
	if(KYPAD_ROW3_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp2IntLok.Field.PatientSwPrs == FALSEE)&&(PatientSwPrsTmr2 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.PatientSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2IntLok.Field.PatientSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
}

void ScanColumn3()	//	Check Column3
{
	Delay_100nSec(2);				//Nano seconds to discharge 10pF capacitor.
	KYPAD_COLMN_uC(0x0B);
	Delay_100nSec(2);				//Nano seconds to discharge 10pF capacitor.
//	Scan "Horizontal Bucky" Switch
	if(KYPAD_ROW0_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.H_BucySwPrs == FALSEE)&&(HBukySwPrsTmr2 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.H_BucySwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.H_BucySwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if((HBukySwPrsTmr2 > TMR2_100MS_2000MS)&&(CntrlPrmtrs.KeyPadSwGp1IntLok.Field.H_BucySwLngPrs == FALSEE))	{
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.H_BucySwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.H_BucySwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}

	//	Scan "Collimator" Switch
	if(KYPAD_ROW1_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.CollimtrSwPrs == FALSEE)&&(ColmtrSwPrsTmr2 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.CollimtrSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.CollimtrSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if((ColmtrSwPrsTmr2 > TMR2_100MS_2000MS)&&(CntrlPrmtrs.KeyPadSwGp1IntLok.Field.CollimtrSwLngPrs == FALSEE))	{
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.CollimtrSwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.CollimtrSwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
	else	{
		CntrlPrmtrs.KeyPadSwGp1IntLok.Field.CollimtrSwPrs = FALSEE;
		CntrlPrmtrs.KeyPadSwGp1IntLok.Field.CollimtrSwLngPrs = FALSEE;
		ColmtrSwPrsTmr2 = 0;
	}

/*	ROW2 is SPARE	*/	
	
	//	Scan "Body Part" Switch
	if(KYPAD_ROW3_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp2IntLok.Field.AnatomySwPrs == FALSEE)&&(BdyPrtSelSwPrsTmr2 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.AnatomySwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2IntLok.Field.AnatomySwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
}

void ScanColumn4()	//	Check Column4
{
	Delay_100nSec(2);				//Nano seconds to discharge 10pF capacitor.
	KYPAD_COLMN_uC(0x07);
	Delay_100nSec(2);				//Nano seconds to discharge 10pF capacitor.
//	Scan "Vertical Bucky" Switch
	if(KYPAD_ROW0_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.V_BucySwPrs == FALSEE)&&(VBukySwPrsTmr2 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.V_BucySwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.V_BucySwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if((VBukySwPrsTmr2 > TMR2_100MS_2000MS)&&(CntrlPrmtrs.KeyPadSwGp1IntLok.Field.V_BucySwLngPrs == FALSEE))	{
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.V_BucySwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.V_BucySwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
	else	{
		CntrlPrmtrs.KeyPadSwGp1IntLok.Field.V_BucySwPrs = FALSEE;
		CntrlPrmtrs.KeyPadSwGp1IntLok.Field.V_BucySwLngPrs = FALSEE;
		VBukySwPrsTmr2 = 0;
	}

	//	Scan "Pre-SET" Switch
	if(KYPAD_ROW1_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.PresetSwPrs == FALSEE)&&(PresetSwPrsTmr2 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.PresetSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.PresetSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if((PresetSwPrsTmr2 > TMR2_100MS_2000MS)&&(CntrlPrmtrs.KeyPadSwGp1IntLok.Field.PresetSwLngPrs == FALSEE))	{
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.PresetSwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.PresetSwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}

	//	Scan "SAVE" Switch
	if(KYPAD_ROW2_uC == LLOW)		{
		if((CntrlPrmtrs.KeyPadSwGp1IntLok.Field.SaveSwPrs == FALSEE)&&(SaveSwPrsTmr2 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.SaveSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.SaveSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
		
		if((SaveSwPrsTmr2 > TMR2_100MS_2000MS)&&(CntrlPrmtrs.KeyPadSwGp1IntLok.Field.SaveSwLngPrs == FALSEE))	{
			CntrlPrmtrs.KeyPadSwGp1IntLok.Field.SaveSwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp1Sts.Field.SaveSwLngPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}

	//	Scan "VIEW" Switch
	if((KYPAD_ROW3_uC == LLOW)&&(CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode != 0))		{
		if((CntrlPrmtrs.KeyPadSwGp2IntLok.Field.ViewSwPrs == FALSEE)&&(ViewSwPrsTmr2 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.ViewSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2IntLok.Field.ViewSwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = TRUEE;
		}
	}
}

/*	This function finds the ordinal number of passed content in an constant array	*/
unsigned char FndOrdinalNumOfShortArr(const unsigned short *ArryAdrs, unsigned char ArrSize, unsigned short ValToFind)
{
	unsigned char LoopVar1 = 0, OrdinalNum = 0;
	const unsigned short *Temp_ArryAdrs;
	
	Temp_ArryAdrs = ArryAdrs;
	for(LoopVar1 = 0; LoopVar1 < ArrSize; LoopVar1++)
	{
		if((*Temp_ArryAdrs <= ValToFind+1)&&(*Temp_ArryAdrs >= ValToFind-1))
		{
			OrdinalNum = LoopVar1;
			break;
		}
		Temp_ArryAdrs++;
	}
return OrdinalNum;	
}

/*	FetchLoc - 0x00: Default value to fetch
		FetchLoc - 0xff: Saved value in RAM to fetch value to fetch
*/
void FetchAPR_Data(unsigned char FetchLoc)
{
	unsigned short TempmAs = 0, TempmA = 0, TempTym = 0;
	unsigned short ArrayRowAdrsOfset = 0, ArrayColAdrsOfset =0;	
	unsigned char PatientType, BodyPart, PartView;
	
	PatientType = CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType;
	BodyPart = CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy;
	PartView = CntrlPrmtrs.KeyPadFn1Sts.Field.AnatmyView;
	
//	Fetch mAs
	if(FetchLoc == 0xff)	{
		TempmAs = Apr_mASx10_Values[PatientType][BodyPart][PartView];
	}
#if APR_SAVE_EN	
	else if(FetchLoc == 0x00)	{
		TempmAs = Apr_DefltmASx10_Values[PatientType][BodyPart][PartView];
	}
#endif
	CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = FndOrdinalNumOfShortArr(StdmAsValues,mASPTR_LIST_MAX,TempmAs);
	CntrlPrmtrs.PresentSetmAsx10 = StdmAsValues[CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt];

//	Fetch KV
	if(FetchLoc == 0xff)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = AprKv_Values[PatientType][BodyPart][PartView];
	}
#if APR_SAVE_EN	
	else if(FetchLoc == 0x00)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = AprDefltKv_Values[PatientType][BodyPart][PartView];
	}
#endif
	
//	Fetch mA
#if APR_INDEPENT_MA_FETCH
	TempmA = Apr_mA_Values[CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType][CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy][CntrlPrmtrs.KeyPadFn1Sts.Field.AnatmyView];
#else
//	TempmA = KvmAs_mA_Table[CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - MIN_KV_SET][CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mASPTR_LIST_MIN];
	ArrayRowAdrsOfset = (CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - KV_MIN_LIMIT)*mASPTR_LIST_MAX;
	ArrayColAdrsOfset = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - mAPTR_LIST_MIN;
	Present_mA_Ptr = KvmAs_mA_Table_Ptr + ArrayRowAdrsOfset + ArrayColAdrsOfset;
	TempmA = *Present_mA_Ptr;
#endif
	CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = FndOrdinalNumOfShortArr(StationsOfmA,mAPTR_LIST_MAX+1,TempmA);
	CntrlPrmtrs.PresentSetmA = StationsOfmA[CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt];

//	Fetch Time
#if  APR_INDEPENT_TYM_FETCH
	CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = Apr_Time_mS_Values[CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType][CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy][CntrlPrmtrs.KeyPadFn1Sts.Field.AnatmyView];;
#else
	TempTym = (unsigned short)((TempmAs * 100)/TempmA);
	if(TempTym > 5000)	TempTym = 5000;
	else if(TempTym < 1)	TempTym = 1;
	CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = TempTym;
#endif
}

/*	Limit KV, mA and mAs parameters as per machine configuration	*/
void LimitXrayParameters()
{
//	Limit KV
	if(CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV > KV_MAX_LIMIT)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = KV_MAX_LIMIT;		
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
	}
	else if(CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV < KV_MIN_LIMIT)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = KV_MIN_LIMIT;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
	}
	
//	Limit mA
	if(CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt >= (mAPTR_LIST_MAX+1))	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = mAPTR_LIST_MAX;		
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
	}
	else if(CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt < mAPTR_LIST_MIN)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = mAPTR_LIST_MIN;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
	}
	
//	Limit Time/mAS
	if(CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt >= mASPTR_LIST_MAX)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = mASPTR_LIST_MAX - 1;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
	}
	else if(CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt < mASPTR_LIST_MIN)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = mASPTR_LIST_MIN;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
	}
}

/*	De Code Usr commands for X Ray Parameters and asign its other duties*/
void DeCodeUsrCommand_XrayParmtrs()
{
	unsigned char TempPrevValue = 0, TempAcceptChange = 0;
/*	Decode KV Increment command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvIncSwPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV;
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV + 1;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x02);					//Argument 0x02 is cross check KV
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = TempPrevValue;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvIncSwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvIncSwLngPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV;
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV + 5;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x02);					//Argument 0x02 is cross check KV
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = TempPrevValue;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvIncSwLngPrs = FALSEE;
	}
	
/*	Decode KV Decrement command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvDecSwPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV;
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - 1;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x02);					//Argument 0x02 is cross check KV
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = TempPrevValue;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvDecSwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvDecSwLngPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV;
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV - 5;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x02);					//Argument 0x02 is cross check KV
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = TempPrevValue;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvDecSwLngPrs = FALSEE;
	}

/*	Decode mA Increment command	*/	
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Inc_SwPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt;
		CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt + 1;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x01);					//Argument 0x01 is cross check mA
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = TempPrevValue;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Inc_SwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Inc_SwLngPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt;
		CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt + 3;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x01);					//Argument 0x01 is cross check mA
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = TempPrevValue;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Inc_SwLngPrs = FALSEE;
	}	
	
/*	Decode mA Decrement command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Dec_SwPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt;
		CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt - 1;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x01);					//Argument 0x01 is cross check mA
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = TempPrevValue;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Dec_SwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Dec_SwLngPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt;
		CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt - 3;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x01);					//Argument 0x01 is cross check mA
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = TempPrevValue;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.mA_Dec_SwLngPrs = FALSEE;
	}	
	
/*	Decode mAS/Time Increment command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsInc_SwPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt;
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt + 1;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x00);					//Argument 0x00 is cross check mAs
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = TempPrevValue;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsInc_SwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsInc_SwLngPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt;
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt + 3;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x00);					//Argument 0x00 is cross check mAs
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = TempPrevValue;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsInc_SwLngPrs = FALSEE;
	}	
	
/*	Decode mAS/Time Decrement command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsDec_SwPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt;
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - 1;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x00);					//Argument 0x00 is cross check mAs
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = TempPrevValue;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsDec_SwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsDec_SwLngPrs == TRUEE)	{
		TempPrevValue = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt;
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt - 3;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
		LimitXrayParameters();
		TempAcceptChange = Normalise_XrayParamtr(0x00);					//Argument 0x00 is cross check mAs
		if(TempAcceptChange == FALSEE)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = TempPrevValue;
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsDec_SwLngPrs = FALSEE;
	}	
}

/*	De Code Usr commands for APR related activities and data fetching and asign its other duties*/
void DeCodeUsrCommand_OpMode()
{
/*	Decode Mode Selection	*/
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.ModeSwPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode = CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode + 1;
		if((CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode >= NUM_OF_OPMODES)||(LowPowerModeLockVar == LOWPWR_MODE_LOCK_VALUE))	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode = 0;
		}
//	Fetch KV, MAS,mA when system enter to APR mode
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode == 1)		{//APR Mode
			FetchAPR_Data(0xff);
			CntrlPrmtrs.KeyPadFn1Sts.Field.PreSetSts = FALSEE;	//To disable if Preset is enabled
			CntrlPrmtrs.IntraSysCtrlDat.Field.PreSetLED = CntrlPrmtrs.KeyPadFn1Sts.Field.PreSetSts;
		}
		CntrlPrmtrs.IntraSysCtrlDat.all |= 0xff ;		//This is to update all the LCD fields in APR mode
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.ModeSwPrs = FALSEE;
	}
	
/*	Decode Patient Selection	*/
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.PatientSwPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType = CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType + 1;
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType >= NUM_OF_PATIENT_TYPES)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType = 0;
		}
		
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode == 1)		{//If APR Mode
			FetchAPR_Data(0xff);
		}
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtPatientReqFlag = TRUEE;			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;					CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.PatientSwPrs = FALSEE;
	}
	
/*	Decode Body Part Selection	*/
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.AnatomySwPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy = CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy + 1;
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy >= NUM_OF_ANATOMY_TYPES)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy = 0;
		}
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode == 1)		{//If APR Mode
			FetchAPR_Data(0xff);
		}
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtAntmyReqFlag = TRUEE;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtViewReqFlag = TRUEE;								//Setting this flag as anatomy and view are inter-related
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.AnatomySwPrs = FALSEE;
	}
	
/*	Decode View type Selection	*/
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.ViewSwPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.AnatmyView = CntrlPrmtrs.KeyPadFn1Sts.Field.AnatmyView + 1;
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.AnatmyView >= NUM_OF_VIEWS_PER_ANATOMY)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.AnatmyView = 0;
		}
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode == 1)		{//If APR Mode
			FetchAPR_Data(0xff);
		}
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtViewReqFlag = TRUEE;								//Setting this flag as anatomy and view are inter-related
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.ViewSwPrs = FALSEE;
	}
}

/*	De Code Usr commands for collimator/Bucky/AEC and data fetching and asign its other duties*/
void DeCodeUsrCommand_XrayPeriphrls()
{
	/*	Decode Collimator Command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.CollimtrSwPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts = ~CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts;
		CntrlPrmtrs.IntraSysCtrlDat.Field.ColimtrLED = CntrlPrmtrs.KeyPadFn2Sts.Field.CollimatorSts;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.CollimtrSwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.CollimtrSwLngPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.CollimtrSwLngPrs = FALSEE;
		/*xxxxxxxxxxxxxxx Left for future Use...	xxxxxxxxxxxxxxxx*/
	}
		
/*	Decode Horizontal Bucky Command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.H_BucySwPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.H_BuckySts = ~CntrlPrmtrs.KeyPadFn2Sts.Field.H_BuckySts;
		CntrlPrmtrs.IntraSysCtrlDat.Field.HBukyLED = CntrlPrmtrs.KeyPadFn2Sts.Field.H_BuckySts;
		if(CntrlPrmtrs.KeyPadFn2Sts.Field.H_BuckySts == TRUEE)	{
			CntrlPrmtrs.KeyPadFn2Sts.Field.V_BuckySts = FALSEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.VBukyLED = CntrlPrmtrs.KeyPadFn2Sts.Field.V_BuckySts;
		}
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.H_BucySwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.H_BucySwLngPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.H_BucySwLngPrs = FALSEE;
		/*xxxxxxxxxxxxxxx Left for future Use...	xxxxxxxxxxxxxxxx*/
	}
	
/*	Decode Vertical Bucky Command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.V_BucySwPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.V_BuckySts = ~CntrlPrmtrs.KeyPadFn2Sts.Field.V_BuckySts;
		CntrlPrmtrs.IntraSysCtrlDat.Field.VBukyLED = CntrlPrmtrs.KeyPadFn2Sts.Field.V_BuckySts;
		if(CntrlPrmtrs.KeyPadFn2Sts.Field.V_BuckySts == TRUEE)	{
			CntrlPrmtrs.KeyPadFn2Sts.Field.H_BuckySts = FALSEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.HBukyLED = CntrlPrmtrs.KeyPadFn2Sts.Field.H_BuckySts;
		}
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.Global_Climtr_HVBky_Flag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.V_BucySwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.V_BucySwLngPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.V_BucySwLngPrs = FALSEE;
		/*xxxxxxxxxxxxxxx Left for future Use...	xxxxxxxxxxxxxxxx*/
	}	
}

/*	De Code Usr commands for Preset data fetching, Save Preset data and asign its other duties */
void DeCodeUsrCommand_PreSetFetch()
{
	unsigned short TempmAs = 0, TempmA = 0, TempTym = 0;
/*	Decode Preset Switch Command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.PresetSwPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.PreSetSts = ~CntrlPrmtrs.KeyPadFn1Sts.Field.PreSetSts;
		CntrlPrmtrs.IntraSysCtrlDat.Field.PreSetLED = CntrlPrmtrs.KeyPadFn1Sts.Field.PreSetSts;
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.PreSetSts == TRUEE)	{
			CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode = 0;			//Set automaticaly Operating mode in to NORMAL
			PopPresetProtocol();
			CntrlPrmtrs.IntraSysCtrlDat.all |= 0xff ;						//This is to update all the LCD fields in APR mode
			//	Calculate Time Required
			TempmAs = CntrlPrmtrs.PresentSetmAsx10;
			TempmA = CntrlPrmtrs.PresentSetmA;
			TempTym = (unsigned short)((TempmAs * 100)/TempmA);
			if(TempTym > 5000)	TempTym = 5000;
			else if(TempTym < 1)	TempTym = 1;
			CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = TempTym;
		}
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.PresetSwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.PresetSwLngPrs == TRUEE)	{
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.PresetSwLngPrs = FALSEE;
		/*xxxxxxxxxxxxxxx Left for future Use...	xxxxxxxxxxxxxxxx*/
	}	
	
/*	Decode SAVE Switch Command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.SaveSwPrs == TRUEE)	{
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.PreSetSts == TRUEE)	{
			SavPresetExposeProtocol();
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gDataSavedBit = TRUEE;
		}
#if	APR_SAVE_EN
		else if(CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode == 1)		{//APR Mode		//@@@@@@@@@@@@@@@
			SavAprExposeProtocol();
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gDataSavedBit = TRUEE;
		}
#endif
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.SaveSwPrs = FALSEE;
	}
	else if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.SaveSwLngPrs == TRUEE)	{
#if APR_SAVE_EN
		if(CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode == 1)		{//APR Mode		//@@@@@@@@@@@@@@@
			FetchAPR_Data(0x00);
			SavAprExposeProtocol();
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gDataSavedBit = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.all |= 0xff ;		//This is to update all the LCD fields in APR mode
		}
#endif			
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.SaveSwLngPrs = FALSEE;
	}	
}

/*	Key PAD Scaning and related action decision	while in fault state*/
void FaultSteScanKeyPadMatrix(void)
{
	if(KYPAD_ROW_uC != 0x0F)	{		//Scan only if any switch press activity is detected
		if(KeyPadScanTmr1 >= TMR1_5MS_10MS)	{	//Scan in 100Hz to reduce the EMI
			ScanColumn4();	//	Check Column4		
			KYPAD_COLMN_uC(0x00);			//Reseting column to zero for further detection
			KeyPadScanTmr1 = 0x00;
		}
	}
	else	{
		KvIncSwPrsTmr2 = TmAsIncSwPrsTmr2 = mAIncSwPrsTmr2 = ModeSwPrsTmr2 = 0x0;
		KvDecSwPrsTmr2 = TmAsDecSwPrsTmr2 = mADecSwPrsTmr2 = PatientSwPrsTmr2 = 0x00;
		HBukySwPrsTmr2 = ColmtrSwPrsTmr2 = BdyPrtSelSwPrsTmr2 = 0x00;
		VBukySwPrsTmr2 = PresetSwPrsTmr2 = SaveSwPrsTmr2 = ViewSwPrsTmr2 = 0x00;
		CntrlPrmtrs.KeyPadSwGp1IntLok.all = 0x00;						// To disable Key pad marix interlock flag
		CntrlPrmtrs.KeyPadSwGp2IntLok.all &= 0xFFC3;				// To disable ONLY Key pad marix interlock flag
		KYPAD_COLMN_uC(0x00);			//Reseting column to zero for further detection
	}
	
	/*	Decode SAVE Switch Command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.SaveSwPrs == TRUEE)	{
		FaultExplainRequest = 0xff;
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.SaveSwPrs = FALSEE;
		ComnDutyEvryKeyPrs();
	}
	
	//Buzzer Reset
	if(gBeepSoundTmr2 >= TMR2_100MS_200MS) {	
		BEEP_TOUCH_Dat(DISABLE);
		CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = DISABLE;
	}
}

/*	Key PAD Scaning and related action decision	*/
void ScanKeyPadMatrix(void)
{
	if(KYPAD_ROW_uC != 0x0F)	{		//Scan only if any switch press activity is detected
		if(KeyPadScanTmr1 >= TMR1_5MS_10MS)	{	//Scan in 100Hz to reduce the EMI
			ScanColumn1();	//	Check Column1
			ScanColumn2();	//	Check Column2
			ScanColumn3();	//	Check Column3
			ScanColumn4();	//	Check Column4		
			KYPAD_COLMN_uC(0x00);			//Reseting column to zero for further detection
			KeyPadScanTmr1 = 0x00;
			SystemSleepTmr2 = 0;
		}
	}
	else	{
		KvIncSwPrsTmr2 = TmAsIncSwPrsTmr2 = mAIncSwPrsTmr2 = ModeSwPrsTmr2 = 0x0;
		KvDecSwPrsTmr2 = TmAsDecSwPrsTmr2 = mADecSwPrsTmr2 = PatientSwPrsTmr2 = 0x00;
		HBukySwPrsTmr2 = ColmtrSwPrsTmr2 = BdyPrtSelSwPrsTmr2 = 0x00;
		VBukySwPrsTmr2 = PresetSwPrsTmr2 = SaveSwPrsTmr2 = ViewSwPrsTmr2 = 0x00;
		CntrlPrmtrs.KeyPadSwGp1IntLok.all = 0x00;						// To disable Key pad marix interlock flag
		CntrlPrmtrs.KeyPadSwGp2IntLok.all &= 0xFFC3;				// To disable ONLY Key pad marix interlock flag
		KYPAD_COLMN_uC(0x00);			//Reseting column to zero for further detection
	}
	
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag == TRUEE)	{
		ComnDutyEvryKeyPrs();
		DeCodeUsrCommand_XrayParmtrs();
		DeCodeUsrCommand_OpMode();
		DeCodeUsrCommand_PreSetFetch();
		DeCodeUsrCommand_XrayPeriphrls();
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag =TRUEE;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = FALSEE;
	}
//Buzzer Reset
	if((gBeepSoundTmr2 >= TMR2_100MS_200MS)&&(CntrlPrmtrs.IntraSysCtrlDat.Field.CapBankChrgDne == TRUEE)) {	
		BEEP_TOUCH_Dat(DISABLE);
		CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = DISABLE;
	}
}

/*	Indipendant Keys like Ready, Exposure, ON and OFF*/
void ScanIndpndntKeys()
{
//	Ready Switch
	if(X_RAY_SW_STEP_uC == HHIGH)		{
		if((CntrlPrmtrs.KeyPadSwGp2IntLok.Field.Enable_SwPrs == FALSEE)&&(EnbleSwPrsTmr1 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.Enable_SwPrs = TRUEE;
			CntrlPrmtrs.KeyPadSwGp2IntLok.Field.Enable_SwPrs = TRUEE;
		}
		EnbleSwReleseTmr1 = 0x00;
		SystemSleepTmr2 = 0;
	}
	else	{
		if((CntrlPrmtrs.KeyPadSwGp2IntLok.Field.Enable_SwPrs == TRUEE)&&(EnbleSwReleseTmr1 >= TMR2_100MS_200MS))	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.Enable_SwPrs = FALSEE;
			CntrlPrmtrs.KeyPadSwGp2IntLok.Field.Enable_SwPrs = FALSEE;
		}		
		EnbleSwPrsTmr1 = 0x00;
	}
}

void CheckLowPwrModeKey()
{
	unsigned char TempVar = 0;
	
	if(LowPowrModeEntryBfr[0] == -1)	{
		TempVar |= 0x01;
	}
	if(LowPowrModeEntryBfr[1] == 0)	{
		TempVar |= 0x02;
	}
	if(LowPowrModeEntryBfr[2] == 1)	{
		TempVar |= 0x04;
	}
	
	if(TempVar == 0x07)	{
		LowPowerModeLockVar = LOWPWR_MODE_LOCK_VALUE;
	}
	else	{
		LowPowerModeLockVar = 0x00;
	}
}


/*	This function is to decode the calibration code service team has set*/
void DeCodeUsrCommand_CalibParmtrs()
{
	signed short temp = 0;
	unsigned char Temp1 = 0;
/*	Decode KV Increment command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvIncSwPrs == TRUEE)	{
		temp = 1;
		temp += CntrlPrmtrs.CalSts.Field.CalibPointer;
		if(temp > CAL_POINTER_MAX)	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
			temp = CAL_POINTER_MAX;
		}
		CntrlPrmtrs.CalSts.Field.CalibPointer = (unsigned char)temp;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		NewCalibPtrSel = 0xff;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvIncSwPrs = FALSEE;
	}
	
/*	Decode KV Decrement command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvDecSwPrs == TRUEE)	{
		temp = -1;
		temp += CntrlPrmtrs.CalSts.Field.CalibPointer;
		if(temp < CAL_POINTER_MIN)	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;
			temp = CAL_POINTER_MIN;
		}
		CntrlPrmtrs.CalSts.Field.CalibPointer = (unsigned char)temp;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		NewCalibPtrSel = 0xff;			
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.KvDecSwPrs = FALSEE;
	}
	
/*	Decode mAS/Time Increment command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsInc_SwPrs == TRUEE)	{
		temp = 1;
    if((CntrlPrmtrs.CalSts.Field.CalibPointer >= EEPROM_CORSE_CALIB_PTR_LOLIMIT)&&\
                    (CntrlPrmtrs.CalSts.Field.CalibPointer <= EEPROM_CORSE_CALIB_PTR_HILIMIT))  {
			temp += (signed char)CntrlPrmtrs.CalSts.Field.DeltaCalibVal;
			if(CntrlPrmtrs.CalSts.Field.CalibPointer > EEPROM_CORSE_CALIB_PTR_SUPRVSR_HILIMIT)	{
				if(temp > EEPROM_CORSE_CALIB_CONSOL_GAIN_HILIMIT)	{
					CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;    
					temp = EEPROM_CORSE_CALIB_CONSOL_GAIN_HILIMIT;
				}
			}
			else if(temp > EEPROM_CORSE_CALIB_GAIN_HILIMIT)	{
				CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;    
				temp = EEPROM_CORSE_CALIB_GAIN_HILIMIT;
			}
			CntrlPrmtrs.CalSts.Field.DeltaCalibVal = temp;
		}
		else if(((CntrlPrmtrs.CalSts.Field.CalibPointer >= EEPROM_FINE_CALIB_PTR_LOLIMIT)&&\
						(CntrlPrmtrs.CalSts.Field.CalibPointer <= EEPROM_FINE_CALIB_PTR_HILIMIT))||\
						((CntrlPrmtrs.CalSts.Field.CalibPointer >= LINE_LOWPWR_PTR1)&&(CntrlPrmtrs.CalSts.Field.CalibPointer <= LINE_LOWPWR_PTR3)))		{
			temp += (signed char)CntrlPrmtrs.CalSts.Field.DeltaCalibVal;
			if(temp > EEPROM_FINE_CALIB_GAIN_HILIMIT)	{
				CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;    
				temp = EEPROM_FINE_CALIB_GAIN_HILIMIT;
			}
			CntrlPrmtrs.CalSts.Field.DeltaCalibVal = temp;
		}
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsInc_SwPrs = FALSEE;
	}
/*	Decode mAS/Time Decrement command	*/
	if(CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsDec_SwPrs == TRUEE)	{
		temp = -1;
		if((CntrlPrmtrs.CalSts.Field.CalibPointer >= EEPROM_CORSE_CALIB_PTR_LOLIMIT)&&\
								(CntrlPrmtrs.CalSts.Field.CalibPointer <= EEPROM_CORSE_CALIB_PTR_HILIMIT))  {
			temp += (signed char)CntrlPrmtrs.CalSts.Field.DeltaCalibVal;
			if(CntrlPrmtrs.CalSts.Field.CalibPointer > EEPROM_CORSE_CALIB_PTR_SUPRVSR_HILIMIT)	{
				if(temp < EEPROM_CORSE_CALIB_CONSOL_GAIN_LOLIMIT)	{
					CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;    
					temp = EEPROM_CORSE_CALIB_CONSOL_GAIN_LOLIMIT;
				}
			}
			else if(temp < EEPROM_CORSE_CALIB_GAIN_LOLIMIT) {
				CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;    
				temp = EEPROM_CORSE_CALIB_GAIN_LOLIMIT;
			}
			CntrlPrmtrs.CalSts.Field.DeltaCalibVal = temp;
		}
		else if(((CntrlPrmtrs.CalSts.Field.CalibPointer >= EEPROM_FINE_CALIB_PTR_LOLIMIT)&&\
						(CntrlPrmtrs.CalSts.Field.CalibPointer <= EEPROM_FINE_CALIB_PTR_HILIMIT))||\
						((CntrlPrmtrs.CalSts.Field.CalibPointer >= LINE_LOWPWR_PTR1)&&(CntrlPrmtrs.CalSts.Field.CalibPointer <= LINE_LOWPWR_PTR3)))		{
			temp += (signed char)CntrlPrmtrs.CalSts.Field.DeltaCalibVal;
			if(temp < EEPROM_FINE_CALIB_GAIN_LOLIMIT) {
				CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = TRUEE;    
				temp = EEPROM_FINE_CALIB_GAIN_LOLIMIT;
			}
			CntrlPrmtrs.CalSts.Field.DeltaCalibVal = temp;
		}
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp1Sts.Field.TmAsDec_SwPrs = FALSEE;
	}
	
//	Decode Mode Switch Press
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.ModeSwPrs == TRUEE)	{
		if((CntrlPrmtrs.CalSts.Field.CalibPointer >= LINE_LOWPWR_PTR1)&&(CntrlPrmtrs.CalSts.Field.CalibPointer <= LINE_LOWPWR_PTR3))	{
			CheckLowPwrModeKey();
			ShowCalibResult(1);		//0: To show calibration results; 1: Match calibration pointers;
		}
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.ModeSwPrs = FALSEE;
	}
	
//	Decode Patient Switch Press
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.PatientSwPrs == TRUEE)	{
		if((CntrlPrmtrs.CalSts.Field.CalibPointer >= LINE_LOWPWR_PTR1)&&(CntrlPrmtrs.CalSts.Field.CalibPointer <= LINE_LOWPWR_PTR3))	{
			Temp1 = CntrlPrmtrs.CalSts.Field.CalibPointer - LINE_LOWPWR_PTR1;
			//************************* To be stored to NVM too	******************************
			LowPowrModeEntryBfr[Temp1] = CntrlPrmtrs.CalSts.Field.DeltaCalibVal;
			CheckLowPwrModeKey();
			ShowCalibResult(1);		//0: To show calibration results; 1: Match calibration pointers;
		}
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.PatientSwPrs = FALSEE;
	}
}


/*	Key PAD Scaning and related action decision when in CALIBRATION State	*/
void ScanKeyPadMatrix_CalibSte(void)
{
	if(KYPAD_ROW_uC != 0x0F)	{		//Scan only if any switch press activity is detected
		if(KeyPadScanTmr1 >= TMR1_5MS_10MS)	{	//Scan in 100Hz to reduce the EMI
			ScanColumn1();	//	Check Column1
			ScanColumn2();	//	Check Column2
			KYPAD_COLMN_uC(0x00);			//Reseting column to zero for further detection
			KeyPadScanTmr1 = 0x00;
		}
		SystemSleepTmr2 = 0;
	}
	else	{
		KvIncSwPrsTmr2 = TmAsIncSwPrsTmr2 = 0x0;
		KvDecSwPrsTmr2 = TmAsDecSwPrsTmr2 = 0x00;
		CntrlPrmtrs.KeyPadSwGp1IntLok.all = 0x00;						// To disable Key pad marix interlock flag
		CntrlPrmtrs.KeyPadSwGp2IntLok.all &= 0xFFC3;				// To disable ONLY Key pad marix interlock flag
		KYPAD_COLMN_uC(0x00);			//Reseting column to zero for further detection
	}
	
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag == TRUEE)	{
		CntrlPrmtrs.KeyPadSwGp1Sts.all &= 0x141400;							//These are to mask unwanted switch press activities in ScanColumn1() and ScanColumn2()
		ComnDutyEvryKeyPrs();
		DeCodeUsrCommand_CalibParmtrs();
		
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalLEDFlag =TRUEE;
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
		CntrlPrmtrs.KeyPadSwGp2Sts.Field.GlobalSwFlag = FALSEE;
	}
//Buzzer Reset
	if((gBeepSoundTmr2 >= TMR2_100MS_200MS)&&(CntrlPrmtrs.IntraSysCtrlDat.Field.CapBankChrgDne == TRUEE)) {	
		BEEP_TOUCH_Dat(DISABLE);
		CntrlPrmtrs.IntraSysCtrlDat.Field.BuzzerStats = DISABLE;
	}
}
