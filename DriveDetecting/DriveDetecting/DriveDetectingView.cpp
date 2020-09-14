// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// DriveDetectingView.cpp : CDriveDetectingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CDriveDetectingView ����/����

CDriveDetectingView::CDriveDetectingView()
{
	// TODO: �ڴ˴���ӹ������
	m_ImgWork = NULL;

}

CDriveDetectingView::~CDriveDetectingView()
{
}

BOOL CDriveDetectingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CDriveDetectingView ����

void CDriveDetectingView::OnDraw(CDC* pDC)
{
	CDriveDetectingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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
		// TODO: �������ͼ�ĺϼƴ�С
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
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CDriveDetectingView ��ӡ


void CDriveDetectingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDriveDetectingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDriveDetectingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDriveDetectingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CDriveDetectingView ���

#ifdef _DEBUG
void CDriveDetectingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDriveDetectingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDriveDetectingDoc* CDriveDetectingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDriveDetectingDoc)));
	return (CDriveDetectingDoc*)m_pDocument;
}
#endif //_DEBUG


// CDriveDetectingView ��Ϣ�������


void CDriveDetectingView::OnCvCallCamera()
{
	// TODO: �ڴ���������������
	CvCapture* capture;
	if((capture = cvCreateCameraCapture(0))==NULL)//���Ĳ����ɸ�������ͷ
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
		sprintf(SavePath,path+"\\Image%05d.bmp", n++); //ѭ������ͼƬ��ѡ��·��
		cvSaveImage(SavePath,frame);
		char c = cvWaitKey(100);
		if( c == 27 ) break;
		if( n==60) n=0;
	}
// 	cvReleaseImage(&frame);//���ﲻҪ���ͷţ���������
	cvReleaseCapture( &capture );
	cvDestroyWindow( "Example" );
	cvReleaseVideoWriter(&writer);
}


