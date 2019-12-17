/*
 * Mountaineer Prime NaCl Library
 * Copyright: Oberon microsystems inc.
 * Based on NaCl by D. J. Bernstein
 * and avrnacl by Michael Hutter & Peter Schwabe.
 */


#include "sc25519.h"


/*Arithmetic modulo the group order m = 2^252 +  27742317777372353535851937790883648493 = 7237005577332262213973186563042994240857116359379907606001950938285454250989 */
static const uint32 m[8] = {0x5cf5d3ed, 0x5812631a, 0xa2f79cd6, 0x14def9de, 0x00000000, 0x00000000, 0x00000000, 0x10000000};

void m_reduction_step(uint32* r, const uint32* a)
{
    /* A = a, a < 2^349 */
    uint32 t[8];
    uint32 h[4];
    uint32 c;
    /* h = a >> 252, h < 2^97 */
    h[3] = a[10] >> 28;
    h[2] = a[10] << 4 | a[9] >> 28;
    h[1] = a[9] << 4 | a[8] >> 28;
    h[0] = a[8] << 4 | a[7] >> 28;
    /* A = h * 2^252 + a & 2^252-1 */
    bigint_mul128(t, h, m);  /* t = h * m[3..0], t < 2^222 */
    t[7] = h[0] << 28;       /* = a[7] & 0xF0000000 */
    bigint_sub256(r, a, t);  /* r = r - h * m[3..0] - a[7] & 0xF0000000 = A - h * m */
    /* -2^222 < r < m */
    c = bigint_add256(t, r, m);
    bigint_cmov256(r, t, c); /* r < 0 => r += m */
    /* 0 <= r < m */
}

void m_reduction(uint32* r, uint32* a) 
{
    /* a < 2^512 */
    m_reduction_step(a + 6, a + 6);
    /* a < m * 2^192 < 2^445 */
    m_reduction_step(a + 3, a + 3);
    /* a < m * 2^96 < 2^349 */
    m_reduction_step(r, a);
    /* r < m */
}

void sc25519_from32bytes(sc25519 *r, const unsigned char x[32])
{
    unsigned int i;
    uint32 t[11];
    for(i=0;i<8;i++) 
        t[i] = load_littleendian(x + i * 4);
    t[8] = t[9] = t[10] = 0;
    m_reduction_step(r->w, t); /* last step only */
}

void sc25519_from64bytes(sc25519 *r, const unsigned char x[64])
{
    unsigned int i;
    uint32 t[17];
    for(i=0;i<16;i++) 
        t[i] = load_littleendian(x + i * 4);
    t[16] = 0;
    m_reduction(r->w, t);
}

void sc25519_to32bytes(unsigned char r[32], const sc25519 *x)
{
    unsigned int i;
    for(i=0;i<8;i++) 
        store_littleendian(r + i * 4, x->w[i]);
}

void sc25519_add(sc25519 *r, const sc25519 *x, const sc25519 *y)
{
    uint32 c;
    uint32 t[8];
    bigint_add256(r->w,x->w,y->w);
    c = bigint_sub256(t,r->w,m);
    bigint_cmov256(r->w,t,1-c);
}

void sc25519_mul(sc25519 *r, const sc25519 *x, const sc25519 *y)
{
    uint32 t[17];
    bigint_mul256(t, x->w, y->w);
    t[16] = 0;
    m_reduction(r->w, t);
}

void sc25519_window4(signed char r[64], const sc25519 *s)
{
    char carry;
    unsigned int i;
    unsigned char t[32];

    sc25519_to32bytes(t, s);
    for(i=0;i<32;i++)
    {
        r[2*i]   = t[i] & 15;
        r[2*i+1] = t[i] >> 4;
    }

    /* Making it signed */
    carry = 0;
    for(i=0;i<63;i++)
    {
        r[i] += carry;
        r[i+1] += r[i] >> 4;
        r[i] &= 15;
        carry = r[i] >> 3;
        r[i] -= carry << 4;
    }
    r[63] += carry;
}

void sc25519_2interleave2(unsigned char r[127], const sc25519 *s1, const sc25519 *s2)
{
    int i;
    unsigned char t1[32], t2[32];
    
    sc25519_to32bytes(t1, s1);
    sc25519_to32bytes(t2, s2);

    for(i=0;i<31;i++)
    {
        r[4*i]   = ( t1[i]       & 3) ^ (( t2[i]       & 3) << 2);
        r[4*i+1] = ((t1[i] >> 2) & 3) ^ (((t2[i] >> 2) & 3) << 2);
        r[4*i+2] = ((t1[i] >> 4) & 3) ^ (((t2[i] >> 4) & 3) << 2);
        r[4*i+3] = ((t1[i] >> 6) & 3) ^ (((t2[i] >> 6) & 3) << 2);
    }
    r[124] = ( t1[31]       & 3) ^ (( t2[31]       & 3) << 2);
    r[125] = ((t1[31] >> 2) & 3) ^ (((t2[31] >> 2) & 3) << 2);
    r[126] = ((t1[31] >> 4) & 3) ^ (((t2[31] >> 4) & 3) << 2);
}
