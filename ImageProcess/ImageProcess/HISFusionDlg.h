#if !defined(AFX_HISFUSIONDLG_H__911F5497_80E5_4D19_9F79_B6EF9C7AA2A0__INCLUDED_)
#define AFX_HISFUSIONDLG_H__911F5497_80E5_4D19_9F79_B6EF9C7AA2A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HISFusionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHISFusionDlg dialog

class CHISFusionDlg : public CDialog
{
// Construction
public:
	void WeightFusion();
	void NonWeightFusion();
	void HisFusion();
	CHISFusionDlg(CWnd* pParent = NULL);   // standard constructor

	int fusion;
	HDIB HDB1,HDB2;
	void OnHisPositive(float *Intensity,float *Hue,float *Saturation) ;
    void Histogrammatch(float *Intensity,BYTE *pImg);
    void OnHisNegative(float *Intensity,float *Hue,float *Saturation);
// Dialog Data
	//{{AFX_DATA(CHISFusionDlg)
	enum { IDD = IDD_HISFUSION };
	CString	m_MultPath;
	CString	m_PanchPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHISFusionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHISFusionDlg)
	afx_msg void OnButtonPanch();
	afx_msg void OnButtonMult();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISFUSIONDLG_H__911F5497_80E5_4D19_9F79_B6EF9C7AA2A0__INCLUDED_)
