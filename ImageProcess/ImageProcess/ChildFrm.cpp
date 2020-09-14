// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "ImageProcess.h"

#include "ChildFrm.h"
#include "ImageProcessView.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style   |=   WS_VISIBLE|WS_MAXIMIZE;//�Ӵ��������ʾ
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
// 	if (!SpWnd.CreateStatic(this, 1, 2))
// 		return FALSE;
// 
// 	CRect rect;
// 	this->GetWindowRect(&rect);
// 
// 	if (!SpWnd.CreateView(0, 0, RUNTIME_CLASS(CImageProcessView), CSize(500, 500), pContext) ||
// 		!SpWnd.CreateView(0, 1, RUNTIME_CLASS(CTestView), CSize(500, 500), pContext))
// 	{
// 		SpWnd.DestroyWindow();
// 		return FALSE;
// 	}	
// 	SpWnd.SetActivePane(0,0);	
// 	return TRUE;
	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}


BOOL CChildFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWnd::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
// 	CRect rect;
// 	GetClientRect(rect);
// 	SpWnd.SetColumnInfo(0,rect.Width()/2,100);
// 	SpWnd.RecalcLayout();//������仰�����ں��Ӵ�������ʱOnsize��ͬ��
}
