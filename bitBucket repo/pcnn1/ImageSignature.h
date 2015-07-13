#pragma once
#include<iostream>
#include <fstream>
#include "pcnn2d.h"
typedef int elementType;
using namespace::std;
const int dim = 128; //image dimansion
const int Niters = 40; // iteration
const int FRAME_NO = 5;
const double TIME_ITERVAL = 0.2; //time interval in second
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
const int numberofcutsitrs = 20;
//#include"neural/FeedForwardAlgorithm.h"
using namespace cv;
class ImageSignature
{	//Matrix t;
	
	string  gSignature;
	int start ; //position in signature array to add new partial image signature
	int sigLength; // signature array length + 1 for output (ex. gesture NO.)

	rimage testRimage;
public:
	elementType * signature; // signature of a gesture (total signature of all images)
	ImageSignature(int frameNumber = FRAME_NO);
	~ImageSignature(void);

	//get signature of current image then add it to total signature
	void getSignature(Mat &mat);

	//save total signature into file
	void save();

	//read sinatue frome file then put it in signature array
	void readSignature();
};

