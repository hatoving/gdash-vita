/*
 * reimpl/env.c
 *
 * Implementation for `getenv()`/`setenv()` functions with predefined
 * environment variables.
 *
 * Copyright (C) 2022-2023 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef SOLOADER_ENV_H
#define SOLOADER_ENV_H

#ifdef __cplusplus
extern "C" {
#endif

char *getenv_soloader(const char *name);

int setenv_soloader(const char *name, const char *value, int overwrite);

#ifdef __cplusplus
};
#endif

#endif // SOLOADER_ENV_H
