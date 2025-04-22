#include "Rs485Communication.h"

void InitStringWith(volatile unsigned char *InitArryId,char ArrLoadVal,unsigned char ArraySize)	//array_name,load value,array_size
{
	unsigned char LocFn1Loop=0;
	for(LocFn1Loop=0;LocFn1Loop<ArraySize;LocFn1Loop++)
	{
		*(InitArryId+LocFn1Loop)=ArrLoadVal;
	}
}

void UpdtRs485Txdata()
{
	unsigned short TempVar = 0;
	Rs485TxFrame1.PACK_1.Field.FrameType = PNL_DATA_FRM1_ADRS >> 5;
	Rs485TxFrame1.PACK_1.Field.FrameAdrs = PNL_DATA_FRM1_ADRS & 0x1F;
	Rs485TxFrame1.PACK_1.Field.UcState = (unsigned char)eUc_States;
	TempVar = CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS + InvExposDelay;
	if((TempVar & 0xFF) == RS485_EOF_CHAR) TempVar = TempVar + 1;
  Rs485TxFrame1.PACK_1.Field.TimeMSB5 = ((TempVar >> 8) & 0x1F);
  Rs485TxFrame1.PACK_2.Field.TimeLSB8 = TempVar & 0xFF;

/*	mA is updated in NormPrmtrs() function	*/	
    if((eUc_States == CALIB_STATE)||(CntrlPrmtrs.IntraSysCtrlDat.Field.CalibEnDisabl == ENABLE))   {
        if(PreCalibSendEn == 0xff)  {
            Rs485TxFrame1.PACK_1.Field.SetKiloVt = PreCalibPointer;
            Rs485TxFrame1.PACK_1.Field.SetMilliA = PreCalibGain;
        }
        else    {
            Rs485TxFrame1.PACK_1.Field.SetKiloVt = CntrlPrmtrs.CalSts.Field.CalibPointer;
            Rs485TxFrame1.PACK_1.Field.SetMilliA = CntrlPrmtrs.CalSts.Field.DeltaCalibVal;
        }
    }
    else    {
        Rs485TxFrame1.PACK_1.Field.SetKiloVt = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV;
//#if MRAD5K0IDR_ENABLE
				if(CntrlPrmtrs.PresentSetmA < 10)	{				// In case of 15mA, TUHD and supervisor should receive 20 as those firmware is not capable of reciving 15mA. it is managed by reducing filament reference above 99kv.
					Rs485TxFrame1.PACK_1.Field.SetMilliA = 10;
				}
//#else		
//				if(CntrlPrmtrs.PresentSetmA < 20)	{				// In case of 15mA, TUHD and supervisor should receive 20 as those firmware is not capable of reciving 15mA. it is managed by reducing filament reference above 99kv.
//					Rs485TxFrame1.PACK_1.Field.SetMilliA = 20;
//				}
				else	{
					Rs485TxFrame1.PACK_1.Field.SetMilliA = CntrlPrmtrs.PresentSetmA;
				}
    }
    
	if(CntrlPrmtrs.ErrFlds.Field.EscErrSte == TRUEE)
		Rs485TxFrame1.PACK_2.Field.ErrRcovr = FAULT_ESC_CMD;
	else	Rs485TxFrame1.PACK_2.Field.ErrRcovr = NO_FAULT_ESC_CMD;

	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.Enable_SwPrs == TRUEE)		{
		Rs485TxFrame1.PACK_2.Field.XRayEnbl = XRAY_ENBL_CMD;
	}	else	Rs485TxFrame1.PACK_2.Field.XRayEnbl = XRAY_DSBL_CMD;
	
	if(eUc_States == EXPOSURE_STATE)
		Rs485TxFrame1.PACK_2.Field.XRayOnOf = XRAY_ON_CMD;
	else 	Rs485TxFrame1.PACK_2.Field.XRayOnOf = XRAY_OF_CMD;

	if(SystemSleepTmr2 >= TMR2_100MS_30MINUTES)	{
		Rs485TxFrame1.PACK_2.Field.ExpoMode = 0x0f;	//Radiography: 0; Pulsed fluoro: 1; Fluoro: 2;
	}
	else	{
		Rs485TxFrame1.PACK_2.Field.ExpoMode = 0x00;	//Radiography: 0; Pulsed fluoro: 1; Fluoro: 2;
	}
	Rs485TxFrame1.PACK_2.Field.EnblmAs = ENABLE;
	Rs485TxFrame1.PACK_2.Field.EndOfFrme = RS485_EOF_CHAR;
}

