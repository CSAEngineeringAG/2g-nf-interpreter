//
// Copyright (c) 2018 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//
// Porting for M4-MCU 12.09.19 mku
// STATUS: OK
//

#include <hal.h>
#include "target_nf_devices_can_config.h"
#include <nf_devices_can_native_target.h>

///////////
// CAN1 //
///////////

// pin configuration for CAN1
// port for TX pin is: GPIOH
// TX pin: is GPIOH_13
// port for RX pin is: GPIOI
// RX pin: is GPIOI_09
// GPIO alternate pin function is 9 (see "Table 12. STM32F427xx and STM32F429xx alternate function mapping" in STM32F427xx/STM32F429xx datasheet)
CAN_CONFIG_PINS(1, GPIOH, GPIOI, 13, 9, 9)

// buffer
CANRxFrame Can1_MsgBuffer[CAN1_RX_BUFFER_SIZE];

// initialization for CAN1
CAN_INIT(1, CAN1_RX_BUFFER_SIZE)
