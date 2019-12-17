#ifndef _crypto_sign_keywrapper_h_
#define _crypto_sign_keywrapper_h_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t
crypto_sign_ed25519_compute_keypair(
        uint8_t *pk,
        uint8_t *sk);

#ifdef __cplusplus
}
#endif

#endif
