#ifndef _crypto_box_keywrapper_curve25519xsalsa20poly1305_h_
#define _crypto_box_keywrapper_curve25519xsalsa20poly1305_h_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t
crypto_box_curve25519xsalsa20poly1305_compute_keypair(
    uint8_t *pk,
    uint8_t *sk);

#ifdef __cplusplus
}
#endif

#endif
