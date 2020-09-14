#if !defined(AFX_HISTOGRAMDLG_H__F2BFCA82_79F9_4818_A528_7158577CF225__INCLUDED_)
#define AFX_HISTOGRAMDLG_H__F2BFCA82_79F9_4818_A528_7158577CF225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistogramDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistogramDlg dialog

class CHistogramDlg : public CDialog
{
// Construction
public:
	void PaintB();
	void PaintG();
	void PaintR();
	void PaintGray();
	void HistogramEqual(HDIB hdb);
	CHistogramDlg(CWnd* pParent = NULL);   // standard constructor

	HDIB HDB;
	float *GrayRatio,*RRatio,*GRatio,*BRatio;
	int bits;
// Dialog Data
	//{{AFX_DATA(CHistogramDlg)
	enum { IDD = IDD_HISTOGRAM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHistogramDlg)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMDLG_H__F2BFCA82_79F9_4818_A528_7158577CF225__INCLUDED_)
