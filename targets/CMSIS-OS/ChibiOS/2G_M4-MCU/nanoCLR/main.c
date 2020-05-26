//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <ch.h>
#include <hal.h>
#include <cmsis_os.h>

#include "usbcfg.h"
#include <swo.h>
#include <targetHAL.h>
#include <CLR_Startup_Thread.h>
#include <WireProtocol_ReceiverThread.h>
#include <nanoCLR_Application.h>
#include <nanoPAL_BlockStorage.h>
#include <nanoHAL_v2.h>
#include <targetPAL.h>
#include "usbh/dev/msd.h"
#include <hal_uart_lld.h>
#include <hal_nf_community.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// need to declare the Receiver thread here
osThreadDef(ReceiverThread, osPriorityHigh, 2048, "ReceiverThread");
// declare CLRStartup thread here 
osThreadDef(CLRStartupThread, osPriorityNormal, 4096, "CLRStartupThread"); 

#if HAL_USE_SDC
// declare SD Card working thread here 
osThreadDef(SdCardWorkingThread, osPriorityNormal, 1024, "SDCWT"); 
#endif
#if HAL_USBH_USE_MSD
// declare USB MSD thread here 
osThreadDef(UsbMsdWorkingThread, osPriorityNormal, 1024, "USBMSDWT"); 
#endif

#ifdef USE_M4MCU_V3
static void config_debug_uart() {
	rccEnableUART7(true);
	rccResetUART7();
	UART7->BRR = STM32_PCLK1 / 115200;
	UART7->CR2 = 0;
	UART7->CR3 = 0;
	UART7->CR1 = USART_CR1_UE | USART_CR1_TE;
}

uint32_t GenericPort_Write(int comPortNum, const char* data, size_t size) {
	(void)comPortNum;

	for (size_t i = 0; i < size; i++) {
		while(!(UART7->SR & USART_SR_TXE)) {
			;
		}

		UART7->DR = data[i];
	}

	return size;
}
#endif

static osMutexId softRebootMutexId = NULL;
osMutexId softRebootMutexIdGet(void)
{
	return softRebootMutexId;
}
//  Application entry point.
int main(void) {

  // find out wakeup reason
  if((RTC->ISR & RTC_ISR_ALRAF) == RTC_ISR_ALRAF)
  {
    // standby, match WakeupReason_FromStandby enum
    WakeupReasonStore = 1;
  }
  else if((PWR->CSR & PWR_CSR_WUF) == PWR_CSR_WUF)
  {
    // wake from pin, match WakeupReason_FromPin enum
    WakeupReasonStore = 2;
  }
  else
  {
    // undetermined reason, match WakeupReason_Undetermined enum
    WakeupReasonStore = 0;
  }

  // first things first: need to clear any possible wakeup flags
  // if this is not done here the next standby -> wakeup sequence won't work
  CLEAR_BIT(RTC->CR, RTC_CR_ALRAIE);
  CLEAR_BIT(RTC->ISR, RTC_ISR_ALRAF);
  SET_BIT(PWR->CR, PWR_CR_CWUF);
  
  // Enable Usage fault, Bus fault and Memoryfault in System handler control and state register
  SET_BIT(SCB->SHCSR, SCB_SHCSR_MEMFAULTENA_Msk);
  SET_BIT(SCB->SHCSR, SCB_SHCSR_BUSFAULTENA_Msk);
  SET_BIT(SCB->SHCSR, SCB_SHCSR_USGFAULTENA_Msk);

  // HAL initialization, this also initializes the configured device drivers
  // and performs the board-specific initializations.
  halInit();
  
  // init SWO as soon as possible to make it available to output ASAP
#if (SWO_OUTPUT == TRUE)  
  SwoInit();
#endif

#ifdef USE_M4MCU_V3
  config_debug_uart();
#endif

  // The kernel is initialized but not started yet, this means that
  // main() is executing with absolute priority but interrupts are already enabled.
  osKernelInitialize();

  // start watchdog
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  // for STM32F4 family if watchdog is enabled can't use standby mode because the IWDG can't be stoped //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  Watchdog_Init();

  // config and init external memory
  // this has to be called after osKernelInitialize, otherwise an hard fault will occur
  Target_ExternalMemoryInit();

#if (HAL_NF_USE_STM32_CRC == TRUE)
  // startup crc
  crcStart(NULL);
#endif

  //  Initializes a serial-over-USB CDC driver.
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  // Activates the USB driver and then the USB bus pull-up on D+.
  // Note, a delay is inserted in order to not have to disconnect the cable after a reset
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  // create a mutex to delay communication at soft reboot
  const osMutexDef_t softRebootMutex = {0};
  softRebootMutexId = osMutexCreate(&softRebootMutex);
  osMutexWait(softRebootMutexId, osWaitForever);

  // create the receiver thread
  osThreadCreate(osThread(ReceiverThread), NULL);

  // CLR settings to launch CLR thread
  CLR_SETTINGS clrSettings;
  (void)memset(&clrSettings, 0, sizeof(CLR_SETTINGS));

  clrSettings.MaxContextSwitches         = 50;
  clrSettings.WaitForDebugger            = false;
  clrSettings.EnterDebuggerLoopAfterExit = true;

  // create the CLR Startup thread 
  osThreadCreate(osThread(CLRStartupThread), &clrSettings);
  
  #if HAL_USE_SDC
  // creates the SD card working thread 
  osThreadCreate(osThread(SdCardWorkingThread), NULL);
  #endif

  #if HAL_USBH_USE_MSD
  // create the USB MSD working thread
  osThreadCreate(osThread(UsbMsdWorkingThread), &MSBLKD[0]);
  #endif

  // start kernel, after this main() will behave like a thread with priority osPriorityNormal
  osKernelStart();
  
  // Activate VBUS for USB Host
  palClearPad(GPIOI, GPIOI_VBUSEN);

  int clrLedAnimation = 0;  // Define a given LED Animation for CLR

  while (true) { 
    if(clrLedAnimation == 1)  // Fast LED Animation
    {
      palSetPad(GPIOH, GPIOH_ONBOARD_LED2_ORANGE);
      osDelay(125);
      palClearPad(GPIOH, GPIOH_ONBOARD_LED2_ORANGE);
      osDelay(125);
      palSetPad(GPIOH, GPIOH_ONBOARD_LED2_ORANGE);
      osDelay(125);
      palClearPad(GPIOH, GPIOH_ONBOARD_LED2_ORANGE);
      osDelay(625);
    }
    else if(clrLedAnimation == 2)  // Slow Animation
    {
      palSetPad(GPIOH, GPIOH_ONBOARD_LED2_ORANGE);
      osDelay(500);
      palClearPad(GPIOH, GPIOH_ONBOARD_LED2_ORANGE);
      osDelay(500);
    }
    else    // No Animation
    {
      osDelay(100);
    }
  }
}
