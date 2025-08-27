/**
 * @file Send.c
 * @author Seb Madgwick
 * @brief Message sending.
 */

//------------------------------------------------------------------------------
// Includes

#include "Leds/Leds.h"
#include "Send.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "Timer/Timer.h"
#include "Usb/UsbCdc.h"
#include "Ximu3Device/x-IMU3-Device/Ximu3.h"

//------------------------------------------------------------------------------
// Function declarations

static void SendDataMessage(const void* const data, const size_t numberOfBytes);
static void SendDataMessagePriority(const void* const data, const size_t numberOfBytes);
static inline __attribute__((always_inline)) size_t Write(const void* const data, const size_t numberOfBytes, const bool priority);

//------------------------------------------------------------------------------
// Variables

static size_t bufferOverflow;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Sends serial accessory message.
 * @param timestamp Timestamp.
 * @param format Format.
 * @param ... Arguments.
 */
void SendSerialAccessory(const uint64_t timestamp, const char* format, ...) {

    // Create string
    char string[256];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(string, sizeof (string), format, arguments);
    va_end(arguments);

    // Send message
    const Ximu3DataSerialAccessory ximu3Data = {
        .timestamp = timestamp / TIMER_TICKS_PER_MICROSECOND,
        .data = (uint8_t*) string,
        .numberOfBytes = strlen(string),
    };
    char message[256];
    const size_t messageSize = Ximu3DataSerialAccessoryBinary(message, sizeof (message), &ximu3Data);
    SendDataMessage(message, messageSize);
}

/**
 * @brief Sends notification message.
 * @param format Format.
 * @param ... Arguments.
 */
void SendNotification(const char* format, ...) {

    // Create string
    char string[256];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(string, sizeof (string), format, arguments);
    va_end(arguments);

    // Send message
    const Ximu3DataNotification ximu3Data = {
        .timestamp = TimerGetTicks64() / TIMER_TICKS_PER_MICROSECOND,
        .string = string
    };
    uint8_t message[128];
    const size_t messageSize = Ximu3DataNotificationBinary(message, sizeof (message), &ximu3Data);
    SendDataMessagePriority(message, messageSize);
}

/**
 * @brief Sends error message.
 * @param format Format.
 * @param ... Arguments.
 */
void SendError(const char* format, ...) {

    // Create string
    char string[256];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(string, sizeof (string), format, arguments);
    va_end(arguments);

    // Send message
    const Ximu3DataError ximu3Data = {
        .timestamp = TimerGetTicks64() / TIMER_TICKS_PER_MICROSECOND,
        .string = string
    };
    uint8_t message[128];
    const size_t messageSize = Ximu3DataErrorAscii(message, sizeof (message), &ximu3Data);
    SendDataMessagePriority(message, messageSize);

    // Blink LED
    LedsBlink(LedsChannelAll, ledsColourRed);
}

/**
 * @brief Sends data message.
 * @param data Data.
 * @param numberOfBytes Number of bytes.
 */
static void SendDataMessage(const void* const data, const size_t numberOfBytes) {
    bufferOverflow += Write(data, numberOfBytes, false);
}

/**
 * @brief Sends data message with priority.
 * @param data Data.
 * @param numberOfBytes Number of bytes.
 */
static void SendDataMessagePriority(const void* const data, const size_t numberOfBytes) {
    bufferOverflow += Write(data, numberOfBytes, true);
}

/**
 * @brief Sends response to USB.
 * @param data Data.
 * @param numberOfBytes Number of bytes.
 */
void SendResponse(const void* const data, const size_t numberOfBytes) {
    bufferOverflow += Write(data, numberOfBytes, true);
}

/**
 * @brief Writes data and returns number of bytes lost due to buffer overflow.
 * @param data Data.
 * @param numberOfBytes Number of bytes.
 * @param priority True to write with priority.
 * @return Number of samples lost due to buffer overflow.
 */
static inline __attribute__((always_inline)) size_t Write(const void* const data, const size_t numberOfBytes, const bool priority) {
    if (UsbCdcPortOpen() == false) {
        return 0;
    }
    if ((priority == false) && (UsbCdcAvailableWrite() < (numberOfBytes + 1024))) {
        return numberOfBytes;
    }
    if (UsbCdcWrite(data, numberOfBytes) != FifoResultOk) {
        return numberOfBytes;
    }
    return 0;
}

/**
 * @brief Returns the number of bytes lost due to buffer overflow. Calling
 * this function will reset the value.
 * @return Number of samples lost due to buffer overflow.
 */
size_t SendBufferOverflow() {
    const size_t bufferOverflow_ = bufferOverflow;
    bufferOverflow = 0;
    return bufferOverflow_;
}

//------------------------------------------------------------------------------
// End of file
