#if !defined(AFX_ROTATEDLG_H__A8E60C01_AE73_40CB_A8A5_6FFD2CDCAD7D__INCLUDED_)
#define AFX_ROTATEDLG_H__A8E60C01_AE73_40CB_A8A5_6FFD2CDCAD7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RotateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRotateDlg dialog

class CRotateDlg : public CDialog
{
// Construction
public:
	HDIB Rotate(HDIB hold,double angle);
	CRotateDlg(CWnd* pParent = NULL);   // standard constructor

	HDIB HOld,HNew;
// Dialog Data
	//{{AFX_DATA(CRotateDlg)
	enum { IDD = IDD_ROTATE };
	float	m_Angle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRotateDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTATEDLG_H__A8E60C01_AE73_40CB_A8A5_6FFD2CDCAD7D__INCLUDED_)
