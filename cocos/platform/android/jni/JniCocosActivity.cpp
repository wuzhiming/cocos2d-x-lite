#include "JniCocosActivity.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/FileUtils-android.h"
#include "platform/Application.h"
#include <jni.h>
#include <android/log.h>
#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>
#include <thread>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "CocosActivity JNI", __VA_ARGS__)

cc::Application *cocos_main(int, int) __attribute__((weak));

namespace cc {
CocosApp cocosApp;

void glThreadEntry(ANativeWindow *window) {
	int width = ANativeWindow_getWidth(window);
	int height = ANativeWindow_getHeight(window);
	auto game = cocos_main(width, height);
	game->init();
	if (!game) return;

	while (1) {
	    LOGD("tick .......");
		JniHelper::callStaticVoidMethod("org.cocos2dx.lib.Cocos2dxHelper", "flushTasksOnGameThread");
		game->tick();
	}
}
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
    if(cc::Application::getInstance()) return;
    cc::cocosApp.window = ANativeWindow_fromSurface(env, surface);

    std::thread glThread(cc::glThreadEntry, cc::cocosApp.window);
    glThread.detach();
}
JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onStartNative(JNIEnv *env, jobject obj) {

}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onPauseNative(JNIEnv *env, jobject obj) {
    cc::Application::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
    	cc::onPaused = true;
	    cc::Application::getInstance()->onPause();
    });
}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onResumeNative(JNIEnv *env, jobject obj) {
    if(!cc::Application::getInstance()->getScheduler()) return;
    cc::onPaused = false;
    cc::Application::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
	    cc::Application::getInstance()->onResume();
    });
}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onStopNative(JNIEnv *env, jobject obj) {

}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onLowMemoryNative(JNIEnv *env, jobject obj) {

}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onWindowFocusChangedNative(JNIEnv *env, jobject obj, jboolean has_focus) {

}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onSurfaceChangedNative(JNIEnv *env, jobject obj, jint width, jint height) {

}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CocosActivity_onSurfaceDestroyNative(JNIEnv *env, jobject obj) {

}

}
