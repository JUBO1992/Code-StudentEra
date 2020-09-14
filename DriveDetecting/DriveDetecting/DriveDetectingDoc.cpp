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

// DriveDetectingDoc.cpp : CDriveDetectingDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DriveDetecting.h"
#endif

#include "MainFrm.h"
#include "DriveDetectingDoc.h"
#include "DriveDetectingView.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDriveDetectingView *MyView;
// CDriveDetectingDoc

IMPLEMENT_DYNCREATE(CDriveDetectingDoc, CDocument)

BEGIN_MESSAGE_MAP(CDriveDetectingDoc, CDocument)
END_MESSAGE_MAP()


// CDriveDetectingDoc 构造/析构

CDriveDetectingDoc::CDriveDetectingDoc()
{
	// TODO: 在此添加一次性构造代码
	m_ImgLoad = NULL;
	m_OrgImg = NULL;
	m_ImgLoadGray = NULL;
}

CDriveDetectingDoc::~CDriveDetectingDoc()
{
	cvReleaseImage(&m_ImgLoad);
	cvReleaseImage(&m_OrgImg);
	cvReleaseImage(&m_ImgLoadGray);
}

BOOL CDriveDetectingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CDriveDetectingDoc 序列化

void CDriveDetectingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CDriveDetectingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CDriveDetectingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CDriveDetectingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDriveDetectingDoc 诊断

#ifdef _DEBUG
void CDriveDetectingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDriveDetectingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDriveDetectingDoc 命令


BOOL CDriveDetectingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	m_ImgLoad = cvLoadImage(lpszPathName);
	m_OrgImg = cvCloneImage(m_ImgLoad);
	m_ImgLoadGray = cvLoadImage(lpszPathName,CV_LOAD_IMAGE_GRAYSCALE);

	IplImage* tempImg = cvCreateImage(cvGetSize(m_ImgLoadGray),8,3);
	cvCvtColor(m_ImgLoadGray,tempImg,CV_GRAY2RGB);
	cvReleaseImage(&m_ImgLoadGray);
	m_ImgLoadGray = cvCloneImage(tempImg);
	cvReleaseImage(&tempImg);
// 	MyView = (CDriveDetectingView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
// 	MyView->m_ImgWork = cvCloneImage(m_ImgLoad);
// 	cvNamedWindow("Test",CV_WINDOW_AUTOSIZE);
// 	cvShowImage("Test",m_ImgLoad);
	return TRUE;
}

void OnFileOpen() 
{
	// 打开文件
	CString filter = "所有支持格式(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2 \
					 |Windows 图片(.BMP)|*.BMP|JPEG图片文件(.JPEG;.JPG;.JPE)|*.jpeg;*.jpg;*.jpe \
					 |便携网络图片(.PNG;.PBM;.PPM)|*.png;*.pbm;*.ppm|TIFF图片文件(.TIF;.TIFF)|*.tif;*.tiff \
					 |其他支持文件(.SR;.RAS;.JP2)|*.sr;*.ras;*.jp2||";
	CFileDialog DlgOpen(TRUE,"BMP",NULL,OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT,filter,NULL);
	if(DlgOpen.DoModal()==IDOK)
	{
		//DlgOpen.GetPathName() 全路径名
		//GetFileName() 文件名和格式
		//GetFileTitle() 只有文件名
		//SetTitle(DlgOpen.GetFileName());
		//SetPathName(DlgOpen.GetFileName());
		IplImage* m_ImgLoad = cvLoadImage(DlgOpen.GetPathName(),CV_LOAD_IMAGE_COLOR);
		IplImage* m_ImgLoadGray = cvLoadImage(DlgOpen.GetPathName(),CV_LOAD_IMAGE_GRAYSCALE);
		IplImage* tempImg = cvCreateImage(cvGetSize(m_ImgLoadGray),8,3);
		cvCvtColor(m_ImgLoadGray,tempImg,CV_GRAY2RGB);
		cvReleaseImage(&m_ImgLoadGray);
		m_ImgLoadGray = cvCloneImage(tempImg);
		cvReleaseImage(&tempImg);

		MyView = (CDriveDetectingView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
		MyView->m_ImgWork = cvCloneImage(m_ImgLoad);
		MyView->Invalidate();
	}
}

void OnFileSave() 
{
	// 保存文件
	CString filter = "所有支持格式(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2||";
	CFileDialog DlgSave(FALSE,"BMP","*.*",OFN_EXPLORER|OFN_EXTENSIONDIFFERENT|OFN_OVERWRITEPROMPT,filter);
	//	DlgSave.SetDefExt(".BMP");
	if(DlgSave.DoModal()==IDOK)
	{
		//DlgOpen.GetPathName() 全路径名
		//AfxMessageBox("save:"+DlgSave.GetPathName());
		cvSaveImage(DlgSave.GetPathName(),MyView->m_ImgWork);
// 		SetModifiedFlag(FALSE);
	}
}

BOOL CDriveDetectingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类

	return cvSaveImage(lpszPathName,m_ImgLoad);
// 	return CDocument::OnSaveDocument(lpszPathName);
}
