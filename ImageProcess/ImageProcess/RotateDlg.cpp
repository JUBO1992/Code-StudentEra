// RotateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "RotateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg dialog


CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotateDlg)
	m_Angle = 45.0f;
	//}}AFX_DATA_INIT
	HOld=HNew=NULL;
}


void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotateDlg)
	DDX_Text(pDX, IDC_ANGLE, m_Angle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
	//{{AFX_MSG_MAP(CRotateDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg message handlers

void CRotateDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	BeginWaitCursor();
	HNew=Rotate(HOld,m_Angle);
	EndWaitCursor();
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	CDialog::OnOK();
}

HDIB CRotateDlg::Rotate(HDIB hold,double angle)
{
	if(hold==NULL)
	{
		AfxMessageBox("Çë´ò¿ªÓ°Ïñ");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(hold);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	LONG i,j,io,jo;
	double a=angle/180*3.1415926;
	LONG WidthN=int((int)fabs((float)Width*cos(a))+(int)fabs((float)Height*sin(a)));
	LONG HeightN=int((int)fabs((float)Width*sin(a))+(int)fabs((float)Height*cos(a)));
	LONG LineBytesN=(WidthN*bits+31)/32*4;
	
	HDIB hnew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		hnew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytesN*HeightN);
		pDbN=(LPSTR)LocalLock(hnew);
		pDataN=(LPBYTE)pDbN+40+256*4;
		memcpy(pDbN,pDb,40+256*4);
	}
	else if(bits==24)
	{
		hnew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytesN*HeightN);
		pDbN=(LPSTR)LocalLock(hnew);
		pDataN=(LPBYTE)pDbN+40;
		memcpy(pDbN,pDb,40);
	}
	((BITMAPINFOHEADER*)pDbN)->biWidth=WidthN;
	((BITMAPINFOHEADER*)pDbN)->biHeight=HeightN;
	((BITMAPINFOHEADER*)pDbN)->biSizeImage=LineBytesN*HeightN;
	for (i=0;i<HeightN;i++)
	{
		for (j=0;j<WidthN;j++)	
		{	
			double x1,y1,x2,y2;
			x2=i-0.5*HeightN;
			y2=0.5*WidthN-j;
			x1=x2*cos(a)-y2*sin(a);
			y1=x2*sin(a)+y2*cos(a);
			io=(long)(x1+0.5*Height+0.5);
			jo=(long)(0.5*Width-y1+0.5);
			if(io>=0&&io<Height&&jo>=0&&jo<Width)
			{
				if(bits==8)
		    		pDataN[i*LineBytesN+j]=pData[io*LineBytes+jo];
				if(bits==24)
				{
					pDataN[i*LineBytesN+3*j+0]=pData[io*LineBytes+3*jo+0];
					pDataN[i*LineBytesN+3*j+1]=pData[io*LineBytes+3*jo+1];
					pDataN[i*LineBytesN+3*j+2]=pData[io*LineBytes+3*jo+2];
				}
			}
			else
			{
				if(bits==8)
			    	pDataN[i*LineBytesN+j]=255;
				if(bits==24)
				{
					pDataN[i*LineBytesN+3*j+0]=255;
					pDataN[i*LineBytesN+3*j+1]=255;
					pDataN[i*LineBytesN+3*j+2]=255;
				}
			}
		}
	}
	::LocalUnlock((HLOCAL)hold);
	::LocalFree((HLOCAL)hold);
	::LocalUnlock((HLOCAL)hnew);
	return hnew;
}
