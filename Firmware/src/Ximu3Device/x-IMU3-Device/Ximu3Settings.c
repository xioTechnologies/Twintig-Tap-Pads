/**
 * @file Ximu3Settings.c
 * @author Seb Madgwick
 * @brief x-IMU3 settings.
 */

//------------------------------------------------------------------------------
// Includes

#include "Metadata.h"
#include <string.h>
#include "Ximu3Settings.h"

//------------------------------------------------------------------------------
// Function declarations

static void SetValue(const Metadata * const metadata, const void* const value);
static void CopyString(char* const destination, const size_t destinationSize, const char* string);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises the module. This function must only be called once, on
 * system startup.
 * @param settings Settings.
 */
void Ximu3SettingsInitialise(Ximu3Settings * const settings) {

    // Read values from NVM
    if (settings->nvmRead != NULL) {
        settings->nvmRead(&settings->values, sizeof (settings->values), settings->context);
    } else {
        memset(&settings->values, 0xFF, sizeof (settings->values));
    }

    // Fix invalid values
    for (int index = 0; index < XIMU3_NUMBER_OF_SETTINGS; index++) {
        const Metadata metadata = MetadataGet(settings, index);
        SetValue(&metadata, metadata.value);
    }

    // Epilogue
    if (settings->initialiseEpilogue != NULL) {
        settings->initialiseEpilogue(settings->context);
    }
}

/**
 * @brief Load defaults.
 * @param settings Settings.
 * @param overwritePreserved True to overwrite preserved settings.
 */
void Ximu3SettingsLoadDefaults(Ximu3Settings * const settings, const bool overwritePreserved) {

    // Load defaults
    for (int index = 0; index < XIMU3_NUMBER_OF_SETTINGS; index++) {
        const Metadata metadata = MetadataGet(settings, index);
        if (metadata.preserved && (overwritePreserved == false)) {
            continue;
        }
        Ximu3SettingsSet(settings, index, metadata.defaultValue, true);
    }

    // Epilogue
    if (settings->defaultsEpilogue != NULL) {
        settings->defaultsEpilogue(settings->context);
    }
}

/**
 * @brief Returns values.
 * @return Values.
 */
const Ximu3SettingsValues* Ximu3SettingsGet(const Ximu3Settings * const settings) {
    return &settings->values;
}

/**
 * @brief Sets value.
 * @param settings Settings.
 * @param index Index.
 * @param value Value.
 * @param overrideReadOnly True to override read-only.
 */
void Ximu3SettingsSet(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const void* const value, const bool overrideReadOnly) {

    // Get metadata
    const Metadata metadata = MetadataGet(settings, index);

    // Do nothing if read-only
    if ((overrideReadOnly == false) && metadata.readOnly) {
        return;
    }

    // Do nothing if value unchanged
    if ((metadata.type == MetadataTypeString) && (strncmp(metadata.value, value, metadata.size) == 0)) {
        return;
    } else if (memcmp(metadata.value, value, metadata.size) == 0) {
        return;
    }

    // Clear applied flag
    *metadata.applied = false;

    // Write value
    SetValue(&metadata, value);
}

/**
 * @brief Sets value. Invalid values (including unterminated strings) will be
 * fixed.
 * @param metadata Metadata.
 * @param value Value.
 */
static void SetValue(const Metadata * const metadata, const void* const value) {

    // Set value
    switch (metadata->type) {
        case MetadataTypeBool:
            memcpy(metadata->value, value, metadata->size);
            return;
        case MetadataTypeString:
            CopyString(metadata->value, metadata->size, value);
            return;
    }
    memcpy(metadata->value, metadata->defaultValue, metadata->size);
}

/**
 * @brief Copies string. Unprintable characters are replaced with '?'. The
 * destination is padded with trailing zeros.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param string String.
 */
static void CopyString(char* const destination, const size_t destinationSize, const char* string) {
    for (size_t index = 0; index < destinationSize; index++) {
        if (*string == '\0') {
            destination[index] = *string;
            continue;
        }
        if (((unsigned char) *string < 0x20) || ((unsigned char) *string > 0x7E)) {
            destination[index] = '?';
        } else {
            destination[index] = *string;
        }
        string++;
    }
    destination[destinationSize - 1] = '\0';
}

/**
 * @brief Saves to NVM.
 * @param settings Settings.
 */
void Ximu3SettingsSave(const Ximu3Settings * const settings) {
    if (settings->nvmWrite != NULL) {
        settings->nvmWrite(&settings->values, sizeof (settings->values), settings->context);
    }
}

/**
 * @brief Returns true if apply pending.
 * @param settings Settings.
 * @param index Index.
 * @return True if apply pending.
 */
bool Ximu3SettingsApplyPending(Ximu3Settings * const settings, const Ximu3SettingsIndex index) {
    const Metadata metadata = MetadataGet(settings, index);
    return *metadata.applied == false;
}

/**
 * @brief Clears apply pending.
 * @param settings Settings.
 */
void Ximu3SettingsClearApplyPending(Ximu3Settings * const settings) {
    for (int index = 0; index < XIMU3_NUMBER_OF_SETTINGS; index++) {
        const Metadata metadata = MetadataGet(settings, index);
        *metadata.applied = true;
    }
}

//------------------------------------------------------------------------------
// End of file
