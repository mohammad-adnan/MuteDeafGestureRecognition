package org.opencv.pcnn;

import java.io.InputStream;
import java.util.Date;
import java.util.Scanner;
import java.util.Vector;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.CvType;
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
    ImageButton flipButton;
    Context context;
    int cameraID = 99;
    
    //PCNN data
    private Vector<Mat> images = new Vector<Mat>();
    MyTimer timer = new MyTimer();
    int FRAME_NO = 5;
    double TIME_ITERVAL = 500; //time interval in second
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
                    mOpenCvCameraView.setCameraIndex(mOpenCvCameraView.CAMERA_ID_BACK);
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
//            	InputStream inputStream = getResources().openRawResource(R.raw.weights);
//            	Scanner sc = new Scanner(inputStream);
//            	float f = sc.nextFloat();
//            	sc.close();
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
        flipButton = (ImageButton) findViewById(R.id.flip);
        flipButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				 mOpenCvCameraView.disableView();
				 if(cameraID == mOpenCvCameraView.CAMERA_ID_BACK){
					 mOpenCvCameraView.setCameraIndex(mOpenCvCameraView.CAMERA_ID_FRONT);
					 cameraID = mOpenCvCameraView.CAMERA_ID_FRONT;
					 }
				 else{
					 mOpenCvCameraView.setCameraIndex(mOpenCvCameraView.CAMERA_ID_BACK);
					 cameraID = mOpenCvCameraView.CAMERA_ID_BACK;
					 }
                 mOpenCvCameraView.enableView();
				
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
    MyTimer t1 = new MyTimer();
    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
    	
    	Mat rgba = inputFrame.rgba();
    	
    	//getTraspose(rgba);
    	if(gestureCount < GESTURE_NO && start){
    		if(timer.getPassedTime() >= TIME_ITERVAL){
    			timer.reset();
    			Mat resultMat = new Mat();
    			//flip(rgba,resultMat, -90);
    			images.add(rgba.clone());
    			Log.i("PCNNPOCESSOR", "PCNNPOCESSOR Take image " + images.size() + "in time : " + t1.getPassedTime()/1000 + "sec");
    			t1.reset();
    		}
    		
    		if(FRAME_NO == images.size()){
    			gestureCount++;
    			Log.i("PCNNPOCESSOR", "PCNNPOCESSOR Start PCNN " + gestureCount);
    			PCNNProcessor pcnnThread = new PCNNProcessor(DIM, DIM);
    			pcnnThread.setImages((Vector<Mat>)images.clone());
    			pcnnThread.setContext(context);
    			pcnnThread.setFrontCamera(cameraID == mOpenCvCameraView.CAMERA_ID_FRONT);
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

    	if(cameraID == mOpenCvCameraView.CAMERA_ID_FRONT)
    		flip(rgba,rgba, 180);
        return rgba;
    }
    
    private void flip(Mat targetMat, Mat result, double angle) {
    	org.opencv.core.Point center = new org.opencv.core.Point(targetMat.width() / 2, targetMat.height() / 2);
    	Size targetSize = targetMat.size();
    	Mat rotImage = Imgproc.getRotationMatrix2D(center, angle, 1.0);
    	//Mat resultMat = new Mat(); // CUBIC
    	Imgproc.warpAffine(targetMat, result, rotImage, targetSize);
//    	m1.get(row, col)
//    	Mat m = new Mat(m1.width(), m1.height(), CvType.CV_64F);
//    	Imgproc.cvtColor(m1,m,Imgproc.COLOR_RGBA2RGB);
//    	int total = (int) m.total();
//    	int channels = m.channels();
//    	int n = total * channels;
//    	float[] mdata = new float[n];
//    	int t = m.type();
//		m.get(0, 0, mdata);
//    	
//    	double[] mdata1 = new double[n];
//    	
//    	for(int i = 0 ;i < n;i+=channels){
//    		int startPixel = n - i - channels - 1;
//    		for(int j = 0;j < channels;++j){
//    			mdata1[startPixel + j] = mdata[i + j];
//    		}
//    	}
//    	//Mat mm = new Mat(m.width(), m.height(), m.type());
//    	m.put(0, 0, mdata1);Imgproc.getr
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
