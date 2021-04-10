/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1459
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
#include <xc.h>
#include "externs.h"
#include "mcc_generated_files/mcc.h"
#include "24aa32a.h"

unsigned char byte;
unsigned char row = 0;
unsigned char column = 0;
unsigned char writecomplete = 0;
unsigned short currentEepromAddress = 0;
uint8_t numBytes;
uint8_t buffer[1];

static unsigned short measarray[26][8] = {
    {0xF371, 0xD964, 0x764, 0x6751, 0xFF36, 0x9797, 0xDD73, 0xC4C5},
    {0xF333, 0x9293, 0x8698, 0x9945, 0xF2F1, 0xB2B3, 0xC9C9, 0xF3F4},
    {16, 17, 18, 19, 20, 21, 22, 23},
    {24, 25, 26, 27, 28, 29, 30, 31},
    {32, 33, 34, 35, 36, 37, 38, 39},
    {40, 41, 42, 43, 44, 45, 46, 47},
    {48, 49, 50, 51, 52, 53, 54, 55},
    {56, 57, 58, 59, 60, 61, 62, 63},
    {64, 65, 66, 67, 68, 69, 70, 71},
    {72, 73, 74, 75, 76, 77, 78, 79},
    {80, 81, 82, 83, 84, 85, 86, 87},
    {88, 89, 90, 91, 92, 93, 94, 95},
    {96, 97, 98, 99, 100, 101, 102, 103},
    {104, 105, 106, 107, 108, 109, 110, 111},
    {112, 113, 114, 115, 116, 117, 118, 119},
    {120, 121, 122, 123, 124, 125, 126, 127},
    {128, 129, 130, 131, 132, 133, 134, 135},
    {136, 137, 138, 139, 140, 141, 142, 143},
    {144, 145, 146, 147, 148, 149, 150, 151},
    {152, 153, 154, 155, 156, 157, 158, 159},
    {160, 161, 162, 163, 164, 165, 166, 167},
    {168, 169, 170, 171, 172, 173, 174, 175},
    {176, 177, 178, 179, 180, 181, 182, 183},
    {184, 185, 186, 187, 188, 189, 190, 191},
    {192, 193, 194, 195, 196, 197, 198, 199},
    {200, 201, 202, 203, 204, 205, 206, 207}};

/*
                         Main application
 */

void main(void)
{
    SYSTEM_Initialize();
    I2C_Initialize();
    CDCInitEP(); //needed for USB
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    uint8_t numBytes; //needed for USB
    uint8_t buffer[1]; //needed for USB
   
    
    while(1)
    {
        CDCTxService(); //needed for USB
        
        
        numBytes = getsUSBUSART(buffer,sizeof(buffer)); //needed for USB
        if(buffer[0] == 'k')
        {
            if(USBUSARTIsTxTrfReady()) //needed for USB
                {
                    if (EEPROM_DONE_READING)
                    {
                        putrsUSBUSART("Stop!"); //needed for USB
                        buffer[0] = 'n'; //needed for USB
                    }
                    else
                    {
                        UPDATE_MEASARRAY_WITH_NEW_PAGE //needed for USB
                        putUSBUSART(measarray,32); //needed for USB
                    }
                }
        }
		
		if(buffer[0] == 'c')
        {
            if(USBUSARTIsTxTrfReady()) //needed for USB
                {
                    if (EEPROM_DONE_READING)
                    {
                        putrsUSBUSART("Stop!"); //needed for USB
                        buffer[0] = 'n'; //needed for USB
                    }
                    else
                    {
                        UPDATE_MEASARRAY_WITH_NEW_PAGE //needed for USB
                        putUSBUSART(measarray,32); //needed for USB
                    }
                }
        }
    }
}
