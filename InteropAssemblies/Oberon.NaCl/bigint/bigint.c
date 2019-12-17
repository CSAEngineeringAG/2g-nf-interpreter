/*
 * Mountaineer Prime NaCl Library
 * Copyright: Oberon microsystems inc.
 * Based on NaCl by D. J. Bernstein
 * and avrnacl by Michael Hutter & Peter Schwabe.
 */


#include "include/fe25519.h"


//uint32 load_littleendian(const unsigned char *x)
//{
//    return
//     (uint32) (x[0])
//    | (((uint32) (x[1])) << 8)
//    | (((uint32) (x[2])) << 16)
//    | (((uint32) (x[3])) << 24);
//}

//void store_littleendian(unsigned char *x, uint32 u)
//{
//    x[0] = u; u >>= 8;
//    x[1] = u; u >>= 8;
//    x[2] = u; u >>= 8;
//    x[3] = u;
//}

void bigint_add128(uint32 r[4], const uint32 a[4], const uint32 b[4])
{
    unsigned int j;
    uint64 u;
    uint32 c = 0;
    for (j = 0;j < 4;++j) { u = (uint64)a[j] + b[j] + c; r[j] = u; c = u >> 32; }
}

char bigint_add256(uint32 r[8], const uint32 a[8], const uint32 b[8])
{
    unsigned int j;
    uint64 u;
    uint32 c = 0;
    for (j = 0;j < 8;++j) { u = (uint64)a[j] + b[j] + c; r[j] = u; c = u >> 32; }
    return c;
}

char bigint_sub256(uint32 r[8], const uint32 a[8], const uint32 b[8])
{
    unsigned int j;
    uint64 u;
    uint32 c = 0;
    for (j = 0;j < 8;++j) { u = (uint64)a[j] - b[j] - c; r[j] = u; c = -(u >> 32); }
    return c;
}

void bigint_mul128(uint32 r[8], const uint32 a[4], const uint32 b[4])
{
    unsigned int i, j;
    uint32 c;
    uint64 u;
    
    for (i = 0;i < 4;++i) r[i] = 0;
    
    for (i = 0; i < 4; i++) {
        c = 0;
        for (j = 0; j < 4; j++) {
            u = (uint64)a[i] * b[j] + r[i + j] + c;
            r[i + j] = u; c = u >> 32;
        }
        r[i + 4] = c;
    }
}

void bigint_mul256(uint32 r[16], const uint32 a[8], const uint32 b[8])
{
    unsigned int i, j;
    uint32 c;
    uint64 u;
    
    for (i = 0;i < 8;++i) r[i] = 0;
    
    for (i = 0; i < 8; i++) {
        c = 0;
        for (j = 0; j < 8; j++) {
            u = (uint64)a[i] * b[j] + r[i + j] + c;
            r[i + j] = u; c = u >> 32;
        }
        r[i + 8] = c;
    }
}

void bigint_cmov256(uint32 r[8], const uint32 x[8], uint32 b)
{
    unsigned int i;
    uint32 mask = -b;
    for(i=0;i<8;i++) 
        r[i] ^= mask & (x[i] ^ r[i]);
}


void fe25519_cmov(fe25519 *r, const fe25519 *x, unsigned char b)
{
    bigint_cmov256(r->w,x->w,b);
}

void fe25519_add(fe25519 *r, const fe25519 *x, const fe25519 *y)
{
    unsigned int j;
    uint64 u;
    uint32 c = 0;
    for (j = 0;j < 8;++j) { u = (uint64)x->w[j] + y->w[j] + c; r->w[j] = u; c = u >> 32; }
    c *= 38;
    for (j = 0;j < 8;++j) { u = (uint64)r->w[j] + c; r->w[j] = u; c = u >> 32; }
    c *= 38;
    r->w[0] += c;
}

void fe25519_sub(fe25519 *r, const fe25519 *x, const fe25519 *y)
{
    unsigned int j;
    uint64 u;
    uint32 c = 0;
    for (j = 0;j < 8;++j) { u = (uint64)x->w[j] - y->w[j] - c; r->w[j] = u; c = -(u >> 32); }
    c *= 38;
    for (j = 0;j < 8;++j) { u = (uint64)r->w[j] - c; r->w[j] = u; c = -(u >> 32); }
    c *= 38;
    r->w[0] -= c;
}

void fe25519_square(fe25519 *r, const fe25519 *x)
{
    fe25519_mul(r,x,x);
}

