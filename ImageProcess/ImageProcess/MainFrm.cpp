// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ImageProcess.h"

#include "MainFrm.h"
#include "ViewTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SKIN_AERO, OnSkinAero)
	ON_UPDATE_COMMAND_UI(ID_SKIN_AERO, OnUpdateSkinAero)
	ON_COMMAND(ID_SKIN_01, OnSkin01)
	ON_UPDATE_COMMAND_UI(ID_SKIN_01, OnUpdateSkin01)
	ON_COMMAND(ID_SKIN_02, OnSkin02)
	ON_UPDATE_COMMAND_UI(ID_SKIN_02, OnUpdateSkin02)
	ON_COMMAND(ID_SKIN_03, OnSkin03)
	ON_UPDATE_COMMAND_UI(ID_SKIN_03, OnUpdateSkin03)
	ON_COMMAND(ID_SKIN_04, OnSkin04)
	ON_UPDATE_COMMAND_UI(ID_SKIN_04, OnUpdateSkin04)
	ON_COMMAND(ID_SKIN_05, OnSkin05)
	ON_UPDATE_COMMAND_UI(ID_SKIN_05, OnUpdateSkin05)
	ON_COMMAND(ID_SKIN_06, OnSkin06)
	ON_UPDATE_COMMAND_UI(ID_SKIN_06, OnUpdateSkin06)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_BTN_ViewTestDlg, &CMainFrame::OnBtnViewTestDlg)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	//Skin
	m_nSkin = 1;
	m_nSkinAero=1;
	
	m_strSkin[0] = "Skin/skin1.she";
	m_strSkin[1] = "Skin/skin2.she";
	m_strSkin[2] = "Skin/skin3.she";
	m_strSkin[3] = "Skin/skin4.she";
	m_strSkin[4] = "Skin/skin5.she";
	m_strSkin[5] = "Skin/skin6.she";
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
// 	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	InitMainButton(&m_MainButton);
	InitTabButton(&m_PanelImages);
	InitCategory();


// 	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
// 		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
// 		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
// 	{
// 		TRACE0("Failed to create toolbar\n");
// 		return -1;      // fail to create
// 	}

// 	if (!m_wndStatusBar.Create(this) ||
// 		!m_wndStatusBar.SetIndicators(indicators,
// 		  sizeof(indicators)/sizeof(UINT)))
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
// 	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
// 	EnableDocking(CBRS_ALIGN_ANY);
// 	DockControlBar(&m_wndToolBar);

	return 0;
}

void CMainFrame::InitMainButton(CMFCRibbonApplicationButton *p_MainButton)
{
	m_MainButton.SetImage(IDB_MAINBMP);
	m_wndRibbonBar.SetApplicationButton(p_MainButton,CSize(45,45));
	m_MainButton.SetToolTipText(_T("���˵�"));
	m_MainButton.SetText(_T("\nf"));

	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(_T("���˵�"), IDB_FILESMALL, IDB_FILELARGE);

	CMFCRibbonButton* btn_tep = new CMFCRibbonButton(IDC_STATIC, _T("�ļ�����"), -1, 1);
	btn_tep->AddSubItem(new CMFCRibbonLabel(_T("�ļ�����")));
	btn_tep->SetDefaultCommand(FALSE);
	pMainPanel->Add(btn_tep);

	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, _T("�½�"),-1,0));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, _T("��"),-1,1));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, _T("�ر�"),-1,8));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, _T("����"),-1,2));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, _T("���"),-1,3));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_PRINT, _T("��ӡ"),-1,4));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, _T("����"),-1,5));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, _T("Ԥ��"),-1,6));
	pMainPanel->Add(new CMFCRibbonButton(ID_APP_ABOUT, _T("����"),-1,7));
	pMainPanel->Add(new CMFCRibbonButton(ID_APP_EXIT, _T("�˳�"),-1,8));

	pMainPanel->AddRecentFilesList(_T("�˵�����"),100);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, _T("�˳�"), 10));
}

