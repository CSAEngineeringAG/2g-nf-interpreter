//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <nanoHAL.h>

#if (CH_CFG_ST_RESOLUTION == 64)
	#error "Not supported"
#elif CH_CFG_ST_RESOLUTION == 32
	#define TOPVALUE ((uint64_t)0x100000000ull)
#elif CH_CFG_ST_RESOLUTION == 16
	#define TOPVALUE ((uint64_t)0x10000ull)
#endif

uint64_t HAL_Time_ExtendedCurrentSysTicks(void) {

	static uint64_t extendedCounter = 0;
	static systime_t prevKernelTick = 0;

	systime_t kernelTick = chVTGetSystemTimeX();

	// Check if we have overflow during this call
	// It is assumed that this function gets called twice within its overflow range
	// (e.g. for 32-bit counter this is 49.71 days)
	GLOBAL_LOCK();
	{
		if (prevKernelTick > kernelTick)
		{
			extendedCounter += TOPVALUE;
		}
		prevKernelTick = kernelTick;
	}
	GLOBAL_UNLOCK();

	return extendedCounter + kernelTick;
}

// implementation required for STM Cube package
// Provides a tick value in millisecond.
extern "C" {

uint32_t HAL_GetTick(void)
{
  return TIME_I2MS(chVTGetSystemTimeX());
}

}

// implementation required for STM Cube package
// This function provides minimum delay (in milliseconds).
extern "C" {

void HAL_Delay(uint32_t delay)
{
    systime_t start = chVTGetSystemTime();
    systime_t end = start + TIME_MS2I(delay);
    
    do
    {
        // do nothing until the timeout expires
        chThdYield();
    }
    while(chVTIsSystemTimeWithin(start, end));
}

}
