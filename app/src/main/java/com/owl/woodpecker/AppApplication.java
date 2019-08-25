package com.owl.woodpecker;

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;
import android.util.Log;

import java.lang.ref.Reference;
import java.lang.ref.ReferenceQueue;
import java.lang.ref.WeakReference;

public class AppApplication extends Application implements Application.ActivityLifecycleCallbacks {
    private static final String TAG = "AppApplication";
    ReferenceQueue<FreeObj> referenceQueue = new ReferenceQueue<>();
    WeakReference<FreeObj> wObj1;

    @Override
    public void onCreate() {
        super.onCreate();
        registerActivityLifecycleCallbacks(this);

        new Thread(){
            @Override
            public void run() {
                while (true) {

                    Reference reference = referenceQueue.poll();
                    if (reference != null) {
                        Log.i(TAG, "wObj1 isFree");
                    } else {
                        Log.i(TAG, "wObj1 isAlive");
                    }


                    try {
                        sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                }
            }
        }.start();
    }

    @Override
    public void onActivityCreated(Activity activity, Bundle bundle) {

    }

    @Override
    public void onActivityStarted(Activity activity) {

    }

    @Override
    public void onActivityResumed(Activity activity) {

    }

    @Override
    public void onActivityPaused(Activity activity) {

    }

    @Override
    public void onActivityStopped(Activity activity) {

    }

    @Override
    public void onActivitySaveInstanceState(Activity activity, Bundle bundle) {

    }

    @Override
    public void onActivityDestroyed(Activity activity) {
        if (activity instanceof Main2Activity && wObj1 == null) {
            Log.i(TAG, "onActivityDestroyed: monitor freeObj1");
            wObj1 = new WeakReference<>(((Main2Activity) activity).freeObj1, referenceQueue);
        }
    }
}
