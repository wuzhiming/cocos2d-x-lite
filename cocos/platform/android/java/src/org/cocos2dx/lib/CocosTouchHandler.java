package org.cocos2dx.lib;

import android.content.Context;
import android.util.Log;
import android.view.MotionEvent;

public class CocosTouchHandler {
    public final static String TAG = "CocosTouchHandler";
    private boolean mStopHandleTouchAndKeyEvents = false;
    private CocosActivity mAct;

    public CocosTouchHandler(CocosActivity act) {
        mAct = act;
    }

    boolean onTouchEvent(MotionEvent pMotionEvent) {
        // these data are used in ACTION_MOVE and ACTION_CANCEL
        final int pointerNumber = pMotionEvent.getPointerCount();
        final int[] ids = new int[pointerNumber];
        final float[] xs = new float[pointerNumber];
        final float[] ys = new float[pointerNumber];

        for (int i = 0; i < pointerNumber; i++) {
            ids[i] = pMotionEvent.getPointerId(i);
            xs[i] = pMotionEvent.getX(i);
            ys[i] = pMotionEvent.getY(i);
        }

        switch (pMotionEvent.getAction() & MotionEvent.ACTION_MASK) {
            case MotionEvent.ACTION_POINTER_DOWN:
                if (mStopHandleTouchAndKeyEvents) {
//                    Cocos2dxEditBox.complete();
                    return true;
                }

                final int indexPointerDown = pMotionEvent.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                final int idPointerDown = pMotionEvent.getPointerId(indexPointerDown);
                final float xPointerDown = pMotionEvent.getX(indexPointerDown);
                final float yPointerDown = pMotionEvent.getY(indexPointerDown);
                Cocos2dxHelper.runOnGameThread(new Runnable() {
                    @Override
                    public void run() {
                        handleActionDown(idPointerDown, xPointerDown, yPointerDown);
                    }
                });
                break;

            case MotionEvent.ACTION_DOWN:
                if (mStopHandleTouchAndKeyEvents) {
//                    Cocos2dxEditBox.complete();
                    return true;
                }

                // there are only one finger on the screen
                final int idDown = pMotionEvent.getPointerId(0);
                final float xDown = xs[0];
                final float yDown = ys[0];

                Cocos2dxHelper.runOnGameThread(new Runnable() {
                    @Override
                    public void run() {
                        handleActionDown(idDown, xDown, yDown);
                    }
                });

                break;

            case MotionEvent.ACTION_MOVE:
                Cocos2dxHelper.runOnGameThread(new Runnable() {
                    @Override
                    public void run() {
                        handleActionMove(ids, xs, ys);
                    }
                });

                break;

            case MotionEvent.ACTION_POINTER_UP:
                final int indexPointUp = pMotionEvent.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                final int idPointerUp = pMotionEvent.getPointerId(indexPointUp);
                final float xPointerUp = pMotionEvent.getX(indexPointUp);
                final float yPointerUp = pMotionEvent.getY(indexPointUp);
                Cocos2dxHelper.runOnGameThread(new Runnable() {
                    @Override
                    public void run() {
                        handleActionUp(idPointerUp, xPointerUp, yPointerUp);
                    }
                });

                break;

            case MotionEvent.ACTION_UP:
                // there are only one finger on the screen
                final int idUp = pMotionEvent.getPointerId(0);
                final float xUp = xs[0];
                final float yUp = ys[0];
                Cocos2dxHelper.runOnGameThread(new Runnable() {
                    @Override
                    public void run() {
                        handleActionUp(idUp, xUp, yUp);
                    }
                });

                break;

            case MotionEvent.ACTION_CANCEL:
                Cocos2dxHelper.runOnGameThread(new Runnable() {
                    @Override
                    public void run() {
                        handleActionCancel(ids, xs, ys);
                    }
                });
                break;
        }

        if (BuildConfig.DEBUG) {
            CocosTouchHandler.dumpMotionEvent(pMotionEvent);
        }
        return true;
    }

    public void setStopHandleTouchAndKeyEvents(boolean value) {
        mStopHandleTouchAndKeyEvents = value;
    }

    private static void dumpMotionEvent(final MotionEvent event) {
        final String names[] = {"DOWN", "UP", "MOVE", "CANCEL", "OUTSIDE", "POINTER_DOWN", "POINTER_UP", "7?", "8?", "9?"};
        final StringBuilder sb = new StringBuilder();
        final int action = event.getAction();
        final int actionCode = action & MotionEvent.ACTION_MASK;
        sb.append("event ACTION_").append(names[actionCode]);
        if (actionCode == MotionEvent.ACTION_POINTER_DOWN || actionCode == MotionEvent.ACTION_POINTER_UP) {
            sb.append("(pid ").append(action >> MotionEvent.ACTION_POINTER_INDEX_SHIFT);
            sb.append(")");
        }
        sb.append("[");
        for (int i = 0; i < event.getPointerCount(); i++) {
            sb.append("#").append(i);
            sb.append("(pid ").append(event.getPointerId(i));
            sb.append(")=").append((int) event.getX(i));
            sb.append(",").append((int) event.getY(i));
            if (i + 1 < event.getPointerCount()) {
                sb.append(";");
            }
        }
        sb.append("]");
        Log.d(TAG, sb.toString());
    }

    native void handleActionDown(final int id, final float x, final float y);

    native void handleActionMove(final int[] ids, final float[] xPointerList, final float[] yPointerList);

    native void handleActionUp(final int id, final float x, final float y);

    native void handleActionCancel(final int[] ids, final float[] xPointerList, final float[] yPointerList);

}
