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

__attribute__((format(printf, 2, 3))) void SendSerialAccessory(const uint64_t ticks, const char* const format, ...);
__attribute__((format(printf, 1, 2))) void SendNotification(const char* const format, ...);
__attribute__((format(printf, 1, 2))) void SendError(const char* const format, ...);
void SendResponse(const void* const data, const size_t numberOfBytes);
size_t SendBufferOverflow(void);

#endif

//------------------------------------------------------------------------------
// End of file
