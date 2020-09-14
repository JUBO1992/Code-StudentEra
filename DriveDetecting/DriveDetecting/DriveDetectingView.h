// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// DriveDetectingView.h : CDriveDetectingView 类的接口
//

#pragma once

class CDriveDetectingView : public CScrollView
{
protected: // 仅从序列化创建
	CDriveDetectingView();
	DECLARE_DYNCREATE(CDriveDetectingView)

// 特性
public:
	CDriveDetectingDoc* GetDocument() const;
	IplImage* m_ImgWork;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDriveDetectingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // DriveDetectingView.cpp 中的调试版本
inline CDriveDetectingDoc* CDriveDetectingView::GetDocument() const
   { return reinterpret_cast<CDriveDetectingDoc*>(m_pDocument); }
#endif

