package com.example.memorytest;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import androidx.core.app.ActivityCompat;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.io.File;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("memory_test_cpp");
    }

    private static String[] PERMISSIONS_STORAGE = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE};
    private static int REQUEST_PERMISSION_CODE = 1;
    private long usedMemory = 0, allocatedMemory = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ActivityCompat.requestPermissions(this, PERMISSIONS_STORAGE, REQUEST_PERMISSION_CODE);

        onClick_java();
        onClick_cpp();
    }

    private void onClick_java() {
        final Button button = findViewById(R.id.test_java);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                String msg = "";
                msg = _checkJava_manually();
                System.out.println("msg = " + msg);
            }
        });
    }

    private void onClick_cpp() {
        final Button button = findViewById(R.id.test_cpp);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                String msg = "";
                String res_msg = "";
                res_msg = _checkCpp_manually();
                msg  = "used: " + usedMemory + "MB\n" + "allocated: " + allocatedMemory + "MB";
                System.out.println(msg);
                AlertDialog error_info = new AlertDialog.Builder(MainActivity.this)
                        .setTitle(res_msg)
                        .setMessage(msg)
                        .create();
                error_info.show();
            }
        });
    }

    private String _checkJava_manually(){
        final Runtime runtime = Runtime.getRuntime();
        final long maxHeapSizeInMB = runtime.maxMemory() / 1048576L;
        int seg_size_MB = 10; // 10MB
        ArrayList data = new ArrayList<byte[]>();
        long usedMemInMB = 0;
        allocatedMemory = 0;
        String msg = "";

//        File mem_prof = new File(this.getExternalFilesDir(null), "memory_profile_out");
//        if (mem_prof.exists()) {
//            mem_prof.delete();
//        }
//        if (!mem_prof.exists()) {
//            mem_prof.mkdirs();
//        }
//        System.out.println(mem_prof.getAbsolutePath());
//
//        File locationToSave = new File(mem_prof, "java_out.txt");
//        try {
//            locationToSave.createNewFile();
//        } catch (Exception e) {
//            e.printStackTrace();
//        }

        try {
            for (int i = 1; i < 1024; i++) {
                byte[] new_data = new byte[seg_size_MB * 1024 * 1024];
                usedMemInMB = (runtime.totalMemory() - runtime.freeMemory()) / 1048576L;
                usedMemory = usedMemInMB;
                allocatedMemory += seg_size_MB;
                msg = "heap memory:" + usedMemInMB + "/" + maxHeapSizeInMB + " (" + Long.toString(i * seg_size_MB) + ")\n";
                Log.v("checkJava", msg);

//                FileWriter writer = new FileWriter(locationToSave, true);
//                writer.write(msg);
//                writer.close();

                data.add(new_data);
            }
        } catch (Error e) {
            data = null;
            msg  = "used: " + usedMemory + "MB\n" + "allocated: " + allocatedMemory + "MB";
            AlertDialog error_info = new AlertDialog.Builder(MainActivity.this)
                    .setTitle("OOM Error(java):")
                    .setMessage(msg)
                    .create();
            error_info.show();
            return msg;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return msg;
    }

    private native String _checkCpp_manually();
}