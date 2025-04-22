#include "XRAY_CAN.h"

const unsigned int CanRxAdrsArr[TOTAL_RX_FRAME] = {INV_ANS_FRAME_RX_ADRS, FIL_ANS_FRAME_RX_ADRS, CALIB_ANS_FRAME_RX_ADRS, LICNC_ANS_FRAME_RX_ADRS};

CAN_MSG MsgBuf_TxINVCMD, MsgBuf_TxFILCMD, MsgBuf_TxCALIBCMD, MsgBuf_TxLICCMD; 									// TX Buffers for CAN message
CAN_MSG MsgBuf_TxRTR_INVANS, MsgBuf_TxRTR_FILANS, MsgBuf_TxRTR_CALIBANS, MsgBuf_TxRTR_LICANS; 	// RTR TX Buffers for CAN message

CAN_MSG MsgBuf_RxINVANS, MsgBuf_RxFILANS, MsgBuf_RxCALIBANS, MsgBuf_RxLICANS; 									// RX Buffers for CAN message

typedef struct
{
unsigned int Dat1; // Bits 0..10: CAN Message ID
				   // Bits 13..15: CAN interface number (1..4)
				   // Bits 16..19: DLC - Data Length Counter
				   // Bits 24..25: Semaphore bits
unsigned int DatA; // CAN Message Data Bytes 0-3
unsigned int DatB; // CAN Message Data Bytes 4-7

} FULLCAN_MSG;


/******************************************************************************
** Function name:		CAN_Init
**
** Descriptions:		Initialize CAN, install CAN interrupt handler
**
** parameters:			bitrate
** Returned value:		true or false, false if initialization failed.
** 
******************************************************************************/
DWORD CAN1_Init( DWORD can_btr )
{
  PCONP |= (1 << 13) | (1 << 14);	// Enable clock to the peripheral

  CAN1MOD = 1;	// Reset CAN
  CAN1IER = 0;	// Disable Receive Interrupt
  CAN1GSR = 0;	// Reset error counter when CANxMOD is in reset

  CAN1BTR = can_btr;
  CAN1MOD = 0x0;	// CAN in normal operation mode

  return( TRUE );
}


/******************************************************************************
** Function name:		CAN_SetACCF_Lookup
**
** Descriptions:		Initialize CAN, install CAN interrupt handler
**
** parameters:			bitrate
** Returned value:		true or false, false if initialization failed.
** 
******************************************************************************/
void CAN_SetACCF_Lookup( void )
{
  DWORD address = 0;
  DWORD i;
  DWORD ID_high, ID_low;

  // Set FULL CAN Frame  
  for ( i = 0; i < TOTAL_RX_FRAME; i += 2 )
  {
		ID_low = (1 << 27) | (CanRxAdrsArr[i] << 16);
		if((i+1) >= TOTAL_RX_FRAME)	{
			ID_high = (0x17FF << 0);				// Disable this 16 bit RAM location
		}
		else	{
			ID_high = ((1) << 11) | (CanRxAdrsArr[i+1] << 0);
		}		
		*((volatile DWORD *)(CAN_MEM_BASE + address)) = ID_low | ID_high;
		address += 4; 
  }
	CAN_SFF_SA = address;

  // Set group standard Frame 
  CAN_SFF_GRP_SA = address;
//  for ( i = 0; i < ACCF_IDEN_NUM; i += 2 )
//  {
//		ID_low = (i << 29) | (GRP_STD_ID << 16);
//		ID_high = ((i+1) << 13) | (GRP_STD_ID << 0);
//		*((volatile DWORD *)(CAN_MEM_BASE + address)) = ID_low | ID_high;
//		address += 4; 
//  }
 
  // Set explicit extended Frame 
  CAN_EFF_SA = address;
//  for ( i = 0; i < ACCF_IDEN_NUM; i++  )
//  {
//	ID_low = (i << 29) | (EXP_EXT_ID << 0);
//	*((volatile DWORD *)(CAN_MEM_BASE + address)) = ID_low;
//	address += 4; 
//  }

  // Set group extended Frame 
  CAN_EFF_GRP_SA = address;
//  for ( i = 0; i < ACCF_IDEN_NUM; i++  )
//  {
//	ID_low = (i << 29) | (GRP_EXT_ID << 0);
//	*((volatile DWORD *)(CAN_MEM_BASE + address)) = ID_low;
//	address += 4; 
//  }
   
  // Set End of Table 
  CAN_EOT = address;
  return;
}

