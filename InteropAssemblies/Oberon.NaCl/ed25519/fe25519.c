/*
 * Mountaineer Prime NaCl Library
 * Copyright: Oberon microsystems inc.
 * Based on NaCl by D. J. Bernstein
 * and avrnacl by Michael Hutter & Peter Schwabe.
 */


#include "include/fe25519.h"


void fe25519_setzero(fe25519 *r)
{
    unsigned int i;
    for(i=0;i<8;i++) r->w[i]=0;
}

void fe25519_setone(fe25519 *r) 
{
    unsigned int i;
    r->w[0] = 1;
    for(i=1;i<8;i++) r->w[i]=0;
}

unsigned char fe25519_getparity(const fe25519 *x)
{
  fe25519 t = *x;  
  fe25519_freeze(&t);
  return t.w[0] & 1;
}

int fe25519_iseq_vartime(const fe25519 *x, const fe25519 *y)
{
    unsigned int i;
    fe25519 t1 = *x;
    fe25519 t2 = *y;
    fe25519_freeze(&t1);
    fe25519_freeze(&t2);
    for(i=0;i<8;i++) {
        if(t1.w[i] != t2.w[i]) return 0;
    }
    return 1;
}

void fe25519_neg(fe25519 *r, const fe25519 *x) 
{
    fe25519 t;
    fe25519_setzero(&t);
    fe25519_sub(r, &t, x);
}

void fe25519_unpack(fe25519 *r, const unsigned char x[32])
{
    r->w[0] = load_littleendian(x);
    r->w[1] = load_littleendian(x + 4);
    r->w[2] = load_littleendian(x + 8);
    r->w[3] = load_littleendian(x + 12);
    r->w[4] = load_littleendian(x + 16);
    r->w[5] = load_littleendian(x + 20);
    r->w[6] = load_littleendian(x + 24);
    r->w[7] = load_littleendian(x + 28) & 0x7FFFFFFF;

}

/* Assumes input x being reduced below 2^255 */
void fe25519_pack(unsigned char r[32], const fe25519 *x)
{
    fe25519 y = *x;
    fe25519_freeze(&y);
    store_littleendian(r,      y.w[0]);
    store_littleendian(r + 4,  y.w[1]);
    store_littleendian(r + 8,  y.w[2]);
    store_littleendian(r + 12, y.w[3]);
    store_littleendian(r + 16, y.w[4]);
    store_littleendian(r + 20, y.w[5]);
    store_littleendian(r + 24, y.w[6]);
    store_littleendian(r + 28, y.w[7]);
}

/*
 * invert = 0: r = x^(2^252-3)  (part of sqrt)
 * invert = 1: r = x^(2^255-21) (1/x)
 */
void fe25519_power(fe25519 *r, const fe25519 *x, int invert)
{
    fe25519 z11;
    fe25519 z2_10_0;
    fe25519 z2_50_0;
    fe25519 t;
    unsigned int i;

    /* 2 */ fe25519_square(&z11,x);
    /* 4 */ fe25519_square(&t,&z11);
    /* 8 */ fe25519_square(&t,&t);
    /* 9 */ fe25519_mul(&z2_10_0,&t,x);
    /* 11 */ fe25519_mul(&z11,&z2_10_0,&z11);
    /* 22 */ fe25519_square(&t,&z11);
    /* 2^5 - 2^0 = 31 */ fe25519_mul(&z2_10_0,&t,&z2_10_0);

    /* 2^6 - 2^1 */ fe25519_square(&t,&z2_10_0);
    /* 2^10 - 2^5 */ for (i = 1;i < 5;i++) { fe25519_square(&t,&t); }
    /* 2^10 - 2^0 */ fe25519_mul(&z2_10_0,&t,&z2_10_0);

    /* 2^11 - 2^1 */ fe25519_square(&t,&z2_10_0);
    /* 2^20 - 2^10 */ for (i = 1;i < 10;i++) { fe25519_square(&t,&t); }
    /* 2^20 - 2^0 */ fe25519_mul(&z2_50_0,&t,&z2_10_0);

    /* 2^21 - 2^1 */ fe25519_square(&t,&z2_50_0);
    /* 2^40 - 2^20 */ for (i = 1;i < 20;i++) { fe25519_square(&t,&t); }
    /* 2^40 - 2^0 */ fe25519_mul(&t,&t,&z2_50_0);

    /* 2^41 - 2^1 */ fe25519_square(&t,&t);
    /* 2^50 - 2^10 */ for (i = 1;i < 10;i++) { fe25519_square(&t,&t); }
    /* 2^50 - 2^0 */ fe25519_mul(&z2_50_0,&t,&z2_10_0);

    /* 2^51 - 2^1 */ fe25519_square(&t,&z2_50_0);
    /* 2^100 - 2^50 */ for (i = 1;i < 50;i++) { fe25519_square(&t,&t); }
    /* 2^100 - 2^0 */ fe25519_mul(&z2_10_0,&t,&z2_50_0);

    /* 2^101 - 2^1 */ fe25519_square(&t,&z2_10_0);
    /* 2^200 - 2^100 */ for (i = 1;i < 100;i++) { fe25519_square(&t,&t); }
    /* 2^200 - 2^0 */ fe25519_mul(&t,&t,&z2_10_0);

    /* 2^201 - 2^1 */ fe25519_square(&t,&t);
    /* 2^250 - 2^50 */ for (i = 1;i < 50;i++) { fe25519_square(&t,&t); }
    /* 2^250 - 2^0 */ fe25519_mul(&t,&t,&z2_50_0);

    /* 2^251 - 2^1 */ fe25519_square(&t,&t);
    /* 2^252 - 2^2 */ fe25519_square(&t,&t);
    
    if (invert) {
        /* 2^253 - 2^3 */ fe25519_square(&t,&t);
        /* 2^254 - 2^4 */ fe25519_square(&t,&t);
        /* 2^255 - 2^5 */ fe25519_square(&t,&t);
        /* 2^255 - 21 */ fe25519_mul(r,&t,&z11);
    } else {
        /* 2^252 - 3 */ fe25519_mul(r,&t,x);
    }
}
