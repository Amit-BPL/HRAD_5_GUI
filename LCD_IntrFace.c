#include "LcdIntrFace.h"

/*	Convert binary data to ASCII value in terms od Decimal representation and make character string	*/
void DecodeValuToASCII(short ValuToCnvrt, unsigned char NoOfDigit, unsigned char EnDividx10, unsigned char *ArayPtr)
{
	short tempvar = 0;
	unsigned char loopvar = 0;
	unsigned char *tempArrLocAdrss;
	tempvar = ValuToCnvrt;
	tempArrLocAdrss = ArayPtr + NoOfDigit;
	*tempArrLocAdrss = '\0';													//To identify end of string.
	for(loopvar = 0;loopvar < NoOfDigit;loopvar++) {
		*--tempArrLocAdrss = (0x30 + (tempvar % 10));
		if(EnDividx10 == ENABLE)	{
			*--tempArrLocAdrss = '.';
			EnDividx10 = FALSEE;
			loopvar++;
		}
		tempvar /= 10;
	}
}

/*	Convert binary data to ASCII value in terms od HexaDecimal representation and make character string	*/
void DecodeHexValuToASCII(short ValuToCnvrt, unsigned char NoOfDigit, unsigned char *ArayPtr)
{
	short tempvar = 0;
	unsigned char loopvar = 0, tempvar1 =0;
	unsigned char *tempArrLocAdrss;
	tempvar = ValuToCnvrt;
	tempArrLocAdrss = ArayPtr + NoOfDigit;
	*tempArrLocAdrss = '\0';													//To identify end of string.
	for(loopvar = 0;loopvar < NoOfDigit;loopvar++) {
		tempvar1 = tempvar % 16;
		if(tempvar1 > 9)	{
			*--tempArrLocAdrss = (0x41 + (tempvar1 - 10));			//Here 0x41 is ASCII of 'A'
		}
		else	{
			*--tempArrLocAdrss = (0x30 + tempvar1);
		}
		tempvar /= 16;
	}
}

/*	This function is to show the animation of DOTS to indicate waiting*/
void ShowWaitStsLcd(unsigned char LcdRowNo,unsigned char LcdColmNo,unsigned char NofDots)
{
	static signed char PrsntDotCnt = 0, FrwrdOrRev = 1;
	
	if(FrwrdOrRev == 1)	{			//For forward animation
		LCD_SetCursor(LcdRowNo,LcdColmNo + PrsntDotCnt);					//ROW number and COLUMN number
		lcd_putchar ('.');
		PrsntDotCnt++;
		if(PrsntDotCnt >= NofDots)	FrwrdOrRev = 2;
	}
	else if(FrwrdOrRev == 2)	{
		LCD_SetCursor(LcdRowNo,LcdColmNo + PrsntDotCnt);					//ROW number and COLUMN number
		lcd_putchar (' ');
		PrsntDotCnt--;
		if(PrsntDotCnt <= 0)		FrwrdOrRev = 1;	
	}	
}

void SleepScreenLCD(unsigned char Print4Line)
{
	
	lcd_clear();
	LCD_SetCursor(1,6);					//ROW number and COLUMN number
	lcd_printS(SleepMod_Line1);
	LCD_SetCursor(2,3);					//ROW number and COLUMN number
	lcd_printS(SleepMod_Line2);
/*currently if part is not working*/	
	if(Print4Line != 0x00)	{			
		LCD_SetCursor(3,1);					//ROW number and COLUMN number
		lcd_printS(SleepMod_Line3);
		LCD_SetCursor(4,5);					//ROW number and COLUMN number
		lcd_printS(SleepMod_Line4);
	}
}

/*	Group the strings to display on LCD in initialisation time.	*/
void DispInitScreenLCD()
{
	lcd_clear();
	lcd_clear();
	lcd_clear();
	LCD_SetCursor(1,1);					//ROW number and COLUMN number
	lcd_printS(CompanyName);
	LCD_SetCursor(2,1);					//ROW number and COLUMN number
	lcd_printS(CompanySubName);
	LCD_SetCursor(3,2);					//ROW number and COLUMN number
	lcd_printS(ProductName);
	LCD_SetCursor(4,4);					//ROW number and COLUMN number
	lcd_printS(StatusBooting);
	lcd_clear();
	lcd_clear();
	lcd_clear();
	LCD_SetCursor(1,1);					//ROW number and COLUMN number
	lcd_printS(CompanyName);
	LCD_SetCursor(2,1);					//ROW number and COLUMN number
	lcd_printS(CompanySubName);
	LCD_SetCursor(3,2);					//ROW number and COLUMN number
	lcd_printS(ProductName);
	LCD_SetCursor(4,4);					//ROW number and COLUMN number
	lcd_printS(StatusBooting);
}

