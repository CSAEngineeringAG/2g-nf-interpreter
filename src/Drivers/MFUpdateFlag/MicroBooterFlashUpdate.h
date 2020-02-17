
#include <nanoHal.h>
#include <MFUpdate_decl.h>

struct MicroBooterFlashUpdateProvider
{
    static BOOL InitializeUpdate( MFUpdate* pUpdate );
    static BOOL GetProperty     ( MFUpdate* pUpdate, LPCSTR szPropName , UINT8* pPropValue, INT32* pPropValueSize                       );
    static BOOL SetProperty     ( MFUpdate* pUpdate, LPCSTR szPropName , UINT8* pPropValue, INT32  pPropValueSize                       );
    static BOOL InstallUpdate   ( MFUpdate* pUpdate, UINT8* pValidation, INT32  validationLen                                           );
};

extern IUpdateProvider g_MicroBooterFlashUpdateProvider;

