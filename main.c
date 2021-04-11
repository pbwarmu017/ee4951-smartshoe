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

#define GREENWIRE 9
#define WHITEWIRE 8
#define YELLOWWIRE 7
#define REDWIRE 6
#define ARRANGEMENT_WPPWW 0 //Whole-Part-Part-Whole-Whole
#define ARRANGEMENT_PPWWPP 1 //Part-Part-Whole-Whole-Part-Part
#define ARRANGEMENT_PWWPPW 3 //Whole-Whole-Part-Part-Whole

unsigned short measarray[26][8] = {
    {0, 1, 2, 3, 4, 5, 6, 7},
    {8, 9, 10, 11, 12, 13, 14, 15},
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
void takeMeasurement(unsigned char channel) {
    ADCON0bits.CHS = channel;
    ADCON0bits.ADON = 1;
    ADCON0bits.ADGO = 1; //initiate conversion.
    while (ADCON0bits.GO_nDONE);
    ADCON0bits.ADON = 0;
}

void measurementBurst(unsigned char measurement_type){
    static unsigned char measrow = 0;
    static unsigned char meascolumn = 0;
    if (measurement_type == ARRANGEMENT_WPPWW) {
        takeMeasurement(GREENWIRE);
        measarray[measrow][meascolumn] = (unsigned short)(ADRESH << 13) | (unsigned short)(ADRESL << 5); // XGGGGGGG GGG-----
        takeMeasurement(WHITEWIRE);
        measarray[measrow][meascolumn] |= (unsigned short)(ADRESH << 3); // xggggggg gggWW---
        measarray[measrow][meascolumn++] |= (unsigned short)(ADRESL >> 5); // xggggggg gggwwWWW
        //1 short full
        measarray[measrow][meascolumn] = (unsigned short)(ADRESL << 10); // XWWWWW-- --------
        takeMeasurement(YELLOWWIRE);
        measarray[measrow][meascolumn++] |= (unsigned short)(ADRESH << 8) | (unsigned short)ADRESL; // xwwwwwYY YYYYYYYY
        //2 short full
        takeMeasurement(REDWIRE);
        measarray[measrow][meascolumn] = (unsigned short)(ADRESH << 13) | (unsigned short)(ADRESL << 5); // XRRRRRRR RRR-----

    }
    if (measurement_type == ARRANGEMENT_PPWWPP) {
        takeMeasurement(GREENWIRE);
        measarray[measrow][meascolumn] |= (unsigned short)(ADRESH << 3); // xrrrrrrr rrrGG---
        measarray[measrow][meascolumn++] |= (unsigned short)(ADRESL >> 5); // xrrrrrrr rrrggGGG
        //3 short full
        measarray[measrow][meascolumn] = (unsigned short)(ADRESL << 10); // XGGGGG-- --------
        takeMeasurement(WHITEWIRE);
        measarray[measrow][meascolumn++] |= (unsigned short)(ADRESH << 8) | (unsigned short)ADRESL; // xgggggWW WWWWWWWW
        //4 short full
        takeMeasurement(YELLOWWIRE);
        measarray[measrow][meascolumn] = (unsigned short)(ADRESH << 13); // XYY----- --------
        measarray[measrow][meascolumn] |= (unsigned short)(ADRESL << 5); // xyyYYYYY YYY-----
        takeMeasurement(REDWIRE);
        measarray[measrow][meascolumn] |= (unsigned short)(ADRESH << 3); // xyyyyyyy yyyRR---
        measarray[measrow][meascolumn++] |= (unsigned short)(ADRESL >> 5); // xyyyyyyy yyyrrRRR
        //5 short full      
    }
    if (measurement_type == ARRANGEMENT_PWWPPW) {
        measarray[measrow][meascolumn] = (unsigned short)(ADRESL << 10); // XRRRRR-- --------
        takeMeasurement(GREENWIRE);
        measarray[measrow][meascolumn] |= (unsigned short)(ADRESH << 8); // xrrrrrGG --------
        measarray[measrow][meascolumn++] |= (unsigned short)(ADRESL); // xrrrrrgg GGGGGGGG
        //6 short full
        takeMeasurement(WHITEWIRE);
        measarray[measrow][meascolumn] = (unsigned short)(ADRESH << 13); // xWW----- --------
        measarray[measrow][meascolumn] = (unsigned short)(ADRESL << 5); // xwwWWWWW WWW-----

        takeMeasurement(YELLOWWIRE);
        measarray[measrow][meascolumn] |= (unsigned short)(ADRESH << 3); // xwwWWWWW WWWYY---
        measarray[measrow][meascolumn++] |= (unsigned short)(ADRESL >> 5); // xwwWwwww wwwyyYYY
        //7 short full
        measarray[measrow][meascolumn] = (unsigned short)(ADRESL << 10); // XYYYYY-- --------
        takeMeasurement(REDWIRE);
        measarray[measrow++][meascolumn] = (unsigned short)(ADRESH << 8) | (unsigned short)ADRESL; // xyyyyyRR RRRRRRRR
        meascolumn = 0;
        ADCON0bits.ADON = 0;
    }
}

void main(void) {
    static unsigned char burst_count = 0;
    static unsigned char write_complete = 0;
    static unsigned short currentEepromAddress = 0;
    static unsigned char transferComplete_flag = 0;
    SYSTEM_Initialize();
    I2C_Initialize();
    CDCInitEP();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    uint8_t numBytes; //needed for USB
    uint8_t buffer[1]; //needed for USB
    while (1)
    {        
        if (measurement_flag) {
            measurement_flag = 0;
            if (burst_count == 0) {
                measurementBurst(ARRANGEMENT_WPPWW);
                burst_count++;
            }
            else if (burst_count == 1) {
                measurementBurst(ARRANGEMENT_PPWWPP);
                burst_count++;
            }
            else if (burst_count == 2) {
                measurementBurst(ARRANGEMENT_PWWPPW);
                burst_count = 0;
//            }
        }
        if (sleep_flag) //prepare for and then command the system to sleep. 
        {
            sleep_flag = 0;
            //TRISCbits.TRISC5 = 0; //turn on LED
            IOCAFbits.IOCAF5 = 0;
            INTCONbits.IOCIE = 1; //enable IOC interrupt
            asm("SLEEP");
            INTCONbits.IOCIE = 0; //disable IOC interrupt
            //TRISCbits.TRISC5 = 1; //turn off LED
            IOCAFbits.IOCAF5 = 0;
            write_complete = 0;
            writeout_flag = 0;
            measurementburst_count = 0; //queue up another round of measurements. 
        }
        if (writeout_flag && !write_complete) //writecomplete is set to 0 after it wakes up from sleep
        {
            //code to write data array to EEPROM
            writeout_flag = 0;
            if (currentEepromAddress >= 0xFFF) currentEepromAddress = 0; //roll over 

            eeprom_storeBurstGroup(currentEepromAddress, measarray);
            currentEepromAddress += 0x1A0; //increment by 13 pages.
            write_complete = 1;
        }
        numBytes = getsUSBUSART(buffer,sizeof(buffer)); //needed for USB
        if(buffer[0] == 'k')
        {
            buffer[0] = 'n'; //needed for USB
            currentEepromAddress = 0;
            usbInit_flag = 1; //stop some of the timer flags from being set while we write out the data
            transferComplete_flag = 0;
            if(USBUSARTIsTxTrfReady()) //needed for USB
            {
                eeprom_readPage(currentEepromAddress, measarray);//needed for USB
                currentEepromAddress += 0x20;
                putUSBUSART(measarray, 32);
            }
        }
        else if(buffer[0] == 'c') 
        {
            buffer[0] = 'n'; //needed for USB
            if (transferComplete_flag)
            {
                putrsUSBUSART("Stop!"); //needed for USB
                usbInit_flag = 0; //we can go back to normal
            }
            else
            {
                eeprom_readPage(currentEepromAddress, measarray);//needed for USB
                currentEepromAddress += 0x20;
                if(currentEepromAddress >= 0xFFF)
                {
                    transferComplete_flag = 1;
                    currentEepromAddress = 0;
                }
                else putUSBUSART(measarray, 32);
//                for(unsigned char PUTUSBUSART_ROW_C = 0; PUTUSBUSART_ROW_C < 2; PUTUSBUSART_ROW_C++)
//                {
//                    for(unsigned char PUTUSBUSART_COL_C = 0; PUTUSBUSART_COL_C < 8; PUTUSBUSART_COL_C++)
//                    {
//                        unsigned short testvar2 = measarray[PUTUSBUSART_ROW_C][PUTUSBUSART_COL_C];
//                        putUSBUSART(testvar2,2); //needed for USB
//                    }
//                }  
            }
        }
        CDCTxService(); //needed for USB
    }
}
