#if !defined(AFX_DRAWCHARDLG_H__F446D20C_6612_40D9_9C6B_5E0FCE752C2A__INCLUDED_)
#define AFX_DRAWCHARDLG_H__F446D20C_6612_40D9_9C6B_5E0FCE752C2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRAWCHARDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDRAWCHARDLG dialog

class CDRAWCHARDLG : public CDialog
{
// Construction
public:
	CDRAWCHARDLG(CWnd* pParent = NULL);   // standard constructor
public:
	CFont m_fnt;
	COLORREF m_clrText;
// Dialog Data
	//{{AFX_DATA(CDRAWCHARDLG)
	enum { IDD = IDD_DRAWCHAR };
	CString	m_strString;
	int		m_nX;
	int		m_nY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDRAWCHARDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDRAWCHARDLG)
	afx_msg void OnButtonFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWCHARDLG_H__F446D20C_6612_40D9_9C6B_5E0FCE752C2A__INCLUDED_)
