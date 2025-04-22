#include "NvmIntrface.h"

void InitFlashSsp()
{
//	Set PIN Configuration
	GuicPinNo_128_Fn(2);
#if NVM_AUTO_CS
	GuicPinNo_130_Fn(2);
#else
	GuicPinNo_130_Fn(0);
#endif
	GuicPinNo_126_Fn(2);
	GuicPinNo_124_Fn(2);
	GuicPinNo_75_Fn(0);
	GuicPinNo_79_Fn(0);
	//	Set Direction 1: Output;	0: Input
	GuicPinNo128_Dir(1);
	GuicPinNo130_Dir(1);
	GuicPinNo126_Dir(0);
	GuicPinNo124_Dir(1);
	GuicPinNo75_Dir(1);
	GuicPinNo79_Dir(1);
//	Set Pin Mode
	GuicPinNo128_Mod(0);
	GuicPinNo130_Mod(0);
	GuicPinNo126_Mod(0);
	GuicPinNo124_Mod(0);
	GuicPinNo75_Mod(0);
	GuicPinNo79_Mod(0);
//	Configure SSP0 Registers
	#if (Fpclk / (Fcclk / 4)) == 1		/* PCLK is 1/4 CCLK */	
	SSP0CPSR = 0x02;							//Clock Prescale Register for 3MHz
	SSP0CR0 = ((1 << 8)| 0x07);			//Control Register 0; 8 bit communication; 3MHz clock; SPI; LOW to HIGH clock
#elif (Fpclk / (Fcclk / 4)) == 2	/* PCLK is 1/2 CCLK */
	SSP0CPSR = 0x02;							//Clock Prescale Register for 3MHz
	SSP0CR0 = ((3 << 8)| 0x07);			//Control Register 0; 8 bit communication; 3MHz clock; SPI; LOW to HIGH clock	
#elif (Fpclk / (Fcclk / 4)) == 4	/* PCLK is the same as CCLK */
	SSP0CPSR = 0x04;							//Clock Prescale Register for 3MHz
	SSP0CR0 = ((3 << 8)| 0x07);			//Control Register 0; 8 bit communication; 3MHz clock; SPI; LOW to HIGH clock
#elif ((Fcclk / 4)/Fpclk) == 2		/* PCLK is 1/8 CCLK */
	SSP0CPSR = 0x02;							//Clock Prescale Register for 3MHz
	SSP0CR0 = ((0 << 8)| 0x07);			//Control Register 0; 8 bit communication; 3MHz clock; SPI; LOW to HIGH clock
#endif	

	SSP0DR = 0x00;								//Data Register
//	SSP1SR = 0x00;								//Status Register	- Read Only	
//	SSP1IMSC = 0x00;							//Interrupt Mask Set/Clear Register 
//	SSP1RIS  = 0x00;							//Raw Interrupt Status Register
//	SSP1MIS = 0x00;								//Masked Interrupt Status Register
//	SSP1ICR = 0x00;								//Interrupt Clear Register
//	SSP1DMACR = 0x00;							//DMA Control Register	
//	Following register need to be loaded after all other configurations
	SSP0CR1 = 0x02;								//Control Register 1; bit0 loop back mode; bit1 SSE enable; Bit2 Master(0)/slave(1) select; 
}

/************************************************************************
Function Name		: Data_Send
Input				: SPI_Data
Return Value		: None
Usage				: TO Define GPIO's 
***********************************************************************/
unsigned char Data_Send(unsigned char SPI_Data)	 	  
{
	unsigned char TempRcvdData;
	SSP0DR = SPI_Data;
	while (!(SSP0SR & SSPSR_RNE));
	TempRcvdData = SSP0DR;
	return TempRcvdData;
     // S0SPDR = SPI_Data;
	   // while(!(S0SPSR & SPIF));
		 // DATA_MEM = S0SPDR;
}
/************************************************************************
Function Name		: read_id
Input				: None
Return Value		: None
Usage				: TO Define GPIO's 
***********************************************************************/
unsigned char read_id(void)
{
	unsigned char status_reg,cntr=0,data;

#if !NVM_AUTO_CS
	FLASH_CS_Dat(LLOW);
#endif

	data = 0x9F;						
	Data_Send(data);
	while(cntr!=4)
	{
		data = 0x00;		
		status_reg = Data_Send(data);
		cntr++;
	}
	
#if !NVM_AUTO_CS
	FLASH_CS_Dat(HHIGH);
#endif
	return(status_reg);
}
/************************************************************************
Function Name		: Check_Busy_Flag
Input				: None
Return Value		: None
Usage				: TO Define GPIO's 
***********************************************************************/
void Check_Busy_Flag(void)
{
	unsigned char status_reg,data;
#if !NVM_AUTO_CS
	FLASH_CS_Dat(LLOW);
#endif
	Delay_1uSec(15);
	data = 0xD7;						
	Data_Send(data);
	while(status_reg!=0x80)
	{
		data		= 0x00;		
		status_reg = Data_Send(data);
		status_reg = status_reg & 0x80;	
	}
	Delay_1uSec(15);
#if !NVM_AUTO_CS
	FLASH_CS_Dat(HHIGH);
#endif
}

