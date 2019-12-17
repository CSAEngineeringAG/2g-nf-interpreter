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
#ifndef _USB_HOST_USB_HOST_INFO_H_
#define _USB_HOST_USB_HOST_INFO_H_

namespace USB
{
    namespace Host
    {
        struct Info
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static bool NativeIsDevicePresent( HRESULT &hr );
            static unsigned short NativeGetVID( HRESULT &hr );
            static unsigned short NativeGetPID( HRESULT &hr );
            static const char* NativeGetSerialNumber( HRESULT &hr );
            static const char* NativeGetManufacturerString( HRESULT &hr );
            static const char* NativeGetProductString( HRESULT &hr );
        };
    }
}
#endif  //_USB_HOST_USB_HOST_INFO_H_
