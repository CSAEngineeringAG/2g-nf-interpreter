//
// Copyright (c) 2017 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include <nanoPAL_BlockStorage.h>
#include <nanoWeak.h>
#include <nanoHAL_v2.h>

BlockStorageList             g_BlockStorage;


/////////////////////////////////////////////////////
// DeviceBlockInfo stubs

SectorAddress DeviceBlockInfo_PhysicalToSectorAddress(DeviceBlockInfo* blockInfo,  const BlockRegionInfo* pRegion, ByteAddress phyAddress)
{
    return (phyAddress - pRegion->Start) / blockInfo->BytesPerSector;
}

bool DeviceBlockInfo_FindRegionFromAddress(DeviceBlockInfo* blockInfo, ByteAddress address, unsigned int* blockRegionIndex, unsigned int* blockRangeIndex)
{
    const BlockRegionInfo *pRegion;

    *blockRegionIndex = 0;

    for(uint32_t i = 0; i < blockInfo->NumRegions;  i++)
    {
        pRegion = &blockInfo->Regions[i];

        if(pRegion->Start <= address && address < (pRegion->Start + pRegion->NumBlocks * pRegion->BytesPerBlock))
        {
            uint32_t endRangeAddr = pRegion->Start + pRegion->BytesPerBlock * pRegion->BlockRanges[0].StartBlock;
            
            for(uint32_t j =0; j < pRegion->NumBlockRanges; j++)
            {
                endRangeAddr += pRegion->BytesPerBlock * BlockRange_GetBlockCount(pRegion->BlockRanges[j]);
                
                if(address < endRangeAddr)
                {
                    *blockRegionIndex = i;
                    *blockRangeIndex  = j;
                    return true;
                }
            }
        }
    }

    return false;
}

bool DeviceBlockInfo_FindNextUsageBlock(DeviceBlockInfo* blockInfo, unsigned int blockUsage, unsigned int* address, unsigned int* blockRegionIndex, unsigned int* blockRangeIndex)
{
    BlockRegionInfo *region;

    for(uint32_t i = *blockRegionIndex; i < blockInfo->NumRegions; i++)
    {
        region = &blockInfo->Regions[i];

        for( int j = *blockRangeIndex; j < (int)region->NumBlockRanges; j++)
        {
            BlockRange *pRange = (BlockRange*)&region->BlockRanges[j];
            
            if ((pRange->RangeType & BlockRange_USAGE_MASK) == blockUsage || blockUsage == BlockUsage_ANY)
            {
                *address = BlockRegionInfo_BlockAddress(region, pRange->StartBlock);
                *blockRegionIndex = i;
                *blockRangeIndex  = j;

                return true;
            }
        }

        *blockRangeIndex = 0;
    }
    
    return false;
}

bool DeviceBlockInfo_FindForBlockUsage(DeviceBlockInfo* blockInfo, unsigned int blockUsage, unsigned int* address, unsigned int* blockRegionIndex, unsigned int* blockRangeIndex)
{
    (void)blockInfo;
    (void)blockUsage;

    *address = 0;
    *blockRegionIndex = 0;
    *blockRangeIndex = 0;
    
    return DeviceBlockInfo_FindNextUsageBlock(blockInfo, blockUsage, address, blockRegionIndex, blockRangeIndex );
}


/////////////////////////////////////////////////////
// BlockStorageStream

bool BlockStorageStream_IsXIP(BlockStorageStream *stream)
{
    return 0 != (stream->Flags & BLOCKSTORAGESTREAM_c_BlockStorageStream__XIP);
}

bool BlockStorageStream_IsReadModifyWrite(BlockStorageStream *stream)
{
    return 0 != (stream->Flags & BLOCKSTORAGESTREAM_c_BlockStorageStream__ReadModWrite);
}

bool BlockStorageStream_SetReadModifyWrite(BlockStorageStream *stream)
{
    if(stream != NULL)
    {
        stream->Flags |= BLOCKSTORAGESTREAM_c_BlockStorageStream__ReadModWrite;
        return true;
    }
    else
    {
        return false;
    }
}

