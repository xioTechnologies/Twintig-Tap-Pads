/**
 * @file Leds.h
 * @author Seb Madgwick
 * @brief Leds.
 */

#ifndef LEDS_H
#define LEDS_H

//------------------------------------------------------------------------------
// Includes

#include <stdint.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief LED channel.
 */
typedef enum {
    LedsChannelCh1 = (1 << 0),
    LedsChannelCh2 = (1 << 1),
    LedsChannelCh3 = (1 << 2),
    LedsChannelCh4 = (1 << 3),
    LedsChannelCh5 = (1 << 4),
    LedsChannelCh6 = (1 << 5),
    LedsChannelCh7 = (1 << 6),
    LedsChannelCh8 = (1 << 7),
    LedsChannelAll = (LedsChannelCh1 | LedsChannelCh2 | LedsChannelCh3 | LedsChannelCh4 | LedsChannelCh5 | LedsChannelCh6 | LedsChannelCh7 | LedsChannelCh8),
} LedsChannel;

/**
 * @brief Colour.
 */
typedef union {

    struct {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        unsigned : 8;
    } __attribute__((__packed__));
    uint32_t rgb;
} LedsColour;

//------------------------------------------------------------------------------
// Variable declarations

extern const LedsColour ledsColourRed;
extern const LedsColour ledsColourOrange;
extern const LedsColour ledsColourYellow;
extern const LedsColour ledsColourGreen;
extern const LedsColour ledsColourCyan;
extern const LedsColour ledsColourBlue;
extern const LedsColour ledsColourMagenta;
extern const LedsColour ledsColourWhite;
extern const LedsColour ledsColourBlack;

//------------------------------------------------------------------------------
// Function declarations

void LedsTasks(void);
void LedsBlink(const LedsChannel channel, const LedsColour colour);
void LedsStrobe(void);

#endif

//------------------------------------------------------------------------------
// End of file
