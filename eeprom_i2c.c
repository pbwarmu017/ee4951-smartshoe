
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
 *   Filename:           AN997_i2c.c
 *   Date:               June 20, 2005
 *   File Version:       1.0
 *   Compiled using:     MPLAB IDE 7.11.00.0
 *                       MPLAB C18 2.40
 *
 *   Author:             Chris Parris
 *   Company:            Microchip Technology, Inc.
 *
 *******************************************************************
 *
 *   Files required:     xc.h
 *                       AN997_i2c.h
 *                       AN997.c
 *
 ** I N C L U D E S ************************************************/
#include "eeprom_i2c.h"

/** V A R I A B L E S **********************************************/
unsigned char control;              // Control byte variable
unsigned int address;               // Address word variable
int temp;

/** P R O T O T Y P E S ********************************************/
void bit_in(unsigned char *data);   // Bit input function
void bit_out(unsigned char data);   // Bit output function

/********************************************************************
 * Function:        void bstart(void)
 *
 * Description:     This function generates an I2C Start condition.
 *******************************************************************/
void bstart(void)
{
    SDA_TRIS = 1;                   // Ensure SDA is high
    SCL = 1;                        // Ensure SCL is high
    SDA_TRIS = 0;                   // Configure SDA as an output
    SDA = 0;                        // Pull SDA low
    SCL = 0;                        // Pull SCL low
    
} // end bstart(void)

/********************************************************************
 * Function:        void bstop(void)
 *
 * Description:     This function generates an I2C Stop condition.
 *******************************************************************/
void bstop(void)
{
    SCL = 0;                        // Ensure SCL is low
    SDA_TRIS = 0;                   // Configure SDA as an output
    SDA = 0;                        // Ensure SDA low
    SCL = 1;                        // Pull SCL high
    SDA_TRIS = 1;                   // Allow SDA to be pulled high
} // end bstop(void)

/********************************************************************
 * Function:        void bit_out(unsigned char data)
 *
 * Description:     This function outputs a bit to the I2C bus.
 *******************************************************************/
void bit_out(unsigned char data)
{
    SCL = 0;                        // Ensure SCL is low
    if (data & 0x80)                // Check if next bit is high
    {
        SDA_TRIS = 1;               // Release SDA to be pulled high
    }
    else
    {
        SDA_TRIS = 0;               // Configure SDA as an output
        SDA = 0;                    // Pull SDA low
    }
    SCL = 1;                        // Pull SCL high to clock bit
    SCL = 0;                        // Pull SCL low for next bit
} // end bit_out(unsigned char data)

/********************************************************************
 * Function:        void bit_in(unsigned char *data)
 *
 * Description:     This function inputs a bit from the I2C bus.
 *******************************************************************/
void bit_in(unsigned char *data)
{
    SCL = 0;                        // Ensure SCL is low
    SDA_TRIS = 1;                   // Configure SDA as an input
    SCL = 1;                        // Bring SCL high to begin transfer
    *data &= 0xFE;                  // Assume next bit is low
    if (SDA)                        // Check if SDA is high
    {
        *data |= 0x01;              // If high, set next bit
    }
    SCL = 0;                        // Bring SCL low again
} // end bit_in(unsigned char *data)

/********************************************************************
 * Function:        unsigned char byte_out(unsigned char data)
 *
 * Description:     This function outputs a byte to the I2C bus.
 *                  It also receives the ACK bit and returns 0 if
 *                  successfully received, or 1 if not.
 *******************************************************************/
unsigned char byte_out(unsigned char data)
{
    unsigned char i;                // Loop counter
    unsigned char ack;              // ACK bit

    ack = 0;
    for (i = 0; i < 8; i++)         // Loop through each bit
    {
        bit_out(data);              // Output bit
        data = data << 1;           // Shift left for next bit
    }
    bit_in(&ack);                   // Input ACK bit

    return ack;
} // end byte_out(unsigned char data)

