package com.owl.woodpecker;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.owl.woodepckerlib.WoodpeckerJni;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        final WoodpeckerJni testJni = new WoodpeckerJni();

        findViewById(R.id.btn_test).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String jniValue = testJni.stringFromJNI();

                Log.i(TAG, "jniString:" + jniValue);
            }
        });
    }
}
