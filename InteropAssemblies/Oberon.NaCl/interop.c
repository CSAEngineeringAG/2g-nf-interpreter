////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Oberon microsystems, Inc.
//
//  *** NaCl library interface ***
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "interop.h"

// Public-key cryptography
#include "crypto_box.h"
#include "crypto_scalarmult.h"
#include "crypto_sign.h"

// Secret-key cryptography
#include "crypto_secretbox.h"
#include "crypto_stream.h"
#include "crypto_onetimeauth.h"

// Low-level functions
#include "crypto_hash.h"
#include "crypto_verify_16.h"
#include "crypto_verify_32.h"

// Key wrapping function for implementations without a RNG
#include "crypto_box_keywrapper.h"
#include "crypto_sign_keywrapper.h"

int32_t
Crypto_compatibility_check()
{
    // Status flag
    int32_t result = 0;

    // Check Crypto Box Constants
    if ((Crypto_box_PUBLICKEYBYTES() != 32)
            || (Crypto_box_SECRETKEYBYTES() != 32)
            || (Crypto_box_NONCEBYTES() != 24)
            || (Crypto_box_BOXZEROBYTES() != 16)
            || (Crypto_box_BEFORENMBYTES() != 32))
    {
        result |= CompatibilityCheckCryptoBoxError;
    }

    // Check Scalarmult Constants
    if ((Crypto_scalarmult_BYTES() != 32)
           || (Crypto_scalarmult_SCALARBYTES() != 32))
    {
        result |= CompatibilityCheckCryptoScalarmultError;
    }

    // Check Crypto Sign Constants
    if ((Crypto_sign_PUBLICKEYBYTES() != 32)
            || (Crypto_sign_SECRETKEYBYTES() != 64)
            || (Crypto_sign_BYTES() != 64))
    {
        result |= CompatibilityCheckCryptoSignError;
    }

    // Check Crypto Secretbox Constants
    if ((Crypto_secretbox_KEYBYTES() != 32)
            || (Crypto_secretbox_NONCEBYTES() != 24)
            || (Crypto_secretbox_ZEROBYTES() != 32)
            || (Crypto_secretbox_BOXZEROBYTES() != 16))
    {
        result |= CompatibilityCheckCryptoSecretboxError;
    }

    // Check Crypto Stream Constants
    if ((Crypto_stream_KEYBYTES() != 32)
            || (Crypto_stream_NONCEBYTES() != 24))
    {
        result |= CompatibilityCheckCryptoStreamError;
    }

    // Check Crypto Onetimeauth Constants
    if ((Crypto_onetimeauth_BYTES() != 16)
            || (Crypto_onetimeauth_KEYBYTES() != 32))
    {
        result |= CompatibilityCheckCryptoOnetimeauthError;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Crypto Box Functions

int32_t
Crypto_box_PUBLICKEYBYTES()
{
    return crypto_box_curve25519xsalsa20poly1305_PUBLICKEYBYTES;
}

int32_t
Crypto_box_SECRETKEYBYTES()
{
    return crypto_box_curve25519xsalsa20poly1305_SECRETKEYBYTES;
}

int32_t
Crypto_box_NONCEBYTES()
{
    return crypto_box_curve25519xsalsa20poly1305_NONCEBYTES;
}

int32_t
Crypto_box_ZEROBYTES()
{
    return crypto_box_curve25519xsalsa20poly1305_ZEROBYTES;
}

int32_t
Crypto_box_BOXZEROBYTES()
{
    return crypto_box_curve25519xsalsa20poly1305_BOXZEROBYTES;
}

int32_t
Crypto_box_BEFORENMBYTES()
{
    return crypto_box_curve25519xsalsa20poly1305_BEFORENMBYTES;
}

int32_t
Crypto_box_compute_keypair(
        uint8_t *pk,
        uint8_t *sk)
{
    return crypto_box_curve25519xsalsa20poly1305_compute_keypair(pk, sk);
}

int32_t
Crypto_box(
              uint8_t *c, int32_t coff,
        const uint8_t *m, int32_t moff, int32_t mlen,
        const uint8_t *n,
        const uint8_t *pk,
        const uint8_t *sk)
{
    return crypto_box_curve25519xsalsa20poly1305(
                c + coff,
                m + moff, mlen,
                n,
                pk,
                sk);
}

int32_t
Crypto_box_open(
              uint8_t *m, int32_t moff,
        const uint8_t *c, int32_t coff, int32_t clen,
        const uint8_t *n,
        const uint8_t *pk,
        const uint8_t *sk)
{
    return crypto_box_curve25519xsalsa20poly1305_open(
                m + moff,
                c + coff, (unsigned long) clen,
                n,
                pk, sk);
}

int32_t
Crypto_box_afternm(
              uint8_t *c, int32_t coff,
        const uint8_t *m, int32_t moff, int32_t mlen,
        const uint8_t *n,
        const uint8_t *k)
{
    return crypto_box_curve25519xsalsa20poly1305_afternm(
                c + coff,
                m + moff, (unsigned long) mlen,
                n,
                k);
}

int32_t
Crypto_box_open_afternm(
              uint8_t *m, int32_t moff,
        const uint8_t *c, int32_t coff, int32_t clen,
        const uint8_t *n,
        const uint8_t *k)
{
    return crypto_box_curve25519xsalsa20poly1305_open_afternm(
                m + moff,
                c + coff, (unsigned long) clen,
                n,
                k);
}

int32_t
Crypto_box_beforenm(
              uint8_t *k, 
        const uint8_t *pk,
        const uint8_t *sk)
{
    return crypto_box_curve25519xsalsa20poly1305_beforenm(
                k,
                pk,
                sk);
}

////////////////////////////////////////////////////////////////////////////////
/// Crypto Scalarmult Functions

int32_t
Crypto_scalarmult_base(
              uint8_t *q,
        const uint8_t *n)
{
    return crypto_scalarmult_curve25519_base(
                q,
                n);
}

int32_t
Crypto_scalarmult(
              uint8_t *q,
        const uint8_t *n,
        const uint8_t *p)
{
    return crypto_scalarmult_curve25519(
                q,
                n,
                p);
}

int32_t
Crypto_scalarmult_BYTES()
{
    return crypto_scalarmult_curve25519_BYTES;
}

int32_t
Crypto_scalarmult_SCALARBYTES()
{
    return crypto_scalarmult_curve25519_SCALARBYTES;
}

////////////////////////////////////////////////////////////////////////////////
/// Crypto Sign Functions

int32_t
Crypto_sign_SECRETKEYBYTES()
{
    return crypto_sign_ed25519_SECRETKEYBYTES;
}

int32_t
Crypto_sign_PUBLICKEYBYTES()
{
    return crypto_sign_ed25519_PUBLICKEYBYTES;
}

int32_t
Crypto_sign_BYTES()
{
    return crypto_sign_ed25519_BYTES;
}

int32_t
Crypto_sign_compute_keypair(
        uint8_t *pk,
        uint8_t *sk)
{
    return crypto_sign_ed25519_compute_keypair(pk, sk);
}

int32_t
Crypto_sign(
              uint8_t *sm, int32_t smoff, uint32_t *smlen,
        const uint8_t *m,  int32_t moff,  int32_t   mlen,
        const uint8_t *sk)
{
    return crypto_sign_ed25519(
                sm + smoff, (unsigned long*) smlen,
                m  + moff,  mlen,
                sk);
}

int32_t
Crypto_sign_open(uint8_t *m, int32_t moff, uint32_t *mlen,
        const uint8_t *sm, int32_t smoff, int32_t smlen,
        const uint8_t *pk)
{
    return crypto_sign_ed25519_open(
                m  + moff, (unsigned long*) mlen,
                sm + smoff, smlen,
                pk);
}

////////////////////////////////////////////////////////////////////////////////
/// Crypto Secretbox Functions

int32_t
Crypto_secretbox_BOXZEROBYTES()
{
    return crypto_secretbox_xsalsa20poly1305_BOXZEROBYTES;
}

int32_t
Crypto_secretbox_KEYBYTES()
{
    return crypto_secretbox_xsalsa20poly1305_KEYBYTES;
}

int32_t
Crypto_secretbox_NONCEBYTES()
{
    return crypto_secretbox_xsalsa20poly1305_NONCEBYTES;
}

int32_t
Crypto_secretbox_ZEROBYTES()
{
    return crypto_secretbox_xsalsa20poly1305_ZEROBYTES;
}

int32_t
Crypto_secretbox(
              uint8_t *c, int32_t coff,
        const uint8_t *m, int32_t moff, int32_t mlen,
        const uint8_t *n,
        const uint8_t *k)
{
    return crypto_secretbox_xsalsa20poly1305(
                c + coff,
                m + moff, mlen,
                n,
                k);
}

int32_t
Crypto_secretbox_open(
              uint8_t *m, int32_t moff,
        const uint8_t *c, int32_t coff, int32_t clen,
        const uint8_t *n,
        const uint8_t *k)
{
    return crypto_secretbox_xsalsa20poly1305_open(
                m + moff,
                c + coff, clen,
                n,
                k);
}

////////////////////////////////////////////////////////////////////////////////
/// Crypto Stream Functions

int32_t
Crypto_stream_KEYBYTES()
{
    return crypto_stream_xsalsa20_KEYBYTES;
}

int32_t
Crypto_stream_NONCEBYTES()
{
    return crypto_stream_xsalsa20_NONCEBYTES;
}

int32_t
Crypto_stream(
              uint8_t *c, int32_t coff, int32_t clen,
        const uint8_t *n,
        const uint8_t *k)
{
    return crypto_stream_xsalsa20(
                c + coff, (unsigned long) clen,
                n,
                k);
}

int32_t
Crypto_stream_xor(
              uint8_t *c, int32_t coff,
        const uint8_t *m, int32_t moff, int32_t mlen,
        const uint8_t *n,
        const uint8_t *k)
{
    return crypto_stream_xsalsa20_xor(
                c + coff,
                m + moff, (unsigned long) mlen,
                n,
                k);
}

////////////////////////////////////////////////////////////////////////////////
/// Crypto Onetimeauth Functions

int32_t
Crypto_onetimeauth_BYTES()
{
    return crypto_onetimeauth_poly1305_BYTES;
}

int32_t
Crypto_onetimeauth_KEYBYTES()
{
    return crypto_onetimeauth_poly1305_KEYBYTES;
}

int32_t
Crypto_onetimeauth(
              uint8_t *a, 
        const uint8_t *m,int32_t moff, int32_t mlen,
        const uint8_t *k)
{
    return crypto_onetimeauth_poly1305(
                a,
                m  + moff, (unsigned long) mlen,
                k);
}

int32_t
Crypto_onetimeauth_verify(
        const uint8_t *a, 
        const uint8_t *m,int32_t moff, int32_t mlen,
        const uint8_t *k)
{
    return crypto_onetimeauth_poly1305_verify(
                a,
                m + moff, (unsigned long) mlen,
                k);
}

////////////////////////////////////////////////////////////////////////////////
/// Crypto Hash Functions

int32_t
Crypto_hash_BYTES()
{
    return crypto_hash_sha512_BYTES;
}

int32_t
Crypto_hash(
              uint8_t *h,
        const uint8_t *m,  int32_t moff,  int32_t mlen)
{
    return crypto_hash_sha512(
                h,
                m  + moff, (unsigned long) mlen);
}

////////////////////////////////////////////////////////////////////////////////
/// Crypto Verify Functions

int32_t
Crypto_verify_16_BYTES()
{
    return crypto_verify_16_BYTES;
}

int32_t
Crypto_verify_16(
        const uint8_t *x, int32_t xoff,
        const uint8_t *y, int32_t yoff)
{
    return crypto_verify_16(
                x + xoff,
                y + yoff);
}

int32_t
Crypto_verify_32_BYTES()
{
    return crypto_verify_32_BYTES;
}

int32_t
Crypto_verify_32(
        const uint8_t *x, int32_t xoff,
        const uint8_t *y, int32_t yoff)
{
    return crypto_verify_32(
                x + xoff,
                y + yoff);
}
