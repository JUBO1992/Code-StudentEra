#if !defined(AFX_OPENRAW_H__B940B10E_13DF_426F_AFA9_6BEEA2A41842__INCLUDED_)
#define AFX_OPENRAW_H__B940B10E_13DF_426F_AFA9_6BEEA2A41842__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Openraw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenraw dialog

class COpenraw : public CDialog
{
// Construction
public:
	COpenraw(CWnd* pParent = NULL);   // standard constructor
	void CreateBitmapInfo(BITMAPINFO *pBitmapInfo,int Width,int Height,int flag);
	HDIB hDB;
// Dialog Data
	//{{AFX_DATA(COpenraw)
	enum { IDD = IDD_OPENRAW };
	int		m_Width;
	int		m_Height;
	CString	m_Filepath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenraw)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenraw)
	afx_msg void OnScan();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENRAW_H__B940B10E_13DF_426F_AFA9_6BEEA2A41842__INCLUDED_)
