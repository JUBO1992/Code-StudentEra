// HoughLineSet.cpp : 实现文件
//

#include "stdafx.h"
#include "DriveDetecting.h"
#include "HoughLineSet.h"
#include "afxdialogex.h"


// CHoughLineSet 对话框

IMPLEMENT_DYNAMIC(CHoughLineSet, CDialog)

CHoughLineSet::CHoughLineSet(CWnd* pParent /*=NULL*/)
	: CDialog(CHoughLineSet::IDD, pParent)
{

	m_param1 = 60.0;
	m_param2 = 7.0;
	m_rho = 1.0;
	m_theta = 1.0;
	m_threshold = 80;
}

CHoughLineSet::~CHoughLineSet()
{
}

void CHoughLineSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PARAM1, m_param1);
	DDX_Text(pDX, IDC_PARAM2, m_param2);
	DDX_Text(pDX, IDC_RHO, m_rho);
	DDX_Text(pDX, IDC_THETA, m_theta);
	DDX_Text(pDX, IDC_THRESHOLD, m_threshold);
}


BEGIN_MESSAGE_MAP(CHoughLineSet, CDialog)
END_MESSAGE_MAP()


// CHoughLineSet 消息处理程序
