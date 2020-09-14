#if !defined(AFX_PEAKDETECTDLG_H__6B0DDAEB_192C_4C59_86D0_3C710A37E6BD__INCLUDED_)
#define AFX_PEAKDETECTDLG_H__6B0DDAEB_192C_4C59_86D0_3C710A37E6BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PeakDetectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPeakDetectDlg dialog

class CPeakDetectDlg : public CDialog
{
// Construction
public:
	int Wave[16][128];
	void OnPaint();
	CPeakDetectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPeakDetectDlg)
	enum { IDD = IDD_PEAKDETECT };
	CString	m_FilePath;
	int		m_WaveNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPeakDetectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPeakDetectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnOpenfile();
	afx_msg void OnUpdate();
	afx_msg void OnCountpeak();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEAKDETECTDLG_H__6B0DDAEB_192C_4C59_86D0_3C710A37E6BD__INCLUDED_)
