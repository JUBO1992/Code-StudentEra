// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "DriveDetecting.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_DriveDetecting_WORKSPACE, &CMainFrame::OnDriveDetectingWorkspace)
	ON_UPDATE_COMMAND_UI(ID_DriveDetecting_WORKSPACE, &CMainFrame::OnUpdateDriveDetectingWorkspace)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	m_MainButton = m_wndRibbonBar.GetApplicationButton();
	InitMainButton(m_MainButton);
	InitTabButton(&m_PanelImages);
	InitCategory();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ز˵���ͼ��(�����κα�׼��������):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
	m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);


	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	return 0;
}

void CMainFrame::InitMainButton(CMFCRibbonApplicationButton *p_MainButton)
{
	p_MainButton->SetImage(IDB_MAINBTN);
	m_wndRibbonBar.SetApplicationButton(p_MainButton,CSize(45,45));
	p_MainButton->SetToolTipText(_T("���˵�"));
	p_MainButton->SetText(_T("\nf"));

	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(_T("���˵�"), IDB_FILESMALL, IDB_FILELARGE);

	CMFCRibbonButton* btn_tep = new CMFCRibbonButton(IDC_STATIC, _T("�ļ�����"), -1, 1);
	btn_tep->AddSubItem(new CMFCRibbonLabel(_T("�ļ�����")));
	btn_tep->SetDefaultCommand(FALSE);
	pMainPanel->Add(btn_tep);

	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, _T("�½�"),0,0));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, _T("��"),1,1));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, _T("�ر�"),8,8));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, _T("����"),2,2));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, _T("���"),3,3));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_PRINT, _T("��ӡ"),4,4));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, _T("����"),5,5));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, _T("Ԥ��"),6,6));
	pMainPanel->Add(new CMFCRibbonButton(ID_APP_ABOUT, _T("����"),7,7));
	pMainPanel->Add(new CMFCRibbonButton(ID_APP_EXIT, _T("�˳�"),9,8));

	pMainPanel->AddRecentFilesList(_T("�˵�����"),100);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, _T("�˳�"), 10));

}

void CMainFrame::InitTabButton(CMFCToolBarImages *p_TabButton)
{
	p_TabButton->Load(IDR_MAINFRAME_256);
	p_TabButton->SetImageSize(CSize(16, 16));


	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_DriveDetecting_WORKSPACE, _T("WS\na"), m_PanelImages.ExtractIcon(18)));
// 	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_MENUITEM_LIDAR_CLASS_FITER, _T("\na"), m_PanelImages.ExtractIcon(5)));
}

void CMainFrame::InitCategory()
{
	CMFCRibbonCategory *m_pCate = m_wndRibbonBar.GetActiveCategory();
	CMFCRibbonPanel *m_pane = m_pCate->AddPanel(_T("OpenCV"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_CV_CALL_CAMERA, _T("����ͷ"),9,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_PLAY_VIDEO, _T("����avi"),10,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_CANNY, _T("Cy�˲�"),11,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_PYR_DOWN, _T("��    ��"),12,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_HISTOGRAM, _T("ֱ��ͼ"),13,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_CONVOLUTION, _T("��    ��"),14,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_UNDO_ALL, _T("��������"),15,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_HOUGH_LINE, _T("Hough��"),16,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_PERSPTRANS, _T("͸�ӱ任"),17,-1));

	m_pane = m_pCate->AddPanel(_T("DETECT"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_CV_EYEDET, _T("�ۼ��"),18,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_MOUTHDET, _T("����"),19,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_NOSEDET, _T("�Ǽ��"),20,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_EYEDET2, _T("�ۼ��2"),18,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_MOUTHDET2, _T("����2"),19,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_NOSEDET2, _T("�Ǽ��2"),20,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_FACE_DETECT, _T("�����"),-1,4));
	m_pane->AddSeparator();
	m_pane->Add(new CMFCRibbonButton(ID_CV_SEAT_BELT, _T("��ȫ��"),21,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_SEAT_BELT2, _T("��ȫ��2"),21,-1));
	m_pane->AddSeparator();
	m_pane->Add(new CMFCRibbonButton(ID_CV_STEERWHEEL, _T("������"),22,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_STEERWHEEL1, _T("������1"),22,-1));
	m_pane->Add(new CMFCRibbonButton(ID_CV_STEERWHEEL2, _T("������2"),22,-1));

	m_pane = m_pCate->AddPanel(_T("GeneralFunc"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_CV_RGB2GRAY, _T("תΪ�Ҷ�"),-1,5));
	m_pane->Add(new CMFCRibbonButton(ID_CV_INVERT_COLOR, _T("ͼ��ɫ"),-1,6));
	m_pane->Add(new CMFCRibbonButton(ID_CV_OPEN_IMAGE, _T("��ͼ��"),-1,7));
	m_pane->Add(new CMFCRibbonButton(ID_SET_HOUGH_PARAM, _T("����Hough����"),-1,8));


// 	for(int i = 0;i<5;i++)
// 		CMFCRibbonCategory *m_pCate = m_wndRibbonBar.AddCategory(_T("��Ŀ����"),0,0);
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// ��������ͼ
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ���������ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����ļ���ͼ
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������ļ���ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	// �������Դ���
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������ԡ�����\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}

void CMainFrame::OnDriveDetectingWorkspace()
{
	// TODO: �ڴ���������������
	m_wndFileView.ShowPane(!m_wndFileView.IsVisible(),FALSE,FALSE);
}

void CMainFrame::OnUpdateDriveDetectingWorkspace(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_wndFileView.IsVisible());
}
