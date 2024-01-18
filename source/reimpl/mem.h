/*
 * reimpl/mem.h
 *
 * Implementations and wrappers for memory-related functions.
 *
 * Copyright (C) 2021      Andy Nguyen
 * Copyright (C) 2022      Rinnegatamante
 * Copyright (C) 2022-2023 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef SOLOADER_MEM_H
#define SOLOADER_MEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <malloc.h>
#include <sys/types.h>
#include <psp2/kernel/clib.h>

#define MAP_FAILED (void*)-1

void *sceClibMemclr(void *dst, SceSize len);

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offs);

int munmap(void *addr, size_t length);

#ifdef __cplusplus
};
#endif

#endif // SOLOADER_MEM_H
