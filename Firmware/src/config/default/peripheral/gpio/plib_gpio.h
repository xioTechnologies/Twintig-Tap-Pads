/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h UUUUUUUUU

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for CH5 pin ***/
#define CH5_Get()               ((PORTG >> 6) & 0x1U)
#define CH5_GetLatch()          ((LATG >> 6) & 0x1U)
#define CH5_PIN                  GPIO_PIN_RG6

/*** Macros for CH6 pin ***/
#define CH6_Get()               ((PORTG >> 7) & 0x1U)
#define CH6_GetLatch()          ((LATG >> 7) & 0x1U)
#define CH6_PIN                  GPIO_PIN_RG7

/*** Macros for CH7 pin ***/
#define CH7_Get()               ((PORTG >> 8) & 0x1U)
#define CH7_GetLatch()          ((LATG >> 8) & 0x1U)
#define CH7_PIN                  GPIO_PIN_RG8

/*** Macros for CH8 pin ***/
#define CH8_Get()               ((PORTG >> 9) & 0x1U)
#define CH8_GetLatch()          ((LATG >> 9) & 0x1U)
#define CH8_PIN                  GPIO_PIN_RG9

/*** Macros for DEBUG pin ***/
#define DEBUG_Get()               ((PORTB >> 6) & 0x1U)
#define DEBUG_GetLatch()          ((LATB >> 6) & 0x1U)
#define DEBUG_PIN                  GPIO_PIN_RB6

/*** Macros for CH4 pin ***/
#define CH4_Get()               ((PORTB >> 12) & 0x1U)
#define CH4_GetLatch()          ((LATB >> 12) & 0x1U)
#define CH4_PIN                  GPIO_PIN_RB12

/*** Macros for CH3 pin ***/
#define CH3_Get()               ((PORTB >> 13) & 0x1U)
#define CH3_GetLatch()          ((LATB >> 13) & 0x1U)
#define CH3_PIN                  GPIO_PIN_RB13

/*** Macros for CH2 pin ***/
#define CH2_Get()               ((PORTB >> 14) & 0x1U)
#define CH2_GetLatch()          ((LATB >> 14) & 0x1U)
#define CH2_PIN                  GPIO_PIN_RB14

/*** Macros for CH1 pin ***/
#define CH1_Get()               ((PORTB >> 15) & 0x1U)
#define CH1_GetLatch()          ((LATB >> 15) & 0x1U)
#define CH1_PIN                  GPIO_PIN_RB15

/*** Macros for CLKI pin ***/
#define CLKI_Get()               ((PORTC >> 12) & 0x1U)
#define CLKI_GetLatch()          ((LATC >> 12) & 0x1U)
#define CLKI_PIN                  GPIO_PIN_RC12

/*** Macros for RGB pin ***/
#define RGB_Get()               ((PORTC >> 13) & 0x1U)
#define RGB_GetLatch()          ((LATC >> 13) & 0x1U)
#define RGB_PIN                  GPIO_PIN_RC13

/*** Macros for RGB_SDI pin ***/
#define RGB_SDI_Get()               ((PORTC >> 14) & 0x1U)
#define RGB_SDI_GetLatch()          ((LATC >> 14) & 0x1U)
#define RGB_SDI_PIN                  GPIO_PIN_RC14

/*** Macros for RGB_SCK pin ***/
#define RGB_SCK_Get()               ((PORTD >> 1) & 0x1U)
#define RGB_SCK_GetLatch()          ((LATD >> 1) & 0x1U)
#define RGB_SCK_PIN                  GPIO_PIN_RD1

/*** Macros for RX pin ***/
#define RX_Get()               ((PORTD >> 2) & 0x1U)
#define RX_GetLatch()          ((LATD >> 2) & 0x1U)
#define RX_PIN                  GPIO_PIN_RD2

/*** Macros for TX pin ***/
#define TX_Get()               ((PORTD >> 3) & 0x1U)
#define TX_GetLatch()          ((LATD >> 3) & 0x1U)
#define TX_PIN                  GPIO_PIN_RD3

