/*
 * main.c
 *
 * Android ARMv7 Shared Libraries loader for PSVita
 *
 * Copyright (C) 2021 Andy Nguyen
 * Copyright (C) 2021-2023 Rinnegatamante
 * Copyright (C) 2022-2023 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "utils/init.h"
#include "utils/dialog.h"
#include "utils/logger.h"
#include "utils/glutil.h"
#include "utils/settings.h"

#include <psp2/kernel/threadmgr.h>
#include <psp2/net/net.h>
#include <psp2/sysmodule.h> 

#include <psp2/touch.h>
#include <psp2/ctrl.h>

#include <falso_jni/FalsoJNI.h>
#include <falso_jni/FalsoJNI_Impl.h>
#include <so_util/so_util.h>
#include <psp2/kernel/processmgr.h>
#include <sched.h>
#include <stdio.h>
#include <sys/stat.h>

#include <fmod/fmod.h>

extern FMOD_RESULT F_API __real_FMOD_System_CreateSound(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
extern FMOD_RESULT F_API __real_FMOD_System_CreateStream(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);

FMOD_RESULT F_API __wrap_FMOD_System_CreateSound(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound) {
    char fname_real[256];
    sprintf(fname_real, "%s%s", ASSETS_PATH, &name_or_data[22]);

    int ret = __real_FMOD_System_CreateSound(system, fname_real, mode, exinfo, sound);
    
    //logv_debug("FMOD SOUND RETURN!!::: %i", ret);
    //logv_debug("FMOD SOUND CREATION!!::: %s", fname_real);

    return ret;
}

FMOD_RESULT F_API __wrap_FMOD_System_CreateStream(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound) {
    char fname_real[256];
    sprintf(fname_real, "%s%s", ASSETS_PATH, &name_or_data[22]);

    int ret = __real_FMOD_System_CreateStream(system, fname_real, mode, exinfo, sound);

    //logv_debug("FMOD STREAM RETURN!!::: %i", ret);
    //logv_debug("FMOD STREAM CREATION!!::: %s", fname_real);

    return ret;
}

int _newlib_heap_size_user = 256 * 1024 * 1024;

#ifdef USE_SCELIBC_IO
int sceLibcHeapSize = 24 * 1024 * 1024;
#endif

so_module so_mod;

void fmod_init() {
    sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
    int ret = sceNetShowNetstat();
    SceNetInitParam initparam;
    
    if (ret == SCE_NET_ERROR_ENOTINIT) {
        initparam.memory = malloc(141 * 1024);
        initparam.size = 141 * 1024;
        initparam.flags = 0;
        sceNetInit(&initparam);
    }
        
    sceKernelLoadStartModule("vs0:sys/external/libfios2.suprx", 0, NULL, 0, NULL, NULL);
    sceKernelLoadStartModule("vs0:sys/external/libc.suprx", 0, NULL, 0, NULL, NULL);
    sceKernelLoadStartModule("ur0:data/libfmodstudio.suprx", 0, NULL, 0, NULL, NULL);
}

int main() {
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);

    soloader_init_all();
    fmod_init();

    int (* JNI_OnLoad)(void *jvm) = (void *)so_symbol(&so_mod, "JNI_OnLoad");
    
    JNI_OnLoad(&jvm);
    gl_init();


    while (1) {
        gl_swap();
    }

    sceKernelExitDeleteThread(0);
}
