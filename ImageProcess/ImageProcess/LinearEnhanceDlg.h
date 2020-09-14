#if !defined(AFX_LINEARENHANCEDLG_H__7C918DBA_4E84_42CE_A6D6_048695CAC8E3__INCLUDED_)
#define AFX_LINEARENHANCEDLG_H__7C918DBA_4E84_42CE_A6D6_048695CAC8E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinearEnhanceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinearEnhanceDlg dialog

class CLinearEnhanceDlg : public CDialog
{
// Construction
public:
	HDIB LinearTrans(HDIB hold,float A,float B);
	CLinearEnhanceDlg(CWnd* pParent = NULL);   // standard constructor

	HDIB HOld,HNew;
// Dialog Data
	//{{AFX_DATA(CLinearEnhanceDlg)
	enum { IDD = IDD_LINEAR_ENHANCE };
	float	m_add;
	float	m_multi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinearEnhanceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinearEnhanceDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEARENHANCEDLG_H__7C918DBA_4E84_42CE_A6D6_048695CAC8E3__INCLUDED_)
