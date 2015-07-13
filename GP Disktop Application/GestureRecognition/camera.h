#pragma once
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
#include "mytimer.h"
#include "ImageSignature.h"
class Camera
{
	VideoCapture stream1;   //0 is the id of video device.0 if you have only one Camera.
public:

	void foo();
	Camera(void);
	~Camera(void);
	//take frameNo image timeInterval time interval and get signature to all image
	int * getGesture(int frameNo = 5, double timeInterval =.5);
	//save mat image in path location
	void saveImage(String path, Mat &mat);

};

