// ImageProcessDoc.cpp : implementation of the CImageProcessDoc class
//

#include "stdafx.h"
#include "ImageProcess.h"

#include "ImageProcessDoc.h"
#include "ImageInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageProcessDoc

IMPLEMENT_DYNCREATE(CImageProcessDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessDoc, CDocument)
	//{{AFX_MSG_MAP(CImageProcessDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageProcessDoc construction/destruction

CImageProcessDoc::CImageProcessDoc()
{
	// TODO: add one-time construction code here
	hDB = NULL;
	hDBOld = NULL;
	nXsize = nYsize = 500;//��ʼ��ֵ��Ϊ���ڳ�ֵ
	BandChoiceTest = 0;
	nBands = 0;
	poBand=NULL;
}

CImageProcessDoc::~CImageProcessDoc()
{
	if(hDB!=NULL)
	{
		::GlobalUnlock((HGLOBAL) hDB);
		::GlobalFree((HGLOBAL)hDB);
	}
	if(hDBOld != NULL)
	{
		::GlobalUnlock((HGLOBAL) hDBOld);
		::GlobalFree((HGLOBAL) hDBOld);
	}
	delete []poBand;
	poBand  = NULL;
}

BOOL CImageProcessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImageProcessDoc serialization

void CImageProcessDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessDoc diagnostics

#ifdef _DEBUG
void CImageProcessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageProcessDoc commands

