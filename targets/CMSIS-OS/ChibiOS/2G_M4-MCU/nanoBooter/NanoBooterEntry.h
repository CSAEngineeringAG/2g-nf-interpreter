
#ifndef __NANOBOOTERENTRY_H__
#define __NANOBOOTERENTRY_H__

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
// Destination  - the address the header should be decompressed to 
// Compressed   - the size of the compressed executable 
// Uncompressed - the size of the uncompressed executable 
////////////////////////////////////////////////////////////////////////////////
struct CompressedImage_Header
{
    char* Destination;
    int   Compressed;
    int   Uncompressed;
};

////////////////////////////////////////////////////////////////////////////////
// The WaitForNanoBooterUpload method was designed to allow porting kit partners
// to define how/when tinybooter mode is entered as well as configure default
// timeout values.  
////////////////////////////////////////////////////////////////////////////////
void WaitForNanoBooterUpload();

#ifdef __cplusplus
}
#endif

#endif /* __NANOBOOTERENTRY_H__ */