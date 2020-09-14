// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// DriveDetectingView.cpp : CDriveDetectingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DriveDetecting.h"
#endif

#include "DriveDetectingDoc.h"
#include "DriveDetectingView.h"

#include "ExhDriDetection.h"
#include "SteerWheelDet.h"
#include "SeatBeltDet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDriveDetectingView

IMPLEMENT_DYNCREATE(CDriveDetectingView, CScrollView)

BEGIN_MESSAGE_MAP(CDriveDetectingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDriveDetectingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CV_CALL_CAMERA, &CDriveDetectingView::OnCvCallCamera)
	ON_COMMAND(ID_CV_PLAY_VIDEO, &CDriveDetectingView::OnCvPlayVideo)
	ON_COMMAND(ID_CV_CANNY, &CDriveDetectingView::OnCvCanny)
	ON_COMMAND(ID_CV_PYR_DOWN, &CDriveDetectingView::OnCvPyrDown)
	ON_COMMAND(ID_CV_HISTOGRAM, &CDriveDetectingView::OnCvHistogram)
	ON_COMMAND(ID_CV_CONVOLUTION, &CDriveDetectingView::OnCvConvolution)
	ON_COMMAND(ID_CV_UNDO_ALL, &CDriveDetectingView::OnCvUndoAll)
	ON_COMMAND(ID_CV_HOUGH_LINE, &CDriveDetectingView::OnCvHoughLine)
	ON_COMMAND(ID_CV_PERSPTRANS, &CDriveDetectingView::OnCvPersptrans)
	ON_COMMAND(ID_CV_FACE_DETECT, &CDriveDetectingView::OnCvFaceDetect)
	ON_COMMAND(ID_CV_STEERWHEEL, &CDriveDetectingView::OnCvSteerwheel)
	ON_COMMAND(ID_CV_SEAT_BELT, &CDriveDetectingView::OnCvSeatBelt)
	ON_COMMAND(ID_CV_RGB2GRAY, &CDriveDetectingView::OnCvRgb2gray)
	ON_COMMAND(ID_CV_INVERT_COLOR, &CDriveDetectingView::OnCvInvertColor)
	ON_COMMAND(ID_CV_OPEN_IMAGE, &CDriveDetectingView::OnCvOpenImage)
	ON_COMMAND(ID_CV_STEERWHEEL2, &CDriveDetectingView::OnCvSteerwheel2)
	ON_COMMAND(ID_CV_SEAT_BELT2, &CDriveDetectingView::OnCvSeatBelt2)
	ON_COMMAND(ID_CV_STEERWHEEL1, &CDriveDetectingView::OnCvSteerwheel1)
	ON_COMMAND(ID_CV_EYEDET, &CDriveDetectingView::OnCvEyedet)
	ON_COMMAND(ID_CV_MOUTHDET, &CDriveDetectingView::OnCvMouthdet)
	ON_COMMAND(ID_CV_NOSEDET, &CDriveDetectingView::OnCvNosedet)
	ON_COMMAND(ID_SET_HOUGH_PARAM, &CDriveDetectingView::OnSetHoughParam)
	ON_COMMAND(ID_CV_EYEDET2, &CDriveDetectingView::OnCvEyedet2)
	ON_COMMAND(ID_CV_MOUTHDET2, &CDriveDetectingView::OnCvMouthdet2)
	ON_COMMAND(ID_CV_NOSEDET2, &CDriveDetectingView::OnCvNosedet2)
END_MESSAGE_MAP()

// CDriveDetectingView 构造/析构

CDriveDetectingView::CDriveDetectingView()
{
	// TODO: 在此处添加构造代码
	m_ImgWork = NULL;

}

CDriveDetectingView::~CDriveDetectingView()
{
}

BOOL CDriveDetectingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CDriveDetectingView 绘制

