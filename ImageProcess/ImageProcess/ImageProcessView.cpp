// ImageProcessView.cpp : implementation of the CImageProcessView class
//

#include "stdafx.h"
#include "ImageProcess.h"

#include "ImageProcessDoc.h"
#include "ImageProcessView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PI 3.14159
/////////////////////////////////////////////////////////////////////////////
// CImageProcessView

IMPLEMENT_DYNCREATE(CImageProcessView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProcessView, CScrollView)
	//{{AFX_MSG_MAP(CImageProcessView)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_OPENIMAGE, OnOpenimage)
	ON_COMMAND(ID_CLASS_KAVG, OnClassKavg)
	ON_COMMAND(ID_WAVEDETECT, OnWavedetect)
	ON_COMMAND(ID_CHANGEMONITOR, OnChangemonitor)
	ON_COMMAND(ID_LIDARDATA, OnLidardata)
	ON_COMMAND(ID_ISODATA, OnIsodata)
	ON_COMMAND(ID_KLTRANS, OnKltrans)
	ON_COMMAND(ID_NDVI, OnNdvi)
	ON_COMMAND(ID_RGB2GRAY, OnRgb2gray)
	ON_COMMAND(ID_RGB2HIS, OnRgb2his)
	ON_COMMAND(ID_HIS2RGB, OnHis2rgb)
	ON_COMMAND(ID_HISFUSION, OnHisfusion)
	ON_COMMAND(ID_NWEIGHTFUSION, OnNweightfusion)
	ON_COMMAND(ID_GEO_ZOOM, OnGeoZoom)
	ON_COMMAND(ID_GEO_ROTATE, OnGeoRotate)
	ON_COMMAND(ID_GEO_ZOOM_S, OnGeoZoomS)
	ON_COMMAND(ID_GEO_ZOOM_B, OnGeoZoomB)
	ON_COMMAND(ID_GEO_ROTATE_CW90, OnGeoRotateCw90)
	ON_COMMAND(ID_GEO_ROTATE_CCW90, OnGeoRotateCcw90)
	ON_COMMAND(ID_GEO_ROTATE_CW180, OnGeoRotateCw180)
	ON_COMMAND(ID_GEO_ROTATE_CCW180, OnGeoRotateCcw180)
	ON_COMMAND(ID_GEO_FLIPHORIZ, OnGeoFliphoriz)
	ON_COMMAND(ID_GEO_FLIPVERTI, OnGeoFlipverti)
	ON_COMMAND(ID_WEIGHTFUSION, OnWeightfusion)
	ON_COMMAND(ID_LINEARENHANCE, OnLinearenhance)
	ON_COMMAND(ID_HISTOGRAM_EQUAL, OnHistogramEqual)
	ON_COMMAND(ID_HISTOGRAM_SHOW, OnHistogramShow)
	ON_COMMAND(ID_POINT_INVERT, OnPointInvert)
	ON_COMMAND(ID_POINT_MEANFILTER, OnPointMeanfilter)
	ON_COMMAND(ID_POINT_MEDIANFILTER, OnPointMedianfilter)
	ON_COMMAND(ID_POINT_GAUSSSMOOTH, OnPointGausssmooth)
	ON_COMMAND(ID_POINT_GRADSHARP, OnPointGradsharp)
	ON_COMMAND(ID_POINT_EDGEROBERTS, OnPointEdgeroberts)
	ON_COMMAND(ID_POINT_EDGESOBEL, OnPointEdgesobel)
	ON_COMMAND(ID_POINT_EDGEPREWITT, OnPointEdgeprewitt)
	ON_COMMAND(ID_POINT_EDGELAPLACE, OnPointEdgelaplace)
	ON_COMMAND(ID_OPENRAW, OnOpenraw)
	ON_COMMAND(ID_POINT_LEEFILTER, OnPointLeefilter)
	ON_COMMAND(ID_POINT_KUANFILTER, OnPointKuanfilter)
	ON_COMMAND(ID_POINT_FROSTFILTER, OnPointFrostfilter)
	ON_COMMAND(ID_SARDISTRANS, OnSardistrans)
	ON_COMMAND(ID_POINT_SIGMAFILTER, OnPointSigmafilter)
	ON_COMMAND(ID_POINT_STATISTICS, OnPointStatistics)
	ON_COMMAND(ID_POINT_SLEEFILTER, OnPointSleefilter)
	ON_COMMAND(ID_POINT_SKUANFILTER, OnPointSkuanfilter)
	ON_COMMAND(ID_POINT_MAPFILTER, OnPointMapfilter)
	ON_COMMAND(ID_POINT_EPOSFILTER, OnPointEposfilter)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_BUTTON_SET_COLOR, &CImageProcessView::OnButtonSetColor)
	ON_WM_ACTIVATE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_IMGPRO_UNDOALL, &CImageProcessView::OnImgproUndoall)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageProcessView construction/destruction

