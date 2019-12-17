/*
 * Mountaineer Prime NaCl Library
 * Copyright: Oberon microsystems inc.
 * Based on NaCl by D. J. Bernstein
 * and avrnacl by Michael Hutter & Peter Schwabe.
 */


#include "include/crypto_core_hsalsa20.h"
#include "include/crypto_stream_salsa20.h"
#include "crypto_stream.h"


static const unsigned char sigma[16] = "expand 32-byte k";

int crypto_stream_xor(
        unsigned char *c,
  const unsigned char *m,unsigned long mlen,
  const unsigned char *n,
  const unsigned char *k
)
{
  unsigned char subkey[32];
  crypto_core_hsalsa20(subkey,n,k,sigma);
  return crypto_stream_salsa20_xor(c,m,mlen,n + 16,subkey);
}
