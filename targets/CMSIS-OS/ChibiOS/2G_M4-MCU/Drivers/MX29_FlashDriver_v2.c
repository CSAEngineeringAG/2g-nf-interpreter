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

#include <nanoHAL_v2.h>
#include "MX29_FlashDriver_v2.h"

#define __min(a,b) (((a) < (b)) ? (a) : (b))


bool MX29Driver_ChipInitialize( void* context )
{
	(void) context;
	
    return TRUE;
}


bool MX29Driver_ChipUnInitialize( void* context )
{
	(void) context;
	
    return TRUE;
}


DeviceBlockInfo* MX29Driver_GetDeviceInfo( void* context )
{
	MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = context;
	
    return config->BlockConfig.BlockDeviceInformation;
}


bool MX29Driver_IsBlockErased( void* context, ByteAddress startAddress, unsigned int blockLength )
{	
	(void) context;

    volatile CHIP_WORD * ChipAddress = (volatile CHIP_WORD *) startAddress;

    CHIP_WORD * EndAddress = (CHIP_WORD*)(startAddress + blockLength);
    
    while(ChipAddress < EndAddress)
    {
        if( (*ChipAddress ) != 0xFFFF)
        {
            return FALSE;   
        }
        ChipAddress ++;
    }
    return TRUE;
}

bool MX29Driver_EraseBlock( void* context, ByteAddress address )
{
    bool result;
    CHIP_WORD * ChipAddress;
    
    unsigned int region, range;

    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*)context;
    DeviceBlockInfo *    deviceInfo = config->BlockConfig.BlockDeviceInformation;

    if (deviceInfo->Attribute == MediaAttribute_WriteProtected) return FALSE;
    
    if (!DeviceBlockInfo_FindRegionFromAddress(deviceInfo, address, &region, &range)) return FALSE;
    
    uint32_t blockSize = deviceInfo->Regions[region].BytesPerBlock;

    if (MX29Driver_IsBlockErased(context, address, blockSize)) return TRUE;

    address -= (address % blockSize);

    ChipAddress = (CHIP_WORD *) address;
    
    result =  MX29Driver_Action_EraseSector( context, ChipAddress );

    return result;
}


bool MX29Driver_Read(void* context, ByteAddress startAddress, unsigned int numBytes, unsigned char * buffer)
{
	(void) context;
	if (buffer == NULL) return FALSE;

    CHIP_WORD* ChipAddress = (CHIP_WORD *) startAddress;
    CHIP_WORD* EndAddress  = (CHIP_WORD *)(startAddress + numBytes);
    CHIP_WORD *pBuf = (CHIP_WORD *)buffer;

    while(ChipAddress < EndAddress)
    {
        *pBuf++ = *ChipAddress++;
    }

    return TRUE;
}

bool MX29Driver_Write(void* context, ByteAddress startAddress, unsigned int NumBytes, unsigned char * buffer, bool ReadModifyWrite)
{
    unsigned char * pData;
    unsigned char * pBuf = NULL;
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*)context;
    DeviceBlockInfo * deviceInfo = config->BlockConfig.BlockDeviceInformation;
    
    unsigned int region, range;

    if(ReadModifyWrite) 
    {
        bool fRet = TRUE;
        
        if(!DeviceBlockInfo_FindRegionFromAddress(deviceInfo, startAddress, &region, &range)) return FALSE;
		
		uint32_t 	bytesPerBlock   = deviceInfo->Regions[region].BytesPerBlock;
        uint32_t 	numBlocks		= deviceInfo->Regions[region].NumBlocks;
        uint32_t    regionEnd       = deviceInfo->Regions[region].Start + (numBlocks * bytesPerBlock);
        uint32_t    offset          = startAddress % bytesPerBlock;
        ByteAddress addr            = startAddress;
        ByteAddress addrEnd         = startAddress + NumBytes;
        uint32_t    index           = 0;

        pBuf = (unsigned char*) platform_malloc(bytesPerBlock);

        if(pBuf == NULL) return FALSE;

        while(fRet && addr < addrEnd)
        {
            ByteAddress sectAddr = (addr - offset);
             
            if(offset == 0 && NumBytes >= bytesPerBlock)
            {
                pData = &buffer[index];
            }
            else
            {
                int bytes = __min(bytesPerBlock - offset, NumBytes); 
                
                memcpy( &pBuf[0]     , (void*)sectAddr    , bytesPerBlock );
                memcpy( &pBuf[offset], &buffer[index], 		bytes         );

                pData = pBuf;
            }

            if(!MX29Driver_EraseBlock( context, sectAddr ))
            {
                fRet = FALSE;
                break;
            }

            fRet = MX29Driver_WriteX(context, sectAddr, bytesPerBlock, pData, ReadModifyWrite, TRUE);

            NumBytes -= bytesPerBlock - offset;
            addr     += bytesPerBlock - offset;
            index    += bytesPerBlock - offset;
            offset    = 0;

            if(NumBytes > 0 && addr >= regionEnd)
            {
                region++;

                if(region >= deviceInfo->NumRegions)
                {
                    fRet = FALSE;
                }
                else
                {
                    bytesPerBlock   = deviceInfo->Regions[region].BytesPerBlock;
					numBlocks		= deviceInfo->Regions[region].NumBlocks;
                    regionEnd       = deviceInfo->Regions[region].Start + (numBlocks * bytesPerBlock);

                    platform_free(pBuf);

                    pBuf = (unsigned char *)platform_malloc(bytesPerBlock);

                    if(pBuf == NULL) fRet = FALSE;
                }
            }
                
        }

        if(pBuf != NULL)
        {
            platform_free(pBuf);
        }

        return fRet;            
    }
    else
    {
        return MX29Driver_WriteX(context, startAddress, NumBytes, buffer, ReadModifyWrite, TRUE);
    }
}

