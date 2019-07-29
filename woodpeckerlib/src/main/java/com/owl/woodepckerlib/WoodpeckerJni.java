package com.owl.woodepckerlib;

public class WoodpeckerJni {
    static {
        System.loadLibrary("woodpecker-lib");
    }

    public native String stringFromJNI();

}
