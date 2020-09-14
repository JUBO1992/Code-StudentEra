// 2010302590054.h : main header file for the 2010302590054 application
//

#if !defined(AFX_2010302590054_H__9E011B6B_DA7C_41B0_9BD8_2722F17388DB__INCLUDED_)
#define AFX_2010302590054_H__9E011B6B_DA7C_41B0_9BD8_2722F17388DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "math.h"
/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054App:
// See 2010302590054.cpp for the implementation of this class
//

class CMy2010302590054App : public CWinApp
{
public:
	CMy2010302590054App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy2010302590054App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy2010302590054App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2010302590054_H__9E011B6B_DA7C_41B0_9BD8_2722F17388DB__INCLUDED_)
