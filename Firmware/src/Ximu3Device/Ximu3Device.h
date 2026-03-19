/**
 * @file Ximu3Device.h
 * @author Seb Madgwick
 * @brief x-IMU3 device.
 */

#ifndef XIMU3_DEVICE_H
#define XIMU3_DEVICE_H

//------------------------------------------------------------------------------
// Includes

#include "x-IMU3-Device/Ximu3.h"

//------------------------------------------------------------------------------
// Function declarations

void Ximu3DeviceInitialise(void);
void Ximu3DeviceTasks(void);
const Ximu3SettingsValues* Ximu3DeviceGet(void);

#endif

//------------------------------------------------------------------------------
// End of file
