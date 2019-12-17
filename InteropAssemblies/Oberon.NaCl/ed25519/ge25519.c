/*
 * Mountaineer Prime NaCl Library
 * Copyright: Oberon microsystems inc.
 * Based on NaCl by D. J. Bernstein
 * and avrnacl by Michael Hutter & Peter Schwabe.
 */


#include "include/fe25519.h"
#include "sc25519.h"
#include "ge25519.h"


/* 
 * Arithmetic on the twisted Edwards curve -x^2 + y^2 = 1 + dx^2y^2 
 * with d = -(121665/121666) = 37095705934669439343138083508754565189542113879843219016388785533085940283555
 * Base point: (15112221349535400772501151409588531511454012693041857206046113283949847762202,46316835694926478169428394003475163141307993866256225615783033603165251855960);
 */

/* d */
static const fe25519 ge25519_ecd = {{0x135978a3, 0x75eb4dca, 0x4141d8ab, 0x00700a4d, 0x7779e898, 0x8cc74079, 0x2b6ffe73, 0x52036cee}};
/* 2*d */
static const fe25519 ge25519_ec2d = {{0x26b2f159, 0xebd69b94, 0x8283b156, 0x00e0149a, 0xeef3d130, 0x198e80f2, 0x56dffce7, 0x2406d9dc}};
/* sqrt(-1) */
static const fe25519 ge25519_sqrtm1 = {{0x4a0ea0b0, 0xc4ee1b27, 0xad2fe478, 0x2f431806, 0x3dfbd7a7, 0x2b4d0099, 0x4fc1df0b, 0x2b832480}};


#define ge25519_p3 ge25519

typedef struct
{
  fe25519 x;
  fe25519 z;
  fe25519 y;
  fe25519 t;
} ge25519_p1p1;

typedef struct
{
  fe25519 x;
  fe25519 y;
  fe25519 z;
} ge25519_p2;

typedef struct
{
  fe25519 x;
  fe25519 y;
} ge25519_aff;


const ge25519 ge25519_base = {
    {{0x8f25d51a, 0xc9562d60, 0x9525a7b2, 0x692cc760, 0xfdd6dc5c, 0xc0a4e231, 0xcd6e53fe, 0x216936d3}}, 
    {{0x66666658, 0x66666666, 0x66666666, 0x66666666, 0x66666666, 0x66666666, 0x66666666, 0x66666666}}, 
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}}, 
    {{0xa5b7dda3, 0x6dde8ab3, 0x775152f5, 0x20f09f80, 0x64abe37d, 0x66ea4e8e, 0xd78b7665, 0x67875f0f}}
};


/* Multiples of the base point in affine representation */
static const ge25519_aff ge25519_base_multiples_affine[9] = {
    {{{0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}}, 
     {{0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}}}, 
    {{{0x8f25d51a, 0xc9562d60, 0x9525a7b2, 0x692cc760, 0xfdd6dc5c, 0xc0a4e231, 0xcd6e53fe, 0x216936d3}}, 
     {{0x66666658, 0x66666666, 0x66666666, 0x66666666, 0x66666666, 0x66666666, 0x66666666, 0x66666666}}}, 
    {{{0x2843ce0e, 0x83c5a14e, 0x15d7a45f, 0x080d8e45, 0x1833e7ac, 0x3d043b7d, 0x9f5a046c, 0x36ab384c}}, 
     {{0x6af8a3c9, 0x0e5f46ae, 0x64385156, 0x97390f51, 0xc9a21f56, 0x1da25ee8, 0x092329c2, 0x2260cdf3}}}, 
    {{{0xd3f8e25c, 0xac62485f, 0x81624886, 0x63439819, 0x3edac83a, 0x1ff4ae74, 0x22928f49, 0x67ae9c4a}}, 
     {{0x78f5b4d4, 0x02c36848, 0x67240304, 0x9f16ec17, 0x60269ef7, 0xa126a18e, 0x77ee69ab, 0x1267b1d1}}}, 
    {{{0xc4c9f870, 0x493aa657, 0x93ce1547, 0x1a739ec1, 0x7a3520f9, 0x8325d4b8, 0x56cff146, 0x203da8db}}, 
     {{0xca32112f, 0xdf38ab61, 0xea2f0ff0, 0x4cf22832, 0x80d5716c, 0x470eb885, 0xcb1595e1, 0x47d0e827}}}, 
    {{{0x322ef233, 0x91409cc0, 0x3e1be1a5, 0x5c2819f9, 0xd12da5de, 0xfcef7cf7, 0xade3587b, 0x49fda73e}}, 
     {{0xd676c8ed, 0x10d21f83, 0x89430b5d, 0x31282eca, 0x89924666, 0xe02c6e14, 0x98feae6f, 0x5f4825b2}}}, 
    {{{0x7dcbf23d, 0x783a741a, 0x6c7b4427, 0xa1e59982, 0xdd0a29be, 0x62aeacc0, 0x7a45601c, 0x4c9797ba}}, 
     {{0xf9497ef4, 0xc1d27ad0, 0x944d6b60, 0xf9417c06, 0xfd4f7d77, 0x1db709a7, 0x2886d8a1, 0x054de3fc}}}, 
    {{{0xf50e4107, 0x5855981a, 0xbbf1ce95, 0x83e809f3, 0x4b1d8107, 0xe9e3ee19, 0xfcf4bd4e, 0x14568685}}, 
     {{0x9f4062b8, 0x12c4c4b5, 0xf7abf23d, 0xf0882b46, 0xdd36ad41, 0x87ce6468, 0x2b47d52f, 0x31c563e3}}}, 
    {{{0x08a584c8, 0x3b87fdbc, 0x80698b99, 0xeb3ac67b, 0xf84ecf93, 0x42862d5c, 0x97d771b6, 0x6742e15f}}, 
     {{0xfc37b9b4, 0x1e2f5ba9, 0x621ee493, 0x81783cfc, 0x668af38f, 0x6ead6f09, 0xc9e57379, 0x21d30600}}}
};

