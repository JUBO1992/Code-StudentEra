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
	int nBands,nXsize,nYsize,C;//ʵʱ����������Ŀ
	int Num[50];//�洢ÿ��������Ŀ
	BYTE *poBandBlock[8];//ָ�����飬����8��ָ������飬�洢��ȡ��Ӱ������
	
	int Minimum(double *d,int m);//��һά��������Сֵ���������±꣬mΪһά�����С���������

	//����ΪISODATA�����㷨��������Ӧ�ĺ���������ֵΪ��Ҫ��ת���Ĳ���
	//(*c)[8]�洢�������ģ�*D1�洢������ģʽ�������ľ����ֵ��
	//D�洢������������Ӧ�������ĵľ����ֵ��(*segma)[8]�洢ÿһ��������������ľ���ı�׼������
	int Step234(double (*c)[8],double *D1,double D,double (*segma)[8]);
	int Step5(int In);//InΪ��������
	int Step678(double (*c)[8],double *D1,double D,double (*segma)[8]);
	int Step9_11(double (*c)[8]);
	CISODATA(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CISODATA)
	enum { IDD = IDD_ISODATA };
	CString	m_InputFileName;
	CString	m_OutputFileName;
	int		m_K;//�����
	int		m_PNum;//һ������Ӧ�þ��е�������Ŀ
	double	m_Stdv;//��׼����ֵ
	double	m_C;//�������ļ����ֵ���鲢ϵ��
	int		m_L;//���鲢�����
	int		m_I;//����������
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
