/**
 * @file Send.h
 * @author Seb Madgwick
 * @brief Message sending.
 */

#ifndef SEND_H
#define SEND_H

//------------------------------------------------------------------------------
// Includes

#include <stddef.h>
#include <stdint.h>

//------------------------------------------------------------------------------
// Function declarations

void SendSerialAccessory(const uint64_t timestamp, const char* format, ...);
void SendNotification(const char* format, ...);
void SendError(const char* format, ...);
void SendResponse(const void* const data, const size_t numberOfBytes);
size_t SendBufferOverflow(void);

#endif

//------------------------------------------------------------------------------
// End of file
