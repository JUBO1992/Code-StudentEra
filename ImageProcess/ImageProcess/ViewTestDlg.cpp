// ViewTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "ViewTestDlg.h"
#include "afxdialogex.h"


// CViewTestDlg 对话框

IMPLEMENT_DYNAMIC(CViewTestDlg, CDialogEx)

CViewTestDlg::CViewTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewTestDlg::IDD, pParent)
{
	m_view1 = NULL;
	m_view2 = NULL;
}

CViewTestDlg::~CViewTestDlg()
{
}

void CViewTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
}


BEGIN_MESSAGE_MAP(CViewTestDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CViewTestDlg 消息处理程序


BOOL CViewTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitView();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CViewTestDlg::InitView()
{
	CCreateContext pContext;
	pContext.m_pCurrentDoc = NULL;
	pContext.m_pNewViewClass = RUNTIME_CLASS(CTestView);

	CFrameWnd* pFrmWnd = (CFrameWnd*)this;
	m_view1 = (CTestView*)((CFrameWnd*)pFrmWnd)->CreateView(&pContext);
	ASSERT(m_view1);
	m_view1->ShowWindow(SW_NORMAL);

	m_view2 = (CTestView*)((CFrameWnd*)pFrmWnd)->CreateView(&pContext);
	ASSERT(m_view2);
	m_view2->ShowWindow(SW_NORMAL);

}

void CViewTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_view1&&m_view2)
	{
		m_view1->Invalidate();
		m_view2->Invalidate();

		CRect rect;
		GetClientRect(rect);

		int Width = rect.Width();
		int Height = rect.Height();

		m_view1->MoveWindow(0,0,Width/2,Height-200);
		m_view1->Invalidate();

		m_view2->MoveWindow(Width/2,0,Width/2,Height-200);
		m_view2->Invalidate();

		m_list1.MoveWindow(0,Height-200,Width/2,200);
		m_list1.Invalidate();

		m_list2.MoveWindow(Width/2,Height-200,Width/2,200);
		m_list2.Invalidate();
	}
}


void CViewTestDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
// 	CDialogEx::OnClose();
}


void CViewTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	delete this;
}
