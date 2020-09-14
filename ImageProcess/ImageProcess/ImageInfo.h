#if !defined(AFX_IMAGEINFO_H__7D8874A1_F8D4_4AFA_BD01_14D65D47D42A__INCLUDED_)
#define AFX_IMAGEINFO_H__7D8874A1_F8D4_4AFA_BD01_14D65D47D42A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageInfo dialog

class CImageInfo : public CDialog
{
// Construction
public:
	int m_BandChoiceR;
	int m_BandChoiceG;
	int m_BandChoiceB;
	int m_BandChoice;
//	int m_BandChoiceTest;
	int nChoiceShow;//获取显示方式方式
	CImageInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImageInfo)
	enum { IDD = IDD_IMAGEINFO };
	CComboBox	m_ComboRed;
	CComboBox	m_ComboGreen;
	CComboBox	m_ComboBlue;
	CComboBox	m_ComboGray;
	CComboBox	m_ComboImageShow;
	int		m_MaxBand;
	int		m_MinBand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnSelchangeComboImageshow();
	afx_msg void OnSelchangeComboGray();
	afx_msg void OnSelchangeComboblue();
	afx_msg void OnSelchangeCombogreen();
	afx_msg void OnSelchangeCombored();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEINFO_H__7D8874A1_F8D4_4AFA_BD01_14D65D47D42A__INCLUDED_)
