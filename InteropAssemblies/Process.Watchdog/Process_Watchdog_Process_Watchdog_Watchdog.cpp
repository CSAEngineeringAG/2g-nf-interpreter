//-----------------------------------------------------------------------------
//
//                   ** WARNING! ** 
//    This file was generated automatically by a tool.
//    Re-running the tool will overwrite this file.
//    You should copy this file to a custom location
//    before adding any customization in the copy to
//    prevent loss of your changes when the tool is
//    re-run.
//
//-----------------------------------------------------------------------------

#include "Process_Watchdog.h"
#include "Process_Watchdog_Process_Watchdog_Watchdog.h"

using namespace Process_Watchdog::Process_Watchdog;


void Watchdog::WatchdogManagedInitNative(  HRESULT &hr )
{
    (void)hr;
	
    Watchdog_Init_From_Managed();
}

void Watchdog::WatchdogManagedResetNative(  HRESULT &hr )
{
    (void)hr;

	Watchdog_Reset_From_Managed();
}

unsigned int Watchdog::GetWatchdogResetReasonNative(  HRESULT &hr )
{
    (void)hr;

    return (int)GetWatchdogResetReason();
}