void Rs485TxFramer()
{
    unsigned char LoopVar = 0;
	if(CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxEnable == DISABLE)
	{
		Rs485TxBuffPtr = Rs485TxBuffr;	//Load the Buffer Base Address to the pointer
		Rs485TxBuffr[0] = Rs485TxFrame1.PACK_1.all & 0xFF;
		Rs485TxBuffr[1] = (Rs485TxFrame1.PACK_1.all >> 8) & 0xFF;
		Rs485TxBuffr[2] = (Rs485TxFrame1.PACK_1.all >> 16) & 0xFF;
		Rs485TxBuffr[3] = (Rs485TxFrame1.PACK_1.all >> 24) & 0xFF;
		Rs485TxBuffr[4] = Rs485TxFrame1.PACK_2.all & 0xFF;
		Rs485TxBuffr[5] = (Rs485TxFrame1.PACK_2.all >> 8) & 0xFF;
		Rs485TxBuffr[6] = (Rs485TxFrame1.PACK_2.all >> 16) & 0xFF;
        Rs485TxBuffr[7] = 0x00;
        for(LoopVar = 0; LoopVar < 7; LoopVar++)    Rs485TxBuffr[7] ^= Rs485TxBuffr[LoopVar];   //ADDING CRC
		Rs485TxBuffr[8] = (Rs485TxFrame1.PACK_2.all >> 24) & 0xFF;
	}
}

void Rs485TxDataFn()		//Function for RS485 transmission
{
	Rs485TxFramer();
	if((CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxEnable == ENABLE)&&\
(CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxFrmOvr == TRUEE))
	{		
		
		U1LCR = 0x2B;								//Enable 9th bit to ONE as Address bit (STICK 1 PARITY is used)
		RS485_RE_TE_Dat(HHIGH);			//Enable RS485 Tranceiver to Transmit mode		
		U1TER = 0x80;								//19Y07M02D
		U1THR = *Rs485TxBuffPtr;
		CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxFrmOvr = FALSEE;
		CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxAdrsOvr = FALSEE;
	}
	else if((CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxFrmOvr == FALSEE)&&(((U1LSR >> 5)& 0x01) == ENABLE))
	{
		if(*Rs485TxBuffPtr == RS485_EOF_CHAR)
		{
			if(((U1LSR >> 6)& 0x01) == HHIGH)	//TSR Register status bit
			{
				CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxFrmOvr = TRUEE;
				CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxAdrsOvr = FALSEE;
				CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxEnable = DISABLE;
				U1LCR = 0x2B;							//Enable 9th bit to ONE as Address bit (STICK 1 PARITY is used)
				RS485_RE_TE_Dat(LLOW);			//Enable RS485 Tranceiver to Receive mode
				U1TER = 0x00;								//19Y07M02D
			}
		}
		else if((((U1LSR >> 6)& 0x01) == HHIGH)||(CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxAdrsOvr == TRUEE))
		{	//	This condition checking is required to ensure address byte is send before setting 9th bit to zero.
			U1LCR = 0x3B;							//Disable 9th bit TO ZERO. These are data bytes (STICK 0 PARITY is used)
			Rs485TxBuffPtr++;
			U1THR = *Rs485TxBuffPtr;
			CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxAdrsOvr = TRUEE;
		}
	}
}

unsigned char ChekRxBuffrEOF()
{
	unsigned char i=0,j=0;
	while(Rs485RxBuffPtr > &Rs485RxBuffr[i])
	{
		if(Rs485RxBuffr[i] == RS485_EOF_CHAR) j = 1;
		else j = 0;
		i++;
	}
	return j;
}

