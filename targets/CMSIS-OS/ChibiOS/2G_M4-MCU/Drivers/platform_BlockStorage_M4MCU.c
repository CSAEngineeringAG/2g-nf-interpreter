#include <nanoPAL_BlockStorage.h>
#include "MX29_FlashDriver_v2.h"

// map here the Block Storage Interface to the STM32 driver
IBlockStorageDevice MX29Flash_BlockStorageInterface =
{                          
    &MX29Driver_ChipInitialize,
    &MX29Driver_ChipUnInitialize,
    &MX29Driver_GetDeviceInfo,
    &MX29Driver_Read,
    &MX29Driver_Write,
    NULL,
    &MX29Driver_IsBlockErased,    
    &MX29Driver_EraseBlock,
    NULL,
    NULL
};