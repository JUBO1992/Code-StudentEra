// NDVIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "NDVIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNDVIDlg dialog


CNDVIDlg::CNDVIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNDVIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNDVIDlg)
	m_InputPath1 = _T("");
	m_InputPath2 = _T("");
	m_OutputPath = _T("");
	//}}AFX_DATA_INIT
	HDB1=HDB2=HDBN=NULL;
}


void CNDVIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNDVIDlg)
	DDX_Text(pDX, IDC_INPUTPATH1, m_InputPath1);
	DDX_Text(pDX, IDC_INPUTPATH2, m_InputPath2);
	DDX_Text(pDX, IDC_OUTPUTPATH, m_OutputPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNDVIDlg, CDialog)
	//{{AFX_MSG_MAP(CNDVIDlg)
	ON_BN_CLICKED(IDC_BUTTON_INPUT1, OnButtonInput1)
	ON_BN_CLICKED(IDC_BUTTON_INPUT2, OnButtonInput2)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, OnButtonOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNDVIDlg message handlers

void CNDVIDlg::OnButtonInput1() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|所有文件(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_InputPath1 = dlg.GetPathName();
	else
		return ;
	CFile file;
	file.Open(m_InputPath1,CFile::modeRead);
	HDB1=ReadDIBFile(file);
	UpdateData(FALSE);
}

void CNDVIDlg::OnButtonInput2() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|所有文件(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_InputPath2 = dlg.GetPathName();
	else
		return ;
	CFile file;
	file.Open(m_InputPath2,CFile::modeRead);
	HDB2=ReadDIBFile(file);
	UpdateData(FALSE);
}

void CNDVIDlg::OnButtonOutput() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|所有文件(*.*)|*.*||";
	CFileDialog dlg(FALSE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_OutputPath = dlg.GetPathName();
	else
		return ;
	
	UpdateData(FALSE);
}

void CNDVIDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(HDB1==NULL || HDB2==NULL)
		return;
	LPSTR pDb1=(LPSTR)LocalLock(HDB1);
	LPSTR pDb2=(LPSTR)LocalLock(HDB2);
	LONG Width=DIBWidth(pDb1);
	LONG Height=DIBHeight(pDb1);
	LPBYTE pData1=(LPBYTE)FindDIBBits(pDb1);
	LPBYTE pData2=(LPBYTE)FindDIBBits(pDb2);
	LONG LineBytes=(Width*8+31)/32*4;
	HDBN=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
	LPSTR pDbN=(LPSTR)LocalLock(HDBN);
	memcpy(pDbN,pDb1,40+256*4);
	LPBYTE pDataN=(LPBYTE)pDbN+40+256*4;
	int i,j;
	double Gray;
	for(i=0;i<Height;i++)
	{
		for(j=0;j<Width;j++)
		{
			if(pData1[i*LineBytes+j]!=0 && pData2[i*LineBytes+j]!=0)
				Gray=(double)(pData1[i*LineBytes+j]-pData2[i*LineBytes+j])/(pData1[i*LineBytes+j]+pData2[i*LineBytes+j]);
			else
				Gray=0;
			Gray=(int)fabs((float)255*Gray);
			pDataN[i*LineBytes+j]=Gray;
		}
	}
	::LocalUnlock((HLOCAL)HDB1);
	::LocalFree((HLOCAL)HDB1);
	::LocalUnlock((HLOCAL)HDB2);
    ::LocalFree((HLOCAL)HDB2);
	::LocalUnlock((HLOCAL)HDBN);
	if(m_OutputPath!="")
	{
		CFile file;
		file.Open(m_OutputPath,CFile::modeCreate|CFile::modeWrite);
		SaveDIB(HDBN,file);
	}
	UpdateData(FALSE);
	CDialog::OnOK();
}
