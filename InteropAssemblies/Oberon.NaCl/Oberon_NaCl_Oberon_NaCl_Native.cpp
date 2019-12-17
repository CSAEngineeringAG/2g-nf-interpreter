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
#include "Oberon_NaCl.h"
#include "Oberon_NaCl_Oberon_NaCl_Native.h"

using namespace Oberon::NaCl;
#include "interop.h"

signed int Native::Crypto_compatibility_check( HRESULT &hr )
{
    (void)hr;
    return ::Crypto_compatibility_check();
}

signed int Native::Crypto_box_compute_keypair( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_box_compute_keypair( 
        param0.GetBuffer(), 
        param1.GetBuffer());
}

signed int Native::Crypto_box( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, CLR_RT_TypedArray_UINT8 param7, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_box( 
        param0.GetBuffer(), 
        param1, 
        param2.GetBuffer(), 
        param3, 
        param4, 
        param5.GetBuffer(), 
        param6.GetBuffer(), 
        param7.GetBuffer());
}

signed int Native::Crypto_box_open( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, CLR_RT_TypedArray_UINT8 param7, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_box_open( 
        param0.GetBuffer(), 
        param1, 
        param2.GetBuffer(), 
        param3, 
        param4, 
        param5.GetBuffer(), 
        param6.GetBuffer(), 
        param7.GetBuffer());
}

signed int Native::Crypto_box_beforenm( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, CLR_RT_TypedArray_UINT8 param2, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_box_beforenm( 
        param0.GetBuffer(), 
        param1.GetBuffer(), 
        param2.GetBuffer());
}

signed int Native::Crypto_box_afternm( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_box_afternm( 
        param0.GetBuffer(), 
        param1, 
        param2.GetBuffer(), 
        param3, 
        param4, 
        param5.GetBuffer(), 
        param6.GetBuffer());
}

signed int Native::Crypto_box_open_afternm( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_box_open_afternm( 
        param0.GetBuffer(), 
        param1, 
        param2.GetBuffer(), 
        param3, 
        param4, 
        param5.GetBuffer(), 
        param6.GetBuffer());
}

signed int Native::Crypto_scalarmult_base( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_scalarmult_base( 
        param0.GetBuffer(), 
        param1.GetBuffer());
}

signed int Native::Crypto_scalarmult( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, CLR_RT_TypedArray_UINT8 param2, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_scalarmult( 
        param0.GetBuffer(), 
        param1.GetBuffer(), 
        param2.GetBuffer());
}

signed int Native::Crypto_sign_compute_keypair( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_sign_compute_keypair( 
        param0.GetBuffer(), 
        param1.GetBuffer());
}

signed int Native::Crypto_sign( CLR_RT_TypedArray_UINT8 param0, signed int param1, unsigned int * param2, CLR_RT_TypedArray_UINT8 param3, signed int param4, signed int param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_sign( 
        param0.GetBuffer(), 
        param1, 
        (uint32_t*)param2, 
        param3.GetBuffer(), 
        param4, 
        param5, 
        param6.GetBuffer());
}

signed int Native::Crypto_sign_open( CLR_RT_TypedArray_UINT8 param0, signed int param1, unsigned int * param2, CLR_RT_TypedArray_UINT8 param3, signed int param4, signed int param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_sign_open( 
        param0.GetBuffer(), 
        param1, 
        (uint32_t*)param2, 
        param3.GetBuffer(), 
        param4, 
        param5, 
        param6.GetBuffer());
}

signed int Native::Crypto_secretbox( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_secretbox( 
        param0.GetBuffer(), 
        param1, 
        param2.GetBuffer(), 
        param3, 
        param4, 
        param5.GetBuffer(), 
        param6.GetBuffer());
}

signed int Native::Crypto_secretbox_open( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_secretbox_open( 
        param0.GetBuffer(), 
        param1, 
        param2.GetBuffer(), 
        param3, 
        param4, 
        param5.GetBuffer(), 
        param6.GetBuffer());
}

signed int Native::Crypto_stream( CLR_RT_TypedArray_UINT8 param0, signed int param1, signed int param2, CLR_RT_TypedArray_UINT8 param3, CLR_RT_TypedArray_UINT8 param4, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_stream( 
        param0.GetBuffer(), 
        param1, 
        param2, 
        param3.GetBuffer(), 
        param4.GetBuffer());
}

signed int Native::Crypto_stream_xor( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, signed int param4, CLR_RT_TypedArray_UINT8 param5, CLR_RT_TypedArray_UINT8 param6, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_stream_xor( 
        param0.GetBuffer(), 
        param1, 
        param2.GetBuffer(), 
        param3, 
        param4, 
        param5.GetBuffer(), 
        param6.GetBuffer());
}

signed int Native::Crypto_onetimeauth( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, signed int param2, signed int param3, CLR_RT_TypedArray_UINT8 param4, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_onetimeauth( 
        param0.GetBuffer(), 
        param1.GetBuffer(), 
        param2, 
        param3, 
        param4.GetBuffer());
}

signed int Native::Crypto_onetimeauth_verify( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, signed int param2, signed int param3, CLR_RT_TypedArray_UINT8 param4, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_onetimeauth_verify( 
        param0.GetBuffer(), 
        param1.GetBuffer(), 
        param2, 
        param3, 
        param4.GetBuffer());
}

signed int Native::Crypto_hash( CLR_RT_TypedArray_UINT8 param0, CLR_RT_TypedArray_UINT8 param1, signed int param2, signed int param3, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_hash( 
        param0.GetBuffer(), 
        param1.GetBuffer(), 
        param2, 
        param3);
}

signed int Native::Crypto_verify_16( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_verify_16( 
        param0.GetBuffer(), 
        param1, 
        param2.GetBuffer(), 
        param3);
}

signed int Native::Crypto_verify_32( CLR_RT_TypedArray_UINT8 param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, signed int param3, HRESULT &hr )
{
	(void)hr;
    return ::Crypto_verify_32( 
        param0.GetBuffer(), 
        param1, 
        param2.GetBuffer(), 
        param3);
}

