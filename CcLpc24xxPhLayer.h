/*	@PROJECT	: BPL-HRAD50																																	//
	@SUB PART	: HRAD50 CONTROL CARD																														//
	@FIRMWARE No: 417_FW_01 control Card Firmware																							//
	@REVISION	: R0xA																																					//
	@FILE 		: CcLpc24xxPhLayer.h																														//
	@SHEMATIC	: 417-S-001 Rev01																																//
	@AUTHER		: BABURAJ C.G.																																	//
	@CODING START DATE	:26 MAY 2018																													//
	@LAST UPDATE DATE	:																																				//
																																														//
	@AIM OF FIRMWARE: This project is intended to produce X-RAY having the variable 					//
				exposure parameters, as given below:																								//
				Tube Current	:	10mA to 600mA	(50kW Radiography)																		//
				Tube Voltage	:	40kv to 150kv 																											//
				The Duties of Control Card is listed below:																					//
				*	Send and Receive CAN command between GUI card																			//
				*	Act as supervisor and mediator between GUI and Generator													//
				*	Check	Faults in all cards	and control card it self																//
				*	Turn ON/OFF Inverter, Relay and contactors of Bucky																//
	@AIM OF FILE: This file is physical layer (Hardware) header file; This will be used 			//
				in Arbitration layer and application layer																					//
*/																																													//
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CCLPC24XXPHLAYER_H_
#define CCLPC24XXPHLAYER_H_

#include "lpc24xx.h"
#include "target.h"
#include "ssp.h"

//################################	Machine Model Description	######################################
#define MRAD3K6W 0
#if MRAD3K6W
	#define MRAD4K4W 0
	#define MRAD5K0W 0
#else
	#define MRAD4K4W 0
	#define MRAD5K0W 1
#endif

#define MRAD5K0IDR_ENABLE    1


//#######################################	End of Model	############################################
#define LINE_VOLT_180 180			//180 => 180v AC
#define LINE_VOLT_200 200			//200 => 200v AC
#define LINE_VOLT_240 240			//240 => 240v AC
#define LINE_VOLT_260 260			//260 => 260v AC

