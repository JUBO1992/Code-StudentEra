// 2010302590054View.h : interface of the CMy2010302590054View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_2010302590054VIEW_H__6211EE45_67D7_470A_A494_AB948AF83308__INCLUDED_)
#define AFX_2010302590054VIEW_H__6211EE45_67D7_470A_A494_AB948AF83308__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Include the OpenGL headers
#include "gl\gl.h"
#include "gl\glu.h"
#include "glaux.h"

class CMy2010302590054View : public CScrollView
{
protected: // create from serialization only
	int MenuID,PressNum,SaveNumber;
	CPoint m_PointOrigin,m_PointOld,m_PointOld1;
	HCURSOR m_hCross;
    CString m_strLine;
	CFont m_font;
	COLORREF m_color;

	int m_flag;
	BOOL m_bPlay;
	int x;
	int y;
	int m_nSpeedX;
	int m_nSpeedY;
	void DrawSphere(CDC *pDC, int x, int y);
	void DrawGlider(CDC *pDC, int x, int y);
	void Drawpillar(CDC *pDC);
	void DrawBase(CDC *pDC);

	CMy2010302590054View();
	DECLARE_DYNCREATE(CMy2010302590054View)

// Attributes
public:
	CMy2010302590054Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy2010302590054View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CBrush m_Brush;
	virtual ~CMy2010302590054View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy2010302590054View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawDdaline();
	afx_msg void OnDrawBcircle();
	afx_msg void OnCurveBezier();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDrawPncircle();
	afx_msg void OnDrawChar();
	afx_msg void OnTransMove();
	afx_msg void OnTransSymmetry();
	afx_msg void OnFillSeed();
	afx_msg void OnDrawPolygon();
	afx_msg void OnCutCs();
	afx_msg void OnFillEdge();
	afx_msg void OnFillScanline();
	afx_msg void OnCutPolygon();
	afx_msg void OnCutCircle();
	afx_msg void OnDrawMidline();
	afx_msg void OnDrawBline();
	afx_msg void OnGlobeLight();
	afx_msg void OnLinewide();
	afx_msg void OnTransRotate();
	afx_msg void OnTransZoom();
	afx_msg void OnCurveBsample();
	afx_msg void OnCubespin();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDrawChar2();
	afx_msg void OnFill();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void On3dspin();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStart();
	afx_msg void OnRestart();
	afx_msg void OnStop();
	afx_msg void OnEnd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
// The following was added
	virtual BOOL SetupPixelFormat( void );
	virtual BOOL SetupViewport( int cx, int cy );
	virtual BOOL SetupViewingFrustum( GLdouble aspect_ratio );
	virtual BOOL SetupViewingTransform( void );
	virtual BOOL PreRenderScene( void ) { return TRUE; }
	virtual void RenderStockScene( void );
	virtual BOOL RenderScene( void );

private:
	BOOL InitializeOpenGL();
	void SetError( int e );

	HGLRC	m_hRC;
	CDC*	m_pDC;
	
	static const char* const _ErrorStrings[];
	const char* m_ErrorString;
};

#ifndef _DEBUG  // debug version in 2010302590054View.cpp
inline CMy2010302590054Doc* CMy2010302590054View::GetDocument()
   { return (CMy2010302590054Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2010302590054VIEW_H__6211EE45_67D7_470A_A494_AB948AF83308__INCLUDED_)
