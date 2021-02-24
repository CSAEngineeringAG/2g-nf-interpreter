//
// Copyright (c) 2018 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//
#ifndef _NANOHAL_WATCHDOG_H_
#define _NANOHAL_WATCHDOG_H_ 1

#include <nanoWeak.h>

typedef enum EResetReason
{
	SOFT_RESET,
	HARD_RESET,
	WATCHDOG_RESET
} eResetReason_t;

#ifdef __cplusplus
extern "C" {
#endif
    //Watchdog functions
    void Watchdog_Init();
    void Watchdog_Reset();
    void Watchdog_Init_From_Managed();
    void Watchdog_Reset_From_Managed();
    eResetReason_t GetWatchdogResetReason();
#ifdef __cplusplus
}
#endif

#endif