CImageProcessView::CImageProcessView()
{
	// TODO: add construction code here
	m_bgcolor = RGB(0,0,0);
	SetScrollSizes(MM_TEXT, CSize(0,0));

}

CImageProcessView::~CImageProcessView()
{

}

BOOL CImageProcessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,
		(HBRUSH)::GetStockObject(m_bgcolor),0); //这里默认为白色画刷 WHITE_BRUSH ,现在修改为m_bgcolor
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessView drawing

void CImageProcessView::OnDraw(CDC* pDC)
{
	CImageProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	HDIB hDB=pDoc->hDB;
	if(hDB==NULL)
		return;
	LPSTR pDb=(LPSTR)LocalLock(hDB);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
	::LocalUnlock((HLOCAL)hDB);
	CRect rect2(0,0,Width,Height);
	CPalette *pPal=new CPalette();
	HDC hDC=pDC->GetSafeHdc();
	PaintDIB(hDC,rect2,hDB,rect2,pPal);

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = Width;
	sizeTotal.cy = Height;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CImageProcessView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessView printing

BOOL CImageProcessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageProcessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageProcessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessView diagnostics

#ifdef _DEBUG
void CImageProcessView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcessView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcessDoc* CImageProcessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessDoc)));
	return (CImageProcessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageProcessView message handlers

void CImageProcessView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CImageProcessDoc *pDoc=GetDocument();

	static char BASED_CODE filetype[]="所有文件(*.*)|*.*|TIF Files(*.TIF;*.TIFF)|*.tif;*.tiff|BMP Files(*.BMP)|*.bmp|JPG Files(*.JPG;*.JPEG;*.JPE)|*.jpg;*.jpeg;*.jpe|IMG Files(*.img)|*.img||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	CString filepath;
	if(dlg.DoModal()==IDOK)
		filepath = dlg.GetPathName();
	else
		return;
	if(pDoc->OnOpenDocument(filepath)!=0)
	{
    	pDoc->SetModifiedFlag(TRUE);//修改标记
    	Invalidate(TRUE);
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CImageProcessView::OnOpenimage() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();

	static char BASED_CODE filetype[]="所有文件(*.*)|*.*|TIF Files(*.TIF;*.TIFF)|*.tif;*.tiff|BMP Files(*.BMP)|*.bmp|JPG Files(*.JPG;*.JPEG;*.JPE)|*.jpg;*.jpeg;*.jpe|IMG Files(*.img)|*.img||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	CString filepath;
	if(dlg.DoModal()==IDOK)
		filepath = dlg.GetPathName();
	else
		return;
	if(pDoc->OnOpenDocument(filepath)!=0)
	{
		pDoc->SetModifiedFlag(TRUE);//修改标记
		Invalidate(TRUE);
	}
}

void CImageProcessView::OnClassKavg() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc = GetDocument();
	CClassifyDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HDB;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnWavedetect() 
{
	// TODO: Add your command handler code here
	CPeakDetectDlg dlg;
	dlg.DoModal();
}

void CImageProcessView::OnChangemonitor() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc = GetDocument();
	CChanMoniDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HDB;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnLidardata() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc = GetDocument();
	CLadarPointDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HDB;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnIsodata() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc = GetDocument();
	CISODATA dlg;
	int c=0;
	if(dlg.DoModal() == IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HDB;
		c=dlg.C;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	CString tmp;
	tmp.Format(_T("最终分类类别数为%d类"),c);
	AfxMessageBox(tmp,MB_OKCANCEL);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnKltrans() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CKLTransDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HDBN;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记

}

void CImageProcessView::OnNdvi() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CNDVIDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HDBN;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnRgb2gray() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	HDIB HDB = pDoc->hDB;
	if(HDB == NULL)
		return;
	LPSTR pDb = (LPSTR)LocalLock(HDB);
	BITMAPINFO *pBIH = (LPBITMAPINFO)pDb;
	DWORD bits=pBIH->bmiHeader.biBitCount;
	if(bits!=24)
		return;
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
	LONG LineBytes=(Width*24+31)/32*4;
	LPBYTE pData=(LPBYTE)FindDIBBits(pDb);
	LONG LineBytesN=(Width*8+31)/32*4;
    ::LocalUnlock((HLOCAL)HDB);
	HDIB HDBN=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytesN*Height);
	LPSTR pDbN=(LPSTR)LocalLock(HDBN);
	LPBYTE pDataN=(LPBYTE)pDbN+40+256*4;
	pBIH->bmiHeader.biBitCount = 8;
	pBIH->bmiHeader.biSizeImage = (Width*8+31)/32*4*Height;
	int i,j;
	for ( i=0; i<256; i++)
	{
		pBIH->bmiColors[i].rgbBlue = i;
		pBIH->bmiColors[i].rgbGreen = i;
		pBIH->bmiColors[i].rgbRed = i;
		pBIH->bmiColors[i].rgbReserved = 0;
	}
	memcpy(pDbN,pBIH,40*256*4);
	for(i=0;i<Height;i++)
	{
		for(j=0;j<Width;j++)
		{
			int R=pData[i*LineBytes+3*j+0];
			int G=pData[i*LineBytes+3*j+1];
			int B=pData[i*LineBytes+3*j+2];
			//pDataN[i*LineBytesN+j]=(R + G + B)/3;
			//pDataN[i*LineBytesN+j]=R*0.299 + G*0.587 + B*0.114;
			pDataN[i*LineBytesN+j] = (R*30 + G*59 + B*11 + 50) / 100;
		}
	}
	pDoc->hDB=HDBN;
	::LocalFree((HLOCAL)HDB);
	::LocalUnlock((HLOCAL)HDBN);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnRgb2his() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	HDIB HDB = pDoc->hDB;
	if(HDB == NULL)
		return;
	LPSTR pDb = (LPSTR)LocalLock(HDB);
	BITMAPINFO *pBIH = (LPBITMAPINFO)pDb;
	DWORD bits=pBIH->bmiHeader.biBitCount;
	if(bits!=24)
		return;
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
	LONG LineBytes=(Width*24+31)/32*4;
	LPBYTE pData=(LPBYTE)FindDIBBits(pDb);
	::LocalUnlock((HLOCAL)HDB);
	HDIB HDBN=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
	LPSTR pDbN=(LPSTR)LocalLock(HDBN);
	memcpy(pDbN,pDb,40);
	LPBYTE pDataN=(LPBYTE)pDbN+40;
	int i=0,j=0;
	float r,g,b,I,H,S;
	Intensity=new float[Height*Width];
	Hue=new float[Height*Width];
	Saturation=new float[Height*Width];
	for(i=0;i<Height;i++)
	{
		for(j=0;j<Width;j++)
		{
			r=pData[i*LineBytes+j*3+0];
			g=pData[i*LineBytes+j*3+1];
			b=pData[i*LineBytes+j*3+2];

			I=float((r+g+b)/sqrt((float)3));
			float m=min(min(r,g),b);
			S=float(1-sqrt((float)3)*m/I);
			double f=0.5*(2*r-g-b)/sqrt((float)(r-g)*(r-g)+(r-b)*(g-b));
			if (g>=b) 
				H=float(acos(f));
			else 
				H=float(2*PI-acos(f));
			
			Intensity[i*Width+j]=I;
			Hue[i*Width+j]=H;
			Saturation[i*Width+j]=S;
			pDataN[i*LineBytes+j*3+0]=S*255/(2*PI);
			pDataN[i*LineBytes+j*3+1]=H*255;
			pDataN[i*LineBytes+j*3+2]=min(255,max(I,0));
		}
	}
	pDoc->hDB=HDBN;
	::LocalFree((HLOCAL)HDB);
	::LocalUnlock((HLOCAL)HDBN);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记

}