//Pin Function selection Definitions
#define GuicPinNo_94_Fn(x) PINSEL0 = ((PINSEL0 & 0xFFFFFFFC) | (x << 0))
#define GuicPinNo_96_Fn(x) PINSEL0 = ((PINSEL0 & 0xFFFFFFF3) | (x << 2))
#define GuicPinNo_164_Fn(x) PINSEL0 = ((PINSEL0 & 0xFFFFCFFF) | (x << 12))
#define GuicPinNo_162_Fn(x) PINSEL0 = ((PINSEL0 & 0xFFFF3FFF) | (x << 14))
#define GuicPinNo_158_Fn(x) PINSEL0 = ((PINSEL0 & 0xFFF3FFFF) | (x << 18))
#define GuicPinNo_41_Fn(x) PINSEL0 = ((PINSEL0 & 0xFCFFFFFF) | (x << 24))
#define GuicPinNo_69_Fn(x) PINSEL0 = ((PINSEL0 & 0xCFFFFFFF) | (x << 28))
#define GuicPinNo_120_Fn(x) PINSEL1 = ((PINSEL1 & 0xFFFFFCFF) | (x << 8))
#define GuicPinNo_177_Fn(x) PINSEL2 = ((PINSEL2 & 0xFFFFFF3F) | (x << 6))
#define GuicPinNo_171_Fn(x) PINSEL2 = ((PINSEL2 & 0xFFFFCFFF) | (x << 12))
#define GuicPinNo_188_Fn(x) PINSEL2 = ((PINSEL2 & 0xFFF3FFFF) | (x << 18))
#define GuicPinNo_186_Fn(x) PINSEL2 = ((PINSEL2 & 0xFFCFFFFF) | (x << 20))
#define GuicPinNo_163_Fn(x) PINSEL2 = ((PINSEL2 & 0xFF3FFFFF) | (x << 22))
#define GuicPinNo_184_Fn(x) PINSEL2 = ((PINSEL2 & 0xCFFFFFFF) | (x << 28))
#define GuicPinNo_182_Fn(x) PINSEL2 = ((PINSEL2 & 0x3FFFFFFF) | (x << 30))
#define GuicPinNo_180_Fn(x) PINSEL3 = ((PINSEL3 & 0xFFFFFFFC) | (x << 0))
#define GuicPinNo_178_Fn(x) PINSEL3 = ((PINSEL3 & 0xFFFFFFF3) | (x << 2))
#define GuicPinNo_70_Fn(x) PINSEL3 = ((PINSEL3 & 0xFFFFFCFF) | (x << 8))
#define GuicPinNo_42_Fn(x) PINSEL3 = ((PINSEL3 & 0xCFFFFFFF) | (x << 28))
#define GuicPinNo_40_Fn(x) PINSEL3 = ((PINSEL3 & 0x3FFFFFFF) | (x << 30))
#define GuicPinNo_187_Fn(x) PINSEL9 = ((PINSEL9 & 0xCFFFFFFF) | (x << 28))
#define GuicPinNo_111_Fn(x) PINSEL9 = ((PINSEL9 & 0xFFFFFF3F) | (x << 6))
#define GuicPinNo_105_Fn(x) PINSEL9 = ((PINSEL9 & 0xFFFFFFCF) | (x << 4))
#define GuicPinNo_159_Fn(x) PINSEL8 = ((PINSEL8 & 0xCFFFFFFF) | (x << 28))
#define GuicPinNo_155_Fn(x) PINSEL8 = ((PINSEL8 & 0xF3FFFFFF) | (x << 26))
#define GuicPinNo_149_Fn(x) PINSEL8 = ((PINSEL8 & 0xFCFFFFFF) | (x << 24))
#define GuicPinNo_145_Fn(x) PINSEL8 = ((PINSEL8 & 0xFF3FFFFF) | (x << 22))
#define GuicPinNo_135_Fn(x) PINSEL8 = ((PINSEL8 & 0xFFCFFFFF) | (x << 20))
#define GuicPinNo_131_Fn(x) PINSEL8 = ((PINSEL8 & 0xFFF3FFFF) | (x << 18))
#define GuicPinNo_127_Fn(x) PINSEL8 = ((PINSEL8 & 0xFFFCFFFF) | (x << 16))
#define GuicPinNo_121_Fn(x) PINSEL8 = ((PINSEL8 & 0xFFFF3FFF) | (x << 14))
#define GuicPinNo_107_Fn(x) PINSEL8 = ((PINSEL8 & 0xFFFFF3FF) | (x << 10))
#define GuicPinNo_97_Fn(x) PINSEL8 = ((PINSEL8 & 0xFFFFFF3F) | (x << 6))
#define GuicPinNo_83_Fn(x) PINSEL8 = ((PINSEL8 & 0xFFFFFFCF) | (x << 4))
#define GuicPinNo_25_Fn(x) PINSEL7 = ((PINSEL7 & 0x3FFFFFFF) | (x << 30))
#define GuicPinNo_19_Fn(x) PINSEL7 = ((PINSEL7 & 0xCFFFFFFF) | (x << 28))
#define GuicPinNo_28_Fn(x) PINSEL6 = ((PINSEL6 & 0x3FFFFFFF) | (x << 30))
#define GuicPinNo_21_Fn(x) PINSEL6 = ((PINSEL6 & 0xCFFFFFFF) | (x << 28))
#define GuicPinNo_7_Fn(x) PINSEL6 = ((PINSEL6 & 0xF3FFFFFF) | (x << 26))
#define GuicPinNo_1_Fn(x) PINSEL6 = ((PINSEL6 & 0xFCFFFFFF) | (x << 24))
#define GuicPinNo_208_Fn(x) PINSEL6 = ((PINSEL6 & 0xFF3FFFFF) | (x << 22))
#define GuicPinNo_205_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFCFFFFF) | (x << 20))
#define GuicPinNo_199_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFF3FFFF) | (x << 18))
#define GuicPinNo_191_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFFCFFFF) | (x << 16))
#define GuicPinNo_27_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFFF3FFF) | (x << 14))
#define GuicPinNo_23_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFFFCFFF) | (x << 12))
#define GuicPinNo_17_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFFFF3FF) | (x << 10))
#define GuicPinNo_13_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFFFFCFF) | (x << 8))
#define GuicPinNo_3_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFFFFF3F) | (x << 6))
#define GuicPinNo_207_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFFFFFCF) | (x << 4))
#define GuicPinNo_201_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFFFFFF3) | (x << 2))
#define GuicPinNo_197_Fn(x) PINSEL6 = ((PINSEL6 & 0xFFFFFFFC) | (x << 0))
#define GuicPinNo_110_Fn(x) PINSEL4 = ((PINSEL4 & 0xFFCFFFFF) | (x << 20))
#define GuicPinNo_152_Fn(x) PINSEL4 = ((PINSEL4 & 0xFFFFFFF3) | (x << 2))
#define GuicPinNo_154_Fn(x) PINSEL4 = ((PINSEL4 & 0xFFFFFFFC) | (x << 0))

