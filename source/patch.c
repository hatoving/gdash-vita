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

#include "utils/logger.h"
#include "utils/utils.h"

#include <kubridge.h>
#include <vitaGL.h>
#include <so_util/so_util.h>

extern so_module so_mod;

void so_patch(void) {
    //http_hook = hook_addr(so_symbol(&so_mod, "_ZThn500_N14DailyLevelPage17dailyStatusFailedE16GJTimedLevelType11GJErrorCode"), (uintptr_t)&FailedDaily);
}