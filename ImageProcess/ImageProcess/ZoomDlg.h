#if !defined(AFX_ZOOMDLG_H__9EB6F6D3_86AC_4C13_9BC6_F8D7C8330113__INCLUDED_)
#define AFX_ZOOMDLG_H__9EB6F6D3_86AC_4C13_9BC6_F8D7C8330113__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog

class CZoomDlg : public CDialog
{
// Construction
public:
	HDIB Zoom(HDIB hold,double x,double y);
	CZoomDlg(CWnd* pParent = NULL);   // standard constructor

	HDIB HOld,HNew;
// Dialog Data
	//{{AFX_DATA(CZoomDlg)
	enum { IDD = IDD_ZOOM };
	float	m_ZoomX;
	float	m_ZoomY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMDLG_H__9EB6F6D3_86AC_4C13_9BC6_F8D7C8330113__INCLUDED_)
