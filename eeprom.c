
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
 *   Filename:           AN997.c
 *   Date:               June 20, 2005
 *   File Version:       1.0
 *   Compiled using:     MPLAB IDE 7.11.00.0
 *                       MPLAB C18 2.40
 *
 *   Author:             Chris Parris
 *   Company:            Microchip Technology Inc.
 *
 *******************************************************************
 *
 *   Files required:     p18f1220.h
 *                       AN997_i2c.h
 *                       AN997_i2c.c
 *
 *******************************************************************
 *
 *   Purpose:
 *
 *   This application note is intended to serve as a reference for
 *   manually communicating with Microchip?s 24XXXX serial EEPROM
 *   devices, that is, without relying on a hardware serial port to
 *   handle the I2C operations.
 *
 *******************************************************************
 *
 *   Program Description:
 *
 *   This program illustrates the following I2C operations:
 *    - Byte Write
 *    - Byte Read
 *    - Page Write
 *    - Sequential Read
 *   Both high- and low-density functions are provided. High-density
 *   is for >= 32 Kb devices, and low-density is for <= 16 Kb devices.
 *   All write operations utilize the Acknowledge polling feature to
 *   determine the end of the write cycle.
 *
 *   For the byte operations, 1 data byte is read from/written to
 *   the serial EEPROM device. For the page write and sequential read,
 *   one full page of data is transferred. This number is set through the
 *   PAGESIZE constant, and so can be changed to support devices with
 *   different page sizes. Note that if you attempt to cross a page
 *   boundary during a write operation, the address will wrap back to the
 *   beginning of the page, overwriting any previously written bytes.
 *   Also note that the PIC18F1220 contains a limited number of registers,
 *   and so there may not be enough available memory to support the
 *   largest page sizes.
 *
 *   Byte operations start at address 0x00AA, whereas page operations
 *   start at address 0x00B0. All timings assume a 10 MHz crystal
 *   oscillator is used. If a different crystal frequency is desired,
 *   considerations may need to be taken to avoid violating device timing
 *   specs. Also, note that no action is taken if the device does not
 *   respond with an ACK bit when one is expected.
 *
 ** I N C L U D E S ************************************************/
#include <xc.h>
#include "eeprom_i2c.h"

/** D E F I N E S **************************************************/
#define PAGESIZE    16                  // Page size in bytes

/** V A R I A B L E S **********************************************/
unsigned char data[PAGESIZE];           // Data array

/** P R O T O T Y P E S ********************************************/
void init(void);                        // Init. function

void main(void)
{
    unsigned char i;                    // Loop counter

    init();                             // Initialize PIC

    control = CONTROLBYTE;              // Load control byte

    // Byte write/read routines
    address = 0x00AA;                   // Load address with 0x00AA
    data[0] = 0x55;                     // Load data with 0x55
    LowDensByteWrite(data[0]);          // Write a single byte
    LowDensByteRead(data);              // Read a single byte
    //HighDensByteWrite(data[0]);         // Write a single byte
    //HighDensByteRead(data);             // Read a single byte

    // Page write/read routines
    address = 0x00B0;                   // Load address with 0x00B0
    for (i = 0; i < PAGESIZE; i++)      // Loop through full page
    {
        data[i] = (PAGESIZE-1) - i;     // Initialize array
    }
    LowDensPageWrite(data,PAGESIZE);    // Write a full page
    LowDensSequentialRead(data,PAGESIZE);// Read a full page
    //HighDensPageWrite(data,PAGESIZE);   // Write a full page
    //HighDensSequentialRead(data,PAGESIZE);// Read a full page

    while(1);                           // Loop here forever
} // end main(void)

/********************************************************************
 * Function:        void init(void)
 *
 * Description:     This function initializes the PICmicro
 *                  microcontroller.
 *******************************************************************/
void init(void)
{
    ADCON1 = 0x70;                      // Enable digital I/O
    SCL = 1;                            // Ensure SCL is high
    TRISB = 0b11101111;                 // Configure PORTB I/O
} // end init(void)

