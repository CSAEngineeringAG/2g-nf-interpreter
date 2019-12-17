#ifndef FE25519_H
#define FE25519_H

#include "bigint.h"

#define fe25519              crypto_sign_ed25519_ref_fe25519
#define fe25519_freeze       crypto_sign_ed25519_ref_fe25519_freeze
#define fe25519_unpack       crypto_sign_ed25519_ref_fe25519_unpack
#define fe25519_pack         crypto_sign_ed25519_ref_fe25519_pack
#define fe25519_iszero       crypto_sign_ed25519_ref_fe25519_iszero
#define fe25519_iseq_vartime crypto_sign_ed25519_ref_fe25519_iseq_vartime
#define fe25519_cmov         crypto_sign_ed25519_ref_fe25519_cmov
#define fe25519_setone       crypto_sign_ed25519_ref_fe25519_setone
#define fe25519_setzero      crypto_sign_ed25519_ref_fe25519_setzero
#define fe25519_neg          crypto_sign_ed25519_ref_fe25519_neg
#define fe25519_getparity    crypto_sign_ed25519_ref_fe25519_getparity
#define fe25519_add          crypto_sign_ed25519_ref_fe25519_add
#define fe25519_sub          crypto_sign_ed25519_ref_fe25519_sub
#define fe25519_mul          crypto_sign_ed25519_ref_fe25519_mul
#define fe25519_mul121666    crypto_sign_ed25519_ref_fe25519_mul121666
#define fe25519_square       crypto_sign_ed25519_ref_fe25519_square
#define fe25519_power        crypto_sign_ed25519_ref_fe25519_power

typedef struct 
{
  uint32 w[8];
}
fe25519;

void fe25519_freeze(fe25519 *r);

void fe25519_unpack(fe25519 *r, const unsigned char x[32]);

void fe25519_pack(unsigned char r[32], const fe25519 *x);

int fe25519_iszero(const fe25519 *x);

int fe25519_iseq_vartime(const fe25519 *x, const fe25519 *y);

void fe25519_cmov(fe25519 *r, const fe25519 *x, unsigned char b);

void fe25519_setone(fe25519 *r);

void fe25519_setzero(fe25519 *r);

void fe25519_neg(fe25519 *r, const fe25519 *x);

unsigned char fe25519_getparity(const fe25519 *x);

void fe25519_add(fe25519 *r, const fe25519 *x, const fe25519 *y);

void fe25519_sub(fe25519 *r, const fe25519 *x, const fe25519 *y);

void fe25519_mul(fe25519 *r, const fe25519 *x, const fe25519 *y);

void fe25519_mul121666(fe25519 *r, const fe25519 *x);

void fe25519_square(fe25519 *r, const fe25519 *x);

void fe25519_power(fe25519 *r, const fe25519 *x, int invert);

#endif