/************************************************************************
Function Name		: Write_NVM
Input				: NVM_Page_Address ,NVM_Byte_Location, NVM_No_Bytes
Return Value		: None
Usage				: TO Define GPIO's 
***********************************************************************/
void Write_NVM(NVM_DATA_STRUCT *NvmSendDatPtr)
{
	unsigned char NVM_Counter, NVM_No_Bytes;
	unsigned char AdressByte[3], TempVar, *TempBufrDatPtr;

	NVM_No_Bytes = NvmSendDatPtr->DataLen;
	TempBufrDatPtr = NvmSendDatPtr->NvmBufrAdrs;
	
	AdressByte[0] = NvmSendDatPtr->StartAdrs.all & 0xFF;
	AdressByte[1] = (NvmSendDatPtr->StartAdrs.all >> 8) & 0xFF;
	AdressByte[2] = (NvmSendDatPtr->StartAdrs.all >> 16) & 0xFF;
	while(NvmWriteDelayTmr1 <= TMR1_5MS_15MS);		//A delay of 10mS requirement was observed between 2 WRITE operation for NVM proper working
	Check_Busy_Flag();			    		//CHECK READ/BUSY FLAG OF STATUS REGISTER	
#if !NVM_AUTO_CS
	FLASH_CS_Dat(LLOW);
#endif
	Delay_1uSec(1);
	TempVar = Data_Send(NVM_READ_MODFY_WRITE);							       	//OPCODE FOR BUFFER1 WRITE
	TempVar = Data_Send(AdressByte[2]);
	TempVar = Data_Send(AdressByte[1]);
	TempVar = Data_Send(AdressByte[0]);
	for(NVM_Counter = 0; NVM_Counter<= NVM_No_Bytes; NVM_Counter++)
	{			
		TempVar = Data_Send(*TempBufrDatPtr);
		TempBufrDatPtr++;
		if(NVM_Counter >= (NVM_DAT_BUFR_SIZE - 1))	break;
	}
	Delay_1uSec(1);
#if !NVM_AUTO_CS
	FLASH_CS_Dat(HHIGH);
#endif
	Delay_1uSec(3000);							//Maximum time for page reprogram is 3mS; Can be fine tuned.
  Check_Busy_Flag();
	NvmWriteDelayTmr1 = 0;
}

/************************************************************************
Function Name		: Read_NVM
Input				: NVM_Page_Address ,NVM_Byte_Location, NVM_No_Bytes
Return Value		: None
Usage				: TO Define GPIO's 
***********************************************************************/
void Read_NVM(NVM_DATA_STRUCT *NvmReadDatPtr)
{
	unsigned char NVM_Counter, NVM_No_Bytes;
	unsigned char AdressByte[3], TempVar, *TempBufrDatPtr;
	
	NVM_No_Bytes = NvmReadDatPtr->DataLen;
	TempBufrDatPtr = NvmReadDatPtr->NvmBufrAdrs;
	
	AdressByte[0] = NvmReadDatPtr->StartAdrs.all & 0xFF;
	AdressByte[1] = (NvmReadDatPtr->StartAdrs.all >> 8) & 0xFF;
	AdressByte[2] = (NvmReadDatPtr->StartAdrs.all >> 16) & 0xFF;
	while(NvmWriteDelayTmr1 <= TMR1_5MS_15MS);		//A delay of 10mS requirement was observed between 2 WRITE operation for NVM proper working
#if !NVM_AUTO_CS
	FLASH_CS_Dat(LLOW);
#endif
	Delay_1uSec(1);
	Data_Send(NVM_READ_CMD);							//OPCODE FOR BUFFER1 WRITE
	TempVar = Data_Send(AdressByte[2]);
	TempVar = Data_Send(AdressByte[1]);
	TempVar = Data_Send(AdressByte[0]);	
	TempVar = Data_Send(0x00);
	TempVar = Data_Send(0x00);
	TempVar = Data_Send(0x00);
	TempVar = Data_Send(0x00);
	
	Data_Send(0x00);
	for(NVM_Counter = 0; NVM_Counter< NVM_No_Bytes; NVM_Counter++)
	{  
		*TempBufrDatPtr = Data_Send(0x00);
		TempBufrDatPtr++;
		if(NVM_Counter >= (NVM_DAT_BUFR_SIZE - 1))	break;
	}
	Delay_1uSec(1);
	NvmWriteDelayTmr1 = 0;
#if !NVM_AUTO_CS
	FLASH_CS_Dat(HHIGH);
#endif
}

