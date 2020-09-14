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

// DriveDetectingDoc.cpp : CDriveDetectingDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CDriveDetectingDoc ����/����

CDriveDetectingDoc::CDriveDetectingDoc()
{
	// TODO: �ڴ����һ���Թ������
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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDriveDetectingDoc ���л�

void CDriveDetectingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CDriveDetectingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CDriveDetectingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CDriveDetectingDoc ���

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


// CDriveDetectingDoc ����


BOOL CDriveDetectingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
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
	// ���ļ�
	CString filter = "����֧�ָ�ʽ(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2 \
					 |Windows ͼƬ(.BMP)|*.BMP|JPEGͼƬ�ļ�(.JPEG;.JPG;.JPE)|*.jpeg;*.jpg;*.jpe \
					 |��Я����ͼƬ(.PNG;.PBM;.PPM)|*.png;*.pbm;*.ppm|TIFFͼƬ�ļ�(.TIF;.TIFF)|*.tif;*.tiff \
					 |����֧���ļ�(.SR;.RAS;.JP2)|*.sr;*.ras;*.jp2||";
	CFileDialog DlgOpen(TRUE,"BMP",NULL,OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT,filter,NULL);
	if(DlgOpen.DoModal()==IDOK)
	{
		//DlgOpen.GetPathName() ȫ·����
		//GetFileName() �ļ����͸�ʽ
		//GetFileTitle() ֻ���ļ���
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
	// �����ļ�
	CString filter = "����֧�ָ�ʽ(.BMP;.JPEG;.PNG;.TIF...)|*.BMP;*.jpeg;*.jpg;*.jpe;*.png;*.pbm;*.ppm;*.tif;*.tiff;*.sr;*.ras;*.jp2||";
	CFileDialog DlgSave(FALSE,"BMP","*.*",OFN_EXPLORER|OFN_EXTENSIONDIFFERENT|OFN_OVERWRITEPROMPT,filter);
	//	DlgSave.SetDefExt(".BMP");
	if(DlgSave.DoModal()==IDOK)
	{
		//DlgOpen.GetPathName() ȫ·����
		//AfxMessageBox("save:"+DlgSave.GetPathName());
		cvSaveImage(DlgSave.GetPathName(),MyView->m_ImgWork);
// 		SetModifiedFlag(FALSE);
	}
}

BOOL CDriveDetectingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���

	return cvSaveImage(lpszPathName,m_ImgLoad);
// 	return CDocument::OnSaveDocument(lpszPathName);
}
