// ImageProcess.h : main header file for the IMAGEPROCESS application
//

#if !defined(AFX_IMAGEPROCESS_H__26277174_C24A_4AEB_8AE4_845FC883F947__INCLUDED_)
#define AFX_IMAGEPROCESS_H__26277174_C24A_4AEB_8AE4_845FC883F947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageProcessApp:
// See ImageProcess.cpp for the implementation of this class
//

class CImageProcessApp : public CWinAppEx
{
public:
	CImageProcessApp();

	UINT  m_nAppLook;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageProcessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImageProcessApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CImageProcessApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPROCESS_H__26277174_C24A_4AEB_8AE4_845FC883F947__INCLUDED_)