/******************************************************************************
** Function name:		CAN_SetACCF
**
** Descriptions:		Set acceptance filter and SRAM associated with	
**
** parameters:			ACMF mode
** Returned value:		None
**
** 
******************************************************************************/
void CAN_SetACCF( DWORD ACCFMode )
{
  switch ( ACCFMode )
  {
	case ACCF_OFF:
	  CAN_AFMR = ACCFMode;
	  CAN1MOD = CAN2MOD = 1;	// Reset CAN
	  CAN1IER = CAN2IER = 0;	// Disable Receive Interrupt
	  CAN1GSR = CAN2GSR = 0;	// Reset error counter when CANxMOD is in reset
	break;

	case ACCF_BYPASS:
	  CAN_AFMR = ACCFMode;
	break;

	case ACCF_ON:
	case ACCF_FULLCAN:
	  CAN_AFMR = ACCF_OFF;
	  CAN_SetACCF_Lookup();
	  CAN_AFMR = ACCFMode;
	break;

	default:
	break;
  }
  return;
}

//	This function is used to collect data using polling method.
void CAN1_FULLCAN_POLL_RX()
{
	CAN_MSG_Ptr pCAN1_Rcv_Data_IRQ;
	FULLCAN_MSG *FULLCAN_msgs;
	unsigned int Dat1,DatA,DatB;
	unsigned int msg_index = 0;
	unsigned char test_bit =0;
	int i =0,j=0;
	unsigned int interrut_word = FCANIC0;
	for(j=0 ; j <2; j++)
	{
	  if((j==0x0) && (FCANIC0 !=0) )
		{
	      interrut_word = FCANIC0;
	  }
	  else if( (j==1) && (FCANIC1 !=0) ) 
		{
		  interrut_word = FCANIC1;
	  }
	  else	
		{
			continue;
	  }
	  if(interrut_word !=0)
		{
			for(i=0; i<=31;i++)
			{
				test_bit = interrut_word	& 0x1;
				interrut_word = interrut_word >>1;
				if(test_bit)
				{
	      	msg_index=i;
	      	FULLCAN_msgs= (FULLCAN_MSG *)(CAN_EOT + 0xE0038000 + msg_index*12);
	      	Dat1=FULLCAN_msgs->Dat1;
					do{
						if((Dat1 & 0x3000000) != 0x1000000){
							if((Dat1 & 0x3000000) == 0x3000000){
								FULLCAN_msgs->Dat1 = Dat1 & 0xFCFFFFFF;
								DatA = FULLCAN_msgs->DatA;
										DatB = FULLCAN_msgs->DatB;
								Dat1=FULLCAN_msgs->Dat1;
								if((Dat1 & 0x3000000) == 0x0000){
								break;
								}
							}
						}
						Dat1=FULLCAN_msgs->Dat1;
					}while (((Dat1 & 0x3000000) != 0x0));
					CntrlPrmtrs.CmnictnPrtoStsFlg.Field.DataRcvdSts = 1;	//indicate one Rx interrupt happened
					pCAN1_Rcv_Data_IRQ->MsgID = Dat1 & 0x7FF;
			
					switch(pCAN1_Rcv_Data_IRQ->MsgID)
					{
						case INV_ANS_FRAME_RX_ADRS: {	
							MsgBuf_RxINVANS.MsgID = pCAN1_Rcv_Data_IRQ->MsgID;	//	Frame ID
							MsgBuf_RxINVANS.Frame = Dat1 >> 11;									// All other bits except ID
							MsgBuf_RxINVANS.DataA = DatA;												//0-31 bits out of 64 bits..
							MsgBuf_RxINVANS.DataB = DatB;												//32-63 bits out of 64 bits..
							MsgBuf_RxINVANS.FULLCALmsg = 1;																
						} break;
						case FIL_ANS_FRAME_RX_ADRS: {	
							MsgBuf_RxFILANS.MsgID = pCAN1_Rcv_Data_IRQ->MsgID;	//	Frame ID
							MsgBuf_RxFILANS.Frame = Dat1 >> 11;									// All other bits except ID
							MsgBuf_RxFILANS.DataA = DatA;												//0-31 bits out of 64 bits..
							MsgBuf_RxFILANS.DataB = DatB;												//32-63 bits out of 64 bits..
							MsgBuf_RxFILANS.FULLCALmsg = 1;																
						} break;
						case CALIB_ANS_FRAME_RX_ADRS: {	
							MsgBuf_RxCALIBANS.MsgID = pCAN1_Rcv_Data_IRQ->MsgID;	//	Frame ID
							MsgBuf_RxCALIBANS.Frame = Dat1 >> 11;									// All other bits except ID
							MsgBuf_RxCALIBANS.DataA = DatA;												//0-31 bits out of 64 bits..
							MsgBuf_RxCALIBANS.DataB = DatB;												//32-63 bits out of 64 bits..
							MsgBuf_RxCALIBANS.FULLCALmsg = 1;																
						} break;
						case LICNC_ANS_FRAME_RX_ADRS: {	
							MsgBuf_RxLICANS.MsgID = pCAN1_Rcv_Data_IRQ->MsgID;	//	Frame ID
							MsgBuf_RxLICANS.Frame = Dat1 >> 11;									// All other bits except ID
							MsgBuf_RxLICANS.DataA = DatA;												//0-31 bits out of 64 bits..
							MsgBuf_RxLICANS.DataB = DatB;												//32-63 bits out of 64 bits..
							MsgBuf_RxLICANS.FULLCALmsg = 1;																
						} break;								
					}
				} //if testbit
			}	//for 0..31
		} //if interrut_word
	}//for j 0..2	
}

