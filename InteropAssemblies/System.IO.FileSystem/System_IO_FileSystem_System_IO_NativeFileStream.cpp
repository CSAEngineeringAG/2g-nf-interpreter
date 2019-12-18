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
#include "System_IO_FileSystem.h"
#include "System_IO_FileSystem_System_IO_NativeFileStream.h"

#include <ff.h>
#include <nanoHAL_Windows_Storage.h>

using namespace System::IO;

void CombinePathAndName(char * outpath, const char * path1, const char * path2)
{
	strcat(outpath, path1);
	
	// Add "\" to path if required
	if (outpath[hal_strlen_s(outpath) - 1] != '\\')
	{
		strcat(outpath, "\\");
	}
	strcat(outpath, path2);
}

void NativeFileStream::OpenFileNative( CLR_RT_HeapBlock* pMngObj, const char* param0, const char* param1, signed int param2, HRESULT &hr )
{
    (void)hr;
    (void)pMngObj;

    const char* workingPath = param0;
    const char* fileName = param1;
    signed int mode = param2;
    
    FIL             file; 
    FRESULT         operationResult;
    uint8_t         modeFlags = 0;
    char*           filePath = NULL;

    // setup file path
    filePath = (char*)platform_malloc(2 * FF_LFN_BUF + 1);

    // sanity check for successfull malloc
    if(filePath == NULL)
    {
        // failed to allocate memory
        NANOCLR_SET_AND_LEAVE(CLR_E_OUT_OF_MEMORY);
    }

    // clear working buffer
    memset(filePath, 0, 2 * FF_LFN_BUF + 1);

    // compose file path
    CombinePathAndName(filePath, workingPath, fileName);

    // change directory
    operationResult = f_chdir(workingPath);

    if(operationResult != FR_OK)
    {
        if(operationResult == FR_INVALID_DRIVE)
        {
            // invalid drive
            NANOCLR_SET_AND_LEAVE(CLR_E_VOLUME_NOT_FOUND);
        }
        else
        {
            // error opening the directoty
            NANOCLR_SET_AND_LEAVE(CLR_E_DIRECTORY_NOT_FOUND);
        }
    }
    else
    {
        // compute mode flags from FileMode
        switch(mode)
        {
            case FileMode_CreateNew:
                modeFlags = FA_CREATE_NEW;
                break;

            case FileMode_Create:
                modeFlags = FA_CREATE_ALWAYS;
                break;

            case FileMode_Open:
                modeFlags = FA_OPEN_EXISTING;
                break;

            case FileMode_OpenOrCreate:
                modeFlags = FA_OPEN_ALWAYS;
                break;

            case FileMode_Truncate:
                modeFlags = FA_CREATE_ALWAYS;
                break;

            case FileMode_Append:
                modeFlags = FA_OPEN_APPEND;
                break;

            default:
                NANOCLR_SET_AND_LEAVE(CLR_E_WRONG_TYPE);
        }

        // open file
        operationResult = f_open(&file, filePath, modeFlags);

        // process operation result according to creation options
        if( (operationResult == FR_EXIST) && 
            (mode == FileMode_CreateNew))
        {
            // file already exists
            NANOCLR_SET_AND_LEAVE(CLR_E_PATH_ALREADY_EXISTS);
        }

        if( (operationResult == FR_NO_FILE) &&
            ((mode == FileMode_Open) || (mode == FileMode_Truncate)))
        {
            // file doesn't exist
            NANOCLR_SET_AND_LEAVE(CLR_E_FILE_NOT_FOUND);
        }

        if(operationResult == FR_OK)
        {
            // file created (or opened) succesfully
            // OK to close it
            f_close(&file);
        }
        else
        {
            // failed to create the file
            NANOCLR_SET_AND_LEAVE(CLR_E_FILE_IO);
        }
    }

    NANOCLR_CLEANUP();

    // free buffer memory, if allocated
    if(filePath != NULL)
    {
        platform_free(filePath);
    }
}

signed int NativeFileStream::ReadNative( CLR_RT_HeapBlock* pMngObj, const char* param0, const char* param1, signed __int64 param2, CLR_RT_TypedArray_UINT8 param3, signed int param4, HRESULT &hr )
{
    (void)hr;
    (void)pMngObj;

    (void)param0;
    (void)param1;
    (void)param2;

    const char* workingPath = param0;
    const char* fileName = param1;
    signed __int64 position = param2;
    unsigned char* buffer = param3.GetBuffer();
    int length = param4;
    unsigned int readCount = 0; 

    FIL             file; 
    FRESULT         operationResult;
    char*           filePath = NULL;

    // setup file path
    filePath = (char*)platform_malloc(2 * FF_LFN_BUF + 1);

    // sanity check for successfull malloc
    if(filePath == NULL)
    {
        // failed to allocate memory
        NANOCLR_SET_AND_LEAVE(CLR_E_OUT_OF_MEMORY);
    }

    // clear working buffer
    memset(filePath, 0, 2 * FF_LFN_BUF + 1);

    // compose file path
    CombinePathAndName(filePath, workingPath, fileName);

    // change directory
    operationResult = f_chdir(workingPath);

    if(operationResult != FR_OK)
    {
        if(operationResult == FR_INVALID_DRIVE)
        {
            // invalid drive
            NANOCLR_SET_AND_LEAVE(CLR_E_VOLUME_NOT_FOUND);
        }
        else
        {
            // error opening the directoty
            NANOCLR_SET_AND_LEAVE(CLR_E_DIRECTORY_NOT_FOUND);
        }
    }
    else
    {
        // open file
        operationResult = f_open(&file, filePath, FA_READ);

        if(operationResult == FR_OK)
        {
            operationResult = f_lseek(&file, position);     // Change to actual position
            if(operationResult != FR_OK)
            {
                // failed to change position
                NANOCLR_SET_AND_LEAVE(CLR_E_INDEX_OUT_OF_RANGE);
            }

            // If there is not as much data to read as asked, shorten the length
            if((f_size(&file) - position) < length)
            {
                length = f_size(&file) - position;
            }

            // file opened succesfully
            operationResult = f_read(&file, buffer, length, &readCount);
            if(operationResult != FR_OK)
            {
                // Failed to write to file
                NANOCLR_SET_AND_LEAVE(CLR_E_FILE_IO);
            }

            // OK to close it
            f_close(&file);
        }
        else
        {
            // failed to create the file
            NANOCLR_SET_AND_LEAVE(CLR_E_FILE_IO);
        }
    }

    NANOCLR_CLEANUP();

    // free buffer memory, if allocated
    if(filePath != NULL)
    {
        platform_free(filePath);
    }

    return readCount;
}