bool BlockStorageStream_Initialize(BlockStorageStream *stream, unsigned int blockUsage)
{
    return BlockStorageStream_InitializeWithBlockStorageDevice(stream, blockUsage, NULL);
}

bool BlockStorageStream_InitializeWithBlockStorageDevice(BlockStorageStream *stream, unsigned int blockUsage, BlockStorageDevice *pDevice)
{
    DeviceBlockInfo* deviceInfo = NULL;
    BlockStorageStream backupStream;
    BlockStorageDevice *device = NULL;

    // backup original stream, in case this gets messed up
    memcpy(&backupStream, stream, sizeof(BlockStorageStream));

    if(pDevice != NULL)
    {
        device = pDevice;

        deviceInfo = BlockStorageDevice_GetDeviceInfo(pDevice);
    }
    else
    {
        for(int i = 0; i < TARGET_BLOCKSTORAGE_COUNT; i++)
        {
            device = g_BlockStorage.DeviceList[i];

            deviceInfo = BlockStorageDevice_GetDeviceInfo(device);
            
            if(DeviceBlockInfo_FindNextUsageBlock(deviceInfo, blockUsage, &stream->BaseAddress, &stream->RegionIndex, &stream->RangeIndex))
            {
                // found a block matching the request usage
                break;
            }
            else
            {
                // couldn't find a block matching the request usage
                // need to NULL the device info that's going to be used to fill in the stream details
                deviceInfo = NULL;
            }
        }
    }

    if(deviceInfo != NULL)
    {
        BlockRegionInfo* pRegion = &deviceInfo->Regions[stream->RegionIndex];

        stream->CurrentIndex = 0;
        stream->Length       = BlockRange_GetBlockCount(pRegion->BlockRanges[stream->RangeIndex])* pRegion->BytesPerBlock;
        stream->BlockLength  = pRegion->BytesPerBlock;
        stream->CurrentUsage = (pRegion->BlockRanges[stream->RangeIndex].RangeType & BlockRange_USAGE_MASK);
        stream->Device       = device;

        if(deviceInfo->Attribute & MediaAttribute_SupportsXIP)
        {
            stream->Flags |= BLOCKSTORAGESTREAM_c_BlockStorageStream__XIP;
        }
        else
        {
            stream->Flags &= ~BLOCKSTORAGESTREAM_c_BlockStorageStream__XIP;
        }

        // check if block region is memory mapped
        if(pRegion->Attributes & BlockRegionAttribute_MemoryMapped)
        {
            BlockStorageDevice_GetMemoryMappedAddress(device, stream->RegionIndex, stream->RangeIndex, &stream->MemoryMappedAddress);

            stream->Flags |= BLOCKSTORAGESTREAM_c_BlockStorageStream__MemoryMapped;
        }
        else
        {
            stream->Flags &= ~BLOCKSTORAGESTREAM_c_BlockStorageStream__MemoryMapped;
        }

        // done here
        return true;
    }

    // couldn't find a device for the requested usage, revert stream from backup
    memcpy(stream, &backupStream, sizeof(BlockStorageStream));

    return false;
}

