#include "camera.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>
#include<vector>
using namespace cv;
using namespace std;


Camera::Camera(void):stream1(0)
{
}


Camera::~Camera(void)
{
}

elementType * Camera::getGesture(int frameNo, double timeInterval)
{
 
	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "cannot open Camera";
	}
	
	MyTimer timer;// create timer 
	int i = 0;
	
	ImageSignature imageSignature(frameNo);
	vector<Mat> imgs;
	while(true) {
		Mat cameraFrame;
		stream1.read(cameraFrame); //take image frome camera and put it in cameraFrame
		imshow("cam", cameraFrame); //show cameraFrame image on secreen

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

	for(int i = 0 ; i < imgs.size();i++){
		Mat im_out;
		resize(imgs[i],im_out,Size(dim,dim),0,0,INTER_LINEAR);
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
		imageSignature.getSignature(greyMat);
	}
	imageSignature.save();
	return imageSignature.signature;
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