/********Arun**************/
#define GuicPinNo_98_Fn(x) PINSEL0 = ((PINSEL0 & 0xFF3FFFFF) | (x << 22))
#define GuicPinNo_100_Fn(x) PINSEL0 = ((PINSEL0 & 0xFFCFFFFF) | (x << 20))
//End OF Pin Function selection Definitions

// Pin Direction Set defenition
#define	GuicPinNo94_Dir(x)	FIO0DIR0 =((FIO0DIR0 & 0xFE) | (x << 0))
#define	GuicPinNo96_Dir(x)	FIO0DIR0 =((FIO0DIR0 & 0xFD) | (x << 1))
#define	GuicPinNo164_Dir(x)	FIO0DIR0 =((FIO0DIR0 & 0xBF) | (x << 6))
#define	GuicPinNo162_Dir(x)	FIO0DIR0 =((FIO0DIR0 & 0x7F) | (x << 7))
#define	GuicPinNo158_Dir(x)	FIO0DIR1 =((FIO0DIR1 & 0xFD) | (x << 1))
#define	GuicPinNo41_Dir(x)	FIO0DIR1 =((FIO0DIR1 & 0xEF) | (x << 4))
#define	GuicPinNo69_Dir(x)	FIO0DIR1 =((FIO0DIR1 & 0xBF) | (x << 6))
#define	GuicPinNo120_Dir(x)	FIO0DIR2 =((FIO0DIR2 & 0xEF) | (x << 4))
#define	GuicPinNo177_Dir(x)	FIO1DIR0 =((FIO1DIR0 & 0xF7) | (x << 3))
#define	GuicPinNo171_Dir(x)	FIO1DIR0 =((FIO1DIR0 & 0xBF) | (x << 6))
#define	GuicPinNo188_Dir(x)	FIO1DIR1 =((FIO1DIR1 & 0xFD) | (x << 1))
#define	GuicPinNo186_Dir(x)	FIO1DIR1 =((FIO1DIR1 & 0xFB) | (x << 2))
#define	GuicPinNo163_Dir(x)	FIO1DIR1 =((FIO1DIR1 & 0xF7) | (x << 3))
#define	GuicPinNo184_Dir(x)	FIO1DIR1 =((FIO1DIR1 & 0xBF) | (x << 6))
#define	GuicPinNo182_Dir(x)	FIO1DIR1 =((FIO1DIR1 & 0x7F) | (x << 7))
#define	GuicPinNo180_Dir(x)	FIO1DIR2 =((FIO1DIR2 & 0xFE) | (x << 0))
#define	GuicPinNo178_Dir(x)	FIO1DIR2 =((FIO1DIR2 & 0xFD) | (x << 1))
#define	GuicPinNo70_Dir(x)	FIO1DIR2 =((FIO1DIR2 & 0xEF) | (x << 4))
#define	GuicPinNo42_Dir(x)	FIO1DIR3 =((FIO1DIR3 & 0xBF) | (x << 6))
#define	GuicPinNo40_Dir(x)	FIO1DIR3 =((FIO1DIR3 & 0x7F) | (x << 7))
#define	GuicPinNo187_Dir(x)	FIO4DIR3 =((FIO4DIR3 & 0xBF) | (x << 6))
#define	GuicPinNo111_Dir(x)	FIO4DIR2 =((FIO4DIR2 & 0xF7) | (x << 3))
#define	GuicPinNo105_Dir(x)	FIO4DIR2 =((FIO4DIR2 & 0xFB) | (x << 2))
#define	GuicPinNo159_Dir(x)	FIO4DIR1 =((FIO4DIR1 & 0xBF) | (x << 6))
#define	GuicPinNo155_Dir(x)	FIO4DIR1 =((FIO4DIR1 & 0xDF) | (x << 5))
#define	GuicPinNo149_Dir(x)	FIO4DIR1 =((FIO4DIR1 & 0xEF) | (x << 4))
#define	GuicPinNo145_Dir(x)	FIO4DIR1 =((FIO4DIR1 & 0xF7) | (x << 3))
#define	GuicPinNo135_Dir(x)	FIO4DIR1 =((FIO4DIR1 & 0xFB) | (x << 2))
#define	GuicPinNo131_Dir(x)	FIO4DIR1 =((FIO4DIR1 & 0xFD) | (x << 1))
#define	GuicPinNo127_Dir(x)	FIO4DIR1 =((FIO4DIR1 & 0xFE) | (x << 0))
#define	GuicPinNo121_Dir(x)	FIO4DIR0 =((FIO4DIR0 & 0x7F) | (x << 7))
#define	GuicPinNo107_Dir(x)	FIO4DIR0 =((FIO4DIR0 & 0xDF) | (x << 5))
#define	GuicPinNo97_Dir(x)	FIO4DIR0 =((FIO4DIR0 & 0xF7) | (x << 3))
#define	GuicPinNo83_Dir(x)	FIO4DIR0 =((FIO4DIR0 & 0xFB) | (x << 2))
#define	GuicPinNo25_Dir(x)	FIO3DIR3 =((FIO3DIR3 & 0x7F) | (x << 7))
#define	GuicPinNo19_Dir(x)	FIO3DIR3 =((FIO3DIR3 & 0xBF) | (x << 6))
#define	GuicPinNo28_Dir(x)	FIO3DIR1 =((FIO3DIR1 & 0x7F) | (x << 7))
#define	GuicPinNo21_Dir(x)	FIO3DIR1 =((FIO3DIR1 & 0xBF) | (x << 6))
#define	GuicPinNo7_Dir(x)	FIO3DIR1 =((FIO3DIR1 & 0xDF) | (x << 5))
#define	GuicPinNo1_Dir(x)	FIO3DIR1 =((FIO3DIR1 & 0xEF) | (x << 4))
#define	GuicPinNo208_Dir(x)	FIO3DIR1 =((FIO3DIR1 & 0xF7) | (x << 3))
#define	GuicPinNo205_Dir(x)	FIO3DIR1 =((FIO3DIR1 & 0xFB) | (x << 2))
#define	GuicPinNo199_Dir(x)	FIO3DIR1 =((FIO3DIR1 & 0xFD) | (x << 1))
#define	GuicPinNo191_Dir(x)	FIO3DIR1 =((FIO3DIR1 & 0xFE) | (x << 0))
#define	GuicPinNo27_Dir(x)	FIO3DIR0 =((FIO3DIR0 & 0x7F) | (x << 7))
#define	GuicPinNo23_Dir(x)	FIO3DIR0 =((FIO3DIR0 & 0xBF) | (x << 6))
#define	GuicPinNo17_Dir(x)	FIO3DIR0 =((FIO3DIR0 & 0xDF) | (x << 5))
#define	GuicPinNo13_Dir(x)	FIO3DIR0 =((FIO3DIR0 & 0xEF) | (x << 4))
#define	GuicPinNo3_Dir(x)	FIO3DIR0 =((FIO3DIR0 & 0xF7) | (x << 3))
#define	GuicPinNo207_Dir(x)	FIO3DIR0 =((FIO3DIR0 & 0xFB) | (x << 2))
#define	GuicPinNo201_Dir(x)	FIO3DIR0 =((FIO3DIR0 & 0xFD) | (x << 1))
#define	GuicPinNo197_Dir(x)	FIO3DIR0 =((FIO3DIR0 & 0xFE) | (x << 0))
#define	GuicPinNo110_Dir(x)	FIO2DIR1 =((FIO2DIR1 & 0xFB) | (x << 2))
#define	GuicPinNo152_Dir(x)	FIO2DIR0 =((FIO2DIR0 & 0xFD) | (x << 1))
#define	GuicPinNo154_Dir(x)	FIO2DIR0 =((FIO2DIR0 & 0xFE) | (x << 0))

