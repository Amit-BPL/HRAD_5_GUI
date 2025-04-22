/****************************************************************************
* FILENAME:      LPC2000_CAN_GAF.h                                          *
*                                                                           *
* VERSION:       V1.0                                                       *
*                                                                           *
* DESCRIPTION:   Header File for CAN Driver LPC2000_CAN_Driver.c            *  
*				 CAN Global Acceptance Filter Configuration File     	    *
*                                                                          	*
* TOOLS:         KEIL uVision3                                          	*
*                ARM Development Suite ADS1.2                               *
*                                                                           *
*                                                                           *
* REVISION HISTORY:                                                         *
* Version  Author          Date          Remarks                            *
* 1.0      Anthony Xie     10/10/2005    - -                                *
*****************************************************************************/

/**
 * @file
 * CAN Controller Acceptance Filter Configuration
 *
 * This header file configures the acceptance filter, i.e. defines Identifier
 * ranges for all sorts of message filtering desired for a certain CAN network
 * This file contains some certain definitions (actually an example) and can
 * be used as a template for further modifications
 */
#ifndef LPC2000CANDRIVER_GAF_H
#define LPC2000CANDRIVER_GAF_H
#include  "type.h"
/*---------------------------------------------------------------------------*/
/*Sections can be enabled or disabled to the application specific needs		 */
/*---------------------------------------------------------------------------*/
 #define LPC2000_CANDRIVER_STD_FULLCAN
// #define LPC2000_CANDRIVER_STD_INDIVIDUAL
// #define LPC2000_CANDRIVER_STD_GROUP      
// #define LPC2000_CANDRIVER_EXT_INDIVIDUAL 
// #define LPC2000_CANDRIVER_EXT_GROUP   

/*****************************************************************************/
/* Standard include files                                                    */
/*****************************************************************************/


/*****************************************************************************/
/* Project include files                                                     */
/*****************************************************************************/

/*****************************************************************************/
/* Types                                                                     */
/*****************************************************************************/

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



#endif /* LPC2000CANDRIVER_GAF_H */
