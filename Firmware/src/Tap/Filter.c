/**
 * @file Filter.c
 * @author Seb Madgwick
 * @brief High-pass filter.
 */

//------------------------------------------------------------------------------
// Includes

#include "Filter.h"
#include <math.h>

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Sets the filter cutoff frequency.
 * @param cutoff Cutoff in Hz.
 * @param filter Filter structure.
 * @param sampleRate Sample rate in Hz.
 */
void FilterSetCutoff(Filter * const filter, const float sampleRate, const float cutoff) {
    filter->coefficient = 1.0f / ((2.0f * M_PI * cutoff * (1.0f / sampleRate)) + 1.0f);
}

/**
 * @brief Updates the filter with the new input value and returns the output.
 * @param filter Filter structure.
 * @param input Input.
 * @return Output.
 */
float FilterUpdate(Filter * const filter, const float input) {
    const float output = filter->coefficient * (filter->previousOutput + input - filter->previousInput);
    filter->previousInput = input;
    filter->previousOutput = output;
    return output;
}

//------------------------------------------------------------------------------
// End of file
