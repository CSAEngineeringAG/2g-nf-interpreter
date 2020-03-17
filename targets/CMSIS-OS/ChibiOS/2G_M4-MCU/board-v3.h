/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * Porting for M4-MCU 17.09.2019 mku
 * STATUS: OK
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for STMicroelectronics STM32F429I-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_2G_M4_MCU
#define BOARD_NAME                  "2G M4-MCU"

#define BOARD_OTG_NOVBUSSENS

/*
 * Ethernet PHY type.
 */
#define BOARD_PHY_ID                0x000E7237		//from maxim integrated 78Q2123 Datasheet
#define BOARD_PHY_MII								//maybe not needed (only if Interface = RMII)

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768U			// Oscillator B2 32768 kHz
#endif


#if !defined(STM32_HSECLK)
#define STM32_HSECLK                12000000U		// Oscillator B1 12.000 MHz
#endif




/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F427xx

/*
 * IO pins assignments.
 */
#define GPIOA_PHY_CRS               0U
#define GPIOA_PHY_RXCLK             1U
#define GPIOA_PHY_MDIO				2U
#define GPIOA_PHY_COL               3U
#define GPIOA_PIN4					4U
#define GPIOA_PIN5                  5U
#define GPIOA_PIN6					6U
#define GPIOA_PHY_RXDV              7U
#define GPIOA_TP19					8U
#define GPIOA_UART1_TX              9U
#define GPIOA_UART1_RX              10U
#define GPIOA_OTG_FS_N              11U
#define GPIOA_OTG_FS_P              12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_RS485_DIR             15U

#define GPIOB_PHY_RXD2              0U
#define GPIOB_PHY_RXD3              1U
#define GPIOB_BOOT1                 2U
#define GPIOB_PIN3                  3U
#define GPIOB_PIN4                  4U
#define GPIOB_PIN5					5U
#define GPIOB_MAC_SCL				6U
#define GPIOB_PHY_INTR              7U
#define GPIOB_PHY_TXD3              8U
#define GPIOB_MAC_SDA               9U
#define GPIOB_PHY_RXER              10U
#define GPIOB_PHY_TXEN              11U
#define GPIOB_PHY_TXD0				12U
#define GPIOB_VBUSHOST				13U
#define GPIOB_OTG_HS_N				14U
#define GPIOB_OTG_HS_P				15U

#define GPIOC_FMC_SDNWE             0U
#define GPIOC_PHY_MDC				1U
#define GPIOC_PHY_TXD2				2U
#define GPIOC_PHY_TXCLK             3U
#define GPIOC_PHY_RXD0				4U
#define GPIOC_PHY_RXD1				5U
#define GPIOC_HW_VER1				6U
#define GPIOC_HW_VER2				7U
#define GPIOC_SD_DAT0               8U
#define GPIOC_SD_DAT1				9U
#define GPIOC_SD_DAT2               10U
#define GPIOC_SD_DAT3               11U
#define GPIOC_SD_CLK                12U
#define GPIOC_SD_CARD_DT            13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOD_FMC_D2				0U
#define GPIOD_FMC_D3				1U
#define GPIOD_SD_CMD                2U
#define GPIOD_PIN3					3U
#define GPIOD_FMC_NOE               4U
#define GPIOD_FMC_NWE               5U
#define GPIOD_FMC_WAIT              6U
#define GPIOD_FMC_NE1               7U
#define GPIOD_FMC_D13				8U
#define GPIOD_FMC_D14				9U
#define GPIOD_FMC_D15				10U
#define GPIOD_FMC_A16				11U
#define GPIOD_FMC_A17				12U
#define GPIOD_FMC_A18				13U
#define GPIOD_FMC_D0				14U
#define GPIOD_FMC_D1				15U

#define GPIOE_FMC_NBL0              0U
#define GPIOE_FMC_NBL1              1U
#define GPIOE_FMC_A23				2U
#define GPIOE_FMC_A19				3U
#define GPIOE_FMC_A20				4U
#define GPIOE_FMC_A21				5U
#define GPIOE_FMC_A22				6U
#define GPIOE_FMC_D4				7U
#define GPIOE_FMC_D5				8U
#define GPIOE_FMC_D6				9U
#define GPIOE_FMC_D7				10U
#define GPIOE_FMC_D8				11U
#define GPIOE_FMC_D9				12U
#define GPIOE_FMC_D10				13U
#define GPIOE_FMC_D11				14U
#define GPIOE_FMC_D12				15U

#define GPIOF_FMC_A0				0U
#define GPIOF_FMC_A1				1U
#define GPIOF_FMC_A2				2U
#define GPIOF_FMC_A3				3U
#define GPIOF_FMC_A4				4U
#define GPIOF_FMC_A5				5U
#define GPIOF_PIN6                  6U
#define GPIOF_TEST					7U
#define GPIOF_PIN8					8U
#define GPIOF_PIN9					9U
#define GPIOF_TP23					10U
#define GPIOF_FMC_SDNRAS            11U
#define GPIOF_FMC_A6				12U
#define GPIOF_FMC_A7				13U
#define GPIOF_FMC_A8				14U
#define GPIOF_FMC_A9				15U

#define GPIOG_FMC_A10				0U
#define GPIOG_FMC_A11				1U
#define GPIOG_FMC_A12				2U
#define GPIOG_FMC_A13				3U
#define GPIOG_FMC_A14				4U
#define GPIOG_FMC_A15				5U
#define GPIOG_HW_VER0               6U
#define GPIOG_PIN7					7U
#define GPIOG_FMC_SDCLK             8U
#define GPIOG_PIN9                  9U
#define GPIOG_FLASH_WP              10U
#define GPIOG_PIN11                 11U
#define GPIOG_TP21					12U
#define GPIOG_FMC_A24				13U
#define GPIOG_PHY_TXD1              14U
#define GPIOG_FMC_SDNCAS            15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_FMC_SDCKE0            2U
#define GPIOH_FMC_SDNE0             3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_TP20                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_ONBOARD_SW            9U
#define GPIOH_ONBOARD_LED3_RED      10U
#define GPIOH_ONBOARD_LED2_ORANGE   11U
#define GPIOH_ONBOARD_LED1_GREEN    12U
#define GPIOH_CAN1_TX               13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PWR_STAT              0U
#define GPIOI_VBUSFAULT             1U
#define GPIOI_VBUSEN                2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_CAN1_RX               9U
#define GPIOI_PIN10                 10U
#define GPIOI_TP22					11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_PHY_CRS                PAL_LINE(GPIOA, 0U)
#define LINE_PHY_RXCLK              PAL_LINE(GPIOA, 1U)
#define LINE_PHY_MDIO				PAL_LINE(GPIOA, 2U)
#define LINE_PHY_COL                PAL_LINE(GPIOA, 3U)
#define LINE_PHY_RXDV               PAL_LINE(GPIOA, 7U)
#define LINE_TP19					PAL_LINE(GPIOA, 8U)
#define LINE_UART1_TX               PAL_LINE(GPIOA, 9U)
#define LINE_UART1_RX               PAL_LINE(GPIOA, 10U)
#define LINE_OTG_FS_N               PAL_LINE(GPIOA, 11U)
#define LINE_OTG_FS_P               PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_RS485_DIR              PAL_LINE(GPIOA, 15U)