void CMainFrame::InitTabButton(CMFCToolBarImages *p_TabButton)
{
 	p_TabButton->Load(IDB_BITMAP_TABIMG);
	p_TabButton->SetImageSize(CSize(16, 16));

// 	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_MENUITEM_LIDAR_ALLDATA, _T("\na"), m_PanelImages.ExtractIcon(18)));
// 	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_MENUITEM_LIDAR_CLASS_FITER, _T("\na"), m_PanelImages.ExtractIcon(5)));

	CMFCRibbonColorButton *m_colorbtn = new CMFCRibbonColorButton(ID_BUTTON_SET_COLOR,_T("���ñ�����ɫ"),43,-1);
	m_wndRibbonBar.AddToTabs(m_colorbtn);
	CreateDocumentColors();
	m_colorbtn->SetColumns(0);
	m_colorbtn->SetDefaultCommand(FALSE);
	m_colorbtn->EnableOtherButton(_T("������ɫ"));
	m_colorbtn->SetColorBoxSize(CSize(18, 18));
	m_colorbtn->AddColorsGroup(_T("������ɫ"), m_lstMainColors);
	m_colorbtn->AddColorsGroup(_T(""), m_lstAdditionalColors, TRUE);
	m_colorbtn->AddColorsGroup(_T("��׼��ɫ"), m_lstStandardColors);
	m_colorbtn->SetColor(RGB(0, 0, 255));

// 	CMFCRibbonComboBox* m_tep_com = new CMFCRibbonComboBox(ID_MENUITEM_LIDAR_POINT_SIZE,TRUE,50,"��ߴ磺");
// 	m_tep_com->AddItem("1");
// 	m_tep_com->AddItem("2");
// 	m_tep_com->AddItem("3");
// 	m_tep_com->AddItem("4");
// 	m_tep_com->AddItem("5");
// 	m_tep_com->SelectItem(0);
// 	m_wndRibbonBar.AddToTabs(m_tep_com);

// 	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_MENUITEM_LIDAR_HEGIT, _T("�߳���ɫ\na"), m_PanelImages.ExtractIcon(4)));
// 	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_MENUITEM_LIDAR_CLASS, _T("�����ɫ\na"), m_PanelImages.ExtractIcon(5)));
// 	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_MENUITEM_LIDAR_INTENSITY, _T("ǿ����ɫ\na"), m_PanelImages.ExtractIcon(6)));
// 	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_MENUITEM_LIDAR_ECHO, _T("�ز���ɫ\na"), m_PanelImages.ExtractIcon(7)));
// 	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_MENUITEM_LIDAR_FLIGHT, _T("������ɫ\na"), m_PanelImages.ExtractIcon(8)));
// 	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_MENUITEM_LIDAR_IMAGE, _T("Ӱ����ɫ\na"), m_PanelImages.ExtractIcon(9)));
	CMFCRibbonButton* p_btn = new CMFCRibbonButton(ID_VIEW_APPLOOK_OFF_2007_BLUE, _T("Ƥ��\na���ڷ��"), m_PanelImages.ExtractIconA(18));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_WIN_2000, _T("win2000"), NULL));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_OFF_XP, _T("offxp"), NULL));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_WIN_XP, _T("winxp"), NULL));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_VS_2005, _T("vs2005"), NULL));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_VS_2008, _T("vs2008"), NULL));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_OFF_2007_BLUE, _T("offblue"), NULL));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_OFF_2007_BLACK, _T("offblack"), NULL));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_OFF_2007_SILVER, _T("offsilver"), NULL));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_OFF_2007_AQUA, _T("offaqua"), NULL));
	p_btn->AddSubItem(new CMFCRibbonButton(ID_VIEW_APPLOOK_WINDOWS_7, _T("win7"), NULL));
	m_wndRibbonBar.AddToTabs(p_btn);
	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT,_T("����\na������Ϣ"), m_PanelImages.ExtractIcon(11)));
}