void DispNormalScreenLCD()
{
	unsigned short temp = 0;
	if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag == TRUEE)	{
		if(CntrlPrmtrs.IntraSysCtrlDat.Field.CalibEnDisabl == DISABLE)		{
			if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtModReqFlag == TRUEE)	{								//Display Operating Mode
				LCD_SetCursor(1,1);					//ROW number and COLUMN number
				lcd_printS(OpModeLcdDataPtr[CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode]);
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtModReqFlag = FALSEE;			
			}
	//	APR Mode	...........
			if(CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode == 1)	{
				if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtPatientReqFlag == TRUEE)	{						//Display Patient type
					LCD_SetCursor(1,11);					//ROW number and COLUMN number
					lcd_printS(PatientTypLcdDataPtr[CntrlPrmtrs.KeyPadFn1Sts.Field.PatientType]);
					CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtPatientReqFlag = FALSEE;			
				}
				
				if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtAntmyReqFlag == TRUEE)	{						//Display Anatomy type
					LCD_SetCursor(2,1);					//ROW number and COLUMN number
					lcd_printS(AnatmyLcdDataPtr[CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy]);
					CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtAntmyReqFlag = FALSEE;			
				}
				
				if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtViewReqFlag == TRUEE)	{						//Display Anatomical View type
					LCD_SetCursor(2,11);					//ROW number and COLUMN number
					lcd_printS(AntmyToVewLcdDataPtr[CntrlPrmtrs.KeyPadFn1Sts.Field.Anatomy][CntrlPrmtrs.KeyPadFn1Sts.Field.AnatmyView]);
					CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtViewReqFlag = FALSEE;			
				}
			}

	//	Normal Mode	...........
			else if(CntrlPrmtrs.KeyPadFn1Sts.Field.OpratngMode == 0)	{
				if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtPatientReqFlag == TRUEE)	{						//Display Blank at Patient type
					LCD_SetCursor(1,11);					//ROW number and COLUMN number
					if(LowPowerModeLockVar == LOWPWR_MODE_LOCK_VALUE)	{
						lcd_printS(LoPwrMsg);				//Show low power stage on display
					}
					else	{
						lcd_printS(Blank_9Space);
					}
					CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtPatientReqFlag = FALSEE;			
				}
				
				if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtAntmyReqFlag == TRUEE)	{						//Display Blank at Anatomy type
					LCD_SetCursor(2,1);					//ROW number and COLUMN number
					lcd_printS(Blank_9Space);
					CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtAntmyReqFlag = FALSEE;			
				}
				
				if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtViewReqFlag == TRUEE)	{						//Display Blank at Anatomical View type
					LCD_SetCursor(2,11);					//ROW number and COLUMN number
					lcd_printS(Blank_9Space);
					CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtViewReqFlag = FALSEE;			
				}
			}
			if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag == TRUEE)	{						//Display KV
				LCD_SetCursor(4,1);					//ROW number and COLUMN number
				/*	Function variables for "DecodeValuToASCII" are value to be converted, number of digits to be displayed, decimal point is required, Buffer address	*/
				DecodeValuToASCII(CntrlPrmtrs.KeyPadFn2Sts.Field.UserSetKV, NO_OF_KV_DIGITS, DISABLE, KvValStringBufr);
				lcd_printS(KvValStringBufr);
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = FALSEE;			
			}
			
			if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag == TRUEE)	{						//Display mA
				LCD_SetCursor(4,9);					//ROW number and COLUMN number
				/*	Function variables for "DecodeValuToASCII" are value to be converted, number of digits to be displayed, decimal point is required, Buffer address	*/
				DecodeValuToASCII(StationsOfmA[CntrlPrmtrs.KeyPadFn1Sts.Field.mA_StationPtrCnt], NO_OF_mA_DIGITS, DISABLE, mAValStringBufr);
				lcd_printS(mAValStringBufr);
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = FALSEE;			
			}
			
			if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag == TRUEE)	{						//Display mAS/Time
				LCD_SetCursor(4,16);					//ROW number and COLUMN number
				/*	Function variables for "DecodeValuToASCII" are value to be converted, number of digits to be displayed, decimal point is required, Buffer address	*/
				DecodeValuToASCII(StdmAsValues[CntrlPrmtrs.KeyPadFn1Sts.Field.Std_mAsPtrCnt], NO_OF_TmAS_DIGITS, ENABLE, TmASValStringBufr);
				lcd_printS(TmASValStringBufr);
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = FALSEE;			
			}	
		}	
		else	{	// IF CALIBRATION STATE
			if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag == TRUEE)	{						//Display KV
				LCD_SetCursor(4,1);					//ROW number and COLUMN number
				KvValStringBufr[0] = 'C';
				if(PreCalibSendEn == 0xFF)  {
						temp = PreCalibPointer;
				}
				else    {
						temp = CntrlPrmtrs.CalSts.Field.CalibPointer;
				} 
				/*	Function variables for "DecodeHexValuToASCII" are value to be converted, number of digits to be displayed, Buffer address	*/
				DecodeHexValuToASCII(temp, 2, KvValStringBufr+1);
				lcd_printS(KvValStringBufr);
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = FALSEE;			
			}
			
			if(CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag == TRUEE)	{						//Display mAS/Time
				LCD_SetCursor(4,15);					//ROW number and COLUMN number
				if(CntrlPrmtrs.IntraSysCtrlDat.Field.CalibPtrAbortTokn == TRUEE)	{
					TmASValStringBufr[0] = 'A';
					TmASValStringBufr[1] = 'b';
					TmASValStringBufr[2] = 'o';
					TmASValStringBufr[3] = 'r';
					TmASValStringBufr[4] = 't';
					TmASValStringBufr[5] = '\0';
					lcd_printS(TmASValStringBufr);
				}
				else if(CntrlPrmtrs.IntraSysCtrlDat.Field.WaitForTuhdEeprom == TRUEE)	{
					TmASValStringBufr[0] = '-';
					TmASValStringBufr[1] = '-';
					TmASValStringBufr[2] = '-';
					TmASValStringBufr[3] = TmASValStringBufr[4] = ' ';
					TmASValStringBufr[5] = '\0';
					lcd_printS(TmASValStringBufr);
					CntrlPrmtrs.IntraSysCtrlDat.Field.WaitForTuhdEeprom = FALSEE;
				}
				else{
					lcd_printS(Blank_5Space);
					LCD_SetCursor(4,15);					//ROW number and COLUMN number
					if((signed char)CntrlPrmtrs.CalSts.Field.DeltaCalibVal < 0)	{
						TmASValStringBufr[0] = '-';
					}
					else	{
						TmASValStringBufr[0] = ' ';
					}
					if(PreCalibSendEn == 0xFF)  {
							temp = abs((signed char)PreCalibGain);
					}
					else    {
							temp = abs((signed char)CntrlPrmtrs.CalSts.Field.DeltaCalibVal);
					}            
					if((CntrlPrmtrs.CalSts.Field.CalibPointer >= FIRMWARE_REV_PTR)&&(CntrlPrmtrs.CalSts.Field.CalibPointer <= TUHD_FIRMWARE_REV_PTR))  { //This is to show Firmware Revision
						/*	Function variables for "DecodeValuToASCII" are value to be converted, number of digits to be displayed, decimal point is required, Buffer address	*/
						DecodeValuToASCII(temp, 3, ENABLE, TmASValStringBufr);							//Number of position is 3 including decimal point.
					}
					else	{
						/*	Function variables for "DecodeValuToASCII" are value to be converted, number of digits to be displayed, decimal point is required, Buffer address	*/
						DecodeValuToASCII(temp, 2, DISABLE, TmASValStringBufr+1);						
					}
					lcd_printS(TmASValStringBufr);
				}
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = FALSEE;			
			}	
		}
		CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = FALSEE;
	}
}

