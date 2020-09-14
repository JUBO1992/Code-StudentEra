#include "StdAfx.h"
#include "SteerWheelDet.h"

#define CHANGEPOINTS 1500
SteerWheelDet::SteerWheelDet(void)
{
}


SteerWheelDet::~SteerWheelDet(void)
{
}


IplImage* SteerWheelDet::Detect(IplImage* mod,IplImage* det)
{
	if(mod->nChannels!=3 || det->nChannels!=3)
		return NULL;
	if(mod->width!=det->width || mod->height!=det->height)
		return NULL;
	int i,j,temp;
	uchar* modData = (uchar*)mod->imageData;
	uchar* detData = (uchar*)det->imageData;
	IplImage* result = cvCreateImage(cvGetSize(mod),IPL_DEPTH_8U,1);

	for (i=0; i<mod->height; i++)
	{
		for (j=0; j<mod->width; j++)
		{
			 temp = abs(modData[i*mod->widthStep+3*j]-detData[i*det->widthStep+3*j])
				 +abs(modData[i*mod->widthStep+3*j+1]-detData[i*det->widthStep+3*j+1])
				 +abs(modData[i*mod->widthStep+3*j+2]-detData[i*det->widthStep+3*j+2]);
			 if(temp >= 60)
				result->imageData[i*result->widthStep+j] = 255;
			 else
				 result->imageData[i*result->widthStep+j] = 0;
		}
	}
	return result;
}

HandState SteerWheelDet::GetState(IplImage* img)
{
	int i,j,lcount=0,rcount=0;
	uchar* data = (uchar*)img->imageData;
	for(i=img->height/2; i<img->height; i++)
	{
		for(j=0; j<img->width/2; j++)
		{
			if(data[i*img->widthStep+j] == 255)
				lcount++;
			else if(data[i*img->widthStep+j+img->width/2] == 255)
				rcount++;
		}
	}
	if(lcount<=CHANGEPOINTS && rcount<=CHANGEPOINTS)
		return NOHAND;
	else if(lcount>CHANGEPOINTS && rcount<=CHANGEPOINTS)
		return LEFTHAND;
	else if(lcount<=CHANGEPOINTS && rcount>CHANGEPOINTS)
		return RIGHTHAND;
	else
		return TWOHANDS;
}

void SteerWheelDet::CameraDetect(IplImage* mod)
{
	CvCapture* capture;
	if((capture = cvCreateCameraCapture(1))==NULL)//更改参数可更换摄像头
		return;

	IplImage *pFrame;
	cvNamedWindow("camera");
	cvNamedWindow("Example",CV_WINDOW_AUTOSIZE);
	while(1)
	{	
		pFrame = cvQueryFrame(capture);
		//显示
		cvShowImage("camera", pFrame);
		IplImage *img=cvCreateImage(cvSize(mod->width,mod->height),
			mod->depth,mod->nChannels); //创建头并分配数据
		cvResize(pFrame,img,CV_INTER_LINEAR);
		IplImage* temp = Detect(mod,img);
		cvShowImage("Example",temp);
		HandState hs = GetState(temp);
		cvReleaseImage(&temp);
		if (hs == TWOHANDS)
		{
		}
		else
		{
			MessageBeep(-1);
		}
		cvReleaseImage(&img);
		char c=cvWaitKey(100);
		if(c==27)  break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("camera");
	cvDestroyWindow("Example");
}


IplImage* SteerWheelDet::Detect2(IplImage* mod,IplImage* det)
{
	IplImage* modGray = cvCreateImage(cvSize(mod->width,mod->height),8,1);
	IplImage* detGray = cvCreateImage(cvSize(det->width,det->height),8,1);
	if(mod->nChannels==3)
		cvCvtColor(mod,modGray,CV_RGB2GRAY);
	else
		modGray = cvCloneImage(mod);
	if(det->nChannels==3)
		cvCvtColor(det,detGray,CV_RGB2GRAY);
	else
		detGray = cvCloneImage(det);
	IplImage* modCanny = cvCreateImage(cvSize(modGray->width,modGray->height),8,1);
	IplImage* detCanny = cvCreateImage(cvSize(detGray->width,detGray->height),8,1);
	cvCanny( modGray, modCanny, 50, 200, 3 );
	cvCanny( detGray, detCanny, 50, 200, 3 );
	cvReleaseImage(&modGray);
	cvReleaseImage(&detGray);
	int i,j;
	uchar* modData = (uchar*)modCanny->imageData;
	uchar* detData = (uchar*)detCanny->imageData;
	IplImage* result = cvCreateImage(cvGetSize(mod),IPL_DEPTH_8U,1);

	for (i=0; i<modCanny->height; i++)
	{
		for (j=0; j<modCanny->width; j++)
		{
			if(modData[i*modCanny->widthStep+j] != detData[i*detCanny->widthStep+j])
				result->imageData[i*result->widthStep+j] = 255;
			else
				result->imageData[i*result->widthStep+j] = 0;
		}
	}
	cvReleaseImage(&modCanny);
	cvReleaseImage(&detCanny);
	return result;
}


void SteerWheelDet::CameraDetect2(IplImage* mod)
{
	CvCapture* capture;
	if((capture = cvCreateCameraCapture(1))==NULL)//更改参数可更换摄像头
		return;

	IplImage *pFrame;
	cvNamedWindow("camera");
	cvNamedWindow("Example",CV_WINDOW_AUTOSIZE);
	while(1)
	{	
		pFrame = cvQueryFrame(capture);
		//显示
		cvShowImage("camera", pFrame);
		IplImage *img=cvCreateImage(cvSize(mod->width,mod->height),
			mod->depth,mod->nChannels); //创建头并分配数据
		cvResize(pFrame,img,CV_INTER_LINEAR);
		IplImage* temp = Detect2(mod,img);
		cvShowImage("Example",temp);
		cvReleaseImage(&img);
		char c=cvWaitKey(100);
		if(c==27)  break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("camera");
	cvDestroyWindow("Example");
}
