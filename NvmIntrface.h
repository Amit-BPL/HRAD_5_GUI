#ifndef NVMINTRFACE_H_
#define NVMINTRFACE_H_

#include "CcAbstLayer.h"

#define NVM_AUTO_CS DISABLE
//	AT45DB161E OP_codes
#define NVM_ERASE_AND_WRITE 0x82
#define NVM_READ_MODFY_WRITE 0x58
#define NVM_READ_CMD 0xD2
//	End of Op-Codes

#define FIRST_BOOT_CHECK_LOC1 4
#define FIRST_BOOT_CHECK_LOC2 5
#define FIRST_BOOT_CHECK_LOC3 6
#define MNUEL_LAST_KV_LOC 10			// Starting Adress of 2 bytes
#define MNUEL_LAST_mAS_LOC 12			// Starting Adress of 2 bytes
#define MNUEL_LAST_mA_LOC 14			// Starting Adress of 2 bytes
#define PRESEL_LAST_KV_LOC 20			// Starting Adress of 2 bytes
#define PRESEL_LAST_mAS_LOC 22		// Starting Adress of 2 bytes
#define PRESEL_LAST_mA_LOC 24			// Starting Adress of 2 bytes
#define PWRMOD_CHEK_KEY_LOC1 30		// First location for checking LOW Power Mode
#define PWRMOD_CHEK_KEY_LOC2 31		// First location for checking LOW Power Mode
#define PWRMOD_CHEK_KEY_LOC3 32		// First location for checking LOW Power Mode
#define LAST_CALB_PTR_LOC 40			// Location For saving Last calibration Pointer.



#define GuicPinNo_128_Fn(x) PINSEL0 = ((PINSEL0 & 0x3FFFFFFF) | (x << 30))
#define GuicPinNo_130_Fn(x) PINSEL1 = ((PINSEL1 & 0xFFFFFFFC) | (x << 0))
#define GuicPinNo_126_Fn(x) PINSEL1 = ((PINSEL1 & 0xFFFFFFF3) | (x << 2))
#define GuicPinNo_124_Fn(x) PINSEL1 = ((PINSEL1 & 0xFFFFFFCF) | (x << 4))
#define GuicPinNo_75_Fn(x) PINSEL8 = ((PINSEL8 & 0xFFFFFFFC) | (x << 0))
#define GuicPinNo_79_Fn(x) PINSEL8 = ((PINSEL8 & 0xFFFFFFF3) | (x << 2))

#define	GuicPinNo128_Dir(x)	FIO0DIR1 =((FIO0DIR1 & 0x7F) | (x << 7))
#define	GuicPinNo130_Dir(x)	FIO0DIR2 =((FIO0DIR2 & 0xFE) | (x << 0))
#define	GuicPinNo126_Dir(x)	FIO0DIR2 =((FIO0DIR2 & 0xFD) | (x << 1))
#define	GuicPinNo124_Dir(x)	FIO0DIR2 =((FIO0DIR2 & 0xFB) | (x << 2))
#define	GuicPinNo75_Dir(x)	FIO4DIR0 =((FIO4DIR0 & 0xFE) | (x << 0))
#define	GuicPinNo79_Dir(x)	FIO4DIR0 =((FIO4DIR0 & 0xFD) | (x << 1))

#define GuicPinNo128_Mod(x) PINMODE0 = ((PINMODE0 & 0x3FFFFFFF) | (x << 30))
#define GuicPinNo130_Mod(x) PINMODE1 = ((PINMODE1 & 0xFFFFFFFC) | (x << 0))
#define GuicPinNo126_Mod(x) PINMODE1 = ((PINMODE1 & 0xFFFFFFF3) | (x << 2))
#define GuicPinNo124_Mod(x) PINMODE1 = ((PINMODE1 & 0xFFFFFFCF) | (x << 4))
#define	GuicPinNo75_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFFFFFFFC) | (x << 0))
#define	GuicPinNo79_Mod(x)	PINMODE8 = ((PINMODE8 & 0xFFFFFFF3) | (x << 2))

#define	FLASH_CS_Dat(x)	FIO0PIN2 =((FIO0PIN2 & 0xFE) | (x << 0))
#define	FLASH_RESET_uC_Dat(x)	FIO4PIN0 =((FIO4PIN0 & 0xFE) | (x << 0))
#define	FLASH_WPROT_uC_Dat(x)	FIO4PIN0 =((FIO4PIN0 & 0xFD) | (x << 1))

#define DEMUX_SEL       (1 << 16)
#define SPIF            (1 << 7)
#define SSPSR_RNE		    (1 << 2)
#define SSPSR_BSY		    (1 << 4)
#define NVM_DAT_BUFR_SIZE 20
#define FIRST_BOOT_KV 40
#define FIRST_BOOT_mAS_ARR_COUNT 15
#define FIRST_BOOT_mA_ARR_COUNT 7


unsigned char NVM_Data_Array[NVM_DAT_BUFR_SIZE];

NVM_DATA_STRUCT NvmSendDat, NvmReadDat;

unsigned short NvmPopKV, NvmPopmA, NvmPopmAS, NvmWriteDelayTmr1;
#if	APR_SAVE_EN
extern const unsigned short EepromLocForAPR[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY];	//@@@@@@@@@@
extern const unsigned char AprDefltKv_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY];
extern const unsigned short Apr_DefltmASx10_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY];
extern unsigned char AprKv_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY];
extern unsigned short Apr_mASx10_Values[NUM_OF_PATIENT_TYPES][NUM_OF_ANATOMY_TYPES][NUM_OF_VIEWS_PER_ANATOMY];
#endif
extern unsigned char FirstBootRegstr;
extern const unsigned short StationsOfmA[], StdmAsValues[];
extern signed char LowPowrModeEntryBfr[];
extern CONTROL_PARAMETER CntrlPrmtrs;
extern void Delay_1uSec(unsigned int);
extern char Normalise_XrayParamtr(unsigned char);
extern unsigned char FndOrdinalNumOfShortArr(const unsigned short*, unsigned char, unsigned short);


#endif