#define LINE_PHY_RXD2               PAL_LINE(GPIOB, 0U)
#define LINE_PHY_RXD3               PAL_LINE(GPIOB, 1U)
#define LINE_BOOT1                  PAL_LINE(GPIOB, 2U)
#define LINE_MAC_SCL				PAL_LINE(GPIOB, 6U)
#define LINE_PHY_INTR				PAL_LINE(GPIOB, 7U)
#define LINE_PHY_TXD3               PAL_LINE(GPIOB, 8U)
#define LINE_MAC_SDA                PAL_LINE(GPIOB, 9U)
#define LINE_PHY_RXER               PAL_LINE(GPIOB, 10U)
#define LINE_PHY_TXEN               PAL_LINE(GPIOB, 11U)
#define LINE_PHY_TXD0				PAL_LINE(GPIOB, 12U)
#define LINE_VBUSHOST				PAL_LINE(GPIOB, 13U)
#define LINE_OTG_HS_N				PAL_LINE(GPIOB, 14U)
#define LINE_OTG_HS_P				PAL_LINE(GPIOB, 15U)

#define LINE_FMC_SDNWE              PAL_LINE(GPIOC, 0U)
#define LINE_PHY_MDC				PAL_LINE(GPIOC, 1U)
#define LINE_PHY_TXD2				PAL_LINE(GPIOC, 2U)
#define LINE_PHY_TXCLK				PAL_LINE(GPIOC, 3U)
#define LINE_PHY_RXD0				PAL_LINE(GPIOC, 4U)
#define LINE_PHY_RXD1				PAL_LINE(GPIOC, 5U)
#define LINE_HW_VER1				PAL_LINE(GPIOC, 6U)
#define LINE_HW_VER2                PAL_LINE(GPIOC, 7U)
#define LINE_SD_DAT0                PAL_LINE(GPIOC, 8U)
#define LINE_SD_DAT1				PAL_LINE(GPIOC, 9U)
#define LINE_SD_DAT2                PAL_LINE(GPIOC, 10U)
#define LINE_SD_DAT3                PAL_LINE(GPIOC, 11U)
#define LINE_SD_CLK                 PAL_LINE(GPIOC, 12U)
#define LINE_SD_DETECT             	PAL_LINE(GPIOC, 13U)
#define LINE_OSC32_IN               PAL_LINE(GPIOC, 14U)
#define LINE_OSC32_OUT              PAL_LINE(GPIOC, 15U)

#define LINE_FMC_D2					PAL_LINE(GPIOD, 0U)
#define LINE_FMC_D3					PAL_LINE(GPIOD, 1U)
#define LINE_SD_CMD                 PAL_LINE(GPIOD, 2U)
#define LINE_FMC_NOE                PAL_LINE(GPIOD, 4U)
#define LINE_FMC_NWE                PAL_LINE(GPIOD, 5U)
#define LINE_FMC_WAIT               PAL_LINE(GPIOD, 6U)
#define LINE_FMC_NE1                PAL_LINE(GPIOD, 7U)
#define LINE_FMC_D13				PAL_LINE(GPIOD, 8U)
#define LINE_FMC_D14				PAL_LINE(GPIOD, 9U)
#define LINE_FMC_D15				PAL_LINE(GPIOD, 10U)
#define LINE_FMC_A16				PAL_LINE(GPIOD, 11U)
#define LINE_FMC_A17				PAL_LINE(GPIOD, 12U)
#define LINE_FMC_A18				PAL_LINE(GPIOD, 13U)
#define LINE_FMC_D0					PAL_LINE(GPIOD, 14U)
#define LINE_FMC_D1					PAL_LINE(GPIOD, 15U)

#define LINE_FMC_NBL0               PAL_LINE(GPIOE, 0U)
#define LINE_FMC_NBL1               PAL_LINE(GPIOE, 1U)
#define LINE_FMC_A23				PAL_LINE(GPIOE, 2U)
#define LINE_FMC_A19				PAL_LINE(GPIOE, 3U)
#define LINE_FMC_A20				PAL_LINE(GPIOE, 4U)
#define LINE_FMC_A21				PAL_LINE(GPIOE, 5U)
#define LINE_FMC_A22				PAL_LINE(GPIOE, 6U)
#define LINE_FMC_D4					PAL_LINE(GPIOE, 7U)
#define LINE_FMC_D5					PAL_LINE(GPIOE, 8U)
#define LINE_FMC_D6					PAL_LINE(GPIOE, 9U)
#define LINE_FMC_D7					PAL_LINE(GPIOE, 10U)
#define LINE_FMC_D8					PAL_LINE(GPIOE, 11U)
#define LINE_FMC_D9					PAL_LINE(GPIOE, 12U)
#define LINE_FMC_D10				PAL_LINE(GPIOE, 13U)
#define LINE_FMC_D11				PAL_LINE(GPIOE, 14U)
#define LINE_FMC_D12				PAL_LINE(GPIOE, 15U)

#define LINE_FMC_A0					PAL_LINE(GPIOF, 0U)
#define LINE_FMC_A1					PAL_LINE(GPIOF, 1U)
#define LINE_FMC_A2					PAL_LINE(GPIOF, 2U)
#define LINE_FMC_A3					PAL_LINE(GPIOF, 3U)
#define LINE_FMC_A4					PAL_LINE(GPIOF, 4U)
#define LINE_FMC_A5					PAL_LINE(GPIOF, 5U)
#define LINE_TEST					PAL_LINE(GPIOF, 7U)
#define LINE_TP23					PAL_LINE(GPIOF, 10U)
#define LINE_FMC_SDNRAS             PAL_LINE(GPIOF, 11U)
#define LINE_FMC_A6					PAL_LINE(GPIOF, 12U)
#define LINE_FMC_A7					PAL_LINE(GPIOF, 13U)
#define LINE_FMC_A8					PAL_LINE(GPIOF, 14U)
#define LINE_FMC_A9					PAL_LINE(GPIOF, 15U)

#define LINE_FMC_A10				PAL_LINE(GPIOG, 0U)
#define LINE_FMC_A11				PAL_LINE(GPIOG, 1U)
#define LINE_FMC_A12				PAL_LINE(GPIOG, 2U)
#define LINE_FMC_A13				PAL_LINE(GPIOG, 3U)
#define LINE_FMC_A14				PAL_LINE(GPIOG, 4U)
#define LINE_FMC_A15				PAL_LINE(GPIOG, 5U)
#define LINE_HW_VER0                PAL_LINE(GPIOG, 6U)
#define LINE_FMC_SDCLK              PAL_LINE(GPIOG, 8U)
#define LINE_FLASH_WP               PAL_LINE(GPIOG, 10U)
#define LINE_TP21					PAL_LINE(GPIOG, 12U)
#define LINE_FMC_A24				PAL_LINE(GPIOG, 13U)
#define LINE_PHY_TXD1               PAL_LINE(GPIOG, 14U)
#define LINE_FMC_SDNCAS             PAL_LINE(GPIOG, 15U)

#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)
#define LINE_FMC_SDCKE0             PAL_LINE(GPIOH, 2U)
#define LINE_FMC_SDNE0              PAL_LINE(GPIOH, 3U)
#define LINE_TP20					PAL_LINE(GPIOH, 6U)
#define LINE_ONBOARD_SW             PAL_LINE(GPIOH, 9U)
#define LINE_ONBOARD_LED3_RED       PAL_LINE(GPIOH, 10U)
#define LINE_ONBOARD_LED2_ORANGE    PAL_LINE(GPIOH, 11U)
#define LINE_ONBOARD_LED1_GREEN     PAL_LINE(GPIOH, 12U)
#define LINE_CAN1_TX                PAL_LINE(GPIOH, 13U)

