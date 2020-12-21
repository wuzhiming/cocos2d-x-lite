package com.cocos.lib;

import android.content.Context;
import android.view.OrientationEventListener;

public class CocosOrientationHelper extends OrientationEventListener {

    private int currentOrientation;

    public CocosOrientationHelper(Context context) {
        super(context);
        currentOrientation = CocosHelper.getDeviceRotation();
    }

    public void onPause() {
        this.disable();
    }

    public void onResume() {
        this.enable();
    }

    @Override
    public void onOrientationChanged(int orientation) {
        int curOrientation = CocosHelper.getDeviceRotation();
        if (curOrientation != currentOrientation) {
            currentOrientation = CocosHelper.getDeviceRotation();
            CocosHelper.runOnGameThread(new Runnable() {
                @Override
                public void run() {
                    nativeOnOrientationChanged(currentOrientation);
                }
            });
        }
    }

    public static native void nativeOnOrientationChanged(int rotation);
}