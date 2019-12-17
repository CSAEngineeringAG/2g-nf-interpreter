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

#ifndef Oberon_NaCl_interop_H
#define Oberon_NaCl_interop_H

#include <stdint.h>

#ifdef _WIN32
#   ifdef _DLL
   /* We are building this library */
#       define WINDLLEXPORT __declspec(dllexport)
#   else
 
#       define WINDLLEXPORT __declspec(dllimport)
#  endif

#else
// ifndef WIN32
#define WINDLLEXPORT
#endif



#ifdef __cplusplus
extern "C" {
#endif

typedef enum CompatibilitycheckCheckError
{
    CompatibilityCheckNoError = 0,
    CompatibilityCheckCryptoBoxError = 1 << 0,
    CompatibilityCheckCryptoSignError = 1 << 1,
    CompatibilityCheckCryptoSecretboxError = 1 << 2,
    CompatibilityCheckCryptoStreamError = 1 << 3,
    CompatibilityCheckCryptoOnetimeauthError = 1 << 4,
    CompatibilityCheckCryptoScalarmultError = 1 << 5
} CompatibilitycheckCheckError;

WINDLLEXPORT int32_t
Crypto_compatibility_check();

////////////////////////////////////////////////////////////////////////////////
/// Crypto Box Functions

WINDLLEXPORT int32_t
Crypto_box_PUBLICKEYBYTES();

WINDLLEXPORT int32_t
Crypto_box_SECRETKEYBYTES();

WINDLLEXPORT int32_t
Crypto_box_NONCEBYTES();

WINDLLEXPORT int32_t
Crypto_box_ZEROBYTES();

WINDLLEXPORT int32_t
Crypto_box_BOXZEROBYTES();

WINDLLEXPORT int32_t
Crypto_box_BEFORENMBYTES();

WINDLLEXPORT int32_t
Crypto_box_compute_keypair(
        uint8_t *pk,
        uint8_t *sk);

WINDLLEXPORT int32_t
Crypto_box(
              uint8_t *c, int32_t coff,
        const uint8_t *m, int32_t moff, int32_t mlen,
        const uint8_t *n,
        const uint8_t *pk,
        const uint8_t *sk);

WINDLLEXPORT int32_t
Crypto_box_open(
              uint8_t *m, int32_t moff,
        const uint8_t *c, int32_t coff, int32_t clen,
        const uint8_t *n,
        const uint8_t *pk,
        const uint8_t *sk);

WINDLLEXPORT int32_t
Crypto_box_afternm(
              uint8_t *c, int32_t coff,
        const uint8_t *m, int32_t moff, int32_t mlen,
        const uint8_t *n,
        const uint8_t *k);

WINDLLEXPORT int32_t
Crypto_box_open_afternm(
              uint8_t *m, int32_t moff,
        const uint8_t *c, int32_t coff, int32_t clen,
        const uint8_t *n,
        const uint8_t *k);

WINDLLEXPORT int32_t
Crypto_box_beforenm(
              uint8_t *k,
        const uint8_t *pk,
        const uint8_t *sk);

////////////////////////////////////////////////////////////////////////////////
/// Crypto Scalarmult Functions

WINDLLEXPORT int32_t
Crypto_scalarmult_base(
              uint8_t *q,
        const uint8_t *n);

WINDLLEXPORT int32_t
Crypto_scalarmult(
              uint8_t *q,
        const uint8_t *n,
        const uint8_t *p);

WINDLLEXPORT int32_t
Crypto_scalarmult_BYTES();

WINDLLEXPORT int32_t
Crypto_scalarmult_SCALARBYTES();

////////////////////////////////////////////////////////////////////////////////
/// Crypto Sign Functions

WINDLLEXPORT int32_t
Crypto_sign_SECRETKEYBYTES();

WINDLLEXPORT int32_t
Crypto_sign_PUBLICKEYBYTES();

WINDLLEXPORT int32_t
Crypto_sign_BYTES();

WINDLLEXPORT int32_t
Crypto_sign_compute_keypair(
        uint8_t *pk,
        uint8_t *sk);

WINDLLEXPORT int32_t
Crypto_sign(uint8_t *sm, int32_t smoff, uint32_t *smlen,
        const uint8_t *m,  int32_t moff, int32_t mlen,
        const uint8_t *sk);

WINDLLEXPORT int32_t
Crypto_sign_open(uint8_t *m, int32_t moff, uint32_t *mlen,
        const uint8_t *sm, int32_t smoff, int32_t smlen,
        const uint8_t *pk);

////////////////////////////////////////////////////////////////////////////////
/// Crypto Secretbox Functions

WINDLLEXPORT int32_t
Crypto_secretbox_BOXZEROBYTES();

WINDLLEXPORT int32_t
Crypto_secretbox_KEYBYTES();

WINDLLEXPORT int32_t
Crypto_secretbox_NONCEBYTES();

WINDLLEXPORT int32_t
Crypto_secretbox_ZEROBYTES();

WINDLLEXPORT int32_t
Crypto_secretbox(
              uint8_t *c, int32_t coff,
        const uint8_t *m, int32_t moff, int32_t mlen,
        const uint8_t *n,
        const uint8_t *k);

WINDLLEXPORT int32_t
Crypto_secretbox_open(
              uint8_t *m, int32_t moff,
        const uint8_t *c, int32_t coff, int32_t clen,
        const uint8_t *n,
        const uint8_t *k);

////////////////////////////////////////////////////////////////////////////////
/// Crypto Stream Functions

WINDLLEXPORT int32_t
Crypto_stream_KEYBYTES();

WINDLLEXPORT int32_t
Crypto_stream_NONCEBYTES();

WINDLLEXPORT int32_t
Crypto_stream(
              uint8_t *c, int32_t coff, int32_t clen,
        const uint8_t *n,
        const uint8_t *k);

WINDLLEXPORT int32_t
Crypto_stream_xor(
              uint8_t *c, int32_t coff,
        const uint8_t *m, int32_t moff, int32_t mlen,
        const uint8_t *n,
        const uint8_t *k);

////////////////////////////////////////////////////////////////////////////////
/// Crypto Onetimeauth Functions

WINDLLEXPORT int32_t
Crypto_onetimeauth_BYTES();

WINDLLEXPORT int32_t
Crypto_onetimeauth_KEYBYTES();

WINDLLEXPORT int32_t
Crypto_onetimeauth(
              uint8_t *a,
        const uint8_t *m, int32_t moff,  int32_t mlen,
        const uint8_t *k);

WINDLLEXPORT int32_t
Crypto_onetimeauth_verify(
        const uint8_t *a, 
        const uint8_t *m,int32_t moff, int32_t mlen,
        const uint8_t *k);

////////////////////////////////////////////////////////////////////////////////
/// Crypto Hash Functions

WINDLLEXPORT int32_t
Crypto_hash_BYTES();

WINDLLEXPORT int32_t
Crypto_hash(
              uint8_t *h,
        const uint8_t *m,  int32_t moff,  int32_t mlen);

////////////////////////////////////////////////////////////////////////////////
/// Crypto Verify Functions

WINDLLEXPORT int32_t
Crypto_verify_16_BYTES();

WINDLLEXPORT int32_t
Crypto_verify_16(
        const uint8_t *x, int32_t xoff,
        const uint8_t *y, int32_t yoff);

WINDLLEXPORT int32_t
Crypto_verify_32_BYTES();

WINDLLEXPORT int32_t
Crypto_verify_32(
        const uint8_t *x, int32_t xoff,
        const uint8_t *y, int32_t yoff);

#ifdef __cplusplus
}
#endif

#endif
