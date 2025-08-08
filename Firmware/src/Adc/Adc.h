/**
 * @file Adc.h
 * @author Seb Madgwick
 * @brief ADC driver.
 */

#ifndef ADC_H
#define ADC_H

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief ADC data.
 */
typedef struct {
    unsigned int counter; // increments each time data is updated
    float ch1;
    float ch2;
    float ch3;
    float ch4;
    float ch5;
    float ch6;
    float ch7;
    float ch8;
} AdcData;

//------------------------------------------------------------------------------
// Function prototypes

void AdcInitialise(void);
void AdcGetData(AdcData * const data_);

#endif

//------------------------------------------------------------------------------
// End of file
