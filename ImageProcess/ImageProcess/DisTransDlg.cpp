// DisTransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "DisTransDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisTransDlg dialog


CDisTransDlg::CDisTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDisTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDisTransDlg)
	m_FlyHeight = 4500;
	m_Fujiao = 30;
	m_Saomiaojiao = 45;
	m_Resolution = 3;
	//}}AFX_DATA_INIT
	HOld=HNew=NULL;
}


void CDisTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisTransDlg)
	DDX_Text(pDX, IDC_ANGLE1, m_Fujiao);
	DDX_Text(pDX, IDC_ANGLE2, m_Saomiaojiao);
	DDX_Text(pDX, IDC_FLYHEIGHT, m_FlyHeight);
	DDX_Text(pDX, IDC_RESOLUTION, m_Resolution);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisTransDlg, CDialog)
	//{{AFX_MSG_MAP(CDisTransDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisTransDlg message handlers

void CDisTransDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return;
	}
	float fheight=m_FlyHeight;
	float fujiao=m_Fujiao;
	float saomjiao=m_Saomiaojiao;
	float resolution=m_Resolution;

	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	int bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;

	fheight=fheight/resolution;//将航高转换为对应像元数目
	float OA=fheight*tan((90-fujiao-saomjiao)/180*3.14159265);
	float SA=fheight/cos((90-fujiao-saomjiao)/180*3.14159265);

	LONG WidthN=(int)(sqrt((float)(SA+Width)*(SA+Width)-fheight*fheight)-OA+0.5);//斜距转地距后影像宽度
	LONG HeightN=(int)(Height);
	LONG LineBytesN=(WidthN*bits+31)/32*4;
	LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytesN*HeightN);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytesN*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40);
		pDataN=(LPBYTE)pDbN+40;
	}
	((BITMAPINFOHEADER*)pDbN)->biWidth=WidthN;
	((BITMAPINFOHEADER*)pDbN)->biHeight=HeightN;
	((BITMAPINFOHEADER*)pDbN)->biSizeImage=LineBytesN*HeightN;	int i,j,J;
	for(i=0;i<HeightN;i++)
		for(j=0;j<WidthN;j++)
		{
			J=(int)(sqrt((float)(OA+j)*(OA+j)+fheight*fheight)-SA+0.5);//转换后第j列对应转换前第J列
			if(bits==8)
				pDataN[i*LineBytesN+j]=pData[i*LineBytes+J];
			else if(bits==24)
			{
				pDataN[i*LineBytesN+3*j+0]=pData[i*LineBytes+3*J+0];
				pDataN[i*LineBytesN+3*j+1]=pData[i*LineBytes+3*J+1];
				pDataN[i*LineBytesN+3*j+2]=pData[i*LineBytes+3*J+2];
			}
		}
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	CDialog::OnOK();
}
