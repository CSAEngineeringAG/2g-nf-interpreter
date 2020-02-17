
#include <nanohal.h>
#include <mfupdate_decl.h>
#include <MicroBooterFlashUpdate.h>
#include <CrcUpdateValidation.h>
#include <BlockStorageUpdate.h>

static const IUpdatePackage s_UpdatePackages[] =
{
    {
        "NetMF",
        &g_MicroBooterFlashUpdateProvider,
        &g_CrcUpdateValidationProvider,
        &g_BlockStorageUpdateProvider,
        NULL,

        NULL,
    }, 
};

const IUpdatePackage* g_UpdatePackages     = s_UpdatePackages;
const INT32           g_UpdatePackageCount = ARRAYSIZE(s_UpdatePackages);

