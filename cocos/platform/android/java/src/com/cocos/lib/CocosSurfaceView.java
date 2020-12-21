package com.cocos.lib;

import android.content.Context;
import android.view.SurfaceView;

public class CocosSurfaceView extends SurfaceView {

    public CocosSurfaceView(Context context) {
        super(context);
    }

    public native void nativeOnSizeChanged(final int width, final int height);

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        CocosHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                nativeOnSizeChanged(w, h);
            }
        });
    }
}
