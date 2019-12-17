#include "include/crypto_sign_keywrapper.h"

#include "include/crypto_hash_sha512.h"

#include "ge25519.h"

int32_t
crypto_sign_ed25519_compute_keypair(
        uint8_t *pk,
        uint8_t *sk)
{
  sc25519 scsk;
  ge25519 gepk;
  unsigned char extsk[64];
  int i;

  crypto_hash_sha512(extsk, sk, 32);
  extsk[0] &= 248;
  extsk[31] &= 127;
  extsk[31] |= 64;

  sc25519_from32bytes(&scsk,extsk);
  
  ge25519_scalarmult_base(&gepk, &scsk);
  ge25519_pack(pk, &gepk);
  for(i=0;i<32;i++)
    sk[32 + i] = pk[i];
  return 0;
}