void CDriveDetectingView::OnDraw(CDC* pDC)
{
	CDriveDetectingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rc;
	GetClientRect(rc);
	int imgLeft = 0;
	int imgTop = 0;
	int rcWidth = rc.Width();
	int rcHeight = rc.Height();
	CvvImage ImgShow;
	if(pDoc->m_ImgLoad != NULL)
	{
		ImgShow.CopyOf(pDoc->m_ImgLoad);
		ImgShow.Show(pDC->m_hDC,imgLeft,imgTop,ImgShow.Width(),ImgShow.Height());
		CSize sizeTotal;
		// TODO: 计算此视图的合计大小
		sizeTotal.cx = ImgShow.Width();
		sizeTotal.cy = ImgShow.Height();
		SetScrollSizes(MM_TEXT, sizeTotal);
	}
	else{
// 		Graphics gh(pDC->m_hDC);
// 		Image* pImage = Image::FromFile(_T"");
// 		int x = rcWidth * 0.15;
// 		int y = rcHeight * 0.15;
// 		gh.DrawImage(pImage,x,y,rcWidth*0.7,rcHeight*0.6);
	}
	ImgShow.Destroy();

}

void CDriveDetectingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CDriveDetectingView 打印


void CDriveDetectingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDriveDetectingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDriveDetectingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDriveDetectingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDriveDetectingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDriveDetectingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDriveDetectingView 诊断

#ifdef _DEBUG
void CDriveDetectingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDriveDetectingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDriveDetectingDoc* CDriveDetectingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDriveDetectingDoc)));
	return (CDriveDetectingDoc*)m_pDocument;
}
#endif //_DEBUG


// CDriveDetectingView 消息处理程序


void CDriveDetectingView::OnCvCallCamera()
{
	// TODO: 在此添加命令处理程序代码
	CvCapture* capture;
	if((capture = cvCreateCameraCapture(0))==NULL)//更改参数可更换摄像头
		return;
	assert(capture!=NULL);
	cvNamedWindow( "Example", CV_WINDOW_AUTOSIZE );
	IplImage* frame;
	char SavePath[500]={0};
	int n=0;
	CvVideoWriter *writer = 0;
	writer  = cvCreateVideoWriter("out.avi",CV_FOURCC('M','P','4','2'),10,cvSize(640,480),1);
	if(!writer)return;

	TCHAR name[MAX_PATH];
	GetModuleFileName(NULL,name,MAX_PATH);
	CString path = (CString)name;
	path = path.Left(path.ReverseFind('\\'));
	path += "\\VideoImages";
	if(!PathIsDirectory(path))
		CreateDirectory(path,NULL);
	while(1)
	{
		frame = cvQueryFrame( capture );

		if( !frame ) break;
		cvShowImage( "Example", frame);
// 		cvWriteFrame(writer,frame);
		sprintf(SavePath,path+"\\Image%05d.bmp", n++); //循环保存图片并选择路径
		cvSaveImage(SavePath,frame);
		char c = cvWaitKey(100);
		if( c == 27 ) break;
		if( n==60) n=0;
	}
// 	cvReleaseImage(&frame);//这里不要改释放，否则会出错
	cvReleaseCapture( &capture );
	cvDestroyWindow( "Example" );
	cvReleaseVideoWriter(&writer);
}


void CDriveDetectingView::OnCvPlayVideo()
{
	// TODO: 在此添加命令处理程序代码
	CString filter = "AVI Files|*.avi|";
	CFileDialog DlgOpen(TRUE,"AVI",NULL,OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT,filter,NULL);
	CString filePath = "D:/学习/OpenCV/abc.avi";
	if(DlgOpen.DoModal()==IDOK)
	{
		filePath = DlgOpen.GetPathName();
	}
	else return;
	CvCapture* capture = cvCaptureFromAVI( filePath ); // either one will work
	//CvCapture* capture = cvCreateFileCapture("D:/学习/OpenCV/abc.avi");
	cvNamedWindow( "Example2", CV_WINDOW_AUTOSIZE );
	IplImage* frame;
	while(1)
	{
		frame = cvQueryFrame( capture );
		if( !frame ) break;
		cvShowImage( "Example2", frame);
		char c = cvWaitKey(33);
		if( c == 27 ) break;
	}
	cvReleaseCapture( &capture );
	cvDestroyWindow( "Example2" );
}