void CImageProcessView::OnHis2rgb() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	HDIB HDB = pDoc->hDB;
	if(HDB == NULL)
		return;
	LPSTR pDb = (LPSTR)LocalLock(HDB);
	BITMAPINFO *pBIH = (LPBITMAPINFO)pDb;
	DWORD bits=pBIH->bmiHeader.biBitCount;
	if(bits!=24)
		return;
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
	LONG LineBytes=(Width*24+31)/32*4;
	LPBYTE pData=(LPBYTE)FindDIBBits(pDb);
	::LocalUnlock((HLOCAL)HDB);
	HDIB HDBN=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
	LPSTR pDbN=(LPSTR)LocalLock(HDBN);
	memcpy(pDbN,pDb,40);
	LPBYTE pDataN=(LPBYTE)pDbN+40;
	int i=0,j=0;
	float R,G,B,I,H,S;
	for(i=0;i<Height;i++)
	{
		for(j=0;j<Width;j++)
		{
			I=Intensity[i*Width+j];
			H=Hue[i*Width+j];
			S=Saturation[i*Width+j];
			
			if (H>=0&&H<2*PI/3)
			{
				R=I*(1+S*cos(H)/cos(PI/3-H))/sqrt((float)3);
				B=I*(1-S)/sqrt((float)3);
				G=sqrt((float)3)*I-R-B;
			}
			else if (H>2*PI/3&&H<4*PI/3)
			{
				G=I*(1+S*cos(H-2*PI/3)/cos(PI-H))/sqrt((float)3);
				R=I*(1-S)/sqrt((float)3);
				B=sqrt((float)3)*I-R-G;
			}
			else if (H>4*PI/3&&H<2*PI)
			{
				B=I*(1+S*cos(H-4*PI/3)/cos(5*PI/3-H))/sqrt((float)3);
				G=I*(1-S)/sqrt((float)3);
				R=sqrt((float)3)*I-G-B;
			}
			int r=int((max(0,min(255,R+0.5))));
			int g=int((max(0,min(255,G+0.5))));
			int b=int((max(0,min(255,B+0.5))));
			
			pDataN[i*LineBytes+j*3+0]=r;
			pDataN[i*LineBytes+j*3+1]=g;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
			pDataN[i*LineBytes+j*3+2]=b;
		}
	}
	pDoc->hDB=HDBN;
	::LocalFree((HLOCAL)HDB);
	::LocalUnlock((HLOCAL)HDBN);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnHisfusion() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CHISFusionDlg dlg;
	dlg.fusion=0;
	if(dlg.DoModal()==IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HDB2;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnNweightfusion() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CHISFusionDlg dlg;
	dlg.fusion=1;
	if(dlg.DoModal()==IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HDB2;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnWeightfusion() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CHISFusionDlg dlg;
	dlg.fusion=2;
	if(dlg.DoModal()==IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HDB2;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//修改标记
}

void CImageProcessView::OnGeoZoom() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CZoomDlg dlg;
	dlg.HOld=pDoc->hDB;
	if(dlg.DoModal()==IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HNew;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);

}

void CImageProcessView::OnGeoRotate() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CRotateDlg dlg;
	dlg.HOld=pDoc->hDB;
	if(dlg.DoModal()==IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HNew;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnGeoZoomS() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CZoomDlg dlg;
	HDIB hold=pDoc->hDB;
	pDoc->hDB=dlg.Zoom(hold,0.5,0.5);
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnGeoZoomB() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CZoomDlg dlg;
	HDIB hold=pDoc->hDB;
	pDoc->hDB=dlg.Zoom(hold,2,2);
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnGeoRotateCw90() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CRotateDlg dlg;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=dlg.Rotate(hold,90);
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnGeoRotateCcw90() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CRotateDlg dlg;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=dlg.Rotate(hold,-90);
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnGeoRotateCw180() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CRotateDlg dlg;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=dlg.Rotate(hold,180);
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnGeoRotateCcw180() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CRotateDlg dlg;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=dlg.Rotate(hold,-180);
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnGeoFliphoriz() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	if(pDoc->hDB==NULL)
		return;
	LPSTR pDb=(LPSTR)LocalLock(pDoc->hDB);
	int Width=DIBWidth(pDb);
	int Height=DIBHeight(pDb);
	int bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	int LineBytes=(Width*bits+31)/32*4;
	LPBYTE pData=(LPBYTE)FindDIBBits(pDb);
	int i,j,k,temp;
	for(i=0;i<Height;i++)
	{
		for(j=0,k=Width-1;j<k;j++,k--)
		{
			if(bits==8)
			{
				temp=pData[i*LineBytes+j];
				pData[i*LineBytes+j]=pData[i*LineBytes+k];
				pData[i*LineBytes+k]=temp;
			}
			else if(bits==24)
			{
				temp=pData[i*LineBytes+3*j+0];
				pData[i*LineBytes+3*j+0]=pData[i*LineBytes+3*k+0];
				pData[i*LineBytes+3*k+0]=temp;
				temp=pData[i*LineBytes+3*j+1];
				pData[i*LineBytes+3*j+1]=pData[i*LineBytes+3*k+1];
				pData[i*LineBytes+3*k+1]=temp;
				temp=pData[i*LineBytes+3*j+2];
				pData[i*LineBytes+3*j+2]=pData[i*LineBytes+3*k+2];
				pData[i*LineBytes+3*k+2]=temp;
			}
		}
	}
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnGeoFlipverti() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	if(pDoc->hDB==NULL)
		return;
	LPSTR pDb=(LPSTR)LocalLock(pDoc->hDB);
	int Width=DIBWidth(pDb);
	int Height=DIBHeight(pDb);
	int bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	int LineBytes=(Width*bits+31)/32*4;
	LPBYTE pData=(LPBYTE)FindDIBBits(pDb);
	int i,j,k,temp;
	for(i=0,j=Height-1;i<j;i++,j--)
	{
		for(k=0;k<Width;k++)
		{
			if(bits==8)
			{
				temp=pData[i*LineBytes+k];
				pData[i*LineBytes+k]=pData[j*LineBytes+k];
				pData[j*LineBytes+k]=temp;
			}
			else if(bits==24)
			{
				temp=pData[i*LineBytes+3*k+0];
				pData[i*LineBytes+3*k+0]=pData[j*LineBytes+3*k+0];
				pData[j*LineBytes+3*k+0]=temp;
				temp=pData[i*LineBytes+3*k+1];
				pData[i*LineBytes+3*k+1]=pData[j*LineBytes+3*k+1];
				pData[j*LineBytes+3*k+1]=temp;
				temp=pData[i*LineBytes+3*k+2];
				pData[i*LineBytes+3*k+2]=pData[j*LineBytes+3*k+2];
				pData[j*LineBytes+3*k+2]=temp;
			}
		}
	}
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);	
}

