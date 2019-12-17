#ifndef crypto_core_H
#define crypto_core_H

#include "include/crypto_core_chacha20.h"

#define crypto_core crypto_core_chacha20
#define crypto_core_OUTPUTBYTES crypto_core_chacha20_OUTPUTBYTES
#define crypto_core_INPUTBYTES crypto_core_chacha20_INPUTBYTES
#define crypto_core_KEYBYTES crypto_core_chacha20_KEYBYTES
#define crypto_core_CONSTBYTES crypto_core_chacha20_CONSTBYTES
#define crypto_core_PRIMITIVE "chacha20"
#define crypto_core_IMPLEMENTATION crypto_core_chacha20_IMPLEMENTATION
#define crypto_core_VERSION crypto_core_chacha20_VERSION

#endif
