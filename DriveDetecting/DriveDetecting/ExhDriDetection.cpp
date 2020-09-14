#include "stdafx.h"
#include "ExhDriDetection.h"

int n=0;
void CExhDriDetection::CameraProduceImg()
{
	const double scale=1.3;

	CvCapture* capture;
	if((capture = cvCreateCameraCapture(0))==NULL)//更改参数可更换摄像头
		return;
	
	IplImage *pFrame;
	cvNamedWindow("camera");
	cvNamedWindow("Example",CV_WINDOW_AUTOSIZE);
	while(1)
	{	
		pFrame = cvQueryFrame(capture);
		//显示
		cvShowImage("camera", pFrame);
		IplImage *img=cvCreateImage(cvSize(pFrame->width,pFrame->height),
			pFrame->depth,pFrame->nChannels); //创建头并分配数据
		cvCopyImage(pFrame,img);
		IplImage * small_img = ImgProcess(img,scale);
		if (!FaceDetect(small_img,m_dType))
			{
				MessageBeep(-1);
				printf("Your face is out of the scope,please turn your face to the Camera!!!\n");
			}
	   	cvReleaseImage(&img);
		cvReleaseImage(&small_img);
		char c=cvWaitKey(33);
		if(c==27)  break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("camera");
	cvDestroyWindow("Example");
	return;
}

//图像灰度化及缩放
IplImage *CExhDriDetection::ImgProcess(IplImage *img,double scale)
{
	//OutputImage(img);//输出原图
	IplImage *gray=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U ,1);
	IplImage *small_img=cvCreateImage(cvSize(cvRound(img->width/scale),cvRound(img->height/scale)),IPL_DEPTH_8U,1);
	cvCvtColor(img,gray,CV_BGR2GRAY);
	//OutputImage(gray);//输出灰度图像
	cvResize(gray,small_img,CV_INTER_LINEAR);
	//OutputImage(small_img);//输出缩放图
	cvEqualizeHist(small_img,small_img);
	//OutputImage(small_img);//输出直方图均衡化图
	cvReleaseImage(&gray);
	return small_img;
}
bool CExhDriDetection::FaceDetect(IplImage *img,DetectType dtype)
{

	CvMemStorage *storage=cvCreateMemStorage(0);
	const char *cascade_name="haarcascade_frontalface_alt2.xml";
    CvHaarClassifierCascade *cascade_f=(CvHaarClassifierCascade *)cvLoad(cascade_name,0,0,0);
	CvSeq *faces=cvHaarDetectObjects(img,cascade_f,storage,1.1,2,0,cvSize(30,30));
	if (faces->total==0)
	{
		cvShowImage("Example",img);
		cvClearSeq(faces);
		cvReleaseMemStorage(&storage);
	    cvReleaseHaarClassifierCascade(&cascade_f);
		return false;
	}
	CvRect *r_face;
	for (int i=0;i<(faces?faces->total:0);i++)
	{
		r_face=(CvRect *)cvGetSeqElem(faces,i);
		cvRectangle(img,cvPoint(r_face->x,r_face->y),cvPoint(r_face->x+r_face->width,r_face->y+r_face->height),cvScalar(255,0,0));
	}
	if(dtype == FACE)
		;
	else if(dtype == EYE)
		EyeDetect(img,r_face);
	else if(dtype == MOUTH)
		MouthDetect(img,r_face);
	else if(dtype == NOSE)
		NoseDetect(img,r_face);
	//OutputImage(img);//输出检测结果图
	cvShowImage("Example",img);
	cvClearSeq(faces);
	cvReleaseMemStorage(&storage);
	cvReleaseHaarClassifierCascade(&cascade_f);
    return true;
}

