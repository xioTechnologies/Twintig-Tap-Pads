/**
 * @file Filter.h
 * @author Seb Madgwick
 * @brief High-pass filter.
 */

#ifndef FILTER_H
#define FILTER_H

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Filter structure. All structure members are private.
 */
typedef struct {
    float coefficient;
    float previousInput;
    float previousOutput;
} Filter;

//------------------------------------------------------------------------------
// Function prototypes

void FilterSetCutoff(Filter * const filter, const float sampleRate, const float cutoff);
float FilterUpdate(Filter * const filter, const float input);

#endif

//------------------------------------------------------------------------------
// End of file