static void p1p1_to_p2(ge25519_p2 *r, const ge25519_p1p1 *p)
{
  fe25519_mul(&r->x, &p->x, &p->t);
  fe25519_mul(&r->y, &p->y, &p->z);
  fe25519_mul(&r->z, &p->z, &p->t);
}

static void p1p1_to_p3(ge25519_p3 *r, const ge25519_p1p1 *p)
{
  p1p1_to_p2((ge25519_p2 *)r, p);
  fe25519_mul(&r->t, &p->x, &p->y);
}

static void ge25519_mixadd2(ge25519_p3 *r, const ge25519_aff *q)
{
  fe25519 a,b,t1,t2,c,d,e,f,g,h,qt;
  fe25519_mul(&qt, &q->x, &q->y);
  fe25519_sub(&a, &r->y, &r->x); /* A = (Y1-X1)*(Y2-X2) */
  fe25519_add(&b, &r->y, &r->x); /* B = (Y1+X1)*(Y2+X2) */
  fe25519_sub(&t1, &q->y, &q->x);
  fe25519_add(&t2, &q->y, &q->x);
  fe25519_mul(&a, &a, &t1);
  fe25519_mul(&b, &b, &t2);
  fe25519_sub(&e, &b, &a); /* E = B-A */
  fe25519_add(&h, &b, &a); /* H = B+A */
  fe25519_mul(&c, &r->t, &qt); /* C = T1*k*T2 */
  fe25519_mul(&c, &c, &ge25519_ec2d);
  fe25519_add(&d, &r->z, &r->z); /* D = Z1*2 */
  fe25519_sub(&f, &d, &c); /* F = D-C */
  fe25519_add(&g, &d, &c); /* G = D+C */
  fe25519_mul(&r->x, &e, &f);
  fe25519_mul(&r->y, &h, &g);
  fe25519_mul(&r->z, &g, &f);
  fe25519_mul(&r->t, &e, &h);
}

static void add_p1p1(ge25519_p1p1 *r, const ge25519_p3 *p, const ge25519_p3 *q)
{
  fe25519 a, b, c, d, t;
  
  fe25519_sub(&a, &p->y, &p->x); /* A = (Y1-X1)*(Y2-X2) */
  fe25519_sub(&t, &q->y, &q->x);
  fe25519_mul(&a, &a, &t);
  fe25519_add(&b, &p->x, &p->y); /* B = (Y1+X1)*(Y2+X2) */
  fe25519_add(&t, &q->x, &q->y);
  fe25519_mul(&b, &b, &t);
  fe25519_mul(&c, &p->t, &q->t); /* C = T1*k*T2 */
  fe25519_mul(&c, &c, &ge25519_ec2d);
  fe25519_mul(&d, &p->z, &q->z); /* D = Z1*2*Z2 */
  fe25519_add(&d, &d, &d);
  fe25519_sub(&r->x, &b, &a); /* E = B-A */
  fe25519_sub(&r->t, &d, &c); /* F = D-C */
  fe25519_add(&r->z, &d, &c); /* G = D+C */
  fe25519_add(&r->y, &b, &a); /* H = B+A */
}

