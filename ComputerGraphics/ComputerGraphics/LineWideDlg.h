#if !defined(AFX_LINEWIDEDLG_H__00D94551_39AF_4F37_97FF_4122738A1C74__INCLUDED_)
#define AFX_LINEWIDEDLG_H__00D94551_39AF_4F37_97FF_4122738A1C74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineWideDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLineWideDlg dialog

class CLineWideDlg : public CDialog
{
// Construction
public:
	CLineWideDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLineWideDlg)
	enum { IDD = IDD_LINEWIDE };
	int		m_LineWide;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineWideDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineWideDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEWIDEDLG_H__00D94551_39AF_4F37_97FF_4122738A1C74__INCLUDED_)
