#ifndef GUICARDINTRFACE_H_
#define GUICARDINTRFACE_H_

#include "CcAbstLayer.h"
#include "irq.h"
#include  "XRAY_CAN.h"


/*	X RAY Tube related	*/
#define mA_MAX_SETBLE 650			//Maximum settable mA
#define mA_MIN_SETBLE 10			//Minimum settable mA

#define TUBE_OPRT_PWR_LVL 7
#define TUBE_PWRLVL_100mS 50000
#define TUBE_PWRLVL_500mS 35000
#define TUBE_PWRLVL_1000mS 25000
#define TUBE_PWRLVL_2000mS 20000
#define TUBE_PWRLVL_3000mS 15000
#define TUBE_PWRLVL_4000mS 12500
#define TUBE_PWRLVL_5000mS 10000

#define TUBE_DURATION_100mS 100
#define TUBE_DURATION_500mS 500
#define TUBE_DURATION_1000mS 1000
#define TUBE_DURATION_2000mS 2000
#define TUBE_DURATION_3000mS 3000
#define TUBE_DURATION_4000mS 4000
#define TUBE_DURATION_5000mS 5000

DWORD CANStatus,CAN1ErrCount;
extern CAN_MSG MsgBuf_TxINVCMD, MsgBuf_TxFILCMD, MsgBuf_TxCALIBCMD, MsgBuf_TxLICCMD; // TX Buffers for CAN message
extern CAN_MSG MsgBuf_RxINVANS, MsgBuf_RxFILANS, MsgBuf_RxCALIBANS, MsgBuf_RxLICANS; // RX Buffers for CAN message
extern short StationsOfmA[], StdmAsValues[];

#endif
