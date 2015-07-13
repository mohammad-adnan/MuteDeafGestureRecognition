#include <time.h>
#include <opencv2/highgui/highgui.hpp>
class MyTimer{
	long long startTime;
public:
	MyTimer(){
		startTime = cv::getTickCount();
	}

	double getPassedTime(){
		long long endTime = cv::getTickCount();
		return ((double)endTime - startTime) / cv::getTickFrequency();
	}
	void reset(){
		startTime = cv::getTickCount();
	}
};