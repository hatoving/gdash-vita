#include <falso_jni/FalsoJNI_Impl.h>
#include "utils/logger.h"

/*
 * JNI Methods
*/

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

jboolean gameServicesIsSignedIn(int id, va_list args) {
	logv_debug("JNI: Method Call: gameServicesIsSignedIn() / id: %i", id);
	return JNI_FALSE;
}

jobject createTextBitmapShadowStroke(int id, va_list args) {
	logv_debug("JNI: Method Call: createTextBitmapShadowStroke() / id: %i", id);
	return (jobject)strdup("0");
}

NameToMethodID nameToMethodId[] = {
	{10, "getUserID", METHOD_TYPE_OBJECT},
	{11, "getDeviceRefreshRate", METHOD_TYPE_FLOAT},
	{12, "setAnimationInterval", METHOD_TYPE_VOID},
	{13, "createTextBitmapShadowStroke", METHOD_TYPE_OBJECT},
	{14, "loadingFinished", METHOD_TYPE_VOID},
	{15, "gameServicesIsSignedIn", METHOD_TYPE_BOOLEAN},
	{16, "openURL", METHOD_TYPE_VOID},
};

MethodsBoolean methodsBoolean[] = {
	{15, gameServicesIsSignedIn},
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
	{15, openURL}
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
