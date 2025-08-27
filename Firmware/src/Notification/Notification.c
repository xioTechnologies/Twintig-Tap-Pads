/**
 * @file Notification.c
 * @author Seb Madgwick
 * @brief Notifications.
 */

//------------------------------------------------------------------------------
// Includes

#include "Adc/Adc.h"
#include "Periodic.h"
#include "Send/Send.h"
#include "Usb/UsbCdc.h"

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Module tasks. This function should be called repeatedly within the
 * main program loop.
 */
void NotificationTasks(void) {

    // Do nothing else until polling period elapsed
    if (PERIODIC_POLL(1.0f) == false) {
        return;
    }

    // IMU buffer overflow
    const uint32_t numberOfSamples = AdcBufferOverflow();
    if (numberOfSamples > 0) {
        SendError("ADC buffer overflow. %u samples lost.", numberOfSamples);
    }

    // Send buffer overflow
    const uint32_t bufferOverflow = SendBufferOverflow();
    if (bufferOverflow > 0) {
        SendError("USB buffer overflow. %u bytes lost.", bufferOverflow);
    }
}

//------------------------------------------------------------------------------
// End of file
