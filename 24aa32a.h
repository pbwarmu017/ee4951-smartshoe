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
 * File:   24aa32a.h
 * Author: Paul Warmuth
 * Comments: This is the header for the 24aa32a EEPROM library
 * Revision history: v1.0: Initial 
 */

#ifndef     HEADER_24AA32A

#define     HEADER_24AA32A
#define     SCL         LATBbits.LATB6   // I2C clock, PORTB pin 6
#define     SDA         PORTBbits.RB4 // I2C data, PORTB pin 4
#define     SDA_TRIS    TRISBbits.TRISB4// SDA tris bit, PORTB pin 4
#define     CONTROLBYTE 0b10100000      // Control byte
#define		HWADDRESSBITS 		0b000 					//EEPROM Address
#define     ACKBIT      0x00            // ACK bit
#define     NAKBIT      0x80            // NAK bit

#include <xc.h> // include processor files - each processor file is guarded.  

void _i2cstart(void);
void _i2cstop(void);
void _writeBit(unsigned char data);
void _readBit(unsigned char *data);
unsigned char _writeByte(unsigned char data);
unsigned char _readByte(unsigned char ack);
void ACK_Poll(void);
void eeprom_writeByte(unsigned int address, unsigned char data);
void eeprom_writePage(unsigned int address, unsigned char *data);
void eeprom_readByte(unsigned int address, unsigned char *data);
void eeprom_readMem(unsigned char *data);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* HEADER_24AA32A*/

