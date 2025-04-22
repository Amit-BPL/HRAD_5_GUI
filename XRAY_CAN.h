#ifndef XRAY_CAN_H_
#define XRAY_CAN_H_

#include "CcAbstLayer.h"

/*---------------------------------------------------------------------------*/
/*Sections can be enabled or disabled to the application specific needs		 */
/*---------------------------------------------------------------------------*/
 #define LPC2000_CANDRIVER_STD_FULLCAN
// #define LPC2000_CANDRIVER_STD_INDIVIDUAL
// #define LPC2000_CANDRIVER_STD_GROUP      
// #define LPC2000_CANDRIVER_EXT_INDIVIDUAL 
// #define LPC2000_CANDRIVER_EXT_GROUP   

#define ACCEPTANCE_FILTER_ENABLED	1

#define CAN_MEM_BASE		0xE0038000

#define MAX_PORTS	2		/* Number of CAN port on the chip */		

/* BRP+1 = Fpclk/(CANBitRate * QUANTAValue)
   QUANTAValue = 1 + (Tseg1+1) + (Tseg2+1)
   QUANTA value varies based on the Fpclk and sample point
   e.g. (1) sample point is 87.5%, Fpclk is 48Mhz
   the QUANTA should be 16
        (2) sample point is 90%, Fpclk is 12.5Mhz
   the QUANTA should be 10 
   Fpclk = Fclk /APBDIV
   or
   BitRate = Fcclk/(APBDIV * (BRP+1) * ((Tseg1+1)+(Tseg2+1)+1))
*/ 	
/* Here are some popular bit timing settings for LPC23xx, google on "SJA1000"
CAN bit timing, the same IP used inside LPC2000 CAN controller. There are several 
bit timing calculators on the internet. 
http://www.port.de/engl/canprod/sv_req_form.html
http://www.kvaser.com/can/index.htm
*/

/**
 * Bit Timing Values for 48MHz clk frequency
 */
#define LPC2000_CANDRIVER_CANBITRATE100K48MHZ          0x002B001D
#define LPC2000_CANDRIVER_CANBITRATE125K48MHZ          0x002B0017
#define LPC2000_CANDRIVER_CANBITRATE250K48MHZ          0x002B000B
#define LPC2000_CANDRIVER_CANBITRATE500K48MHZ          0x002B0005
#define LPC2000_CANDRIVER_CANBITRATE1000K48MHZ         0x002B0002

/**
 * Bit Timing Values for 60MHz clk frequency
 */
//#define LPC2000_CANDRIVER_CANBITRATE100K60MHZ          0x00180031
//#define LPC2000_CANDRIVER_CANBITRATE125K60MHZ          0x00180027
//#define LPC2000_CANDRIVER_CANBITRATE250K60MHZ          0x00180013
//#define LPC2000_CANDRIVER_CANBITRATE500K60MHZ          0x00180009
//#define LPC2000_CANDRIVER_CANBITRATE1000K60MHZ         0x00180004



/* Acceptance filter mode in AFMR register */
#define ACCF_OFF				0x01
#define ACCF_BYPASS				0x02
#define ACCF_ON					0x00
#define ACCF_FULLCAN			0x04

/**
 * Structure used for 11-bit CAN Identifiers
 */
typedef struct
{
  UInt8    Channel;
  UInt16   ID;

} lpc2000CANdriver_ACFilter_t;

/**
 * Structure used for 29-bit CAN Identifiers
 */
typedef struct
{
  UInt8    Channel;
  UInt32   IDx;

} lpc2000CANdriver_ACFilterx_t;

typedef struct
{
	DWORD FULLCALmsg;	
	DWORD Frame; 	// Bits 16..19: DLC - Data Length Counter
					// Bit 30: Set if this is a RTR message
					// Bit 31: Set if this is a 29-bit ID message
	DWORD MsgID;	// CAN Message ID (11-bit or 29-bit)
	DWORD DataA;	// CAN Message Data Bytes 0-3
	DWORD DataB;	// CAN Message Data Bytes 4-7
} CAN_MSG, *CAN_MSG_Ptr;

typedef struct
{
	unsigned int Priorty : 8;
	unsigned int Resrve1 : 8;
	unsigned int DataLen : 4;
	unsigned int Resrve2 : 10;
	unsigned int RmotFrmeReq : 1;					//1 is remote frame
	unsigned int FF_11bit0_29bit1 : 1;						//1 is extended frame (29 bit)	
} CnFrmeBrakUp;

typedef union
{
	unsigned int all;
	CnFrmeBrakUp Field;
}CanFrmeInfoBreakUp;

typedef struct
{
	unsigned int StndrdIDPart : 11;
	unsigned int ExtnddIDPart : 18;
	unsigned int Reserved1 : 3;
	
} CanIdBrakUp;

typedef union
{
	unsigned int all;
	CanIdBrakUp Field;
}CanIdBreakUp;

typedef struct
{
	CanFrmeInfoBreakUp CanFrmInfoBrkUp;
	CanIdBreakUp CanIdBrkUp;
}CanFrameHeader;

//	Used for Frame mapping using loop
typedef struct
{
    unsigned char FrameOrdinalNum;
    void (*callFramingFn)(void);
    DWORD (*callCanSendFn) (CAN_MSG*);
    CAN_MSG *pTxBuf;
} CAN_FRAME_MAP, *CAN_FRAME_PMAP;

#define INV_ANS_FRAME_RX_ADRS 304					//Identifier for Invertter command frame
#define FIL_ANS_FRAME_RX_ADRS 305					//Identifier for Filament/Rotor command frame
#define CALIB_ANS_FRAME_RX_ADRS 306				//Identifier for Calibration command frame
#define LICNC_ANS_FRAME_RX_ADRS 307				//Identifier for Licence command frame

#define TOTAL_RX_FRAME 4

#define INV_CMD_FRAME_TX_ADRS 204					//Identifier for Invertter command frame
#define FIL_CMD_FRAME_TX_ADRS 205					//Identifier for Filament/Rotor command frame
#define CALIB_CMD_FRAME_TX_ADRS 206				//Identifier for Calibration command frame
#define LICNC_CMD_FRAME_TX_ADRS 207				//Identifier for Licence command frame

#define TOTAL_TX_FRAME 4

#define NUM_OF_CAN_FRAMES TOTAL_TX_FRAME + TOTAL_RX_FRAME

extern CONTROL_PARAMETER CntrlPrmtrs;
extern DWORD CAN1_Init( DWORD );
extern void CAN_SetACCF( DWORD );

#endif
