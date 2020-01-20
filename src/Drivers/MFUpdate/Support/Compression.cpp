#include <Compression.h>

#define WINSIZE  4096

#define LENGTH(x) ((((x) & 0x0F)) + 3)
#define OFFSET(x1, x2) ((((((x2 & 0xF0) >> 4) * 0x0100) + x1) & 0x0FFF) + 0x0010)

#define FAKE2REAL_POS(x)   ((x) & (WINSIZE - 1))
#define BITSET(byte, bit)  (((byte) & (1<<bit)) > 0)


int LZ77_Decompress( UINT8* inBuf, INT32 inSize, UINT8* outBuf, INT32 outSize, WRITE_MEMORY_FUNCT writeMem, READ_MEMORY_FUNCT readMem)
{
    UINT8* inBufEnd  = inBuf  + inSize;
    UINT8* outBufEnd = outBuf + outSize;
    INT32    counter;
    INT32    currPos = 0;
    UINT8  window[ WINSIZE ];

    for(counter = 0; counter < WINSIZE; counter ++)
    {
        window[ counter ] = ' ';
    }

//#define CHECKEDREAD(x)  if(inBuf  >= inBufEnd ) { DebugBreak(); return -1; } x
//#define CHECKEDWRITE(x) if(outBuf >= outBufEnd) { DebugBreak(); return -1; } x
#define CHECKEDREAD(x,y)  if(inBuf  >= inBufEnd ) return -1; if(readMem  != NULL) readMem ( (UINT32)y, 1, &x ); else  x = *y
#define CHECKEDWRITE(x,y) if(outBuf >= outBufEnd) return -1; if(writeMem != NULL) writeMem( (UINT32)x, 1, &y ); else *x =  y

    while(inBuf < inBufEnd)
    {
        //
        // Get BitMap and data following it.
        //
        UINT8 bitMap;
        
        CHECKEDREAD(bitMap, inBuf++);

        //
        // Go through and decode data.
        //
        for(counter = 0; counter < 8 && outBuf < outBufEnd; counter++)
        {
            //
            // It's a code, so decode it and copy the data.
            //
            if(!BITSET(bitMap, counter))
            {
                UINT8 byte1;
                UINT8 byte2;
                
                CHECKEDREAD(byte1, inBuf++);
                CHECKEDREAD(byte2, inBuf++);

                INT32 length = LENGTH(byte2);
                INT32 offset = OFFSET(byte1, byte2);

                //
                // Copy data from window.
                //
                while(length)
                {
                    byte1 = window[ FAKE2REAL_POS(offset) ];

                    window[ FAKE2REAL_POS(currPos) ] = byte1;

                    CHECKEDWRITE(outBuf++, byte1);

                    currPos++;
                    offset++; 
                    length--;
                }
            }
            else
            {
                UINT8 byte1;
                
                CHECKEDREAD(byte1, inBuf++);

                window[ FAKE2REAL_POS(currPos) ] = byte1;

                CHECKEDWRITE(outBuf++, byte1);

                currPos++;
            }
        }
    }

#undef CHECKEDREAD
#undef CHECKEDWRITE

    return 1;
}


int LZ77_Decompress( UINT8* inBuf, int inSize, UINT8* outBuf, int outSize)
{
    return LZ77_Decompress(inBuf, inSize, outBuf, outSize, NULL, NULL);
}
