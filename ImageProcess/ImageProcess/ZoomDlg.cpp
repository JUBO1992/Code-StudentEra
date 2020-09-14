// ZoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "ZoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog


CZoomDlg::CZoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomDlg)
	m_ZoomX = 1.0f;
	m_ZoomY = 1.0f;
	//}}AFX_DATA_INIT
	HOld=HNew=NULL;
}


void CZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomDlg)
	DDX_Text(pDX, IDC_ZOOMX, m_ZoomX);
	DDV_MinMaxFloat(pDX, m_ZoomX, 0.f, 100.f);
	DDX_Text(pDX, IDC_ZOOMY, m_ZoomY);
	DDV_MinMaxFloat(pDX, m_ZoomY, 0.f, 100.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg message handlers

void CZoomDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	BeginWaitCursor();
	HNew=Zoom(HOld,m_ZoomX,m_ZoomY);
	EndWaitCursor();
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	CDialog::OnOK();
}

HDIB CZoomDlg::Zoom(HDIB hold,double x,double y)
{
	if(hold==NULL)
	{
		AfxMessageBox("ÇëÏÈ´ò¿ªÍ¼Ïñ");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(hold);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	LONG i,j,io,jo;
	double ZoomInCoef=x;
	double ZoomInCoefH=y;
	LONG WidthN=(int)(Width*ZoomInCoef);
	LONG HeightN=(int)(Height*ZoomInCoefH);
	LONG LineBytesN=(WidthN*bits+31)/32*4;
	HDIB hnew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		hnew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytesN*HeightN);
		pDbN=(LPSTR)LocalLock(hnew);
		memcpy(pDbN,pDb,40+256*4);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		hnew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytesN*HeightN);
		pDbN=(LPSTR)LocalLock(hnew);
		memcpy(pDbN,pDb,40);
		pDataN=(LPBYTE)pDbN+40;
	}
	((BITMAPINFOHEADER*)pDbN)->biWidth=WidthN;
	((BITMAPINFOHEADER*)pDbN)->biHeight=HeightN;
	((BITMAPINFOHEADER*)pDbN)->biSizeImage=LineBytesN*HeightN;
	for (i=0;i<HeightN;i++)
	{
		for (j=0;j<WidthN;j++)	
		{	
			io=(int)(i/ZoomInCoefH);
			jo=(int)(j/ZoomInCoef);
			if(bits==8)
				pDataN[i*LineBytesN+j]=pData[io*LineBytes+jo];
			else if(bits==24)
			{
				pDataN[i*LineBytesN+3*j+0]=pData[io*LineBytes+3*jo+0];
				pDataN[i*LineBytesN+3*j+1]=pData[io*LineBytes+3*jo+1];
				pDataN[i*LineBytesN+3*j+2]=pData[io*LineBytes+3*jo+2];
			}
		}
	}
	::LocalUnlock((HLOCAL)hold);
	::LocalFree((HLOCAL)hold);
	::LocalUnlock((HLOCAL)hnew);
	return hnew;
}