void CImageProcessView::OnLinearenhance() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CLinearEnhanceDlg dlg;
	dlg.HOld=pDoc->hDB;
	if(dlg.DoModal()==IDOK)
	{
		::LocalFree((HLOCAL)pDoc->hDB);
		pDoc->hDB=dlg.HNew;
	}
	else
		return;
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnHistogramEqual() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	if(pDoc->hDB==NULL)
		return;
	CHistogramDlg dlg;
	dlg.HistogramEqual(pDoc->hDB);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);//保存更改
}

void CImageProcessView::OnHistogramShow() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	if(pDoc->hDB==NULL)
		return;
	CHistogramDlg dlg;
	LPSTR pDb=(LPSTR)LocalLock(pDoc->hDB);
	int Width=DIBWidth(pDb);
	int Height=DIBHeight(pDb);
	int bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	int LineBytes=(Width*bits+31)/32*4;
	LPBYTE pData=(LPBYTE)FindDIBBits(pDb);
	int *a=new int[256*bits/8];
	float *b=new float[256*bits/8];
	memset(a,0,sizeof(int)*256*bits/8);
	memset(b,0,sizeof(float)*256*bits/8);
	int i=0,j=0,k=0;
	if(bits==8)
	{
		for(i=0;i<Height;i++)
		{	
			for(j=0;j<Width;j++)
				a[pData[i*LineBytes+j]]++;
		}	
		for(k=0;k<256;k++)
			b[k]=(float)a[k]/(Width*Height);
		dlg.GrayRatio=new float[256];
		memcpy(dlg.GrayRatio,b,256*sizeof(float));
	}
	else if(bits==24)
	{
		for(i=0;i<Height;i++)
		{	
			for(j=0;j<Width;j++)
			{
				a[pData[i*LineBytes+3*j+0]]++;
				a[256+pData[i*LineBytes+3*j+1]]++;
				a[512+pData[i*LineBytes+3*j+2]]++;
			}
		}	
		for(k=0;k<3*256;k++)
			b[k]=(float)a[k]/(Width*Height);
		dlg.RRatio=new float[256];
		dlg.GRatio=new float[256];
		dlg.BRatio=new float[256];
		memcpy(dlg.RRatio,b,256*sizeof(float));
		memcpy(dlg.GRatio,b+256,256*sizeof(float));
		memcpy(dlg.BRatio,b+512,256*sizeof(float));
	}
	dlg.bits=bits;
	delete []a;delete []b;
	dlg.DoModal();
}

