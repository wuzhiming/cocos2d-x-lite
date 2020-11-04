package org.cocos2dx.lib;

import android.app.Activity;
import android.view.KeyEvent;

public class CocosKeyCodeHandler {
    private CocosActivity mAct;

    public native void handleKeyDown(final int keyCode);

    public native void handleKeyUp(final int keyCode);

    public CocosKeyCodeHandler(CocosActivity act) {
        mAct = act;
    }

    public boolean onKeyDown(final int keyCode, final KeyEvent event) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_BACK:
//                Cocos2dxVideoHelper.mVideoHandler.sendEmptyMessage(Cocos2dxVideoHelper.KeyEventBack);
            case KeyEvent.KEYCODE_MENU:
            case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT:
            case KeyEvent.KEYCODE_DPAD_UP:
            case KeyEvent.KEYCODE_DPAD_DOWN:
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
            case KeyEvent.KEYCODE_DPAD_CENTER:
                Cocos2dxHelper.runOnGameThread(new Runnable() {
                    @Override
                    public void run() {
                        handleKeyDown(keyCode);
                    }
                });
                return true;
            default:
                return false;
        }
    }

    public boolean onKeyUp(final int keyCode, KeyEvent event) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_BACK:
            case KeyEvent.KEYCODE_MENU:
            case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT:
            case KeyEvent.KEYCODE_DPAD_UP:
            case KeyEvent.KEYCODE_DPAD_DOWN:
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
            case KeyEvent.KEYCODE_DPAD_CENTER:
                Cocos2dxHelper.runOnGameThread(new Runnable() {
                    @Override
                    public void run() {
                        handleKeyDown(keyCode);
                    }
                });
                return true;
            default:
                return false;
        }
    }
}
