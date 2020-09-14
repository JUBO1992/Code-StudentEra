#if !defined(AFX_CLASSIFYDLG_H__D76BCE67_E1DC_4211_9B17_A0E1C7F0B24C__INCLUDED_)
#define AFX_CLASSIFYDLG_H__D76BCE67_E1DC_4211_9B17_A0E1C7F0B24C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassifyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClassifyDlg dialog

class CClassifyDlg : public CDialog
{
// Construction
public:
	CClassifyDlg(CWnd* pParent = NULL);   // standard constructor
	HDIB HDB;
	int nBands,nXsize,nYsize;
	int Num[20];//存储每类像素数目
	BYTE *poBandBlock[8];//指针数组，具有8个指针的数组，存储读取的影像数据

	int Minimum(int *d);//求一维数组中最小值并返回其下标
	BOOL Compare(double (*c1)[8],double (*c2)[8],int Category);//比较前后两次聚类中心是否相同
	BOOL Sort(double *in,double *out,int m);//排序
// Dialog Data
	//{{AFX_DATA(CClassifyDlg)
	enum { IDD = IDD_CLASSIFY };
	int		m_Category;
	CString	m_Inputpath;
	CString	m_Outputpath;
	int		m_Interation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassifyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClassifyDlg)
	afx_msg void OnButtonInput();
	afx_msg void OnButtonOutput();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSIFYDLG_H__D76BCE67_E1DC_4211_9B17_A0E1C7F0B24C__INCLUDED_)
