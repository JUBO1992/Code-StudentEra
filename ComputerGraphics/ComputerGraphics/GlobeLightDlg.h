#if !defined(AFX_GLOBELIGHTDLG_H__CD204335_C59B_4112_8DB6_8E41A4B7211B__INCLUDED_)
#define AFX_GLOBELIGHTDLG_H__CD204335_C59B_4112_8DB6_8E41A4B7211B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobeLightDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGlobeLightDlg dialog

class CGlobeLightDlg : public CDialog
{
// Construction
public:
	CGlobeLightDlg(CWnd* pParent = NULL);   // standard constructor
	void Draw();
	double CalculateCos(int a,int b,int c);
	double CalculateCosi(int a,int b,int c);
	double guangqiang(int a,int b,int c);
    int n;
// Dialog Data
	//{{AFX_DATA(CGlobeLightDlg)
	enum { IDD = IDD_GLOBE_LIGHT };
	int		m_lightX;
	int		m_colorR;
	int		m_colorG;
	int		m_colorB;
	int		m_lightY;
	int		m_lightZ;
	int		m_R;
	double	m_man;
	double	m_jing;
	double	m_hjgq;
	double	m_gdgq;
	int		m_tt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlobeLightDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGlobeLightDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBELIGHTDLG_H__CD204335_C59B_4112_8DB6_8E41A4B7211B__INCLUDED_)
