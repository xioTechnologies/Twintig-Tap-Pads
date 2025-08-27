/**
 * @file Adc.h
 * @author Seb Madgwick
 * @brief ADC driver.
 */

#ifndef ADC_H
#define ADC_H

//------------------------------------------------------------------------------
// Includes

#include <stdint.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief ADC data.
 */
typedef struct {
    uint64_t timestamp;
    float ch1;
    float ch2;
    float ch3;
    float ch4;
    float ch5;
    float ch6;
    float ch7;
    float ch8;
} AdcData;

/**
 * @brief Result.
 */
typedef enum {
    AdcResultOk,
    AdcResultError,
} AdcResult;

//------------------------------------------------------------------------------
// Function prototypes

void AdcInitialise(void);
AdcResult AdcGetData(AdcData * const data);
uint32_t AdcBufferOverflow(void);

#endif

//------------------------------------------------------------------------------
// End of file