void CImageProcessView::OnPointInvert() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CLinearEnhanceDlg dlg;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=dlg.LinearTrans(hold,-1,255);
	delete dlg;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointMeanfilter() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.MeanFilter(hold,3,3);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointMedianfilter() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.MedianFilter(hold,3,3);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointGausssmooth() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	int Array[9]={1,2,1,2,4,2,1,2,1};
	pDoc->hDB=CPT.TemplateOperations(hold,Array,3,3);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointGradsharp() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.GradSharp(hold,0);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointEdgeroberts() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.GradSharp(hold,1);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointEdgesobel() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	int X[9]={-1,0,1,-2,0,2,-1,0,1};
	int Y[9]={-1,-2,-1,0,0,0,1,2,1};
	pDoc->hDB=CPT.EdgeDetectTemplate(hold,X,Y,3);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointEdgeprewitt() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	int X[9]={-1,0,1,-1,0,1,-1,0,1};
	int Y[9]={-1,-1,-1,0,0,0,1,1,1};
	pDoc->hDB=CPT.EdgeDetectTemplate(hold,X,Y,3);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointEdgelaplace() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	int Array[9]={0,1,0,1,-4,1,0,1,0};
	pDoc->hDB=CPT.TemplateOperations(hold,Array,3,3);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}
