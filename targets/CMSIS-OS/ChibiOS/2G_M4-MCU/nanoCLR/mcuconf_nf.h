//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _MCUCONF_NF_H_
#define _MCUCONF_NF_H_


/*
 * FSMC driver system settings.
 */
#define STM32_FSMC_USE_FSMC1                TRUE
#define STM32_FSMC_FSMC1_IRQ_PRIORITY       10
#define STM32_FSMC_DMA_CHN                  0x03010201

// +++++++++++++++++++++ FSMC settings for M4MCUv3 +++++++++++++++++++++
#ifdef USE_M4MCU_V3
/*
 * FSMC SDRAM driver system settings.
 */
#define STM32_USE_FSMC_SDRAM                TRUE
#define STM32_SDRAM_USE_FSMC_SDRAM1         TRUE
#define STM32_SDRAM_USE_FSMC_SDRAM2         FALSE

/*
 * FSMC NOR FLASH driver system settings.
 */
#define STM32_USE_FSMC_SRAM                	TRUE
#define STM32_SRAM_USE_FSMC_SRAM1         	TRUE
#define STM32_SRAM_USE_FSMC_SRAM2         	FALSE
#define STM32_SRAM_USE_FSMC_SRAM3         	FALSE
#define STM32_SRAM_USE_FSMC_SRAM4         	FALSE

#else
// +++++++++++++++++++++ FSMC settings for M4MCUv1 +++++++++++++++++++++
/*
 * FSMC SDRAM driver system settings.
 */
#define STM32_USE_FSMC_SDRAM                FALSE
#define STM32_SDRAM_USE_FSMC_SDRAM1         FALSE
#define STM32_SDRAM_USE_FSMC_SDRAM2         FALSE

/*
 * FSMC NOR Flash and PSRAM driver system settings.
 */
#define STM32_USE_FSMC_SRAM                	TRUE
#define STM32_SRAM_USE_FSMC_SRAM1         	TRUE
#define STM32_SRAM_USE_FSMC_SRAM2         	TRUE
#define STM32_SRAM_USE_FSMC_SRAM3         	FALSE
#define STM32_SRAM_USE_FSMC_SRAM4         	FALSE

#endif

#endif // _MCUCONF_NF_H_