unsigned char PrintCascadedString(const unsigned char *StringAdress, unsigned char SringStartLoc)
{
	const unsigned char *StringStartAdress = StringAdress;
	unsigned char StringEndLoc = 0, CharCount = 0;
	
	StringStartAdress = StringAdress + SringStartLoc;
	LCD_SetCursor(3,1);					//ROW number and COLUMN number
	lcd_printS(StatusBarBlankMsg);
	LCD_SetCursor(3,1);					//ROW number and COLUMN number	
	while ((*StringStartAdress)&&(CharCount < 19))  {		//20 charecter LCD is used
    lcd_putchar (*StringStartAdress++);
		CharCount++;
  }
		
	if(*StringStartAdress == '\0')	{
		StringEndLoc = 0;
		lcd_putchar ('|');
	}
	else	{
		StringEndLoc = SringStartLoc + CharCount;
		lcd_putchar ('>');
	}
	
	if(StringEndLoc > 0xFF)	StringEndLoc = 0xFF;
	
	return StringEndLoc;
}

unsigned char ExplainErrorCode()
{
	unsigned char TempErrCode = 0, PrsntSringStartLoc = 0;
	static unsigned char StringPntrOfset = 0;
	
	TempErrCode = CntrlPrmtrs.ErrFlds.Field.ErrorCode;
	PrsntSringStartLoc = StringPntrOfset;
	switch(TempErrCode)
	{
		case 1:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod001, PrsntSringStartLoc);
		}break;
		case 2:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod002, PrsntSringStartLoc);
		}break;
		case 3:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod003, PrsntSringStartLoc);
		}break;
		case 4:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod004, PrsntSringStartLoc);
		}break;
		case 5:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod005, PrsntSringStartLoc);
		}break;	
		case 6:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod006, PrsntSringStartLoc);
		}break;
		case 7:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod007, PrsntSringStartLoc);
		}break;
		case 8:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod008, PrsntSringStartLoc);
		}break;
		case 9:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod009, PrsntSringStartLoc);
		}break;
		case 10:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod010, PrsntSringStartLoc);
		}break;
		case 11:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod011, PrsntSringStartLoc);
		}break;
		case 12:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod012, PrsntSringStartLoc);
		}break;
		case 50:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod050, PrsntSringStartLoc);
		}break;
		case 51:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod051, PrsntSringStartLoc);
		}break;
		case 52:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod052, PrsntSringStartLoc);
		}break;
		case 53:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod053, PrsntSringStartLoc);
		}break;
		case 54:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod054, PrsntSringStartLoc);
		}break;
		case 55:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod055, PrsntSringStartLoc);
		}break;
		case 100:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod100, PrsntSringStartLoc);
		}break;
		case 101:	{
			StringPntrOfset = PrintCascadedString(ExplnErrCod101, PrsntSringStartLoc);
		}break;				
	}
	
	return StringPntrOfset;
}

