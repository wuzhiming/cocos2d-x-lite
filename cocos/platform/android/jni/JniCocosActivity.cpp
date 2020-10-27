#include "JniCocosActivity.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/FileUtils-android.h"
#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>
#include <thread>

void cocos_main(ANativeWindow *) __attribute__((weak));

namespace cc {
CocosApp cocosApp;
}

extern "C" {

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onCreateNative(JNIEnv *env, jobject obj, jobject activity,
	jobject assetMgr, jstring obbPath, jint sdkVersion) {
	cc::cocosApp.sdkVersion = sdkVersion;
	cc::JniHelper::init(env, activity);
	cc::cocosApp.obbPath = cc::JniHelper::jstring2string(obbPath);
	cc::cocosApp.assetManager = AAssetManager_fromJava(env, assetMgr);
	static_cast<cc::FileUtilsAndroid*>(cc::FileUtils::getInstance())->setassetmanager(cc::cocosApp.assetManager);
}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onSurfaceCreatedNative(JNIEnv *env, jobject obj, jobject surface) {
    cc::cocosApp.window = ANativeWindow_fromSurface(env, surface);

    std::thread glThread(cocos_main, cc::cocosApp.window);
    glThread.detach();
}

}