bool BlockStorageStream_NextStream(BlockStorageStream* stream)
{
    bool fFirstDevice = (stream->Device == NULL);

    BlockStorageStream orig;

    memcpy(&orig, stream, sizeof(orig));

    if(fFirstDevice)
    {
        stream->Device = BlockStorageList_GetFirstDevice();

        if(stream->Device == NULL || BlockStorageDevice_Next(stream->Device) == NULL) return false;

        const DeviceBlockInfo* deviceInfo = BlockStorageDevice_GetDeviceInfo(stream->Device);
        
        if(deviceInfo->Attribute & MediaAttribute_SupportsXIP)
        {
            stream->Flags |= BLOCKSTORAGESTREAM_c_BlockStorageStream__XIP;
        }
        else
        {
            stream->Flags &= ~BLOCKSTORAGESTREAM_c_BlockStorageStream__XIP;
        }
    }
    else
    {
        // move to the next range
        stream->RangeIndex++;
    }

    while(true)
    {
        if(stream->Device == NULL || BlockStorageDevice_Next(stream->Device) == NULL) break;

        if(BlockStorageDevice_FindNextUsageBlock(stream->Device, stream->Usage, &stream->BaseAddress, &stream->RegionIndex, &stream->RangeIndex))
        {
            const BlockRegionInfo* pRegion = &(BlockStorageDevice_GetDeviceInfo(stream->Device)->Regions[stream->RegionIndex]);

            stream->CurrentIndex = 0;
            stream->Length       = BlockRange_GetBlockCount(pRegion->BlockRanges[stream->RangeIndex]) * pRegion->BytesPerBlock;
            stream->BlockLength  = pRegion->BytesPerBlock;
            stream->CurrentUsage = (pRegion->BlockRanges[stream->RangeIndex].RangeType & BlockRange_USAGE_MASK);
            return true;
        }

        stream->Device = BlockStorageDevice_Next(stream->Device);

        if(BlockStorageDevice_Next(stream->Device) != NULL)
        {
            const DeviceBlockInfo* deviceInfo = BlockStorageDevice_GetDeviceInfo(stream->Device);
        
            if(deviceInfo->Attribute & MediaAttribute_SupportsXIP)
            {
                stream->Flags |= BLOCKSTORAGESTREAM_c_BlockStorageStream__XIP;
            }
            else
            {
                stream->Flags &= ~BLOCKSTORAGESTREAM_c_BlockStorageStream__XIP;
            }
        }  

        stream->RegionIndex = 0;
        stream->RangeIndex  = 0;
    }

    // go back to original stream if no others can be found
    memcpy(stream, &orig, sizeof(orig)); 

    return false;
}

bool BlockStorageStream_PrevStream(BlockStorageStream* stream)
{
    if(stream->Device == NULL || BlockStorageDevice_Prev(stream->Device) == NULL) return false;

    const BlockRegionInfo* pRegion;
    const DeviceBlockInfo* deviceInfo = BlockStorageDevice_GetDeviceInfo(stream->Device);

    BlockStorageStream orig;

    memcpy(&orig, stream, sizeof(orig));

    do
    {
        bool fLastIndex = false;
        
        if(stream->RangeIndex == 0) 
        {
            if(stream->RegionIndex == 0)
            {
                stream->Device = BlockStorageDevice_Prev(stream->Device);
                
                if(stream->Device == NULL || BlockStorageDevice_Prev(stream->Device) == NULL)
                {
                    memcpy(stream, &orig, sizeof(orig));
                    return false;
                }
                
                deviceInfo = BlockStorageDevice_GetDeviceInfo(stream->Device);
            
                stream->RegionIndex = deviceInfo->NumRegions - 1;
            }
            else
            {
                stream->RegionIndex--;
            }

            fLastIndex = true;
        }
        else
        {
            stream->RangeIndex--;
        }

        pRegion = &deviceInfo->Regions[stream->RegionIndex];

        if(fLastIndex)
        {
            stream->RangeIndex = pRegion->NumBlockRanges - 1;
        }

    } while( BlockRange_GetBlockUsage(pRegion->BlockRanges[stream->RangeIndex]) != stream->Usage );

    if(deviceInfo->Attribute & MediaAttribute_SupportsXIP)
    {
        stream->Flags |= BLOCKSTORAGESTREAM_c_BlockStorageStream__XIP;
    }
    else
    {
        stream->Flags &= ~BLOCKSTORAGESTREAM_c_BlockStorageStream__XIP;
    }
    
    stream->BlockLength  = pRegion->BytesPerBlock;
    stream->BaseAddress  = pRegion->Start + pRegion->BlockRanges[stream->RangeIndex].StartBlock * stream->BlockLength;
    stream->Length       = BlockRange_GetBlockCount(pRegion->BlockRanges[stream->RangeIndex]) * stream->BlockLength;
    stream->CurrentIndex = 0;

    return true;
}