void CMainFrame::InitCategory()
{
	CMFCRibbonCategory *m_pCate = m_wndRibbonBar.AddCategory(_T("���˵�"),IDB_FILESMALL,IDB_FILELARGE);
	CMFCRibbonPanel *m_pane = m_pCate->AddPanel(_T("�ļ�"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_FILE_NEW, _T("�½��ļ�"),0,0));
	m_pane->Add(new CMFCRibbonButton(ID_FILE_OPEN, _T("��  ��"),1,-1));
	m_pane->Add(new CMFCRibbonButton(ID_FILE_CLOSE, _T("��  ��"),8,-1));
	m_pane->AddSeparator();
	m_pane->Add(new CMFCRibbonButton(ID_FILE_SAVE, _T("��  ��"),2,-1));
	m_pane->Add(new CMFCRibbonButton(ID_FILE_SAVE_AS, _T("��  ��"),3,-1));
	m_pane->AddSeparator();
	m_pane->Add(new CMFCRibbonButton(ID_FILE_PRINT, _T("��  ӡ"),4,-1));
	m_pane->Add(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, _T("��  ��"),5,-1));
	m_pane->Add(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, _T("Ԥ  ��"),6,-1));
	m_pane->AddSeparator();
	m_pane->Add(new CMFCRibbonButton(ID_APP_ABOUT, _T("����"),7,7));
	m_pane->Add(new CMFCRibbonButton(ID_APP_EXIT, _T("�˳�����"),8,8));

	m_pane = m_pCate->AddPanel(_T("�鿴"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_BTN_ViewTestDlg, _T("��ͼ����"),6,-1));
	m_pane->Add(new CMFCRibbonCheckBox(ID_VIEW_STATUS_BAR,_T("״̬��")));

	m_pane = m_pCate->AddPanel(_T("����"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_WINDOW_NEW, _T("�½�����"),-1,0));
	m_pane->Add(new CMFCRibbonButton(ID_WINDOW_CASCADE, _T("�������"),-1,1));
	m_pane->Add(new CMFCRibbonButton(ID_WINDOW_TILE_HORZ, _T("ˮƽƽ��"),-1,2));
	m_pane->Add(new CMFCRibbonButton(ID_WINDOW_TILE_VERT, _T("��ֱƽ��"),-1,3));
	m_pane->Add(new CMFCRibbonButton(ID_WINDOW_ARRANGE, _T("����ͼ��"),-1,4));

	m_pane = m_pCate->AddPanel(_T("����"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_OPENIMAGE, _T("��ͼ��"),1,1));
	m_pane->Add(new CMFCRibbonButton(ID_OPENRAW, _T("��RAW"),1,1));



	m_pCate = m_wndRibbonBar.AddCategory(_T("��ͼ�˵�"),IDB_WRITESMALL,IDB_WRITELARGE);
	m_pane = m_pCate->AddPanel(_T("���α任"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_GEO_ZOOM,_T("����"),0,10));
	m_pane->Add(new CMFCRibbonButton(ID_GEO_ZOOM_S,_T("��С"),0,-1));
	m_pane->Add(new CMFCRibbonButton(ID_GEO_ZOOM_B,_T("�Ŵ�"),1,-1));
	m_pane->AddSeparator();
	m_pane->Add(new CMFCRibbonButton(ID_GEO_ROTATE,_T("��ת"),-1,9));
	m_pane->Add(new CMFCRibbonButton(ID_GEO_ROTATE_CW90,_T("˳90"),4,-1));
	m_pane->Add(new CMFCRibbonButton(ID_GEO_ROTATE_CCW90,_T("��90"),6,-1));
	m_pane->AddSeparator();
	m_pane->Add(new CMFCRibbonButton(ID_GEO_ROTATE_CW180,_T("˳180"),5,-1));
	m_pane->Add(new CMFCRibbonButton(ID_GEO_ROTATE_CCW180,_T("��180"),7,-1));
	m_pane->AddSeparator();
	m_pane->Add(new CMFCRibbonButton(ID_GEO_FLIPHORIZ,_T("ˮƽ��ת"),2,-1));
	m_pane->Add(new CMFCRibbonButton(ID_GEO_FLIPVERTI,_T("��ֱ��ת"),3,-1));

	m_pane = m_pCate->AddPanel(_T("ֱ��ͼ"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_LINEARENHANCE,_T("��������"),8,13));
	m_pane->Add(new CMFCRibbonButton(ID_HISTOGRAM_EQUAL,_T("ֱ��ͼ����"),9,-1));
	m_pane->Add(new CMFCRibbonButton(ID_HISTOGRAM_SHOW,_T("��ʾֱ��ͼ"),9,-1));

	m_pane = m_pCate->AddPanel(_T("������"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_POINT_INVERT,_T("ͼ�η�ɫ"),0,6));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_MEANFILTER,_T("��ֵ�˲�"),10,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_MEANFILTER,_T("��ֵ�˲�"),11,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_GAUSSSMOOTH,_T("��˹ƽ��"),12,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_GRADSHARP,_T("�ݶ���"),-1,13));
	m_pane = m_pCate->AddPanel(_T("��Ե���"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_POINT_EDGEROBERTS,_T("Robert"),13,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_EDGESOBEL,_T("Sobel"),14,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_EDGEPREWITT,_T("Prewitt"),15,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_EDGELAPLACE,_T("Laplace"),16,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_EDGEKRISCH,_T("Krisch"),17,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_EDGECANNY,_T("Canny"),18,-1));
	m_pane = m_pCate->AddPanel(_T("�״������˲�"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_POINT_LEEFILTER,_T("LEE�˲�"),19,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_SLEEFILTER,_T("��ǿLEE"),20,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_KUANFILTER,_T("KUAN�˲�"),21,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_SKUANFILTER,_T("��ǿKUAN"),22,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_FROSTFILTER,_T("FROST�˲�"),23,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_SIGMAFILTER,_T("SIGMA�˲�"),24,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_MAPFILTER,_T("MAP�˲�"),25,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_EPOSFILTER,_T("EPOS�˲�"),26,-1));
	m_pane->Add(new CMFCRibbonButton(ID_POINT_STATISTICS,_T("ͳ����Ϣ"),27,-1));
	m_pane->Add(new CMFCRibbonButton(ID_SARDISTRANS,_T("б��ת�ؾ�"),7,1));
	m_pane = m_pCate->AddPanel(_T("����"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_IMGPRO_UNDOALL,_T("��������"),-1,20));


	m_pCate = m_wndRibbonBar.AddCategory(_T("RemoteSensing"),IDB_WRITESMALL,IDB_WRITELARGE);
	m_pane = m_pCate->AddPanel(_T("����"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_CLASS_KAVG,_T("K��ֵ����"),-1,2));
	m_pane->Add(new CMFCRibbonButton(ID_ISODATA,_T("ISODATA"),-1,0));

	m_pane = m_pCate->AddPanel(_T("RS"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_KLTRANS,_T("K-L�任"),-1,5));
	m_pane->Add(new CMFCRibbonButton(ID_NDVI,_T("NDVI"),-1,15));
	m_pane->Add(new CMFCRibbonButton(ID_CHANGEMONITOR,_T("�仯���"),-1,4));
	m_pane->Add(new CMFCRibbonButton(ID_HISFUSION,_T("HIS�ں�"),-1,3));
	m_pane->Add(new CMFCRibbonButton(ID_NWEIGHTFUSION,_T("�Ǽ�Ȩ�ں�"),-1,8));
	m_pane->Add(new CMFCRibbonButton(ID_WEIGHTFUSION,_T("��Ȩ�ں�"),-1,13));

	m_pane = m_pCate->AddPanel(_T("ɫ�ʱ任"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_RGB2GRAY,_T("RGB2Gray"),-1,10));
	m_pane->Add(new CMFCRibbonButton(ID_RGB2HIS,_T("RGB2HIS"),-1,11));
	m_pane->Add(new CMFCRibbonButton(ID_HIS2RGB,_T("HIS2RGB"),-1,12));

	m_pane = m_pCate->AddPanel(_T("����ң��"));
	m_pane->SetCenterColumnVert(TRUE);
	m_pane->Add(new CMFCRibbonButton(ID_WAVEDETECT,_T("������"),-1,14));
	m_pane->Add(new CMFCRibbonButton(ID_LIDARDATA,_T("�״�����"),-1,15));

}

