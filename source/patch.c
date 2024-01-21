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

#ifdef USE_FMOD

extern so_module so_mod;

int* (* _ZN15FMODAudioEngine21getActiveMusicChannelEi)(void* this, int a2);

int FMODAudioEngine_isMusicPlaying_soloader(void *this, int a2) {
    void* channel = _ZN15FMODAudioEngine21getActiveMusicChannelEi(this, a2);
    int ret = 0;
    if (channel) {
        _ZN4FMOD14ChannelControl9getPausedEPb(channel, &ret);
    }

    return ret == 0 ? 0 : 1;
}

#endif

void so_patch(void) {
    _ZN15FMODAudioEngine21getActiveMusicChannelEi = (void *)so_symbol(&so_mod, "_ZN15FMODAudioEngine21getActiveMusicChannelEi");

    patch_openssl();
    #ifdef USE_FMOD
        hook_addr(so_symbol(&so_mod, "_ZN15FMODAudioEngine14isMusicPlayingEi"), (uintptr_t)&FMODAudioEngine_isMusicPlaying_soloader);
    #endif
}