void PopLastExposeProtocol()
{
	unsigned short TempVar = 0;
	NvmReadDat.DataLen = 6;	//2 for KV, 2 for mA, 2 for mAs
	NvmReadDat.NvmBufrAdrs = NVM_Data_Array;
	NvmReadDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmReadDat.StartAdrs.Field.ByteLoc = MNUEL_LAST_KV_LOC;
	Read_NVM(&NvmReadDat);
	TempVar = NVM_Data_Array[1];
	TempVar <<= 8;
	TempVar |= NVM_Data_Array[0];
	if(TempVar < MIN_KV_SET)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = FIRST_BOOT_KV;
	}
	else if(TempVar > MAX_KV_SET)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = FIRST_BOOT_KV;
	}
	else	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = TempVar;
	}
	TempVar = NVM_Data_Array[3];
	TempVar <<= 8;
	TempVar |= NVM_Data_Array[2];
	if(TempVar < mASPTR_LIST_MIN)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = FIRST_BOOT_mAS_ARR_COUNT;
	}
	else if(TempVar > mASPTR_LIST_MAX)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = FIRST_BOOT_mAS_ARR_COUNT;
	}
	else	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = TempVar;
	}	
}

void PopPresetProtocol()
{
	unsigned short TempVar = 0, TempChkVar = 0;
	NvmReadDat.DataLen = 6;	//2 for KV, 2 for mA, 2 for mAs
	NvmReadDat.NvmBufrAdrs = NVM_Data_Array;
	NvmReadDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmReadDat.StartAdrs.Field.ByteLoc = PRESEL_LAST_KV_LOC;
	Read_NVM(&NvmReadDat);
//	POP and Normalise KV data
	TempVar = NVM_Data_Array[1];
	TempVar <<= 8;
	TempVar |= NVM_Data_Array[0];
	if(TempVar < MIN_KV_SET)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = FIRST_BOOT_KV;
	}
	else if(TempVar > MAX_KV_SET)	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = FIRST_BOOT_KV;
	}
	else	{
		CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV = TempVar;
	}
//	POP and Normalise mAS data
	TempVar = NVM_Data_Array[3];
	TempVar <<= 8;
	TempVar |= NVM_Data_Array[2];
	if(TempVar < mASPTR_LIST_MIN)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = FIRST_BOOT_mAS_ARR_COUNT;
	}
	else if(TempVar > mASPTR_LIST_MAX)	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = FIRST_BOOT_mAS_ARR_COUNT;
	}
	else	{		
		CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt = TempVar;
	}		
	TempChkVar = Normalise_XrayParamtr(0x02);			//This is to check and Set valid mAS value for set KV if EEPROM is corrupted.
//	POP and Normalise mA data
	TempVar = NVM_Data_Array[5];
	TempVar <<= 8;
	TempVar |= NVM_Data_Array[4];
	if((TempVar < mAPTR_LIST_MIN)||(TempVar > mAPTR_LIST_MAX))	{
		CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = FIRST_BOOT_mA_ARR_COUNT;
	}
	else	{		
		CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt = TempVar;
	}	
	TempChkVar = Normalise_XrayParamtr(0x01);			//This is to check and Set valid mAS value for set KV if EEPROM is corrupted.
	if(TempChkVar == 0)	{
		TempChkVar = Normalise_XrayParamtr(0x00);			//This is to check and Set valid mAS value for set KV if EEPROM is corrupted.
	}
}