#define LINE_PWR_STAT               PAL_LINE(GPIOI, 0U)
#define LINE_VBUSFAULT              PAL_LINE(GPIOI, 1U)
#define LINE_VBUSEN					PAL_LINE(GPIOI, 2U)
#define LINE_CAN1_RX                PAL_LINE(GPIOI, 9U)
#define LINE_TP22					PAL_LINE(GPIOI, 11U)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - PHY_CRS                   (alternate 11).
 * PA1  - PHY_RXCLK                 (alternate 11).
 * PA2  - PHY_MDIO					(alternate 11).
 * PA3  - PHY_COL                   (alternate 11).
 * PA4  - PIN4						(input pullup).
 * PA5  - PIN5                      (input pullup).
 * PA6  - PIN6						(input pullup).
 * PA7  - PHY_RXDV                  (alternate 11).
 * PA8  - TP19						(input pullup).
 * PA9  - UART1_TX                  (alternate 7 pullup).
 * PA10 - UART1_RX                  (alternate 7 pullup).
 * PA11 - OTG_FS_N                  (alternate 10).
 * PA12 - OTG_FS_P                  (alternate 10).
 * PA13 - SWDIO                     (alternate 0 pullup).
 * PA14 - SWCLK                     (alternate 0 pulldown).
 * PA15 - RS485_DIR                 (output pulldown).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ALTERNATE(GPIOA_PHY_CRS) |		\
                                     PIN_MODE_ALTERNATE(GPIOA_PHY_RXCLK) |		\
                                     PIN_MODE_ALTERNATE(GPIOA_PHY_MDIO) |		\
                                     PIN_MODE_ALTERNATE(GPIOA_PHY_COL) |		\
                                     PIN_MODE_INPUT(GPIOA_PIN4) |				\
                                     PIN_MODE_INPUT(GPIOA_PIN5) |				\
                                     PIN_MODE_INPUT(GPIOA_PIN6) |				\
                                     PIN_MODE_ALTERNATE(GPIOA_PHY_RXDV) |       \
                                     PIN_MODE_INPUT(GPIOA_TP19) |				\
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_TX) |		\
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_RX) |		\
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_N) |		\
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_P) |		\
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |			\
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |			\
                                     PIN_MODE_OUTPUT(GPIOA_RS485_DIR))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PHY_CRS) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PHY_RXCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PHY_MDIO) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOA_PHY_COL) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN4) |			\
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN5) |           \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN6) |			\
                                     PIN_OTYPE_PUSHPULL(GPIOA_PHY_RXDV) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TP19) |			\
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_TX) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_RX) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_N) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_P) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |			\
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |			\
                                     PIN_OTYPE_PUSHPULL(GPIOA_RS485_DIR))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_LOW(GPIOA_PHY_CRS) |			\
                                     PIN_OSPEED_HIGH(GPIOA_PHY_RXCLK) |			\
                                     PIN_OSPEED_HIGH(GPIOA_PHY_MDIO) |			\
                                     PIN_OSPEED_HIGH(GPIOA_PHY_COL) |			\
                                     PIN_OSPEED_VERYLOW(GPIOA_PIN4) |			\
                                     PIN_OSPEED_VERYLOW(GPIOA_PIN5) |           \
                                     PIN_OSPEED_VERYLOW(GPIOA_PIN6) |			\
                                     PIN_OSPEED_HIGH(GPIOA_PHY_RXDV) |			\
                                     PIN_OSPEED_VERYLOW(GPIOA_TP19) |			\
                                     PIN_OSPEED_VERYLOW(GPIOA_UART1_TX) |		\
                                     PIN_OSPEED_VERYLOW(GPIOA_UART1_RX) |		\
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_N) |			\
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_P) |			\
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |				\
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |				\
                                     PIN_OSPEED_HIGH(GPIOA_RS485_DIR))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_PHY_CRS) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_PHY_RXCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_PHY_MDIO) |		\
                                     PIN_PUPDR_FLOATING(GPIOA_PHY_COL) |		\
                                     PIN_PUPDR_PULLUP(GPIOA_PIN4) |				\
                                     PIN_PUPDR_PULLUP(GPIOA_PIN5) |				\
                                     PIN_PUPDR_PULLUP(GPIOA_PIN6) |				\
                                     PIN_PUPDR_FLOATING(GPIOA_PHY_RXDV) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_TP19) |				\
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_TX) |			\
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_RX) |			\
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_N) |		\
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_P) |		\
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |			\
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |			\
                                     PIN_PUPDR_PULLDOWN(GPIOA_RS485_DIR))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_PHY_CRS) |				\
                                     PIN_ODR_HIGH(GPIOA_PHY_RXCLK) |			\
                                     PIN_ODR_HIGH(GPIOA_PHY_MDIO) |				\
                                     PIN_ODR_HIGH(GPIOA_PHY_COL) |				\
                                     PIN_ODR_HIGH(GPIOA_PIN4) |					\
                                     PIN_ODR_HIGH(GPIOA_PIN5) |					\
                                     PIN_ODR_HIGH(GPIOA_PIN6) |					\
                                     PIN_ODR_HIGH(GPIOA_PHY_RXDV) |				\
                                     PIN_ODR_HIGH(GPIOA_TP19) |					\
                                     PIN_ODR_HIGH(GPIOA_UART1_TX) |				\
                                     PIN_ODR_HIGH(GPIOA_UART1_RX) |				\
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_N) |				\
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_P) |				\
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |				\
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |				\
                                     PIN_ODR_HIGH(GPIOA_RS485_DIR))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PHY_CRS, 11U) |			\
                                     PIN_AFIO_AF(GPIOA_PHY_RXCLK, 11U) |		\
                                     PIN_AFIO_AF(GPIOA_PHY_MDIO, 11U) |			\
                                     PIN_AFIO_AF(GPIOA_PHY_COL, 11U) |			\
                                     PIN_AFIO_AF(GPIOA_PIN4, 0U) |				\
                                     PIN_AFIO_AF(GPIOA_PIN5, 0U) |				\
                                     PIN_AFIO_AF(GPIOA_PIN6, 0U) |				\
                                     PIN_AFIO_AF(GPIOA_PHY_RXDV, 11U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_TP19, 0U) |				\
                                     PIN_AFIO_AF(GPIOA_UART1_TX, 7U) |			\
                                     PIN_AFIO_AF(GPIOA_UART1_RX, 7U) |			\
                                     PIN_AFIO_AF(GPIOA_OTG_FS_N, 10U) |			\
                                     PIN_AFIO_AF(GPIOA_OTG_FS_P, 10U) |			\
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |				\
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |				\
                                     PIN_AFIO_AF(GPIOA_RS485_DIR, 0U))
#define VAL_GPIOA_BSRRH				(0x0)
#define VAL_GPIOA_BSRRL				(0x0)


