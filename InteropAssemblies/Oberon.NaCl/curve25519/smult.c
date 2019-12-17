/*
 * Mountaineer Prime NaCl Library
 * Copyright: Oberon microsystems inc.
 * Based on NaCl by D. J. Bernstein
 * and avrnacl by Michael Hutter & Peter Schwabe.
 */


#include "crypto_scalarmult.h"
#include "include/fe25519.h"


static void work_cswap(fe25519 *work, unsigned int b)
{
    fe25519 t;
    fe25519_setzero(&t);
    fe25519_cmov(&t, &work[1], b);
    fe25519_cmov(&work[1], &work[3], b);
    fe25519_cmov(&work[3], &t, b);
    fe25519_cmov(&t, &work[2], b);
    fe25519_cmov(&work[2], &work[4], b);
    fe25519_cmov(&work[4], &t, b);
}

static void ladderstep(fe25519 *work)
{
    fe25519 t1,t2,t3,t4,t5,t6,t7;
    fe25519 *x0 = work; 
    fe25519 *xp = work+1; 
    fe25519 *zp = work+2;
    fe25519 *xq = work+3;
    fe25519 *zq = work+4;
    fe25519_add(&t1, xp, zp);
    fe25519_sub(&t2, xp, zp); 
    fe25519_square(&t7, &t2);
    fe25519_square(&t6, &t1);
    fe25519_sub(&t5,&t6,&t7);
    fe25519_add(&t3, xq, zq); 
    fe25519_sub(&t4, xq, zq);
    fe25519_mul(&t2,&t3,&t2);
    fe25519_mul(&t3,&t4,&t1);
    fe25519_add(xq, &t3, &t2);
    fe25519_sub(zq, &t3, &t2);
    fe25519_square(xq, xq);
    fe25519_square(zq, zq);
    fe25519_mul(zq, zq, x0);
    fe25519_mul(xp, &t6, &t7);
    fe25519_mul121666(zp, &t5);
    fe25519_add(zp, zp, &t7);
    fe25519_mul(zp, zp, &t5);
}

static void mladder(fe25519 *xr, fe25519 *zr, const unsigned char s[32])
{
    fe25519 work[5];
    unsigned int bit, prevbit=0;
    unsigned int swap;
    signed int j;
    signed int i;

    work[0] = *xr;
    fe25519_setone(work+1);
    fe25519_setzero(work+2);
    work[3] = *xr;
    fe25519_setone(work+4);

    j = 6;
    for(i=31;i>=0;i--)
    {
        while(j >= 0)
        {
            bit = 1&(s[i]>>j);
            swap = bit ^ prevbit;
            prevbit = bit;
            work_cswap(work,swap);
            ladderstep(work);
            j -= 1;
        }
        j = 7;
    }
    *xr = work[1];
    *zr = work[2];
}

int crypto_scalarmult(unsigned char *r,
                      const unsigned char *s,
                      const unsigned char *p)
{
    unsigned char e[32];
    unsigned int i;
    fe25519 t;
    fe25519 z;

    for(i=0;i<32;i++) e[i] = s[i];
    e[0] &= 248;
    e[31] &= 127;
    e[31] |= 64; 

    fe25519_unpack(&t, p);
    mladder(&t, &z, e);
    fe25519_power(&z, &z, 1); /* invert */
    fe25519_mul(&t, &t, &z);
    fe25519_pack(r, &t);
    return 0;
}
