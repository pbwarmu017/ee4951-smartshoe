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

#define     CONTROLBYTE 0b10100000      // Control byte
#define		HWADDRESSBITS 		0b000 					//EEPROM Address

#define I2CINTERRUPTFLAG PIR1bits.SSP1IF
#define I2CINTERRUPTENABLE PIE1bits.SSP1IE
#define NACKFLAG SSP1CON2bits.ACKSTAT

#include <xc.h> // include processor files - each processor file is guarded.  

void I2C_Initialize();
void ACK_Poll(void);
void I2C_WaitForCompletion(void);
void I2C_MasterStart(void);
void I2C_MasterStop(void);
void I2C_MasterWrite(unsigned char data);
void I2C_MasterSetReceive(void);
void I2C_MasterSendAck(void);
void I2C_MasterSendNack(void);
void eeprom_writeByte(unsigned short address, unsigned char *databyte);
void eeprom_writePage(unsigned short address, unsigned char *data);
void eeprom_storeBurstGroup(unsigned short address, unsigned short data[][8]);
void eeprom_readByte(unsigned short address, unsigned char *databyte);
void eeprom_readMem(unsigned char *databyte);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* HEADER_24AA32A*/

