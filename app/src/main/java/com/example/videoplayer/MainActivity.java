package com.example.videoplayer;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import com.example.videoplayer.databinding.ActivityMainBinding;

import java.io.File;

public class MainActivity extends MediaCodecDecoderLifeCycle implements SurfaceHolder.Callback {
    private static final String TAG = "MainActivity2";

    // Used to load the 'videoplayer' library on application startup.
    static {
        System.loadLibrary("videoplayer");
    }

    private ActivityMainBinding binding;
    private String testPath;
    private SurfaceView surfaceView;
    float playTimeSeconds = 0.0f;
    float bufferedTimeSeconds = 0.0f;
    float totalDuration = 0.0f;
    public static final int UPDATE_PLAY_VIEDO_TIME_FLAG = 1201;
    private static final int PLAY_END_FLAG = 12330;
    private Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case UPDATE_PLAY_VIEDO_TIME_FLAG:

                    break;
                case PLAY_END_FLAG:
                    Toast.makeText(MainActivity.this, "播放结束了！", Toast.LENGTH_SHORT).show();
                    break;
                default:
                    break;
            }
        }

    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        surfaceView = binding.sampleSurface;
        surfaceView.getHolder().addCallback(this);

        String assertDir = "picture";
        AssectsUtil.loadAssetsDirfile(getApplicationContext(),assertDir);
        String appFilePath = AssectsUtil.getAppDir(getApplicationContext(),assertDir)+ File.separator;
        Log.d(TAG,"appFilePath="+appFilePath);
        testPath = appFilePath+"Butterfly.mp4";
    }

    /**
     * A native method that is implemented by the 'videoplayer' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void onSurfaceCreated(final Surface surface);

    public native void onSurfaceDestroyed(final Surface surface);

    /**
     * 初始化
     *
     * @param srcFilenameParam
     *            文件路径或者直播地址
     * @return 是否正确初始化
     */
    public native boolean prepare(String srcFilenameParam, int[] max_analyze_durations, int size, int probesize, boolean fpsProbesizeConfigured,
                                  float minBufferedDuration, float maxBufferedDuration, int width, int height, Surface surface);

    /**
     * 暂停播放
     */
    public native void pause();

    /**
     * 继续播放
     */
    public native void play();



    public native void stop();

    /**
     * 获得缓冲进度 返回秒数（单位秒 但是小数点后有3位 精确到毫秒）
     */
    public native float getBufferedProgress();

    /**
     * 获得播放进度（单位秒 但是小数点后有3位 精确到毫秒）
     */
    public native float getPlayProgress();

    /**
     * 跳转到某一个位置
     */
    public native void seekToPosition(float position);

    /**
     * 只做seek操作，seek到指定位置
     */
    public native void seekCurrent(float position);

    public native void beforeSeekCurrent();
    public native void afterSeekCurrent();
    public native void resetRenderSize(int left, int top, int width, int height);

    boolean isFirst = true;
    SurfaceHolder surfaceHolder = null;

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {
        surfaceHolder = holder;
        Log.d(TAG, "surfaceCreated a");
        if (isFirst) {
            Log.d(TAG, "surfaceCreated b");

            Surface surface = holder.getSurface();
            int width = getWindowManager().getDefaultDisplay().getWidth();
            int height = getWindowManager().getDefaultDisplay().getHeight();
            int[] max_analyze_durations = new int[]{-1, -1, -1};
            prepare(testPath, max_analyze_durations, max_analyze_durations.length, -1, true, 0.5f, 1.0f, width, height, holder.getSurface());
            isFirst = false;
        } else {
            onSurfaceCreated(holder.getSurface());
        }

    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder surfaceHolder, int i, int i1, int i2) {

    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder surfaceHolder) {

    }

    public void viewStreamMetaCallback(final int width, final int height, float duration) {
        totalDuration = duration;
        handler.post(new Runnable() {

            @Override
            public void run() {
                int screenWidth = getWindowManager().getDefaultDisplay().getWidth();
                int drawHeight = (int) ((float) screenWidth / ((float) width / (float) height));
                ViewGroup.LayoutParams params = (ViewGroup.LayoutParams) surfaceView.getLayoutParams();
                params.height = drawHeight;
                surfaceView.setLayoutParams(params);

               resetRenderSize(0, 0, screenWidth, drawHeight);
            }
        });
    }

    public void onInitializedFromNative(boolean initCode) {

    }
}