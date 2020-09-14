#if !defined(AFX_LADARPOINTDLG_H__4D1F1F15_82D6_4F11_8231_6907FAD60152__INCLUDED_)
#define AFX_LADARPOINTDLG_H__4D1F1F15_82D6_4F11_8231_6907FAD60152__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LadarPointDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLadarPointDlg dialog

class CLadarPointDlg : public CDialog
{
// Construction
public:
	CLadarPointDlg(CWnd* pParent = NULL);   // standard constructor
	HDIB HDB;
	float (*point)[4];
	int PNum;
	int nXsize,nYsize;
	BYTE *poBandGray;//¼Ù²ÊÉ«²¨¶Î£¬ÓÃÓÚÊä³öÍ¼Ïñ
// Dialog Data
	//{{AFX_DATA(CLadarPointDlg)
	enum { IDD = IDD_LADARPOINT };
	CString	m_InPutPath;
	CString	m_OutPutPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLadarPointDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLadarPointDlg)
	afx_msg void OnScanfilepath();
	virtual void OnOK();
	afx_msg void OnScansavepath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADARPOINTDLG_H__4D1F1F15_82D6_4F11_8231_6907FAD60152__INCLUDED_)