bool BlockStorageStream_Seek(BlockStorageStream *stream, unsigned int offset, SeekOrigin origin)
{
    int32_t seekIndex;

    switch (origin)
    {
    case BlockStorageStream_SeekBegin:
        seekIndex = 0;
        break;

    case BlockStorageStream_SeekCurrent:
        seekIndex = stream->CurrentIndex;
        break;

    case BlockStorageStream_SeekEnd:
        seekIndex = stream->Length;
        break;

    default:

        return false;
    }

    if(offset == BLOCKSTORAGESTREAM_STREAM_SEEK_NEXT_BLOCK || offset == BLOCKSTORAGESTREAM_STREAM_SEEK_PREV_BLOCK)
    {
        int32_t blkOffset = seekIndex % stream->BlockLength;

        if(offset == BLOCKSTORAGESTREAM_STREAM_SEEK_NEXT_BLOCK) offset = stream->BlockLength - blkOffset;
        else if(blkOffset != 0)              offset = -blkOffset; 
        else                                 offset = -(int32_t)stream->BlockLength;
    }

    seekIndex += offset;

    while (seekIndex >= (int32_t)stream->Length)
    {
        seekIndex -= stream->Length; // subtract the length of the current stream to get the correct offset for the new stream
        
        if(!BlockStorageStream_NextStream(stream)) return false;
    }

    while (seekIndex < 0)
    {
        if(!BlockStorageStream_PrevStream(stream)) return false;

        seekIndex += stream->Length; // add the length of the new stream to get the correct offset for the new stream
    }

    stream->CurrentIndex = seekIndex;

    return true;
}

bool BlockStorageStream_Write(BlockStorageStream *stream, unsigned char *data, unsigned int length)
{
    //if(stream->Device == NULL || BlockStorageDevice_Next(stream->Device) == NULL || !data) return FALSE;
    if(stream->Device == NULL || !data) return FALSE;

    unsigned char* pData = data;

    while(length > 0)
    {
        if(stream->CurrentIndex == stream->Length)
        {
            if(!BlockStorageStream_NextStream(stream)) return false;
        }

        int writeLen = length;
        
        if((stream->CurrentIndex + writeLen) > stream->Length)
        {
            writeLen = stream->Length - stream->CurrentIndex;
        }
        
        if(!BlockStorageDevice_Write(stream->Device, BlockStorageStream_CurrentAddress(stream), writeLen, pData, BlockStorageStream_IsReadModifyWrite(stream)))
        {
            return false;
        }

        pData        += writeLen;
        length       -= writeLen;
        stream->CurrentIndex += writeLen;
    }

    return true;
}

bool BlockStorageStream_Erase(BlockStorageStream *stream, unsigned int length)
{
    bool fRet = true;
    
    //if(stream->Device == NULL || BlockStorageDevice_Next(stream->Device) == NULL) return FALSE;
    if(stream->Device == NULL) return FALSE;

    BlockStorageStream orig;
    memcpy(&orig, stream, sizeof(orig));

    if(stream->CurrentIndex == stream->Length)
    {
        if(!BlockStorageStream_NextStream(stream)) return false;
    }

    signed int len = (signed int)length;

    while(len > 0)
    {
        if(!BlockStorageDevice_EraseBlock(stream->Device, BlockStorageStream_CurrentAddress(stream) )) return FALSE;

        len -= stream->BlockLength;

        if(len > 0 && !BlockStorageStream_Seek(stream, BLOCKSTORAGESTREAM_STREAM_SEEK_NEXT_BLOCK, BlockStorageStream_SeekCurrent ))
        {
            if(!BlockStorageStream_NextStream(stream))
            {
                fRet = false;
                break;
            }
        }
    }

    // always return stream back to its original position for erases
    memcpy(stream, &orig, sizeof(orig));

    return fRet;
}

bool BlockStorageStream_ReadIntoBuffer(BlockStorageStream *stream, unsigned char *buffer, unsigned int length)
{
    if(!BlockStorageStream_IsXIP(stream))
    {
        return BlockStorageStream_Read(stream, &buffer, length);
    }
    else
    {
        unsigned char* pTmp = NULL;

        if(BlockStorageStream_Read(stream, &pTmp, length))
        {
            memcpy(buffer, pTmp, length);

            return true;
        }
    }

    return false;
}

