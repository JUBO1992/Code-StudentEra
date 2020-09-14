// ImageInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "ImageInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageInfo dialog


CImageInfo::CImageInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CImageInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageInfo)
	m_MaxBand = 0;
	m_MinBand = 0;
	//}}AFX_DATA_INIT
}


void CImageInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageInfo)
	DDX_Control(pDX, IDC_COMBORED, m_ComboRed);
	DDX_Control(pDX, IDC_COMBOGREEN, m_ComboGreen);
	DDX_Control(pDX, IDC_COMBOBLUE, m_ComboBlue);
	DDX_Control(pDX, IDC_COMBO_GRAY, m_ComboGray);
	DDX_Control(pDX, IDC_COMBO_IMAGESHOW, m_ComboImageShow);
	DDX_Text(pDX, IDC_MAXBAND, m_MaxBand);
	DDX_Text(pDX, IDC_MINBAND, m_MinBand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageInfo, CDialog)
	//{{AFX_MSG_MAP(CImageInfo)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_IMAGESHOW, OnSelchangeComboImageshow)
	ON_CBN_SELCHANGE(IDC_COMBO_GRAY, OnSelchangeComboGray)
	ON_CBN_SELCHANGE(IDC_COMBOBLUE, OnSelchangeComboblue)
	ON_CBN_SELCHANGE(IDC_COMBOGREEN, OnSelchangeCombogreen)
	ON_CBN_SELCHANGE(IDC_COMBORED, OnSelchangeCombored)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageInfo message handlers

BOOL CImageInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if(m_MaxBand == 1)//灰度
	{
	m_ComboGray.ShowWindow(SW_NORMAL);		//定义初始显示状态，显示“灰度”选项
	m_ComboRed.ShowWindow(SW_HIDE);
	m_ComboGreen.ShowWindow(SW_HIDE);
	m_ComboBlue.ShowWindow(SW_HIDE);
	m_ComboImageShow.SetCurSel(0);
	}	
	else//彩色
	{
	m_ComboGray.ShowWindow(SW_HIDE);		//定义初始显示状态，显示“彩色”选项
	m_ComboRed.ShowWindow(SW_NORMAL);
	m_ComboGreen.ShowWindow(SW_NORMAL);
	m_ComboBlue.ShowWindow(SW_NORMAL);
	m_ComboImageShow.SetCurSel(1);
	}

	nChoiceShow = m_ComboImageShow.GetCurSel();
	m_BandChoice = m_ComboGray.SetCurSel(0);//灰度
	if(m_MaxBand == 3)//三波段真彩色
	{
		m_BandChoiceR = m_ComboRed.SetCurSel(0);
		m_BandChoiceG = m_ComboGreen.SetCurSel(1);
		m_BandChoiceB = m_ComboBlue.SetCurSel(2);
	}
	else if(m_MaxBand == 4||m_MaxBand == 5||m_MaxBand == 6||m_MaxBand == 7)//m_MaxBand == 7为TM影像
	{
		m_BandChoiceR = m_ComboRed.SetCurSel(2);
		m_BandChoiceG = m_ComboGreen.SetCurSel(1);
		m_BandChoiceB = m_ComboBlue.SetCurSel(0);
	}
	else if(m_MaxBand == 8)//ETM
	{
		m_BandChoiceR = m_ComboRed.SetCurSel(3);
		m_BandChoiceG = m_ComboGreen.SetCurSel(2);
		m_BandChoiceB = m_ComboBlue.SetCurSel(1);
	}
	

	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImageInfo::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CImageInfo::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CImageInfo::OnSelchangeComboImageshow() 
{
	// TODO: Add your control notification handler code here
	nChoiceShow = m_ComboImageShow.GetCurSel();		//获得当前选项的索引
	switch(nChoiceShow)
	{
	case 0:
	/*	pWndCtrl = new CStatic;
		((CStatic *)pWndCtrl)->Create(_T("灰度显示"), WS_VISIBLE, 
									CRect(50,100,150,200),this, 1);
		pWndCtrl = new CComboBox;
		((CComboBox *)pWndCtrl)->Create( WS_VISIBLE|WS_BORDER, CRect(150,100,250,200), 
									this, IDC_COMBONBND);
	*/
		m_ComboGray.ShowWindow(SW_NORMAL);
		m_ComboRed.ShowWindow(SW_HIDE);
		m_ComboGreen.ShowWindow(SW_HIDE);
		m_ComboBlue.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_ComboRed.ShowWindow(SW_NORMAL);
		m_ComboGreen.ShowWindow(SW_NORMAL);
		m_ComboBlue.ShowWindow(SW_NORMAL);
		m_ComboGray.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_ComboGray.ShowWindow(SW_NORMAL);
		m_ComboRed.ShowWindow(SW_HIDE);
		m_ComboGreen.ShowWindow(SW_HIDE);
		m_ComboBlue.ShowWindow(SW_HIDE);
		break;
	}

}

void CImageInfo::OnSelchangeComboGray() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ComboGray.GetCurSel();
	CString m_BandChoiceT; 
    m_ComboGray.GetLBText(nIndex,m_BandChoiceT);
	m_BandChoice = atoi(m_BandChoiceT)-1;
	//m_BandChoice = m_ComboBands.Get
	//GetDlgItemTextA(IDC_COMBO,变量);IDC_COMBONBNDR
//	UpdateData(FALSE);
}

void CImageInfo::OnSelchangeComboblue() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ComboBlue.GetCurSel();//返回组合框中列表框中当前选中的项的下标。如果没有选中项，则返回CB_ERR
	CString m_BandChoiceBT; 
    m_ComboBlue.GetLBText(nIndex,m_BandChoiceBT);
	//GetLBText把索引号为nIndex的数据放到rString变量中. 与其对应的GetLBTextLen(int nIndex)函数就是得到索引号为nIndex中数据的长度。
	m_BandChoiceB = atoi(m_BandChoiceBT)-1;
	//atoi把字符串转换成整型数.
 
}

void CImageInfo::OnSelchangeCombogreen() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ComboGreen.GetCurSel();
	CString m_BandChoiceGT; 
    m_ComboGreen.GetLBText(nIndex,m_BandChoiceGT);
	m_BandChoiceG = atoi(m_BandChoiceGT)-1;

}

void CImageInfo::OnSelchangeCombored() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ComboRed.GetCurSel();
	CString m_BandChoiceRT; 
    m_ComboRed.GetLBText(nIndex,m_BandChoiceRT);
	m_BandChoiceR = atoi(m_BandChoiceRT)-1;

}
