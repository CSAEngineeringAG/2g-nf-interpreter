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
#ifndef _OBERON_NACL_OBERON_NACL_NATIVE_H_
#define _OBERON_NACL_OBERON_NACL_NATIVE_H_

namespace Oberon
{
    namespace NaCl
    {
        struct Native
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static signed int Crypto_compatibility_check( HRESULT &hr );
            static signed int Crypto_box_compute_keypair( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr );
            static signed int Crypto_box( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, CLR_RT_TypedArray_UINT8 param7, HRESULT &hr );
            static signed int Crypto_box_open( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, CLR_RT_TypedArray_UINT8 param7, HRESULT &hr );
            static signed int Crypto_box_beforenm( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, CLR_RT_TypedArray_UINT8 param2, HRESULT &hr );
            static signed int Crypto_box_afternm( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr );
            static signed int Crypto_box_open_afternm( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr );
            static signed int Crypto_scalarmult_base( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr );
            static signed int Crypto_scalarmult( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, CLR_RT_TypedArray_UINT8 param2, HRESULT &hr );
            static signed int Crypto_sign_compute_keypair( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr );
            static signed int Crypto_sign( CLR_RT_TypedArray_UINT8 param0, signed int param1, unsigned int * param2, CLR_RT_TypedArray_UINT8 param3, signed int param4, signed int param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr );
            static signed int Crypto_sign_open( CLR_RT_TypedArray_UINT8 param0, signed int param1, unsigned int * param2, CLR_RT_TypedArray_UINT8 param3, signed int param4, signed int param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr );
            static signed int Crypto_secretbox( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr );
            static signed int Crypto_secretbox_open( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr );
            static signed int Crypto_stream( CLR_RT_TypedArray_UINT8 param0, signed int param1, signed int param2, CLR_RT_TypedArray_UINT8 param3, CLR_RT_TypedArray_UINT8 param4, HRESULT &hr );
            static signed int Crypto_stream_xor( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr );
            static signed int Crypto_onetimeauth( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, signed int param2, signed int param3, CLR_RT_TypedArray_UINT8 param4, HRESULT &hr );
            static signed int Crypto_onetimeauth_verify( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, signed int param2, signed int param3, CLR_RT_TypedArray_UINT8 param4, HRESULT &hr );
            static signed int Crypto_hash( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, signed int param2, signed int param3, HRESULT &hr );
            static signed int Crypto_verify_16( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, HRESULT &hr );
            static signed int Crypto_verify_32( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, HRESULT &hr );
        };
    }
}
#endif  //_OBERON_NACL_OBERON_NACL_NATIVE_H_
