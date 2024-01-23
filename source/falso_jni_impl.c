#include <falso_jni/FalsoJNI_Impl.h>
#include <falso_jni/FalsoJNI.h>

#include <so_util/so_util.h>
#include <vitaGL.h>
#include <stdio.h>

#include "utils/dialog.h"
#include "utils/logger.h"

/*
 * JNI Methods
*/

int keyboard_active = 0;
extern so_module so_mod;

jobject getUserId(jmethodID id, va_list args) {
    logv_debug("JNI: Method Call: getUserId() / id: %i", id);
    return (jobject) strdup("0");
}

jfloat getDeviceRefreshRate(jmethodID id, va_list args) {
    logv_debug("JNI: Method Call: getDeviceRefreshRate() / id: %i", id);
    return (jfloat)60.0f;
}

void setAnimationInterval(int id, va_list args) {
	logv_debug("JNI: Method Call: setAnimationInterval() / id: %i", id);
}

void loadingFinished(int id, va_list args) {
	logv_debug("JNI: Method Call: loadingFinished() / id: %i", id);
}

void openURL(int id, va_list args) {
	logv_debug("JNI: Method Call: openURL() / id: %i", id);
}

void setKeyboardState(int id, va_list args) {
	logv_debug("JNI: Method Call: setKeyboardState() / id: %i", id);
}

void closeIMEKeyboard(int id, va_list args) {
	logv_debug("JNI: Method Call: closeIMEKeyboard() / id: %i", id);
}

void openIMEKeyboard(int id, va_list args) {
	logv_debug("JNI: Method Call: openIMEKeyboard() / id: %i", id);

	int (* Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInsertText)(JNIEnv* env, jobject thiz, jstring text)
        = (void *)so_symbol(&so_mod, "Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInsertText");

	int active = 1;
	init_ime_dialog("Please input your answer.", "");

	while(active == 1) {
		char* r = get_ime_dialog_result();
		if (r) {
			logv_debug("RESULT: %s", r);
			Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInsertText(&jni, NULL, r);
			active = 0;
		}
		vglSwapBuffers(GL_TRUE);
	}
}

jboolean gameServicesIsSignedIn(int id, va_list args) {
	logv_debug("JNI: Method Call: gameServicesIsSignedIn() / id: %i", id);
	return JNI_FALSE;
}

jboolean isNetworkAvailable(int id, va_list args) {
	logv_debug("JNI: Method Call: isNetworkAvailable() / id: %i", id);
	return JNI_TRUE;
}

jobject createTextBitmapShadowStroke(int id, va_list args) {
	logv_debug("JNI: Method Call: createTextBitmapShadowStroke() / id: %i", id);
	return (jobject)strdup("0");
}

void terminateProcess(int id, va_list args) {
	logv_debug("JNI: Method Call: terminateProcess() / id: %i", id);
	sceKernelExitProcess(0);
}

NameToMethodID nameToMethodId[] = {
	{10, "getUserID", METHOD_TYPE_OBJECT},
	{11, "getDeviceRefreshRate", METHOD_TYPE_FLOAT},
	{12, "setAnimationInterval", METHOD_TYPE_VOID},
	{13, "createTextBitmapShadowStroke", METHOD_TYPE_OBJECT},
	{14, "loadingFinished", METHOD_TYPE_VOID},
	{15, "gameServicesIsSignedIn", METHOD_TYPE_BOOLEAN},
	{16, "openURL", METHOD_TYPE_VOID},
	{17, "setKeyboardState", METHOD_TYPE_VOID},
	{18, "openIMEKeyboard", METHOD_TYPE_VOID},
	{19, "closeIMEKeyboard", METHOD_TYPE_VOID},
	{20, "isNetworkAvailable", METHOD_TYPE_BOOLEAN},
	{21, "terminateProcess", METHOD_TYPE_VOID},
};

MethodsBoolean methodsBoolean[] = {
	{15, gameServicesIsSignedIn},
	{20, isNetworkAvailable}
};
MethodsByte methodsByte[] = {};
MethodsChar methodsChar[] = {};
MethodsDouble methodsDouble[] = {};
MethodsFloat methodsFloat[] = {
	{11, getDeviceRefreshRate},
};
MethodsInt methodsInt[] = {};
MethodsLong methodsLong[] = {};
MethodsObject methodsObject[] = {
	{10, getUserId},
	{13, createTextBitmapShadowStroke},
};
MethodsShort methodsShort[] = {};
MethodsVoid methodsVoid[] = {
	{12, setAnimationInterval},
	{14, loadingFinished},
	{16, openURL},
	{17, setKeyboardState},
	{18, openIMEKeyboard},
	{19, closeIMEKeyboard},
	{21, terminateProcess}
};

/*
 * JNI Fields
*/

// System-wide constant that applications sometimes request
// https://developer.android.com/reference/android/content/Context.html#WINDOW_SERVICE
char WINDOW_SERVICE[] = "window";

// System-wide constant that's often used to determine Android version
// https://developer.android.com/reference/android/os/Build.VERSION.html#SDK_INT
// Possible values: https://developer.android.com/reference/android/os/Build.VERSION_CODES
const int SDK_INT = 21; // Android 5.0, Lollipop

NameToFieldID nameToFieldId[] = {
		{ 0, "WINDOW_SERVICE", FIELD_TYPE_OBJECT }, 
		{ 1, "SDK_INT", FIELD_TYPE_INT },
};

FieldsBoolean fieldsBoolean[] = {};
FieldsByte fieldsByte[] = {};
FieldsChar fieldsChar[] = {};
FieldsDouble fieldsDouble[] = {};
FieldsFloat fieldsFloat[] = {};
FieldsInt fieldsInt[] = {
		{ 1, SDK_INT },
};
FieldsObject fieldsObject[] = {
		{ 0, WINDOW_SERVICE },
};
FieldsLong fieldsLong[] = {};
FieldsShort fieldsShort[] = {};

__FALSOJNI_IMPL_CONTAINER_SIZES
