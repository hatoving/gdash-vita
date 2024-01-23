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
extern int move_id;
extern float move_data[2];

so_hook move_hook;

void handleTouchesMove(void *this, int size, int *ids, float *x, float *y) {
    SO_CONTINUE(int, move_hook, this, 1, &move_id, &move_data[0], &move_data[1]);
}


void so_patch(void) {
    patch_openssl();
    move_hook = hook_addr(so_symbol(&so_mod, "_ZN7cocos2d17CCEGLViewProtocol17handleTouchesMoveEiPiPfS2_"), (uintptr_t)&handleTouchesMove);
}