void DispStatusLineLCD(unsigned char TimerVar)
{
	static unsigned char StatusToken = 0, VarForBlink = 0, TimerToken = 0, FaultMsgSwitch = 0;
	static unsigned short PrevPhaseVoltDispVal = 0;
	unsigned char TempVar = 0, TempStrngBfr[5] ;
	if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit == TRUEE)	{
//		if(TimerToken != TimerVar)	{	StatusToken = 0;	TimerToken = TimerVar;	}
		if(StatusToken != PRSNT_STS_LIMIT_EXEED)	{
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(StatusBarBlankMsg);
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(LimitOvrMsg);			
			StatusToken = PRSNT_STS_LIMIT_EXEED;
			LimitExeedMsgTmr2 = 0;
			LcdRefreshTmr2 = 0;					// Otherwise Automatic refresh replace this message before 1 sec at some occasions.
		}		
		if(LimitExeedMsgTmr2 > TMR2_100MS_1000MS)	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gLimitExeedBit = FALSEE;
		}
	}
	else if(CntrlPrmtrs.KeyPadSwGp2Sts.Field.gDataSavedBit == TRUEE)	{
		if(StatusToken != PRSNT_STS_SAVD_MSG)	{
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(StatusBarBlankMsg);
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(DataSavedMsg);			
			StatusToken = PRSNT_STS_SAVD_MSG;
			LimitExeedMsgTmr2 = 0;
			LcdRefreshTmr2 = 0;					// Otherwise Automatic refresh replace this message before 1 sec at some occasions.
		}		
		if(LimitExeedMsgTmr2 > TMR2_100MS_1000MS)	{
			CntrlPrmtrs.KeyPadSwGp2Sts.Field.gDataSavedBit = FALSEE;
		}
	}	
	else if((CntrlPrmtrs.IntraSysCtrlDat.Field.CapBankChrgDne == FALSEE)&&(eUc_States == STANDBY_STATE))	{
		if(TimerToken != TimerVar)	{	StatusToken = 0;	TimerToken = TimerVar;	}
		if(StatusToken != PRSNT_STS_CAP_CHARGE)	{
			if(VarForBlink == 0)	{
				LCD_SetCursor(3,1);					//ROW number and COLUMN number
				lcd_printS(StatusBarBlankMsg);
				VarForBlink = 0xFF;
			}
			else {
				LCD_SetCursor(2,1);					//ROW number and COLUMN number
				lcd_printS(StatusBarBlankMsg);
				LCD_SetCursor(3,1);					//ROW number and COLUMN number
				lcd_printS(CapChrgingMsg);
				VarForBlink = 0x00;
				}
			StatusToken = PRSNT_STS_CAP_CHARGE;
			
		}
	}
	else if(eUc_States == FAULT_STATE)	{
		if(TimerToken != TimerVar)	{	StatusToken = 0;	TimerToken = TimerVar;	}
		if(StatusToken != PRSNT_STS_FAULT)	{
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(StatusBarBlankMsg);
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(ErrMsg);			
			TempVar = CntrlPrmtrs.ErrFlds.Field.ErrorCode;
			DecodeValuToASCII(TempVar, 3, DISABLE, TempStrngBfr);
			lcd_printS(TempStrngBfr);
			StatusToken = PRSNT_STS_FAULT;
			FaultMsgSwitch = 0xFF;
		}		
		if(FaultExplainRequest == 0xff)	{	
			if(FaultMsgSwitch == 0)	{				//This is for display error code again after error explanation.
				StatusToken = 0;
			}
			else	{
				FaultMsgSwitch = ExplainErrorCode();
			}

			FaultExplainRequest = 0x00;
		}
	}
	else if((eUc_States == ENABLE_STATE)&&(CntrlPrmtrs.IntraSysCtrlDat.Field.ReadySts == FALSEE))	{
		if(StatusToken != PRSNT_STS_FIL_BOOST)	{
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(StatusBarBlankMsg);
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(FilBoostMsg);
			StatusToken = PRSNT_STS_FIL_BOOST;
		}	
		if(TimerToken != TimerVar)	{	
			ShowWaitStsLcd(3,17,3);						//Starting Location and number of dots
			TimerToken = TimerVar;	
		}
	}
	else if(eUc_States == COOLING_STATE)	{
		if(StatusToken != PRSNT_STS_COOLING)	{
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(StatusBarBlankMsg);
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(CoolingMsg);			
			StatusToken = PRSNT_STS_COOLING;
		}		
		if(TimerToken != TimerVar)	{	
			ShowWaitStsLcd(3,8,4);						//Starting Location and number of dots
			TimerToken = TimerVar;	
		}
	}
	else if(eUc_States == WARNING_STATE)	{
		if(TimerToken != TimerVar)	{	StatusToken = 0;	TimerToken = TimerVar;	}
		if(StatusToken != PRSNT_STS_WARNING)	{
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(StatusBarBlankMsg);
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(WarningMsg);			
			TempVar = CntrlPrmtrs.ErrFlds.Field.WarningCode;
			DecodeValuToASCII(TempVar, 2, DISABLE, TempStrngBfr);
			lcd_printS(TempStrngBfr);			
			StatusToken = PRSNT_STS_WARNING;
		}		
	}
	else if(DispLineFltTkn == HHIGH)	{
		if(TimerToken != TimerVar)	{	StatusToken = 0;	TimerToken = TimerVar;	}
		if(StatusToken != PRSNT_STS_CHEK_IP_MSG)	{
			if(VarForBlink == 0)	{
				LCD_SetCursor(3,1);					//ROW number and COLUMN number
				lcd_printS(StatusBarBlankMsg);
				VarForBlink = 0xFF;
			}
			else {
				LCD_SetCursor(3,1);					//ROW number and COLUMN number
				lcd_printS(CheckIPVMsg);
				VarForBlink = 0x00;
			}
			StatusToken = PRSNT_STS_CHEK_IP_MSG;
		}
	}
	else if(eUc_States == EXPOSURE_STATE)	{
		if(StatusToken != PRSNT_STS_EXPOSE)	{
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(StatusBarBlankMsg);
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(ExposingMsg);			
			StatusToken = PRSNT_STS_EXPOSE;
		}		
	}
	else	{
		if((StatusToken != PRSNT_STS_PHASE_VOLT)||(LcdRefreshTmr2 > TMR2_LCD_REFRESH_TME))	{
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(StatusBarBlankMsg);
			LCD_SetCursor(3,1);					//ROW number and COLUMN number
			lcd_printS(PhVoltMsg);			
			StatusToken = PRSNT_STS_PHASE_VOLT;
			PrevPhaseVoltDispVal = 0;
		}
		if((TimerToken != TimerVar)&&(PhaseVoltDispVal != PrevPhaseVoltDispVal))	
		{	
			LCD_SetCursor(3,15);					//ROW number and COLUMN number
			DecodeValuToASCII(PhaseVoltDispVal, 3, DISABLE, TempStrngBfr);
			lcd_printS(TempStrngBfr);			
			PrevPhaseVoltDispVal = PhaseVoltDispVal;
			TimerToken = TimerVar;	
			LCD_SetCursor(3,18);
			lcd_printS("   ");
		}		
	}
}