/********Arun**************/
#define	GuicPinNo98_Dir(x)	FIO0DIR1 =((FIO0DIR1 & 0xF) | (x << 2))
#define	GuicPinNo100_Dir(x)	FIO0DIR1 =((FIO0DIR1 & 0xE) | (x << 3))
// End of Pin Direction Set defenition

// Pin Pullup/Tristate/Pulldown Set defenition
#define	GuicPinNo94_Mod(x)	PINMODE0 = ((PINMODE0 & 0xFFFFFFFC) | (x << 0))
#define	GuicPinNo96_Mod(x)	PINMODE0 = ((PINMODE0 & 0xFFFFFFF3) | (x << 2))
#define	GuicPinNo164_Mod(x)	PINMODE0 = ((PINMODE0 & 0xFFFFCFFF) | (x << 12))
#define	GuicPinNo162_Mod(x)	PINMODE0 = ((PINMODE0 & 0xFFFF3FFF) | (x << 14))
#define	GuicPinNo158_Mod(x)	PINMODE0 = ((PINMODE0 & 0xFFF3FFFF) | (x << 18))
#define	GuicPinNo41_Mod(x)	PINMODE0 = ((PINMODE0 & 0xFCFFFFFF) | (x << 24))
#define	GuicPinNo69_Mod(x)	PINMODE0 = ((PINMODE0 & 0xCFFFFFFF) | (x << 28))
#define	GuicPinNo120_Mod(x)	PINMODE1 = ((PINMODE1 & 0xFFFFFCFF) | (x << 8))
#define	GuicPinNo177_Mod(x)	PINMODE2 = ((PINMODE2 & 0xFFFFFF3F) | (x << 6))
#define	GuicPinNo171_Mod(x)	PINMODE2 = ((PINMODE2 & 0xFFFFCFFF) | (x << 12))
#define	GuicPinNo188_Mod(x)	PINMODE2 = ((PINMODE2 & 0xFFF3FFFF) | (x << 18))
#define	GuicPinNo186_Mod(x)	PINMODE2 = ((PINMODE2 & 0xFFCFFFFF) | (x << 20))
#define	GuicPinNo163_Mod(x)	PINMODE2 = ((PINMODE2 & 0xFF3FFFFF) | (x << 22))
#define	GuicPinNo184_Mod(x)	PINMODE2 = ((PINMODE2 & 0xCFFFFFFF) | (x << 28))
#define	GuicPinNo182_Mod(x)	PINMODE2 = ((PINMODE2 & 0x3FFFFFFF) | (x << 30))
#define	GuicPinNo180_Mod(x)	PINMODE3 = ((PINMODE3 & 0xFFFFFFFC) | (x << 0))
#define	GuicPinNo178_Mod(x)	PINMODE3 = ((PINMODE3 & 0xFFFFFFF3) | (x << 2))
#define	GuicPinNo70_Mod(x)	PINMODE3 = ((PINMODE3 & 0xFFFFFCFF) | (x << 8))
#define	GuicPinNo42_Mod(x)	PINMODE3 = ((PINMODE3 & 0xCFFFFFFF) | (x << 28))
#define	GuicPinNo40_Mod(x)	PINMODE3 = ((PINMODE3 & 0x3FFFFFFF) | (x << 30))
#define	GuicPinNo187_Mod(x)	PINMODE9 = ((PINMODE9 & 0xCFFFFFFF) | (x << 28))
#define	GuicPinNo111_Mod(x)	PINMODE9 = ((PINMODE9 & 0xFFFFFF3F) | (x << 6))
#define	GuicPinNo105_Mod(x)	PINMODE9 = ((PINMODE9 & 0xFFFFFFCF) | (x << 4))
#define	GuicPinNo159_Mod(x)	PINMODE8 = ((PINMODE8 & 0xCFFFFFFF) | (x << 28))
#define	GuicPinNo155_Mod(x)	PINMODE8 = ((PINMODE8 & 0xF3FFFFFF) | (x << 26))
#define	GuicPinNo149_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFCFFFFFF) | (x << 24))
#define	GuicPinNo145_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFF3FFFFF) | (x << 22))
#define	GuicPinNo135_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFFCFFFFF) | (x << 20))
#define	GuicPinNo131_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFFF3FFFF) | (x << 18))
#define	GuicPinNo127_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFFFCFFFF) | (x << 16))
#define	GuicPinNo121_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFFFF3FFF) | (x << 14))
#define	GuicPinNo107_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFFFFF3FF) | (x << 10))
#define	GuicPinNo97_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFFFFFF3F) | (x << 6))
#define	GuicPinNo83_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFFFFFFCF) | (x << 4))
#define	GuicPinNo25_Mod(x)	PINMODE7 = ((PINMODE7 & 0x3FFFFFFF) | (x << 30))
#define	GuicPinNo19_Mod(x)	PINMODE7 = ((PINMODE7 & 0xCFFFFFFF) | (x << 28))
#define	GuicPinNo28_Mod(x)	PINMODE6 = ((PINMODE6 & 0x3FFFFFFF) | (x << 30))
#define	GuicPinNo21_Mod(x)	PINMODE6 = ((PINMODE6 & 0xCFFFFFFF) | (x << 28))
#define	GuicPinNo7_Mod(x)	PINMODE6 = ((PINMODE6 & 0xF3FFFFFF) | (x << 26))
#define	GuicPinNo1_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFCFFFFFF) | (x << 24))
#define	GuicPinNo208_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFF3FFFFF) | (x << 22))
#define	GuicPinNo205_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFCFFFFF) | (x << 20))
#define	GuicPinNo199_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFF3FFFF) | (x << 18))
#define	GuicPinNo191_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFFCFFFF) | (x << 16))
#define	GuicPinNo27_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFFF3FFF) | (x << 14))
#define	GuicPinNo23_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFFFCFFF) | (x << 12))
#define	GuicPinNo17_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFFFF3FF) | (x << 10))
#define	GuicPinNo13_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFFFFCFF) | (x << 8))
#define	GuicPinNo3_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFFFFF3F) | (x << 6))
#define	GuicPinNo207_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFFFFFCF) | (x << 4))
#define	GuicPinNo201_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFFFFFF3) | (x << 2))
#define	GuicPinNo197_Mod(x)	PINMODE6 = ((PINMODE6 & 0xFFFFFFFC) | (x << 0))
#define	GuicPinNo110_Mod(x)	PINMODE4 = ((PINMODE4 & 0xFFCFFFFF) | (x << 20))
#define	GuicPinNo152_Mod(x)	PINMODE4 = ((PINMODE4 & 0xFFFFFFF3) | (x << 2))
#define	GuicPinNo154_Mod(x)	PINMODE4 = ((PINMODE4 & 0xFFFFFFFC) | (x << 0))
//END of Pin Pullup/Tristate/Pulldown Set defenition

