// ImageProcessDoc.h : interface of the CImageProcessDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPROCESSDOC_H__0F5B3B5E_E75A_4B75_9D59_E56F28EBAC88__INCLUDED_)
#define AFX_IMAGEPROCESSDOC_H__0F5B3B5E_E75A_4B75_9D59_E56F28EBAC88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImageProcessDoc : public CDocument
{
protected: // create from serialization only
//	CImageProcessDoc();
	DECLARE_DYNCREATE(CImageProcessDoc)

// Attributes
public:
	CImageProcessDoc();
	HDIB hDB,hDBOld;
	int nBands;//��ȡ������
	int nXsize;
	int nYsize;
	int BandChoiceTest;//������ʾ��ʽ �Ҷȡ���ɫ

	//GDALDataset *poDadaset;//�������ݼ�
	GDALRasterBand **poBand;//���岨��ָ������
	int BandChoice;//�Ҷ���ʾ��ʽ������ѡ������
	int BandChoiceR;//��ɫ��ʾ��ʽ������ѡ������
	int BandChoiceG;
	int BandChoiceB;
// Operations
public:
	//�ú������ڴ���λͼ�ļ���Ϣͷ��flagΪ��ǣ�1Ϊ�Ҷȣ�2Ϊ���ɫ��3Ϊ�ٲ�ɫ
	void CreateBitmapInfo(BITMAPINFO *pBitMapInfo,int Width,int Height,int flag);
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageProcessDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	template<class T>
	void GetDIB(T);
	virtual ~CImageProcessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageProcessDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPROCESSDOC_H__0F5B3B5E_E75A_4B75_9D59_E56F28EBAC88__INCLUDED_)
