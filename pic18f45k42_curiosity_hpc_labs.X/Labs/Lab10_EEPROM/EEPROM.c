/**
  EEPROM Lab Source File

  Company:
    Microchip Technology Inc.

  File Name:
    EEPROM.c

  Summary:
    This is the source file for the EEPROM lab

  Description:
    This source file contains the code on how the EEPROM lab works.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18F45K42
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.45
        MPLAB             :  MPLAB X v4.15
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
 */

#include "../../mcc_generated_files/system/pins.h"
#include "../../mcc_generated_files/adc/adcc.h"
#include "../../mcc_generated_files/nvm/nvm.h"
#include "../../labs.h"

/**
  Section: Macro Declaration
 */
#define EEAddr    0x0000      // EEPROM starting address

/**
  Section: Local Variable Declarations
 */
static uint8_t adcResult;
static uint8_t ledDisplay;

/*
                             Application    
 */
void EEPROM(void) {

    if (labState == NOT_RUNNING) {
        LEDs_SetLow();

        labState = RUNNING;
    }

    if (labState == RUNNING) {
        //Get the top 4 MSBs of the ADC and write them to EEPROM
        adcResult = ADCC_GetSingleConversion(POT_CHANNEL) >> 12;
        NVM_UnlockKeySet(UNLOCK_KEY);
        EEPROM_Write(EEAddr, adcResult);
        NVM_UnlockKeyClear();

        //Load whatever is in EEPROM to the LED Display
        ledDisplay = EEPROM_Read(EEAddr);

        //Determine which LEDs will light up
        LEDs = ledDisplay << 4;
    }

    if (switchEvent) {
        labState = NOT_RUNNING;
    }
}
/*
 End of File
 */
