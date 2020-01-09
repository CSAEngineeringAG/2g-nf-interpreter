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
//#include <MFUpdate_decl.h>

using namespace SPOT::MFUpdate;

void MFNativeUpdate::_cctor( HRESULT &hr )
{
    (void)hr;
/*
    MFUpdate_Initialize();
*/
}

signed int MFNativeUpdate::Initialize( UNSUPPORTED_TYPE param0, HRESULT &hr )
{
    (void)hr;
    (void)param0;
    CLR_INT32 retVal = 0; 
/*
    CLR_RT_HeapBlock* pUpdateBase = stack.Arg0().Dereference();
    MFUpdateHeader header;
    LPCSTR szProvider;

    FAULT_ON_NULL(pUpdateBase);

    szProvider = pUpdateBase[Library_spot_update_native_Microsoft_SPOT_MFUpdate_MFUpdateBase::FIELD__m_provider].Dereference()->StringText();

    MarshalStorageHeader(pUpdateBase, header);

    retVal = MFUpdate_InitUpdate(szProvider, header);
*/
    return retVal;
}

bool MFNativeUpdate::Authenticate( signed int param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
    (void)hr;
    (void)param0;
    (void)param1;

    bool retVal = 0; 
/*
    CLR_INT32               handle  = param0;
    CLR_RT_HeapBlock_Array* paArgs  = param1;
    CLR_UINT8*              pArgs   = paArgs == NULL ? NULL : paArgs->GetFirstElement();
    CLR_INT32               argsLen = paArgs == NULL ? 0    : paArgs->m_numOfElements;

    retVal = MFUpdate_Authenticate(handle, pArgs, argsLen);
*/
    return retVal;
}

bool MFNativeUpdate::Open( signed int param0, HRESULT &hr )
{
    (void)hr;
    (void)param0;

    bool retVal = 0; 
/*
    CLR_INT32 handle = param0;

    retVal = MFUpdate_Open(handle);
*/
    return retVal;
}

bool MFNativeUpdate::Create( signed int param0, HRESULT &hr )
{
    (void)hr;
    (void)param0;

    bool retVal = 0;
/*
    CLR_INT32 handle = param0;

    retVal = MFUpdate_Create(handle);
*/
    return retVal;
}

void MFNativeUpdate::GetMissingPackets( signed int param0, CLR_RT_TypedArray_UINT32 param1, HRESULT &hr )
{
    (void)hr;
    (void)param0;
    (void)param1;
/*
    CLR_INT32 handle = param0;
    CLR_RT_HeapBlock_Array* pArray = param1; 
    CLR_INT32 pktCount;

    FAULT_ON_NULL(pArray);

    pktCount = pArray->m_numOfElements;

    if(!MFUpdate_GetMissingPackets(handle, (UINT32*)pArray->GetFirstElement(), &pktCount))
    {
        TINYCLR_SET_AND_LEAVE(CLR_E_FAIL);
    }
*/
}

bool MFNativeUpdate::AddPacket( signed int param0, signed int param1, CLR_RT_TypedArray_UINT8 param2, CLR_RT_TypedArray_UINT8 param3, HRESULT &hr )
{
    (void)hr;
    (void)param0;
    (void)param1;
    (void)param2;
    (void)param3;

    bool retVal = 0;
/*
    CLR_INT32  handle       = param0;
    CLR_INT32  pktIndex     = param1;
    CLR_RT_HeapBlock_Array* pPacket     = param2;
    CLR_RT_HeapBlock_Array* pValidation = param3;
    CLR_UINT8* pValidData;
    CLR_INT32 validLen;

    FAULT_ON_NULL(pPacket);

    if(pValidation == NULL)
    {
        pValidData = NULL;
        validLen = 0;
    }
    else
    {
        pValidData = pValidation->GetFirstElement();
        validLen = pValidation->m_numOfElements;
    }

    retVal = MFUpdate_AddPacket(handle, pktIndex, pPacket->GetFirstElement(), pPacket->m_numOfElements, pValidData, validLen);
*/
    return retVal;
}

bool MFNativeUpdate::Validate( signed int param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
    (void)hr;
    (void)param0;
    (void)param1;

    bool retVal = 0;
/*
    CLR_INT32               handle      = param0;
    CLR_RT_HeapBlock_Array* pValidation = param1;
    CLR_UINT8*              pValidData;
    CLR_INT32               validLen;

    if(pValidation == NULL)
    {
        pValidData = NULL;
        validLen = 0;
    }
    else
    {
        pValidData = pValidation->GetFirstElement();
        validLen = pValidation->m_numOfElements;
    }

    retVal = MFUpdate_Validate(handle, pValidData, validLen);
*/
    return retVal;
}

bool MFNativeUpdate::Install( signed int param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
    (void)hr;
    (void)param0;
    (void)param1;

    bool retVal = 0; 
/*
    CLR_INT32               handle      = param0;
    CLR_RT_HeapBlock_Array* pValidation = param1;
    CLR_UINT8*              pValidData;
    CLR_INT32               validLen;

    if(pValidation == NULL)
    {
        pValidData = NULL;
        validLen = 0;
    }
    else
    {
        pValidData = pValidation->GetFirstElement();
        validLen = pValidation->m_numOfElements;
    }

    retVal = MFUpdate_Install(handle, pValidData, validLen);
*/
    return retVal;
}