/* See http://www.hyperelliptic.org/EFD/g1p/auto-twisted-extended-1.html#doubling-dbl-2008-hwcd */
static void dbl_p1p1(ge25519_p1p1 *r, const ge25519_p2 *p)
{
  fe25519 a,b,c,d;
  fe25519_square(&a, &p->x);
  fe25519_square(&b, &p->y);
  fe25519_square(&c, &p->z);
  fe25519_add(&c, &c, &c);
  fe25519_neg(&d, &a);

  fe25519_add(&r->x, &p->x, &p->y);
  fe25519_square(&r->x, &r->x);
  fe25519_sub(&r->x, &r->x, &a);
  fe25519_sub(&r->x, &r->x, &b);
  fe25519_add(&r->z, &d, &b);
  fe25519_sub(&r->t, &r->z, &c);
  fe25519_sub(&r->y, &d, &b);
}

static void choose_t(ge25519_aff *t, signed char b)
{
  fe25519 v;
  unsigned char u;
  signed char mask = (unsigned char)b >> 7;
  mask = -mask;
  u = (b + mask) ^ mask; /* abs(b) */
  *t = ge25519_base_multiples_affine[u];
  
  fe25519_neg(&v, &t->x);
  fe25519_cmov(&t->x, &v, (unsigned char)b >> 7);
}

static void setneutral(ge25519 *r)
{
  fe25519_setzero(&r->x);
  fe25519_setone(&r->y);
  fe25519_setone(&r->z);
  fe25519_setzero(&r->t);
}

/* ********************************************************************
 *                    EXPORTED FUNCTIONS
 ******************************************************************** */

/* return 0 on success, -1 otherwise */
int ge25519_unpackneg_vartime(ge25519_p3 *r, const unsigned char p[32])
{
  fe25519 t, chk, num, den, den2, den4, den6;
  unsigned char par = p[31] >> 7;
  fe25519_setone(&r->z);
  fe25519_unpack(&r->y, p); 
  fe25519_square(&num, &r->y); /* x = y^2 */
  fe25519_mul(&den, &num, &ge25519_ecd); /* den = dy^2 */
  fe25519_sub(&num, &num, &r->z); /* x = y^2-1 */
  fe25519_add(&den, &r->z, &den); /* den = dy^2+1 */

  /* Computation of sqrt(num/den) */
  /* 1.: computation of num^((p-5)/8)*den^((7p-35)/8) = (num*den^7)^((p-5)/8) */
  fe25519_square(&den2, &den);
  fe25519_square(&den4, &den2);
  fe25519_mul(&den6, &den4, &den2);
  fe25519_mul(&t, &den6, &num);
  fe25519_mul(&t, &t, &den);
  fe25519_power(&t, &t, 0); /* t ^ 2^252-3 */

  /* 2. computation of r->x = t * num * den^3 */
  fe25519_mul(&t, &t, &num);
  fe25519_mul(&t, &t, &den);
  fe25519_mul(&t, &t, &den);
  fe25519_mul(&r->x, &t, &den);

  /* 3. Check whether sqrt computation gave correct result, multiply by sqrt(-1) if not: */
  fe25519_square(&chk, &r->x);
  fe25519_mul(&chk, &chk, &den);
  if (!fe25519_iseq_vartime(&chk, &num))
    fe25519_mul(&r->x, &r->x, &ge25519_sqrtm1);

  /* 4. Now we have one of the two square roots, except if input was not a square */
  fe25519_square(&chk, &r->x);
  fe25519_mul(&chk, &chk, &den);
  if (!fe25519_iseq_vartime(&chk, &num))
    return -1;

  /* 5. Choose the desired square root according to parity: */
  if(fe25519_getparity(&r->x) != (1-par))
    fe25519_neg(&r->x, &r->x);

  fe25519_mul(&r->t, &r->x, &r->y);
  return 0;
}

void ge25519_pack(unsigned char r[32], const ge25519_p3 *p)
{
  fe25519 tx, ty, zi;
  fe25519_power(&zi, &p->z, 1); /* invert */
  fe25519_mul(&tx, &p->x, &zi);
  fe25519_mul(&ty, &p->y, &zi);
  fe25519_pack(r, &ty);
  r[31] ^= fe25519_getparity(&tx) << 7;
}

