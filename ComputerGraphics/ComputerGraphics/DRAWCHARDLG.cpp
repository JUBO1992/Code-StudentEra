// DRAWCHARDLG.cpp : implementation file
//

#include "stdafx.h"
#include "2010302590054.h"
#include "DRAWCHARDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDRAWCHARDLG dialog


CDRAWCHARDLG::CDRAWCHARDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CDRAWCHARDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDRAWCHARDLG)
	m_strString = _T("");
	m_nX = 0;
	m_nY = 0;
	m_clrText=RGB(0,0,0);
	//}}AFX_DATA_INIT
}


void CDRAWCHARDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDRAWCHARDLG)
	DDX_Text(pDX, IDC_EDIT_STRING, m_strString);
	DDX_Text(pDX, IDC_EDIT_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_Y, m_nY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDRAWCHARDLG, CDialog)
	//{{AFX_MSG_MAP(CDRAWCHARDLG)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRAWCHARDLG message handlers

void CDRAWCHARDLG::OnButtonFont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_fnt.DeleteObject();
		LOGFONT LogFnt;
		dlg.GetCurrentFont(&LogFnt);
		m_fnt.CreateFontIndirect(&LogFnt);
		m_clrText=dlg.GetColor();
	}
}
