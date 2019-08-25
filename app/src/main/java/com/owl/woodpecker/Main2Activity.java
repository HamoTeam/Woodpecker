package com.owl.woodpecker;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

public class Main2Activity extends AppCompatActivity {
    public FreeObj[] freeObj = new FreeObj[1000];
    public FreeObj freeObj1 = new FreeObj();
    public FreeObj freeObj2 = new FreeObj();
    public FreeObj freeObj3 = new FreeObj();
    public FreeObj freeObj4 = new FreeObj();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        findViewById(R.id.btn_gcstart).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Runtime.getRuntime().gc();
            }
        });
        findViewById(R.id.btn_obj_free).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                freeObj = null;
                freeObj1 = null;
                freeObj2 = null;
                freeObj3 = null;
                freeObj4 = null;
            }
        });
    }
}
