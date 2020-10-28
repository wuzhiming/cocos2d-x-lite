#include "JniCocosActivity.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/FileUtils-android.h"
#include "platform/Application.h"
#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>
#include <thread>

cc::Application *cocos_main(int, int) __attribute__((weak));

namespace cc {
CocosApp cocosApp;

void glThreadEntry(ANativeWindow *window) {
	int width = ANativeWindow_getWidth(window);
	int height = ANativeWindow_getHeight(window);
	auto game = cocos_main(width, height);
	if (!game) return;

	while (1) {
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
    cc::cocosApp.window = ANativeWindow_fromSurface(env, surface);

    std::thread glThread(cc::glThreadEntry, cc::cocosApp.window);
    glThread.detach();
}

}