void Rs485RxStrngDcodFn()	//Function to copy data to variables
{
  unsigned char LoopVar = 0, Rx_CRC_Data = 0;
	switch(Rs485RxBuffr[0])
	{
		case PNL_PRMTR_CMD_FRM1_ADRS:{
			Rx_CRC_Data = 0x00;
			for(LoopVar = 0; LoopVar < 7; LoopVar++)    Rx_CRC_Data ^= Rs485RxBuffr[LoopVar];
			if(Rx_CRC_Data == Rs485RxBuffr[7])  {
					Rs485RxFrame.PACK_1.all = Rs485RxBuffr[3];
					Rs485RxFrame.PACK_1.all <<= 8;	Rs485RxFrame.PACK_1.all |= Rs485RxBuffr[2];
					Rs485RxFrame.PACK_1.all <<= 8;	Rs485RxFrame.PACK_1.all |= Rs485RxBuffr[1];
					Rs485RxFrame.PACK_1.all <<= 8;	Rs485RxFrame.PACK_1.all |= Rs485RxBuffr[0];
					Rs485RxFrame.PACK_2.all = Rs485RxBuffr[8];
					Rs485RxFrame.PACK_2.all <<= 8;	Rs485RxFrame.PACK_2.all |= Rs485RxBuffr[6];
					Rs485RxFrame.PACK_2.all <<= 8;	Rs485RxFrame.PACK_2.all |= Rs485RxBuffr[5];
					Rs485RxFrame.PACK_2.all <<= 8;	Rs485RxFrame.PACK_2.all |= Rs485RxBuffr[4];
					eSupUc_States = (Uc_States)Rs485RxFrame.PACK_2.Field.UcState;
       }
            WarnStsChkTokn = 0xff;
		} break;

		case PNL_DATA_RQST_FRM1_ADRS:{
			Delay_1uSec(2000);					//This is to match the timing with supervisor.
			CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485TxEnable = ENABLE;
		} break;
	}
	InitStringWith(Rs485RxBuffr,'\0',RS485RX_BUF_SIZE);		//Clear the buffer with null character
	Rs485RxBuffPtr = Rs485RxBuffr;							//Initialize the pinter
}

void Rs485RxDataFn()	//Function for RS485 reception
{	
	unsigned char TempLSR = 0, TempData = 0;
	
	TempLSR = U1LSR;
	if(TempLSR & 0x01) {
		TempData = U1RBR;
		if((TempLSR & 0x04) == 0)	{			// Parity is being checked
			*Rs485RxBuffPtr = TempData;
			Rs485RxBuffPtr++;
			CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxEnable = ENABLE;
		}
		else	{
			CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxFrmOvr = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxEnable = DISABLE;
			InitStringWith(Rs485RxBuffr,'\0',RS485RX_BUF_SIZE);		//Clear the buffer with null character
			Rs485RxBuffPtr = Rs485RxBuffr;							//Initialize the pointer
			*Rs485RxBuffPtr = 0x00;
			U1LCR = 0x2B;							//Enable 9th bit to ONE as Address bit (STICK 1 PARITY is used)
		}
	}

	if(CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxEnable == ENABLE)
	{
		if(CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxFrmOvr == TRUEE)
		{
			switch(Rs485RxBuffr[0])
			{
				case PNL_PRMTR_CMD_FRM1_ADRS:{	U1LCR = 0x3B;							//Disable 9th bit TO ZERO. These are data bytes (STICK 0 PARITY is used)
					CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxFrmOvr = FALSEE;	} break;

				case PNL_DATA_RQST_FRM1_ADRS:{	U1LCR = 0x3B;							//Disable 9th bit TO ZERO. These are data bytes (STICK 0 PARITY is used)
					CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxFrmOvr = FALSEE;	} break;

				default:Rs485RxBuffPtr = Rs485RxBuffr;	break;
			}
		}
		if(CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxFrmOvr == FALSEE)
		{
			if((Rs485RxBuffr + RS485RX_BUF_SIZE)<Rs485RxBuffPtr)	//if the buffer is overflown
			{
				Rs485RxStrngDcodFn();
				CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxFrmOvr = TRUEE;
				U1LCR = 0x2B;							//Enable 9th bit to ONE as Address bit (STICK 1 PARITY is used)
			}
		}
		CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxEnable = DISABLE;
	}

	if(CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxFrmOvr == FALSEE)
	{
		if(ChekRxBuffrEOF())
		{
			Rs485RxStrngDcodFn();
			U1LCR = 0x2B;							//Enable 9th bit to ONE as Address bit (STICK 1 PARITY is used)
			CntrlPrmtrs.IntraSysCtrlDat.Field.Rs485RxFrmOvr = TRUEE;
		}
	}
}