/******************************************************************************
** Function name:		CAN1_SendMessage
**
** Descriptions:		Send message block to CAN1	
**
** parameters:			pointer to the CAN message
** Returned value:		true or false, if message buffer is available,
**						message can be sent successfully, return TRUE,
**						otherwise, return FALSE.
** 
******************************************************************************/
DWORD CAN1_SendMessage( CAN_MSG *pTxBuf )
{
  DWORD CANStatus;

  CANStatus = CAN1SR;
  if ( CANStatus & 0x00000004 )
  {
	CAN1TFI1 = pTxBuf->Frame & 0xC00F0000;
	CAN1TID1 = pTxBuf->MsgID;
	CAN1TDA1 = pTxBuf->DataA;
	CAN1TDB1 = pTxBuf->DataB;
	CAN1CMR = 0x21;
	return ( TRUE );
  }
  else if ( CANStatus & 0x00000400 )
  {
	CAN1TFI2 = pTxBuf->Frame & 0xC00F0000;
	CAN1TID2 = pTxBuf->MsgID;
	CAN1TDA2 = pTxBuf->DataA;
	CAN1TDB2 = pTxBuf->DataB;
	CAN1CMR = 0x41;
	return ( TRUE );
  }
  else if ( CANStatus & 0x00040000 )
  {	
	CAN1TFI3 = pTxBuf->Frame & 0xC00F0000;
	CAN1TID3 = pTxBuf->MsgID;
	CAN1TDA3 = pTxBuf->DataA;
	CAN1TDB3 = pTxBuf->DataB;
	CAN1CMR = 0x81;
	return ( TRUE );
  }
  return ( FALSE );
}