IplImage* doPyrDown(IplImage* in, int filter = IPL_GAUSSIAN_5x5)//缩放两倍
{
	//	assert(in->width%2 == 0 && in->height%2 == 0);//assert-断言，假设
	IplImage* out = cvCreateImage(cvSize(in->width/2,in->height/2),in->depth,in->nChannels);
	cvPyrDown(in,out);
	return out;
}
IplImage* doCanny(IplImage* in,double lowThresh,double highThresh,double aperture)
{
	if(in->nChannels!=1)
		return(0);
	IplImage* out = cvCreateImage(
		cvGetSize(in),
		IPL_DEPTH_8U,
		1);
	cvCanny(in,out,(int)lowThresh,(int)highThresh,(int)aperture);
	return(out);
}
void CDriveDetectingView::OnCvCanny()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	IplImage* image = pDoc->m_ImgLoad; 
	IplImage* tempImg = cvCreateImage(cvGetSize(image),8,1);
	if(image->nChannels != 1)
		cvCvtColor(image,tempImg,CV_RGB2GRAY);
	else
		tempImg = cvCloneImage(image);
	pDoc->m_ImgLoad = doCanny(tempImg,50,500,3);
	cvReleaseImage(&tempImg);
	cvReleaseImage(&image);
	Invalidate(TRUE);
}

void CDriveDetectingView::OnCvPyrDown()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	IplImage* image = pDoc->m_ImgLoad; 
	pDoc->m_ImgLoad = doPyrDown(image,IPL_GAUSSIAN_5x5);
	cvReleaseImage(&image);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvHistogram()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	IplImage* image = pDoc->m_ImgLoad; 
	IplImage* tempImg = cvCreateImage(cvGetSize(image),8,1);
	if(image->nChannels != 1)
	{
		cvCvtColor(image,tempImg,CV_RGB2GRAY);
	}
	cvReleaseImage(&image);
	int hist_size = 256;    //直方图尺寸   
	int hist_height = 256;  
	float range[] = {0,255};  //灰度级的范围   
	float* ranges[]={range};  
	//创建一维直方图，统计图像在[0 255]像素的均匀分布   
	CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);  
	//计算灰度图像的一维直方图   
	cvCalcHist(&tempImg,gray_hist,0,0);  
	//归一化直方图   
	cvNormalizeHist(gray_hist,1.0);  

	int scale = 2;  
	//创建一张一维直方图的“图”，横坐标为灰度级，纵坐标为像素个数（*scale）   
	IplImage* hist_image = cvCreateImage(cvSize(hist_size*scale,hist_height),8,3);  
	cvZero(hist_image);  
	//统计直方图中的最大直方块   
	float max_value = 0;  
	cvGetMinMaxHistValue(gray_hist, 0,&max_value,0,0);  

	//分别将每个直方块的值绘制到图中   
	for(int i=0;i<hist_size;i++)  
	{  
		float bin_val = cvQueryHistValue_1D(gray_hist,i); //像素i的概率   
		int intensity = cvRound(bin_val*hist_height/max_value);  //要绘制的高度   
		cvRectangle(hist_image,  
			cvPoint(i*scale,hist_height-1),  
			cvPoint((i+1)*scale - 1, hist_height - intensity),  
			CV_RGB(0,0,255));    
	}  
	pDoc->m_ImgLoad = tempImg;
	cvNamedWindow( "H-S Histogram", 1 );  
	cvShowImage( "H-S Histogram", hist_image ); 
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvConvolution()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	IplImage* image = pDoc->m_ImgLoad; 
	IplImage *Img = cvCreateImage(cvGetSize(image),8,1);
	if(image->nChannels != 1)
		cvCvtColor(image,Img,CV_RGB2GRAY);
	else
		Img = cvCloneImage(image);
	IplImage *Out = cvCreateImage(cvGetSize(Img),IPL_DEPTH_8U,1);
	//	IplImage *Out = cvCreateImage(cvGetSize(Img),IPL_DEPTH_32F,1);//用于Laplace算子输出图像
	CvMat *kernel = cvCreateMat(3,3,CV_32F);
	float f[]={1,-2,1,2,-4,2,1,-2,1};
	float k[]={-3,0,3,-10,0,10,-3,0,3};
	kernel->data.fl = k;
	cvFilter2D(Img,Out,kernel,cvPoint(1,1));//卷积核滤波
	//cvSobel(Img,Out,0,1,3);//Sobel算子!有问题
	//cvLaplace(Img,Out,3);//Laplace算子!有问题
	//cvCanny(Img,Out,250,225,3);//Canny算子
	//cvEqualizeHist(Img,Out);//直方图均衡化
	cvNamedWindow("exp6_1");
	cvShowImage("exp6_1",Out);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvUndoAll()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_OrgImg == NULL)
	{
		return;
	}
	pDoc->m_ImgLoad = cvCloneImage(pDoc->m_OrgImg);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvHoughLine()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	IplImage* src = cvCreateImage(cvGetSize(pDoc->m_ImgLoad),8,1);
	if(pDoc->m_ImgLoad->nChannels != 1)
		cvCvtColor(pDoc->m_ImgLoad,src,CV_RGB2GRAY);
	else
		src = pDoc->m_ImgLoad;
	IplImage* dst;
	IplImage* color_dst;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;
	int i;

	if( !src )	return;

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
	lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 100, 50, 5 );
	for( i = 0; i < lines->total; i++ )
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
		cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 2, CV_AA, 0 );
	}