void fe25519_mul(fe25519 *r, const fe25519 *x, const fe25519 *y)
{
    unsigned int i, j;
    uint32 p[16]; /* full product */
    uint32 c;
    uint64 u;
    
    for (i = 0;i < 8;++i) p[i] = 0;
    
    for (i = 0; i < 8; i++) {
        c = 0;
        for (j = 0; j < 8; j++) {
            u = (uint64)x->w[i] * y->w[j] + p[i + j] + c;
            p[i + j] = u; c = u >> 32;
        }
        p[i + 8] = c;
    }
    
    /* reduce to 256 bit */
    c = 0;
    for (i = 0;i < 8;++i) {
        u = 38ull * p[i + 8] + p[i] + c;
        r->w[i] = u; c = u >> 32;
    }
    c *= 38;
    for (j = 0;j < 8;++j) { u = (uint64)r->w[j] + c; r->w[j] = u; c = u >> 32; }
    c *= 38;
    r->w[0] += c;
}

void fe25519_mul121666(fe25519 *r, const fe25519 *x)
{
    unsigned int i;
    uint64 u;
    uint32 c = 0;
    
    for (i = 0;i < 8;++i) {
        u = 121666ull * x->w[i] + c;
        r->w[i] = u; c = u >> 32;
    }
    
    /* reduce to 256 bit */
    c *= 38;
    for (i = 0;i < 8;++i) { u = (uint64)r->w[i] + c; r->w[i] = u; c = u >> 32; }
    c *= 38;
    r->w[0] += c;
}



/* reduction modulo 2^255-19 */
void fe25519_freeze(fe25519 *r)
{
    unsigned int j;
    uint64 u;
    uint32 c, d;
    d = (signed long)r->w[7] >> 31; // bit31 -> mask
    d &= 19; // r >= 2^255 ? 19 : 0
    r->w[7] &= 0x7FFFFFFF;
    c = d + 19;
    for (j = 0;j < 7;++j) { u = (uint64)r->w[j] + c; c = u >> 32; }
    c += r->w[7]; // high word of r + d + 19
    c = (signed long)c >> 31; // bit31 -> mask
    c &= 19; // r + d + 19 >= 2^255 ? 19 : 0
    c += d; // total increment (0 or 19 or 38)
    for (j = 0;j < 8;++j) { u = (uint64)r->w[j] + c; r->w[j] = u; c = u >> 32; }
    r->w[7] &= 0x7FFFFFFF;
}



/* reduction modulo 2^130-5 */
void freeze1305(uint32 h[5])
{
    unsigned int j;
    uint64 u;
    uint32 c;

    /* h < 2^130 */
    c = 5;
    for (j = 0;j < 4;++j) { u = (uint64)h[j] + c; c = u >> 32; }
    /* res[4].bit2 set => h >= p */
    c = ((h[4] + c) >> 2) * 5;
    for (j = 0;j < 4;++j) { u = (uint64)h[j] + c; h[j] = u; c = u >> 32; }
    h[4] = (h[4] + c) & 3;
    /* h < p */
}

void add130(uint32 h[5],const uint32 a[5])
{
  unsigned int j;
  uint64 u;
    uint32 c = 0;
  for (j = 0;j < 5;++j) { u = (uint64)h[j] + a[j] + c; h[j] = u; c = u >> 32; }
}


void mulmod1305(uint32 h[5],const uint32 r[5])
{
    uint32 hr[10], c, q;
    unsigned int i;
    unsigned int j;
    uint64 u;
    
    for (i = 0;i < 5;++i) hr[i] = 0;
    
    /* h,r < 2^231 */
    for (i = 0; i < 5; i++) {
        c = 0;
        for (j = 0; j < 5; j++) {
            u = (uint64)h[i] * r[j] + hr[i + j] + c;
            hr[i + j] = u; c = u >> 32;
        }
        hr[i + 5] = c; // c=0 if i=4
    }
    /* hr = h * r < 2^262 */
    
    /* first reduction: add (hr >> 144) * 5*2^14 to hr */
    c = 0;
    for (i = 0;i < 4;++i) {
        q = hr[i + 5] << 16 | hr[i + 4] >> 16;
        u = 0x14000ull * q + hr[i] + c;
        hr[i] = u; c = u >> 32;
    }
    hr[4] = (hr[4] & 0xFFFF) + c;
    /* hr < 2^145 */
    
    /* second reduction: add (hr[4] >> 2) * 5 to hr */
    c = 5 * (hr[4] >> 2); hr[4] &= 3;
    for (i = 0;i < 5;++i) {
    u = (uint64)hr[i] + c;
    hr[i] = u; c = u >> 32;
    }
    /* hr < 2 * p < 2^131 */
    
    for (i = 0;i < 5;++i) h[i] = hr[i];
}