#include "Openraw.h"
void CImageProcessView::OnOpenraw() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	COpenraw dlg;
	if (dlg.DoModal()!=IDOK)
		return;

	pDoc->hDB=dlg.hDB;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointLeefilter() //lee filter
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.LeeFilter(hold,3,3,0);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointKuanfilter() //kuan filter
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.KuanFilter(hold,3,3,0);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointSleefilter() //strengthen lee filter
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.LeeFilter(hold,3,3,1);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointSkuanfilter() //strengthen kuan filter
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.KuanFilter(hold,3,3,1);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointFrostfilter() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.FrostFilter(hold,3,3);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointSigmafilter() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.SigmaFilter(hold,3,3);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

#include "DisTransDlg.h"
void CImageProcessView::OnSardistrans()//雷达图像斜距转地距 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CDisTransDlg dlg;
	dlg.HOld=pDoc->hDB;
	if (dlg.DoModal()!=IDOK)
		return;
	
	pDoc->hDB=dlg.HNew;
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}


void CImageProcessView::OnPointStatistics() //统计信息
{
	// TODO: Add your command handler code here
	
	CImageProcessDoc *pDoc=GetDocument();
	if(pDoc->hDB==NULL)
		return;
	LPSTR pDb=(LPSTR)LocalLock(pDoc->hDB);
	int width=DIBWidth(pDb);
	int height=DIBHeight(pDb);
	int bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	int LineBytes=(width*bits+31)/32*4;
	LPBYTE AA=(LPBYTE)FindDIBBits(pDb);
	int i,j;
	float u=0,ur=0,ug=0,ub=0;//均值
	float dn=0,dnr=0,dng=0,dnb=0;//方差
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
			if(bits==8)
				u+=AA[i*LineBytes+j];
			else if(bits==24)
			{
				ur+=AA[i*LineBytes+3*j+0];
				ug+=AA[i*LineBytes+3*j+1];
				ub+=AA[i*LineBytes+3*j+2];
			}
	}
	u=u/(width*height);ur/=width*height;ug/=width*height;ub/=width*height;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
			if(bits==8)
				dn+=((AA[i*LineBytes+j]-u)*(AA[i*LineBytes+j]-u));
			else if(bits==24)
			{
				dnr+=((AA[i*LineBytes+3*j+0]-ur)*(AA[i*LineBytes+3*j+0]-ur));
				dng+=((AA[i*LineBytes+3*j+1]-ug)*(AA[i*LineBytes+3*j+0]-ug));
				dnb+=((AA[i*LineBytes+3*j+2]-ub)*(AA[i*LineBytes+3*j+0]-ub));
			}
	}
	dn=dn/(width*height);dnr/=width*height;dng/=width*height;dnb/=width*height;
	float Menl,Menlr,Menlg,Menlb;//等效视数
	float r,rr,rg,rb;//辐射分辨率
	CString str;
	if(bits==8)
	{
		Menl=u*u/dn;
		r=10*log(1/sqrt((float)Menl)+1);
		str.Format("方差:%15f\n均值:%15f\n等效视数:%11f\n辐射分辨率:%9f",dn,u,Menl,r);
	}
	else if(bits==24)
	{
		Menlr=ur*ur/dnr;
		Menlg=ug*ug/dng;
		Menlb=ub*ub/dnb;
		rr=10*log(1/sqrt((float)Menlr)+1);
		rg=10*log(1/sqrt((float)Menlg)+1);
		rb=10*log(1/sqrt((float)Menlb)+1);
		str.Format("R:方差:%10f  均值:%10f\n等效视数:%10f  辐射分辨率:%10f\n\nG:方差:%10f  均值:%10f\n等效视数:%10f  辐射分辨率:%10f\n\nB:方差:%10f  均值:%10f\n等效视数:%10f  辐射分辨率:%10f",dnr,ur,Menlr,rr,dng,ug,Menlg,rg,dnb,ub,Menlb,rb);
	}
	MessageBox(str,NULL,MB_OK);
}

