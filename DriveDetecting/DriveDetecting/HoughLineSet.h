#pragma once


// CHoughLineSet �Ի���

class CHoughLineSet : public CDialog
{
	DECLARE_DYNAMIC(CHoughLineSet)

public:
	CHoughLineSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHoughLineSet();

// �Ի�������
	enum { IDD = IDD_HOUGHLINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_param1;
	double m_param2;
	double m_rho;
	double m_theta;
	int m_threshold;
};
