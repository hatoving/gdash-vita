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
        
    sceKernelLoadStartModule("ur0:data/libfios2.suprx", 0, NULL, 0, NULL, NULL);
    sceKernelLoadStartModule("ur0:data/libc.suprx", 0, NULL, 0, NULL, NULL);
    sceKernelLoadStartModule("ur0:data/libfmodstudio.suprx", 0, NULL, 0, NULL, NULL);
}

// For some reason, Geometry Dash doesn't create the files necessary at boot
// to actually store your level/save data. This functions takes responsibility
// of that.
void save_files_init() {
    char* file_paths[] = {
        "ux0:data/gdash/CCGameManager.dat",
        "ux0:data/gdash/CCGameManager2.dat",
        "ux0:data/gdash/CCGameManager.dat.bak",
        "ux0:data/gdash/CCLocalLevels.dat",
        "ux0:data/gdash/CCLocalLevels.dat.bak",
        "ux0:data/gdash/CCLocalLevels2.dat",
    };

    for (int i = 0; i < 6; i++) {
        FILE* f = fopen(file_paths[i], "r");

        // if file doesn't exist, then create it
        // so that the game can open it
        if (f == NULL) {
            logv_debug("File \"%s\" doesn't exist. Creating...", file_paths[i]);

            FILE* nf = fopen(file_paths[i], "w");
            if (nf != NULL) {
                logv_debug("File \"%s\" successfully created", file_paths[i]);
                fclose(nf);
            }
        }

        fclose(f);
    }
}

float move_data[2];
int move_id;

float x_dummy;
float y_dummy;

int main() {
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);

    soloader_init_all();
    fmod_init();
    save_files_init();

    int (* JNI_OnLoad)(void *jvm) = (void *)so_symbol(&so_mod, "JNI_OnLoad");
    //_ZN7cocos2d9extension13AssetsManager14setStoragePathEPKc
    int (* Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath)(JNIEnv *jni, void *unk, jstring apk_path) 
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath");

    int (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit)(JNIEnv *jni, void* unk, jint w, jint h) 
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit");
    int (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender)(void) 
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender");

    void (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin)(JNIEnv * jni, jobject thiz, jint id, jfloat x, jfloat y) 
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin");
    //jboolean (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeKeyDown)(JNIEnv * jni, jobject thiz, jint keyCode) = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeKeyDown");
    void (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove)(JNIEnv * jni, jobject thiz, jint *ids, jfloat *xs, jfloat *ys)
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove");
    void (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd)(JNIEnv * jni, jobject thiz, jint id, jfloat x, jfloat y)
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd");

    bool (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeKeyDown)(JNIEnv* jni, jobject thiz, jint keyCode)
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeKeyDown");

    int (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInsertText)(JNIEnv* jni, jobject thiz, jstring text)
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInsertText");

    JNI_OnLoad(&jvm);

    Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath(&jni, NULL, APK_PATH);
    gl_init();
    Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(&jni, NULL, 960, 544);

    int lastX[SCE_TOUCH_MAX_REPORT] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int lastY[SCE_TOUCH_MAX_REPORT] = {-1, -1, -1, -1, -1, -1, -1, -1};

    while (1) {
        static uint32_t oldpad;

        SceCtrlData pad;
		sceCtrlPeekBufferPositive(0, &pad, 1);

        SceTouchData touch;
        sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);

        if (pad.buttons & SCE_CTRL_LEFT) {
            x_dummy = 95;
            y_dummy = 480;

            int id_dummy = 16;
            
            if ((oldpad & SCE_CTRL_LEFT)) {
                Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(&jni, NULL, &id_dummy, &x_dummy, &y_dummy);
            } else {
                Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(&jni, NULL, id_dummy, x_dummy, y_dummy);
            }
        } else if (oldpad & SCE_CTRL_LEFT) {
            int id_dummy = 16;
            Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(&jni, NULL, id_dummy, x_dummy, y_dummy);
        }

        if (pad.buttons & SCE_CTRL_RIGHT) {
            x_dummy = 225;
            y_dummy = 480;

            int id_dummy = 17;

            if ((oldpad & SCE_CTRL_RIGHT)) {
                Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(&jni, NULL, &id_dummy, &x_dummy, &y_dummy);
            } else {
                Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(&jni, NULL, id_dummy, x_dummy, y_dummy);
            }
        } else if (oldpad & SCE_CTRL_RIGHT) {
            int id_dummy = 17;
            Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(&jni, NULL, id_dummy, x_dummy, y_dummy);
        }

        if (pad.buttons & SCE_CTRL_CROSS) {
            x_dummy = 959;
            y_dummy = 543;

            int id_dummy = 18;
            
            if ((oldpad & SCE_CTRL_CROSS)) {
                Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(&jni, NULL, &id_dummy, &x_dummy, &y_dummy);
            } else {
                Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(&jni, NULL, id_dummy, x_dummy, y_dummy);
            }
        } else if (oldpad & SCE_CTRL_CROSS) {
            int id_dummy = 18;
            Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(&jni, NULL, id_dummy, x_dummy, y_dummy);
        }
        
        if (((pad.buttons & SCE_CTRL_CIRCLE) && (!(oldpad & SCE_CTRL_CIRCLE))) || ((pad.buttons & SCE_CTRL_START) && (!(oldpad & SCE_CTRL_START)))) {
            Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeKeyDown(&jni, NULL, 0x04);
        }

        oldpad = pad.buttons;

        for (int i = 0; i < SCE_TOUCH_MAX_REPORT; i++) {
            if (i < touch.reportNum) {
                float x = (float)touch.report[i].x * (float)960.0f / 1920.0f;
                float y = (float)touch.report[i].y * (float)544.0f / 1088.0f;
                int id = i;

                if (lastX[i] == -1 || lastY[i] == -1) {
                    Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(&jni, NULL, i, x, y);
                } else {
                    move_data[0] = (float)x;
					move_data[1] = (float)y;
					move_id = id;

                    Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(&jni, NULL,
                        &id, &x, &y);
                }

                lastX[i] = x;
                lastY[i] = y;

            } else {
                if (lastX[i] != -1 || lastY[i] != -1) {
                    Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(&jni, NULL, i, lastX[i], lastY[i]);
                    lastX[i] = -1;
                    lastY[i] = -1;
                }
            }
        }

        Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender();
        gl_swap();
    }

    sceKernelExitDeleteThread(0);
}
