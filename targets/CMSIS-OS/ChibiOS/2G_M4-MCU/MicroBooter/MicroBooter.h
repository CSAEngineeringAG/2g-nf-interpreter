
#ifndef __MICROBOOTER_DECL_H__
#define __MICROBOOTER_DECL_H__

/////////////////////////////////////////////////////////////////////////////

#include <nanoHAL.h>
#include <MFUpdate_decl.h>

//extern BOOL EnterMicroBooter(INT32& timeout);

//extern UINT32 MicroBooter_ProgramMarker();

//extern UINT32 MicroBooter_PrepareForExecution(UINT32 physicalEntryPointAddress);

extern const IUpdateStorageProvider** g_MicroBooter_UpdateStorageList;
extern UINT32                         g_MicroBooter_UpdateStorageListCount;

/////////////////////////////////////////////////////////////////////////////

#endif /* __MICROBOOTER_DECL_H__ */