
#include "BlockStorageUpdate.h"

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_BlockStorageUpdate"
#endif

BlockStorageUpdate g_BlockStorageUpdate;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

void BlockStorageUpdate::BlockStorageUpdate_RebootHandler()
{
    g_BlockStorageUpdate.m_initialized = FALSE;
}

IUpdateStorageProvider g_BlockStorageUpdateProvider = 
{
    BlockStorageUpdate::Initialize,
    BlockStorageUpdate::Create,
    BlockStorageUpdate::Open,
    BlockStorageUpdate::Close,
    BlockStorageUpdate::Delete,
    BlockStorageUpdate::GetFiles,
    BlockStorageUpdate::IsErased,
    BlockStorageUpdate::Write,
    BlockStorageUpdate::Read,
    BlockStorageUpdate::GetHeader,
    BlockStorageUpdate::GetEraseSize,

    NULL,
};

BOOL BlockStorageUpdate::Initialize()
{
    if(NULL == BlockStorageList_GetFirstDevice())
    {
        BlockStorageList_Initialize();

        BlockStorage_AddDevices();

        BlockStorageList_InitializeDevices();
    }    

    return TRUE;
}

BOOL BlockStorageUpdate::InitializeFiles( UINT32 blockTypes )
{
    struct UpdateBlockHeader header;
    int freeListIdx = 0;

    if(g_BlockStorageUpdate.m_initialized) return FALSE;

    HAL_AddSoftRebootHandler(BlockStorageUpdate_RebootHandler);
    
    memset(g_BlockStorageUpdate.m_files   , 0, sizeof(g_BlockStorageUpdate.m_files   ));
    memset(g_BlockStorageUpdate.m_freeList, 0, sizeof(g_BlockStorageUpdate.m_freeList));

    g_BlockStorageUpdate.m_pFreeList = g_BlockStorageUpdate.m_freeList;

    if(!BlockStorageStream_Initialize(&g_BlockStorageUpdate.m_stream, blockTypes)) return FALSE;

    do
    {
        if(!BlockStorageStream_IsErased(&g_BlockStorageUpdate.m_stream, g_BlockStorageUpdate.m_stream.BlockLength))
        {
            if(BlockStorageStream_ReadIntoBuffer(&g_BlockStorageUpdate.m_stream, (UINT8*)&header, sizeof(header)))
            {
                if(header.fileSignature == c_FileSignature)
                {
                    INT32 handle = GetFreeHandle();

                    g_BlockStorageUpdate.m_files[handle].StartAddress = g_BlockStorageUpdate.m_stream.CurrentIndex - sizeof(header);
                    g_BlockStorageUpdate.m_files[handle].Size         = header.storageHeader.UpdateSize + sizeof(header);
                    g_BlockStorageUpdate.m_files[handle].ID           = header.storageHeader.UpdateID;
                    g_BlockStorageUpdate.m_files[handle].Type         = header.storageHeader.UpdateType;
                    g_BlockStorageUpdate.m_files[handle].SubType      = header.storageHeader.UpdateSubType;

                    BlockStorageStream_Seek(&g_BlockStorageUpdate.m_stream, g_BlockStorageUpdate.m_files[handle].Size, SeekOrigin::BlockStorageStream_SeekCurrent);
                }
            }
        }
        else if((unsigned long) freeListIdx < ARRAYSIZE(g_BlockStorageUpdate.m_freeList))
        {

            int size = g_BlockStorageUpdate.m_freeList[freeListIdx].File.Size;
            
            if(size == 0)
            {
                g_BlockStorageUpdate.m_freeList[freeListIdx].File.StartAddress = g_BlockStorageUpdate.m_stream.CurrentIndex;
                g_BlockStorageUpdate.m_freeList[freeListIdx].File.Size         = g_BlockStorageUpdate.m_stream.BlockLength;
            }
            else if(g_BlockStorageUpdate.m_freeList[freeListIdx].File.StartAddress + size == g_BlockStorageUpdate.m_stream.CurrentIndex)
            {
                g_BlockStorageUpdate.m_freeList[freeListIdx].File.Size += g_BlockStorageUpdate.m_stream.BlockLength;
            }
            else
            {
                freeListIdx++;
                g_BlockStorageUpdate.m_freeList[freeListIdx].Next              = &g_BlockStorageUpdate.m_freeList[freeListIdx];
                g_BlockStorageUpdate.m_freeList[freeListIdx].File.StartAddress = g_BlockStorageUpdate.m_stream.CurrentIndex;
                g_BlockStorageUpdate.m_freeList[freeListIdx].File.Size         = g_BlockStorageUpdate.m_stream.BlockLength;
            }
        }
    }
    while(BlockStorageStream_Seek(&g_BlockStorageUpdate.m_stream, BLOCKSTORAGESTREAM_STREAM_SEEK_NEXT_BLOCK, SeekOrigin::BlockStorageStream_SeekCurrent));

    g_BlockStorageUpdate.m_initialized = TRUE;

    return TRUE;
}

