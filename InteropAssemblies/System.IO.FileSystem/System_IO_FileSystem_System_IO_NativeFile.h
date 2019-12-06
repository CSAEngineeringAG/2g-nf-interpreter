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
#ifndef _SYSTEM_IO_FILESYSTEM_SYSTEM_IO_NATIVEFILE_H_
#define _SYSTEM_IO_FILESYSTEM_SYSTEM_IO_NATIVEFILE_H_

namespace System
{
    namespace IO
    {
        struct NativeFile
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static bool ExistsNative( const char* param0, const char* param1, HRESULT &hr );
            static void MoveNative( const char* param0, const char* param1, HRESULT &hr );
            static void DeleteNative( const char* param0, HRESULT &hr );
            static unsigned char GetAttributesNative( const char* param0, HRESULT &hr );
            static void SetAttributesNative( const char* param0, unsigned char param1, HRESULT &hr );
        };
    }
}
#endif  //_SYSTEM_IO_FILESYSTEM_SYSTEM_IO_NATIVEFILE_H_
