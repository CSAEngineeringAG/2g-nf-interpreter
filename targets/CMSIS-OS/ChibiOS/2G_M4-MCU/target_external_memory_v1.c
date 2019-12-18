//
// Copyright (c) 2018 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <ch.h>
#include "hal.h"
#include "fsmc_sram_lld.h"

// ============= External NOR FLASH ============== //

// FSMC Bank 1.1 		0x60000000 - 0x64000000 (64MB)

// NOR FLASH driver configuration
static const SRAMConfig flash_cfg = {
  .bcr = (uint32_t) FSMC_BCR1_WREN |      		// enable write operations
                    FSMC_BCR1_FACCEN |    		// enable flash access
                    FSMC_BCR1_MWID_0 |    		// memory databus width = 16 bit
                    FSMC_BCR1_MTYP_1 |   		// select NOR flash
                    FSMC_BCR1_MBKEN,    		// enable bank
  .btr = (uint32_t) (5  - 0) |					// ADDSET: address setup phase duration 5 HCLK		1???
					(1 << 4) |					// ADDHLD: address hold phase duration 1 HCLK
					(9 << 8) |					// DATAST: data-phase duration 10 HCLK				18???
					(5 << 16)|					// BUSTURN: bus turnaround phase duration 5 HCLK
					(1 << 20),					// CLKDIV: Clock divide ratio for FSMC clk signal
  .bwtr = (uint32_t)(15 << 0)					// ADDSET: address setup phase duration 15 HCLK		default value to make init function happy
};

// =============================================== //



// ================ External RAM ================= //

// FSMC Bank 1.2 		0x64000000 - 0x68000000 (64MB)
// The PSRAM has a size of 64Mb = 8MB

// RAM driver configuration
static const SRAMConfig ram_cfg = {
  .bcr = (uint32_t) 0 |
					FSMC_BCR1_WREN |      		// enable write operations
                    FSMC_BCR1_MWID_0 |    		// memory databus width = 16 bit
                    FSMC_BCR1_MTYP_0 |   		// select PSRAM
                    FSMC_BCR1_MBKEN,    		// enable bank
  .btr = (uint32_t) 0 |
					(3  - 0) |					// ADDSET: address setup phase duration 3 HCLK
					(1 << 4) |					// ADDHLD: address hold phase duration 1 HCLK  (only for synchronous transfers)
					(9 << 8) |					// DATAST: data-phase duration 9 HCLK
					(0 << 16)|					// BUSTURN: bus turnaround phase duration 0 HCLK
					(1 << 20),					// CLKDIV: Clock divide ratio for FSMC clk signal (only for synchronous transfers)
  .bwtr = (uint32_t)(15 << 0)					// ADDSET: address setup phase duration 15 HCLK		default value to make init function happy
};

// =============================================== //

void Target_ExternalMemoryInit()
{
	// external NOR FLASH
	fsmcSramInit();
	fsmcSramStart(&SRAMD1, &flash_cfg);
	// external PSRAM
    //fsmcSramInit();
	fsmcSramStart(&SRAMD2, &ram_cfg);
	
}