/* computes [s1]p1 + [s2]p2 */
void ge25519_double_scalarmult_vartime(ge25519_p3 *r, const ge25519_p3 *p1, const sc25519 *s1, const sc25519 *s2)
{
    signed int i;
    ge25519_p1p1 tp1p1;
    ge25519_p3 pre[16];
    unsigned char b[127];
    ge25519 p2;

    for (i=0;i<8; i++) {
        p2.x.w[i]=ge25519_base.x.w[i];
        p2.y.w[i]=ge25519_base.y.w[i];
        p2.z.w[i]=ge25519_base.z.w[i];
        p2.t.w[i]=ge25519_base.t.w[i];
    }

    /* precomputation                                                        s2 s1 */
    setneutral(pre);                                                      /* 00 00 */
    pre[1] = *p1;                                                         /* 00 01 */
    dbl_p1p1(&tp1p1,(ge25519_p2 *)p1);      p1p1_to_p3( &pre[2], &tp1p1); /* 00 10 */
    add_p1p1(&tp1p1,&pre[1], &pre[2]);      p1p1_to_p3( &pre[3], &tp1p1); /* 00 11 */
    pre[4] = p2;                                                          /* 01 00 */
    add_p1p1(&tp1p1,&pre[1], &pre[4]);      p1p1_to_p3( &pre[5], &tp1p1); /* 01 01 */
    add_p1p1(&tp1p1,&pre[2], &pre[4]);      p1p1_to_p3( &pre[6], &tp1p1); /* 01 10 */
    add_p1p1(&tp1p1,&pre[3], &pre[4]);      p1p1_to_p3( &pre[7], &tp1p1); /* 01 11 */
    dbl_p1p1(&tp1p1,(ge25519_p2 *)&p2);     p1p1_to_p3( &pre[8], &tp1p1); /* 10 00 */
    add_p1p1(&tp1p1,&pre[1], &pre[8]);      p1p1_to_p3( &pre[9], &tp1p1); /* 10 01 */
    dbl_p1p1(&tp1p1,(ge25519_p2 *)&pre[5]); p1p1_to_p3(&pre[10], &tp1p1); /* 10 10 */
    add_p1p1(&tp1p1,&pre[3], &pre[8]);      p1p1_to_p3(&pre[11], &tp1p1); /* 10 11 */
    add_p1p1(&tp1p1,&pre[4], &pre[8]);      p1p1_to_p3(&pre[12], &tp1p1); /* 11 00 */
    add_p1p1(&tp1p1,&pre[1],&pre[12]);      p1p1_to_p3(&pre[13], &tp1p1); /* 11 01 */
    add_p1p1(&tp1p1,&pre[2],&pre[12]);      p1p1_to_p3(&pre[14], &tp1p1); /* 11 10 */
    add_p1p1(&tp1p1,&pre[3],&pre[12]);      p1p1_to_p3(&pre[15], &tp1p1); /* 11 11 */

    sc25519_2interleave2(b,s1,s2);

    /* scalar multiplication */
    *r = pre[b[126]];
    for(i=125;i>=0;i--)
    {
        dbl_p1p1(&tp1p1, (ge25519_p2 *)r);
        p1p1_to_p2((ge25519_p2 *) r, &tp1p1);
        dbl_p1p1(&tp1p1, (ge25519_p2 *)r);
        if(b[i]!=0)
        {
            p1p1_to_p3(r, &tp1p1);
            add_p1p1(&tp1p1, r, &pre[b[i]]);
        }
        if(i != 0) p1p1_to_p2((ge25519_p2 *)r, &tp1p1);
        else p1p1_to_p3(r, &tp1p1);
    }
}

void ge25519_scalarmult_base(ge25519_p3 *r, const sc25519 *s)
{
  signed char b[64];
  signed int i;       //1 byte
  ge25519_aff t;       //64 bytes
  ge25519_p1p1 tp1p1;  //128 bytes
  sc25519_window4(b,s);
  
  choose_t((ge25519_aff *)r, b[63]);
  fe25519_setone(&r->z);
  fe25519_mul(&r->t,&r->x,&r->y);

  for(i=62;i>=0;i--)
  {
    dbl_p1p1(&tp1p1, (ge25519_p2 *)r);
    p1p1_to_p2((ge25519_p2 *)r, &tp1p1);
    dbl_p1p1(&tp1p1, (ge25519_p2 *)r);
    p1p1_to_p2((ge25519_p2 *)r, &tp1p1);
    dbl_p1p1(&tp1p1, (ge25519_p2 *)r);
    p1p1_to_p2((ge25519_p2 *)r, &tp1p1);
    dbl_p1p1(&tp1p1, (ge25519_p2 *)r);
    p1p1_to_p3(r, &tp1p1);

    choose_t(&t, b[i]);
    ge25519_mixadd2(r, &t);
  }  
}