#endif
	cvReleaseImage(&dst);
	cvNamedWindow( "Hough", 1 );
	cvShowImage( "Hough", color_dst );
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvPersptrans()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	CvPoint2D32f srcQuad[4],dstQuad[4];
	CvMat *warp_mat = cvCreateMat(3,3,CV_32FC1);
	IplImage *src,*dst;

	if((src=cvCloneImage(pDoc->m_ImgLoad))!=0)
	{
		dst = cvCloneImage(src);
		dst->origin = src->origin;
		cvZero(dst);
		srcQuad[0].x = 0;
		srcQuad[0].y = 0;
		srcQuad[1].x = (float)src->width - 1;
		srcQuad[1].y = 0;
		srcQuad[2].x = 0;
		srcQuad[2].y = (float)src->height - 1;
		srcQuad[3].x = (float)src->width - 1;
		srcQuad[3].y = (float)src->height - 1;
		dstQuad[0].x = (float)(src->width*0.0);
		dstQuad[0].y = (float)(src->height*0.33);
		dstQuad[1].x = (float)(src->width*0.85);
		dstQuad[1].y = (float)(src->height*0.25);
		dstQuad[2].x = (float)(src->width*0.15);
		dstQuad[2].y = (float)(src->height*0.7);
		dstQuad[3].x = (float)(src->width*0.8);
		dstQuad[3].y = (float)(src->height*0.9);

		cvGetPerspectiveTransform(srcQuad,dstQuad,warp_mat);//计算warp matrix
		cvWarpPerspective(src,dst,warp_mat);
// 		cvNamedWindow("Affine_Transform",1);
// 		cvShowImage("Affine_Transform",dst);
	}
// 	cvReleaseImage(&dst);
	cvReleaseMat(&warp_mat);
	pDoc->m_ImgLoad = dst;
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvFaceDetect()
{
	// TODO: 在此添加命令处理程序代码
	CExhDriDetection p;
	p.CameraProduceImg();	

}


