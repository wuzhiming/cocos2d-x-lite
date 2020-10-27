package org.cocos2dx.lib;

import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.FrameLayout;

import java.io.File;

public class CocosActivity extends Activity implements SurfaceHolder.Callback {
    private native void onCreateNative(Activity activity, AssetManager assetManager, String obbPath, int sdkVersion);
    private native void onSurfaceCreatedNative(Surface surface);
    private native void onSurfaceChangedNative(int width, int height);
    private native void onSurfaceDestroyNative();
    private native void onPauseNative();
    private native void onResumeNative();
    private native void onStopNative();
    private native void onStartNative();
    private native void onLowMemoryNative();
    private native void onWindowFocusChangedNative(boolean hasFocus);

    private boolean mDestroyed;
    private SurfaceHolder mSurfaceHolder;
    private FrameLayout mFrameLayout;
    private SurfaceView mSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        GlobalObject.setActivity(this);
        Cocos2dxHelper.registerBatteryLevelReceiver(this);
        Cocos2dxHelper.init(this);
        CanvasRenderingContext2DImpl.init(this);
        onLoadNativeLibraries();
        this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_NOTHING);
        initView();
        onCreateNative(this, getAssets(), getAbsolutePath(getObbDir()), Build.VERSION.SDK_INT);
    }

    private static String getAbsolutePath(File file) {
        return (file != null) ? file.getAbsolutePath() : null;
    }

    protected void initView() {
        ViewGroup.LayoutParams frameLayoutParams = new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT);
        mFrameLayout = new FrameLayout(this);
        mFrameLayout.setLayoutParams(frameLayoutParams);
        setContentView(mFrameLayout);

        mSurfaceView = new SurfaceView(this);
        mSurfaceView.getHolder().addCallback(this);
        mFrameLayout.addView(mSurfaceView);
    }

    @Override
    protected void onDestroy() {
        mDestroyed = true;
//        if (mSurfaceHolder != null) {
//            onSurfaceDestroyNative();
//            mSurfaceHolder = null;
//        }
        super.onDestroy();
    }

    @Override
    protected void onPause() {
        super.onPause();
//        onPauseNative();
    }

    @Override
    protected void onResume() {
        super.onResume();
//        onResumeNative();
    }

    @Override
    protected void onStop() {
        super.onStop();
//        onStopNative();
    }

    @Override
    protected void onStart() {
        super.onStart();
//        onStartNative();
    }

    @Override
    public void onLowMemory() {
        super.onLowMemory();
//        if (!mDestroyed) {
//            onLowMemoryNative();
//        }
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
//        super.onWindowFocusChanged(hasFocus);
//        if (!mDestroyed) {
//            onWindowFocusChangedNative(hasFocus);
//        }
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        if (!mDestroyed) {
            mSurfaceHolder = holder;
            onSurfaceCreatedNative(holder.getSurface());
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
//        if (!mDestroyed) {
//            mSurfaceHolder = holder;
//            onSurfaceChangedNative(width, height);
//        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        mSurfaceHolder = null;
//        if (!mDestroyed) {
//            onSurfaceDestroyNative();
//        }
    }

    private void onLoadNativeLibraries() {
        try {
            ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            Bundle bundle = ai.metaData;
            String libName = bundle.getString("android.app.lib_name");
            System.loadLibrary(libName);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