//void NativeFileStream::WriteNative( CLR_RT_HeapBlock* pMngObj, const char* param0, const char* param1, signed __int64 param2, const char* param3, signed int param4, HRESULT &hr )
void NativeFileStream::WriteNative( CLR_RT_HeapBlock* pMngObj, const char* param0, const char* param1, signed __int64 param2, CLR_RT_TypedArray_UINT8 param3, signed int param4, HRESULT &hr )
{
    (void)hr;
    (void)pMngObj;

    const char* workingPath = param0;
    const char* fileName = param1;
    signed __int64 position = param2;
    const unsigned char* buffer = param3.GetBuffer();
    const int length = param4;

    FIL             file; 
    FRESULT         operationResult;
    char*           filePath = NULL;

    // setup file path
    filePath = (char*)platform_malloc(2 * FF_LFN_BUF + 1);

    // sanity check for successfull malloc
    if(filePath == NULL)
    {
        // failed to allocate memory
        NANOCLR_SET_AND_LEAVE(CLR_E_OUT_OF_MEMORY);
    }

    // clear working buffer
    memset(filePath, 0, 2 * FF_LFN_BUF + 1);

    // compose file path
    CombinePathAndName(filePath, workingPath, fileName);

    // change directory
    operationResult = f_chdir(workingPath);

    if(operationResult != FR_OK)
    {
        if(operationResult == FR_INVALID_DRIVE)
        {
            // invalid drive
            NANOCLR_SET_AND_LEAVE(CLR_E_VOLUME_NOT_FOUND);
        }
        else
        {
            // error opening the directoty
            NANOCLR_SET_AND_LEAVE(CLR_E_DIRECTORY_NOT_FOUND);
        }
    }
    else
    {
        // open file
        operationResult = f_open(&file, filePath, FA_WRITE);

        if(operationResult == FR_OK)
        {
            operationResult = f_lseek(&file, position);     // Change to actual position
            if(operationResult != FR_OK)
            {
                // failed to change position
                NANOCLR_SET_AND_LEAVE(CLR_E_INDEX_OUT_OF_RANGE);
            }

            // file opened succesfully
            UINT written = 0;
            operationResult = f_write(&file, buffer, length, &written);
            if(operationResult != FR_OK)
            {
                // Failed to write to file
                NANOCLR_SET_AND_LEAVE(CLR_E_FILE_IO);
            }

            // OK to close it
            f_close(&file);
        }
        else
        {
            // failed to create the file
            NANOCLR_SET_AND_LEAVE(CLR_E_FILE_IO);
        }
    }

    NANOCLR_CLEANUP();

    // free buffer memory, if allocated
    if(filePath != NULL)
    {
        platform_free(filePath);
    }
}

signed __int64 NativeFileStream::GetLengthNative( CLR_RT_HeapBlock* pMngObj, const char* param0, const char* param1, HRESULT &hr )
{
    signed __int64 length = 0;

    (void)hr;
    (void)pMngObj;

    const char* workingPath = param0;
    const char* fileName = param1;

    FIL             file; 
    FRESULT         operationResult;
    char*           filePath = NULL;

    // setup file path
    filePath = (char*)platform_malloc(2 * FF_LFN_BUF + 1);

    // sanity check for successfull malloc
    if(filePath == NULL)
    {
        // failed to allocate memory
        NANOCLR_SET_AND_LEAVE(CLR_E_OUT_OF_MEMORY);
    }

    // clear working buffer
    memset(filePath, 0, 2 * FF_LFN_BUF + 1);

    // compose file path
    CombinePathAndName(filePath, workingPath, fileName);

    // change directory
    operationResult = f_chdir(workingPath);

    if(operationResult != FR_OK)
    {
        if(operationResult == FR_INVALID_DRIVE)
        {
            // invalid drive
            NANOCLR_SET_AND_LEAVE(CLR_E_VOLUME_NOT_FOUND);
        }
        else
        {
            // error opening the directoty
            NANOCLR_SET_AND_LEAVE(CLR_E_DIRECTORY_NOT_FOUND);
        }
    }
    else
    {
        // open file
        operationResult = f_open(&file, filePath, FA_OPEN_EXISTING);

        if(operationResult == FR_OK)
        {
            // file opened succesfully
            length = f_size(&file);

            // OK to close it
            f_close(&file);
        }
        else
        {
            // failed to create the file
            NANOCLR_SET_AND_LEAVE(CLR_E_FILE_IO);
        }
    }

    NANOCLR_CLEANUP();

    // free buffer memory, if allocated
    if(filePath != NULL)
    {
        platform_free(filePath);
    }

    return length;
}
