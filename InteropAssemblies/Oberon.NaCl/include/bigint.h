/*
 * Mountaineer Prime NaCl Library
 * Copyright: Oberon microsystems inc.
 * Based on NaCl by D. J. Bernstein
 * and avrnacl by Michael Hutter & Peter Schwabe.
 */


#ifndef BIGINT_H
#define BIGINT_H


typedef unsigned long uint32;
typedef unsigned long long uint64;


__inline uint32 load_littleendian(const unsigned char *x)
{
    /* Cortex-M4 allows dealigned word access */
    return *(uint32*)x;
}

__inline void store_littleendian(unsigned char *x, uint32 u)
{
    /* Cortex-M4 allows dealigned word access */
    *(uint32*)x = u;
}


// extern uint32 load_littleendian(const unsigned char *x);

// extern void store_littleendian(unsigned char *x, uint32 u);

extern void bigint_add128(uint32 r[4], const uint32 a[4], const uint32 b[4]);

extern char bigint_add256(uint32 r[8], const uint32 a[8], const uint32 b[8]);

extern char bigint_sub256(uint32 r[8], const uint32 a[8], const uint32 b[8]);

extern void bigint_mul128(uint32 r[8], const uint32 a[4], const uint32 b[4]);

extern void bigint_mul256(uint32 r[16], const uint32 a[8], const uint32 b[8]);

extern void bigint_cmov256(uint32 r[8], const uint32 x[8], uint32 b);


extern void freeze1305(uint32 h[5]);

extern void addmulmod1305(uint32 h[5],const uint32 r[4],const uint32 a[5]);


extern void salsa20rounds(uint32 x[16]);

extern void chacha20rounds(unsigned int x[16]);

#endif
