// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F5C5A24F_8399_457A_9FB4_DE765B532FDB__INCLUDED_)
#define AFX_MAINFRM_H__F5C5A24F_8399_457A_9FB4_DE765B532FDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

	//Skin
	int        m_nSkin;
	int        m_nSkinAero;
	CString    m_strSkin[6];
// Attributes
public:
	void InitMainButton(CMFCRibbonApplicationButton *p_MainButton);
	void InitTabButton(CMFCToolBarImages *p_TabButton);
	void InitCategory();
	CList<COLORREF,COLORREF> m_lstMainColors;
	CList<COLORREF,COLORREF> m_lstAdditionalColors;
	CList<COLORREF,COLORREF> m_lstStandardColors;
	void CreateDocumentColors();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
// 	CStatusBar  m_wndStatusBar;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;

public:
	CMFCRibbonBar* GetRibbonBar() {return &m_wndRibbonBar;}
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSkinAero();
	afx_msg void OnUpdateSkinAero(CCmdUI* pCmdUI);
	afx_msg void OnSkin01();
	afx_msg void OnUpdateSkin01(CCmdUI* pCmdUI);
	afx_msg void OnSkin02();
	afx_msg void OnUpdateSkin02(CCmdUI* pCmdUI);
	afx_msg void OnSkin03();
	afx_msg void OnUpdateSkin03(CCmdUI* pCmdUI);
	afx_msg void OnSkin04();
	afx_msg void OnUpdateSkin04(CCmdUI* pCmdUI);
	afx_msg void OnSkin05();
	afx_msg void OnUpdateSkin05(CCmdUI* pCmdUI);
	afx_msg void OnSkin06();
	afx_msg void OnUpdateSkin06(CCmdUI* pCmdUI);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnViewTestDlg();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F5C5A24F_8399_457A_9FB4_DE765B532FDB__INCLUDED_)