void PopLastCalibPointer()
{
	unsigned short TempVar = 0;
	NvmReadDat.DataLen = 1;	// For Calibration Pointer to save
	NvmReadDat.NvmBufrAdrs = NVM_Data_Array;
	NvmReadDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmReadDat.StartAdrs.Field.ByteLoc = LAST_CALB_PTR_LOC;
	Read_NVM(&NvmReadDat);
	TempVar = NVM_Data_Array[0];
	if(TempVar < CAL_POINTER_MIN)	{
		CntrlPrmtrs.CalSts.Field.CalibPointer = FIRMWARE_REV_PTR;
	}
	else if(TempVar > CAL_POINTER_MAX)	{
		CntrlPrmtrs.CalSts.Field.CalibPointer = FIRMWARE_REV_PTR;
	}
	else	{		
		CntrlPrmtrs.CalSts.Field.CalibPointer = TempVar & 0xFF;
	}	
}

void PushLastExposeProtocol()
{
	unsigned short TempVar = 0;
	NvmSendDat.DataLen = 6;	//2 for KV, 2 for mA, 2 for mAs
	NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
	NvmSendDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmSendDat.StartAdrs.Field.ByteLoc = MNUEL_LAST_KV_LOC;
	TempVar = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV;
	NVM_Data_Array[0] = TempVar & 0xFF;
	NVM_Data_Array[1] = (TempVar >> 8) & 0xFF;
	TempVar = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt;
	NVM_Data_Array[2] = TempVar & 0xFF;
	NVM_Data_Array[3] = (TempVar >> 8) & 0xFF;
	NVM_Data_Array[4] = 0x00;
	NVM_Data_Array[5] = 0x00;
	Write_NVM(&NvmSendDat);
}

void PushCalibExposeProtocol()
{
	unsigned short TempVar = 0;
	NvmSendDat.DataLen = 1;	// For Calibration Pointer to save
	NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
	NvmSendDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmSendDat.StartAdrs.Field.ByteLoc = LAST_CALB_PTR_LOC;
	TempVar = CntrlPrmtrs.CalSts.Field.CalibPointer;
	NVM_Data_Array[0] = TempVar & 0xFF;
	Write_NVM(&NvmSendDat);
}

void SavPresetExposeProtocol()
{
	unsigned short TempVar = 0;
	NvmSendDat.DataLen = 6;	//2 for KV, 2 for mA, 2 for mAs
	NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
	NvmSendDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmSendDat.StartAdrs.Field.ByteLoc = PRESEL_LAST_KV_LOC;
	TempVar = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV;
	NVM_Data_Array[0] = TempVar & 0xFF;
	NVM_Data_Array[1] = (TempVar >> 8) & 0xFF;
	TempVar = CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt;
	NVM_Data_Array[2] = TempVar & 0xFF;
	NVM_Data_Array[3] = (TempVar >> 8) & 0xFF;
	TempVar = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt;
	NVM_Data_Array[4] = TempVar & 0xFF;
	NVM_Data_Array[5] = (TempVar >> 8) & 0xFF;
	Write_NVM(&NvmSendDat);
}

void SavAprExposeProtocol()				//@@@@@@@@@@@@@@
{
#if	APR_SAVE_EN
	unsigned short TempVar = 0, TempVar1 = 0;
	unsigned char PatientType, BodyPart, PartView;
	NvmSendDat.DataLen = 6;	//2 for KV, 2 for mA, 2 for mAs
	NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
	TempVar1 = APR_DATA_PATIENTYPE_PAGE1_ADRS + CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType;
	NvmSendDat.StartAdrs.Field.PageAdrs = TempVar1;
	
	PatientType = CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType;
	BodyPart = CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy;
	PartView = CntrlPrmtrs.KeyPadFn1Sts.Field.AnatmyView;
	
	TempVar1 = EepromLocForAPR[PatientType][BodyPart][PartView];
	NvmSendDat.StartAdrs.Field.ByteLoc = TempVar1;
	
	TempVar = CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV;
	AprKv_Values[PatientType][BodyPart][PartView] = TempVar;			//RAM Location is added
	NVM_Data_Array[0] = TempVar & 0xFF;
	NVM_Data_Array[1] = (TempVar >> 8) & 0xFF;
	
	TempVar = CntrlPrmtrs.PresentSetmAsx10;
	Apr_mASx10_Values[PatientType][BodyPart][PartView] = TempVar;	//RAM Location is added
	NVM_Data_Array[2] = TempVar & 0xFF;
	NVM_Data_Array[3] = (TempVar >> 8) & 0xFF;
	
	TempVar = CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt;
	NVM_Data_Array[4] = TempVar & 0xFF;
	NVM_Data_Array[5] = (TempVar >> 8) & 0xFF;
	Write_NVM(&NvmSendDat);
#endif
}

