//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <nanoHAL_Types.h>
#include <nanoPAL_BlockStorage.h>


// >>>>>>>>>>>>>>>>>>>>>>>> INTERNAL FLASH <<<<<<<<<<<<<<<<<<<<<<<<<<

// 16kB blocks
const BlockRange STM32F4_BlockRange1[] = 
{
    { BlockRange_BLOCKTYPE_BOOTSTRAP ,   0, 3 },            // 0x08000000 nanoBooter 48k
	
	///////////////////////////////////////////////////////////////////////////////////////
    // because this target is using a configuration block need to add the
    // configuration manager files to the CMake and call ConfigurationManager_Initialize()
    // in nanoBooter so the configuration can be managed when in booter mode
    ///////////////////////////////////////////////////////////////////////////////////////
    { BlockRange_BLOCKTYPE_CONFIG    ,   3, 3 },            // 0x0800C000 configuration block 16kB
    ///////////////////////////////////////////////////////////////////////////////////////
	
    //{ BlockRange_BLOCKTYPE_CODE      ,   3, 3 }             // 0x0800C000 nanoCLR
};

// 64kB blocks
const BlockRange STM32F4_BlockRange2[] = 
{
    { BlockRange_BLOCKTYPE_CODE      ,   0, 0 }             // 0x08010000 nanoCLR
};

// 128kB blocks
const BlockRange STM32F4_BlockRange3[] =
{
    { BlockRange_BLOCKTYPE_CODE      ,   0, 6 },            // 0x08020000 nanoCLR
    //{ BlockRange_BLOCKTYPE_DEPLOYMENT,   3, 6 },            // 0x08080000 deployment
};


const BlockRegionInfo STM32F4_BlockRegions[] = 
{
    {
        (0),                                // no attributes for this region
        0x08000000,                         // start address for block region
        4,                                  // total number of blocks in this region
        0x4000,                             // total number of bytes per block = 16kB
        ARRAYSIZE_CONST_EXPR(STM32F4_BlockRange1),
        STM32F4_BlockRange1,
    },

    {
        (0),                                // no attributes for this region
        0x08010000,                         // start address for block region
        1,                                  // total number of blocks in this region
        0x10000,                            // total number of bytes per block = 64kB
        ARRAYSIZE_CONST_EXPR(STM32F4_BlockRange2),
        STM32F4_BlockRange2,
    },

    {
        (0),                                // no attributes for this region
        0x08020000,                         // start address for block region
        7,                                  // total number of blocks in this region
        0x20000,                            // total number of bytes per block = 128kB
        ARRAYSIZE_CONST_EXPR(STM32F4_BlockRange3),
        STM32F4_BlockRange3,
    }
};

const DeviceBlockInfo STM32F4_Device_BlockInfo =
{
    (MediaAttribute_SupportsXIP),           		// STM32 flash memory is XIP
    2,                                      		// UINT32 BytesPerSector
    ARRAYSIZE_CONST_EXPR(STM32F4_BlockRegions),     // UINT32 NumRegions;
    (BlockRegionInfo*)STM32F4_BlockRegions,         // const BlockRegionInfo* pRegions;
};

MEMORY_MAPPED_NOR_BLOCK_CONFIG STM32F4_Device_BSConfig =
{
    { // BLOCK_CONFIG
        {
            0,          // GPIO_PIN             Pin;
            false,      // BOOL                 ActiveState;
        },

        (DeviceBlockInfo*)&STM32F4_Device_BlockInfo,    // BlockDeviceinfo
    },

    { // CPU_MEMORY_CONFIG
        0,                          // UINT8  CPU_MEMORY_CONFIG::ChipSelect;
        true,                       // UINT8  CPU_MEMORY_CONFIG::ReadOnly;
        0,                          // UINT32 CPU_MEMORY_CONFIG::WaitStates;
        0,                          // UINT32 CPU_MEMORY_CONFIG::ReleaseCounts;
        16,                         // UINT32 CPU_MEMORY_CONFIG::BitWidth;
        0x08000000,                 // UINT32 CPU_MEMORY_CONFIG::BaseAddress;
        0x00100000,                 // UINT32 CPU_MEMORY_CONFIG::SizeInBytes;			STM32F427 has only 1MB of internal Flash!
        0,                          // UINT8  CPU_MEMORY_CONFIG::XREADYEnable 
        0,                          // UINT8  CPU_MEMORY_CONFIG::ByteSignalsForRead 
        0,                          // UINT8  CPU_MEMORY_CONFIG::ExternalBufferEnable
    },

    0,                              // UINT32 ChipProtection;
    0,                              // UINT32 ManufacturerCode;
    0,                              // UINT32 DeviceCode;
};

