#pragma once

#include "TestView.h"
// CViewTestDlg �Ի���

class CViewTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewTestDlg)

public:
	CViewTestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CViewTestDlg();

// �Ի�������
	enum { IDD = IDD_VIEWTESTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CTestView* m_view1;
	CTestView* m_view2;
	CListCtrl m_list1;
	CListCtrl m_list2;

	void InitView();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
};
