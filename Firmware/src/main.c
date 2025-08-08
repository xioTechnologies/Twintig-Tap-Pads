/**
 * @file main.c
 * @author Seb Madgwick
 * @brief Main file.
 *
 * Device:
 * PIC32MZ0512EFE064
 *
 * Compiler:
 * XC32 v4.50, MPLAB Harmony 3
 */

//------------------------------------------------------------------------------
// Includes

#include "Adc/Adc.h"
#include "definitions.h"
#include "ResetCause/ResetCause.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Timer/Timer.h"
#include "Uart/Uart1DmaTX.h"
#include "Uart/Uart2.h"

//------------------------------------------------------------------------------
// Functions

int main(void) {
    SYS_Initialize(NULL);

    // Initialise modules
    TimerInitialise();
    Uart2Initialise(&uartSettingsDefault);
    UartSettings settings = uartSettingsDefault;
    settings.baudRate = 1500000;
    Uart1DmaTXInitialise(&settings);
    AdcInitialise();

    // Print start up message
    TimerDelayMilliseconds(500);
    ResetCausePrint(ResetCauseGet());
    static char __attribute__((coherent)) string[256] = "x-IMU3-SA-AX v1.0.0\n";
    printf(string);
    Uart1DmaTXWrite(string, strlen(string));

    // Main program loop
    while (true) {
        SYS_Tasks();

        // Send ADC data
        static AdcData previousData;
        AdcData data;
        AdcGetData(&data);
        if (data.counter != previousData.counter) {
            previousData = data;
            //            snprintf(string, sizeof (string), "%04u,%04u,%04u,%04u,%04u,%04u,%04u,%04u\n",
            //                    (unsigned int) data.ch1,
            //                    (unsigned int) data.ch2,
            //                    (unsigned int) data.ch3,
            //                    (unsigned int) data.ch4,
            //                    (unsigned int) data.ch5,
            //                    (unsigned int) data.ch6,
            //                    (unsigned int) data.ch7,
            //                    (unsigned int) data.ch8);
            snprintf(string, sizeof (string), "%f\n", data.ch1);
            if (Uart1DmaTXWriteInProgress() == false) {
                Uart1DmaTXWrite(string, strlen(string));
            }
        }

        // Enable idle mode (will wake up on next interrupt)
        POWER_LowPowerModeEnter(LOW_POWER_IDLE_MODE);
    }
    return (EXIT_FAILURE);
}

//------------------------------------------------------------------------------
// End of file