void CMainFrame::CreateDocumentColors()
{
	typedef struct
	{
		COLORREF color;
		TCHAR* szName;
	}
	ColorTableEntry;

	int i = 0;
	int nNumColours = 0;

	static ColorTableEntry colorsMain [] =
	{
		{ RGB(255, 255, 255), _T("White, Background 1") },
		{ RGB(0, 0, 0), _T("Black, Text 1") },
		{ RGB(0, 0, 255), _T("Blue, Background 2") },
		{ RGB(31, 73, 125), _T("Dark Blue, Text 2") },
		{ RGB(79, 129, 189), _T("Blue, Accent 1") },
		{ RGB(192, 80, 77), _T("Red, Accent 2") },
		{ RGB(155, 187, 89), _T("Olive Green, Accent 3") },
		{ RGB(128, 100, 162), _T("Purple, Accent 4") },
		{ RGB(75, 172, 198), _T("Aqua, Accent 5") },
		{ RGB(245, 150, 70), _T("Orange, Accent 6") }
	};

	static ColorTableEntry colorsAdditional [] =
	{
		{ RGB(242, 242, 242), _T("White, Background 1, Darker 5%") },
		{ RGB(127, 127, 127), _T("Black, Text 1, Lighter 50%") },
		{ RGB(214, 212, 202), _T("Tan, Background 2, Darker 10%") },
		{ RGB(210, 218, 229), _T("Dark Blue, Text 2, Lighter 80%") },
		{ RGB(217, 228, 240), _T("Blue, Accent 1, Lighter 80%") },
		{ RGB(244, 219, 218), _T("Red, Accent 2, Lighter 80%") },
		{ RGB(234, 241, 221), _T("Olive Green, Accent 3, Lighter 80%")},
		{ RGB(229, 223, 235), _T("Purple, Accent 4, Lighter 80%") },
		{ RGB(216, 237, 242), _T("Aqua, Accent 5, Lighter 80%") },
		{ RGB(255, 234, 218), _T("Orange, Accent 6, Lighter 80%") },
		{ RGB(215, 215, 215), _T("White, Background 1, Darker 15%") },
		{ RGB(89, 89, 89), _T("Black, Text 1, Lighter 35%") },
		{ RGB(177, 176, 167), _T("Tan, Background 2, Darker 25%") },
		{ RGB(161, 180, 201), _T("Dark Blue, Text 2, Lighter 60%") },
		{ RGB(179, 202, 226), _T("Blue, Accent 1, Lighter 60%") },
		{ RGB(233, 184, 182), _T("Red, Accent 2, Lighter 60%") },
		{ RGB(213, 226, 188), _T("Olive Green, Accent 3, Lighter 60%")},
		{ RGB(203, 191, 215), _T("Purple, Accent 4, Lighter 60%") },
		{ RGB(176, 220, 231), _T("Aqua, Accent 5, Lighter 60%") },
		{ RGB(255, 212, 181), _T("Orange, Accent 6, Lighter 60%") },
		{ RGB(190, 190, 190), _T("White, Background 1, Darker 25%") },
		{ RGB(65, 65, 65), _T("Black, Text 1, Lighter 25%") },
		{ RGB(118, 117, 112), _T("Tan, Background 2, Darker 35%") },
		{ RGB(115, 143, 175), _T("Dark Blue, Text 2, Lighter 40%") },
		{ RGB(143, 177, 213), _T("Blue, Accent 1, Lighter 40%") },
		{ RGB(222, 149, 147), _T("Red, Accent 2, Lighter 40%") },
		{ RGB(192, 213, 155), _T("Olive Green, Accent 3, Lighter 40%")},
		{ RGB(177, 160, 197), _T("Purple, Accent 4, Lighter 40%") },
		{ RGB(137, 203, 218), _T("Aqua, Accent 5, Lighter 40%") },
		{ RGB(255, 191, 145), _T("Orange, Accent 6, Lighter 40%") },
		{ RGB(163, 163, 163), _T("White, Background 1, Darker 35%") },
		{ RGB(42, 42, 42), _T("Black, Text 1, Lighter 15%") },
		{ RGB(61, 61, 59), _T("Tan, Background 2, Darker 50%") },
		{ RGB(20, 57, 92), _T("Dark Blue, Text 2, Darker 25%") },
		{ RGB(54, 96, 139), _T("Blue, Accent 1, Darker 25%") },
		{ RGB(149, 63, 60), _T("Red, Accent 2, Darker 25%") },
		{ RGB(114, 139, 71), _T("Olive Green, Accent 3, Darker 25%") },
		{ RGB(97, 76, 119), _T("Purple, Accent 4, Darker 25%") },
		{ RGB(41, 128, 146), _T("Aqua, Accent 5, Darker 25%") },
		{ RGB(190, 112, 59), _T("Orange, Accent 6, Darker 25%") },
		{ RGB(126, 126, 126), _T("White, Background 1, Darker 50%") },
		{ RGB(20, 20, 20), _T("Black, Text 1, Lighter 5%") },
		{ RGB(29, 29, 28), _T("Tan, Background 2, Darker 90%") },
		{ RGB(17, 40, 64), _T("Dark Blue, Text 2, Darker 50%") },
		{ RGB(38, 66, 94), _T("Blue, Accent 1, Darker 50%") },
		{ RGB(100, 44, 43), _T("Red, Accent 2, Darker 50%") },
		{ RGB(77, 93, 49), _T("Olive Green, Accent 3, Darker 50%") },
		{ RGB(67, 53, 81), _T("Purple, Accent 4, Darker 50%") },
		{ RGB(31, 86, 99), _T("Aqua, Accent 5, Darker 50%") },
		{ RGB(126, 77, 42), _T("Orange, Accent 6, Darker 50%") },
	};

	static ColorTableEntry colorsStandard [] =
	{
		{ RGB(200, 15, 18), _T("Dark Red") },
		{ RGB(255, 20, 24), _T("Red") },
		{ RGB(255, 191, 40), _T("Orange") },
		{ RGB(255, 255, 49), _T("Yellow") },
		{ RGB(138, 207, 87), _T("Light Green") },
		{ RGB(0, 175, 84), _T("Green") },
		{ RGB(0, 174, 238), _T("Light Blue") },
		{ RGB(0, 111, 189), _T("Blue") },
		{ RGB(0, 36, 95), _T("Black") },
		{ RGB(114, 50, 157), _T("Purple") },
	};

	m_lstMainColors.RemoveAll();
	nNumColours = sizeof(colorsMain) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstMainColors.AddTail(colorsMain [i].color);
		CMFCRibbonColorButton::SetColorName(colorsMain [i].color, colorsMain [i].szName);
	};

	m_lstAdditionalColors.RemoveAll();
	nNumColours = sizeof(colorsAdditional) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstAdditionalColors.AddTail(colorsAdditional [i].color);
		CMFCRibbonColorButton::SetColorName(colorsAdditional [i].color, colorsAdditional [i].szName);
	};

	m_lstStandardColors.RemoveAll();
	nNumColours = sizeof(colorsStandard) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstStandardColors.AddTail(colorsStandard [i].color);
		CMFCRibbonColorButton::SetColorName(colorsStandard [i].color, colorsStandard [i].szName);
	};
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


