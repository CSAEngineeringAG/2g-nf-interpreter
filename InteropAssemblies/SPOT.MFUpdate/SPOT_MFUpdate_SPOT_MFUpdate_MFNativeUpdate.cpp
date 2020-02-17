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
#include "SPOT_MFUpdate.h"
#include "SPOT_MFUpdate_SPOT_MFUpdate_MFNativeUpdate.h"
#include <MFUpdate_decl.h>

using namespace SPOT::MFUpdate;

void MFNativeUpdate::_cctor( HRESULT &hr )
{
    (void)hr;

    MFUpdate_Initialize();
}

signed int MFNativeUpdate::Initialize( unsigned int param0, unsigned int param1, unsigned int param2, unsigned short param3, unsigned short param4, signed int param5, signed int param6, signed int param7, signed int param8, const char* param9, HRESULT &hr )
{
    (void)hr;
    // param9 ^= szProvider

    CLR_INT32 retVal = 0; 

    MFUpdateHeader header;

    // Set UpdateHeader Properties
    header.PacketSize = param0;
    header.UpdateID = param1;
    header.UpdateSize  = param2;
    header.UpdateType = param3;
    header.UpdateSubType = param4;

    header.Version.usMajor = (unsigned short) param5;
    header.Version.usMinor = (unsigned short) param6;
    header.Version.usBuild = (unsigned short) param7;
    header.Version.usRevision = (unsigned short) param8;

    retVal = MFUpdate_InitUpdate(param9, header);

    return retVal;
}

bool MFNativeUpdate::Authenticate( signed int param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
    (void)hr;
    // param0 ^= handle
    // param1 ^= AuthenticationData (param1) for the moment always given as null

    bool retVal = 0; 

    CLR_UINT8* pAuthData;
    CLR_INT32 authLen;

    if(param1.GetBuffer() == NULL)
    {
        pAuthData = NULL;
        authLen = 0;
    }
    else
    {
        pAuthData = param1.GetBuffer();
        authLen = param1.GetSize();
    }

    retVal = MFUpdate_Authenticate(param0, pAuthData, authLen);

    return retVal;
}

bool MFNativeUpdate::Open( signed int param0, HRESULT &hr )
{
    (void)hr;
    // param0 ^= handle

    bool retVal = 0; 

    retVal = MFUpdate_Open(param0);

    return retVal;
}

bool MFNativeUpdate::Create( signed int param0, HRESULT &hr )
{
    (void)hr;
    // param0 ^= handle

    bool retVal = 0;

    retVal = MFUpdate_Create(param0);

    return retVal;
}

void MFNativeUpdate::GetMissingPackets( signed int param0, CLR_RT_TypedArray_UINT32 param1, HRESULT &hr )
{
    (void)hr;
    // param0 ^= handle
    // param1 ^= packetBitCheck

    CLR_INT32 pktCount;

    FAULT_ON_NULL(param1.GetBuffer());

    pktCount = param1.GetSize();

    if(!MFUpdate_GetMissingPackets(param0, (UINT32*)param1.GetBuffer(), &pktCount))
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_FAIL);
    }

    NANOCLR_CLEANUP();
}

bool MFNativeUpdate::AddPacket( signed int param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, CLR_RT_TypedArray_UINT8 param3, HRESULT &hr )
{
    (void)hr;
    // param0 ^= handle
    // param1 ^= pktIndex
    // param2 ^= pPacket
    // param3 ^= pValidation

    bool retVal = 0;

    CLR_UINT8* pValidData;
    CLR_INT32 validLen;

    FAULT_ON_NULL(param2.GetBuffer());

    if(param3.GetBuffer() == NULL)
    {
        pValidData = NULL;
        validLen = 0;
    }
    else
    {
        pValidData = param3.GetBuffer();
        validLen = param3.GetSize();
    }

    retVal = MFUpdate_AddPacket(param0, param1, param2.GetBuffer(), param2.GetSize(), pValidData, validLen);

    NANOCLR_CLEANUP();

    return retVal;
}

bool MFNativeUpdate::Validate( signed int param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
    (void)hr;
    // param0 ^= handle
    // param1 ^= pValidation

    bool retVal = 0;

    CLR_UINT8*              pValidData;
    CLR_INT32               validLen;

    if(param1.GetBuffer() == NULL)
    {
        pValidData = NULL;
        validLen = 0;
    }
    else
    {
        pValidData = param1.GetBuffer();
        validLen = param1.GetSize();
    }

    retVal = MFUpdate_Validate(param0, pValidData, validLen);

    return retVal;
}

bool MFNativeUpdate::Install( signed int param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
    (void)hr;
    // param0 ^= handle
    // param1 ^= pValidation

    bool retVal = 0; 

    CLR_UINT8*              pValidData;
    CLR_INT32               validLen;

    if(param1.GetBuffer() == NULL)
    {
        pValidData = NULL;
        validLen = 0;
    }
    else
    {
        pValidData = param1.GetBuffer();
        validLen = param1.GetSize();
    }

    retVal = MFUpdate_Install(param0, pValidData, validLen);

    return retVal;
}