bool MX29Driver_Memset(void* context, ByteAddress startAddress, unsigned char data, unsigned int numBytes)
{
    CHIP_WORD chipData;

    memset(&chipData, data, sizeof(CHIP_WORD));

    return MX29Driver_WriteX(context, startAddress, numBytes, (unsigned char*)&chipData, TRUE, FALSE);
}


bool MX29Driver_WriteX(void* context, ByteAddress startAddress, unsigned int numBytes, unsigned char * buffer, bool ReadModifyWrite, bool fIncrementDataPtr)
{
	if(ReadModifyWrite){};

    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*)context;
    const DeviceBlockInfo * deviceInfo = config->BlockConfig.BlockDeviceInformation;
	
    bool result = TRUE;
	
    if (deviceInfo->Attribute == MediaAttribute_WriteProtected) return FALSE;

    CHIP_WORD* ChipAddress = (CHIP_WORD *)startAddress;
    CHIP_WORD* EndAddress  = (CHIP_WORD *)(startAddress + numBytes); 
    CHIP_WORD* pData       = (CHIP_WORD *)buffer;

   
    while(ChipAddress < EndAddress)
    {
       // if same, nothing to do, continue nextword.
       if(*ChipAddress != *pData) 
       {
            // check for having to move bits from 0->1, a failure case for a write
            if(0 != (*pData  & ~(*ChipAddress)))
            {
                debug_printf( "Write X erase failure: 0x%08x=0x%04x\r\n", (size_t)ChipAddress, *ChipAddress );
                ASSERT(0);
                result =FALSE;
                break;
            }

            MX29Driver_Action_WriteWord( config, ChipAddress, *pData );

            
            if (*ChipAddress != *pData)
            {
                debug_printf( "Flash_WriteToSector failure @ 0x%08x, wrote 0x%08x, read 0x%08x\r\n", (uint32_t)ChipAddress, *pData, *ChipAddress );
                result = FALSE;
                break;
            }
        }

        ChipAddress++;
        if(fIncrementDataPtr) pData++;    
    }

    return result;
}

void MX29Driver_SetPowerState(void* context, unsigned int State )
{
	(void)context;
	if(State){};
	
    // our flash driver is always ON
    return ;
}

//--//

bool MX29Driver_Action_EraseSector( void* context, volatile CHIP_WORD* SectorStart )
{
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*)context;
    
    volatile CHIP_WORD* BaseAddress = (CHIP_WORD*)config->BlockConfig.BlockDeviceInformation->Regions[0].Start;

    // Erase command sequence
    BaseAddress[0x0555] = 0x00AA;
    BaseAddress[0x02AA] = 0x0055;
    __ASM("DSB");
    BaseAddress[0x0555] = 0x0080;
    __ASM("DSB");
    BaseAddress[0x0555] = 0x00AA;
    BaseAddress[0x02AA] = 0x0055;
    __ASM("DSB");

    *SectorStart = 0x0030; // start erase
    __ASM("DSB");
    
    // wait for device to signal completion
    while (TRUE) {
        // read twice to asure Q7 cannot be older than Q5
        CHIP_WORD status1 = *SectorStart; // get status for Q5
        CHIP_WORD status2 = *SectorStart; // get status for Q7
        if (status2 & 0x0080) { // done
            return TRUE;
        }
        if (status1 & 0x0020) { // timeout
            BaseAddress[0x0] = 0x00F0; // reset mode
            __ASM("DSB");
            return FALSE;
        }
    }
}

void MX29Driver_Action_WriteWord( void* context, volatile CHIP_WORD* Address, CHIP_WORD Data )
{
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*)context;
    
    volatile CHIP_WORD* BaseAddress = (CHIP_WORD *)config->BlockConfig.BlockDeviceInformation->Regions[0].Start;
     
    // Program command sequence
    BaseAddress[0x0555] = 0x00AA;
    BaseAddress[0x02AA] = 0x0055;
    __ASM("DSB");
    BaseAddress[0x0555] = 0x00A0;
    __ASM("DSB");

    *Address = Data; // start data write
    __ASM("DSB");

    // wait for device to signal completion
    while (TRUE) {
        // read twice to asure Q7 cannot be older than Q5
        CHIP_WORD status1 = *Address; // get status for Q5
        CHIP_WORD status2 = *Address; // get status for Q7
        if ((status2 & 0x0080) == (Data & 0x0080)) { // done
            return;
        }
        if (status1 & 0x0020) { // timeout
            BaseAddress[0x0] = 0x00F0; // reset mode
            __ASM("DSB");
            return;
        }
    }
}