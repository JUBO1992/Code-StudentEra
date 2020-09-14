#include "StdAfx.h"
#include "SeatBeltDet.h"
#include <vector>
using namespace std;

#define MAX_BELTWIDTH 60
#define MIN_BELTWIDTH 20
#define MIN_DOTPAIR	  100

typedef struct Point_2D
{
	int x;
	int y;
	Point_2D(){}
	Point_2D(int a,int b){x=a;y=b;}
	//double Dist(Point_2D p){return sqrt((double)(p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));}
}Point2D;

typedef struct Point_Pair
{
	Point2D pointL;
	Point2D pointR;
	Point_Pair(Point2D L,Point2D R){pointL=L;pointR=R;}
}PointPair;

double SeatBeltDet::rho = 1;
double SeatBeltDet::theta = 1;
int SeatBeltDet::threshold = 80;
double SeatBeltDet::param1 = 60;
double SeatBeltDet::param2 = 7;

SeatBeltDet::SeatBeltDet(void)
{
}


SeatBeltDet::~SeatBeltDet(void)
{
}


IplImage* SeatBeltDet::DoCanny(IplImage* img)
{
	IplImage* tempImg = cvCreateImage(cvGetSize(img),8,1);
	if(img->nChannels != 1)
		cvCvtColor(img,tempImg,CV_RGB2GRAY);
	else
		tempImg = img;
	IplImage* out = cvCreateImage(
		cvGetSize(tempImg),
		IPL_DEPTH_8U,
		1);
	cvCanny(tempImg,out,(int)50,(int)500,(int)3);
	cvReleaseImage(&tempImg);
	return(out);
}


IplImage* SeatBeltDet::DoHoughLine(IplImage* img)
{
	if( !img )return NULL;
	IplImage* src = cvCreateImage(cvGetSize(img),8,1);
	if(img->nChannels != 1)
		cvCvtColor(img,src,CV_RGB2GRAY);
	else
		src = cvCloneImage(img);
	IplImage* dst;
	IplImage* color_dst;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;
	int i,j;

	if( !src )	return NULL;

	dst = cvCreateImage( cvGetSize(src), 8, 1 );
	color_dst = cvCreateImage( cvGetSize(src), 8, 3 );

	cvCanny( src, dst, 50, 200, 3 );
	cvCvtColor( dst, color_dst, CV_GRAY2BGR );
#if 0
	lines = cvHoughLines2( dst, storage, CV_HOUGH_STANDARD, 1, CV_PI/180, 100, 0, 0 );

	for( i = 0; i < MIN(lines->total,100); i++ )
	{
		float* line = (float*)cvGetSeqElem(lines,i);
		float rho = line[0];
		float theta = line[1];
		CvPoint pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		cvLine( color_dst, pt1, pt2, CV_RGB(255,0,0), 2, CV_AA, 0 );
	}
#else
// 	lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 80, 60, 7 );
	lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, SeatBeltDet::rho, 
		SeatBeltDet::theta*CV_PI/180, SeatBeltDet::threshold, SeatBeltDet::param1, SeatBeltDet::param2 );
	double k1,b1,k2,b2;
	for( i = 0; i < lines->total-1; i++ )
	{
		CvPoint* line1 = (CvPoint*)cvGetSeqElem(lines,i);
		if (line1[1].x == line1[0].x)
			continue;
		k1 = double(line1[1].y-line1[0].y)/(line1[1].x-line1[0].x);
		for( j=i+1; j<lines->total; j++)
		{
			
			CvPoint* line2 = (CvPoint*)cvGetSeqElem(lines,j);
			if(line2[1].x == line2[0].x)
				continue;
			k2 = double(line2[1].y-line2[0].y)/(line2[1].x-line2[0].x);
			double d = fabs(line2[0].y-line1[0].y-k1*(line2[0].x-line1[0].x))/sqrt(1+k1*k1);
			if(d>10 && d<70 && k2<-0.5770 && k2>-1.732 && fabs(atan(k1)-atan(k2))<5*3.1415926/180)
			{
				cvLine( color_dst, line1[0], line1[1], CV_RGB(255,0,0), 2, CV_AA, 0 );
				cvLine( color_dst, line2[0], line2[1], CV_RGB(255,0,0), 2, CV_AA, 0 );
			}
		}
	}
#endif
	cvClearSeq(lines);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseMemStorage(&storage);
	cvNamedWindow( "Example", 1 );
	cvShowImage( "Example", color_dst );
	return color_dst;
}
bool SeatBeltDet::SeatBeltState(IplImage* cannyImg)
{
	int i,j,k,l;
	int height ,width ,step ,channels ;
	height    = cannyImg->height;
	width     = cannyImg->width;
	step      = cannyImg->widthStep/sizeof(uchar);
	channels  = cannyImg->nChannels;
	uchar*data= (uchar*)cannyImg->imageData;
	vector<vector<PointPair>> DotPair(height);
	int tempxL=0,tempxR=0;
	for(i=0; i<height; i++)
	{
		for(j=MAX_BELTWIDTH/2; j<width-MAX_BELTWIDTH/2; j++)
		{
			for (k=-MAX_BELTWIDTH/2;k<0;k++)
			{
				if (data[i*step+j+k]==255)
				{
					tempxL=k;
					break;
				}
			}

			for (k=0;k<MAX_BELTWIDTH/2;k++)
			{
				if (data[i*step+j+k]==255)
				{
					tempxR=k;
					//PointID[i].push_back(temp);
					break;
				}
			}
		    if (tempxL!=0 && tempxR!=0 && tempxR-tempxL>MIN_BELTWIDTH)
		    {
				Point2D potL(i,j+tempxL);
				Point2D potR(i,j+tempxR);
				PointPair dotpair(potL,potR);
// 				dotpair.pointL=potL;
// 				dotpair.pointR=potR;
				DotPair.at(i).push_back(dotpair);
		    }
			j+=tempxR;
			tempxL= tempxR = 0; 
		}
	}
    IplImage *parallel_img=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
	memset(parallel_img->imageData,0,sizeof(uchar)*height*width);
	for (i=0;i<height;i++)
	{
		for (j=0;j<DotPair.at(i).size();j++)
		{
			parallel_img->imageData[i*width+DotPair.at(i).at(j).pointL.y]=255;
			parallel_img->imageData[i*width+DotPair.at(i).at(j).pointR.y]=255;
		}
	}
	cvNamedWindow("Example");
	cvShowImage("Example",parallel_img);
	return true;
}


void SeatBeltDet::CameraDetect()
{
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
		IplImage* img = cvCreateImage(cvSize(640,480),8,3);
		cvResize(pFrame,img,CV_INTER_LINEAR);
		IplImage* temp = DoHoughLine(img);
// 		cvShowImage("Example",temp);
		cvReleaseImage(&temp);
		cvReleaseImage(&img);
		char c=cvWaitKey(100);
		if(c==27)  break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("camera");
 	cvDestroyWindow("Example");

}
