#if !defined(AFX_DISTRANSDLG_H__922DCFA3_C3B1_47DA_AD5F_A60F669637FC__INCLUDED_)
#define AFX_DISTRANSDLG_H__922DCFA3_C3B1_47DA_AD5F_A60F669637FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisTransDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisTransDlg dialog

class CDisTransDlg : public CDialog
{
// Construction
public:
	HDIB HOld,HNew;
	CDisTransDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDisTransDlg)
	enum { IDD = IDD_DISTRANS };
	float	m_Fujiao;
	float	m_Saomiaojiao;
	float	m_FlyHeight;
	float	m_Resolution;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDisTransDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISTRANSDLG_H__922DCFA3_C3B1_47DA_AD5F_A60F669637FC__INCLUDED_)
