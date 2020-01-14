
#include "MicroBooterFlashUpdate.h"
#include "UpdateFlashConfig.h"
#include <nanoCLR_Types.h>

IUpdateProvider g_MicroBooterFlashUpdateProvider = 
{
    MicroBooterFlashUpdateProvider::InitializeUpdate,
    MicroBooterFlashUpdateProvider::GetProperty,
    MicroBooterFlashUpdateProvider::SetProperty,
    MicroBooterFlashUpdateProvider::InstallUpdate,

    NULL,
};

extern void ClrReboot(void);

BOOL MicroBooterFlashUpdateProvider::InitializeUpdate( MFUpdate* pUpdate )
{
    if(pUpdate == NULL) return FALSE;

    switch(pUpdate->Header.UpdateType)
    {
        case MFUPDATE_UPDATETYPE_FIRMWARE:
        case MFUPDATE_UPDATETYPE_ASSEMBLY:
            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL MicroBooterFlashUpdateProvider::GetProperty( MFUpdate* pUpdate, LPCSTR szPropName , UINT8* pPropValue, INT32* pPropValueSize )
{
    (void) pUpdate;
    (void) szPropName;
    (void) pPropValue;
    (void) pPropValueSize;

    return FALSE;
}

BOOL MicroBooterFlashUpdateProvider::SetProperty( MFUpdate* pUpdate, LPCSTR szPropName , UINT8* pPropValue, INT32 pPropValueSize )
{
    (void) pUpdate;
    (void) szPropName;
    (void) pPropValue;
    (void) pPropValueSize;

    return FALSE;
}


BOOL MicroBooterFlashUpdateProvider::InstallUpdate( MFUpdate* pUpdate, UINT8* pValidation, INT32 validationLen )
{
    if(pUpdate->Providers->Storage == NULL) return FALSE;

    if(!pUpdate->IsValidated()) return FALSE;

    switch(pUpdate->Header.UpdateType)
    {
        case MFUPDATE_UPDATETYPE_FIRMWARE:
            {
                HAL_UPDATE_CONFIG cfg;

                if(sizeof(cfg.UpdateSignature) < (unsigned int) validationLen) return FALSE;
                
                cfg.Header.Enable = TRUE;
                cfg.UpdateID = pUpdate->Header.UpdateID;

                if(validationLen == sizeof(UINT32))
                {
                    cfg.UpdateSignType = HAL_UPDATE_CONFIG_SIGN_TYPE__CRC;
                }
                else
                {
                    cfg.UpdateSignType = HAL_UPDATE_CONFIG_SIGN_TYPE__SIGNATURE;
                }
                
                memcpy( cfg.UpdateSignature, pValidation, validationLen );

                //if(HAL_CONFIG_BLOCK::UpdateBlockWithName(cfg.GetDriverName(), &cfg, sizeof(cfg), FALSE))
                if(WriteUpdateFlashConfig(&cfg))
                {
                    CPU_Reset();
                }
            }
            break;
            
        case MFUPDATE_UPDATETYPE_ASSEMBLY:
            {
                BlockStorageStream stream;
                
                if(NULL == BlockStorageList_GetFirstDevice())
                {
                    BlockStorageList_Initialize();
                
                    BlockStorage_AddDevices();
                
                    BlockStorageList_InitializeDevices();
                }

                if(BlockStorageStream_Initialize(&stream, BlockUsage::BlockUsage_DEPLOYMENT))
                {
                    if(pUpdate->Header.UpdateSubType == MFUPDATE_UPDATESUBTYPE_ASSEMBLY_REPLACE_DEPLOY)
                    {
                        do
                        {
                            BlockStorageStream_Erase(&stream, stream.Length);
                        }
                        while(BlockStorageStream_NextStream(&stream));

                        BlockStorageStream_Initialize(&stream, BlockUsage::BlockUsage_DEPLOYMENT);
                    }
                    
                    do
                    {
                        unsigned char buf[512];
                        signed int offset = 0;
                        signed int len = sizeof(buf);
                        const DeviceBlockInfo* deviceInfo = BlockStorageDevice_GetDeviceInfo(stream.Device);
                        BOOL isXIP = deviceInfo->Attribute & MediaAttribute_SupportsXIP;
                        
                        const CLR_RECORD_ASSEMBLY* header;
                        signed int  headerInBytes = sizeof(CLR_RECORD_ASSEMBLY);
                        unsigned char * headerBuffer  = NULL;
                        
                        if(!isXIP)
                        {
                            headerBuffer = (unsigned char*)platform_malloc( headerInBytes );  if(!headerBuffer) return FALSE;
                            memset( headerBuffer, 0,  headerInBytes );
                        }
                        
                        while(TRUE)
                        {
                            if(!BlockStorageStream_Read(&stream, &headerBuffer, headerInBytes )) break;
                        
                            header = (const CLR_RECORD_ASSEMBLY*)headerBuffer;
                        
                            // check header first before read
                            if(!header->GoodHeader())
                            {
                                BlockStorageStream_Seek(&stream, -headerInBytes, SeekOrigin::BlockStorageStream_SeekCurrent);
                                
                                if(BlockStorageStream_IsErased(&stream, pUpdate->Header.UpdateSize))
                                {
                                    while((unsigned int) offset < pUpdate->Header.UpdateSize)
                                    {
                                        if((signed int)(pUpdate->Header.UpdateSize - offset) < len)
                                        {
                                            len = pUpdate->Header.UpdateSize - offset;
                                        }
                                        
                                        offset += pUpdate->Providers->Storage->Read(pUpdate->StorageHandle, offset, buf, len);

                                        BlockStorageStream_Write(&stream, buf, len);
                                    }

                                    ClrReboot();
                                    return TRUE;
                                }
                                break;
                            }
                        
                            UINT32 AssemblySizeInByte = ROUNDTOMULTIPLE(header->TotalSize(), CLR_UINT32);
                        
                            BlockStorageStream_Seek(&stream, AssemblySizeInByte, SeekOrigin::BlockStorageStream_SeekCurrent);
                        }
                        if(!isXIP) platform_free( headerBuffer );
                    
                    }
                    while(BlockStorageStream_NextStream(&stream));
                }

            }
            break;
    }
    
    return FALSE;
}
 
