// LinearEnhanceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "LinearEnhanceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinearEnhanceDlg dialog


CLinearEnhanceDlg::CLinearEnhanceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLinearEnhanceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinearEnhanceDlg)
	m_add = 0.0f;
	m_multi = 1.0f;
	//}}AFX_DATA_INIT
	HOld=HNew=NULL;
}


void CLinearEnhanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinearEnhanceDlg)
	DDX_Text(pDX, IDC_ADD, m_add);
	DDX_Text(pDX, IDC_MULTI, m_multi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinearEnhanceDlg, CDialog)
	//{{AFX_MSG_MAP(CLinearEnhanceDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinearEnhanceDlg message handlers

void CLinearEnhanceDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	HNew=LinearTrans(HOld,m_multi,m_add);
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	CDialog::OnOK();
}

HDIB CLinearEnhanceDlg::LinearTrans(HDIB hold, float A, float B)
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
	int i,j;
	HDIB hnew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		hnew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(hnew);
		memcpy(pDbN,pDb,40+256*4);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		hnew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(hnew);
		memcpy(pDbN,pDb,40);
		pDataN=(LPBYTE)pDbN+40;
	}
	double gray,r,g,b;
	for (i=0;i<Height;i++)
	{
		for (j=0;j<Width;j++)	
		{	
			if(bits==8)
			{
				gray=A*pData[i*LineBytes+j]+B;
				pDataN[i*LineBytes+j]=min(255,max(gray,0));
			}
			else if(bits==24)
			{
				r=A*pData[i*LineBytes+3*j+0]+B;
				pDataN[i*LineBytes+3*j+0]=min(255,max(r,0));
				g=A*pData[i*LineBytes+3*j+1]+B;
				pDataN[i*LineBytes+3*j+1]=min(255,max(g,0));
				b=A*pData[i*LineBytes+3*j+2]+B;
				pDataN[i*LineBytes+3*j+2]=min(255,max(b,0));
			}
		}
	}
	::LocalUnlock((HLOCAL)hold);
	::LocalFree((HLOCAL)hold);
	::LocalUnlock((HLOCAL)hnew);
	return hnew;
}
