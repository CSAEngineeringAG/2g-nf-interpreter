
#include "UpdateFlashConfig.h"
#include <nanoPAL_BlockStorage.h>
#include <stdlib.h>


#define USAGE_UPDATE_CONFIG (BlockUsage::BlockUsage_UPDATE + 1)


BOOL GetConfigFlashBlock(BlockStorageDevice* &device, ByteAddress &address)
{
    device = BlockStorageList_GetFirstDevice();
    while (device) {
        UINT32 regionIdx, rangeIdx;
        if (BlockStorageDevice_FindForBlockUsage(device, USAGE_UPDATE_CONFIG, &address, &regionIdx, &rangeIdx)) {
            return TRUE;
        }
        device = BlockStorageList_GetNextDevice(device);
    }
    return FALSE;
}

BOOL InvalidateUpdateFlashConfig()
{
    BlockStorageDevice* device;
    ByteAddress address;
    if (GetConfigFlashBlock(device, address)) {
        // clear config.header
        //return BlockStorageDevice_Memset(device, address, 0, sizeof(HAL_UPDATE_CONFIG));
        return BlockStorageDevice_EraseBlock(device, address);
    }
    return FALSE;
}

BOOL WriteUpdateFlashConfig(HAL_UPDATE_CONFIG* config)
{
    if (config) {
        BlockStorageDevice* device;
        ByteAddress address;
        if (GetConfigFlashBlock(device, address)) {
            if (BlockStorageDevice_EraseBlock(device, address)) {
                return BlockStorageDevice_Write(device, address, sizeof(HAL_UPDATE_CONFIG), (unsigned char*) config, FALSE);
            }
        }
    }
    return FALSE;
}

BOOL GetUpdateFlashConfig(HAL_UPDATE_CONFIG* config)
{
    if (config) {
        BlockStorageDevice* device;
        ByteAddress address;
        if (GetConfigFlashBlock(device, address)) {
            if (BlockStorageDevice_Read(device, address, sizeof(HAL_UPDATE_CONFIG), (unsigned char*) config)) {
                // check enable flag, reject 0 & 0xFF
                if (config->Header.Enable == TRUE) return TRUE;
            }
        }
    }
    return FALSE;
}

