// ChanMoniDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "ChanMoniDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChanMoniDlg dialog


CChanMoniDlg::CChanMoniDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChanMoniDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChanMoniDlg)
	m_OpenPath1 = _T("");
	m_OpenPath2 = _T("");
	m_SavePath = _T("");
	//}}AFX_DATA_INIT
	HDB=NULL;
}


void CChanMoniDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChanMoniDlg)
	DDX_Text(pDX, IDC_OPENPATH1, m_OpenPath1);
	DDX_Text(pDX, IDC_OPENPATH2, m_OpenPath2);
	DDX_Text(pDX, IDC_SAVEPATH, m_SavePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChanMoniDlg, CDialog)
	//{{AFX_MSG_MAP(CChanMoniDlg)
	ON_BN_CLICKED(IDC_SCAN1, OnScan1)
	ON_BN_CLICKED(IDC_SCAN2, OnScan2)
	ON_BN_CLICKED(IDC_SCANSAVE, OnScansave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChanMoniDlg message handlers

void CChanMoniDlg::OnScan1() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<8;i++)//置空
	{
		poBandBlock1[i]=NULL;
	}
	
	static char BASED_CODE filetype[]="所有文件(*.*)|*.*|TIF Files(*.TIF;*.TIFF)|*.tif;*.tiff|BMP Files(*.BMP)|*.bmp|JPG Files(*.JPG;*.JPEG;*.JPE)|*.jpg;*.jpeg;*.jpe|IMG Files(*.img)|*.img||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_OpenPath1 = dlg.GetPathName();
	else
		return ;
	
	GDALDataset *poDadaset;
	GDALAllRegister();//注册驱动
    poDadaset = (GDALDataset *)GDALOpen(m_OpenPath1,GA_ReadOnly);
	
	if(poDadaset == NULL)
	{
		AfxMessageBox("影像打开失败！",MB_OK);
		return;
	}
	//获取影像信息
	nBands1 = poDadaset->GetRasterCount();//获取波段总数
	GDALRasterBand **poBand;//定义波段指针数组
	poBand = new GDALRasterBand *[nBands1];
	
	if(poBand == NULL)
	{
		AfxMessageBox("创建各波段数据集失败！",MB_ICONWARNING);
		return;
	}
	
	for(i=0;i<nBands1;i++)
	{
		poBand[i] = poDadaset->GetRasterBand(i+1);
		if(poBand[i] == NULL)
		{
			AfxMessageBox("创建i波段数据集失败！",MB_ICONWARNING);
			return;
		}
	}
	
	nXsize1 = poBand[0]->GetXSize();
	nYsize1 = poBand[0]->GetYSize();
	BeginWaitCursor();
	for(i =0 ;i<nBands1; i++)
	{
		//分配缓存空间
		poBandBlock1[i] = (BYTE *)CPLMalloc(sizeof(BYTE)*(nXsize1*nYsize1));
		//一次性读取RasterIO
		poBand[i]->RasterIO(GF_Read,0,0,nXsize1,nYsize1,
			poBandBlock1[i],nXsize1,nYsize1,poBand[i]->GetRasterDataType(),0,0);
	}
	EndWaitCursor();
	UpdateData(FALSE);
}

