////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for MX29: Copyright (c) Oberon microsystems, Inc.
//
//  *** MX29 Flash Driver ***
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ch.h>
#include <hal.h>
#include <nanoPAL_BlockStorage.h>
#include <hal_nf_community.h>

#ifndef _DRIVERS_BS_MX29_
#define _DRIVERS_BS_MX29_ 1

// need to declare this here instead of adding an include because debug_printf is declared in nanoHAL.h which is a C++ header
extern void debug_printf(const char* format, ...);

typedef uint16_t CHIP_WORD;

bool MX29Driver_ChipInitialize( void* );
bool MX29Driver_ChipUnInitialize( void* );
DeviceBlockInfo* MX29Driver_GetDeviceInfo( void* );
bool MX29Driver_Read(void*, ByteAddress startAddress, unsigned int numBytes, unsigned char * buffer);
bool MX29Driver_Write(void*, ByteAddress startAddress, unsigned int NumBytes, unsigned char * buffer, bool ReadModifyWrite);
bool MX29Driver_Memset(void*, ByteAddress startAddress, unsigned char data, unsigned int numBytes);
bool MX29Driver_IsBlockErased( void*, ByteAddress startAddress, unsigned int blockLength );
bool MX29Driver_EraseBlock( void*, ByteAddress address );
void MX29Driver_SetPowerState(void*, unsigned int State );

bool MX29Driver_WriteX(void*, ByteAddress startAddress, unsigned int numBytes, unsigned char * buffer, bool ReadModifyWrite, bool fIncrementDataPtr);
bool MX29Driver_Action_EraseSector( void*, volatile CHIP_WORD* SectorStart );
void MX29Driver_Action_WriteWord( void*, volatile CHIP_WORD* Address, CHIP_WORD Data );


#endif // _DRIVERS_BS_MX29_

