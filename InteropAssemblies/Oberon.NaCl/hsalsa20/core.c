/*
 * Mountaineer Prime NaCl Library
 * Copyright: Oberon microsystems inc.
 * Based on NaCl by D. J. Bernstein
 * and avrnacl by Michael Hutter & Peter Schwabe.
 */


#include "crypto_core.h"
#include "include/bigint.h"


int crypto_core(
          unsigned char *out,
    const unsigned char *in,
    const unsigned char *k,
    const unsigned char *c
)
{
    uint32 x[16];

    x[0] = load_littleendian(c + 0);
    x[1] = load_littleendian(k + 0);
    x[2] = load_littleendian(k + 4);
    x[3] = load_littleendian(k + 8);
    x[4] = load_littleendian(k + 12);
    x[5] = load_littleendian(c + 4);
    x[6] = load_littleendian(in + 0);
    x[7] = load_littleendian(in + 4);
    x[8] = load_littleendian(in + 8);
    x[9] = load_littleendian(in + 12);
    x[10] = load_littleendian(c + 8);
    x[11] = load_littleendian(k + 16);
    x[12] = load_littleendian(k + 20);
    x[13] = load_littleendian(k + 24);
    x[14] = load_littleendian(k + 28);
    x[15] = load_littleendian(c + 12);

    salsa20rounds(x);

    store_littleendian(out + 0,x[0]);
    store_littleendian(out + 4,x[5]);
    store_littleendian(out + 8,x[10]);
    store_littleendian(out + 12,x[15]);
    store_littleendian(out + 16,x[6]);
    store_littleendian(out + 20,x[7]);
    store_littleendian(out + 24,x[8]);
    store_littleendian(out + 28,x[9]);

    return 0;
}
