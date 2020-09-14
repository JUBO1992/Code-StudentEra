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
	int nBands;//读取波段数
	int nXsize;
	int nYsize;
	int BandChoiceTest;//定义显示方式 灰度、彩色

	//GDALDataset *poDadaset;//定义数据集
	GDALRasterBand **poBand;//定义波段指针数组
	int BandChoice;//灰度显示方式下拉框选择索引
	int BandChoiceR;//彩色显示方式下拉框选择索引
	int BandChoiceG;
	int BandChoiceB;
// Operations
public:
	//该函数用于创建位图文件信息头，flag为标记，1为灰度，2为真彩色，3为假彩色
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
