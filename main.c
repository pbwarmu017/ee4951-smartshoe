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

#include "mcc_generated_files/mcc.h"
#include "eeprom_i2c.h"

/** D E F I N E S **************************************************/
#define PAGESIZE    16                  // Page size in bytes

/** V A R I A B L E S **********************************************/
unsigned char data[PAGESIZE];           // Data array
USB_HANDLE USBInHandle;

void USBCBInitEP(void){
    USBEnableEndpoint(_EP01_IN, USB_IN_ENABLED|USB_DISALLOW_SETUP);
}
/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    unsigned char i;                    // Loop counter

    control = CONTROLBYTE;              // Load control byte


   

    while (1)
    {
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


        //USB CODE
        USBDeviceTasks();
        if ((USBGetDeviceState() != CONFIGURED_STATE)||(USBIsDeviceSuspended() == 1))
        {
            //device isn't connected or configured
            continue;
        }
        else
        {
            //USB Transmit code goes here
            if(!USBHandleBusy(USBInHandle))
            {
                //Write the new data that we wish to send to the host to the INPacket[] array
                //For first run just sending the data array
                

                //Send the data contained in the INPacket[] array through endpoint "EP_NUM"
                USBInHandle = USBTransferOnePacket(_EP01_IN,IN_TO_HOST,(uint8_t*)&data[0],sizeof(data));
            }
        }
    }
}
/**
 End of File
*/