void CImageProcessDoc::CreateBitmapInfo(BITMAPINFO *pBitmapInfo,int Width,int Height,int flag)
{
/*
	if(flag==1||flag==3)
    	pBitmapInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(256)]; 	
	else if(flag==2)
		pBitmapInfo = (BITMAPINFO*)new char[40];*/
	pBitmapInfo->bmiHeader.biClrUsed = 0;
	if(flag==1||flag==3)
    	pBitmapInfo->bmiHeader.biBitCount = 8;
	else if(flag==2)
		pBitmapInfo->bmiHeader.biBitCount = 24;
	pBitmapInfo->bmiHeader.biClrImportant = 0;
	pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	pBitmapInfo->bmiHeader.biWidth = Width;
	pBitmapInfo->bmiHeader.biHeight = Height;
	pBitmapInfo->bmiHeader.biPlanes = 1;
	pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	if(flag==1||flag==3)
		pBitmapInfo->bmiHeader.biSizeImage = (Width*8+31)/32*4*Height; 
	else if(flag==2)
    	pBitmapInfo->bmiHeader.biSizeImage = (Width*24+31)/32*4*Height; 
	pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;	
	pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	//Ϊ��ɫ��ֵ
	int i;
	if(flag==1)
		for ( i=0; i<256; i++)
		{
			pBitmapInfo->bmiColors[i].rgbBlue = (unsigned char)i;
			pBitmapInfo->bmiColors[i].rgbGreen = (unsigned char)i;
			pBitmapInfo->bmiColors[i].rgbRed = (unsigned char)i;
			pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	else if(flag==3)
		for ( i=0; i<256; i++)
		{
			pBitmapInfo->bmiColors[i].rgbBlue = i*2;
			pBitmapInfo->bmiColors[i].rgbGreen = (int)fabs((float)i*2-128);
			pBitmapInfo->bmiColors[i].rgbRed = (int)fabs((float)255-i*2);	
			pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
}

BOOL CImageProcessDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))//���ļ�ʧ��ʱ���ô˺���
	{
		AfxMessageBox("���ļ�ʧ��");
		return FALSE;
	}
	// TODO: Add your specialized creation code here

	CFile file;
	CFileException fe;
	if(!file.Open(lpszPathName,CFile::modeRead|CFile::shareDenyWrite,&fe))
	{
		AfxMessageBox("���ļ�ʧ��");
		ReportSaveLoadException(lpszPathName,&fe,
			FALSE,AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}
	
	GDALAllRegister();//ע������
	GDALDataset *poDadaset;//�������ݼ�
    poDadaset = (GDALDataset *)GDALOpen(lpszPathName,GA_ReadOnly);
	
	if(poDadaset == NULL)
	{
		AfxMessageBox("Ӱ���ʧ�ܣ�",MB_OK);
		return 0;
	}
	if(poBand!=NULL)
	{
		delete []poBand;
		poBand = NULL;
	}
	//��ȡӰ����Ϣ
	nBands = poDadaset->GetRasterCount();//��ȡ��������
	//GDALRasterBand **poBand;//���岨��ָ������
	poBand = new GDALRasterBand *[nBands];

	if(poBand == NULL)
	{
		AfxMessageBox("�������������ݼ�ʧ�ܣ�",MB_ICONWARNING);
		return 0;
	}
	int i;
	for(i=0;i<nBands;i++)
	{
		poBand[i] = poDadaset->GetRasterBand(i+1);
		
		if(poBand[i] == NULL)
		{
			AfxMessageBox("����i�������ݼ�ʧ�ܣ�",MB_ICONWARNING);
			return 0;
		}
	}

	CImageInfo ImgInfo;
	ImgInfo.m_MinBand = 1;
	ImgInfo.m_MaxBand = nBands;

	if(ImgInfo.DoModal() != IDOK)
	{
		//���ͷ��ڴ���return
		delete ImgInfo;
		delete poDadaset;//�ͷ��ڴ���Դ
		return 0;
	}

	if(hDB!=NULL)
	{
		::GlobalUnlock((HGLOBAL)hDB);
		::GlobalFree((HGLOBAL)hDB);
	}
	if(ImgInfo.nChoiceShow == 0 || ImgInfo.nChoiceShow == 2)//��ʾģʽ������Ϊ�ҶȻ�ٲ�ɫ
	{
		BandChoiceTest = ImgInfo.nChoiceShow+1;
		
		BandChoice = ImgInfo.m_BandChoice;
		while (BandChoice > (nBands-1))
		{
			CString warningBand;
			warningBand.Format("%s%d%s","��ѡӰ�����󲨶���Ϊ�� ", nBands, "  ������ѡ��");
			AfxMessageBox(warningBand);
			if(ImgInfo.DoModal()!=IDOK)
				return 0;
			BandChoice = ImgInfo.m_BandChoice;
		}
		if(poBand[BandChoice] == NULL)
			return 0;
		nXsize = poBand[BandChoice]->GetXSize();
		nYsize = poBand[BandChoice]->GetYSize();
	}
	else if(ImgInfo.nChoiceShow == 1)//��ʾģʽ������Ϊ��ɫ 
	{
		BandChoiceTest = 2;
		
		BandChoiceR = ImgInfo.m_BandChoiceR;
		BandChoiceG = ImgInfo.m_BandChoiceG;
		BandChoiceB = ImgInfo.m_BandChoiceB;
		
		while ((BandChoiceB>(nBands-1))||(BandChoiceG>(nBands-1))||(BandChoiceR > (nBands-1)))
		{
			CString warningBand;
			warningBand.Format("%s%d%s","��ѡӰ�����󲨶���Ϊ�� ", nBands, "  ������ѡ��");
			//	AfxMessageBox("��ѡ���γ���Ӱ�����󲨶�����������ѡ��");	
			AfxMessageBox(warningBand);
			if(ImgInfo.DoModal()!=IDOK)
				return 0;
			BandChoiceR = ImgInfo.m_BandChoiceR;
			BandChoiceG = ImgInfo.m_BandChoiceG;
			BandChoiceB = ImgInfo.m_BandChoiceB;		
		}
		nXsize = poBand[BandChoiceR]->GetXSize();
		nYsize = poBand[BandChoiceR]->GetYSize();
	}

	switch(poBand[0]->GetRasterDataType())
	{
	case GDT_Byte:
		GetDIB(BYTE(0));break;
	case GDT_UInt16:
		GetDIB(WORD(0));break;
	case GDT_Int16:
		GetDIB(short(0));break;
	case GDT_UInt32:
		GetDIB(DWORD(0));break;
	case GDT_Int32:
		GetDIB(int(0));break;
	case GDT_Float32:
		GetDIB(float(0));break;
	case  GDT_Float64:
		GetDIB(double(0));break;
	default:
		break;
	}
	delete ImgInfo;
	delete poDadaset;//�ͷ��ڴ���Դ
	UpdateAllViews(FALSE);
	return TRUE;
}

BOOL CImageProcessDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	CFile file;
	file.Open(lpszPathName,CFile::modeCreate|CFile::modeWrite);
 	if(SaveDIB(hDB,file))
	{
		SetModifiedFlag(FALSE);
		return TRUE;
	}
	else
		return FALSE;
	//return CDocument::OnSaveDocument(lpszPathName);
}

