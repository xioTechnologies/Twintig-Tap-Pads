/**
 * @file Ximu3Device.c
 * @author Seb Madgwick
 * @brief x-IMU3 device.
 */

//------------------------------------------------------------------------------
// Includes

#include "FirmwareVersion.h"
#include "LastPage/LastPage.h"
#include "Leds/Leds.h"
#include "Send/Send.h"
#include "SerialNumber/SerialNumber.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "Timer/Timer.h"
#include "Timestamp/Timestamp.h"
#include "Usb/UsbCdc.h"
#include "x-IMU3-Device/Ximu3.h"

//------------------------------------------------------------------------------
// Function declarations

static size_t UsbRead(void* const destination, size_t numberOfBytes, void* const context);
static void UsbWrite(const void* const data, const size_t numberOfBytes, void* const context);
static void Ping(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Default(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Apply(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Save(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Note(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Timestamp(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Blink(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Strobe(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void Factory(const char* * const value, Ximu3CommandResponse * const response, void* const context);
static void NvmRead(void* const destination, const size_t numberOfBytes, void* const context);
static void NvmWrite(const void* const data, const size_t numberOfBytes, void* const context);
static void InitialiseEpilogue(void* const context);
static void DefaultsEpilogue(void* const context);
static bool OverrideReadOnly(void* const context);
static void Error(const char* const error, void* const context);

//------------------------------------------------------------------------------
// Variables

static Ximu3CommandInterface interfaces[] = {
    { .name = "USB", .read = UsbRead, .write = UsbWrite},
};

static const Ximu3CommandMap commands[] = {
    {"ping", Ping},
    {"default", Default},
    {"apply", Apply},
    {"save", Save},
    {"note", Note},
    {"timestamp", Timestamp},
    {"blink", Blink},
    {"strobe", Strobe},
    {"factory", Factory},
};

static Ximu3Settings settings = {
    .nvmRead = NvmRead,
    .nvmWrite = NvmWrite,
    .initialiseEpilogue = InitialiseEpilogue,
    .defaultsEpilogue = DefaultsEpilogue,
};

static Ximu3CommandBridge bridge = {
    .interfaces = interfaces,
    .numberOfInterfaces = sizeof (interfaces) / sizeof (Ximu3CommandInterface),
    .commands = commands,
    .numberOfCommands = sizeof (commands) / sizeof (Ximu3CommandMap),
    .settings = &settings,
    .overrideReadOnly = OverrideReadOnly,
    .error = Error,
};

static bool factoryMode;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises the module. This function must only be called once, on
 * system startup.
 */
void Ximu3DeviceInitialise(void) {
    Ximu3SettingsInitialise(&settings);
}

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
static size_t UsbRead(void* const destination, size_t numberOfBytes, void* const context) {
    return UsbCdcRead(destination, numberOfBytes);
}

/**
 * @brief Writes data to the write buffer.
 * @param data Data.
 * @param numberOfBytes Number of bytes.
 * @param context Context.
 */
static void UsbWrite(const void* const data, const size_t numberOfBytes, void* const context) {
    SendResponse(data, numberOfBytes);
}

/**
 * @brief Ping command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Ping(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != Ximu3ResultOk) {
        return;
    }
    Ximu3CommandRespondPing(response, Ximu3SettingsGet(&settings)->deviceName, Ximu3SettingsGet(&settings)->serialNumber);
}

/**
 * @brief Default command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Default(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != Ximu3ResultOk) {
        return;
    }
    Ximu3SettingsLoadDefaults(&settings, false);
    Ximu3CommandRespond(response);
}

/**
 * @brief Apply command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Apply(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != Ximu3ResultOk) {
        return;
    }
    Ximu3CommandRespond(response);
}

/**
 * @brief Save command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Save(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != Ximu3ResultOk) {
        return;
    }
    Ximu3SettingsSave(&settings);
    Ximu3CommandRespond(response);
}

/**
 * @brief Note command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Note(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    char string[XIMU3_SIZE_VALUE];
    if (Ximu3CommandParseString(value, response, string, sizeof (string), NULL) != Ximu3ResultOk) {
        return;
    }
    SendNotification(string);
    Ximu3CommandRespond(response);
}

/**
 * @brief Timestamp command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Timestamp(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    uint64_t timestamp;
    if (Ximu3CommandParseNumberU64(value, response, &timestamp) != Ximu3ResultOk) {
        return;
    }
    TimestampSet(timestamp);
    Ximu3CommandRespond(response);
}

/**
 * @brief Blink command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Blink(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != Ximu3ResultOk) {
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
static void Strobe(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != Ximu3ResultOk) {
        return;
    }
    LedsStrobe();
    Ximu3CommandRespond(response);
}

/**
 * @brief Factory command.
 * @param value Value.
 * @param response Response.
 * @param context Context.
 */
static void Factory(const char* * const value, Ximu3CommandResponse * const response, void* const context) {
    if (Ximu3CommandParseNull(value, response) != Ximu3ResultOk) {
        return;
    }
    factoryMode = true;
    Ximu3CommandRespond(response);
}

/**
 * @brief Reads from NVM.
 * @param destination Destination.
 * @param numberOfBytes Number of bytes.
 * @param context Context.
 */
static void NvmRead(void* const destination, const size_t numberOfBytes, void* const context) {
    LastPageRead(destination, numberOfBytes);
}

/**
 * @brief Writes to NVM.
 * @param data Data.
 * @param numberOfBytes Number of bytes.
 * @param context Context.
 */
static void NvmWrite(const void* const data, const size_t numberOfBytes, void* const context) {
    LastPageUpdate(data, numberOfBytes);
}

/**
 * @brief Initialise epilogue.
 * @param context Context.
 */
static void InitialiseEpilogue(void* const context) {
    const char* const firmwareVersion = Ximu3SettingsGet(&settings)->firmwareVersion;
    if (strspn(firmwareVersion, "?") == strlen(firmwareVersion)) { // if NVM blank
        Ximu3SettingsLoadDefaults(&settings, true);
        return;
    }
    if (strncmp(firmwareVersion, FIRMWARE_VERSION, sizeof (FIRMWARE_VERSION)) != 0) { // if firmware changed
        Ximu3SettingsLoadDefaults(&settings, false);
    }
}

/**
 * @brief Defaults epilogue.
 * @param context Context.
 */
static void DefaultsEpilogue(void* const context) {
    Ximu3SettingsSet(&settings, Ximu3SettingsIndexSerialNumber, SerialNumberString(), true);
    Ximu3SettingsSet(&settings, Ximu3SettingsIndexFirmwareVersion, FIRMWARE_VERSION, true);
}

/**
 * @brief Returns true if factory mode enabled.
 * @return True if factory mode enabled.
 */
static bool OverrideReadOnly(void* const context) {
    return factoryMode;
}

/**
 * @brief Error callback.
 * @param error Error.
 * @param context Context.
 */
static void Error(const char* const error, void* const context) {
    SendError(error);
}

/**
 * @brief Returns values.
 * @return Values.
 */
const Ximu3SettingsValues* Ximu3DeviceGet(void) {
    return Ximu3SettingsGet(&settings);
}

//------------------------------------------------------------------------------
// End of file
