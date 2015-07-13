#include "camera.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>
#include<vector>
#include<thread>
using namespace cv;
using namespace std;

Camera::Camera(void):stream1(0)
{
}


Camera::~Camera(void)
{
}
void Camera ::foo()
{

}

int * Camera::getGesture(int frameNo, double timeInterval)
{
	
	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "cannot open Camera";
	}
	
	MyTimer timer;// create timer 
	int i = 0;

	//ImageSignature imageSignature(frameNo);
	int DIM = 128;
	ImageSignature *imSig = new ImageSignature(5, 20, 40, DIM, DIM);

	vector<Mat> imgs;
	int count = 0;
	while(true) {
		Mat cameraFrame;
		stream1.read(cameraFrame); //take image frome camera and put it in cameraFrame
		imshow("cam", cameraFrame); //show cameraFrame image on secreen
		count++;
		if (count < 2)
			continue;

		//wait a while to allow system show image otherwise image will not shown
		//and break fi a key press
		if (waitKey(1) >= 0)
			break;
	
		if(timer.getPassedTime() >= timeInterval){
			stringstream ss;
			string path = "";
			if( i <=9 ) ss << '0';
			ss << i;
			path = ss.str();
			path = path + ".jpeg";
			cout<< "image:" << path<<endl;
			
			//saveImage(path, cameraFrame);
			//imageSignature.getSignature(_strdup(path.c_str()));
			imgs.push_back(cameraFrame);
			//imageSignature.getSignature(im_out);
			//saveImage(path, im_out);
			i++;
			if( i == frameNo)
				break;
			timer.reset();
		}
	}

thread threads[5];

thread s;
int start2 = 0;
	for(int i = 0 ; i < imgs.size();i++){
		Mat im_out;
		resize(imgs[i],im_out,Size(128,128),0,0,INTER_LINEAR);
		Mat greyMat;
		cvtColor(im_out, greyMat, CV_BGR2GRAY);
		/*imshow("cam", greyMat);
		stringstream ss;
			string path = "";
			if( i <=9 ) ss << '0';
			ss << i;
			path = ss.str();
			path = path + ".jpeg";
			cout<< "image:" << path<<endl;
			
			saveImage(path, greyMat);*/

   //threads[i] = thread(&ImageSignature::getSignature,imageSignature, greyMat,start2);
   
		float **t = new float*[DIM];

		for (int i = 0; i<DIM; i++){
			t[i] = new float[DIM];
			for (int j = 0; j<DIM; ++j)
			{
				//Vec3b data = m.at<Vec3b>(i,j);
				//data[0] = // blue pixel
				//data[1] = // green pixel
				//data[2] = // red pixel
				//cout <<"pixel:"<<  data[0] << " " <<  data[1] <<" " << data[2] << " " ;
				//cout<<"pixel:"<< (int)m.at<uchar>(i,j) <<endl;
				t[i][j] = (int)greyMat.at<uchar>(i, j);

			}
		}
	//	imSig->getSignature(t);
		threads[i] = thread(&ImageSignature::getSignature, imSig, t, start2);
		start2 += 20;

		//imageSignature.getSignature( greyMat);
//		System::Threading::Thread^ newThread = gcnew
	//		System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(greyMat, &ImageSignature::getSignature));

	

	}
	for (int i = 0; i < imgs.size(); i++)
			threads[i].join();

		imSig->save();
		//cout<<"getgesture";
		//cout<<"size "<<imageSignature.signature;

		return imSig->signature;

}

void Camera::saveImage(String path, Mat &mat)
{

    vector<int> compression_params;

    try {
		imwrite(path, mat, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to target format: %s\n", ex.what());
    }

   // fprintf(stdout, "Saved file with alpha data.\n");
}