CvRect * CExhDriDetection::FaceDetect2(IplImage *img)
{

// 	m_facestorage=cvCreateMemStorage(0);
	const char *cascade_name="haarcascade_frontalface_alt2.xml";
	CvHaarClassifierCascade *cascade_f=(CvHaarClassifierCascade *)cvLoad(cascade_name,0,0,0);
	cvClearMemStorage(m_facestorage);
	CvSeq *faces=cvHaarDetectObjects(img,cascade_f,m_facestorage,1.1,2,0,cvSize(30,30));
	if (faces->total==0)
	{
		cvClearSeq(faces);
		cvReleaseMemStorage(&m_facestorage);
		cvReleaseHaarClassifierCascade(&cascade_f);
		return NULL;
	}
	CvRect *r_face;
	for (int i=0;i<(faces?faces->total:0);i++)
	{
		r_face=(CvRect *)cvGetSeqElem(faces,i);
		cvRectangle(img,cvPoint(r_face->x,r_face->y),cvPoint(r_face->x+r_face->width,r_face->y+r_face->height),cvScalar(255,0,0));
	}
	cvClearSeq(faces);
	cvReleaseHaarClassifierCascade(&cascade_f);
	return r_face;
}

void CExhDriDetection::OutputImage(IplImage *img)
{
	char *SavePath=new char[500];
	TCHAR name[MAX_PATH];
	GetModuleFileName(NULL,name,MAX_PATH);
	CString path = (CString)name;
	path = path.Left(path.ReverseFind('\\'));
	path += "\\VideoImages";
	sprintf(SavePath,path+"\\Image%05d.bmp", n++); //循环保存图片并选择路径
	cvSaveImage(SavePath,img);
	if(n>=60) n=0;
}

void CExhDriDetection::EyeDetect(IplImage *img,CvRect *r)
{   
	int i;
	CvMemStorage *storage=cvCreateMemStorage(0);
    const char *cascade_name="haarcascade_eye.xml";
    CvHaarClassifierCascade *cascade_e=(CvHaarClassifierCascade *)cvLoad(cascade_name,0,0,0);
    cvSetImageROI(img,cvRect(r->x,r->y+r->height/5,r->x+r->width,r->y+r->height/2));
	cvClearMemStorage(storage);
    CvSeq *eyes=cvHaarDetectObjects(img,cascade_e,storage,1.1,3,0,cvSize(4,5));
	CvRect *r_eyes;
	for (i=0;i<(eyes?eyes->total:0);i++)
	{
		r_eyes=(CvRect *)cvGetSeqElem(eyes,i);
		if ((eyes->total<2)|(abs((r->y+r_eyes->y+r_eyes->height/2)-(r->y+r->height/3))>30))
		{
			cvRectangle(img,cvPoint(r_eyes->x,r_eyes->y),cvPoint(r_eyes->x+r_eyes->width,r_eyes->y+r_eyes->height),cvScalar(0,255,128));
			MessageBeep(MB_ICONASTERISK  );
			printf("Your Eyes are closed or face the erroneous direction,please pay attention!\n");
		}
		else
		{
			cvRectangle(img,cvPoint(r_eyes->x,r_eyes->y),cvPoint(r_eyes->x+r_eyes->width,r_eyes->y+r_eyes->height),cvScalar(0,255,128));
			printf("Your Eyes are open ,please keep up!\n");
		}

	}
    cvResetImageROI(img);
	cvShowImage("Example",img);
	cvClearSeq(eyes);
	cvReleaseMemStorage(&storage);
	cvReleaseHaarClassifierCascade(&cascade_e);
}