BlockStorageDevice    STM32F4_BS;

// >>>>>>>>>>>>>>>>>>>>>>>> EXTERNAL FLASH <<<<<<<<<<<<<<<<<<<<<<<<<<

#define MX29_MANUFACTURER_CODE              0x0000  // not used
#define MX29_DEVICE_CODE                    0x0000  // not used
#define MX29_BASE_ADDRESS                   0x60000000
#define MX29_BLOCK_COUNT                    128
#define MX29_BYTES_PER_BLOCK                0x10000
#define MX29_BYTES_PER_SECTOR               2


// EBIU Information
#define MX29__CHIP_SELECT       0
#define MX29__WAIT_STATES       6
#define MX29__RELEASE_COUNTS    0
#define MX29__BIT_WIDTH         16
#define MX29__BASE_ADDRESS      0x60000000
#define MX29__SIZE_IN_BYTES     0x00800000 
#define MX29__WP_GPIO_PIN       0
#define MX29__WP_ACTIVE         false


// BlockDeviceInformation
#define MX29__NUM_REGIONS       1

// 64kB Blocks
const BlockRange MX29_BlockRange[] =
{
    { BlockRange_BLOCKTYPE_DEPLOYMENT,   0,  53 },  // deployment:  3'456 KB
    { BlockRange_BLOCKTYPE_UPDATE,      54, 122 },  // update:      4'416 KB
    { BlockRange_BLOCKTYPE_UPDATE,     123, 123 },  // update flag:    64 KB
    { BlockRange_BLOCKTYPE_FILESYSTEM, 124, 127 }   // filesystem:    256 KB
};


const BlockRegionInfo  MX29_BlockRegions[MX29__NUM_REGIONS] = 
{
    {
		(0),                                // no attributes for this region
        MX29_BASE_ADDRESS,    				// start address for block region
        MX29_BLOCK_COUNT,     				// total number of blocks in this region
        MX29_BYTES_PER_BLOCK, 				// total number of bytes per block = 64kB
        ARRAYSIZE_CONST_EXPR(MX29_BlockRange),
        MX29_BlockRange,
    }
};


const DeviceBlockInfo MX29_Device_BlockInfo=
{
    (MediaAttribute_SupportsXIP),			// STM32 flash memory is XIP
    MX29_BYTES_PER_SECTOR,               	// UINT32 BytesPerSector;     
    MX29__NUM_REGIONS,                    	// UINT32 NumRegions;
    (BlockRegionInfo*)MX29_BlockRegions,    // const BlockRegionInfo* pRegions;
};


MEMORY_MAPPED_NOR_BLOCK_CONFIG MX29_Device_BSConfig =
{
    { // BLOCK_CONFIG
        {
            MX29__WP_GPIO_PIN,            // GPIO_PIN             Pin;
            MX29__WP_ACTIVE,              // BOOL                 ActiveState;
        },

        (DeviceBlockInfo*)&MX29_Device_BlockInfo,               // BlockDeviceinfo
    },

    { // CPU_MEMORY_CONFIG
        MX29__CHIP_SELECT,                // UINT8  CPU_MEMORY_CONFIG::ChipSelect;
        true,                             // UINT8  CPU_MEMORY_CONFIG::ReadOnly;
        MX29__WAIT_STATES,                // UINT32 CPU_MEMORY_CONFIG::WaitStates;
        MX29__RELEASE_COUNTS,             // UINT32 CPU_MEMORY_CONFIG::ReleaseCounts;
        MX29__BIT_WIDTH,                  // UINT32 CPU_MEMORY_CONFIG::BitWidth;
        MX29__BASE_ADDRESS,               // UINT32 CPU_MEMORY_CONFIG::BaseAddress;
        MX29__SIZE_IN_BYTES,              // UINT32 CPU_MEMORY_CONFIG::SizeInBytes;
        0,                                // UINT8  CPU_MEMORY_CONFIG::XREADYEnable 
        0,                                // UINT8  CPU_MEMORY_CONFIG::ByteSignalsForRead 
        0,                                // UINT8  CPU_MEMORY_CONFIG::ExternalBufferEnable
    },

    0,                                    // UINT32 ChipProtection;
    MX29_MANUFACTURER_CODE,              // UINT32 ManufacturerCode;
    MX29_DEVICE_CODE,                    // UINT32 DeviceCode;
};

BlockStorageDevice MX29_BS;