/* h = (h + a) * r modulo 2^130-5 */
void addmulmod1305(uint32 h[5],const uint32 r[4],const uint32 a[5])
{
    uint32 hr[10], q;
    unsigned int i;
    unsigned int j;
    uint64 u;
    uint32 c = 0;
    for (i = 0;i < 5;++i) {
        u = (uint64)h[i] + a[i] + c; h[i] = u; c = u >> 32;
        hr[i] = 0;
    }
    
    /* h,r < 2^231 */
    for (i = 0; i < 5; i++) {
        c = 0;
        for (j = 0; j < 5; j++) {
            u = (uint64)h[i] * r[j] + hr[i + j] + c;
            hr[i + j] = u; c = u >> 32;
        }
        hr[i + 5] = c; // c=0 if i=4
    }
    /* hr = h * r < 2^262 */
    
    /* first reduction: add (hr >> 144) * 5*2^14 to hr */
    c = 0;
    for (i = 0;i < 4;++i) {
        q = hr[i + 5] << 16 | hr[i + 4] >> 16;
        u = 0x14000ull * q + hr[i] + c;
        hr[i] = u; c = u >> 32;
    }
    hr[4] = (hr[4] & 0xFFFF) + c;
    /* hr < 2^145 */
    
    /* second reduction: add (hr[4] >> 2) * 5 to hr */
    c = 5 * (hr[4] >> 2); hr[4] &= 3;
    for (i = 0;i < 5;++i) {
    u = (uint64)hr[i] + c;
    hr[i] = u; c = u >> 32;
    }
    /* hr < 2 * p < 2^131 */
    
    for (i = 0;i < 5;++i) h[i] = hr[i];
}


__inline uint32 rotate(uint32 u,int c)
{
  return (u << c) | (u >> (32 - c));
}

void salsa20rounds(uint32 x[16])
{
    int i;
    for (i = 10;i > 0;i--) {
         x[4] ^= rotate( x[0]+x[12], 7);
         x[8] ^= rotate( x[4]+ x[0], 9);
        x[12] ^= rotate( x[8]+ x[4],13);
         x[0] ^= rotate(x[12]+ x[8],18);
         x[9] ^= rotate( x[5]+ x[1], 7);
        x[13] ^= rotate( x[9]+ x[5], 9);
         x[1] ^= rotate(x[13]+ x[9],13);
         x[5] ^= rotate( x[1]+x[13],18);
        x[14] ^= rotate(x[10]+ x[6], 7);
         x[2] ^= rotate(x[14]+x[10], 9);
         x[6] ^= rotate( x[2]+x[14],13);
        x[10] ^= rotate( x[6]+ x[2],18);
         x[3] ^= rotate(x[15]+x[11], 7);
         x[7] ^= rotate( x[3]+x[15], 9);
        x[11] ^= rotate( x[7]+ x[3],13);
        x[15] ^= rotate(x[11]+ x[7],18);
         x[1] ^= rotate( x[0]+ x[3], 7);
         x[2] ^= rotate( x[1]+ x[0], 9);
         x[3] ^= rotate( x[2]+ x[1],13);
         x[0] ^= rotate( x[3]+ x[2],18);
         x[6] ^= rotate( x[5]+ x[4], 7);
         x[7] ^= rotate( x[6]+ x[5], 9);
         x[4] ^= rotate( x[7]+ x[6],13);
         x[5] ^= rotate( x[4]+ x[7],18);
        x[11] ^= rotate(x[10]+ x[9], 7);
         x[8] ^= rotate(x[11]+x[10], 9);
         x[9] ^= rotate( x[8]+x[11],13);
        x[10] ^= rotate( x[9]+ x[8],18);
        x[12] ^= rotate(x[15]+x[14], 7);
        x[13] ^= rotate(x[12]+x[15], 9);
        x[14] ^= rotate(x[13]+x[12],13);
        x[15] ^= rotate(x[14]+x[13],18);
    }
}

#define QUARTERROUND(a,b,c,d) \
  a += b; d = rotate(d ^ a, 16); \
  c += d; b = rotate(b ^ c, 12); \
  a += b; d = rotate(d ^ a,  8); \
  c += d; b = rotate(b ^ c,  7);

void chacha20rounds(unsigned int x[16])
{
    int i;
    for (i = 10;i > 0;i--) {
        QUARTERROUND( x[0], x[4], x[8],x[12])
        QUARTERROUND( x[1], x[5], x[9],x[13])
        QUARTERROUND( x[2], x[6],x[10],x[14])
        QUARTERROUND( x[3], x[7],x[11],x[15])
        QUARTERROUND( x[0], x[5],x[10],x[15])
        QUARTERROUND( x[1], x[6],x[11],x[12])
        QUARTERROUND( x[2], x[7], x[8],x[13])
        QUARTERROUND( x[3], x[4], x[9],x[14])
    }
}
