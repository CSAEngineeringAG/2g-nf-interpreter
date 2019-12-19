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
#include "System_IO_FileSystem_System_IO_NativeFile.h"

#include <ff.h>
#include <nanoHAL_Windows_Storage.h>

using namespace System::IO;

void CombinePathAndName2(char * outpath, const char * path1, const char * path2)
{
	strcat(outpath, path1);
	
	// Add "\" to path if required
	if (outpath[hal_strlen_s(outpath) - 1] != '\\')
	{
		strcat(outpath, "\\");
	}
	strcat(outpath, path2);
}

bool NativeFile::ExistsNative( const char* param0, const char* param1, HRESULT &hr )
{
    (void)hr;

    const char* workingPath = param0;
    const char* fileName = param1;
    bool exists = false; 

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
    CombinePathAndName2(filePath, workingPath, fileName);

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
        FILINFO fno; 

        operationResult = f_stat(filePath, &fno);

        if(operationResult == FR_OK)
        {
            exists = true;
        }
        else if (operationResult == FR_NO_FILE)
        {
            exists = false;
        }
        else
        {
            exists = false;
        }
    }

    NANOCLR_CLEANUP();

    // free buffer memory, if allocated
    if(filePath != NULL)
    {
        platform_free(filePath);
    }

    return exists;
}

void NativeFile::MoveNative( const char* param0, const char* param1, HRESULT &hr )
{
    (void)hr;

    const char* filePathSrc = param0;
    const char* filePathDest = param1;

    // rename file
    FRESULT operationResult = f_rename(filePathSrc, filePathDest);

    if (operationResult == FR_INVALID_NAME)
    {
        // invalid path
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }
    else if (operationResult != FR_OK)
    {
        // folder doesn't exist
        NANOCLR_SET_AND_LEAVE(CLR_E_DIRECTORY_NOT_FOUND);
    }
    
    NANOCLR_CLEANUP();
}

void NativeFile::DeleteNative( const char* param0, HRESULT &hr )
{
    (void)hr;
    
    const char* filePath = param0;

    // Delete file
    FRESULT operationResult = f_unlink(filePath);

    if (operationResult != FR_OK)
    {
        // file doesn't exist
        NANOCLR_SET_AND_LEAVE(CLR_E_FILE_NOT_FOUND);
    }

    NANOCLR_CLEANUP();
}

unsigned char NativeFile::GetAttributesNative( const char* param0, HRESULT &hr )
{
    (void)hr;
    
    const char* filePath = param0;
    unsigned char attributes = 0xFF;

    FILINFO fno;

    // Get infos about file
    FRESULT operationResult = f_stat(filePath, &fno);

    if(operationResult == FR_OK)
    {
        attributes = fno.fattrib;
    }
    else if (operationResult == FR_NO_FILE)
    {
        // File/Directory not found
    }
    else
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_FILE_IO);
    }
    
    NANOCLR_CLEANUP();

    return attributes;
}

void NativeFile::SetAttributesNative( const char* param0, unsigned char param1, HRESULT &hr )
{
    (void)hr;
    
    const char* filePath = param0;
    unsigned char attributes = param1;

    // Get infos about file
    FRESULT operationResult = f_chmod(filePath, attributes, 0xFF);

    if(operationResult != FR_OK)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_OPERATION);
    }

    NANOCLR_CLEANUP();
}