bool BlockStorageStream_Read(BlockStorageStream* stream, unsigned char** buffer, unsigned int length)
{
    if(stream == NULL || stream->Device == NULL || buffer == 0)
    {
        return false;
    }

    DeviceBlockInfo* deviceInfo = BlockStorageDevice_GetDeviceInfo(stream->Device);
    unsigned char* pBuffer = *buffer;

    while(length > 0)
    {
        int readLen = length;

        // find the next stream if we are at the end of this one
        if(stream->CurrentIndex == stream->Length)
        {
            // TODO FIXME
            // need to check implementation of this call to get pointers to stream continuation
            if(!BlockStorageStream_NextStream(stream)) return FALSE;
        }

        if((stream->CurrentIndex + readLen) > stream->Length)
        {
            readLen = stream->Length - stream->CurrentIndex;
        }

        if(deviceInfo->Attribute & MediaAttribute_SupportsXIP)
        {
            // XIP assumes contiguous USAGE blocks
            *buffer = (unsigned char*)(BlockStorageStream_CurrentAddress(stream));
        }
        else
        {
            // non XIP storage...

            if(stream->Flags & BLOCKSTORAGESTREAM_c_BlockStorageStream__MemoryMapped)
            {
                // memory mapped region, get mapped address for read
                *buffer = (unsigned char*)(BlockStorageStream_CurrentMappedAddress(stream));
            }
            else
            {
                // non mapped access... need to call driver
                if(!stream->Device->m_BSD->Read(stream->Device->m_context, BlockStorageStream_CurrentAddress(stream), readLen, pBuffer))
                {
                    return false;
                }
            }
        }

        length       -= readLen;
        pBuffer      += readLen;
        stream->CurrentIndex += readLen;    
    }

    return true;
}

unsigned int BlockStorageStream_CurrentAddress(BlockStorageStream *stream)
{
    return stream->BaseAddress + stream->CurrentIndex;
}

unsigned int BlockStorageStream_CurrentMappedAddress(BlockStorageStream *stream)
{
    return stream->MemoryMappedAddress + stream->CurrentIndex;
}

bool BlockStorageStream_IsErased(BlockStorageStream *stream, unsigned int length)
{
    unsigned int bkupIdx   = stream->CurrentIndex;
    signed int  rem       = bkupIdx % stream->BlockLength;
    unsigned char  compValue = (unsigned int) BlockStorageDevice_GetDeviceInfo(stream->Device)->Attribute & MediaAttribute_ErasedBitsAreZero ? 0 : 0xFF;

    signed int  len       = (signed int) length;

    if(rem != 0)
    {
        if(length > stream->BlockLength)
        {
            rem = stream->BlockLength - rem;
            len -= rem;
        }
        else
        {
            rem = length;
            len = 0;
        }
        
        while(rem > 0)
        {
            unsigned char tmp[512];
            signed int left = ((unsigned long long)rem < sizeof(tmp) ? rem : (signed int) sizeof(tmp));

            BlockStorageStream_ReadIntoBuffer(stream, tmp, left);

            for(int i=0; i<left; i++)
            {
                if(tmp[i] != compValue)
                {
                    return FALSE;
                }
            }

            rem -= left;
        }
    }

    while((unsigned int) len >= stream->BlockLength)
    {
        if(!BlockStorageDevice_IsBlockErased(stream->Device, stream->BaseAddress + stream->CurrentIndex, stream->BlockLength)) return FALSE;

        len                  -= stream->BlockLength;
        stream->CurrentIndex += stream->BlockLength;
    }

    while(len > 0)
    {
        unsigned char tmp[512];
        signed int left = (len < (signed int) sizeof(tmp) ? len : (signed int) sizeof(tmp));

        BlockStorageStream_ReadIntoBuffer(stream, tmp, left);

        for(int i=0; i<left; i++)
        {
            if(tmp[i] != compValue)
            {
                return FALSE;
            }
        }

        len -= left;
    }

    stream->CurrentIndex = bkupIdx;

    return TRUE;
}

/////////////////////////////////////////////////////
// BlockStorageDevice