template<class T>
void CImageProcessDoc::GetDIB(T)
{
	int i,j;
	double dMin,dMax;
	double dMinR,dMaxR;double dMinG,dMaxG;double dMinB,dMaxB;
	if(BandChoiceTest == 1||BandChoiceTest == 3)//�򿪻Ҷ�Ӱ���ٲ�ɫ��ʾ
	{
		
		//���仺��ռ�
		T *poBandBlock_Gray = (T *)CPLMalloc(sizeof(T)*(nXsize*nYsize));
		//һ���Զ�ȡRasterIO
		poBand[BandChoice]->RasterIO(GF_Read,0,0,nXsize,nYsize,
			poBandBlock_Gray,nXsize,nYsize,poBand[BandChoice]->GetRasterDataType(),0,0);
		
		poBand[BandChoice]->GetStatistics(FALSE,TRUE,&dMin,&dMax,NULL,NULL);
		//����ת��Ϊλͼ
		BITMAPINFO *pBitmapInfo=(BITMAPINFO*)new char[40+256*4];
		CreateBitmapInfo(pBitmapInfo,nXsize,nYsize,BandChoiceTest);
		LONG LineBytes = (nXsize*8 + 31)/32*4;
		hDB=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*nYsize);
		LPSTR pDB=(LPSTR)LocalLock(hDB);
		memcpy(pDB,pBitmapInfo,40+256*4);
		LPBYTE pData = (LPBYTE)pDB+40+256*4;
		//Ϊ�����ظ�ֵ
		for ( i=0; i<nYsize; i++)
		{
			for ( j=0; j<nXsize; j++)
			{
				//pData[(nYsize-i-1)*LineBytes + j] = poBandBlock_Gray[i*nXsize + j];
				pData[(nYsize-i-1)*LineBytes + j] = (BYTE)((poBandBlock_Gray[i*nXsize+j]-dMin)*255/(dMax-dMin)+0.5);
			}
		}
		::LocalUnlock((HGLOBAL)hDB);
		CPLFree(poBandBlock_Gray);//�ͷ��ڴ�
	}
	
	if(BandChoiceTest == 2)//�򿪲�ɫӰ��
	{
		
		//���仺�����ռ�
		T *poBandBlock_Red = (T*)CPLMalloc(sizeof(T)*(nXsize*nYsize));	
		T *poBandBlock_Green = (T*)CPLMalloc(sizeof(T)*(nXsize*nYsize));
		T *poBandBlock_Blue = (T*)CPLMalloc(sizeof(T)*(nXsize*nYsize));
		
		BeginWaitCursor();
		//һ���Զ�ȡ-----���RasterIO�������������壺��ȡ��ΧΪ[0,0]~[0+nXsize,0+nYsize]
		poBand[BandChoiceR]->RasterIO(GF_Read, 0, 0, nXsize, 
			nYsize, poBandBlock_Red, nXsize, nYsize, poBand[BandChoiceR]->GetRasterDataType(), 0, 0);
		poBand[BandChoiceG]->RasterIO(GF_Read, 0, 0, nXsize, 
			nYsize, poBandBlock_Green, nXsize, nYsize, poBand[BandChoiceG]->GetRasterDataType(), 0, 0);
		poBand[BandChoiceB]->RasterIO(GF_Read, 0, 0, nXsize, 
			nYsize, poBandBlock_Blue, nXsize, nYsize, poBand[BandChoiceB]->GetRasterDataType(), 0, 0);
		EndWaitCursor();
		
		poBand[BandChoiceR]->GetStatistics(FALSE,TRUE,&dMinR,&dMaxR,NULL,NULL);
		poBand[BandChoiceG]->GetStatistics(FALSE,TRUE,&dMinG,&dMaxG,NULL,NULL);
		poBand[BandChoiceB]->GetStatistics(FALSE,TRUE,&dMinB,&dMaxB,NULL,NULL);
		//����ת��Ϊλͼ
		BITMAPINFO *pBitmapInfo=(BITMAPINFO*)new char[40];
		CreateBitmapInfo(pBitmapInfo,nXsize,nYsize,BandChoiceTest);
		LONG LineBytes = (nXsize*24 + 31)/32*4;
		hDB=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*nYsize);
		LPSTR pDB=(LPSTR)LocalLock(hDB);
		memcpy(pDB,pBitmapInfo,40);
		LPBYTE pData = (LPBYTE)pDB+40;
		//Ϊ�����ظ�ֵ
		int j2 ;
		for ( i=0; i<nYsize; i++)
		{
			for ( j=0, j2=0; j<nXsize, j2<3*nXsize; j++, j2+=3)
			{
				//pData[(nYsize-i-1)*LineBytes + j2+0] = poBandBlock_Blue[i*nXsize + j];
				//pData[(nYsize-i-1)*LineBytes + j2+1] = poBandBlock_Green[i*nXsize + j];
				//pData[(nYsize-i-1)*LineBytes + j2+2] = poBandBlock_Red[i*nXsize + j];
				pData[(nYsize-i-1)*LineBytes + j2+0] = (BYTE)((poBandBlock_Blue[i*nXsize+j]-dMinB)*255/(dMaxB-dMinB)+0.5);//b
				pData[(nYsize-i-1)*LineBytes + j2+1] = (BYTE)((poBandBlock_Green[i*nXsize+j]-dMinG)*255/(dMaxB-dMinG)+0.5);//g
				pData[(nYsize-i-1)*LineBytes + j2+2] = (BYTE)((poBandBlock_Red[i*nXsize+j]-dMinR)*255/(dMaxB-dMinR)+0.5);//r
			}
		}
		::LocalUnlock((HGLOBAL)hDB);
		CPLFree(poBandBlock_Red);//�ͷ��ڴ�
		CPLFree(poBandBlock_Green);//�ͷ��ڴ�
		CPLFree(poBandBlock_Blue);//�ͷ��ڴ�
	}	
}