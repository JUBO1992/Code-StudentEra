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

	static double rho;//Houghֱ�߼����������Ϊ��λ�ľ��뾫��
	static double theta;//���Ȳ����ĽǶȾ���,�˴�Ϊ�Ƕ�
	static int threshold;//�����ۼ�������ֵ
	static double param1;
	static double param2;
};