void FetchCalDltaTuhdEeprm()
{
	signed char TempVar = 0;
	unsigned char Temp1 = 0;
	if(NewCalibPtrSel == 0xff)  {
		if(Rs485RxFrame.PACK_1.Field.OutputKV == CntrlPrmtrs.CalSts.Field.CalibPointer)    {
			TempVar = (signed char)Rs485RxFrame.PACK_1.Field.OutputMA;
			if((TempVar <= EEPROM_CORSE_CALIB_GAIN_HILIMIT)||(CntrlPrmtrs.CalSts.Field.CalibPointer == SUP_FIRMWARE_REV_PTR)||\
				(CntrlPrmtrs.CalSts.Field.CalibPointer == TUHD_FIRMWARE_REV_PTR))   {   //This condition is to avoid, Set mA value being send from supervisor in ENABLE State, loading in "DeltaCalibVal"
				CntrlPrmtrs.CalSts.Field.DeltaCalibVal = (signed char)Rs485RxFrame.PACK_1.Field.OutputMA;
				NewCalibPtrSel = 0x00;
				CntrlPrmtrs.IntraSysCtrlDat.Field.WaitForTuhdEeprom = FALSEE;
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
				CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
			}
		}
		else    {
			CntrlPrmtrs.IntraSysCtrlDat.Field.WaitForTuhdEeprom = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
		}
		
		if(CntrlPrmtrs.CalSts.Field.CalibPointer == mAS_TYM_ADJST_PTR)	{
			CntrlPrmtrs.CalSts.Field.DeltaCalibVal = CorseCalibValus[mAS_TYM_ADJST_PTR - CALIBmAFIL_STATION1_PTR];
			NewCalibPtrSel = 0x00;
			CntrlPrmtrs.IntraSysCtrlDat.Field.WaitForTuhdEeprom = FALSEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
		}
		else if(CntrlPrmtrs.CalSts.Field.CalibPointer == IPVOLT_DISPADJ_PTR)	{
			CntrlPrmtrs.CalSts.Field.DeltaCalibVal = CorseCalibValus[IPVOLT_DISPADJ_PTR - CALIBmAFIL_STATION1_PTR];
			NewCalibPtrSel = 0x00;
			CntrlPrmtrs.IntraSysCtrlDat.Field.WaitForTuhdEeprom = FALSEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
		}
		else if(CntrlPrmtrs.CalSts.Field.CalibPointer == CALIB_COLIMTR_TMEADJ_PTR)	{
			CntrlPrmtrs.CalSts.Field.DeltaCalibVal = CorseCalibValus[CALIB_COLIMTR_TMEADJ_PTR - CALIBmAFIL_STATION1_PTR];
			NewCalibPtrSel = 0x00;
			CntrlPrmtrs.IntraSysCtrlDat.Field.WaitForTuhdEeprom = FALSEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
		}
		else if(CntrlPrmtrs.CalSts.Field.CalibPointer == FIRMWARE_REV_PTR)    //Console Software Revision
		{
			CntrlPrmtrs.CalSts.Field.DeltaCalibVal = (signed char)FIRMWARE_REV;
			NewCalibPtrSel = 0x00;
			CntrlPrmtrs.IntraSysCtrlDat.Field.WaitForTuhdEeprom = FALSEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
		}		
		else if((CntrlPrmtrs.CalSts.Field.CalibPointer >= LINE_LOWPWR_PTR1)&&(CntrlPrmtrs.CalSts.Field.CalibPointer <= LINE_LOWPWR_PTR3))
		{
			Temp1 = CntrlPrmtrs.CalSts.Field.CalibPointer - LINE_LOWPWR_PTR1;
			CntrlPrmtrs.CalSts.Field.DeltaCalibVal = LowPowrModeEntryBfr[Temp1];
			NewCalibPtrSel = 0x00;
			CntrlPrmtrs.IntraSysCtrlDat.Field.WaitForTuhdEeprom = FALSEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
		}
		else if(CntrlPrmtrs.CalSts.Field.CalibPointer == LINE_RESISTANCE_PTR)	{
			CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = 1000 + InvExposDelay;			// For measuring line resistance minimum 1 second exposure is required
		}
		else	{
			CntrlPrmtrs.KeyPadFn2Sts.Field.UsrSetTme1mS = 100 + InvExposDelay;
		}
	}
}