//	Output Port Definition
#define	CAN_TX_Dat(x)	FIO0PIN0 =((FIO0PIN0 & 0xFD) | (x << 1))
#define	DAC_SSEL1_Dat(x)	FIO0PIN0 =((FIO0PIN0 & 0xBF) | (x << 6))
#define	DAC_SCLK1_Dat(x)	FIO0PIN0 =((FIO0PIN0 & 0x7F) | (x << 7))
#define	DAC_MOSI1_Dat(x)	FIO0PIN1 =((FIO0PIN1 & 0xFD) | (x << 1))
#define	DAC_LDAC_Dat(x)	FIO0PIN1 =((FIO0PIN1 & 0xBF) | (x << 6))
#define	RS485_RE_TE_Dat(x)	FIO0PIN2 =((FIO0PIN2 & 0xEF) | (x << 4))
#define	XRAY_ON_CMD_uC_Dat(x)	FIO1PIN0 =((FIO1PIN0 & 0xF7) | (x << 3))
#define	BEEP_TOUCH_Dat(x)	FIO1PIN0 =((FIO1PIN0 & 0xBF) | (x << 6))
#define	CONSOLE_STS_uC_Dat(x)	FIO1PIN1 =((FIO1PIN1 & 0xF7) | (x << 3))
#define	HV_85_PRCNT_LED_Uc_Dat(x)	FIO1PIN1 =((FIO1PIN1 & 0xBF) | (x << 6))
#define	VERTICAL_BUCKY_uC_Dat(x)	FIO1PIN1 =((FIO1PIN1 & 0x7F) | (x << 7))
#define	HORIZ_BUCKY_uC_Dat(x)	FIO1PIN2 =((FIO1PIN2 & 0xFE) | (x << 0))
#define	COLLIMATOR_uC_Dat(x)	FIO1PIN2 =((FIO1PIN2 & 0xFD) | (x << 1))
#define	POWER_SHUTDOWN_UC_Dat(x)	FIO1PIN2 =((FIO1PIN2 & 0xEF) | (x << 4))
#define	POWER_SW_LED_uC_Dat(x)	FIO4PIN3 =((FIO4PIN3 & 0xBF) | (x << 6))
#define	LCD_LSIC_EN_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xBF) | (x << 6))
#define	LCD_D3_uC_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xDF) | (x << 5))
#define	LCD_D2_uC_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xEF) | (x << 4))
#define	LCD_D1_uC_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xF7) | (x << 3))
#define	LCD_D0_uC_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xFB) | (x << 2))
#define	LCD_EN_uC_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xFD) | (x << 1))
#define	LCD_RW_uC_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xFE) | (x << 0))
#define	LCD_RS_uC_Dat(x)	FIO4PIN0 =((FIO4PIN0 & 0x7F) | (x << 7))
#define	XRAY_READY_uC_Dat(x)	FIO4PIN0 =((FIO4PIN0 & 0xDF) | (x << 5))
#define	FAULT_LED_uC_Dat(x)	FIO4PIN0 =((FIO4PIN0 & 0xF7) | (x << 3))
#define	STATUS_LED_uC_Dat(x)	FIO4PIN0 =((FIO4PIN0 & 0xFB) | (x << 2))
#define	PRESEL_LED_uC(x)	FIO3PIN1 =((FIO3PIN1 & 0x7F) | (x << 7))
#define	ERROR_LED_uC(x)	FIO3PIN1 =((FIO3PIN1 & 0xBF) | (x << 6))
#define	COLIM_LED_uC(x)	FIO3PIN1 =((FIO3PIN1 & 0xDF) | (x << 5))
#define	VBUKY_LED_uC(x)	FIO3PIN1 =((FIO3PIN1 & 0xEF) | (x << 4))
#define	HBUKY_LED_uC(x)	FIO3PIN1 =((FIO3PIN1 & 0xF7) | (x << 3))
#define	EXPOS_LED_uC(x)	FIO3PIN1 =((FIO3PIN1 & 0xFB) | (x << 2))
#define	READY_LED_uC(x)	FIO3PIN1 =((FIO3PIN1 & 0xFD) | (x << 1))
#define	SPARE_LED_uC(x)	FIO3PIN1 =((FIO3PIN1 & 0xFE) | (x << 0))
#define	KYPAD_COLMN3_uC(x)	FIO3PIN0 =((FIO3PIN0 & 0x7F) | (x << 7))
#define	KYPAD_COLMN2_uC(x)	FIO3PIN0 =((FIO3PIN0 & 0xBF) | (x << 6))
#define	KYPAD_COLMN1_uC(x)	FIO3PIN0 =((FIO3PIN0 & 0xDF) | (x << 5))
#define	KYPAD_COLMN0_uC(x)	FIO3PIN0 =((FIO3PIN0 & 0xEF) | (x << 4))
#define	RS485_TX_Dat(x)	FIO2PIN0 =((FIO2PIN0 & 0xFE) | (x << 0))
#define	KYPAD_COLMN_uC(x)	FIO3PIN0 =( (FIO3PIN0 & 0x0F) | (x << 4))
#define	LED_PORT_uC	FIO3PIN1
#define	LCD_D0_D3_uC_Dat(x)	FIO4PIN1 =((FIO4PIN1 & 0xC3) | (x << 2))
//	END of Output Port Definition