/********************************************************************
 * Function:        unsigned char byte_in(unsigned char ack)
 *
 * Description:     This function inputs a byte from the I2C bus.
 *                  Depending on the value of ack, it will also
 *                  transmit either an ACK or a NAK bit.
 *******************************************************************/
unsigned char byte_in(unsigned char ack)
{
    unsigned char i;                // Loop counter
    unsigned char retval;           // Return value

    retval = 0;
    for (i = 0; i < 8; i++)         // Loop through each bit
    {
        retval = retval << 1;       // Shift left for next bit
        bit_in(&retval);            // Input bit
    }
    bit_out(ack);                   // Output ACK/NAK bit

    return retval;
} // end byte_in(void)

/********************************************************************
 * Function:        void LowDensByteWrite(unsigned char data)
 *
 * Description:     This function writes a single byte to a
 *                  low-density (<= 16 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void LowDensByteWrite(unsigned char data)
{
    unsigned char temp_control;     // Temp. variable for control byte

    // Merge block bits with control byte
    temp_control = (control & 0xF1) | ((address >> 7) & 0x0E);

    bstart();                       // Generate Start condition
    byte_out(temp_control);         // Output control byte
    byte_out((unsigned char)address);// Output address LSB
    byte_out(data);                 // Output data byte
    bstop();                        // Generate Stop condition
    ACK_Poll();                     // Begin ACK polling
} // end LowDensByteWrite(unsigned char data)

/********************************************************************
 * Function:        void HighDensByteWrite(unsigned char data)
 *
 * Description:     This function writes a single byte to a
 *                  high-density (>= 32 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void HighDensByteWrite(unsigned char data)
{
    bstart();                       // Generate Start condition
    byte_out(control);              // Output control byte
    byte_out((unsigned char)(address>>8));// Output address MSB
    byte_out((unsigned char)address);// Output address LSB
    byte_out(data);                 // Output data byte
    bstop();                        // Generate Stop condition
    ACK_Poll();                     // Begin ACK polling
} // end HighDensByteWrite(unsigned char data)

/********************************************************************
 * Function:        void LowDensPageWrite(unsigned char *data,
 *                                        unsigned char numbytes)
 *
 * Description:     This function writes multiple bytes to a
 *                  low-density (<= 16 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void LowDensPageWrite(unsigned char *data, unsigned char numbytes)
{
    unsigned char i;                // Loop counter
    unsigned char temp_control;     // Temp. variable for control byte

    // Merge block bits with control byte
    temp_control = (control & 0xF1) | ((address >> 7) & 0x0E);

    bstart();                       // Generate Start condition
    byte_out(temp_control);         // Output control byte
    byte_out((unsigned char)address);// Output address LSB
    for (i = 0; i < numbytes; i++)  // Loop through data bytes
    {
        byte_out(data[i]);          // Output next data byte
    }
    bstop();                        // Generate Stop condition
    ACK_Poll();                     // Begin ACK polling
} // end LowDensPageWrite(unsigned char *data, unsigned char numbytes)

/********************************************************************
 * Function:        void HighDensPageWrite(unsigned char *data,
 *                                         unsigned char numbytes)
 *
 * Description:     This function writes multiple bytes to a
 *                  high-density (>= 32 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void HighDensPageWrite(unsigned char *data, unsigned char numbytes)
{
    unsigned char i;                // Loop counter

    bstart();                       // Generate Start condition
    byte_out(control);              // Output control byte
    byte_out((unsigned char)(address>>8));// Output address MSB
    byte_out((unsigned char)address);// Output address LSB
    for (i = 0; i < numbytes; i++)  // Loop through data bytes
    {
        byte_out(data[i]);          // Output next data byte
    }
    bstop();                        // Generate Stop condition
    ACK_Poll();                     // Begin ACK polling
} // end HighDensPageWrite(unsigned char *data, unsigned char numbytes)

/********************************************************************
 * Function:        void LowDensByteRead(unsigned char *data)
 *
 * Description:     This function reads a single byte from a
 *                  low-density (<= 16 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void LowDensByteRead(unsigned char *data)
{
    unsigned char temp_control;     // Temp. variable for control byte

    // Merge block bits with control byte
    temp_control = (control & 0xF1) | ((address >> 7) & 0x0E);

    bstart();                       // Generate Start condition
    byte_out(temp_control);         // Output control byte
    byte_out((unsigned char)address);// Output address LSB
    bstart();                       // Generate Start condition
    byte_out(temp_control | 0x01);  // Output control byte
    *data = byte_in(NAKBIT) + 1;        // Input data byte
    bstop();                        // Generate Stop condition
} // end LowDensByteRead(unsigned char data)

/********************************************************************
 * Function:        void HighDensByteRead(unsigned char *data)
 *
 * Description:     This function reads a single byte from a
 *                  high-density (>= 32 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void HighDensByteRead(unsigned char *data)
{
    bstart();                       // Generate Start condition
    byte_out(control);              // Output control byte
    byte_out((unsigned char)(address>>8));// Output address MSB
    byte_out((unsigned char)address);// Output address LSB
    bstart();                       // Generate Start condition
    byte_out(control | 0x01);       // Output control byte
    *data = byte_in(NAKBIT);        // Input data byte
    bstop();                        // Generate Stop condition
} // end HighDensByteRead(unsigned char data)

/********************************************************************
 * Function:        void LowDensSequentialRead(unsigned char *data,
 *                                             unsigned char numbytes)
 *
 * Description:     This function reads multiple bytes from a
 *                  low-density (<= 16 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void LowDensSequentialRead(unsigned char *data, unsigned int numbytes)
{
    unsigned int i;                 // Loop counter
    unsigned char temp_control;     // Temp. variable for control byte

    // Merge block bits with control byte
    temp_control = (control & 0xF1) | ((address >> 7) & 0x0E);

    bstart();                       // Generate Start condition
    byte_out(temp_control);         // Output control byte
    byte_out((unsigned char)address);// Output address LSB
    bstart();                       // Generate Start condition
    byte_out(temp_control | 0x01);  // Output control byte
    for (i = 0; i < numbytes; i++)  // Loop through data bytes
    {
        if (i < (numbytes - 1))     // Check if more data will be read
        {
            data[i] = byte_in(ACKBIT); // If not last, input byte & send ACK
        }
        else
        {
            data[i] = byte_in(NAKBIT); // If last byte, input byte & send NAK
        }
    }
    bstop();                        // Generate Stop condition
} // end LowDensSequentialRead(unsigned char *data, unsigned char numbytes)

/********************************************************************
 * Function:        void HighDensSequentialRead(unsigned char *data,
 *                                              unsigned char numbytes)
 *
 * Description:     This function reads multiple bytes from a
 *                  high-density (>= 32 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void HighDensSequentialRead(unsigned char *data, unsigned int numbytes)
{
    unsigned int i;                 // Loop counter

    bstart();                       // Generate Start condition
    byte_out(control);              // Output control byte
    byte_out((unsigned char)(address>>8));// Output address MSB
    byte_out((unsigned char)address);// Output address LSB
    bstart();                       // Generate Start condition
    byte_out(control | 0x01);       // Output control byte
    for (i = 0; i < numbytes; i++)  // Loop through data bytes
    {
        if (i < (numbytes - 1))     // Check if more data will be read
        {
            data[i] = byte_in(ACKBIT); // If not last, input byte & send ACK
        }
        else
        {
            data[i] = byte_in(NAKBIT); // If last byte, input byte & send NAK
        }
    }
    bstop();                        // Generate Stop condition
} // end HighDensSequentialRead(unsigned char *data, unsigned char numbytes)

/********************************************************************
 * Function:        void ACK_Poll(void)
 *
 * Description:     This function implements Acknowledge polling.
 *
 * Dependencies:    'control' contains the control byte
 *******************************************************************/
void ACK_Poll(void)
{
    unsigned char result;           // Polling result

    result = 1;                     // Initialize result
    do
    {
        bstart();                   // Generate Start condition
        result = byte_out(control); // Output control byte
    } while (result == 1);
    bstop();                        // Generate Stop condition
} // end ACK_Poll(void)