void PopPowerModeKey()
{
	FLASH_RESET_uC_Dat(HHIGH);		// LOW: Reset
	FLASH_WPROT_uC_Dat(HHIGH);		// LOW: Write Protect
	Delay_1uSec(10);
	NvmReadDat.DataLen = 3;	//2 for KV, 2 for mA, 2 for mAs
	NvmReadDat.NvmBufrAdrs = NVM_Data_Array;
	NvmReadDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmReadDat.StartAdrs.Field.ByteLoc = PWRMOD_CHEK_KEY_LOC1;
	Read_NVM(&NvmReadDat);
	LowPowrModeEntryBfr[0] = (signed char)NVM_Data_Array[0];
	LowPowrModeEntryBfr[1] = (signed char)NVM_Data_Array[1];
	LowPowrModeEntryBfr[2] = (signed char)NVM_Data_Array[2];
}

void PushLowPowerModeKey()
{
	NvmSendDat.DataLen = 3;	//2 for KV, 2 for mA, 2 for mAs
	NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
	NvmSendDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmSendDat.StartAdrs.Field.ByteLoc = PWRMOD_CHEK_KEY_LOC1;
	NVM_Data_Array[0] = (unsigned char)-1;
	NVM_Data_Array[1] = (unsigned char)0;
	NVM_Data_Array[2] = (unsigned char)1;
	Write_NVM(&NvmSendDat);
}

void PushHiPowerModeKey()
{
	NvmSendDat.DataLen = 3;	//2 for KV, 2 for mA, 2 for mAs
	NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
	NvmSendDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmSendDat.StartAdrs.Field.ByteLoc = PWRMOD_CHEK_KEY_LOC1;
	NVM_Data_Array[0] = (unsigned char)1;
	NVM_Data_Array[1] = (unsigned char)1;
	NVM_Data_Array[2] = (unsigned char)-1;
	Write_NVM(&NvmSendDat);
}

void PopAPRdataToRAM(unsigned char PatientType, unsigned char BodyPart, unsigned char PartView)	//@@@@@@@@@@@@@@@@
{
#if APR_SAVE_EN
	unsigned short TempVar = 0, TempVar1 = 0;
	NvmReadDat.DataLen = 6;	//2 for KV, 2 for mA, 2 for mAs
	NvmReadDat.NvmBufrAdrs = NVM_Data_Array;
	TempVar1 = APR_DATA_PATIENTYPE_PAGE1_ADRS + PatientType;
	NvmReadDat.StartAdrs.Field.PageAdrs = TempVar1;
	TempVar1 = EepromLocForAPR[PatientType][BodyPart][PartView];
	NvmReadDat.StartAdrs.Field.ByteLoc = TempVar1;	
	Read_NVM(&NvmReadDat);
//	POP and Normalise KV data
	TempVar = NVM_Data_Array[1];
	TempVar <<= 8;
	TempVar |= NVM_Data_Array[0];	
	TempVar1 = AprDefltKv_Values[PatientType][BodyPart][PartView];	
	if((TempVar < (TempVar1 - 10))||(TempVar > (TempVar1 + 10)))	{
		AprKv_Values[PatientType][BodyPart][PartView] = AprDefltKv_Values[PatientType][BodyPart][PartView];
	}
	else	{
		AprKv_Values[PatientType][BodyPart][PartView] = TempVar;
	}
//	POP and Normalise mAS data
	TempVar = NVM_Data_Array[3];
	TempVar <<= 8;
	TempVar |= NVM_Data_Array[2];
	
	TempVar1 = FndOrdinalNumOfShortArr(StdmAsValues,mASPTR_LIST_MAX,TempVar);
	
	if(TempVar1 == 0x00)	{
		Apr_mASx10_Values[PatientType][BodyPart][PartView] = Apr_DefltmASx10_Values[PatientType][BodyPart][PartView];
	}
	else	{		
		Apr_mASx10_Values[PatientType][BodyPart][PartView] = TempVar;
	}		
#endif
}