void ChekSelProtocolAbrtCndtn()     //  This function is to show "Abt" when user select protocol which is higher than inverter capacity on calibration mode
{
    static unsigned char CalibAbrtMsgEscToken = 0;
    if((Rs485RxFrame.PACK_2.Field.CalibAbort == TRUEE)||(CntrlPrmtrs.CalSts.Field.CalibPointer == 0xBD))    {
			CntrlPrmtrs.IntraSysCtrlDat.Field.CalibPtrAbortTokn = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
			CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
      CalibAbrtMsgEscToken = 0;
    }
    else if(CalibAbrtMsgEscToken == 0)  {
      CalibAbrtMsgEscToken = 0xff;
      NewCalibPtrSel = 0xff;  //This is to enter in to FetchCalDltaTuhdEeprm()
			CntrlPrmtrs.IntraSysCtrlDat.Field.CalibPtrAbortTokn = FALSEE;
      CntrlPrmtrs.CalSts.Field.DeltaCalibVal = 0x70;  // 0x70 is invalid value for calibvalue. This is to enter in to FetchCalDltaTuhdEeprm()
    }
}

void ShowCalibScreen(void)
{
	unsigned char temp;
	lcd_clear();									//This is required for clearing Initialising screen
	LCD_SetCursor(1,3);					//ROW number and COLUMN number
	lcd_printS(Om_Calibration);			
	LCD_SetCursor(3,1);					//ROW number and COLUMN number
	lcd_printS(PhVoltMsg);
	LCD_SetCursor(4,1);					//ROW number and COLUMN number
	KvValStringBufr[0] = 'C';
	/*	Function variables for "DecodeHexValuToASCII" are value to be converted, number of digits to be displayed, decimal point is required, Buffer address	*/
	temp = CntrlPrmtrs.CalSts.Field.CalibPointer;
	DecodeHexValuToASCII(temp, 2, KvValStringBufr+1);
	lcd_printS(KvValStringBufr);
	LCD_SetCursor(4,15);					//ROW number and COLUMN number
	if((signed char)CntrlPrmtrs.CalSts.Field.DeltaCalibVal < 0)	{
		TmASValStringBufr[0] = '-';
	}
	else	{
		TmASValStringBufr[0] = ' ';
	}
	temp = abs((signed char)CntrlPrmtrs.CalSts.Field.DeltaCalibVal);
	DecodeValuToASCII(temp, 2, DISABLE, TmASValStringBufr+1);
	lcd_printS(TmASValStringBufr);
}	

