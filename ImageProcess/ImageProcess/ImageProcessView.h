// ImageProcessView.h : interface of the CImageProcessView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPROCESSVIEW_H__0D6AB73B_969E_4818_AA10_78A053FE381E__INCLUDED_)
#define AFX_IMAGEPROCESSVIEW_H__0D6AB73B_969E_4818_AA10_78A053FE381E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImageProcessView : public CScrollView
{
protected: // create from serialization only
	CImageProcessView();
	DECLARE_DYNCREATE(CImageProcessView)

// Attributes
public:
	CImageProcessDoc* GetDocument();

// Operations
public:

	COLORREF m_bgcolor;
	float *Intensity,*Hue,*Saturation;//IHS

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageProcessView)
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
	virtual ~CImageProcessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageProcessView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnOpenimage();
	afx_msg void OnClassKavg();
	afx_msg void OnWavedetect();
	afx_msg void OnChangemonitor();
	afx_msg void OnLidardata();
	afx_msg void OnIsodata();
	afx_msg void OnKltrans();
	afx_msg void OnNdvi();
	afx_msg void OnRgb2gray();
	afx_msg void OnRgb2his();
	afx_msg void OnHis2rgb();
	afx_msg void OnHisfusion();
	afx_msg void OnNweightfusion();
	afx_msg void OnGeoZoom();
	afx_msg void OnGeoRotate();
	afx_msg void OnGeoZoomS();
	afx_msg void OnGeoZoomB();
	afx_msg void OnGeoRotateCw90();
	afx_msg void OnGeoRotateCcw90();
	afx_msg void OnGeoRotateCw180();
	afx_msg void OnGeoRotateCcw180();
	afx_msg void OnGeoFliphoriz();
	afx_msg void OnGeoFlipverti();
	afx_msg void OnWeightfusion();
	afx_msg void OnLinearenhance();
	afx_msg void OnHistogramEqual();
	afx_msg void OnHistogramShow();
	afx_msg void OnPointInvert();
	afx_msg void OnPointMeanfilter();
	afx_msg void OnPointMedianfilter();
	afx_msg void OnPointGausssmooth();
	afx_msg void OnPointGradsharp();
	afx_msg void OnPointEdgeroberts();
	afx_msg void OnPointEdgesobel();
	afx_msg void OnPointEdgeprewitt();
	afx_msg void OnPointEdgelaplace();
	afx_msg void OnOpenraw();
	afx_msg void OnPointLeefilter();
	afx_msg void OnPointKuanfilter();
	afx_msg void OnPointFrostfilter();
	afx_msg void OnSardistrans();
	afx_msg void OnPointSigmafilter();
	afx_msg void OnPointStatistics();
	afx_msg void OnPointSleefilter();
	afx_msg void OnPointSkuanfilter();
	afx_msg void OnPointMapfilter();
	afx_msg void OnPointEposfilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonSetColor();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnImgproUndoall();
};

#ifndef _DEBUG  // debug version in ImageProcessView.cpp
inline CImageProcessDoc* CImageProcessView::GetDocument()
   { return (CImageProcessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPROCESSVIEW_H__0D6AB73B_969E_4818_AA10_78A053FE381E__INCLUDED_)
