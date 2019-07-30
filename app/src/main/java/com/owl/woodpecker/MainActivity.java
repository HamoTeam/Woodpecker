package com.owl.woodpecker;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
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

        // findViewById(R.id.btn_test).setOnClickListener(new View.OnClickListener() {
        //     @Override
        //     public void onClick(View v) {
        //         String jniValue = testJni.stringFromJNI();
        //
        //         Log.i(TAG, "jniString:" + jniValue);
        //     }
        // });


        findViewById(R.id.btn_attach).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testJni.attachAgent(getApplication());
            }
        });


        findViewById(R.id.btn_startActy).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Main2Activity.class);
                startActivity(intent);
            }
        });
    }
}
