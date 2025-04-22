/*****************************************************************************
 *   type.h:  Type definition Header file for NXP LPC230x Family 
 *   Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.09.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned int   BOOL;

//--------------------------------------------------------------------------
// Standard Data Types
//--------------------------------------------------------------------------
//                      Type
//                      Pointer
//
typedef signed   char   Int8,       	/**< 8 bit    signed integer */
                        *pInt8;     	/**< 8 bit    signed integer */
typedef signed   short  Int16,      	/**< 16 bit   signed integer */
                        *pInt16;    	/**< 16 bit   signed integer */
typedef signed   long   Int32,      	/**< 32 bit   signed integer */
                        *pInt32;    	/**< 32 bit   signed integer */
typedef unsigned char   UInt8,      	/**< 8 bit  unsigned integer */
                        *pUInt8;    	/**< 8 bit  unsigned integer */
typedef unsigned short  UInt16,     	/**< 16 bit unsigned integer */
                        *pUInt16;   	/**< 16 bit unsigned integer */
typedef unsigned long   UInt32,     	/**< 32 bit unsigned integer */
                        *pUInt32,   	/**< 32 bit unsigned integer */
						CanStatusCode,  /**< General return code */
						*pCanStatusCode;/**< General return code */
typedef float           Float,      	/**< 32 bit floating point */
                        *pFloat;    	/**< 32 bit floating point */
typedef double          Double,     	/**< 32/64 bit floating point */
                        *pDouble;   	/**< 32/64 bit floating point */
typedef unsigned int    Bool,       	/**< Boolean (TM_TRUE or TM_FALSE) */
                        *pBool;     	/**< Boolean (TM_TRUE or TM_FALSE) */
typedef char            Char,       	/**< 8 bit character */
                        *pChar;     	/**< 8 bit character */

#endif  /* __TYPE_H__ */
