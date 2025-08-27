/**
 * @file Config.h
 * @author Seb Madgwick
 * @brief Library configuration.
 */

#ifndef CONFIG_H
#define CONFIG_H

//------------------------------------------------------------------------------
// Includes

#include "Spi/Spi1DmaTx.h"

//------------------------------------------------------------------------------
// Definitions

#define NEOPIXELS_1_HAL_NUMBER_OF_PIXELS    (8)
#define NEOPIXELS_1_SPI                     spi1DmaTx

#define UART1_READ_BUFFER_SIZE              (4096)
#define UART1_WRITE_BUFFER_SIZE             (4096)

#define UART2_READ_BUFFER_SIZE              (16)
#define UART2_WRITE_BUFFER_SIZE             (4096)

#define USB_CDC_READ_BUFFER_SIZE            (4096)
#define USB_CDC_WRITE_BUFFER_SIZE           (4096)

#endif

//------------------------------------------------------------------------------
// End of file
