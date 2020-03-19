//-----------------------------------------------------------------------------
//
//    ** DO NOT EDIT THIS FILE! **
//    This file was generated by a tool
//    re-running the tool will overwrite this file.
//
//-----------------------------------------------------------------------------


#include "System_IO_FileSystem.h"
#include "System_IO_FileSystem_System_IO_NativeFileStream.h"

using namespace System::IO;


HRESULT Library_System_IO_FileSystem_System_IO_NativeFileStream::OpenFileNative___VOID__STRING__STRING__I4( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        const char* param0;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_LPCSTR( stack, 1, param0 ) );

        const char* param1;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_LPCSTR( stack, 2, param1 ) );

        signed int param2;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 3, param2 ) );

        NativeFileStream::OpenFileNative( pMngObj,  param0, param1, param2, hr );
        NANOCLR_CHECK_HRESULT( hr );
    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_System_IO_FileSystem_System_IO_NativeFileStream::ReadNative___I4__STRING__STRING__I8__SZARRAY_U1__I4( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        const char* param0;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_LPCSTR( stack, 1, param0 ) );

        const char* param1;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_LPCSTR( stack, 2, param1 ) );

        signed __int64 param2;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_INT64( stack, 3, param2 ) );

        CLR_RT_TypedArray_UINT8 param3;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 4, param3 ) );

        signed int param4;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 5, param4 ) );

        signed int retVal = NativeFileStream::ReadNative( pMngObj,  param0, param1, param2, param3, param4, hr );
        NANOCLR_CHECK_HRESULT( hr );
        SetResult_INT32( stack, retVal );

    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_System_IO_FileSystem_System_IO_NativeFileStream::WriteNative___VOID__STRING__STRING__I8__SZARRAY_U1__I4( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        const char* param0;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_LPCSTR( stack, 1, param0 ) );

        const char* param1;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_LPCSTR( stack, 2, param1 ) );

        signed __int64 param2;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_INT64( stack, 3, param2 ) );

        CLR_RT_TypedArray_UINT8 param3;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 4, param3 ) );

        signed int param4;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 5, param4 ) );

        NativeFileStream::WriteNative( pMngObj,  param0, param1, param2, param3, param4, hr );
        NANOCLR_CHECK_HRESULT( hr );
    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_System_IO_FileSystem_System_IO_NativeFileStream::GetLengthNative___I8__STRING__STRING( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        const char* param0;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_LPCSTR( stack, 1, param0 ) );

        const char* param1;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_LPCSTR( stack, 2, param1 ) );

        signed __int64 retVal = NativeFileStream::GetLengthNative( pMngObj,  param0, param1, hr );
        NANOCLR_CHECK_HRESULT( hr );
        SetResult_INT64( stack, retVal );

    }
    NANOCLR_NOCLEANUP();
}