void ShowCalibResult(unsigned char MatchPrevPresPtr)
{
	static unsigned char PrevCalibPointer = 0xFF, BlankResult = 0xFF;
	static signed char PrevDeltaCalibVal = 0x7F;
	unsigned char TempVar = 0, TempStrngBfr[5];
	if((PrevCalibPointer == CntrlPrmtrs.CalSts.Field.CalibPointer)&&(PrevDeltaCalibVal == CntrlPrmtrs.CalSts.Field.DeltaCalibVal)&&(BlankResult == 0x00))	{
		if(((CntrlPrmtrs.CalSts.Field.CalibPointer >= EEPROM_CORSE_CALIB_PTR_LOLIMIT)&&(CntrlPrmtrs.CalSts.Field.CalibPointer <= EEPROM_CORSE_CALIB_PTR_HILIMIT))||\
			((CntrlPrmtrs.CalSts.Field.CalibPointer >= EEPROM_FINE_CALIB_PTR_LOLIMIT)&&(CntrlPrmtrs.CalSts.Field.CalibPointer <= EEPROM_FINE_CALIB_PTR_HILIMIT)))	{ 
			LCD_SetCursor(2,1);					//ROW number and COLUMN number
			lcd_printS(OutPutKvMsg);				
			DecodeValuToASCII(OutputKvLastExpos, 3, DISABLE, TempStrngBfr);
			lcd_printS(TempStrngBfr);
			LCD_SetCursor(2,11);					//ROW number and COLUMN number
			lcd_printS(OutPutmAMsg);				
			DecodeValuToASCII(OutputmALastExpos, 3, DISABLE, TempStrngBfr);
			lcd_printS(TempStrngBfr);
			BlankResult = 0xFF;
		}
		else if(CntrlPrmtrs.CalSts.Field.CalibPointer == LINE_RESISTANCE_PTR)	{
			CalculateLineRes();
			LCD_SetCursor(2,1);					//ROW number and COLUMN number
			lcd_printS(LineResMsg);				
			DecodeValuToASCII(LineResx10, 3, ENABLE, TempStrngBfr);
			lcd_printS(TempStrngBfr);
			BlankResult = 0xFF;
		}
		else if((CntrlPrmtrs.CalSts.Field.CalibPointer >= LINE_LOWPWR_PTR1)&&(CntrlPrmtrs.CalSts.Field.CalibPointer <= LINE_LOWPWR_PTR3))	{
			if(LowPowerModeLockVar == LOWPWR_MODE_LOCK_VALUE)	{
				LCD_SetCursor(2,1);					//ROW number and COLUMN number
				lcd_printS(LowPowrModMsg);	
				PushLowPowerModeKey();
			}
			else	{
				LCD_SetCursor(2,1);					//ROW number and COLUMN number
				lcd_printS(HighPowrModMsg);	
				PushHiPowerModeKey();
			}
			BlankResult = 0xFF;
		}
	}
	else if(MatchPrevPresPtr == ENABLE)	{
		PrevCalibPointer = CntrlPrmtrs.CalSts.Field.CalibPointer;
		PrevDeltaCalibVal = CntrlPrmtrs.CalSts.Field.DeltaCalibVal;
	}
	else if(((PrevCalibPointer != CntrlPrmtrs.CalSts.Field.CalibPointer)||(PrevDeltaCalibVal != CntrlPrmtrs.CalSts.Field.DeltaCalibVal))&&(BlankResult == 0xFF))	{			// Make Blank Row 2
		LCD_SetCursor(2,1);					//ROW number and COLUMN number
		lcd_printS(StatusBarBlankMsg);
		PrevDeltaCalibVal = 0x7F;
		PrevCalibPointer = 0xFF;
		BlankResult = 0x00;
	}
}

void RefreshLcdFrame()
{
	lcd_clear();									//This is required for clearing Initialising screen
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtModReqFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtPatientReqFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtAntmyReqFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtViewReqFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtKVReqFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtmAReqFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdUpdtTmAsReqFlag = TRUEE;
	CntrlPrmtrs.IntraSysCtrlDat.Field.LcdGloblUpdtReqFlag = TRUEE;
}



