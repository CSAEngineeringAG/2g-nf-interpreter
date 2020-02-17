
#include "NanoBooterEntry.h"
#include "UpdateFlashConfig.h"
#include <nanoHAL.h>
//#include <nanoHAL_v2.h>

BOOL MicroBooter_Install(HAL_UPDATE_CONFIG updateCfg);

////////////////////////////////////////////////////////////////////////////////
// The WaitForNanoBooterUpload method was designed to allow porting kit partners
// to define how/when tinybooter mode is entered as well as configure default
// timeout values.  
////////////////////////////////////////////////////////////////////////////////
void WaitForNanoBooterUpload()
{
    // check for NMF update
    HAL_UPDATE_CONFIG cfg;

    if(GetUpdateFlashConfig(&cfg))
    {
        MicroBooter_Install(cfg);
        InvalidateUpdateFlashConfig();
        NVIC_SystemReset();     // CPU_Reset();
    }
}
