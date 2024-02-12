#include "openssl_patch.h"

#include <kubridge.h>
#include <so_util/so_util.h>

extern so_module so_mod;

int CRYPTO_atomic_add(int *val, int amount, int *ret) {
    *val += amount;
    *ret = *val;
    return 1;
}

void *CRYPTO_zalloc(size_t num, const char *file, int line)
{
    void *ret;

    ret = CRYPTO_malloc(num, file, line);
    if (ret != NULL)
        memset(ret, 0, num);

    return ret;
}

void EVP_CIPHER_CTX_set_num(EVP_CIPHER_CTX *ctx, int num) {
    ctx->num = num;
}

void* EVP_CIPHER_CTX_get_cipher_data(const EVP_CIPHER_CTX *ctx) {
    return ctx->cipher_data;
}

int EVP_CIPHER_CTX_num(const EVP_CIPHER_CTX *ctx) {
    return ctx->num;
}

unsigned char *EVP_CIPHER_CTX_iv_noconst(const EVP_CIPHER_CTX *ctx) {
    return ctx->iv;
}

unsigned char *EVP_CIPHER_CTX_buf_noconst(const EVP_CIPHER_CTX *ctx) {
    return ctx->buf;
}

void patch_openssl(void) {
    hook_addr(so_symbol(&so_mod, "CRYPTO_free"), (uintptr_t)&CRYPTO_free);
    hook_addr(so_symbol(&so_mod, "CRYPTO_zalloc"), (uintptr_t)&CRYPTO_zalloc);
    hook_addr(so_symbol(&so_mod, "CRYPTO_malloc"), (uintptr_t)&CRYPTO_malloc);
    hook_addr(so_symbol(&so_mod, "CRYPTO_realloc"), (uintptr_t)&CRYPTO_realloc);
    hook_addr(so_symbol(&so_mod, "OPENSSL_cleanse"), (uintptr_t)&OPENSSL_cleanse);
    hook_addr(so_symbol(&so_mod, "CRYPTO_free_ex_data"), (uintptr_t)&CRYPTO_free_ex_data);
    hook_addr(so_symbol(&so_mod, "CRYPTO_get_ex_data"), (uintptr_t)&CRYPTO_get_ex_data);
    hook_addr(so_symbol(&so_mod, "CRYPTO_get_ex_new_index"), (uintptr_t)&CRYPTO_get_ex_new_index);
    hook_addr(so_symbol(&so_mod, "CRYPTO_get_mem_functions"), (uintptr_t)&CRYPTO_get_mem_functions);
    hook_addr(so_symbol(&so_mod, "CRYPTO_mem_ctrl"), (uintptr_t)&CRYPTO_mem_ctrl);
    hook_addr(so_symbol(&so_mod, "CRYPTO_memcmp"), (uintptr_t)&CRYPTO_memcmp);
    hook_addr(so_symbol(&so_mod, "CRYPTO_new_ex_data"), (uintptr_t)&CRYPTO_new_ex_data);
    hook_addr(so_symbol(&so_mod, "ERR_load_CRYPTO_strings"), (uintptr_t)&ERR_load_CRYPTO_strings);
    hook_addr(so_symbol(&so_mod, "CRYPTO_atomic_add"), (uintptr_t)&CRYPTO_atomic_add);

    // EVP
    hook_addr(so_symbol(&so_mod, "EVP_CIPHER_CTX_num"), (uintptr_t)&EVP_CIPHER_CTX_num);
    hook_addr(so_symbol(&so_mod, "EVP_CIPHER_CTX_set_num"), (uintptr_t)&EVP_CIPHER_CTX_set_num);
    hook_addr(so_symbol(&so_mod, "EVP_CIPHER_CTX_get_cipher_data"), (uintptr_t)&EVP_CIPHER_CTX_get_cipher_data);
    hook_addr(so_symbol(&so_mod, "EVP_CIPHER_CTX_iv_noconst"), (uintptr_t)&EVP_CIPHER_CTX_iv_noconst);
    hook_addr(so_symbol(&so_mod, "EVP_CIPHER_CTX_buf_noconst"), (uintptr_t)&EVP_CIPHER_CTX_buf_noconst);
    hook_addr(so_symbol(&so_mod, "EVP_add_cipher"), (uintptr_t)&EVP_add_cipher);
    hook_addr(so_symbol(&so_mod, "EVP_add_digest"), (uintptr_t)&EVP_add_digest);
    hook_addr(so_symbol(&so_mod, "EVP_add_alg_module"), (uintptr_t)&EVP_add_alg_module);
    hook_addr(so_symbol(&so_mod, "ERR_load_EVP_strings"), (uintptr_t)&ERR_load_EVP_strings);
    hook_addr(so_symbol(&so_mod, "EVP_DecodeInit"), (uintptr_t)&EVP_DecodeInit);
    hook_addr(so_symbol(&so_mod, "EVP_DecodeUpdate"), (uintptr_t)&EVP_DecodeUpdate);
    hook_addr(so_symbol(&so_mod, "EVP_DecodeFinal"), (uintptr_t)&EVP_DecodeFinal);
    hook_addr(so_symbol(&so_mod, "EVP_DecodeBlock"), (uintptr_t)&EVP_DecodeBlock);
    hook_addr(so_symbol(&so_mod, "EVP_DecryptInit"), (uintptr_t)&EVP_DecryptInit);
    hook_addr(so_symbol(&so_mod, "EVP_DecryptInit_ex"), (uintptr_t)&EVP_DecryptInit_ex);
    hook_addr(so_symbol(&so_mod, "EVP_DecryptFinal"), (uintptr_t)&EVP_DecryptFinal);
    hook_addr(so_symbol(&so_mod, "EVP_DecryptFinal_ex"), (uintptr_t)&EVP_DecryptFinal_ex);
    hook_addr(so_symbol(&so_mod, "EVP_DecryptUpdate"), (uintptr_t)&EVP_DecryptUpdate);
    hook_addr(so_symbol(&so_mod, "EVP_DigestUpdate"), (uintptr_t)&EVP_DigestUpdate);
    hook_addr(so_symbol(&so_mod, "EVP_DigestFinal"), (uintptr_t)&EVP_DigestFinal);
    hook_addr(so_symbol(&so_mod, "EVP_DigestFinal_ex"), (uintptr_t)&EVP_DigestFinal_ex);
    hook_addr(so_symbol(&so_mod, "EVP_DigestInit"), (uintptr_t)&EVP_DigestInit);
    hook_addr(so_symbol(&so_mod, "EVP_DigestInit_ex"), (uintptr_t)&EVP_DigestInit_ex);
    hook_addr(so_symbol(&so_mod, "EVP_DigestSignInit"), (uintptr_t)&EVP_DigestSignInit);
    hook_addr(so_symbol(&so_mod, "EVP_DigestSignFinal"), (uintptr_t)&EVP_DigestSignFinal);
    hook_addr(so_symbol(&so_mod, "EVP_enc_null"), (uintptr_t)&EVP_enc_null);
    hook_addr(so_symbol(&so_mod, "EVP_EncodeUpdate"), (uintptr_t)&EVP_EncodeUpdate);
    hook_addr(so_symbol(&so_mod, "EVP_EncodeFinal"), (uintptr_t)&EVP_EncodeFinal);
    hook_addr(so_symbol(&so_mod, "EVP_EncodeBlock"), (uintptr_t)&EVP_EncodeBlock);
    hook_addr(so_symbol(&so_mod, "EVP_EncodeInit"), (uintptr_t)&EVP_EncodeInit);
    hook_addr(so_symbol(&so_mod, "EVP_EncryptInit"), (uintptr_t)&EVP_EncryptInit);
    hook_addr(so_symbol(&so_mod, "EVP_EncryptUpdate"), (uintptr_t)&EVP_EncryptUpdate);
    hook_addr(so_symbol(&so_mod, "EVP_EncryptInit_ex"), (uintptr_t)&EVP_EncryptInit_ex);
    hook_addr(so_symbol(&so_mod, "EVP_EncryptFinal"), (uintptr_t)&EVP_EncryptFinal);
    hook_addr(so_symbol(&so_mod, "EVP_EncryptFinal_ex"), (uintptr_t)&EVP_EncryptFinal_ex);
}