BlockStorageDevice* BlockStorageDevice_Next(BlockStorageDevice* device)
{
    (void)device;

    if(g_BlockStorage.DeviceCount > 1)
    {
        signed int pos = -1;
        unsigned int i;

        // Search position of actual device
        for(i = 0; i < g_BlockStorage.DeviceCount; i++)
        {
            // Check if pointer adress is identical
            if (device == g_BlockStorage.DeviceList[i])
            {
                pos = (signed int) i;
                break;
            }
        }

        // Check if another device is following actual
        if ((pos >= 0) & (pos < (signed int) g_BlockStorage.DeviceCount - 1))
        {
            return g_BlockStorage.DeviceList[pos + 1];
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

BlockStorageDevice* BlockStorageDevice_Prev(BlockStorageDevice* device)
{
    (void)device;

    if(g_BlockStorage.DeviceCount > 1)
    {
        signed int pos = -1;
        unsigned int i;

        // Search position of actual device
        for(i = 0; i < g_BlockStorage.DeviceCount; i++)
        {
            // Check if pointer adress is identical
            if (device == g_BlockStorage.DeviceList[i])
            {
                pos = (signed int) i;
                break;
            }
        }

        // Check if another device is in front of actual
        if ((pos >= 1) & (pos < (signed int) g_BlockStorage.DeviceCount - 1))
        {
            return g_BlockStorage.DeviceList[pos - 1];
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

/////////////////////////////////////////////////////////
// Description:
//    Initializes a given block device for use
// 
// Returns:
//   true if successful; false if not
//
// Remarks:
//    No other functions in this interface may be called
//    until after Init returns.
//
bool BlockStorageDevice_InitializeDevice(BlockStorageDevice* device)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

    return device->m_BSD->InitializeDevice(device->m_context);
}

/////////////////////////////////////////////////////////
// Description:
//    Initializes a given block device for use
// 
// Returns:
//   true if successful; false if not
//
// Remarks:
//   De initializes the device when no longer needed
//
bool BlockStorageDevice_UninitializeDevice(BlockStorageDevice* device)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

    return device->m_BSD->UninitializeDevice(device->m_context);
}

/////////////////////////////////////////////////////////
// Description:
//    Gets the information describing the device
//
DeviceBlockInfo* BlockStorageDevice_GetDeviceInfo(BlockStorageDevice* device)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

    return device->m_BSD->GetDeviceInfo(device->m_context);
}

/////////////////////////////////////////////////////////
// Description:
//    Reads data from a set of sectors
//
// Input:
//    startAddress - Starting Sector for the read
//    numBytes  - Number of sectors to read
//    buffer - pointer to buffer to read the data into.
//                  Must be large enough to hold all of the data
//                  being read.
//
//    pSectorMetadata - pointer to an array of structured (one for each sector)
//                      for the extra sector information.
// 
// Returns:
//   true if successful; false if not
//
// Remarks:
//   This function reads the number of sectors specified from the device.
//   
//   pSectorBuff may be NULL. This is to allow for reading just the metadata.
// 
//   pSectorMetadata can be set to NULL if the caller does not need the extra
//   data.
//
//   If the device does not support sector Metadata it should fail if the 
//   pSectorMetadata parameter is not NULL.
//
bool BlockStorageDevice_Read(BlockStorageDevice* device, unsigned int startAddress, unsigned int numBytes, unsigned char* buffer)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

     return device->m_BSD->Read(device->m_context, startAddress, numBytes, buffer);
}

/////////////////////////////////////////////////////////
// Description:
//    Writes data to a set of sectors
//
// Input:
//    startAddress - Starting Sector for the write
//    numBytes  - Number of sectors to write
//    buffer - pointer to data to write.
//                  Must be large enough to hold complete sectors
//                  for the number of sectors being written.
//
//    pSectorMetadata - pointer to an array of structures (one for each sector)
//                      for the extra sector information.
// 
// Returns:
//   true if successful; false if not
//
// Remarks:
//   This function reads the number of sectors specified from the device.
//   The SectorMetadata is used for flash arrays without special controllers
//   to manage wear leveling etc... (mostly for NOR and NAND). The metadata
//   is used by upper layers to ensure that data is moved around on the flash
//   when writing to prevent failure of the device from too many erase cycles
//   on a sector. 
//   
//   If the device does not support sector Metadata it should fail if the 
//   pSectorMetadata parameter is not NULL.
//
//   pSectorMetadata can be set to NULL if the caller does not need the extra
//   data. Implementations must not attempt to write data through a NULL pointer! 
//
bool BlockStorageDevice_Write(BlockStorageDevice* device, unsigned int startAddress, unsigned int numBytes, unsigned char* buffer, bool readModifyWrite)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

    return device->m_BSD->Write(device->m_context, startAddress, numBytes, buffer, readModifyWrite);
}

bool BlockStorageDevice_Memset(BlockStorageDevice* device, unsigned int startAddress, unsigned char buffer, unsigned int numBytes)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

    return device->m_BSD->Memset(device->m_context, startAddress, buffer, numBytes);
}

