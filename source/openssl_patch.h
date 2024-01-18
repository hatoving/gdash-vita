/*
 * patch.h
 *
 * Patching OpenSSL functions.
 *
 * Copyright (C) 2024 hatoving
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef OPENSSL_PATCH_H
#define OPENSSL_PATCH_H

#include <openssl/crypto.h>
#include <openssl/evp.h>

int CRYPTO_atomic_add(int *val, int amount, int *ret);
void *CRYPTO_zalloc(size_t num, const char *file, int line);
void EVP_CIPHER_CTX_set_num(EVP_CIPHER_CTX *ctx, int num);
void* EVP_CIPHER_CTX_get_cipher_data(const EVP_CIPHER_CTX *ctx);
int EVP_CIPHER_CTX_num(const EVP_CIPHER_CTX *ctx);
unsigned char *EVP_CIPHER_CTX_iv_noconst(const EVP_CIPHER_CTX *ctx);
unsigned char *EVP_CIPHER_CTX_buf_noconst(const EVP_CIPHER_CTX *ctx);

void patch_openssl();

#endif