void CExhDriDetection::MouthDetect(IplImage *img,CvRect *r)
{
	int i;
	CvMemStorage *storage=cvCreateMemStorage(0);
    const char *cascade_name="haarcascade_mcs_mouth.xml";
    CvHaarClassifierCascade *cascade_m=(CvHaarClassifierCascade *)cvLoad(cascade_name,0,0,0);
    cvSetImageROI(img,cvRect(r->x,r->y+r->height/2,r->x+r->width,r->y+4*r->height/5));
	cvClearMemStorage(storage);
    CvSeq *mouth=cvHaarDetectObjects(img,cascade_m,storage,1.1,3,0,cvSize(4,5));
	CvRect *r_mouth;
    for (i=0;i<(mouth?mouth->total:0);i++)
    {
// 		if(i==0)continue;
		r_mouth=(CvRect *)cvGetSeqElem(mouth,i);
		cvRectangle(img,cvPoint(r_mouth->x,r_mouth->y),cvPoint(r_mouth->x+r_mouth->width,r_mouth->y+r_mouth->height),cvScalar(0,255,128));
	}
	cvResetImageROI(img);
	cvShowImage("Example",img);
	cvClearSeq(mouth);
	cvReleaseMemStorage(&storage);
	cvReleaseHaarClassifierCascade(&cascade_m);
}

void CExhDriDetection::NoseDetect(IplImage *img,CvRect *r)
{
	int i;
	CvMemStorage *storage=cvCreateMemStorage(0);
    const char *cascade_name="haarcascade_mcs_nose.xml";
    CvHaarClassifierCascade *cascade_n=(CvHaarClassifierCascade *)cvLoad(cascade_name,0,0,0);
    cvSetImageROI(img,cvRect(r->x,r->y+2*r->height/5,r->x+r->width,r->y+4*r->height/5));
	cvClearMemStorage(storage);
    CvSeq *mouth=cvHaarDetectObjects(img,cascade_n,storage,1.1,3,0,cvSize(3,3));
	CvRect *r_nose;
    for (i=0;i<(mouth?mouth->total:0);i++)
    {
		r_nose=(CvRect *)cvGetSeqElem(mouth,i);
		printf("x1=%d\t,y1=%d\n",r->x+r_nose->x+r_nose->width/2,r->y+r_nose->y+r_nose->height/2);
		printf("x2=%d\t,y2=%d\n",r->x+r->width/2,r->y+r->height/2);
	
		if ((abs((r->x+r_nose->x+r_nose->width/2)-(r->x+r->width/2))<=10)&&(abs((r->y+r_nose->y+r_nose->height/2)-(r->y+r->height/2))<=40))
			{
				printf("You are in good driving condition,please keep up!\n");
				cvRectangle(img,cvPoint(r_nose->x,r_nose->y),cvPoint(r_nose->x+r_nose->width,r_nose->y+r_nose->height),cvScalar(0,255,128));
			}
			else
			{
				MessageBeep(MB_ICONASTERISK);
				printf("Don't fall asleep,be awake!\n");
				cvRectangle(img,cvPoint(r_nose->x,r_nose->y),cvPoint(r_nose->x+r_nose->width,r_nose->y+r_nose->height),cvScalar(0,255,128));
			}
	
    }
	cvResetImageROI(img);
	cvShowImage("Example",img);
	cvClearSeq(mouth);
	cvReleaseMemStorage(&storage);
	cvReleaseHaarClassifierCascade(&cascade_n);
}

void CExhDriDetection::EyeDetect2(IplImage *img)
{
	IplImage* small_img = ImgProcess(img,1.3);
	CvRect* rect = FaceDetect2(small_img);
	if(!rect)
	{
		AfxMessageBox("未检测到脸");
			return;
	}
	EyeDetect(small_img,rect);
	cvReleaseImage(&small_img);
}

void CExhDriDetection::MouthDetect2(IplImage *img)
{
	IplImage* small_img = ImgProcess(img,1.3);
	CvRect* rect = FaceDetect2(small_img);
	if(!rect)
	{
		AfxMessageBox("未检测到脸");
		return;
	}
	MouthDetect(small_img,rect);
	cvReleaseImage(&small_img);
}

void CExhDriDetection::NoseDetect2(IplImage *img)
{
	IplImage* small_img = ImgProcess(img,1.3);
	CvRect* rect = FaceDetect2(small_img);
	if(!rect)
	{
		AfxMessageBox("未检测到脸");
		return;
	}
	NoseDetect(small_img,rect);
	cvReleaseImage(&small_img);
}
