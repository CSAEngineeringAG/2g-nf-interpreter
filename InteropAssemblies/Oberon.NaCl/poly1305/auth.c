/*
 * Mountaineer Prime NaCl Library
 * Copyright: Oberon microsystems inc.
 * Based on NaCl by D. J. Bernstein
 * and avrnacl by Michael Hutter & Peter Schwabe.
 */


#include "crypto_onetimeauth.h"
#include "include/bigint.h"


int crypto_onetimeauth(unsigned char *out,const unsigned char *in,unsigned long inlen,const unsigned char *k)
{
    unsigned int j;
    uint32 r[5];
    uint32 h[5];
    uint32 c[5];
    unsigned char cb[17];

    r[0] = load_littleendian(k)      & 0x0FFFFFFF;
    r[1] = load_littleendian(k + 4)  & 0x0FFFFFFC;
    r[2] = load_littleendian(k + 8)  & 0x0FFFFFFC;
    r[3] = load_littleendian(k + 12) & 0x0FFFFFFC;
    r[4] = 0;

    for (j = 0;j < 5;++j) h[j] = 0;

    while (inlen > 0) {
        for (j = 0;(j < 16) && (j < inlen);++j) cb[j] = in[j];
        cb[j] = 1;
        in += j; inlen -= j;
        while (j < 16) cb[++j] = 0;
        c[0] = load_littleendian(cb);
        c[1] = load_littleendian(cb + 4);
        c[2] = load_littleendian(cb + 8);
        c[3] = load_littleendian(cb + 12);
        c[4] = cb[16];
        addmulmod1305(h,r,c);
    }

    freeze1305(h); /* mod 2^130-5 */

    c[0] = load_littleendian(k + 16);
    c[1] = load_littleendian(k + 20);
    c[2] = load_littleendian(k + 24);
    c[3] = load_littleendian(k + 28);

    bigint_add128(h,h,c);

    store_littleendian(out,      h[0]);
    store_littleendian(out + 4,  h[1]);
    store_littleendian(out + 8,  h[2]);
    store_littleendian(out + 12, h[3]);
    return 0;
}
