#if !defined(AFX_CUBESPINDLG_H__70BD5ABD_477D_4E3B_868A_4EB923B152D0__INCLUDED_)
#define AFX_CUBESPINDLG_H__70BD5ABD_477D_4E3B_868A_4EB923B152D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CubeSpinDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCubeSpinDlg dialog

class CCubeSpinDlg : public CDialog
{
// Construction
public:
	void fill(POINT *x,POINT *y,POINT *z,int i,int j,int q);
	int Maxnum(int *p,int n);
	struct D
	{
		int x;
		int y;
		int z;
	};
	void Draw();
	int a,b,c;
	int Ctrl;
	CCubeSpinDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCubeSpinDlg)
	enum { IDD = IDD_CUBESPIN };
	CScrollBar	m_Scroll3;
	CScrollBar	m_Scroll2;
	CScrollBar	m_Scroll1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCubeSpinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCubeSpinDlg)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUBESPINDLG_H__70BD5ABD_477D_4E3B_868A_4EB923B152D0__INCLUDED_)
