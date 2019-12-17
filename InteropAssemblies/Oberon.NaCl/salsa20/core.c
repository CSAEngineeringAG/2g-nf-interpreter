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
    uint32 j0, j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12, j13, j14, j15;

    j0 = x[0] = load_littleendian(c + 0);
    j1 = x[1] = load_littleendian(k + 0);
    j2 = x[2] = load_littleendian(k + 4);
    j3 = x[3] = load_littleendian(k + 8);
    j4 = x[4] = load_littleendian(k + 12);
    j5 = x[5] = load_littleendian(c + 4);
    j6 = x[6] = load_littleendian(in + 0);
    j7 = x[7] = load_littleendian(in + 4);
    j8 = x[8] = load_littleendian(in + 8);
    j9 = x[9] = load_littleendian(in + 12);
    j10 = x[10] = load_littleendian(c + 8);
    j11 = x[11] = load_littleendian(k + 16);
    j12 = x[12] = load_littleendian(k + 20);
    j13 = x[13] = load_littleendian(k + 24);
    j14 = x[14] = load_littleendian(k + 28);
    j15 = x[15] = load_littleendian(c + 12);

    salsa20rounds(x);

    x[0] += j0;
    x[1] += j1;
    x[2] += j2;
    x[3] += j3;
    x[4] += j4;
    x[5] += j5;
    x[6] += j6;
    x[7] += j7;
    x[8] += j8;
    x[9] += j9;
    x[10] += j10;
    x[11] += j11;
    x[12] += j12;
    x[13] += j13;
    x[14] += j14;
    x[15] += j15;

    store_littleendian(out + 0,x[0]);
    store_littleendian(out + 4,x[1]);
    store_littleendian(out + 8,x[2]);
    store_littleendian(out + 12,x[3]);
    store_littleendian(out + 16,x[4]);
    store_littleendian(out + 20,x[5]);
    store_littleendian(out + 24,x[6]);
    store_littleendian(out + 28,x[7]);
    store_littleendian(out + 32,x[8]);
    store_littleendian(out + 36,x[9]);
    store_littleendian(out + 40,x[10]);
    store_littleendian(out + 44,x[11]);
    store_littleendian(out + 48,x[12]);
    store_littleendian(out + 52,x[13]);
    store_littleendian(out + 56,x[14]);
    store_littleendian(out + 60,x[15]);

    return 0;
}
