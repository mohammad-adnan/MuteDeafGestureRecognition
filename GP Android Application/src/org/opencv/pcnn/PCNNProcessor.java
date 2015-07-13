package org.opencv.pcnn;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Date;
import java.util.Vector;

import org.opencv.core.Mat;
import org.opencv.core.Size;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

import Classifer.DistanceClassifer;
import Classifer.FeedForward;
import JPCNN.ImageSignature;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Environment;
import android.os.IBinder;
import android.util.Log;

public class PCNNProcessor extends Thread {
	String TAG = PCNNProcessor.class.getName();
	private Context context;
	private boolean frontCamera;

	public void setFrontCamera(boolean frontCamera) {
		this.frontCamera = frontCamera;
	}

	public void setContext(Context context) {
		this.context = context;
	}

	private int frameNumber = 5;
	private int numberofcutsitrs = 20;
	private int Niters = 40;
	private int vert;
	private int horz;
	private Vector<Mat> images;

	public PCNNProcessor(int vert, int horz) {
		this.vert = vert;
		this.horz = horz;
	}

	public void setImages(Vector<Mat> images) {
		this.images = images;
	}

	@Override
	public void run() {
		int soundFile = 0;
		boolean serial = false;
		int[] signature = (serial?serialPCNN():ThreadPCNN());
		MyTimer t = new MyTimer();
		try {
			Vector<Integer>vec=new Vector<Integer>();
			vec.setSize(100);
			for(int i=0;i<vec.size();i++)
			    vec.set(i, signature[i]);
			DistanceClassifer disClas = new DistanceClassifer(context);
			soundFile = disClas.calculateDistances(vec);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//do what you want on signature 
//		 FeedForward feed=new FeedForward();
//		 Vector<Integer>vec=new Vector<Integer>();
//		 vec.setSize(100);
//		 for(int i=0;i<vec.size();i++)
//		     vec.set(i, signature[i]);
//		 //System.out.print(vec.size());
//
		 
//		 try {
//			 soundFile = feed.run(vec, 100,context);
//		} catch (FileNotFoundException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		} catch (IOException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		Log.i("PCNN","PCNN sound nomber " + soundFile + "with time : " + t.getPassedTime() / 1000+ " sec");
        playSound(soundFile);
		
		
	}

	private void playSound(int sound) {
		MediaPlayer mp;
		switch (sound) {
		case 1:
			mp = MediaPlayer.create(context, R.raw.sound1);
			mp.start();
			break;
		case 2:
			mp = MediaPlayer.create(context, R.raw.sound2);
			mp.start();
			break;
		case 3:
			mp = MediaPlayer.create(context, R.raw.sound3);
			mp.start();
			break;
		case 4:
			mp = MediaPlayer.create(context, R.raw.sound4);
			mp.start();
			break;
		default:
			mp = MediaPlayer.create(context, R.raw.bombsound);
			mp.start();
			Log.i("PCNN", "PCNNPOCESSOR unknown sound \'" + sound + "\'");
		}
	}

	Mat modifyImage(Mat mat) {

		Mat dst1 = new Mat(), dst2 = new Mat();
		Imgproc.cvtColor(mat, dst1, Imgproc.COLOR_BGR2GRAY);
		Size size = new Size(vert, horz);
		Imgproc.resize(dst1, dst2, size);

		if (frontCamera)
			flip(dst2, dst2, 180 - 90);
		else
			flip(dst2, dst2, -90);
		return dst2;
	}

	private void flip(Mat targetMat, Mat result, double angle) {
		org.opencv.core.Point center = new org.opencv.core.Point(
				targetMat.width() / 2, targetMat.height() / 2);
		Size targetSize = targetMat.size();
		Mat rotImage = Imgproc.getRotationMatrix2D(center, angle, 1.0);
		// Mat resultMat = new Mat(); // CUBIC
		Imgproc.warpAffine(targetMat, result, rotImage, targetSize);
		// m1.get(row, col)
		// Mat m = new Mat(m1.width(), m1.height(), CvType.CV_64F);
		// Imgproc.cvtColor(m1,m,Imgproc.COLOR_RGBA2RGB);
		// int total = (int) m.total();
		// int channels = m.channels();
		// int n = total * channels;
		// float[] mdata = new float[n];
		// int t = m.type();
		// m.get(0, 0, mdata);
		//
		// double[] mdata1 = new double[n];
		//
		// for(int i = 0 ;i < n;i+=channels){
		// int startPixel = n - i - channels - 1;
		// for(int j = 0;j < channels;++j){
		// mdata1[startPixel + j] = mdata[i + j];
		// }
		// }
		// //Mat mm = new Mat(m.width(), m.height(), m.type());
		// m.put(0, 0, mdata1);Imgproc.getr
	}

	int[] ThreadPCNN() {
		MyTimer time = new MyTimer();
		Vector<ImageSignature> ImageSignatureThreads = new Vector<ImageSignature>();
		int count = 1;
		for (Mat mat : images) {
			Log.i("PCNNPOCESSOR",
					"PCNNPOCESSOR Image " + count + " : "
							+ time.getPassedTime() / 1000 + " sec");
			count++;
			Mat dst2 = modifyImage(mat);
			// there are some code to call pcnn code or send image to server ...

			/**
			 * type of dst2 is CV_8U = 0 and has one channel so we can use
			 * byte[] array to get data
			 */
			byte[] mdata = new byte[(int) (dst2.total() * dst2.channels())];
			dst2.get(0, 0, mdata);
			float[][] m = new float[vert][horz];
			int k = 0;
			for (int i = 0; i < vert; ++i)
				for (int j = 0; j < horz; ++j) {
					m[i][j] = mdata[k];
					++k;
				}
			ImageSignature ImgSig = new ImageSignature(1, numberofcutsitrs,
					Niters, vert, horz, m);
			ImgSig.start();
			ImageSignatureThreads.add(ImgSig);

			// end
			 //SaveImage(dst2);
		}

		for (ImageSignature IS : ImageSignatureThreads) {
			try {
				IS.join();
			} catch (InterruptedException e) {
				Log.i("PCNN", "PCNNPOCESSOR join error");
			}
		}

		int totalLength = (Niters - numberofcutsitrs) * frameNumber;
		int[] sigArray = new int[totalLength];
		int k = 0;
		String sigStr = "";
		for (ImageSignature IS : ImageSignatureThreads) {
			for (int i = 0; i < IS.sigLength; ++i) {
				sigArray[k] = IS.signature[i];
				k++;
			}
			sigStr += IS.gSignature;
		}

		SaveSigneture(sigStr);
		Log.i("PCNNPOCESSOR",
				"PCNNPOCESSOR FINISH in : " + time.getPassedTime() / 1000
						+ " sec");
		return sigArray;
	}

	int[] serialPCNN() {
		MyTimer time = new MyTimer();

		ImageSignature imSig = new ImageSignature(frameNumber,
				numberofcutsitrs, Niters, vert, horz);
		int count = 1;
		for (Mat mat : images) {
			Log.i("PCNNPOCESSOR",
					"PCNNPOCESSOR Image " + count + " : "
							+ time.getPassedTime() / 1000 + " sec");
			count++;
			Mat dst2 = modifyImage(mat);
			// there are some code to call pcnn code or send image to server ...

			/**
			 * type of dst2 is CV_8U = 0 and has one channel so we can use
			 * byte[] array to get data
			 */
			byte[] mdata = new byte[(int) (dst2.total() * dst2.channels())];
			dst2.get(0, 0, mdata);
			float[][] m = new float[vert][horz];
			int k = 0;
			for (int i = 0; i < vert; ++i)
				for (int j = 0; j < horz; ++j) {
					m[i][j] = mdata[k];
					++k;
				}
			imSig.getSignature(m);

			// end
			// SaveImage(dst2);
		}
		// SaveSigneture(imSig.gSignature);
		Log.i("PCNNPOCESSOR",
				"PCNNPOCESSOR FINISH in : " + time.getPassedTime() / 1000
						+ " sec");
		return imSig.signature;
	}

	public class BackgroundSoundService extends Service {

		int sound;

		public BackgroundSoundService(int sound) {
			this.sound = sound;
		}

		MediaPlayer mp;

		public void onCreate() {
			mp = MediaPlayer.create(this, sound);
			mp.setLooping(false);
		}

		public void onDestroy() {
			mp.stop();
		}

		public void onStart(Intent intent, int startid) {

			Log.d("sound", " PCNN On start");
			mp.start();
		}

		@Override
		public IBinder onBind(Intent intent) {
			// TODO Auto-generated method stub
			return null;
		}
	}

	public void SaveImage(Mat mat) {
		File path = new File(
				Environment
						.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES),
				"myOpencv");
		if (!path.exists()) {
			if (!path.mkdirs()) {
				Log.e(TAG, "failed to create directory");
				return;
			}
		}
		String timeStamp = Long.valueOf(new Date().getTime()).toString();// new
																			// SimpleDateFormat("yyyyMMdd_HHmmss").format(new
																			// Date());
		File mediaFile;
		mediaFile = new File(path.getPath() + File.separator + "testimage_"
				+ timeStamp + ".jpeg");

		Boolean bool = null;
		bool = Imgcodecs.imwrite(mediaFile.getPath(), mat);

		if (bool == true)
			Log.d(TAG, "SUCCESS writing image to external storage");
		else
			Log.d(TAG, "Fail writing image to external storage");
	}

	public void SaveSigneture(String s) {
		File path = new File(
				Environment
						.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES),
				"myOpencv");
		if (!path.exists()) {
			if (!path.mkdirs()) {
				Log.e(TAG, "failed to create directory");
				return;
			}
		}

		File sfile = new File(path.getPath(), "DataFile.txt");
		try {
			BufferedWriter bW = new BufferedWriter(new FileWriter(sfile, true));
			bW.write(s);
			bW.newLine();
			bW.flush();
			bW.close();
			Log.d(TAG, "SUCCESS writing signature to external storage");
		} catch (IOException e) {
			Log.d(TAG, "Fail writing signature to external storage");
		}
	}
}
