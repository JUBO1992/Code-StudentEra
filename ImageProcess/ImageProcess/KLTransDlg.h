#if !defined(AFX_KLTRANSDLG_H__32CCA808_22B7_4423_9DFE_1503331CE150__INCLUDED_)
#define AFX_KLTRANSDLG_H__32CCA808_22B7_4423_9DFE_1503331CE150__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KLTransDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CKLTransDlg dialog

class CKLTransDlg : public CDialog
{
// Construction
public:
	int MatrixTrans(double *In,double*Out,int m,int n);//����ת��
	int Multiply(double *M1, int m1, int n, int m2, double *M2,double *Out);//�������
	int Covariance(double *M,int m,int n,double *Cov);//�������M��Э�������Cov
	int eejcb(double a[],int n,double v[],double eps,int jt);//��������ֵ����������
	int nBands;
	int nXsize,nYsize;
	HDIB HDB,HDBN;
	//BYTE *poBandBlock[8];//ָ�����飬����8��ָ������飬�洢��ȡ��Ӱ������
	//BYTE *poBand[8];//K-L
	
	CKLTransDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKLTransDlg)
	enum { IDD = IDD_KLTRANS };
	CString	m_InputFile;
	CString	m_OutputFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKLTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKLTransDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnScaninput();
	afx_msg void OnScanoutput();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KLTRANSDLG_H__32CCA808_22B7_4423_9DFE_1503331CE150__INCLUDED_)
