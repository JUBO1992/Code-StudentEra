#if !defined(AFX_NDVIDLG_H__549967A2_DA20_4C91_B5D8_CA9B2CB9D0AE__INCLUDED_)
#define AFX_NDVIDLG_H__549967A2_DA20_4C91_B5D8_CA9B2CB9D0AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NDVIDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNDVIDlg dialog

class CNDVIDlg : public CDialog
{
// Construction
public:
	CNDVIDlg(CWnd* pParent = NULL);   // standard constructor

	HDIB HDB1,HDB2,HDBN;

// Dialog Data
	//{{AFX_DATA(CNDVIDlg)
	enum { IDD = IDD_NDVI };
	CString	m_InputPath1;
	CString	m_InputPath2;
	CString	m_OutputPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNDVIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNDVIDlg)
	afx_msg void OnButtonInput1();
	afx_msg void OnButtonInput2();
	afx_msg void OnButtonOutput();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NDVIDLG_H__549967A2_DA20_4C91_B5D8_CA9B2CB9D0AE__INCLUDED_)
