#if !defined(AFX_ISODATA_H__C3B7E4C2_6CFE_4930_8CBE_6109A7CF7F90__INCLUDED_)
#define AFX_ISODATA_H__C3B7E4C2_6CFE_4930_8CBE_6109A7CF7F90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ISODATA.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CISODATA dialog

class CISODATA : public CDialog
{
// Construction
public:
	HDIB HDB;
	int nBands,nXsize,nYsize,C;//实时聚类中心数目
	int Num[50];//存储每类像素数目
	BYTE *poBandBlock[8];//指针数组，具有8个指针的数组，存储读取的影像数据
	
	int Minimum(double *d,int m);//求一维数组中最小值并返回其下标，m为一维数组大小（类别数）

	//以下为ISODATA分类算法各步骤相应的函数，返回值为将要跳转到的步骤
	//(*c)[8]存储聚类中心，*D1存储各类内模式与类中心距离均值，
	//D存储所有样本到相应聚类中心的距离均值，(*segma)[8]存储每一类样本与聚类中心距离的标准差向量
	int Step234(double (*c)[8],double *D1,double D,double (*segma)[8]);
	int Step5(int In);//In为迭代次数
	int Step678(double (*c)[8],double *D1,double D,double (*segma)[8]);
	int Step9_11(double (*c)[8]);
	CISODATA(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CISODATA)
	enum { IDD = IDD_ISODATA };
	CString	m_InputFileName;
	CString	m_OutputFileName;
	int		m_K;//类别数
	int		m_PNum;//一类至少应该具有的样本数目
	double	m_Stdv;//标准差阈值
	double	m_C;//积累中心间距阈值、归并系数
	int		m_L;//最大归并类别数
	int		m_I;//最大迭代次数
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CISODATA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CISODATA)
	virtual BOOL OnInitDialog();
	afx_msg void OnScaninputfile();
	afx_msg void OnScanoutputfile();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ISODATA_H__C3B7E4C2_6CFE_4930_8CBE_6109A7CF7F90__INCLUDED_)