//--------------------------Skin-----------------------//
void CMainFrame::OnSkinAero() 
{
	m_nSkinAero = (m_nSkinAero==1)?0:1;
	SkinH_SetAero(m_nSkinAero);	
}

void CMainFrame::OnUpdateSkinAero(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nSkinAero);
}

void CMainFrame::OnSkin01() 
{
	m_nSkin = 0;
	SkinH_Detach();
	SkinH_AttachEx(m_strSkin[m_nSkin],NULL);	
}

void CMainFrame::OnUpdateSkin01(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nSkin == 0 ? 1:0);
}

void CMainFrame::OnSkin02() 
{
	m_nSkin = 1;
	SkinH_Detach();
	SkinH_AttachEx(m_strSkin[m_nSkin],NULL);
}

void CMainFrame::OnUpdateSkin02(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nSkin == 1 ? 1:0);
}

void CMainFrame::OnSkin03() 
{
	m_nSkin = 2;
	SkinH_Detach();
	SkinH_AttachEx(m_strSkin[m_nSkin],NULL);
}

void CMainFrame::OnUpdateSkin03(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nSkin == 2 ? 1:0);
}

void CMainFrame::OnSkin04() 
{
	m_nSkin = 3;
	SkinH_Detach();
	SkinH_AttachEx(m_strSkin[m_nSkin],NULL);
	
}

void CMainFrame::OnUpdateSkin04(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nSkin == 3 ? 1:0);
}

void CMainFrame::OnSkin05() 
{
	m_nSkin = 4;
	SkinH_Detach();
	SkinH_AttachEx(m_strSkin[m_nSkin],NULL);
}

void CMainFrame::OnUpdateSkin05(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nSkin == 4 ? 1:0);
}

void CMainFrame::OnSkin06() 
{
	m_nSkin = 5;
	SkinH_Detach();
	SkinH_AttachEx(m_strSkin[m_nSkin],NULL);
}

void CMainFrame::OnUpdateSkin06(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nSkin == 5 ? 1:0);
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


void CMainFrame::OnBtnViewTestDlg()
{
	// TODO: �ڴ���������������
	CViewTestDlg *dlg = new CViewTestDlg();
	dlg->Create(IDD_VIEWTESTDLG);
	dlg->ShowWindow(SW_SHOWMAXIMIZED);
}
