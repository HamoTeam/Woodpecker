package com.owl.woodpecker;

import android.util.Log;

public class FreeObj {
    private static final String TAG = "FreeObj";
    public FreeObj() {
        Log.i(TAG, "new FreeObj");
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        Log.i(TAG, "finalize: FreeObj");
    }
}
