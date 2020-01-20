#include <nanoHAL.h>
#include <MFUpdate_decl.h>

typedef BOOL (*WRITE_MEMORY_FUNCT)( UINT32 Address, UINT32 NumBytes, const UINT8 * pSectorBuff );
typedef BOOL (*READ_MEMORY_FUNCT) ( UINT32 Address, UINT32 NumBytes, UINT8 * pSectorBuff );

int LZ77_Decompress( UINT8* inBuf, int inSize, UINT8* outBuf, int outSize );
int LZ77_Decompress( UINT8* inBuf, int inSize, UINT8* outBuf, int outSize, WRITE_MEMORY_FUNCT writeMem, READ_MEMORY_FUNCT readMem );
