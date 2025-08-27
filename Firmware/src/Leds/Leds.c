/**
 * @file Leds.c
 * @author Seb Madgwick
 * @brief Leds.
 */

//------------------------------------------------------------------------------
// Includes

#include "Leds.h"
#include "NeoPixels/NeoPixels1.h"
#include "Periodic.h"
#include <stdbool.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Brightness.
 */
typedef enum {
    BrightnessLow = 7,
    BrightnessHigh = 4,
} Brightness;

//------------------------------------------------------------------------------
// Function declarations

static inline __attribute__((always_inline)) void SetLeds(const LedsChannel channel, const LedsColour colour, const Brightness brightness);

//------------------------------------------------------------------------------
// Variables

const LedsColour ledsColourRed = {.rgb = 0xFF0000};
const LedsColour ledsColourOrange = {.rgb = 0xFF1F00};
const LedsColour ledsColourYellow = {.rgb = 0xFFFF00};
const LedsColour ledsColourGreen = {.rgb = 0x00FF1F};
const LedsColour ledsColourCyan = {.rgb = 0x00FFFF};
const LedsColour ledsColourBlue = {.rgb = 0x001FFF};
const LedsColour ledsColourMagenta = {.rgb = 0xFF00FF};
const LedsColour ledsColourWhite = {.rgb = 0xFFFFFF};
const LedsColour ledsColourBlack = {.rgb = 0x000000};

static bool blinkPending;
static LedsChannel blinkChannel;
static LedsColour blinkColour;
static uint64_t strobeTimeout;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Module tasks. This function should be called repeatedly within the
 * main program loop.
 */
void LedsTasks(void) {

    // Do nothing else until polling period elapsed
    if (PERIODIC_POLL(0.1f) == false) {
        return;
    }

    // Strobe
    if (TimerGetTicks64() < strobeTimeout) {
        static int counter;
        counter++;
        SetLeds(LedsChannelAll, (counter & 1) != 0 ? ledsColourWhite : ledsColourBlack, BrightnessHigh);
        return;
    }

    // Blink
    if (blinkPending) {
        SetLeds(blinkChannel, blinkColour, BrightnessHigh);
        blinkPending = false;
        return;
    }

    // Normal
    SetLeds(LedsChannelAll, ledsColourWhite, BrightnessLow);
}

/**
 * @brief Sets the PWM.
 * @param channel Channel.
 * @param colour Colour.
 * @param brightness Brightness.
 */
static inline __attribute__((always_inline)) void SetLeds(const LedsChannel channel, const LedsColour colour, const Brightness brightness) {
    const NeoPixelsPixel pixel = {
        .red = colour.red >> brightness,
        .green = colour.green >> brightness,
        .blue = colour.blue >> brightness,
    };
    for (int index = 0; index < NEOPIXELS_1_HAL_NUMBER_OF_PIXELS; index++) {
        if ((channel & (1 << index)) != 0) {
            neoPixels1Pixels[index] = pixel;
        }
    }
    NeoPixels1Update();
}

/**
 * @brief Blinks the LEDs.
 */
void LedsBlink(const LedsChannel channel, const LedsColour colour) {
    blinkPending = true;
    blinkChannel = channel;
    blinkColour = colour;
}

/**
 * @brief Strobes the LEDs.
 */
void LedsStrobe(void) {
    strobeTimeout = TimerGetTicks64() + (5 * TIMER_TICKS_PER_SECOND);
}

//------------------------------------------------------------------------------
// End of file