/*
 * GPIOB setup:
 *
 * PB0  - PHY_RXD2                  (alternate 11).
 * PB1  - PHY_RXD3                  (alternate 11).
 * PB2  - BOOT1                     (input pullup).
 * PB3  - PIN3                      (input pullup).
 * PB4  - PIN4                      (input pullup).
 * PB5  - PIN5						(input pullup).
 * PB6  - MAC_SCL					(alternate 4 opendrain).
 * PB7  - PHY_INTR                  (input floating).
 * PB8  - PHY_TXD3                  (alternate 11).
 * PB9  - MAC_SDA                   (alternate 4 opendrain).
 * PB10 - PHY_RXER                  (alternate 11).
 * PB11 - PHY_TXEN                  (alternate 11).
 * PB12 - PHY_TXD0                  (alternate 11).
 * PB13 - VBUSHOST					(input floating).
 * PB14 - OTG_HS_N					(alternate 12).
 * PB15 - OTG_HS_P					(alternate 12).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(GPIOB_PHY_RXD2) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_PHY_RXD3) |   \
                                     PIN_MODE_INPUT(GPIOB_BOOT1) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN3) |			\
                                     PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN5) |			\
                                     PIN_MODE_ALTERNATE(GPIOB_MAC_SCL) |	\
                                     PIN_MODE_INPUT(GPIOB_PHY_INTR) |       \
                                     PIN_MODE_ALTERNATE(GPIOB_PHY_TXD3) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_MAC_SDA) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_PHY_RXER) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_PHY_TXEN) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_PHY_TXD0) |	\
                                     PIN_MODE_INPUT(GPIOB_VBUSHOST) |		\
                                     PIN_MODE_ALTERNATE(GPIOB_OTG_HS_N) |	\
                                     PIN_MODE_ALTERNATE(GPIOB_OTG_HS_P))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PHY_RXD2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PHY_RXD3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BOOT1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN5) |		\
                                     PIN_OTYPE_OPENDRAIN(GPIOB_MAC_SCL) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PHY_INTR) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PHY_TXD3) |   \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_MAC_SDA) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PHY_RXER) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PHY_TXEN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PHY_TXD0) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOB_VBUSHOST) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_N) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_P))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_PHY_RXD2) |		\
                                     PIN_OSPEED_HIGH(GPIOB_PHY_RXD3) |		\
                                     PIN_OSPEED_HIGH(GPIOB_BOOT1) |         \
                                     PIN_OSPEED_VERYLOW(GPIOB_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_PIN5) |		\
                                     PIN_OSPEED_HIGH(GPIOB_MAC_SCL) |		\
                                     PIN_OSPEED_HIGH(GPIOB_PHY_INTR) |      \
                                     PIN_OSPEED_HIGH(GPIOB_PHY_TXD3) |		\
                                     PIN_OSPEED_HIGH(GPIOB_MAC_SDA) |		\
                                     PIN_OSPEED_HIGH(GPIOB_PHY_RXER) |		\
                                     PIN_OSPEED_HIGH(GPIOB_PHY_TXEN) |		\
                                     PIN_OSPEED_HIGH(GPIOB_PHY_TXD0) |		\
                                     PIN_OSPEED_VERYLOW(GPIOB_VBUSHOST) |   \
                                     PIN_OSPEED_HIGH(GPIOB_OTG_HS_N) |		\
                                     PIN_OSPEED_HIGH(GPIOB_OTG_HS_P))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_PHY_RXD2) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_PHY_RXD3) |   \
                                     PIN_PUPDR_PULLUP(GPIOB_BOOT1) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN3) |			\
                                     PIN_PUPDR_PULLUP(GPIOB_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN5) |			\
                                     PIN_PUPDR_FLOATING(GPIOB_MAC_SCL) |	\
                                     PIN_PUPDR_FLOATING(GPIOB_PHY_INTR) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_PHY_TXD3) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_MAC_SDA) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_PHY_RXER) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_PHY_TXEN) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_PHY_TXD0) |	\
                                     PIN_PUPDR_FLOATING(GPIOB_VBUSHOST) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_OTG_HS_N) |	\
                                     PIN_PUPDR_FLOATING(GPIOB_OTG_HS_P))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_PHY_RXD2) |			\
                                     PIN_ODR_HIGH(GPIOB_PHY_RXD3) |			\
                                     PIN_ODR_HIGH(GPIOB_BOOT1) |			\
                                     PIN_ODR_HIGH(GPIOB_PIN3) |				\
                                     PIN_ODR_HIGH(GPIOB_PIN4) |				\
                                     PIN_ODR_HIGH(GPIOB_PIN5) |				\
                                     PIN_ODR_HIGH(GPIOB_MAC_SCL) |			\
                                     PIN_ODR_HIGH(GPIOB_PHY_INTR) |         \
                                     PIN_ODR_HIGH(GPIOB_PHY_TXD3) |			\
                                     PIN_ODR_HIGH(GPIOB_MAC_SDA) |			\
                                     PIN_ODR_HIGH(GPIOB_PHY_RXER) |			\
                                     PIN_ODR_HIGH(GPIOB_PHY_TXEN) |			\
                                     PIN_ODR_HIGH(GPIOB_PHY_TXD0) |			\
                                     PIN_ODR_HIGH(GPIOB_VBUSHOST) |			\
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_N) |			\
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_P))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PHY_RXD2, 11U) |     \
                                     PIN_AFIO_AF(GPIOB_PHY_RXD3, 11U) |     \
                                     PIN_AFIO_AF(GPIOB_BOOT1, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN5, 0U) |			\
                                     PIN_AFIO_AF(GPIOB_MAC_SCL, 4U) |		\
                                     PIN_AFIO_AF(GPIOB_PHY_INTR, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PHY_TXD3, 11U) |     \
                                     PIN_AFIO_AF(GPIOB_MAC_SDA, 4U) |       \
                                     PIN_AFIO_AF(GPIOB_PHY_RXER, 11U) |     \
                                     PIN_AFIO_AF(GPIOB_PHY_TXEN, 11U) |     \
                                     PIN_AFIO_AF(GPIOB_PHY_TXD0, 11U) |		\
                                     PIN_AFIO_AF(GPIOB_VBUSHOST, 0U) |		\
                                     PIN_AFIO_AF(GPIOB_OTG_HS_N, 12U) |		\
                                     PIN_AFIO_AF(GPIOB_OTG_HS_P, 12U))
#define	VAL_GPIOB_BSRRH				(0x0)
#define VAL_GPIOB_BSRRL				(0x0)


/*
 * GPIOC setup:
 *
 * PC0  - FMC_SDNWE                 (alternate 12).
 * PC1  - PHY_MDC					(alternate 11).
 * PC2  - PHY_TXD2					(alternate 11).
 * PC3  - PHY_TXCLK                 (alternate 11).
 * PC4  - PHY_RXD0					(alternate 11).
 * PC5  - PHY_RXD1					(alternate 11).
 * PC6  - HW_VER1					(input floating).
 * PC7  - HW_VER2                   (input floating).
 * PC8  - SD_DAT0                   (alternate 12).
 * PC9  - SD_DAT1					(alternate 12).
 * PC10 - SD_DAT2                   (alternate 12).
 * PC11 - SD_DAT3                   (alternate 12).
 * PC12 - SD_CLK                    (alternate 12).
 * PC13 - SD_CARD_DT                (input floating).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (input floating).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ALTERNATE(GPIOC_FMC_SDNWE) |  \
                                     PIN_MODE_ALTERNATE(GPIOC_PHY_MDC) |	\
                                     PIN_MODE_ALTERNATE(GPIOC_PHY_TXD2) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_PHY_TXCLK) |  \
                                     PIN_MODE_ALTERNATE(GPIOC_PHY_RXD0) |	\
                                     PIN_MODE_ALTERNATE(GPIOC_PHY_RXD1) |   \
                                     PIN_MODE_INPUT(GPIOC_HW_VER1) |		\
                                     PIN_MODE_INPUT(GPIOC_HW_VER2) |		\
                                     PIN_MODE_ALTERNATE(GPIOC_SD_DAT0) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_DAT1) |	\
                                     PIN_MODE_ALTERNATE(GPIOC_SD_DAT2) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_DAT3) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_CLK) |     \
                                     PIN_MODE_INPUT(GPIOC_SD_CARD_DT) |     \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_FMC_SDNWE) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PHY_MDC) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOC_PHY_TXD2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PHY_TXCLK) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PHY_RXD0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PHY_RXD1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_HW_VER1) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOC_HW_VER2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_DAT0) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_DAT1) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_DAT2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_DAT3) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_CLK) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_CARD_DT) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_FMC_SDNWE) |		\
                                     PIN_OSPEED_HIGH(GPIOC_PHY_MDC) |		\
                                     PIN_OSPEED_HIGH(GPIOC_PHY_TXD2) |		\
                                     PIN_OSPEED_HIGH(GPIOC_PHY_TXCLK) |     \
                                     PIN_OSPEED_HIGH(GPIOC_PHY_RXD0) |		\
                                     PIN_OSPEED_HIGH(GPIOC_PHY_RXD1) |      \
                                     PIN_OSPEED_LOW(GPIOC_HW_VER1) |		\
                                     PIN_OSPEED_LOW(GPIOC_HW_VER2) |		\
                                     PIN_OSPEED_HIGH(GPIOC_SD_DAT0) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SD_DAT1) |		\
                                     PIN_OSPEED_HIGH(GPIOC_SD_DAT2) |		\
                                     PIN_OSPEED_HIGH(GPIOC_SD_DAT3) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SD_CLK) |        \
                                     PIN_OSPEED_HIGH(GPIOC_SD_CARD_DT) |    \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_IN) |      \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_FMC_SDNWE) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_PHY_MDC) |	\
                                     PIN_PUPDR_FLOATING(GPIOC_PHY_TXD2) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_PHY_TXCLK) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_PHY_RXD0) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_PHY_RXD1) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_HW_VER1) |	\
                                     PIN_PUPDR_FLOATING(GPIOC_HW_VER2) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_DAT0) |	\
                                     PIN_PUPDR_FLOATING(GPIOC_SD_DAT1) |	\
                                     PIN_PUPDR_FLOATING(GPIOC_SD_DAT2) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_DAT3) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_CLK) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_CARD_DT) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_FMC_SDNWE) |		\
                                     PIN_ODR_HIGH(GPIOC_PHY_MDC) |			\
                                     PIN_ODR_HIGH(GPIOC_PHY_TXD2) |			\
                                     PIN_ODR_HIGH(GPIOC_PHY_TXCLK) |		\
                                     PIN_ODR_HIGH(GPIOC_PHY_RXD0) |			\
                                     PIN_ODR_HIGH(GPIOC_PHY_RXD1) |			\
                                     PIN_ODR_HIGH(GPIOC_HW_VER1) |			\
                                     PIN_ODR_HIGH(GPIOC_HW_VER2) |			\
                                     PIN_ODR_HIGH(GPIOC_SD_DAT0) |          \
                                     PIN_ODR_HIGH(GPIOC_SD_DAT1) |			\
                                     PIN_ODR_HIGH(GPIOC_SD_DAT2) |			\
                                     PIN_ODR_HIGH(GPIOC_SD_DAT3) |          \
                                     PIN_ODR_HIGH(GPIOC_SD_CLK) |			\
                                     PIN_ODR_HIGH(GPIOC_SD_CARD_DT) |       \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |			\
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_FMC_SDNWE, 12U) |    \
                                     PIN_AFIO_AF(GPIOC_PHY_MDC, 11U) |		\
                                     PIN_AFIO_AF(GPIOC_PHY_TXD2, 11U) |		\
                                     PIN_AFIO_AF(GPIOC_PHY_TXCLK, 11U) |    \
                                     PIN_AFIO_AF(GPIOC_PHY_RXD0, 11U) |		\
                                     PIN_AFIO_AF(GPIOC_PHY_RXD1, 11U) |     \
                                     PIN_AFIO_AF(GPIOC_HW_VER1, 0U) |		\
                                     PIN_AFIO_AF(GPIOC_HW_VER2, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SD_DAT0, 12U) |      \
                                     PIN_AFIO_AF(GPIOC_SD_DAT1, 12U) |      \
                                     PIN_AFIO_AF(GPIOC_SD_DAT2, 12U) |      \
                                     PIN_AFIO_AF(GPIOC_SD_DAT3, 12U) |      \
                                     PIN_AFIO_AF(GPIOC_SD_CLK, 12U) |       \
                                     PIN_AFIO_AF(GPIOC_SD_CARD_DT, 0U) |    \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))
#define VAL_GPIOC_BSRRH				(0x0)
#define VAL_GPIOC_BSRRL				(0x0)


/*
 * GPIOD setup:
 *
 * PD0  - FMC_D2					(alternate 12).
 * PD1  - FMC_D3					(alternate 12).
 * PD2  - SD_CMD                    (alternate 12).
 * PD3  - PIN3						(input pullup).
 * PD4  - FMC_NOE                   (alternate 12).
 * PD5  - FMC_NWE                   (alternate 12).
 * PD6  - FMC_WAIT                  (alternate 12).  // input??
 * PD7  - FMC_NE1                   (alternate 12).
 * PD8  - FMC_D13					(alternate 12).
 * PD9  - FMC_D14					(alternate 12).
 * PD10 - FMC_D15					(alternate 12).
 * PD11 - FMC_A16					(alternate 12).
 * PD12 - FMC_A17					(alternate 12).
 * PD13 - FMC_A18					(alternate 12).
 * PD14 - FMC_D0					(alternate 12).
 * PD15 - FMC_D1					(alternate 12).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_ALTERNATE(GPIOD_FMC_D2) |		\
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D3) |		\
                                     PIN_MODE_ALTERNATE(GPIOD_SD_CMD) |     \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |			\
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NOE) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NWE) |    \
                                     PIN_MODE_INPUT(GPIOD_FMC_WAIT) |   	\
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NE1) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D13) |	\
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D14) |	\
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D15) |	\
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_A16) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_A17) |	\
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_A18) |	\
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D0) |		\
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D1))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_FMC_D2) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D3) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOD_SD_CMD) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NOE) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NWE) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_WAIT) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NE1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D13) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D14) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D15) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_A16) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_A17) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_A18) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D0) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D1))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_FMC_D2) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D3) |		\
                                     PIN_OSPEED_HIGH(GPIOD_SD_CMD) |        \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN3) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NOE) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NWE) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_WAIT) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NE1) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D13) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D14) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D15) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_A16) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_A17) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_A18) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D0) |		\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_FMC_D2) |		\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D3) |		\
                                     PIN_PUPDR_FLOATING(GPIOD_SD_CMD) |     \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |			\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NOE) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NWE) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_WAIT) |   \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NE1) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D13) |	\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D14) |	\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D15) |	\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_A16) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_A17) |	\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_A18) |	\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D0) |		\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D1))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_FMC_D2) |			\
                                     PIN_ODR_HIGH(GPIOD_FMC_D3) |			\
                                     PIN_ODR_HIGH(GPIOD_SD_CMD) |           \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |				\
                                     PIN_ODR_HIGH(GPIOD_FMC_NOE) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_NWE) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_WAIT) |			\
                                     PIN_ODR_HIGH(GPIOD_FMC_NE1) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D13) |			\
                                     PIN_ODR_HIGH(GPIOD_FMC_D14) |			\
                                     PIN_ODR_HIGH(GPIOD_FMC_D15) |			\
                                     PIN_ODR_HIGH(GPIOD_FMC_A16) |			\
                                     PIN_ODR_HIGH(GPIOD_FMC_A17) |			\
                                     PIN_ODR_HIGH(GPIOD_FMC_A18) |			\
                                     PIN_ODR_HIGH(GPIOD_FMC_D0) |			\
                                     PIN_ODR_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_FMC_D2, 12U) |		\
                                     PIN_AFIO_AF(GPIOD_FMC_D3, 12U) |		\
                                     PIN_AFIO_AF(GPIOD_SD_CMD, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |			\
                                     PIN_AFIO_AF(GPIOD_FMC_NOE, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_NWE, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_WAIT, 12U) |     \
                                     PIN_AFIO_AF(GPIOD_FMC_NE1, 12U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_FMC_D13, 12U) |		\
                                     PIN_AFIO_AF(GPIOD_FMC_D14, 12U) |		\
                                     PIN_AFIO_AF(GPIOD_FMC_D15, 12U) |		\
                                     PIN_AFIO_AF(GPIOD_FMC_A16, 12U) |		\
                                     PIN_AFIO_AF(GPIOD_FMC_A17, 12U) |		\
                                     PIN_AFIO_AF(GPIOD_FMC_A18, 12U) |		\
                                     PIN_AFIO_AF(GPIOD_FMC_D0, 12U) |		\
                                     PIN_AFIO_AF(GPIOD_FMC_D1, 12U))
#define	VAL_GPIOD_BSRRH				(0x0)
#define VAL_GPIOD_BSRRL				(0x0)


/*
 * GPIOE setup:
 *
 * PE0  - FMC_NBL0                  (alternate 12).
 * PE1  - FMC_NBL1                  (alternate 12).
 * PE2  - FMC_A23					(alternate 12).
 * PE3  - FMC_A19					(alternate 12).
 * PE4  - FMC_A20					(alternate 12).
 * PE5  - FMC_A21					(alternate 12).
 * PE6  - FMC_A22					(alternate 12).
 * PE7  - FMC_D4					(alternate 12).
 * PE8  - FMC_D5					(alternate 12).
 * PE9  - FMC_D6					(alternate 12).
 * PE10 - FMC_D7					(alternate 12).
 * PE11 - FMC_D8					(alternate 12).
 * PE12 - FMC_D9					(alternate 12).
 * PE13 - FMC_D10					(alternate 12).
 * PE14 - FMC_D11					(alternate 12).
 * PE15 - FMC_D12					(alternate 12).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ALTERNATE(GPIOE_FMC_NBL0) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_NBL1) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_A23) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_A19) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_A20) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_A21) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_A22) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D4) |		\
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D5) |		\
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D6) |		\
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D7) |		\
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D8) |		\
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D9) |		\
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D10) |	\
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D11) |	\
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D12))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_A23) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_A19) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_A20) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_A21) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_A22) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D4) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D5) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D6) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D7) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D8) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D9) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D10) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D11) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D12))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_FMC_NBL0) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_NBL1) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_A23) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_A19) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_A20) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_A21) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_A22) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D4) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D5) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D6) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D7) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D8) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D9) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D10) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D11) |		\
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_FMC_NBL0) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_NBL1) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_A23) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_A19) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_A20) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_A21) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_A22) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D4) |		\
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D5) |		\
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D6) |		\
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D7) |		\
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D8) |		\
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D9) |		\
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D10) |	\
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D11) |	\
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D12))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_FMC_NBL0) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_NBL1) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_A23) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_A19) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_A20) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_A21) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_A22) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_D4) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_D5) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_D6) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_D7) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_D8) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_D9) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_D10) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_D11) |			\
                                     PIN_ODR_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_FMC_NBL0, 12U) |     \
                                     PIN_AFIO_AF(GPIOE_FMC_NBL1, 12U) |     \
                                     PIN_AFIO_AF(GPIOE_FMC_A23, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_A19, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_A20, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_A21, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_A22, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_D4, 12U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_FMC_D5, 12U) |		\
                                     PIN_AFIO_AF(GPIOE_FMC_D6, 12U) |		\
                                     PIN_AFIO_AF(GPIOE_FMC_D7, 12U) |		\
                                     PIN_AFIO_AF(GPIOE_FMC_D8, 12U) |		\
                                     PIN_AFIO_AF(GPIOE_FMC_D9, 12U) |		\
                                     PIN_AFIO_AF(GPIOE_FMC_D10, 12U) |		\
                                     PIN_AFIO_AF(GPIOE_FMC_D11, 12U) |		\
                                     PIN_AFIO_AF(GPIOE_FMC_D12, 12U))
#define VAL_GPIOE_BSRRH				(0x0)
#define VAL_GPIOE_BSRRL				(0x0)


/*
 * GPIOF setup:
 *
 * PF0  - FMC_A0					(alternate 12).
 * PF1  - FMC_A1					(alternate 12).
 * PF2  - FMC_A2					(alternate 12).
 * PF3  - FMC_A3					(alternate 12).
 * PF4  - FMC_A4					(alternate 12).
 * PF5  - FMC_A5					(alternate 12).
 * PF6  - PIN6                      (input pullup).
 * PF7  - TEST						(input floating).
 * PF8  - PIN8						(input pullup).
 * PF9  - PIN9						(input pullup).
 * PF10 - TP23						(input pullup).
 * PF11 - FMC_SDNRAS                (alternate 12).
 * PF12 - FMC_A6					(alternate 12).
 * PF13 - FMC_A7					(alternate 12).
 * PF14 - FMC_A8					(alternate 12).
 * PF15 - FMC_A9					(alternate 12).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_ALTERNATE(GPIOF_FMC_A0) |		\
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A1) |		\
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A2) |		\
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A3) |		\
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A4) |		\
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A5) |		\
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_ALTERNATE(GPIOF_TEST) |			\
                                     PIN_MODE_INPUT(GPIOF_PIN8) |			\
                                     PIN_MODE_INPUT(GPIOF_PIN9) |			\
                                     PIN_MODE_INPUT(GPIOF_TP23) |			\
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_SDNRAS) | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A6) |		\
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A7) |		\
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A8) |		\
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A9))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_FMC_A0) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A1) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A2) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A3) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A4) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A5) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_TEST) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_TP23) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_SDNRAS) | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A6) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A7) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A8) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A9))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_FMC_A0) |		\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A1) |		\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A2) |		\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A3) |		\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A4) |		\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A5) |		\
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN6) |       \
                                     PIN_OSPEED_HIGH(GPIOF_TEST) |			\
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN8) |		\
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN9) |		\
                                     PIN_OSPEED_VERYLOW(GPIOF_TP23) |		\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_SDNRAS) |	\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A6) |		\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A7) |		\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A8) |		\
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_FMC_A0) |		\
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A1) |		\
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A2) |		\
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A3) |		\
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A4) |		\
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A5) |		\
                                     PIN_PUPDR_PULLUP(GPIOF_PIN6) |         \
                                     PIN_PUPDR_FLOATING(GPIOF_TEST) |		\
                                     PIN_PUPDR_PULLUP(GPIOF_PIN8) |			\
                                     PIN_PUPDR_PULLUP(GPIOF_PIN9) |			\
                                     PIN_PUPDR_PULLUP(GPIOF_TP23) |			\
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_SDNRAS) | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A6) |		\
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A7) |		\
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A8) |		\
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A9))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_FMC_A0) |			\
                                     PIN_ODR_HIGH(GPIOF_FMC_A1) |			\
                                     PIN_ODR_HIGH(GPIOF_FMC_A2) |			\
                                     PIN_ODR_HIGH(GPIOF_FMC_A3) |			\
                                     PIN_ODR_HIGH(GPIOF_FMC_A4) |			\
                                     PIN_ODR_HIGH(GPIOF_FMC_A5) |			\
                                     PIN_ODR_HIGH(GPIOF_PIN6) |				\
                                     PIN_ODR_HIGH(GPIOF_TEST) |				\
                                     PIN_ODR_HIGH(GPIOF_PIN8) |				\
                                     PIN_ODR_HIGH(GPIOF_PIN9) |				\
                                     PIN_ODR_HIGH(GPIOF_TP23) |				\
                                     PIN_ODR_HIGH(GPIOF_FMC_SDNRAS) |		\
                                     PIN_ODR_HIGH(GPIOF_FMC_A6) |			\
                                     PIN_ODR_HIGH(GPIOF_FMC_A7) |			\
                                     PIN_ODR_HIGH(GPIOF_FMC_A8) |			\
                                     PIN_ODR_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_FMC_A0, 12U) |		\
                                     PIN_AFIO_AF(GPIOF_FMC_A1, 12U) |		\
                                     PIN_AFIO_AF(GPIOF_FMC_A2, 12U) |		\
                                     PIN_AFIO_AF(GPIOF_FMC_A3, 12U) |		\
                                     PIN_AFIO_AF(GPIOF_FMC_A4, 12U) |		\
                                     PIN_AFIO_AF(GPIOF_FMC_A5, 12U) |		\
                                     PIN_AFIO_AF(GPIOF_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_TEST, 8U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0U) |			\
                                     PIN_AFIO_AF(GPIOF_PIN9, 0U) |			\
                                     PIN_AFIO_AF(GPIOF_TP23, 0U) |			\
                                     PIN_AFIO_AF(GPIOF_FMC_SDNRAS, 12U) |   \
                                     PIN_AFIO_AF(GPIOF_FMC_A6, 12U) |		\
                                     PIN_AFIO_AF(GPIOF_FMC_A7, 12U) |		\
                                     PIN_AFIO_AF(GPIOF_FMC_A8, 12U) |		\
                                     PIN_AFIO_AF(GPIOF_FMC_A9, 12U))
#define VAL_GPIOF_BSRRH				(0x0)
#define VAL_GPIOF_BSRRL				(0x0)


/*
 * GPIOG setup:
 *
 * PG0  - FMC_A10					(alternate 12).
 * PG1  - FMC_A11					(alternate 12).
 * PG2  - FMC_A12					(alternate 12).
 * PG3  - FMC_A13					(alternate 12).
 * PG4  - FMC_A14					(alternate 12).
 * PG5  - FMC_A15					(alternate 12).
 * PG6  - HW_VER0                   (input floating).
 * PG7  - PIN7						(input pullup).
 * PG8  - FMC_SDCLK                 (alternate 12).
 * PG9  - PIN9                      (input pullup).
 * PG10 - FLASH_WP					(output floating).		--> set to 1
 * PG11 - PIN11						(input pullup).
 * PG12 - TP21						(input pullup).
 * PG13 - FMC_A24					(alternate 12).
 * PG14 - PHY_TXD1                  (alternate 11).
 * PG15 - FMC_SDNCAS                (alternate 12).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_ALTERNATE(GPIOG_FMC_A10) |	\
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A11) |	\
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A12) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A13) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A14) |	\
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A15) |	\
                                     PIN_MODE_INPUT(GPIOG_HW_VER0) |		\
                                     PIN_MODE_INPUT(GPIOG_PIN7) |			\
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_SDCLK) |  \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_OUTPUT(GPIOG_FLASH_WP) |		\
                                     PIN_MODE_INPUT(GPIOG_PIN11) |			\
                                     PIN_MODE_INPUT(GPIOG_TP21) |			\
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A24) |	\
                                     PIN_MODE_ALTERNATE(GPIOG_PHY_TXD1) |   \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_FMC_A10) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A11) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A12) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A14) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A15) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOG_HW_VER0) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_SDCLK) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FLASH_WP) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOG_TP21) |		\
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A24) |	\
                                     PIN_OTYPE_PUSHPULL(GPIOG_PHY_TXD1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_FMC_A10) |		\
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A11) |		\
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A12) |		\
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A13) |		\
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A14) |		\
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A15) |		\
                                     PIN_OSPEED_LOW(GPIOG_HW_VER0) |		\
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN7) |		\
                                     PIN_OSPEED_HIGH(GPIOG_FMC_SDCLK) |		\
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN9) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FLASH_WP) |		\
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN11) |		\
                                     PIN_OSPEED_VERYLOW(GPIOG_TP21) |		\
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A24) |		\
                                     PIN_OSPEED_HIGH(GPIOG_PHY_TXD1) |		\
                                     PIN_OSPEED_HIGH(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_FMC_A10) |	\
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A11) |	\
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A12) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A13) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A14) |	\
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A15) |	\
                                     PIN_PUPDR_FLOATING(GPIOG_HW_VER0) |	\
                                     PIN_PUPDR_PULLUP(GPIOG_PIN7) |			\
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_SDCLK) |  \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOG_FLASH_WP) |	\
                                     PIN_PUPDR_PULLUP(GPIOG_PIN11) |		\
                                     PIN_PUPDR_PULLUP(GPIOG_TP21) |			\
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A24) |	\
                                     PIN_PUPDR_FLOATING(GPIOG_PHY_TXD1) |   \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_FMC_A10) |			\
                                     PIN_ODR_HIGH(GPIOG_FMC_A11) |			\
                                     PIN_ODR_HIGH(GPIOG_FMC_A12) |			\
                                     PIN_ODR_HIGH(GPIOG_FMC_A13) |			\
                                     PIN_ODR_HIGH(GPIOG_FMC_A14) |			\
                                     PIN_ODR_HIGH(GPIOG_FMC_A15) |			\
                                     PIN_ODR_HIGH(GPIOG_HW_VER0) |			\
                                     PIN_ODR_HIGH(GPIOG_PIN7) |				\
                                     PIN_ODR_HIGH(GPIOG_FMC_SDCLK) |		\
                                     PIN_ODR_HIGH(GPIOG_PIN9) |				\
                                     PIN_ODR_HIGH(GPIOG_FLASH_WP) |			\
                                     PIN_ODR_HIGH(GPIOG_PIN11) |			\
                                     PIN_ODR_HIGH(GPIOG_TP21) |				\
                                     PIN_ODR_HIGH(GPIOG_FMC_A24) |			\
                                     PIN_ODR_HIGH(GPIOG_PHY_TXD1) |			\
                                     PIN_ODR_HIGH(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_FMC_A10, 12U) |		\
                                     PIN_AFIO_AF(GPIOG_FMC_A11, 12U) |		\
                                     PIN_AFIO_AF(GPIOG_FMC_A12, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A13, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A14, 12U) |		\
                                     PIN_AFIO_AF(GPIOG_FMC_A15, 12U) |		\
                                     PIN_AFIO_AF(GPIOG_HW_VER0, 0U) |       \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_FMC_SDCLK, 12U) |    \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_FLASH_WP, 0U) |      \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0U) |			\
                                     PIN_AFIO_AF(GPIOG_TP21, 0U) |			\
                                     PIN_AFIO_AF(GPIOG_FMC_A24, 12U) |		\
                                     PIN_AFIO_AF(GPIOG_PHY_TXD1, 11U) |     \
                                     PIN_AFIO_AF(GPIOG_FMC_SDNCAS, 12U))
#define VAL_GPIOG_BSRRH				(0x0)
#define VAL_GPIOG_BSRRL				(0x0400)


/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - FMC_SDCKE0                (alternate 12).
 * PH3  - FMC_SDNE0                 (alternate 12).
 * PH4  - PIN4                      (input pullup).
 * PH5  - PIN5                      (input pullup).
 * PH6  - TP20                      (input pullup).
 * PH7  - PIN7                      (input pullup).
 * PH8  - PIN8                      (input pullup).
 * PH9  - ONBOARD_SW                (input floating).
 * PH10 - ONBOARD_LED3_RED          (output floating).
 * PH11 - ONBOARD_LED2_ORANGE       (output floating).
 * PH12 - ONBOARD_LED1_GREEN        (output floating).
 * PH13 - CAN1_TX                   (alternate 9).
 * PH14 - PIN14                     (input pullup).
 * PH15 - PIN15                     (input pullup).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |					\
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |				\
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_SDCKE0) |         \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_SDNE0) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |					\
                                     PIN_MODE_INPUT(GPIOH_PIN5) |					\
                                     PIN_MODE_INPUT(GPIOH_TP20) |					\
                                     PIN_MODE_INPUT(GPIOH_PIN7) |					\
                                     PIN_MODE_INPUT(GPIOH_PIN8) |					\
                                     PIN_MODE_INPUT(GPIOH_ONBOARD_SW) |				\
                                     PIN_MODE_OUTPUT(GPIOH_ONBOARD_LED3_RED) |      \
                                     PIN_MODE_OUTPUT(GPIOH_ONBOARD_LED2_ORANGE) |	\
                                     PIN_MODE_OUTPUT(GPIOH_ONBOARD_LED1_GREEN) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_CAN1_TX) |			\
                                     PIN_MODE_INPUT(GPIOH_PIN14) |					\
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |				\
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |			\
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_SDCKE0) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_SDNE0) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |				\
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |				\
                                     PIN_OTYPE_PUSHPULL(GPIOH_TP20) |				\
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |				\
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |				\
                                     PIN_OTYPE_PUSHPULL(GPIOH_ONBOARD_SW) |			\
                                     PIN_OTYPE_PUSHPULL(GPIOH_ONBOARD_LED3_RED) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_ONBOARD_LED2_ORANGE) |\
                                     PIN_OTYPE_PUSHPULL(GPIOH_ONBOARD_LED1_GREEN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_CAN1_TX) |			\
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |				\
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |				\
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |				\
                                     PIN_OSPEED_HIGH(GPIOH_FMC_SDCKE0) |			\
                                     PIN_OSPEED_HIGH(GPIOH_FMC_SDNE0) |				\
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN4) |				\
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN5) |				\
                                     PIN_OSPEED_VERYLOW(GPIOH_TP20) |				\
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN7) |				\
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN8) |				\
                                     PIN_OSPEED_VERYLOW(GPIOH_ONBOARD_SW) |			\
                                     PIN_OSPEED_HIGH(GPIOH_ONBOARD_LED3_RED) |      \
                                     PIN_OSPEED_HIGH(GPIOH_ONBOARD_LED2_ORANGE) |	\
                                     PIN_OSPEED_HIGH(GPIOH_ONBOARD_LED1_GREEN) |    \
                                     PIN_OSPEED_HIGH(GPIOH_CAN1_TX) |				\
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN14) |				\
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |				\
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |			\
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_SDCKE0) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_SDNE0) |          \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN4) |					\
                                     PIN_PUPDR_PULLUP(GPIOH_PIN5) |					\
                                     PIN_PUPDR_PULLUP(GPIOH_TP20) |					\
                                     PIN_PUPDR_PULLUP(GPIOH_PIN7) |					\
                                     PIN_PUPDR_PULLUP(GPIOH_PIN8) |					\
                                     PIN_PUPDR_FLOATING(GPIOH_ONBOARD_SW) |			\
                                     PIN_PUPDR_FLOATING(GPIOH_ONBOARD_LED3_RED) |   \
                                     PIN_PUPDR_FLOATING(GPIOH_ONBOARD_LED2_ORANGE) |\
                                     PIN_PUPDR_FLOATING(GPIOH_ONBOARD_LED1_GREEN) | \
                                     PIN_PUPDR_PULLUP(GPIOH_CAN1_TX) |				\
                                     PIN_PUPDR_PULLUP(GPIOH_PIN14) |				\
                                     PIN_PUPDR_PULLUP(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |					\
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |					\
                                     PIN_ODR_HIGH(GPIOH_FMC_SDCKE0) |				\
                                     PIN_ODR_HIGH(GPIOH_FMC_SDNE0) |				\
                                     PIN_ODR_HIGH(GPIOH_PIN4) |						\
                                     PIN_ODR_HIGH(GPIOH_PIN5) |						\
                                     PIN_ODR_HIGH(GPIOH_TP20) |						\
                                     PIN_ODR_HIGH(GPIOH_PIN7) |						\
                                     PIN_ODR_HIGH(GPIOH_PIN8) |						\
                                     PIN_ODR_HIGH(GPIOH_ONBOARD_SW) |				\
                                     PIN_ODR_LOW(GPIOH_ONBOARD_LED3_RED) |			\
                                     PIN_ODR_LOW(GPIOH_ONBOARD_LED2_ORANGE) |		\
                                     PIN_ODR_LOW(GPIOH_ONBOARD_LED1_GREEN) |		\
                                     PIN_ODR_HIGH(GPIOH_CAN1_TX) |					\
                                     PIN_ODR_HIGH(GPIOH_PIN14) |					\
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |				\
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |				\
                                     PIN_AFIO_AF(GPIOH_FMC_SDCKE0, 12U) |			\
                                     PIN_AFIO_AF(GPIOH_FMC_SDNE0, 12U) |			\
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |					\
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |					\
                                     PIN_AFIO_AF(GPIOH_TP20, 0U) |					\
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |					\
                                     PIN_AFIO_AF(GPIOH_ONBOARD_SW, 0U) |			\
                                     PIN_AFIO_AF(GPIOH_ONBOARD_LED3_RED, 0U) |      \
                                     PIN_AFIO_AF(GPIOH_ONBOARD_LED2_ORANGE, 0U) |   \
                                     PIN_AFIO_AF(GPIOH_ONBOARD_LED1_GREEN, 0U) |    \
                                     PIN_AFIO_AF(GPIOH_CAN1_TX, 9U) |				\
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |					\
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))
#define VAL_GPIOH_BSRRH				(0x0)
#define VAL_GPIOH_BSRRL				(0x0)
/*
 * GPIOI setup:
 *
 * PI0  - PWR_STAT					(input floating).
 * PI1  - VBUSFAULT                 (input floating).
 * PI2  - VBUSEN                    (output floating).
 * PI3  - PIN3                      (input pullup).
 * PI4  - PIN4                      (input pullup).
 * PI5  - PIN5                      (input pullup).
 * PI6  - PIN6                      (input pullup).
 * PI7  - PIN7                      (input pullup).
 * PI8  - PIN8                      (input pullup).
 * PI9  - CAN1_RX                   (alternate 9 pullup).
 * PI10 - PIN10                     (input pullup).
 * PI11 - TP22						(input pullup).
 * PI12 - PIN12                     (input pullup).
 * PI13 - PIN13                     (input pullup).
 * PI14 - PIN14                     (input pullup).
 * PI15 - PIN15                     (input pullup).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PWR_STAT) |		\
                                     PIN_MODE_INPUT(GPIOI_VBUSFAULT) |      \
                                     PIN_MODE_OUTPUT(GPIOI_VBUSEN) |        \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_ALTERNATE(GPIOI_CAN1_RX) |    \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_TP22) |			\
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PWR_STAT) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOI_VBUSFAULT) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOI_VBUSEN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_CAN1_RX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_TP22) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_LOW(GPIOI_PWR_STAT) |       \
                                     PIN_OSPEED_HIGH(GPIOI_VBUSFAULT) |     \
                                     PIN_OSPEED_HIGH(GPIOI_VBUSEN) |        \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN8) |       \
                                     PIN_OSPEED_HIGH(GPIOI_CAN1_RX) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_TP22) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_FLOATING(GPIOI_PWR_STAT) |   \
                                     PIN_PUPDR_FLOATING(GPIOI_VBUSFAULT) |  \
                                     PIN_PUPDR_FLOATING(GPIOI_VBUSEN) |     \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_CAN1_RX) |      \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_TP22) |			\
                                     PIN_PUPDR_PULLUP(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PWR_STAT) |         \
                                     PIN_ODR_HIGH(GPIOI_VBUSFAULT) |        \
                                     PIN_ODR_HIGH(GPIOI_VBUSEN) |           \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_CAN1_RX) |          \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_TP22) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PWR_STAT, 0U) |      \
                                     PIN_AFIO_AF(GPIOI_VBUSFAULT, 0U) |     \
                                     PIN_AFIO_AF(GPIOI_VBUSEN, 0U) |        \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_CAN1_RX, 9U) |       \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_TP22, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))
#define VAL_GPIOI_BSRRH				(0x0)
#define VAL_GPIOI_BSRRL				(0x0)


/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
