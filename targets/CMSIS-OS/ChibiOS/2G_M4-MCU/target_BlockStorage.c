//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <nanoPAL_BlockStorage.h>

// Internal Flash
extern struct BlockStorageDevice    STM32F4_BS;
extern struct MEMORY_MAPPED_NOR_BLOCK_CONFIG   STM32F4_Device_BSConfig;
extern IBlockStorageDevice STM32Flash_BlockStorageInterface;

// External Flash MX29
extern struct BlockStorageDevice    MX29_BS;
extern struct MEMORY_MAPPED_NOR_BLOCK_CONFIG   MX29_Device_BSConfig;
extern IBlockStorageDevice MX29Flash_BlockStorageInterface;

void BlockStorage_AddDevices()
{
    BlockStorageList_AddDevice( (BlockStorageDevice*)&STM32F4_BS, &STM32Flash_BlockStorageInterface, &STM32F4_Device_BSConfig, false);
	BlockStorageList_AddDevice( (BlockStorageDevice*)&MX29_BS, &MX29Flash_BlockStorageInterface, &MX29_Device_BSConfig, false);
}