void CDriveDetectingView::OnCvPlayVideo()
{
	// TODO: �ڴ���������������
	CString filter = "AVI Files|*.avi|";
	CFileDialog DlgOpen(TRUE,"AVI",NULL,OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT,filter,NULL);
	CString filePath = "D:/ѧϰ/OpenCV/abc.avi";
	if(DlgOpen.DoModal()==IDOK)
	{
		filePath = DlgOpen.GetPathName();
	}
	else return;
	CvCapture* capture = cvCaptureFromAVI( filePath ); // either one will work
	//CvCapture* capture = cvCreateFileCapture("D:/ѧϰ/OpenCV/abc.avi");
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


IplImage* doPyrDown(IplImage* in, int filter = IPL_GAUSSIAN_5x5)//��������
{
	//	assert(in->width%2 == 0 && in->height%2 == 0);//assert-���ԣ�����
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	int hist_size = 256;    //ֱ��ͼ�ߴ�   
	int hist_height = 256;  
	float range[] = {0,255};  //�Ҷȼ��ķ�Χ   
	float* ranges[]={range};  
	//����һάֱ��ͼ��ͳ��ͼ����[0 255]���صľ��ȷֲ�   
	CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);  
	//����Ҷ�ͼ���һάֱ��ͼ   
	cvCalcHist(&tempImg,gray_hist,0,0);  
	//��һ��ֱ��ͼ   
	cvNormalizeHist(gray_hist,1.0);  

	int scale = 2;  
	//����һ��һάֱ��ͼ�ġ�ͼ����������Ϊ�Ҷȼ���������Ϊ���ظ�����*scale��   
	IplImage* hist_image = cvCreateImage(cvSize(hist_size*scale,hist_height),8,3);  
	cvZero(hist_image);  
	//ͳ��ֱ��ͼ�е����ֱ����   
	float max_value = 0;  
	cvGetMinMaxHistValue(gray_hist, 0,&max_value,0,0);  

	//�ֱ�ÿ��ֱ�����ֵ���Ƶ�ͼ��   
	for(int i=0;i<hist_size;i++)  
	{  
		float bin_val = cvQueryHistValue_1D(gray_hist,i); //����i�ĸ���   
		int intensity = cvRound(bin_val*hist_height/max_value);  //Ҫ���Ƶĸ߶�   
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
	// TODO: �ڴ���������������
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
	//	IplImage *Out = cvCreateImage(cvGetSize(Img),IPL_DEPTH_32F,1);//����Laplace�������ͼ��
	CvMat *kernel = cvCreateMat(3,3,CV_32F);
	float f[]={1,-2,1,2,-4,2,1,-2,1};
	float k[]={-3,0,3,-10,0,10,-3,0,3};
	kernel->data.fl = k;
	cvFilter2D(Img,Out,kernel,cvPoint(1,1));//������˲�
	//cvSobel(Img,Out,0,1,3);//Sobel����!������
	//cvLaplace(Img,Out,3);//Laplace����!������
	//cvCanny(Img,Out,250,225,3);//Canny����
	//cvEqualizeHist(Img,Out);//ֱ��ͼ���⻯
	cvNamedWindow("exp6_1");
	cvShowImage("exp6_1",Out);
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvUndoAll()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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

		cvGetPerspectiveTransform(srcQuad,dstQuad,warp_mat);//����warp matrix
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
	// TODO: �ڴ���������������
	CExhDriDetection p;
	p.CameraProduceImg();	

}


void CDriveDetectingView::OnCvSteerwheel()
{
	// TODO: �ڴ���������������
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
	CString filter = "����֧�ָ�ʽ(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2 \
					 |Windows ͼƬ(.BMP)|*.BMP|JPEGͼƬ�ļ�(.JPEG;.JPG;.JPE)|*.jpeg;*.jpg;*.jpe \
					 |��Я����ͼƬ(.PNG;.PBM;.PPM)|*.png;*.pbm;*.ppm|TIFFͼƬ�ļ�(.TIF;.TIFF)|*.tif;*.tiff \
					 |����֧���ļ�(.SR;.RAS;.JP2)|*.sr;*.ras;*.jp2||";
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	IplImage* Img; //����IplImageָ��
	//����ͼ��
	Img = pDoc->m_ImgLoad;
	height    = Img->height;
	width     = Img->width;
	step      = Img->widthStep/sizeof(uchar);
	channels = Img->nChannels;
	data   = (uchar*)Img->imageData;
// 	printf("Processing a %d X %d image with %d channels\n",height,width,channels);
	// ��ɫͼ��
	for(i=0;i<height;i++) for(j=0;j<width;j++) for(k=0;k<channels;k++)
		data[i*step+j*channels+k]=255-data[i*step+j*channels+k];//��ɫ
	Invalidate(TRUE);
}


void CDriveDetectingView::OnCvOpenImage()
{
	// TODO: �ڴ���������������
	CDriveDetectingDoc *pDoc = GetDocument();
	// ���ļ�
	CString filter = "����֧�ָ�ʽ(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2 \
					 |Windows ͼƬ(.BMP)|*.BMP|JPEGͼƬ�ļ�(.JPEG;.JPG;.JPE)|*.jpeg;*.jpg;*.jpe \
					 |��Я����ͼƬ(.PNG;.PBM;.PPM)|*.png;*.pbm;*.ppm|TIFFͼƬ�ļ�(.TIF;.TIFF)|*.tif;*.tiff \
					 |����֧���ļ�(.SR;.RAS;.JP2)|*.sr;*.ras;*.jp2||";
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
	// TODO: �ڴ���������������
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
	// 	CString filter = "����֧�ָ�ʽ(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2 \
	// 					 |Windows ͼƬ(.BMP)|*.BMP|JPEGͼƬ�ļ�(.JPEG;.JPG;.JPE)|*.jpeg;*.jpg;*.jpe \
	// 					 |��Я����ͼƬ(.PNG;.PBM;.PPM)|*.png;*.pbm;*.ppm|TIFFͼƬ�ļ�(.TIF;.TIFF)|*.tif;*.tiff \
	// 					 |����֧���ļ�(.SR;.RAS;.JP2)|*.sr;*.ras;*.jp2||";
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
	// TODO: �ڴ���������������
	CDriveDetectingDoc *pDoc = GetDocument();
	CvCapture* capture;
	if((capture = cvCreateCameraCapture(1))==NULL)//���Ĳ����ɸ�������ͷ
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
	// TODO: �ڴ���������������
	SeatBeltDet p;
	p.CameraDetect();
}



void CDriveDetectingView::OnCvEyedet()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	CExhDriDetection p;
	p.SetDetectType(EYE);
	p.CameraProduceImg();	
}


void CDriveDetectingView::OnCvMouthdet2()
{
	// TODO: �ڴ���������������
	CExhDriDetection p;
	p.SetDetectType(MOUTH);
	p.CameraProduceImg();	
}


void CDriveDetectingView::OnCvNosedet2()
{
	// TODO: �ڴ���������������
	CExhDriDetection p;
	p.SetDetectType(NOSE);
	p.CameraProduceImg();	
}
