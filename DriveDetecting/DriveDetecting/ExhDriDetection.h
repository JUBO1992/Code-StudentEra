#pragma once
#include "cv.h"
#include "highgui.h"

enum DetectType
{
	FACE = 0,
	EYE,
	MOUTH,
	NOSE
};
class CExhDriDetection
{
public:
	CExhDriDetection()
	{
		m_dType = FACE;
		m_facestorage = cvCreateMemStorage(0);
	}
	~CExhDriDetection()
	{
		cvReleaseMemStorage(&m_facestorage);
	}
	CvMemStorage *m_facestorage;

protected:
	DetectType m_dType;
public:
	void SetDetectType(DetectType dtype){m_dType = dtype;}
	DetectType GetDetectType(){return m_dType;}
public:
	void CameraProduceImg();
	void OutputImage(IplImage *img);

	//图像灰度化及缩放
	IplImage *ImgProcess(IplImage *img,double scale);

	//以下检测所用img图像均为处理后灰度缩放图
	bool FaceDetect(IplImage *img, DetectType dtype);
	CvRect *FaceDetect2(IplImage *img);
	void EyeDetect(IplImage *img,CvRect *r);
	void MouthDetect(IplImage *img,CvRect *r);
	void NoseDetect(IplImage *img,CvRect *r);

	//以下检测img输入为原始RGB图像
	void EyeDetect2(IplImage *img);
	void MouthDetect2(IplImage *img);
	void NoseDetect2(IplImage *img);
};