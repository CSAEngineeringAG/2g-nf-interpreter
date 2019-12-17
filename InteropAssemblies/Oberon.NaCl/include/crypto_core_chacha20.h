#ifndef crypto_core_chacha20_H
#define crypto_core_chacha20_H

#define crypto_core_chacha20_ref_OUTPUTBYTES 64
#define crypto_core_chacha20_ref_INPUTBYTES 16
#define crypto_core_chacha20_ref_KEYBYTES 32
#define crypto_core_chacha20_ref_CONSTBYTES 16
#ifdef __cplusplus
extern "C" {
#endif
extern int crypto_core_chacha20_ref(unsigned char *,const unsigned char *,const unsigned char *,const unsigned char *);
#ifdef __cplusplus
}
#endif

#define crypto_core_chacha20 crypto_core_chacha20_ref
#define crypto_core_chacha20_OUTPUTBYTES crypto_core_chacha20_ref_OUTPUTBYTES
#define crypto_core_chacha20_INPUTBYTES crypto_core_chacha20_ref_INPUTBYTES
#define crypto_core_chacha20_KEYBYTES crypto_core_chacha20_ref_KEYBYTES
#define crypto_core_chacha20_CONSTBYTES crypto_core_chacha20_ref_CONSTBYTES
#define crypto_core_chacha20_IMPLEMENTATION "crypto_core/chacha20/ref"
#ifndef crypto_core_chacha20_ref_VERSION
#define crypto_core_chacha20_ref_VERSION "-"
#endif
#define crypto_core_chacha20_VERSION crypto_core_chacha20_ref_VERSION

#endif