INT32 BlockStorageUpdate::GetFreeHandle()
{
    INT32 newHandle = -1;

    for(int idx = 0; (unsigned long) idx < ARRAYSIZE(g_BlockStorageUpdate.m_files); idx++)
    {
        if(g_BlockStorageUpdate.m_files[idx].Size == 0)
        {
            newHandle = idx;
            break;
        }
    }

    return newHandle;
}

INT32 BlockStorageUpdate::Create( MFUpdateHeader& storageHeader, UINT32 flags )
{
    (void) flags;

    INT32 newHandle = -1, i;
    UpdateBlockHeader header;
    header.fileSignature = c_FileSignature;
    FreeListItem* pCur, *pLast;
    INT32 mod;

    if(!g_BlockStorageUpdate.m_initialized) g_BlockStorageUpdate.InitializeFiles(BlockUsage::BlockUsage_UPDATE);

    INT32 updateSizeTotal = storageHeader.UpdateSize + sizeof(header);

    // make sure we are on block boundaries for erases
    mod = (updateSizeTotal % g_BlockStorageUpdate.m_stream.BlockLength);

    if(mod != 0)
    {
        updateSizeTotal += g_BlockStorageUpdate.m_stream.BlockLength - mod;
    }

    // If we are creating a new deployment we should erase any other of the same type 
    Delete( MFUPDATE_UPDATEID_ANY, storageHeader.UpdateType, MFUPDATE_UPDATESUBTYPE_ANY );

    for(i=0; (unsigned long) i < ARRAYSIZE(g_BlockStorageUpdate.m_files); i++)
    {
        if( g_BlockStorageUpdate.m_files[i].Type    == storageHeader.UpdateType    && 
            g_BlockStorageUpdate.m_files[i].SubType == storageHeader.UpdateSubType && 
            g_BlockStorageUpdate.m_files[i].ID      == (unsigned int) storageHeader.UpdateID      && 
            g_BlockStorageUpdate.m_files[i].Size    != 0 )
        {
            return -1;
        }
    }
    
    memcpy(&header.storageHeader, &storageHeader, sizeof(header.storageHeader));

    newHandle = g_BlockStorageUpdate.GetFreeHandle();

    if(newHandle == -1) return -1;

    pCur = g_BlockStorageUpdate.m_pFreeList;
    pLast = pCur;
    
    while(pCur)
    {
        if((signed long) pCur->File.Size >= updateSizeTotal)
        {
            g_BlockStorageUpdate.m_files[newHandle].ID           = storageHeader.UpdateID;
            g_BlockStorageUpdate.m_files[newHandle].Type         = storageHeader.UpdateType;
            g_BlockStorageUpdate.m_files[newHandle].SubType      = storageHeader.UpdateSubType;
            g_BlockStorageUpdate.m_files[newHandle].StartAddress = pCur->File.StartAddress;
            g_BlockStorageUpdate.m_files[newHandle].Size         = updateSizeTotal;

            if((signed long) pCur->File.Size > updateSizeTotal)
            {
                pCur->File.StartAddress += updateSizeTotal;
                pCur->File.Size         -= updateSizeTotal;
            }
            else if(pCur == g_BlockStorageUpdate.m_pFreeList)
            {
                g_BlockStorageUpdate.m_pFreeList = pCur->Next;
            }
            else
            {
                pLast->Next = pCur->Next;
            }
            
            break;
        }

        pLast = pCur;
        pCur  = pCur->Next;
    }

    if(pCur == NULL) return -1;

    BlockStorageDevice_Write(g_BlockStorageUpdate.m_stream.Device, g_BlockStorageUpdate.m_files[newHandle].StartAddress + g_BlockStorageUpdate.m_stream.BaseAddress, sizeof(header), (UINT8*)&header, FALSE);

    return newHandle;
}