void CChanMoniDlg::OnScan2() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<8;i++)//置空
	{
		poBandBlock2[i]=NULL;
	}
	
	static char BASED_CODE filetype[]="所有文件(*.*)|*.*|TIF Files(*.TIF;*.TIFF)|*.tif;*.tiff|BMP Files(*.BMP)|*.bmp|JPG Files(*.JPG;*.JPEG;*.JPE)|*.jpg;*.jpeg;*.jpe|IMG Files(*.img)|*.img||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_OpenPath2 = dlg.GetPathName();
	else
		return ;
	
	GDALDataset *poDadaset;
	GDALAllRegister();//注册驱动
    poDadaset = (GDALDataset *)GDALOpen(m_OpenPath2,GA_ReadOnly);
	
	if(poDadaset == NULL)
	{
		AfxMessageBox("影像打开失败！",MB_OK);
		return;
	}
	//获取影像信息
	nBands2 = poDadaset->GetRasterCount();//获取波段总数
	GDALRasterBand **poBand;//定义波段指针数组
	poBand = new GDALRasterBand *[nBands2];
	
	if(poBand == NULL)
	{
		AfxMessageBox("创建各波段数据集失败！",MB_ICONWARNING);
		return;
	}
	
	for(i=0;i<nBands2;i++)
	{
		poBand[i] = poDadaset->GetRasterBand(i+1);
		if(poBand[i] == NULL)
		{
			AfxMessageBox("创建i波段数据集失败！",MB_ICONWARNING);
			return;
		}
	}
	
	nXsize2 = poBand[0]->GetXSize();
	nYsize2 = poBand[0]->GetYSize();
	BeginWaitCursor();
	for(i =0 ;i<nBands2; i++)
	{
		//分配缓存空间
		poBandBlock2[i] = (BYTE *)CPLMalloc(sizeof(BYTE)*(nXsize2*nYsize2));
		//一次性读取RasterIO
		poBand[i]->RasterIO(GF_Read,0,0,nXsize2,nYsize2,
			poBandBlock2[i],nXsize2,nYsize2,poBand[i]->GetRasterDataType(),0,0);
	}
	EndWaitCursor();
	UpdateData(FALSE);
}

void CChanMoniDlg::OnScansave() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|所有文件(*.*)|*.*|";
	CFileDialog dlg(FALSE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_SavePath = dlg.GetPathName();
	else
		return ;
	
	UpdateData(FALSE);
}

BOOL CChanMoniDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChanMoniDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int i,j,k;
	if(nXsize1!=nXsize2||nYsize1!=nYsize1||nBands1!=nBands2)
	{
		AfxMessageBox("两张影像大小不一或波段数不等，无法进行变化检测");
		return;
	}
	nXsize = nXsize1;
	nYsize = nYsize1;

	int flag=0;
	BeginWaitCursor();
/*	for(k=0;k<nXsize*nYsize;k++)
	{
		for(i=0;i<nBands1;i++)
		{
			if(poBandBlock1[i][k]<(poBandBlock2[i][k]-5)||poBandBlock1[i][k]>(poBandBlock2[i][k]+5))
			{
				flag = 0;
				break;
			}
			else
				flag = 1;//flag = 1;表示无变化
		}
		if(flag == 1)
			poBandFcolor[k] = 0;
		else
			poBandFcolor[k] = 255;
		flag = 0;
	}*/
	CImageProcessDoc Doc;
	BITMAPINFO *pBitmapInfo=(BITMAPINFO*)new char[sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(256)]; 
	Doc.CreateBitmapInfo(pBitmapInfo,nXsize,nYsize,1);
	LONG LineBytes = (nXsize*8+31)/32*4;
	HDB=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*nYsize);
	LPSTR pDB=(LPSTR)LocalLock(HDB);
	memcpy(pDB,pBitmapInfo,40+256*4);
	LPBYTE pData = (LPBYTE)pDB+40+256*4;
	//为各像素赋值
	int Gray1=0,Gray2=0;
	for(j=0;j<nYsize;j++)
	{
		for(k=0;k<nXsize;k++)
		{
			for(i=0;i<nBands1;i++)
			{
				Gray1+=(int)fabs((float)poBandBlock1[i][j*nXsize+k]-poBandBlock2[i][j*nXsize+k]);
			}
			Gray1=Gray1/nBands1*3;
			if(Gray1>255)
				Gray1 = 255;
			pData[(nYsize-j-1)*LineBytes + k] = Gray1;
			Gray1 = Gray2 = 0;
			
		}
	}
	::LocalUnlock((HLOCAL)HDB);
	for(i=0;i<nBands1;i++)
	{
		CPLFree(poBandBlock1[i]);
		CPLFree(poBandBlock2[i]);
	}

	if(m_SavePath!="")
	{
		CFile file;
		file.Open(m_SavePath,CFile::modeCreate|CFile::modeWrite);
		SaveDIB(HDB,file);
	}
	EndWaitCursor();
	UpdateData(TRUE);
	CDialog::OnOK();
}
