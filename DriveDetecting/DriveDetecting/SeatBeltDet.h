#pragma once
#include "cv.h"
#include "highgui.h"

class SeatBeltDet
{
public:
	SeatBeltDet(void);
	~SeatBeltDet(void);

	IplImage* DoCanny(IplImage* img);
	IplImage* DoHoughLine(IplImage* img);
	bool SeatBeltState(IplImage* cannyImg);
	void CameraDetect();

	static double rho;//Hough直线检测中以像素为单位的距离精度
	static double theta;//弧度测量的角度精度,此处为角度
	static int threshold;//线条累计像素阈值
	static double param1;
	static double param2;
};