// bool BlockStorageDevice_GetSectorMetadata(BlockStorageDevice* device, unsigned int sectorStart, SectorMetadata* pSectorMetadata);
// bool BlockStorageDevice_SetSectorMetadata(BlockStorageDevice* device, unsigned int sectorStart, SectorMetadata* pSectorMetadata);

/////////////////////////////////////////////////////////
// Description:
//    Check a block is erased or not
// 
// Input:
//    Address - Logical Sector Address
//
// Returns:
//   true it is erased; false if not
//
// Remarks:
//    check the block containing the sector address specified.
//  
bool BlockStorageDevice_IsBlockErased(BlockStorageDevice* device, unsigned int blockStartAddress, unsigned int length)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

    return device->m_BSD->IsBlockErased(device->m_context, blockStartAddress, length);
}

/////////////////////////////////////////////////////////
// Description:
//    Erases a block
// 
// Input:
//    Address - Logical Sector Address
//
// Returns:
//   true if successful; false if not
//
// Remarks:
//    Erases the block containing the sector address specified.
//
bool BlockStorageDevice_EraseBlock(BlockStorageDevice* device, unsigned int address)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

    return device->m_BSD->EraseBlock(device->m_context, address);
}

/////////////////////////////////////////////////////////
// Description:
//   Changes the power state of the device
// 
// Input:
//    state   - true= power on; false = power off
//
// Remarks:
//   This function allows systems to conserve power by 
//   shutting down the hardware when the system is 
//   going into low power states.
//
void BlockStorageDevice_SetPowerState(BlockStorageDevice* device, unsigned int state)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

    device->m_BSD->SetPowerState(device->m_context, state);
}

bool BlockStorageDevice_FindRegionFromAddress(BlockStorageDevice* device, unsigned int address, unsigned int* blockRegionIndex, unsigned int* blockRangeIndex)
{
    ASSERT(device != NULL);

    DeviceBlockInfo* deviceInfo = BlockStorageDevice_GetDeviceInfo(device);

    return DeviceBlockInfo_FindRegionFromAddress(deviceInfo, address, blockRegionIndex, blockRangeIndex);
}

bool BlockStorageDevice_FindForBlockUsage(BlockStorageDevice* device, unsigned int blockUsage, unsigned int* address, unsigned int* blockRegionIndex, unsigned int* blockRangeIndex)
{
    ASSERT(device != NULL);

    DeviceBlockInfo* deviceInfo = BlockStorageDevice_GetDeviceInfo(device);

    return DeviceBlockInfo_FindForBlockUsage(deviceInfo, blockUsage, address, blockRegionIndex, blockRangeIndex);
}

bool BlockStorageDevice_FindNextUsageBlock(BlockStorageDevice* device, unsigned int blockUsage, unsigned int* address, unsigned int* blockRegionIndex, unsigned int* blockRangeIndex)
{
    ASSERT(device != NULL);

    DeviceBlockInfo* deviceInfo = BlockStorageDevice_GetDeviceInfo(device);

    return DeviceBlockInfo_FindNextUsageBlock(deviceInfo, blockUsage, address, blockRegionIndex, blockRangeIndex);
}

bool BlockStorageDevice_GetMemoryMappedAddress(BlockStorageDevice* device, unsigned int blockRegionIndex, unsigned int blockRangeIndex, unsigned int* address)
{
    ASSERT(device != NULL);
    ASSERT(device->m_context != NULL);

    return device->m_BSD->GetMemoryMappedAddress(device->m_context, blockRegionIndex, blockRangeIndex, address);
}

///////////////////////////////////////////////////
// BlockStorageList declarations 

