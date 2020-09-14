// ZoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "2010302590054.h"
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
	m_Point_X = 0;
	m_Point_Y = 0;
	m_Zoom_X = 0.0f;
	m_Zoom_Y = 0.0f;
	//}}AFX_DATA_INIT
}


void CZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomDlg)
	DDX_Text(pDX, IDC_BASEPOINT_X, m_Point_X);
	DDX_Text(pDX, IDC_BASEPOINT_Y, m_Point_Y);
	DDX_Text(pDX, IDC_ZOOM_X, m_Zoom_X);
	DDX_Text(pDX, IDC_ZOOM_Y, m_Zoom_Y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg message handlers