void PushAPRdataToFlash(unsigned char PatientType, unsigned char BodyPart, unsigned char PartView)	//@@@@@@@@@@@@@@@@
{
#if APR_SAVE_EN
	unsigned short TempVar = 0, TempVar1 = 0;
	NvmSendDat.DataLen = 6;	//2 for KV, 2 for mA, 2 for mAs
	NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
	TempVar1 = APR_DATA_PATIENTYPE_PAGE1_ADRS + PatientType;
	NvmSendDat.StartAdrs.Field.PageAdrs = TempVar1;
	TempVar1 = EepromLocForAPR[PatientType][BodyPart][PartView];
	NvmSendDat.StartAdrs.Field.ByteLoc = TempVar1;	

//	Updating values to be loaded to flash
	AprKv_Values[PatientType][BodyPart][PartView] = AprDefltKv_Values[PatientType][BodyPart][PartView];
	TempVar = AprDefltKv_Values[PatientType][BodyPart][PartView];
	NVM_Data_Array[0] = TempVar & 0xFF;
	NVM_Data_Array[1] = (TempVar >> 8) & 0xFF;
	
	Apr_mASx10_Values[PatientType][BodyPart][PartView] = Apr_DefltmASx10_Values[PatientType][BodyPart][PartView];
	TempVar = Apr_DefltmASx10_Values[PatientType][BodyPart][PartView];
	NVM_Data_Array[2] = TempVar & 0xFF;
	NVM_Data_Array[3] = (TempVar >> 8) & 0xFF;
	NVM_Data_Array[4] = 0x00;
	NVM_Data_Array[5] = 0x00;
	Write_NVM(&NvmSendDat);	
#endif
}


unsigned char CheckFirstBoot()						//@@@@@@@@@@@@@@@@
{
	unsigned char TempVar[3];
	
	NvmReadDat.DataLen = 3;	
	NvmReadDat.NvmBufrAdrs = NVM_Data_Array;
	NvmReadDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
	NvmReadDat.StartAdrs.Field.ByteLoc = FIRST_BOOT_CHECK_LOC1;
	Read_NVM(&NvmReadDat);
	
	TempVar[0] = NVM_Data_Array[0];
	TempVar[1] = NVM_Data_Array[1];
	TempVar[2] = NVM_Data_Array[2];
	
	if((TempVar[0] == 'A')||(TempVar[1] == 'B')||(TempVar[2] == 'C'))
	{
		return NOT_A_FIRST_BOOT_ACK;	// Indicating that IT IS NOT A FIRST BOOTING.
	}
	else	{
		return FIRST_BOOT_ACK;	// Indicating that IT IS A FIRST BOOTING.
	}
}

unsigned char PushPopAPRValues()
{
	static unsigned char PatientType = 0, BodyPart = 0, PartView = 0, PushPopFinish = 0;
	
#if APR_SAVE_EN
	if(FirstBootRegstr == NOT_A_FIRST_BOOT_ACK)	{		//If not a first boot.
		if(PatientType < NUM_OF_PATIENT_TYPES)		{
			if(BodyPart < NUM_OF_ANATOMY_TYPES)			{
				if(PartView < NUM_OF_VIEWS_PER_ANATOMY)		{
					PopAPRdataToRAM(PatientType,BodyPart,PartView);
					PartView++;
				}
				else	{
					PartView = 0;
					BodyPart++;
				}
			}
			else	{
				PartView = 0;
				BodyPart = 0;
				PatientType++;
			}
		}
		else	{
			PushPopFinish = 0xff;
		}
	}
	else if(FirstBootRegstr == FIRST_BOOT_ACK)	{		//If it is a first boot.
		if(PatientType < NUM_OF_PATIENT_TYPES)		{
			if(BodyPart < NUM_OF_ANATOMY_TYPES)			{
				if(PartView < NUM_OF_VIEWS_PER_ANATOMY)		{
					PushAPRdataToFlash(PatientType,BodyPart,PartView);
					PartView++;
				}
				else	{
					PartView = 0;
					BodyPart++;
				}
			}
			else	{
				PartView = 0;
				BodyPart = 0;
				PatientType++;
			}
		}
		else if(PushPopFinish == 0x00)	{
			PushPopFinish = 0xff;
			NvmSendDat.DataLen = 3;	//2 for KV, 2 for mA, 2 for mAs
			NvmSendDat.NvmBufrAdrs = NVM_Data_Array;
			NvmSendDat.StartAdrs.Field.PageAdrs = MANUAL_DATA_PAGE_ADRS;
			NvmSendDat.StartAdrs.Field.ByteLoc = FIRST_BOOT_CHECK_LOC1;
			NVM_Data_Array[0] = 'A';
			NVM_Data_Array[1] = 'B';
			NVM_Data_Array[2] = 'C';
			Write_NVM(&NvmSendDat);
		}
	}
#else
	PushPopFinish = 0xff;
#endif
	return PushPopFinish;
}


