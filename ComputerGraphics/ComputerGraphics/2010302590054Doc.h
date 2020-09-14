// 2010302590054Doc.h : interface of the CMy2010302590054Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_2010302590054DOC_H__8C63C7F0_50E1_4FBE_98AE_C271A5D97663__INCLUDED_)
#define AFX_2010302590054DOC_H__8C63C7F0_50E1_4FBE_98AE_C271A5D97663__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy2010302590054Doc : public CDocument
{
protected: // create from serialization only
	CMy2010302590054Doc();
	DECLARE_DYNCREATE(CMy2010302590054Doc)

// Attributes
public:
	CPoint group[100];
	int PointNum;
    COLORREF m_crColor;
	int LineWide;
// Operations
public:
	void DDALine(CClientDC *DCPoint);
	void MidpointLine(CClientDC *DCPoint);
	void BLine(CClientDC *DCPoint);
	void BCircle(CClientDC*DCPoint,CPoint p1,CPoint p2);
	void BCircle(CClientDC*DCPoint,CRect *rc,CPoint p1,CPoint p2);
	void PNCircle(CClientDC*DCPoint,CPoint p1,CPoint p2);
    void Bezier(CClientDC*DCPoint,int mode);
	void Bezier_4(CClientDC*pDC,int mode,CPoint p1,CPoint p2,CPoint p3,CPoint p4);
	void BSample(CClientDC*DCPoint,int mode);
	void BSample_4(CClientDC*DCPoint,int mode,CPoint p1,CPoint p2,CPoint p3,CPoint p4);
	void GenerateGraph(CClientDC *DCPoint);
	void DrawGraph(CClientDC *DCPoint);
	void DrawGraph1(CClientDC*DCPoint);
	void TransRotate(CPoint p1,CPoint p2);//xuanzhuan
	void TransZoom(int x,int y,float zoomx,float zoomy);
	void Symmetry(CPoint p1,CPoint p2);//duichengbianhuan
	void SeedFill(CClientDC*DCPoint,CPoint p);
	void EdgeFill(CClientDC*DCPoint);
	void DrawWindow(CClientDC*DCPoint);
	void CohenSutherland(CClientDC*DCPoint,CPoint p1,CPoint p2);
	int encode(int x,int y);
	void PolygonCut(CClientDC*DCPoint);
	void EdgeClipping(int linecode);
	void CircleCut(CClientDC*DCPoint,CPoint p1,CPoint p2);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy2010302590054Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMy2010302590054Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy2010302590054Doc)
	afx_msg void OnGraphColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2010302590054DOC_H__8C63C7F0_50E1_4FBE_98AE_C271A5D97663__INCLUDED_)
