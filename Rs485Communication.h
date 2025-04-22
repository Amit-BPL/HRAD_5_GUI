#ifndef RS485COMMUNICATION_H_
#define RS485COMMUNICATION_H_

#include "CcAbstLayer.h"
#include <math.h>

//	RS485 Frame Addresses
#define	PNL_PRMTR_CMD_FRM1_ADRS 0x21	// 001 00001	-> Command frame1 from supervisor to panel controller
#define	PNL_PRMTR_CMD_FRM2_ADRS 0x24	// 001 00100	-> Command frame2 from supervisor to panel controller
#define	PNL_DATA_RQST_FRM1_ADRS 0x61	// 011 00001	-> Request frame from supervisor to send Pannel PCB Data set1
#define	PNL_DATA_RQST_FRM2_ADRS 0x64	// 011 00100	-> Request frame from supervisor to send Pannel PCB Data set2
#define	PNL_DATA_FRM1_ADRS 0x41			// 010 00001	-> User Set data set1 from PANEL CONTROLLER
#define	PNL_DATA_FRM2_ADRS 0x44			// 010 00100	-> User Set data set2 from PANEL CONTROLLER

#define RS485_EOF_CHAR 0xBD          //End of frame character
#define RS485RX_BUF_SIZE 14
#define RS485TX_BUF_SIZE 9

#define XRAY_ENBL_CMD 0x02
#define XRAY_DSBL_CMD 0x01
#define XRAY_ON_CMD 0x02
#define XRAY_OF_CMD 0x01
#define FAULT_ESC_CMD 0x02
#define NO_FAULT_ESC_CMD 0x01

RS485_PANL_TXF1 Rs485TxFrame1;		//Structure variable
RS485_PANL_RX Rs485RxFrame;

volatile unsigned char Rs485RxBuffr[RS485RX_BUF_SIZE],Rs485TxBuffr[RS485TX_BUF_SIZE];
volatile unsigned char *Rs485RxBuffPtr,*Rs485TxBuffPtr;

unsigned char PreCalibPointer = 0x03, PreCalibSendEn = 0x00, ConSupMachDelayTmr = 0, WarnStsChkTokn = 0x00;
signed char PreCalibGain = 0, InvExposDelay = 0;
extern unsigned short SystemSleepTmr2;
extern CONTROL_PARAMETER CntrlPrmtrs;
extern Uc_States eUc_States, eLastUc_States, eSupUc_States;

extern void Delay_1uSec(unsigned int);

#endif
