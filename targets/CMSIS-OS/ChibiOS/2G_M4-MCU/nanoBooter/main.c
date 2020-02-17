//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//
// Porting for M4-MCU 17.09.10 mku 
// STATUS: 
//

#include <ch.h>
#include <hal.h>
#include <cmsis_os.h>

#include <usbcfg.h>
#include <swo.h>
#include <targetHAL.h>
#include <WireProtocol_ReceiverThread.h>
#include <nanoPAL_BlockStorage.h>
#include <LaunchCLR.h>
#include <NanoBooterEntry.h>

// need to declare the Receiver thread here
osThreadDef(ReceiverThread, osPriorityHigh, 2048, "ReceiverThread");

//  Application entry point.
int main(void) {

  // HAL initialization, this also initializes the configured device drivers
  // and performs the board-specific initializations.
  halInit();

  // init SWO as soon as possible to make it available to output ASAP
  #if (SWO_OUTPUT == TRUE)  
  SwoInit();
  #endif

  // The kernel is initialized but not started yet, this means that
  // main() is executing with absolute priority but interrupts are already enabled.
  osKernelInitialize();
  osDelay(20);    // Let init stabilize

  // the following IF is not mandatory, it's just providing a way for a user to 'force'
  // the board to remain in nanoBooter and not launching nanoCLR

  // config and init external memory
  // this has to be called after osKernelInitialize, otherwise an hard fault will occur
  Target_ExternalMemoryInit();
  // initialize block storage list and devices
  // in CLR this is called in nanoHAL_Initialize()
  // for nanoBooter we have to init it in order to provide the flash map for Monitor_FlashSectorMap command
  BlockStorageList_Initialize();
  BlockStorage_AddDevices();

  // if the USER button (blue one) is pressed, skip the check for a valid CLR image and remain in booter
  // the user button in this board has a pull-up resistor so the check has to be inverted
  if (!palReadPad(GPIOH, GPIOH_ONBOARD_SW))
  {
    // Check for Update
    palSetPad(GPIOH, GPIOH_ONBOARD_LED1_GREEN);
    palSetPad(GPIOH, GPIOH_ONBOARD_LED3_RED);

    WaitForNanoBooterUpload();

    palClearPad(GPIOH, GPIOH_ONBOARD_LED1_GREEN);
    palClearPad(GPIOH, GPIOH_ONBOARD_LED3_RED);

    // check for valid CLR image 
    // this target has a configuration block and a NETMF compatibility block.
    // this target DOES NOT have configuration block, so we need to use the __nanoImage_end__ address here
    if(CheckValidCLRImage((uint32_t)(&__netmfBlock_end__)))
    {
      // there seems to be a valid CLR image
      // launch nanoCLR
      LaunchCLR((uint32_t)(&__netmfBlock_end__));
    }
  }

  //  Initializes a serial-over-USB CDC driver.
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  // Activates the USB driver and then the USB bus pull-up on D+.
  // Note, a delay is inserted in order to not have to disconnect the cable after a reset.
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  // create the receiver thread
  osThreadCreate(osThread(ReceiverThread), NULL);

  // start kernel, after this main() will behave like a thread with priority osPriorityNormal
  osKernelStart();

  // initialize configuration manager
  // in CLR this is called in nanoHAL_Initialize()
  // for nanoBooter we have to init it here to have access to network configuration blocks
  ConfigurationManager_Initialize();

  //  Normal main() thread
  while (true) {
      palSetPad(GPIOH, GPIOH_ONBOARD_LED1_GREEN);
      osDelay(250);
      palClearPad(GPIOH, GPIOH_ONBOARD_LED1_GREEN);
      osDelay(250);
  }
}
