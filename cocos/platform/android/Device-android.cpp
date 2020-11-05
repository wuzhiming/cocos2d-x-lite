/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/


#if CC_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/Device.h"
#include <string.h>
#include <android/log.h>
#include <jni.h>
#include <android_native_app_glue.h>
#include <android/window.h>
#include <android/sensor.h>
#include "platform/android/jni/JniCocosActivity.h"
#include "platform/FileUtils.h"
#include "base/UTF8.h"
#include "platform/android/jni/JniHelper.h"

#ifndef JCLS_HELPER
#define JCLS_HELPER "org/cocos2dx/lib/Cocos2dxHelper"
#endif

#ifndef JCLS_SENSOR
#define JCLS_SENSOR "org/cocos2dx/lib/CocosSensorHandler"
#endif

namespace {
    cc::Device::MotionValue motionValue;
}

namespace cc {

int Device::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        AConfiguration* config = AConfiguration_new();
        AConfiguration_fromAssetManager(config, cocosApp.assetManager);
        int32_t density = AConfiguration_getDensity(config);
        AConfiguration_delete(config);
        dpi = density * 160;
    }
    return dpi;
}

void Device::setAccelerometerEnabled(bool isEnabled)
{
    JniHelper::callStaticVoidMethod(JCLS_SENSOR, "setAccelerometerEnabled", isEnabled);
}

void Device::setAccelerometerInterval(float interval)
{
    JniHelper::callStaticVoidMethod(JCLS_SENSOR, "setAccelerometerInterval", interval);
}

const Device::MotionValue& Device::getDeviceMotionValue()
{
    float* v = JniHelper::callStaticFloatArrayMethod(JCLS_SENSOR,"getDeviceMotionValue");

    motionValue.accelerationIncludingGravityX = v[0];
    motionValue.accelerationIncludingGravityY = v[1];
    motionValue.accelerationIncludingGravityZ = v[2];

    motionValue.accelerationX = v[3];
    motionValue.accelerationY = v[4];
    motionValue.accelerationZ = v[5];

    motionValue.rotationRateAlpha = v[6];
    motionValue.rotationRateBeta = v[7];
    motionValue.rotationRateGamma = v[8];

    return motionValue;
}

Device::Rotation Device::getDeviceRotation()
{
    int rotation = JniHelper::callStaticIntMethod(JCLS_HELPER, "getDeviceRotation");
    return (Device::Rotation)rotation;
}

std::string Device::getDeviceModel()
{
    return JniHelper::callStaticStringMethod(JCLS_HELPER, "getDeviceModel");
}

void Device::setKeepScreenOn(bool value)
{
    // JniHelper::callStaticVoidMethod(JCLS_HELPER, "setKeepScreenOn", value);
//    ANativeActivity_setWindowFlags(JniHelper::getAndroidApp()->activity, AWINDOW_FLAG_KEEP_SCREEN_ON, 0);
}

void Device::vibrate(float duration)
{
    JniHelper::callStaticVoidMethod(JCLS_HELPER, "vibrate", duration);
}

float Device::getBatteryLevel()
{
    return JniHelper::callStaticFloatMethod(JCLS_HELPER, "getBatteryLevel");
}

Device::NetworkType Device::getNetworkType()
{
    return (Device::NetworkType)JniHelper::callStaticIntMethod(JCLS_HELPER, "getNetworkType");
}

cc::Vec4 Device::getSafeAreaEdge()
{
    // no SafeArea concept on android, return ZERO Vec4.
    return cc::Vec4();
}

int Device::getDevicePixelRatio()
{
    return 1;
}
}

#endif // CC_PLATFORM == CC_PLATFORM_ANDROID
