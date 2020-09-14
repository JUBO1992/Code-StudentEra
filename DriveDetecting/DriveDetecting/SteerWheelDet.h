#pragma once
#include "cv.h"
#include "highgui.h"

enum HandState{
	NOHAND = 0,
	LEFTHAND,
	RIGHTHAND,
	TWOHANDS
};
class SteerWheelDet
{
public:
	SteerWheelDet(void);
	~SteerWheelDet(void);

	IplImage* Detect(IplImage* mod,IplImage* det);
	HandState GetState(IplImage* img);
	void CameraDetect(IplImage* mod);
	IplImage* Detect2(IplImage* mod,IplImage* det);
	void CameraDetect2(IplImage* mod);
};

