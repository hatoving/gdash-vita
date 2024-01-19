/*
 * patch.c
 *
 * Patching some of the .so internal functions or bridging them to native for
 * better compatibility.
 *
 * Copyright (C) 2023 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "patch.h"

#include "openssl_patch.h"
#include "fmod_symbols.h"

#include "utils/logger.h"
#include "utils/utils.h"

#include <kubridge.h>
#include <vitaGL.h>
#include <so_util/so_util.h>

extern so_module so_mod;

void so_patch(void) {
    patch_openssl();
}
