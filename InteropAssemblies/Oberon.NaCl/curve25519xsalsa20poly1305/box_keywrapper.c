#include "include/crypto_box_keywrapper.h"
#include "include/crypto_scalarmult_curve25519.h"

int32_t
crypto_box_curve25519xsalsa20poly1305_compute_keypair(
        uint8_t *pk,
        uint8_t *sk)
{
    return crypto_scalarmult_curve25519_base(pk,sk);
}
