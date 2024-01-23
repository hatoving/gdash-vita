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

so_hook music_hook;
so_hook move_hook;

int* (* _ZN15FMODAudioEngine21getActiveMusicChannelEi)(void* this, int a2);

int FMODAudioEngine_isMusicPlaying_soloader(void *this, int a2) {
    void* channel = _ZN15FMODAudioEngine21getActiveMusicChannelEi(this, a2);
    int ret = 1;
    if (channel) {
        _ZN4FMOD14ChannelControl9getPausedEPb(channel, &ret);
    }

    return ret == 0 ? 0 : 1;
}

void FMODAudioEngine_playMusic_soloader(void *this, int *unk, int unk2, float fade_vol, int unk3) {
    SO_CONTINUE(int, music_hook, this, unk, unk2, 0.0f, unk3);
}

void handleTouchesMove(void *this, int size, int *ids, float *x, float *y) {
    SO_CONTINUE(int, move_hook, this, 1, &move_id, &move_data[0], &move_data[1]);
}

void so_patch(void) {
    _ZN15FMODAudioEngine21getActiveMusicChannelEi = (void *)so_symbol(&so_mod, "_ZN15FMODAudioEngine21getActiveMusicChannelEi");

    patch_openssl();

    hook_addr(so_symbol(&so_mod, "_ZN15FMODAudioEngine14isMusicPlayingEi"), (uintptr_t)&FMODAudioEngine_isMusicPlaying_soloader);

    music_hook = hook_addr(so_symbol(&so_mod, "_ZN15FMODAudioEngine9playMusicESsbfi"), (uintptr_t)&FMODAudioEngine_playMusic_soloader);
    move_hook = hook_addr(so_symbol(&so_mod, "_ZN7cocos2d17CCEGLViewProtocol17handleTouchesMoveEiPiPfS2_"), (uintptr_t)&handleTouchesMove);
}