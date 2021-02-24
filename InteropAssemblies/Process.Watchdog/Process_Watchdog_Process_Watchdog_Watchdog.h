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

#ifndef _PROCESS_WATCHDOG_PROCESS_WATCHDOG_PROCESS_WATCHDOG_WATCHDOG_H_
#define _PROCESS_WATCHDOG_PROCESS_WATCHDOG_PROCESS_WATCHDOG_WATCHDOG_H_

namespace Process_Watchdog
{
    namespace Process_Watchdog
    {
        struct Watchdog
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers

            static void WatchdogManagedInitNative(  HRESULT &hr );

            static void WatchdogManagedResetNative(  HRESULT &hr );

            static unsigned int GetWatchdogResetReasonNative(  HRESULT &hr );

        };
    }
}

#endif //_PROCESS_WATCHDOG_PROCESS_WATCHDOG_PROCESS_WATCHDOG_WATCHDOG_H_
