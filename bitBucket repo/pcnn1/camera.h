#pragma once
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
#include "mytimer.h"
#include "ImageSignature.h"
class Camera
{
	VideoCapture stream1;   //0 is the id of video device.0 if you have only one Camera.
public:
	Camera(void);
	~Camera(void);
	//take frameNo image timeInterval time interval and get signature to all image
	elementType * getGesture(int frameNo = FRAME_NO, double timeInterval = TIME_ITERVAL);
	//save mat image in path location
	void saveImage(String path, Mat &mat);
};