void CDriveDetectingView::OnCvSteerwheel()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	if(pDoc->m_ImgLoad->nChannels != 3)
		return;
	IplImage* mod = cvCloneImage(pDoc->m_ImgLoad);
	IplImage* img;
	CString filter = "所有支持格式(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2 \
					 |Windows 图片(.BMP)|*.BMP|JPEG图片文件(.JPEG;.JPG;.JPE)|*.jpeg;*.jpg;*.jpe \
					 |便携网络图片(.PNG;.PBM;.PPM)|*.png;*.pbm;*.ppm|TIFF图片文件(.TIF;.TIFF)|*.tif;*.tiff \
					 |其他支持文件(.SR;.RAS;.JP2)|*.sr;*.ras;*.jp2||";
	CFileDialog DlgOpen(TRUE,"BMP",NULL,OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT,filter,NULL);
	if(DlgOpen.DoModal()==IDOK)
		img = cvLoadImage(DlgOpen.GetPathName(),CV_LOAD_IMAGE_COLOR);
	else
		return;
 	SteerWheelDet p;
// 	p.CameraDetect(mod);
	pDoc->m_ImgLoad = p.Detect(mod,img);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvSeatBelt()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	SeatBeltDet p;
	IplImage* tempImg = cvCloneImage(pDoc->m_ImgLoad);
// 	pDoc->m_ImgLoad = p.DoCanny(tempImg);
// 	p.SeatBeltState(pDoc->m_ImgLoad);
	p.DoHoughLine(tempImg);
	cvReleaseImage(&tempImg);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvRgb2gray()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	IplImage* image = pDoc->m_ImgLoad; 
	IplImage* tempImg = cvCreateImage(cvGetSize(image),8,1);
	if(image->nChannels != 1)
		cvCvtColor(image,tempImg,CV_RGB2GRAY);
	else
		tempImg = cvCloneImage(image);
	pDoc->m_ImgLoad = tempImg;
	cvReleaseImage(&image);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvInvertColor()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	int height ,width ,step ,channels ;
	int i,j,k;
	uchar*data ;
	//char *filename="result.bmp";
	IplImage* Img; //声明IplImage指针
	//载入图像
	Img = pDoc->m_ImgLoad;
	height    = Img->height;
	width     = Img->width;
	step      = Img->widthStep/sizeof(uchar);
	channels = Img->nChannels;
	data   = (uchar*)Img->imageData;
// 	printf("Processing a %d X %d image with %d channels\n",height,width,channels);
	// 反色图像
	for(i=0;i<height;i++) for(j=0;j<width;j++) for(k=0;k<channels;k++)
		data[i*step+j*channels+k]=255-data[i*step+j*channels+k];//反色
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvOpenImage()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	// 打开文件
	CString filter = "所有支持格式(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2 \
					 |Windows 图片(.BMP)|*.BMP|JPEG图片文件(.JPEG;.JPG;.JPE)|*.jpeg;*.jpg;*.jpe \
					 |便携网络图片(.PNG;.PBM;.PPM)|*.png;*.pbm;*.ppm|TIFF图片文件(.TIF;.TIFF)|*.tif;*.tiff \
					 |其他支持文件(.SR;.RAS;.JP2)|*.sr;*.ras;*.jp2||";
	CFileDialog DlgOpen(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT,filter,NULL);
	if(DlgOpen.DoModal()==IDOK)
	{
		pDoc->m_ImgLoad = cvLoadImage(DlgOpen.GetPathName(),CV_LOAD_IMAGE_COLOR);
		pDoc->m_OrgImg = cvCloneImage(pDoc->m_ImgLoad);
		pDoc->m_ImgLoadGray = cvLoadImage(DlgOpen.GetPathName(),CV_LOAD_IMAGE_GRAYSCALE);
		pDoc->SetTitle(DlgOpen.GetFileName());
	}
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvSteerwheel1()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	if(pDoc->m_ImgLoad->nChannels != 3)
		return;
	IplImage* mod = cvCloneImage(pDoc->m_ImgLoad);
	// 	IplImage* img;
	// 	CString filter = "所有支持格式(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2 \
	// 					 |Windows 图片(.BMP)|*.BMP|JPEG图片文件(.JPEG;.JPG;.JPE)|*.jpeg;*.jpg;*.jpe \
	// 					 |便携网络图片(.PNG;.PBM;.PPM)|*.png;*.pbm;*.ppm|TIFF图片文件(.TIF;.TIFF)|*.tif;*.tiff \
	// 					 |其他支持文件(.SR;.RAS;.JP2)|*.sr;*.ras;*.jp2||";
	// 	CFileDialog DlgOpen(TRUE,"BMP",NULL,OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT,filter,NULL);
	// 	if(DlgOpen.DoModal()==IDOK)
	// 		img = cvLoadImage(DlgOpen.GetPathName(),CV_LOAD_IMAGE_COLOR);
	// 	else
	// 		return;
	SteerWheelDet p;
	p.CameraDetect(mod);
	// 	pDoc->m_ImgLoad = p.Detect(mod,img);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvSteerwheel2()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	CvCapture* capture;
	if((capture = cvCreateCameraCapture(1))==NULL)//更改参数可更换摄像头
		return;

	IplImage *pFrame;
	pFrame = cvCloneImage(cvQueryFrame(capture));
	pDoc->m_ImgLoad = pFrame;
	Invalidate(TRUE);
	SteerWheelDet p;
 	p.CameraDetect(pFrame);
