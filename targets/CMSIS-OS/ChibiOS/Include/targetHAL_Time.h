//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _TARGET_HAL_TIME_H_
#define _TARGET_HAL_TIME_H_ 1

#include <stdint.h>
#include <targetHAL.h>

#define HAL_Time_CurrentSysTicks HAL_Time_ExtendedCurrentSysTicks
#define HAL_Time_SysTicksToTime  HAL_Time_SysTicks1kHzToTime

#ifdef __cplusplus
extern "C" {
#endif
uint64_t HAL_Time_ExtendedCurrentSysTicks( void );

// Converts sysTicks (e.g. from HAL_Time_CurrentSysTicks) to .NET ticks (100 nanoseconds)
static inline uint64_t HAL_Time_SysTicks1kHzToTime(uint64_t sysTicks)
{
#if defined(CH_CFG_ST_FREQUENCY) && (CH_CFG_ST_FREQUENCY == 1000)
	#define SYS_TICKS_TO_100_NANO_SECONDS 10000
#else
	#error "Systick frequency must be 1kHz"
#endif
    return sysTicks * SYS_TICKS_TO_100_NANO_SECONDS;
}

#ifdef __cplusplus
}
#endif


#endif //_TARGET_HAL_TIME_H_
