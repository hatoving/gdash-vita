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
#include "utils/glutil.h"
#include "utils/settings.h"

#include <psp2/kernel/threadmgr.h>
#include <psp2/net/net.h>
#include <psp2/sysmodule.h> 

#include <psp2/touch.h>
#include <psp2/ctrl.h>

#include <falso_jni/FalsoJNI.h>
#include <so_util/so_util.h>
#include <psp2/kernel/processmgr.h>
#include <sched.h>

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
        
    sceClibPrintf("sceKernelLoadStartModule %x\n", sceKernelLoadStartModule("ux0:data/libfios2.suprx", 0, NULL, 0, NULL, NULL));
    sceClibPrintf("sceKernelLoadStartModule %x\n", sceKernelLoadStartModule("ux0:data/libc.suprx", 0, NULL, 0, NULL, NULL));
    sceClibPrintf("sceKernelLoadStartModule %x\n", sceKernelLoadStartModule("ur0:data/libfmodstudio.suprx", 0, NULL, 0, NULL, NULL));
}

int main() {
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);

    soloader_init_all();
    fmod_init();

    int (* JNI_OnLoad)(void *jvm) = (void *)so_symbol(&so_mod, "JNI_OnLoad");
    //_ZN7cocos2d9extension13AssetsManager14setStoragePathEPKc
    int (* Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath)(JNIEnv *jni, void *unk, jstring apk_path) 
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath");

    int (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit)(JNIEnv *jni, void* unk, jint w, jint h) 
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit");
    int (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender)(void) 
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender");

    void (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin)(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y) 
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin");
    //jboolean (* Cocos2D_KeyDown)(JNIEnv *jni, jobject thiz, jint keyCode) = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeKeyDown");
    void (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove)(JNIEnv * env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys)
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove");
    void (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd)(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y)
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd");

    JNI_OnLoad(&jvm);
    Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath(&jni, NULL, APK_PATH);

    gl_init();
    Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(&jni, NULL, 960, 544);

    int lastX[SCE_TOUCH_MAX_REPORT] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int lastY[SCE_TOUCH_MAX_REPORT] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int ids[SCE_TOUCH_MAX_REPORT] = {-1, -1, -1, -1, -1, -1, -1, -1};

    while (1) {
        SceTouchData touch;
        sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
        for (int i = 0; i < SCE_TOUCH_MAX_REPORT; i++) {
            if (i < touch.reportNum) {
                int x = (int)((float)touch.report[i].x * (float)960.0f / 1920.0f);
                int y = (int)((float)touch.report[i].y * (float)544.0f / 1088.0f);
                int id = i;

                if (lastX[i] == -1 || lastY[i] == -1) {
                    //Java_com_twodboy_worldofgoo_DemoRenderer_nativeTouchEvent(&jni, 0, TOUCH_START, x, y, i);
                    Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(&jni, NULL, i, x, y);
                }

                lastX[i] = x;
                lastY[i] = y;
                ids[i] = id;

                if (lastX[i] != x || lastY[i] != y)
                    Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(&jni, NULL, ids, lastX, lastY);

            } else {
                if (lastX[i] != -1 || lastY[i] != -1) {
                    //Java_com_twodboy_worldofgoo_DemoRenderer_nativeTouchEvent(fake_env, 0, TOUCH_END, lastX[i], lastY[i], i);
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
