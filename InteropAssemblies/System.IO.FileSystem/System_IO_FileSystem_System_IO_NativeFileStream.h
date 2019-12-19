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
#ifndef _SYSTEM_IO_FILESYSTEM_SYSTEM_IO_NATIVEFILESTREAM_H_
#define _SYSTEM_IO_FILESYSTEM_SYSTEM_IO_NATIVEFILESTREAM_H_

/////////////////////////////////////////////////////////////////////////////////////////
// !!! KEEP IN SYNC WITH System.IO.FileSystem FileMode.cs (in managed code) !!!        //
/////////////////////////////////////////////////////////////////////////////////////////
enum FileMode
{
    FileMode_CreateNew = 1,
    FileMode_Create = 2,
    FileMode_Open = 3,
    FileMode_OpenOrCreate = 4,
    FileMode_Truncate = 5,
    FileMode_Append = 6
};

namespace System
{
    namespace IO
    {
        struct NativeFileStream
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static void OpenFileNative( CLR_RT_HeapBlock* pMngObj, const char* param0, const char* param1, signed int param2, HRESULT &hr );
            static signed int ReadNative( CLR_RT_HeapBlock* pMngObj, const char* param0, const char* param1, signed __int64 param2, CLR_RT_TypedArray_UINT8 param3, signed int param4, HRESULT &hr );
            static void WriteNative( CLR_RT_HeapBlock* pMngObj, const char* param0, const char* param1, signed __int64 param2, CLR_RT_TypedArray_UINT8 param3, signed int param4, HRESULT &hr );
            static signed __int64 GetLengthNative( CLR_RT_HeapBlock* pMngObj, const char* param0, const char* param1, HRESULT &hr );
        };
    }
}
#endif  //_SYSTEM_IO_FILESYSTEM_SYSTEM_IO_NATIVEFILESTREAM_H_
