package org.opencv.pcnn;

import java.util.Vector;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Mat;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;
import org.opencv.pcnn.R;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceView;
import android.view.View;
import android.view.WindowManager;
import android.view.animation.RotateAnimation;
import android.view.animation.TranslateAnimation;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ProgressBar;

public class MainActivity extends Activity implements CvCameraViewListener2 {
    private static final String TAG = "OCVSample::Activity";

    private CameraBridgeViewBase mOpenCvCameraView;
    
    ProgressBar ProgressBar;
    ImageButton startButton;
    Context context;
    
    //PCNN data
    private Vector<Mat> images = new Vector<Mat>();
    MyTimer timer = new MyTimer();
    int FRAME_NO = 5;
    double TIME_ITERVAL = 200; //time interval in second
    int DIM = 128; //image dimension
    int GESTURE_NO = 1;
    boolean start = false;
    boolean finish = true;
    
    

    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    Log.i(TAG, "OpenCV loaded successfully");
                    mOpenCvCameraView.enableView();
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
    };

    public MainActivity() {
        Log.i(TAG, "Instantiated new " + this.getClass());
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.tutorial1_surface_view);

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.tutorial1_activity_java_surface_view);
        
        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);

        mOpenCvCameraView.setCvCameraViewListener(this);
        //System.loadLibrary(org.opencv.core.Core.NATIVE_LIBRARY_NAME);
        
        context = this;
        ProgressBar = (ProgressBar) findViewById(R.id.progressBar1);
        startButton = (ImageButton) findViewById(R.id.start);
        startButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if(finish){
                	finish = false;
                	start = true;
					runOnUiThread(new Runnable() {
						@Override
						public void run() {
							ProgressBar.setVisibility(View.VISIBLE);

						}
					});
                }
            }
        });
		// rotation from 0 to 90 degrees here
//		float x = bstart.getX(),y = bstart.getY();
//		RotateAnimation a = new RotateAnimation(0, -90, -bstart.getWidth()/(float)2, -bstart.getHeight()/(float)2);
//		TranslateAnimation t = new TranslateAnimation(0, x, 0, y);
//		a.setFillAfter(true);
//		a.setDuration(0);
//		bstart.startAnimation(a);
//		bstart.startAnimation(t);
	}

    @Override
    public void onPause()
    {
        super.onPause();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    @Override
    public void onResume()
    {
        super.onResume();
        if (!OpenCVLoader.initDebug()) {
            Log.d(TAG, "Internal OpenCV library not found. Using OpenCV Manager for initialization");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_0_0, this, mLoaderCallback);
        } else {
            Log.d(TAG, "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
    }

    public void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    public void onCameraViewStarted(int width, int height) {
    }

    public void onCameraViewStopped() {
    }
    
    int gestureCount = 0;
    PCNNProcessor lastPcnnThread;
    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
    	Mat rgba = inputFrame.rgba();
    	//getTraspose(rgba);
    	
    	if(gestureCount < GESTURE_NO && start){
    		if(timer.getPassedTime() >= TIME_ITERVAL){
    			timer.reset();
    			images.add(rgba.clone());
    			Log.i("PCNNPOCESSOR", "PCNNPOCESSOR Take image " + images.size());
    		}
    		
    		if(FRAME_NO == images.size()){
    			gestureCount++;
    			Log.i("PCNNPOCESSOR", "PCNNPOCESSOR Start PCNN " + gestureCount);
    			PCNNProcessor pcnnThread = new PCNNProcessor(DIM, DIM);
    			pcnnThread.setImages((Vector<Mat>)images.clone());
    			pcnnThread.setContext(context);
    			images.clear();
    			pcnnThread.start();
    			lastPcnnThread = pcnnThread;
    			
    		}
    	}else if(lastPcnnThread != null && !lastPcnnThread.isAlive()){
    		start = false;
    		gestureCount = 0;
    		finish = true;
    		runOnUiThread(new Runnable() {
				@Override
				public void run() {
					ProgressBar.setVisibility(View.INVISIBLE);

				}
			});
    		
    	}
        return rgba;
    }
    
    public Mat getTraspose(Mat m){
    	Size s = m.size();
    	float[] mdata = new float[(int) (m.total() * m.channels())];
		m.get(0, 0, mdata);
    	Mat t = new Mat((int)s.width,(int)s.height, m.type());
    	for(int i = 0 ;i < (int)s.height;++i)
    		for(int j = 0 ;j < (int)s.width;++j){
    			//float[] = new float[4];
     			t.put(j, i, m.get(i, j));
    	}
    			
    	return t;
    }
}
