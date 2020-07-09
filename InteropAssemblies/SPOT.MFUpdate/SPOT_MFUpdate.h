//-----------------------------------------------------------------------------
//
//    ** DO NOT EDIT THIS FILE! **
//    This file was generated by a tool
//    re-running the tool will overwrite this file.
//
//-----------------------------------------------------------------------------


#ifndef _SPOT_MFUPDATE_H_
#define _SPOT_MFUPDATE_H_

#include <nanoCLR_Interop.h>
#include <nanoCLR_Runtime.h>
struct Library_SPOT_MFUpdate_SPOT_MFUpdate_MFUpdateBase
{
    static const int FIELD__m_provider = 1;
    static const int FIELD__m_updateID = 2;
    static const int FIELD__m_updateVersion = 3;
    static const int FIELD__m_updateType = 4;
    static const int FIELD__m_updateSubType = 5;
    static const int FIELD__m_updateSize = 6;
    static const int FIELD__m_packetSize = 7;
    static const int FIELD__m_updateHandle = 8;


    //--//

};

struct Library_SPOT_MFUpdate_SPOT_MFUpdate_MFUpdate
{
    static const int FIELD__m_pktBitChk = 9;
    static const int FIELD__m_maxPkt = 10;
    static const int FIELD__m_authenticated = 11;


    //--//

};

struct Library_SPOT_MFUpdate_SPOT_MFUpdate_MFNativeUpdate
{
    NANOCLR_NATIVE_DECLARE(_cctor___STATIC__VOID);
    NANOCLR_NATIVE_DECLARE(Initialize___STATIC__I4__U4__U4__U4__U2__U2__I4__I4__I4__I4__STRING);
    NANOCLR_NATIVE_DECLARE(Authenticate___STATIC__BOOLEAN__I4__SZARRAY_U1);
    NANOCLR_NATIVE_DECLARE(Open___STATIC__BOOLEAN__I4);
    NANOCLR_NATIVE_DECLARE(Create___STATIC__BOOLEAN__I4);
    NANOCLR_NATIVE_DECLARE(GetMissingPackets___STATIC__VOID__I4__SZARRAY_U4);
    NANOCLR_NATIVE_DECLARE(AddPacket___STATIC__BOOLEAN__I4__I4__SZARRAY_U1__SZARRAY_U1);
    NANOCLR_NATIVE_DECLARE(Validate___STATIC__BOOLEAN__I4__SZARRAY_U1);
    NANOCLR_NATIVE_DECLARE(Install___STATIC__BOOLEAN__I4__SZARRAY_U1);

    //--//

};

struct Library_SPOT_MFUpdate_SPOT_MFUpdate_MFUpdatePkt
{
    static const int FIELD__PacketIndex = 1;
    static const int FIELD__ValidationData = 2;
    static const int FIELD__Data = 3;


    //--//

};

struct Library_SPOT_MFUpdate_SPOT_MFUpdate_MFUpdateProperty
{
    static const int FIELD__Name = 1;
    static const int FIELD__Value = 2;


    //--//

};

struct Library_SPOT_MFUpdate_SPOT_MFUpdate_MissingPacketEnumerator
{
    static const int FIELD__m_pktBitChk = 1;
    static const int FIELD__m_currentIdx = 2;
    static const int FIELD__m_maxPkt = 3;


    //--//

};



extern const CLR_RT_NativeAssemblyData g_CLR_AssemblyNative_SPOT_MFUpdate;

#endif  //_SPOT_MFUPDATE_H_
