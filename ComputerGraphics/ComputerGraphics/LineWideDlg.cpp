// LineWideDlg.cpp : implementation file
//

#include "stdafx.h"
#include "2010302590054.h"
#include "LineWideDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineWideDlg dialog


CLineWideDlg::CLineWideDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLineWideDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineWideDlg)
	m_LineWide = 0;
	//}}AFX_DATA_INIT
}


void CLineWideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineWideDlg)
	DDX_Text(pDX, IDC_EDIT1, m_LineWide);
	DDV_MinMaxInt(pDX, m_LineWide, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineWideDlg, CDialog)
	//{{AFX_MSG_MAP(CLineWideDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineWideDlg message handlers