INT32 BlockStorageUpdate::Open( INT32 storageID, UINT16 storageType, UINT16 storageSubType)
{
    INT32 i;
    struct UpdateBlockHeader header;

    memset(&header, 0, sizeof(header));

    if(!g_BlockStorageUpdate.m_initialized) g_BlockStorageUpdate.InitializeFiles(BlockUsage::BlockUsage_UPDATE);

    for(i = 0; (unsigned long) i <  ARRAYSIZE(g_BlockStorageUpdate.m_files); i++)
    {
        if( (MFUPDATE_UPDATEID_ANY      == (unsigned int) storageID      || g_BlockStorageUpdate.m_files[i].ID      == (unsigned int) storageID     ) && 
            (MFUPDATE_UPDATETYPE_ANY    == storageType    || g_BlockStorageUpdate.m_files[i].Type    == storageType   ) &&
            (MFUPDATE_UPDATESUBTYPE_ANY == storageSubType || g_BlockStorageUpdate.m_files[i].SubType == storageSubType) &&
            g_BlockStorageUpdate.m_files[i].Size > 0)
        {
            
            return i;
        }
    }

    return -1;
}

void  BlockStorageUpdate::Close     ( INT32 handleStorage )
{
    (void) handleStorage;
}

BOOL BlockStorageUpdate::Delete( INT32 storageID, UINT16 storageType, UINT16 storageSubType )
{
    for(int i = 0; (unsigned long) i < ARRAYSIZE(g_BlockStorageUpdate.m_files); i++)
    {
        if( (MFUPDATE_UPDATEID_ANY      == (unsigned int) storageID   || g_BlockStorageUpdate.m_files[i].ID      == (unsigned int) storageID     ) && 
            (MFUPDATE_UPDATETYPE_ANY    == storageType || g_BlockStorageUpdate.m_files[i].Type    == storageType   ) &&
            (MFUPDATE_UPDATESUBTYPE_ANY == storageType || g_BlockStorageUpdate.m_files[i].SubType == storageSubType) &&
            g_BlockStorageUpdate.m_files[i].Size > 0)
        {
            FreeListItem* pCur  = g_BlockStorageUpdate.m_pFreeList;
            FreeListItem* pLast = pCur;

            BlockStorageStream_Seek(&g_BlockStorageUpdate.m_stream, g_BlockStorageUpdate.m_files[i].StartAddress, SeekOrigin::BlockStorageStream_SeekBegin);
            BlockStorageStream_Erase(&g_BlockStorageUpdate.m_stream, g_BlockStorageUpdate.m_files[i].Size);

            while(pCur)
            {
                int size = g_BlockStorageUpdate.m_files[i].Size;
                int start = g_BlockStorageUpdate.m_files[i].StartAddress;
                
                if((unsigned long) pCur->File.StartAddress > size)
                {
                    if((unsigned long) (size + start) == pCur->File.StartAddress)
                    {
                        pCur->File.StartAddress -= size;
                        pCur->File.Size         += size;
                    }
                    else
                    {
                        for(int j = 0; (unsigned long) j < ARRAYSIZE(g_BlockStorageUpdate.m_freeList); j++)
                        {
                            if(g_BlockStorageUpdate.m_freeList[j].File.Size == 0)
                            {
                                FreeListItem *pItem = &g_BlockStorageUpdate.m_freeList[j];

                                pItem->File.StartAddress = start;
                                pItem->File.Size         = size;

                                pItem->Next = pCur;

                                if(g_BlockStorageUpdate.m_pFreeList == pCur)
                                {
                                    g_BlockStorageUpdate.m_pFreeList = pItem;
                                }
                                else
                                {
                                    pLast->Next = pItem;
                                }
                            }
                        }
                    }
                    break;
                }
                pLast = pCur;
                pCur  = pCur->Next;
            }
            
            g_BlockStorageUpdate.m_files[i].Size = 0;
            
            return TRUE;
        }
    }

    return FALSE;
}
BOOL BlockStorageUpdate::GetFiles( UINT16 storageType, INT32* storageIDs, INT32* storageCount )
{
    if(storageCount == NULL) return FALSE;
    if(storageIDs == NULL) *storageCount = 0;

    INT32 idx = 0;

    if(!g_BlockStorageUpdate.m_initialized) g_BlockStorageUpdate.InitializeFiles(BlockUsage::BlockUsage_UPDATE);
        
    for(int i = 0; (unsigned long) i < ARRAYSIZE(g_BlockStorageUpdate.m_files); i++)
    {
        if((MFUPDATE_UPDATETYPE_ANY == storageType || g_BlockStorageUpdate.m_files[i].Type == storageType) && 
            g_BlockStorageUpdate.m_files[i].Size > 0)
        {
            if(storageIDs == NULL)
            {
                (*storageCount)++;
            }
            else
            {
                if(idx < *storageCount)
                {
                    storageIDs[idx++] = i;
                }
                else
                {
                    break;
                }
            }
        }
    }

    return TRUE;
}

