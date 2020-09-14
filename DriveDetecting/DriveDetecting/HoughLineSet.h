#pragma once


// CHoughLineSet 对话框

class CHoughLineSet : public CDialog
{
	DECLARE_DYNAMIC(CHoughLineSet)

public:
	CHoughLineSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHoughLineSet();

// 对话框数据
	enum { IDD = IDD_HOUGHLINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_param1;
	double m_param2;
	double m_rho;
	double m_theta;
	int m_threshold;
};
