// LadarPointDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "LadarPointDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLadarPointDlg dialog


CLadarPointDlg::CLadarPointDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLadarPointDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLadarPointDlg)
	m_InPutPath = _T("");
	m_OutPutPath = _T("");
	//}}AFX_DATA_INIT
	HDB=NULL;
}


void CLadarPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLadarPointDlg)
	DDX_Text(pDX, IDC_INPUTFILEPATH, m_InPutPath);
	DDX_Text(pDX, IDC_OUTPUTFILEPATH, m_OutPutPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLadarPointDlg, CDialog)
	//{{AFX_MSG_MAP(CLadarPointDlg)
	ON_BN_CLICKED(IDC_SCANFILEPATH, OnScanfilepath)
	ON_BN_CLICKED(IDC_SCANSAVEPATH, OnScansavepath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLadarPointDlg message handlers

void CLadarPointDlg::OnScanfilepath() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="TXT Files(*.txt)|*.txt||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_InPutPath = dlg.GetPathName();
	else
		return ;
	
	point = new float[1e6][4];
	FILE *fp;
	fp = fopen(m_InPutPath,"r+");
	int i=0,j;
	BeginWaitCursor();
	while(1)
	{
		if(feof(fp))
			break;
		for(j =0;j<4;j++)
		{
			point[i][j] = 0;
			fscanf(fp,"%f",&point[i][j]);
		}
		i++;
	}
	fclose(fp);
	PNum = i;
	EndWaitCursor();

	UpdateData(FALSE);
}

void CLadarPointDlg::OnScansavepath() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.bmp)|*.bmp|所有文件(*.*)|*.*||";
	CFileDialog dlg(FALSE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_OutPutPath = dlg.GetPathName();
	else
		return ;
	UpdateData(FALSE);
}

void CLadarPointDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int i,j,k;
	int XMin,XMax,YMin,YMax;
	XMin = XMax = point[0][0]+0.5;
	YMin = YMax = point[0][1]+0.5;
	BeginWaitCursor();
	for(k=0;k<PNum-1;k++)
	{
		int x=point[k][0]+0.5,y=point[k][1]+0.5,g=point[k][3];
//		int y=point[k][0],x=point[k][1],g=point[k][3];
		if(XMin>x)
			XMin = x;
		if(XMax<x)
			XMax = x;
		if(YMin>y)
			YMin = y;
		if(YMax<y)
			YMax = y;
//		poBandFcolor[x*1000+y] = g;
	}
	nXsize = XMax-XMin;//宽
	nYsize = YMax-YMin;//高
	poBandGray = (BYTE *)CPLMalloc(sizeof(BYTE)*(nXsize*nYsize));
	memset(poBandGray,0,sizeof(poBandGray));
	for(k=0;k<PNum-1;k++)
	{
		int x=point[k][0]+0.5-XMin,y=point[k][1]+0.5-YMin,g=point[k][3];
		//		int y=point[k][0],x=point[k][1],g=point[k][3];

		poBandGray[y*nXsize+x] = g;
	}
	delete []point;//释放内存

//插值方法一：
/*	for(i=XMin;i<=XMax;i++)
	{
		for(j=YMin;j<=YMax;j++)
		{
			if(poBandFcolor[i*1000+j] == 0 && poBandFcolor[i*1000+j-1])
				poBandFcolor[i*1000+j] =poBandFcolor[i*1000+j-1];
			else if(poBandFcolor[i*1000+j] == 0 && poBandFcolor[i*1000+j+1])
				poBandFcolor[i*1000+j] =poBandFcolor[i*1000+j+1];

		}
	}
	*/
//插值方法二：
	int m,n,flag=0,g = 0;
	for(i=2;i<XMax-XMin-1;i++)
	{
		for(j=2;j<YMax-YMin-1;j++)
		{
			if(poBandGray[j*nXsize+i] == 0)
			{
				for(m=i-1;m<=i+1;m++)
				{
					for(n=j-1;n<=j+1;n++)
					{
						if(poBandGray[n*nXsize+m]!=0)
						{
							g+=poBandGray[n*nXsize+m];
							flag++;
						}
					}
				}
				if(flag != 0)
				{
				g/=flag;
				poBandGray[j*nXsize+i] = g;
				g=flag=0;
				}
			}	
		}
	}
	//创建位图句柄
	CImageProcessDoc Doc;
	BITMAPINFO *pBitmapInfo=(BITMAPINFO*)new char[sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(256)]; 
	Doc.CreateBitmapInfo(pBitmapInfo,nXsize,nYsize,1);
	LONG LineBytes = (nXsize*8+31)/32*4;
	HDB=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*nYsize);
	LPSTR pDB=(LPSTR)LocalLock(HDB);
	memcpy(pDB,pBitmapInfo,40+256*4);
	LPBYTE pData = (LPBYTE)pDB+40+256*4;
	//为各像素赋值
	for ( i=0; i<nYsize; i++)
	{
		for ( j=0; j<nXsize; j++)
		{
			pData[(nYsize-i-1)*LineBytes + j] = poBandGray[i*nXsize + j];
		}
	}
	Save(m_OutPutPath,HDB);
	::LocalUnlock((HLOCAL)HDB);
	EndWaitCursor();
	UpdateData(TRUE);
	CDialog::OnOK();
}