// initialize the storage
void BlockStorageList_Initialize()
{
    for(int i = 0; i < TARGET_BLOCKSTORAGE_COUNT; i++)
    {
        g_BlockStorage.DeviceList[i] = NULL;
    }

    g_BlockStorage.DeviceCount = 0;
}

// walk through list of devices and calls Init() function
bool BlockStorageList_InitializeDevices()
{
    // TODO FIXME
    return true;
}

// walk through list of devices and calls UnInit() function
bool BlockStorageList_UnInitializeDevices()
{
    // TODO FIXME
    return true;
}

bool BlockStorageList_AddDevice(BlockStorageDevice* pBSD, IBlockStorageDevice* vtable, void* config, bool init)
{
    bool success = true;

    // find next empty device slot
    for(int i = 0; i < TARGET_BLOCKSTORAGE_COUNT; i++)
    {
        if(g_BlockStorage.DeviceList[i] == NULL)
        {
            // found an empty slot

            // link the driver and context
            pBSD->m_BSD     = vtable;
            pBSD->m_context = config;

            // call initialize device, if requested
            if(init)
            {
                success = BlockStorageDevice_InitializeDevice(pBSD);
            }
          
            // add device to list only init was successful
            if(success)
            {
                // add the BSD
                g_BlockStorage.DeviceList[i] = pBSD;

                g_BlockStorage.DeviceCount++;

                // done here
                return true;
            }
        }
    }

    return false;
}

bool BlockStorageList_RemoveDevice(BlockStorageDevice* pBSD, bool unInit)
{
    // find device
    for(int i = 0; i < TARGET_BLOCKSTORAGE_COUNT; i++)
    {
        if(g_BlockStorage.DeviceList[i] == pBSD)
        {
            // found it

            // call uninitialize device, if requested
            if(unInit)
            {
                BlockStorageDevice_UninitializeDevice(pBSD);
            }
          
            // remove device
            g_BlockStorage.DeviceList[i] = NULL;

            // done here
            return true;
        }
    }

    return false;
}

bool BlockStorageList_FindDeviceForPhysicalAddress(BlockStorageDevice** pBSD, unsigned int physicalAddress, ByteAddress* blockAddress)
{
    *pBSD = NULL;
       
    BlockStorageDevice* block = BlockStorageList_GetFirstDevice();

    // this has to add to make metadataprocessor happy
    if(!block) return true;

    DeviceBlockInfo* pDeviceInfo = BlockStorageDevice_GetDeviceInfo(block);
        
    for(uint32_t i=0; i < pDeviceInfo->NumRegions; i++)
    {
        BlockRegionInfo* pRegion = &pDeviceInfo->Regions[i];
        
        if(pRegion->Start <= physicalAddress && physicalAddress < (pRegion->Start + pRegion->NumBlocks * pRegion->BytesPerBlock))
        {
            *pBSD = block; 

            // get block start address 
            *blockAddress = (ByteAddress)((physicalAddress - pRegion->Start) / pRegion->BytesPerBlock);
            *blockAddress *= pRegion->BytesPerBlock;
            *blockAddress += pRegion->Start;

            return true;
        }
    }

    return false;
}

BlockStorageDevice* BlockStorageList_GetFirstDevice()
{
    for(int i = 0; i < TARGET_BLOCKSTORAGE_COUNT; i++)
    {
        if(g_BlockStorage.DeviceList[i] != NULL)
        {
            return g_BlockStorage.DeviceList[i];
        }
    }

    return NULL;
}

// returns the next device in BlockStorageList
BlockStorageDevice* BlockStorageList_GetNextDevice(BlockStorageDevice* device)
{
	for(int i = 0; i < TARGET_BLOCKSTORAGE_COUNT; i++)
    {
        if(g_BlockStorage.DeviceList[i] == device)
        {
			if((i + 1) < TARGET_BLOCKSTORAGE_COUNT){
				return g_BlockStorage.DeviceList[i + 1];
			}
        }
    }
    return NULL;
}

// // returns number of devices has been declared in the system
unsigned int BlockStorageList_GetNumDevices()
{
    return TARGET_BLOCKSTORAGE_COUNT;
}

/////////////////////////////////////////////////////
