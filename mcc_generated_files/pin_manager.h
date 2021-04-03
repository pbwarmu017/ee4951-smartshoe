/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1459
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 procedures
#define RA0_GetValue()              PORTAbits.RA0

// get/set RA1 procedures
#define RA1_GetValue()              PORTAbits.RA1

// get/set NA3 aliases
#define NA3_TRIS                 TRISAbits.TRISA4
#define NA3_LAT                  LATAbits.LATA4
#define NA3_PORT                 PORTAbits.RA4
#define NA3_WPU                  WPUAbits.WPUA4
#define NA3_ANS                  ANSELAbits.ANSA4
#define NA3_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define NA3_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define NA3_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define NA3_GetValue()           PORTAbits.RA4
#define NA3_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define NA3_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define NA3_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define NA3_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define NA3_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define NA3_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set motion_detect aliases
#define motion_detect_TRIS                 TRISAbits.TRISA5
#define motion_detect_LAT                  LATAbits.LATA5
#define motion_detect_PORT                 PORTAbits.RA5
#define motion_detect_WPU                  WPUAbits.WPUA5
#define motion_detect_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define motion_detect_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define motion_detect_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define motion_detect_GetValue()           PORTAbits.RA5
#define motion_detect_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define motion_detect_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define motion_detect_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define motion_detect_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)

// get/set NA1 aliases
#define NA1_TRIS                 TRISBbits.TRISB5
#define NA1_LAT                  LATBbits.LATB5
#define NA1_PORT                 PORTBbits.RB5
#define NA1_WPU                  WPUBbits.WPUB5
#define NA1_ANS                  ANSELBbits.ANSB5
#define NA1_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define NA1_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define NA1_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define NA1_GetValue()           PORTBbits.RB5
#define NA1_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define NA1_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define NA1_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define NA1_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define NA1_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define NA1_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set NA2 aliases
#define NA2_TRIS                 TRISBbits.TRISB7
#define NA2_LAT                  LATBbits.LATB7
#define NA2_PORT                 PORTBbits.RB7
#define NA2_WPU                  WPUBbits.WPUB7
#define NA2_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define NA2_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define NA2_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define NA2_GetValue()           PORTBbits.RB7
#define NA2_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define NA2_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define NA2_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define NA2_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)

// get/set pin_icspdat aliases
#define pin_icspdat_TRIS                 TRISCbits.TRISC0
#define pin_icspdat_LAT                  LATCbits.LATC0
#define pin_icspdat_PORT                 PORTCbits.RC0
#define pin_icspdat_ANS                  ANSELCbits.ANSC0
#define pin_icspdat_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define pin_icspdat_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define pin_icspdat_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define pin_icspdat_GetValue()           PORTCbits.RC0
#define pin_icspdat_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define pin_icspdat_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define pin_icspdat_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define pin_icspdat_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set pin_icspclk aliases
#define pin_icspclk_TRIS                 TRISCbits.TRISC1
#define pin_icspclk_LAT                  LATCbits.LATC1
#define pin_icspclk_PORT                 PORTCbits.RC1
#define pin_icspclk_ANS                  ANSELCbits.ANSC1
#define pin_icspclk_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define pin_icspclk_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define pin_icspclk_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define pin_icspclk_GetValue()           PORTCbits.RC1
#define pin_icspclk_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define pin_icspclk_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define pin_icspclk_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define pin_icspclk_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set pin_red aliases
#define pin_red_TRIS                 TRISCbits.TRISC2
#define pin_red_LAT                  LATCbits.LATC2
#define pin_red_PORT                 PORTCbits.RC2
#define pin_red_ANS                  ANSELCbits.ANSC2
#define pin_red_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define pin_red_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define pin_red_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define pin_red_GetValue()           PORTCbits.RC2
#define pin_red_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define pin_red_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define pin_red_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define pin_red_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set pin_yellow aliases
#define pin_yellow_TRIS                 TRISCbits.TRISC3
#define pin_yellow_LAT                  LATCbits.LATC3
#define pin_yellow_PORT                 PORTCbits.RC3
#define pin_yellow_ANS                  ANSELCbits.ANSC3
#define pin_yellow_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define pin_yellow_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define pin_yellow_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define pin_yellow_GetValue()           PORTCbits.RC3
#define pin_yellow_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define pin_yellow_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define pin_yellow_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define pin_yellow_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set NA4 aliases
#define NA4_TRIS                 TRISCbits.TRISC4
#define NA4_LAT                  LATCbits.LATC4
#define NA4_PORT                 PORTCbits.RC4
#define NA4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define NA4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define NA4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define NA4_GetValue()           PORTCbits.RC4
#define NA4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define NA4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set pin_led aliases
#define pin_led_TRIS                 TRISCbits.TRISC5
#define pin_led_LAT                  LATCbits.LATC5
#define pin_led_PORT                 PORTCbits.RC5
#define pin_led_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define pin_led_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define pin_led_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define pin_led_GetValue()           PORTCbits.RC5
#define pin_led_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define pin_led_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)

// get/set pin_white aliases
#define pin_white_TRIS                 TRISCbits.TRISC6
#define pin_white_LAT                  LATCbits.LATC6
#define pin_white_PORT                 PORTCbits.RC6
#define pin_white_ANS                  ANSELCbits.ANSC6
#define pin_white_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define pin_white_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define pin_white_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define pin_white_GetValue()           PORTCbits.RC6
#define pin_white_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define pin_white_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define pin_white_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define pin_white_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set pin_green aliases
#define pin_green_TRIS                 TRISCbits.TRISC7
#define pin_green_LAT                  LATCbits.LATC7
#define pin_green_PORT                 PORTCbits.RC7
#define pin_green_ANS                  ANSELCbits.ANSC7
#define pin_green_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define pin_green_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define pin_green_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define pin_green_GetValue()           PORTCbits.RC7
#define pin_green_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define pin_green_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define pin_green_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define pin_green_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF5 pin functionality
 * @Example
    IOCAF5_ISR();
 */
void IOCAF5_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF5 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF5 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF5_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF5_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF5 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF5_SetInterruptHandler() method.
    This handler is called every time the IOCAF5 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF5_SetInterruptHandler(IOCAF5_InterruptHandler);

*/
extern void (*IOCAF5_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF5 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF5_SetInterruptHandler() method.
    This handler is called every time the IOCAF5 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF5_SetInterruptHandler(IOCAF5_DefaultInterruptHandler);

*/
void IOCAF5_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/