/*** Macros for CTS pin ***/
#define CTS_Get()               ((PORTD >> 4) & 0x1U)
#define CTS_GetLatch()          ((LATD >> 4) & 0x1U)
#define CTS_PIN                  GPIO_PIN_RD4

/*** Macros for RTS pin ***/
#define RTS_Get()               ((PORTD >> 5) & 0x1U)
#define RTS_GetLatch()          ((LATD >> 5) & 0x1U)
#define RTS_PIN                  GPIO_PIN_RD5


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/


#define    GPIO_PORT_B  (0)
#define    GPIO_PORT_C  (1)
#define    GPIO_PORT_D  (2)
#define    GPIO_PORT_E  (3)
#define    GPIO_PORT_F  (4)
#define    GPIO_PORT_G  (5)
typedef uint32_t GPIO_PORT;

typedef enum
{
    GPIO_INTERRUPT_ON_MISMATCH,
    GPIO_INTERRUPT_ON_RISING_EDGE,
    GPIO_INTERRUPT_ON_FALLING_EDGE,
    GPIO_INTERRUPT_ON_BOTH_EDGES,
}GPIO_INTERRUPT_STYLE;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/


#define     GPIO_PIN_RB0  (0U)
#define     GPIO_PIN_RB1  (1U)
#define     GPIO_PIN_RB2  (2U)
#define     GPIO_PIN_RB3  (3U)
#define     GPIO_PIN_RB4  (4U)
#define     GPIO_PIN_RB5  (5U)
#define     GPIO_PIN_RB6  (6U)
#define     GPIO_PIN_RB7  (7U)
#define     GPIO_PIN_RB8  (8U)
#define     GPIO_PIN_RB9  (9U)
#define     GPIO_PIN_RB10  (10U)
#define     GPIO_PIN_RB11  (11U)
#define     GPIO_PIN_RB12  (12U)
#define     GPIO_PIN_RB13  (13U)
#define     GPIO_PIN_RB14  (14U)
#define     GPIO_PIN_RB15  (15U)
#define     GPIO_PIN_RC12  (28U)
#define     GPIO_PIN_RC13  (29U)
#define     GPIO_PIN_RC14  (30U)
#define     GPIO_PIN_RC15  (31U)
#define     GPIO_PIN_RD0  (32U)
#define     GPIO_PIN_RD1  (33U)
#define     GPIO_PIN_RD2  (34U)
#define     GPIO_PIN_RD3  (35U)
#define     GPIO_PIN_RD4  (36U)
#define     GPIO_PIN_RD5  (37U)
#define     GPIO_PIN_RD9  (41U)
#define     GPIO_PIN_RD10  (42U)
#define     GPIO_PIN_RD11  (43U)
#define     GPIO_PIN_RE0  (48U)
#define     GPIO_PIN_RE1  (49U)
#define     GPIO_PIN_RE2  (50U)
#define     GPIO_PIN_RE3  (51U)
#define     GPIO_PIN_RE4  (52U)
#define     GPIO_PIN_RE5  (53U)
#define     GPIO_PIN_RE6  (54U)
#define     GPIO_PIN_RE7  (55U)
#define     GPIO_PIN_RF0  (64U)
#define     GPIO_PIN_RF1  (65U)
#define     GPIO_PIN_RF3  (67U)
#define     GPIO_PIN_RF4  (68U)
#define     GPIO_PIN_RF5  (69U)
#define     GPIO_PIN_RG6  (86U)
#define     GPIO_PIN_RG7  (87U)
#define     GPIO_PIN_RG8  (88U)
#define     GPIO_PIN_RG9  (89U)

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
#define    GPIO_PIN_NONE   (-1)

typedef uint32_t GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
     uint32_t xvalue = (uint32_t)value;
    GPIO_PortWrite((pin>>4U), (uint32_t)(0x1U) << (pin & 0xFU), (xvalue) << (pin & 0xFU));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return ((((GPIO_PortRead((GPIO_PORT)(pin>>4U))) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (((GPIO_PortLatchRead((GPIO_PORT)(pin>>4U)) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
