package org.opencv.pcnn;

import java.util.Date;


public class MyTimer {
	long startTime;
	public MyTimer(){
		startTime = new Date().getTime();//Core.getTickCount();
	}
	double getPassedTime(){
		long endTime = new Date().getTime();//Core.getTickCount();
		return ((double)endTime - startTime);// / Core.getTickFrequency();
	}
	void reset(){
		startTime = new Date().getTime();// Core.getTickCount();
	}
}
