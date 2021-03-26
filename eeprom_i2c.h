/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  


/********************************************************************
 *                                                                    
 *                     Software License Agreement                      
 *                                                                     
 * The software supplied herewith by Microchip Technology Incorporated 
 * (the "Company") for its PICmicro® Microcontroller is intended and   
 * supplied to you, the Company?s customer, for use solely and         
 * exclusively on Microchip PICmicro Microcontroller products.         
 *                                                                     
 * The software is owned by the Company and/or its supplier, and is     
 * protected under applicable copyright laws. All rights are reserved.  
 * Any use in violation of the foregoing restrictions may subject the  
 * user to criminal sanctions under applicable laws, as well as to     
 * civil liability for the breach of the terms and conditions of this  
 * license.                                                             
 *                                                                      
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,   
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED   
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A         
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,   
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR          
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.                    
 *                                                                     
 *******************************************************************
 *
 *   Filename:           AN997_i2c.h
 *   Date:               June 20, 2005
 *   File Version:       1.0
 *   Compiled using:     MPLAB IDE 7.11.00.0
 *                       MPLAB C18 2.40
 *
 *   Author:             Chris Parris
 *   Company:            Microchip Technology, Inc.
 *
 ** C O N S T A N T S *********************************************/
#define     SCL         PORTBbits.RB6   // I2C clock, PORTB pin 6
#define     SDA         PORTBbits.RB4 // I2C data, PORTB pin 4
#define     SDA_TRIS    TRISBbits.TRISB4// SDA tris bit, PORTB pin 4
#define     CONTROLBYTE 0b10100000      // Control byte
#define     ACKBIT      0x00            // ACK bit
#define     NAKBIT      0x80            // NAK bit

/** E X T E R N A L   V A R I A B L E S ***************************/
extern unsigned char control;           // Control byte variable
extern unsigned int address;            // Address word variable

/** P U B L I C   P R O T O T Y P E S *****************************/
void bstart(void);                      // Start condition
void bstop(void);                       // Stop condition
unsigned char byte_out(unsigned char);  // Byte output
unsigned char byte_in(unsigned char);   // Byte input
void LowDensByteWrite(unsigned char);   // Low-density byte write
void HighDensByteWrite(unsigned char);  // High-density byte write
void LowDensPageWrite(unsigned char*,unsigned char);    // Low-density page write
void HighDensPageWrite(unsigned char*,unsigned char);   // High-density page write
void LowDensByteRead(unsigned char*);   // Low-density byte read
void HighDensByteRead(unsigned char*);  // High-density byte read
void LowDensSequentialRead(unsigned char*,unsigned int);    // Low-density sequential read
void HighDensSequentialRead(unsigned char*,unsigned int);   // High-density sequential read
void ACK_Poll(void);                    // Acknowledge polling


// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

