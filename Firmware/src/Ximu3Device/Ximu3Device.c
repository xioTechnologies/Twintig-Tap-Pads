/**
 * @file Ximu3Device.c
 * @author Seb Madgwick
 * @brief x-IMU3 device.
 */

//------------------------------------------------------------------------------
// Includes

#include "Leds/Leds.h"
#include "Send/Send.h"
#include "Timer/Timer.h"
#include "Usb/UsbCdc.h"
#include "x-IMU3-Device/Ximu3.h"

//------------------------------------------------------------------------------
// Function declarations

static size_t UsbRead(void* const destination, size_t numberOfBytes, void* const context);
static void UsbWrite(const void* const data, const size_t numberOfBytes, void* const context);
static void Ping(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Blink(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Strobe(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Note(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Error(const char* const error, void* const context);

//------------------------------------------------------------------------------
// Variables

static Ximu3CommandInterface interfaces[] = {
    { .name = "USB", .read = UsbRead, .write = UsbWrite},
};
static const Ximu3CommandMap commands[] = {
    {"ping", Ping},
    {"blink", Blink},
    {"strobe", Strobe},
    {"note", Note},
};
static Ximu3CommandBridge bridge = {
    .interfaces = interfaces,
    .numberOfInterfaces = sizeof (interfaces) / sizeof (Ximu3CommandInterface),
    .commands = commands,
    .numberOfCommands = sizeof (commands) / sizeof (Ximu3CommandMap),
    .error = Error,
};

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Module tasks. This function should be called repeatedly within the
 * main program loop.
 */
void Ximu3DeviceTasks(void) {
    Ximu3CommandTasks(&bridge);
}

/**
 * @brief Reads data from the read buffer.
 * @param destination Destination.
 * @param numberOfBytes Number of bytes.
 * @param context Context.
 * @return Number of bytes read.
 */
size_t UsbRead(void* const destination, size_t numberOfBytes, void* const context) {
    return UsbCdcRead(destination, numberOfBytes);
}

/**
 * @brief Writes data to the write buffer.
 * @param data Data.
 * @param numberOfBytes Number of bytes.
 * @param context Context.
 */
void UsbWrite(const void* const data, const size_t numberOfBytes, void* const context) {
    SendResponse(data, numberOfBytes);
}

/**
 * @brief Ping command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Ping(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    Ximu3CommandRespondPing(response, "Twintig Tap Pads", "");
}

/**
 * @brief Blink command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
void Blink(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    LedsBlink(LedsChannelAll, ledsColourWhite);
    Ximu3CommandRespond(response);
}

/**
 * @brief Strobe command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
void Strobe(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    LedsStrobe();
    Ximu3CommandRespond(response);
}

/**
 * @brief Note command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Note(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    char string[XIMU3_VALUE_SIZE];
    if (Ximu3CommandParseString(value, response, string, sizeof (string), NULL) != 0) {
        return;
    }
    SendNotification(string);
    Ximu3CommandRespond(response);
}

/**
 * @brief Error handler.
 * @param error error.
 * @param context Context.
 */
static void Error(const char* const error, void* const context) {
    SendError(error);
}

//------------------------------------------------------------------------------
// End of file
