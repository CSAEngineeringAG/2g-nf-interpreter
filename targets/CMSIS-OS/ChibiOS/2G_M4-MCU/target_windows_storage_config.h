//
// Copyright (c) 2018 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//
// Porting for M4-MCU 17.09.10 mku 
// STATUS: OK
//

// maps the SD Card driver
#define SD_CARD_DRIVER      SDCD1

// maps the SD Card detect GPIO definition (in Target_Windows_Storage.c) to board GPIO line (in board.h)
#define SDCARD_LINE_DETECT  LINE_SD_DETECT

// includes SPIFFS in storage
#define USE_SPIFFS_FOR_STORAGE  FALSE

// maps the USB mass storage device driver
#define USB_MSD_DRIVER		USBHD2
