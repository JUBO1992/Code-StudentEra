#if !defined(AFX_CHANMONIDLG_H__911C0F82_D37A_4E68_A639_80A9C16F7EA0__INCLUDED_)
#define AFX_CHANMONIDLG_H__911C0F82_D37A_4E68_A639_80A9C16F7EA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChanMoniDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChanMoniDlg dialog

class CChanMoniDlg : public CDialog
{
// Construction
public:
	HDIB HDB;
	int nBands1,nBands2;
	int nXsize,nYsize,nXsize1,nYsize1,nXsize2,nYsize2;
	BYTE *poBandBlock1[8],*poBandBlock2[8];//指针数组，具有8个指针的数组，存储读取的影像数据
	CChanMoniDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChanMoniDlg)
	enum { IDD = IDD_MONITOR };
	CString	m_OpenPath1;
	CString	m_OpenPath2;
	CString	m_SavePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChanMoniDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChanMoniDlg)
	afx_msg void OnScan1();
	afx_msg void OnScan2();
	afx_msg void OnScansave();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANMONIDLG_H__911C0F82_D37A_4E68_A639_80A9C16F7EA0__INCLUDED_)
