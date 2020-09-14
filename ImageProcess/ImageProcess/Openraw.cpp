// Openraw.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "Openraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenraw dialog


COpenraw::COpenraw(CWnd* pParent /*=NULL*/)
	: CDialog(COpenraw::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenraw)
	m_Width = 1000;
	m_Height = 1000;
	m_Filepath = _T("");
	//}}AFX_DATA_INIT
}


void COpenraw::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenraw)
	DDX_Text(pDX, IDC_WIDTH, m_Width);
	DDX_Text(pDX, IDC_HEIGHT, m_Height);
	DDX_Text(pDX, IDC_RAWFILEPATH, m_Filepath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenraw, CDialog)
	//{{AFX_MSG_MAP(COpenraw)
	ON_BN_CLICKED(IDC_SCAN, OnScan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenraw message handlers

void COpenraw::OnScan() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE file[]="RAW Files(*.RAW)|*.raw|所有文件（*.*)|*.*||";
	CFileDialog SelectFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,file,NULL);
	SelectFile.DoModal();
	CString FileName;
	FileName=SelectFile.GetPathName();
	m_Filepath=FileName;
	CFile fileraw;
	fileraw.Open(m_Filepath,CFile::modeRead|CFile::shareDenyWrite,NULL);
	DWORD filesize=fileraw.GetLength();
	m_Width=m_Height=(int)sqrt((float)(float)filesize);
	fileraw.Close();
	UpdateData(FALSE);
}

void COpenraw::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CFile fileraw;
	fileraw.Open(m_Filepath,CFile::modeRead|CFile::shareDenyWrite,NULL);
	DWORD filesize=fileraw.GetLength();
	if(m_Height*m_Width!=filesize)
	{
		MessageBox("图像数据与原图像大小不符");
		return;
	}

	BITMAPINFO *pBitmapInfo=(BITMAPINFO*)new char[40+256*4];
	CreateBitmapInfo(pBitmapInfo,m_Width,m_Height,1);
	LONG LineBytes = (m_Width*8 + 31)/32*4;
	hDB=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*m_Height);
	LPSTR pDB=(LPSTR)LocalLock(hDB);
	memcpy(pDB,pBitmapInfo,40+256*4);
	LPBYTE pData = (LPBYTE)pDB+40+256*4;
// 	fileraw.ReadHuge(pData,filesize);//works in vc6.0
	fileraw.Read(pData,filesize);
	::LocalUnlock((HGLOBAL)hDB);
	fileraw.Close();
	CDialog::OnOK();
}
void COpenraw::CreateBitmapInfo(BITMAPINFO *pBitmapInfo,int Width,int Height,int flag)
{

	pBitmapInfo->bmiHeader.biClrUsed = 0;
	if(flag==1||flag==3)
    	pBitmapInfo->bmiHeader.biBitCount = 8;
	else if(flag==2)
		pBitmapInfo->bmiHeader.biBitCount = 24;
	pBitmapInfo->bmiHeader.biClrImportant = 0;
	pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	pBitmapInfo->bmiHeader.biWidth = Width;
	pBitmapInfo->bmiHeader.biHeight = Height;
	pBitmapInfo->bmiHeader.biPlanes = 1;
	pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	if(flag==1||flag==3)
		pBitmapInfo->bmiHeader.biSizeImage = (Width*8+31)/32*4*Height; 
	else if(flag==2)
    	pBitmapInfo->bmiHeader.biSizeImage = (Width*24+31)/32*4*Height; 
	pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;	
	pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	//为颜色表赋值
	int i;
	if(flag==1)
		for ( i=0; i<256; i++)
		{
			pBitmapInfo->bmiColors[i].rgbBlue = (unsigned char)i;
			pBitmapInfo->bmiColors[i].rgbGreen = (unsigned char)i;
			pBitmapInfo->bmiColors[i].rgbRed = (unsigned char)i;
			pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	else if(flag==3)
		for ( i=0; i<256; i++)
		{
			pBitmapInfo->bmiColors[i].rgbBlue = i*2;
			pBitmapInfo->bmiColors[i].rgbGreen = (int)fabs((float)i*2-128);
			pBitmapInfo->bmiColors[i].rgbRed = (int)fabs((float)255-i*2);	
			pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
}