//	Input Port Definition
#define	HV_85_PRCNT_uC	( (FIO1PIN1 & 0x02) >> 1)
#define	GEN_FAULT_uC	( (FIO1PIN1 & 0x04) >> 2)
#define	X_RAY_SW_STEP_uC	( (FIO1PIN3 & 0x40) >> 6)
#define	X_RAY_SW_uC	( (FIO1PIN3 & 0x80) >> 7)
#define	DIP_SW2_uC	( (FIO4PIN2 & 0x08) >> 3)
#define	DIP_SW1_uC	( (FIO4PIN2 & 0x04) >> 2)
#define	KEYPAD_EXPOS_SW_uC	( (FIO3PIN3 & 0x80) >> 7)
#define	KEYPAD_READY_SW_uC	( (FIO3PIN3 & 0x40) >> 6)
#define	KYPAD_ROW3_uC	( (FIO3PIN0 & 0x08) >> 3)
#define	KYPAD_ROW2_uC	( (FIO3PIN0 & 0x04) >> 2)
#define	KYPAD_ROW1_uC	( (FIO3PIN0 & 0x02) >> 1)
#define	KYPAD_ROW0_uC	( (FIO3PIN0 & 0x01) >> 0)
#define	CALIB_SW_uC	( (FIO2PIN1 & 0x04) >> 2)
#define	KYPAD_ROW_uC	(FIO3PIN0 & 0x0F)
//	End of Input Port Definition

//	ADC Related Pe-directives
//	****	Channel Select	****
#define ADC0_CHANEL1_SEL_MASK	0xFFFFFF01
#define ADC0_CHANEL2_SEL_MASK	0xFFFFFF02
#define ADC0_CHANEL3_SEL_MASK	0xFFFFFF04
#define ADC0_CHANEL4_SEL_MASK	0xFFFFFF08
#define ADC0_CHANEL5_SEL_MASK	0xFFFFFF10
#define ADC0_CHANEL6_SEL_MASK	0xFFFFFF20
#define ADC0_CHANEL7_SEL_MASK	0xFFFFFF40
#define ADC0_CHANEL8_SEL_MASK	0xFFFFFF80

//	****	DAC Control Word	****
//#define FL_DAC_CW 0x9000	// 4 bit Configuration word of DAC (MCP4822)
#define LCDC_DAC_CW 0x1000	// 4 bit Configuration word of DAC (MCP4822)
//#define mA_DAC_CW 0x1000	// 4 bit Configuration word of DAC (MCP4822)



#endif
