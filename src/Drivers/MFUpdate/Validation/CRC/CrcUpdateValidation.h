
#include <nanohal.h>
#include <mfupdate_decl.h>
//#include <PAL\PKCS11\cryptokipal.h>

struct UpdateValidationCRC
{
    static BOOL AuthCommand   ( MFUpdate* pUpdate, UINT32 cmd        , UINT8* pArgs        , INT32  argsLen    , UINT8* pResponse   , INT32& responseLen );
    static BOOL Authenticate  ( MFUpdate* pUpdate, UINT8* pAuth      , INT32  authLen                                                                   );    
    static BOOL ValidatePacket( MFUpdate* pUpdate, UINT8* pPacket    , INT32  packetLen    , UINT8* pValidation, INT32 validationLen                    );
    static BOOL ValidateUpdate( MFUpdate* pUpdate, UINT8* pValidation, INT32  validationLen                                                             );
};

//--//

extern IUpdateValidationProvider g_CrcUpdateValidationProvider;

UINT32 SUPPORT_ComputeCRC( const void* rgBlock , int nLength, UINT32 crc );
