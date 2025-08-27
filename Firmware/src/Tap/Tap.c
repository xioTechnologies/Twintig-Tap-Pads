/**
 * @file Tap.c
 * @author Seb Madgwick
 * @brief Tap.
 */

//------------------------------------------------------------------------------
// Includes

#include "Adc/Adc.h"
#include "Filter.h"
#include "Leds/Leds.h"
#include <math.h>
#include "Send/Send.h"
#include "Tap.h"
#include "Timer/Timer.h"
#include "TrueOnce.h"

//------------------------------------------------------------------------------
// Function declarations

static inline __attribute__((always_inline)) void Detect(uint64_t * const holdoff, const float value, const char* const string, const LedsChannel channel);

//------------------------------------------------------------------------------
// Variables

static Filter ch1Filter;
static Filter ch2Filter;
static Filter ch3Filter;
static Filter ch4Filter;
static Filter ch5Filter;
static Filter ch6Filter;
static Filter ch7Filter;
static Filter ch8Filter;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Module tasks. This function should be called repeatedly within the
 * main program loop.
 */
void TapTasks(void) {

    // Initialise filters
    if (TRUE_ONCE()) {
        static const float sampleRate = 375.0f;
        static const float cutoff = 10.0f;
        FilterSetCutoff(&ch1Filter, sampleRate, cutoff);
        FilterSetCutoff(&ch2Filter, sampleRate, cutoff);
        FilterSetCutoff(&ch3Filter, sampleRate, cutoff);
        FilterSetCutoff(&ch4Filter, sampleRate, cutoff);
        FilterSetCutoff(&ch5Filter, sampleRate, cutoff);
        FilterSetCutoff(&ch6Filter, sampleRate, cutoff);
        FilterSetCutoff(&ch7Filter, sampleRate, cutoff);
        FilterSetCutoff(&ch8Filter, sampleRate, cutoff);
    }

    // Read ADC data
    AdcData data;
    if (AdcGetData(&data) != AdcResultOk) {
        return;
    }

    // Filter ADC data
    data.ch1 = FilterUpdate(&ch1Filter, data.ch1);
    data.ch2 = FilterUpdate(&ch2Filter, data.ch2);
    data.ch3 = FilterUpdate(&ch3Filter, data.ch3);
    data.ch4 = FilterUpdate(&ch4Filter, data.ch4);
    data.ch5 = FilterUpdate(&ch5Filter, data.ch5);
    data.ch6 = FilterUpdate(&ch6Filter, data.ch6);
    data.ch7 = FilterUpdate(&ch7Filter, data.ch7);
    data.ch8 = FilterUpdate(&ch8Filter, data.ch8);

    // Wait for filter outputs to settle
    if (TimerGetTicks64() < TIMER_TICKS_PER_SECOND) {
        return;
    }

    // Send ADC data as serial accessory message
    SendSerialAccessory(data.timestamp, "%f,%f,%f,%f,%f,%f,%f,%f\n",
            data.ch1,
            data.ch2,
            data.ch3,
            data.ch4,
            data.ch5,
            data.ch6,
            data.ch7,
            data.ch8);

    // Detect taps
    static uint64_t holdoff;
    if (TimerGetTicks64() < holdoff) {
        return;
    }
    Detect(&holdoff, data.ch1, "CH1", LedsChannelCh1);
    Detect(&holdoff, data.ch2, "CH2", LedsChannelCh2);
    Detect(&holdoff, data.ch3, "CH3", LedsChannelCh3);
    Detect(&holdoff, data.ch4, "CH4", LedsChannelCh4);
    Detect(&holdoff, data.ch5, "CH5", LedsChannelCh5);
    Detect(&holdoff, data.ch6, "CH6", LedsChannelCh6);
    Detect(&holdoff, data.ch7, "CH7", LedsChannelCh7);
    Detect(&holdoff, data.ch8, "CH8", LedsChannelCh8);
}

/**
 * @brief Detect tap.
 * @param holdoff Holdoff.
 * @param value Value.
 * @param string String.
 */
static inline __attribute__((always_inline)) void Detect(uint64_t * const holdoff, const float value, const char* const string, const LedsChannel channel) {
    if (fabs(value) < 0.1f) {
        return;
    }
    *holdoff = TimerGetTicks64() + (250 * TIMER_TICKS_PER_MILLISECOND);
    SendNotification(string);
    LedsBlink(channel, ledsColourCyan);
}

//------------------------------------------------------------------------------
// End of file
