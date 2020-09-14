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

	//ͼ��ҶȻ�������
	IplImage *ImgProcess(IplImage *img,double scale);

	//���¼������imgͼ���Ϊ�����Ҷ�����ͼ
	bool FaceDetect(IplImage *img, DetectType dtype);
	CvRect *FaceDetect2(IplImage *img);
	void EyeDetect(IplImage *img,CvRect *r);
	void MouthDetect(IplImage *img,CvRect *r);
	void NoseDetect(IplImage *img,CvRect *r);

	//���¼��img����ΪԭʼRGBͼ��
	void EyeDetect2(IplImage *img);
	void MouthDetect2(IplImage *img);
	void NoseDetect2(IplImage *img);
};