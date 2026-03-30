/**
 * @file main.c
 * @author Seb Madgwick
 * @brief Main file.
 *
 * Device:
 * PIC32MZ0512EFE064
 *
 * Compiler:
 * XC32 v5.10, MPLAB Harmony 3
 */

//------------------------------------------------------------------------------
// Includes

#include "Adc/Adc.h"
#include "definitions.h"
#include "FirmwareVersion.h"
#include "Leds/Leds.h"
#include "NeoPixels/NeoPixels.h"
#include "Notification/Notification.h"
#include "ResetCause/ResetCause.h"
#include "Spi/Spi1DmaTx.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "Tap/Tap.h"
#include "Timer/Timer.h"
#include "Uart/Uart1.h"
#include "Uart/Uart2.h"
#include "Usb/UsbCdc.h"
#include "Ximu3Device/Ximu3Device.h"

//------------------------------------------------------------------------------
// Functions

int main(void) {
    SYS_Initialize(NULL);

    // Initialise debug UART
    Uart2Initialise(&uartSettingsDefault);

    // Print startup message
    ResetCausePrint(ResetCauseGet());
    printf("Twintig Tap Pads " FIRMWARE_VERSION "\n");

    // Initialise modules
    TimerInitialise();
    AdcInitialise();
    Spi1DmaTxInitialise(&neoPixelsSpiSettings);
    Uart1Initialise(&uartSettingsDefault);
    Ximu3DeviceInitialise();

    // Main program loop
    while (true) {
        SYS_Tasks();

        // Application tasks
        LedsTasks();
        NotificationTasks();
        TapTasks();
        UsbCdcTasks();
        Ximu3DeviceTasks();
    }
    return (EXIT_FAILURE);
}

//------------------------------------------------------------------------------
// End of file
