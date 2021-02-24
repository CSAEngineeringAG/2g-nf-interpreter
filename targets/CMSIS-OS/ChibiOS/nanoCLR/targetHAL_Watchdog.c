//
// Copyright (c) 2018 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <ch.h>
#include <hal.h>
#include <targetHAL_Watchdog.h>
#include <target_common.h>

// LSI clock value (series dependent)
#if defined(STM32L0xx_MCUCONF)
#define LSI_CLK_TYPICAL   38000
#elif defined(STM32F0xx_MCUCONF)
#define LSI_CLK_TYPICAL   40000
#elif defined(STM32F4xx_MCUCONF) || defined(STM32F7xx_MCUCONF) || defined(STM32H7xx_MCUCONF)
#define LSI_CLK_TYPICAL   32000
#else
#error "The LSI value for this STM32 series hasn't been defined."
#endif

#if (HAL_USE_WDG)


//Watchdog configuration structure required by ChibiOS
#if (STM32_IWDG_IS_WINDOWED == TRUE)
    static WDGConfig wdgConfig = {STM32_IWDG_PR_256, STM32_IWDG_RL(0xFFF), 0x0FFF}; //default is max
#else
    static WDGConfig wdgConfig = {STM32_IWDG_PR_256, STM32_IWDG_RL(0xFFF)}; //default is max
#endif

static bool m_isWatchdogManaged = FALSE;
static uint32_t m_eResetReason = 0;


static void ReadWatchdogResetReason();

/**
* Method to initialize the watchdog. In ChibiOS, the watchdog sub-system is 
* initialized when halInit() is called. In this method, we perform 
* further specific initializations and also start the watchdog
*/
void Watchdog_Init()
{
	ReadWatchdogResetReason();

    //setup required watchdog timeout...(for IWATCHDOG_TIMEOUT_MILLIS)
    /*
        There are minor variations in STM32 LSI clock across models (e.g STM32F091 has 40KHz LSI
        and STM32F401 has 32 KHz). Also, across the same model, due to manufacturing differences
        the LSI clock has a minimum and maximum range. Therefore, the timeout is always an approximation
        and not exact
    */        
    uint32_t ticksForTimeout=0;

    uint16_t prescaler[] = {STM32_IWDG_PR_4,STM32_IWDG_PR_8,STM32_IWDG_PR_16,
                            STM32_IWDG_PR_32,STM32_IWDG_PR_64,STM32_IWDG_PR_128,
                            STM32_IWDG_PR_256};    

    uint8_t length = (sizeof(prescaler)/sizeof(prescaler[0]));

    uint16_t divisor= 4;

    for(uint8_t index=0; index < length;index++)
    {
        divisor = 4 << prescaler[index];        
        ticksForTimeout = (LSI_CLK_TYPICAL / divisor) * (IWATCHDOG_TIMEOUT_MILLIS/1000) - 1;
        
        if(ticksForTimeout <= 0xFFF) 
        {
            // the max reload register value

            wdgConfig.pr = prescaler[index];
            wdgConfig.rlr = ticksForTimeout;
            break;
        }
    }

    wdgStart(&WDGD1,&wdgConfig);

  #if !defined(BUILD_RTM)
    // these are required to stop the watchdog peripheral when stopping the core
    // useful for debugging without the watchdog triggering
    DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_IWDG_STOP;
    DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_WWDG_STOP;
  #endif
}

/**
 * Reset the watchdog. If not done within the timeout period,
 * the watchdog will trigger and MCU will reset
 */ 
void Watchdog_Reset()
{
	if( FALSE == m_isWatchdogManaged )
	{
		wdgReset(&WDGD1);
	}
}

/**
 * Initializes the watchdog to be controlled by the managed code,
 * this is not reversable due to the usage. We want to choose if the
 * managed code controls the watchdog or the clr.
 */
void Watchdog_Init_From_Managed()
{
	m_isWatchdogManaged = TRUE;
	Watchdog_Reset_From_Managed();
}

/**
 * Reset the watchdog from the managed code. If not done withing
 * the timeout period, the watchdog will trigger and the MCU
 * will reset.
 */
void Watchdog_Reset_From_Managed()
{
	wdgReset(&WDGD1);
}

/**
 * Read the last reset reason from the register and keep in a module variable.
 */
static void ReadWatchdogResetReason()
{
	// check which flag has been set RCC_CSR_PINRSTF
	if(RCC->CSR & RCC_CSR_IWDGRSTF)
	{
		m_eResetReason = WATCHDOG_RESET;
	}
	else if(RCC->CSR & RCC_CSR_SFTRSTF)
	{
		m_eResetReason = SOFT_RESET;
	}
	else // assume everything other than watchdog- or soft-reset can be declared as hard-reset
	{
		m_eResetReason = HARD_RESET;
	}

	// clear last reset reason
	RCC->CSR = RCC->CSR | RCC_CSR_RMVF;
}

/**
 * Gets the last reset reason for the watchdog and passes it to the managed code.
 */
eResetReason_t GetWatchdogResetReason()
{
	return m_eResetReason;
}

#endif