//	p.CameraDetect2(pFrame);
	cvReleaseCapture(&capture);
}


void CDriveDetectingView::OnCvSeatBelt2()
{
	// TODO: 在此添加命令处理程序代码
	SeatBeltDet p;
	p.CameraDetect();
}



void CDriveDetectingView::OnCvEyedet()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	if(pDoc->m_ImgLoad->nChannels != 3)
		return;
	IplImage* mod = cvCloneImage(pDoc->m_ImgLoad);
	CExhDriDetection p;
	p.EyeDetect2(mod);
	cvReleaseImage(&mod);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvMouthdet()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	if(pDoc->m_ImgLoad->nChannels != 3)
		return;
	IplImage* mod = cvCloneImage(pDoc->m_ImgLoad);
	CExhDriDetection p;
	p.MouthDetect2(mod);
	cvReleaseImage(&mod);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvNosedet()
{
	// TODO: 在此添加命令处理程序代码
	CDriveDetectingDoc *pDoc = GetDocument();
	if(pDoc->m_ImgLoad == NULL)
	{
		MessageBox("Please open the picture first.");
		return;
	}
	if(pDoc->m_ImgLoad->nChannels != 3)
		return;
	IplImage* mod = cvCloneImage(pDoc->m_ImgLoad);
	CExhDriDetection p;
	p.NoseDetect2(mod);
	cvReleaseImage(&mod);
	Invalidate(TRUE);
}

#include "HoughLineSet.h"
void CDriveDetectingView::OnSetHoughParam()
{
	// TODO: 在此添加命令处理程序代码
	CHoughLineSet dlg;
	dlg.m_rho = SeatBeltDet::rho;
	dlg.m_theta = SeatBeltDet::theta;
	dlg.m_threshold = SeatBeltDet::threshold;
	dlg.m_param1 = SeatBeltDet::param1;
	dlg.m_param2 = SeatBeltDet::param2;
	if(dlg.DoModal() == IDOK)
	{
		SeatBeltDet::rho = dlg.m_rho;
		SeatBeltDet::theta = dlg.m_theta;
		SeatBeltDet::threshold = dlg.m_threshold;
		SeatBeltDet::param1 = dlg.m_param1;
		SeatBeltDet::param2 = dlg.m_param2;
	}
}


void CDriveDetectingView::OnCvEyedet2()
{
	// TODO: 在此添加命令处理程序代码
	CExhDriDetection p;
	p.SetDetectType(EYE);
	p.CameraProduceImg();	
}


void CDriveDetectingView::OnCvMouthdet2()
{
	// TODO: 在此添加命令处理程序代码
	CExhDriDetection p;
	p.SetDetectType(MOUTH);
	p.CameraProduceImg();	
}


void CDriveDetectingView::OnCvNosedet2()
{
	// TODO: 在此添加命令处理程序代码
	CExhDriDetection p;
	p.SetDetectType(NOSE);
	p.CameraProduceImg();	
}
