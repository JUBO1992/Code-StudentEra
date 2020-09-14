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

// DriveDetectingView.h : CDriveDetectingView ��Ľӿ�
//

#pragma once

class CDriveDetectingView : public CScrollView
{
protected: // �������л�����
	CDriveDetectingView();
	DECLARE_DYNCREATE(CDriveDetectingView)

// ����
public:
	CDriveDetectingDoc* GetDocument() const;
	IplImage* m_ImgWork;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDriveDetectingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCvCallCamera();
	afx_msg void OnCvPlayVideo();
	afx_msg void OnCvCanny();
	afx_msg void OnCvPyrDown();
	afx_msg void OnCvHistogram();
	afx_msg void OnCvConvolution();
	afx_msg void OnCvUndoAll();
	afx_msg void OnCvHoughLine();
	afx_msg void OnCvPersptrans();
	afx_msg void OnCvFaceDetect();
	afx_msg void OnCvSteerwheel();
	afx_msg void OnCvSeatBelt();
	afx_msg void OnCvRgb2gray();
	afx_msg void OnCvInvertColor();
	afx_msg void OnCvOpenImage();
	afx_msg void OnCvSteerwheel2();
	afx_msg void OnCvSeatBelt2();
	afx_msg void OnCvSteerwheel1();
	afx_msg void OnCvEyedet();
	afx_msg void OnCvMouthdet();
	afx_msg void OnCvNosedet();
	afx_msg void OnSetHoughParam();
	afx_msg void OnCvEyedet2();
	afx_msg void OnCvMouthdet2();
	afx_msg void OnCvNosedet2();
};

#ifndef _DEBUG  // DriveDetectingView.cpp �еĵ��԰汾
inline CDriveDetectingDoc* CDriveDetectingView::GetDocument() const
   { return reinterpret_cast<CDriveDetectingDoc*>(m_pDocument); }
#endif