BOOL BlockStorageUpdate::IsErased ( INT32  handleStorage, INT32 fileOffset, INT32  len )
{
    if(handleStorage < 0 || (unsigned long) handleStorage >= ARRAYSIZE(g_BlockStorageUpdate.m_files) || g_BlockStorageUpdate.m_files[handleStorage].Size <= 0) return FALSE;

    BlockStorageStream_Seek(&g_BlockStorageUpdate.m_stream, g_BlockStorageUpdate.m_files[handleStorage].StartAddress + sizeof(UpdateBlockHeader) + fileOffset, SeekOrigin::BlockStorageStream_SeekBegin);
        
    return BlockStorageStream_IsErased(&g_BlockStorageUpdate.m_stream, len);
}

INT32 BlockStorageUpdate::Write( INT32  handleStorage, INT32 fileOffset, UINT8* pData, INT32 len )
{
    if(handleStorage < 0 || (unsigned long) handleStorage >= ARRAYSIZE(g_BlockStorageUpdate.m_files) || g_BlockStorageUpdate.m_files[handleStorage].Size <= 0) return FALSE;

    BlockStorageStream_Seek(&g_BlockStorageUpdate.m_stream, g_BlockStorageUpdate.m_files[handleStorage].StartAddress + sizeof(UpdateBlockHeader) + fileOffset, SeekOrigin::BlockStorageStream_SeekBegin );
        
    return BlockStorageStream_Write(&g_BlockStorageUpdate.m_stream, pData, len) ? len : -1;
}

INT32 BlockStorageUpdate::Read( INT32  handleStorage, INT32 fileOffset, UINT8* pData, INT32 len )
{
    if(handleStorage < 0 || (unsigned long) handleStorage >= ARRAYSIZE(g_BlockStorageUpdate.m_files) || g_BlockStorageUpdate.m_files[handleStorage].Size <= 0) return FALSE;

    BlockStorageStream_Seek(&g_BlockStorageUpdate.m_stream, g_BlockStorageUpdate.m_files[handleStorage].StartAddress + sizeof(UpdateBlockHeader) + fileOffset, SeekOrigin::BlockStorageStream_SeekBegin );
        
    return BlockStorageStream_ReadIntoBuffer(&g_BlockStorageUpdate.m_stream, pData, len) ? len : -1;
}

BOOL BlockStorageUpdate::GetHeader( INT32 handleStorage, MFUpdateHeader* pHeader )
{
    UpdateBlockHeader hdr;
    
    if(handleStorage < 0 || (unsigned long) handleStorage >= ARRAYSIZE(g_BlockStorageUpdate.m_files) || g_BlockStorageUpdate.m_files[handleStorage].Size <= 0) return FALSE;

    BlockStorageStream_Seek(&g_BlockStorageUpdate.m_stream, g_BlockStorageUpdate.m_files[handleStorage].StartAddress, SeekOrigin::BlockStorageStream_SeekBegin );
        
    if(!BlockStorageStream_ReadIntoBuffer(&g_BlockStorageUpdate.m_stream, (UINT8*)&hdr, sizeof(hdr))) return FALSE;

    memcpy(pHeader, &hdr.storageHeader, sizeof(hdr.storageHeader));

    return TRUE;
}

UINT32 BlockStorageUpdate::GetEraseSize( INT32 handleStorage )
{
    if(handleStorage < 0 || (unsigned long) handleStorage >= ARRAYSIZE(g_BlockStorageUpdate.m_files) || g_BlockStorageUpdate.m_files[handleStorage].Size <= 0) return FALSE;

    return g_BlockStorageUpdate.m_stream.BlockLength;
}