void CImageProcessView::OnPointMapfilter() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.MAPFilter(hold,3,3);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}

void CImageProcessView::OnPointEposfilter() 
{
	// TODO: Add your command handler code here
	CImageProcessDoc *pDoc=GetDocument();
	CPointTrans CPT;
    HDIB hold=pDoc->hDB;
	pDoc->hDB=CPT.EPOSFilter(hold,7);
	Invalidate(TRUE);
	pDoc->SetModifiedFlag(TRUE);
}


void CImageProcessView::OnButtonSetColor()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* tt = (CMainFrame*)((CImageProcessApp*)AfxGetApp())->m_pMainWnd;
	CMFCRibbonBar *pbar =tt->GetRibbonBar();
	CMFCRibbonColorButton *pColor = DYNAMIC_DOWNCAST(CMFCRibbonColorButton,pbar->FindByID(ID_BUTTON_SET_COLOR));
	m_bgcolor = pColor->GetColor();
	Invalidate();
}


void CImageProcessView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CScrollView::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
	// Called when CWnd is being activated or deactivated.
}

#define WM_ACTIVATEVIEWCHANGED WM_USER + 1000
void CImageProcessView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: 在此添加专用代码和/或调用基类
	// Called when a view is activated.
	CString str;
	str.Format("%d",bActivate);
// 	MessageBox(str);
	::SendMessage(this->GetSafeHwnd(),WM_ACTIVATEVIEWCHANGED,0,0);
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


BOOL CImageProcessView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect   m_rt;   
	GetClientRect(&m_rt);   
	CBrush   brush;   
	brush.CreateSolidBrush(m_bgcolor);   
	pDC->FillRect(&m_rt,&brush); 
	return TRUE;//此处不return则没有效果
	return CScrollView::OnEraseBkgnd(pDC);
}



void CImageProcessView::OnImgproUndoall()
{
	// TODO: 在此添加命令处理程序代码
	CImageProcessDoc *pDoc=GetDocument();
// 	pDoc->hDB = pDoc->hDBOld;
// 	pDoc->SetModifiedFlag(FALSE);
}
