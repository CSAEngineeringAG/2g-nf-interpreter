
#include <MFUpdate_decl.h>

void  MFUpdate_Initialize(void)
{
}

/*
BOOL MFUpdate_GetProperty( UINT32 updateHandle, LPCSTR szPropName, UINT8* pPropValue, INT32* pPropValueSize )
{
    return FALSE;
}

BOOL MFUpdate_SetProperty( UINT32 updateHandle, LPCSTR szPropName, UINT8* pPropValue, INT32 pPropValueSize )
{
    return FALSE;
}
*/

INT32 MFUpdate_InitUpdate( LPCSTR szProvider, MFUpdateHeader& update )
{
    (void) szProvider;
    (void) update;

    return -1;
}

/*
BOOL MFUpdate_AuthCommand( INT32 updateHandle, UINT32 cmd, UINT8* pArgs, INT32 argsLen, UINT8* pResponse, INT32& responseLen )
{
    return FALSE;
}
*/

BOOL MFUpdate_Authenticate( INT32 updateHandle, UINT8* pAuthData, INT32 authLen )
{
    (void) updateHandle;
    (void) pAuthData;
    (void) authLen;

    return FALSE;
}

BOOL MFUpdate_Open( INT32 updateHandle )
{
    (void) updateHandle;

    return FALSE;
}

BOOL MFUpdate_Create( INT32 updateHandle )
{
    (void) updateHandle;

    return FALSE;
}

BOOL MFUpdate_GetMissingPackets( INT32 updateHandle, UINT32* pPacketBits, INT32* pCount )
{
    (void) updateHandle;
    (void) pPacketBits;
    (void) pCount;

    return FALSE;
}

BOOL MFUpdate_AddPacket( INT32 updateHandle, INT32 packetIndex, UINT8* packetData, INT32 packetLen, UINT8* pValidationData, INT32 validationLen )
{
    (void) updateHandle;
    (void) packetIndex;
    (void) packetData;
    (void) packetLen;
    (void) pValidationData;
    (void) validationLen;

    return FALSE;
}

BOOL MFUpdate_Validate( INT32 updateHandle, UINT8* pValidationData, INT32 validationLen )
{
    (void) updateHandle;
    (void) pValidationData;
    (void) validationLen;
    
    return FALSE;
}

BOOL MFUpdate_Install( INT32 updateHandle, UINT8* pValidationData, INT32 validationLen )
{ 
    (void) updateHandle;
    (void) pValidationData;
    (void) validationLen;
    
    return FALSE;
}

/*
BOOL MFUpdate_Delete( INT32 updateHandle )
{
    return FALSE;
}
*/
