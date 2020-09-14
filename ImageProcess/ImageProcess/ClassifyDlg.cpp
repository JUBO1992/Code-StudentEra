// ClassifyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "ClassifyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassifyDlg dialog


CClassifyDlg::CClassifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClassifyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClassifyDlg)
	m_Category = 5;
	m_Inputpath = _T("");
	m_Outputpath = _T("");
	m_Interation = 8;
	//}}AFX_DATA_INIT
	HDB=NULL;
}


void CClassifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClassifyDlg)
	DDX_Text(pDX, IDC_CATEGORY, m_Category);
	DDV_MinMaxInt(pDX, m_Category, 2, 15);
	DDX_Text(pDX, IDC_INPUTPATH, m_Inputpath);
	DDX_Text(pDX, IDC_OUTPUTPATH, m_Outputpath);
	DDX_Text(pDX, IDC_INTERATION, m_Interation);
	DDV_MinMaxInt(pDX, m_Interation, 1, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClassifyDlg, CDialog)
	//{{AFX_MSG_MAP(CClassifyDlg)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, OnButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, OnButtonOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassifyDlg message handlers

BOOL CClassifyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CClassifyDlg::OnButtonInput() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<8;i++)//�ÿ�
	{
		poBandBlock[i]=NULL;
	}

	static char BASED_CODE filetype[]="�����ļ�(*.*)|*.*|TIF Files(*.TIF;*.TIFF)|*.tif;*.tiff|BMP Files(*.BMP)|*.bmp|JPG Files(*.JPG;*.JPEG;*.JPE)|*.jpg;*.jpeg;*.jpe|IMG Files(*.img)|*.img||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
    	m_Inputpath = dlg.GetPathName();
	else
		return ;

	GDALDataset *poDadaset;
	GDALAllRegister();//ע������
    poDadaset = (GDALDataset *)GDALOpen(m_Inputpath,GA_ReadOnly);
	
	if(poDadaset == NULL)
	{
		AfxMessageBox("Ӱ���ʧ�ܣ�",MB_OK);
		return;
	}
	//��ȡӰ����Ϣ
	nBands = poDadaset->GetRasterCount();//��ȡ��������
	GDALRasterBand **poBand;//���岨��ָ������
	poBand = new GDALRasterBand *[nBands];
	
	if(poBand == NULL)
	{
		AfxMessageBox("�������������ݼ�ʧ�ܣ�",MB_ICONWARNING);
		return;
	}
	
	for(i=0;i<nBands;i++)
	{
		poBand[i] = poDadaset->GetRasterBand(i+1);
		if(poBand[i] == NULL)
		{
			AfxMessageBox("����i�������ݼ�ʧ�ܣ�",MB_ICONWARNING);
			return;
		}
	}

	nXsize = poBand[0]->GetXSize();
	nYsize = poBand[0]->GetYSize();
	BeginWaitCursor();
	for(i =0 ;i<nBands; i++)
	{
	//���仺��ռ�
	poBandBlock[i] = (BYTE *)CPLMalloc(sizeof(BYTE)*(nXsize*nYsize));
	//һ���Զ�ȡRasterIO
	poBand[i]->RasterIO(GF_Read,0,0,nXsize,nYsize,
		poBandBlock[i],nXsize,nYsize,poBand[i]->GetRasterDataType(),0,0);
	}
	EndWaitCursor();
	UpdateData(FALSE);
}

void CClassifyDlg::OnButtonOutput() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|TIF Files(*.TIF;*.TIFF)|*.tif;*.tiff|JPG Files(*.JPG;*.JPEG;*.JPE)|*.jpg;*.jpeg;*.jpe|�����ļ�(*.*)|*.*||";
	CFileDialog dlg(FALSE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
    	m_Outputpath = dlg.GetPathName();
	else
		return ;

	UpdateData(FALSE);
}

int CClassifyDlg::Minimum(int *d)
{
	int i=0,j=0,n;
	n=d[0];
	for(i=0;i<m_Category;i++)
		if(n>d[i])
		{
			n=d[i];
	     	j=i;
		}
	return j;
}

BOOL CClassifyDlg::Compare(double (*c1)[8],double (*c2)[8],int Category)
{
	int i,j;
	for (i=0;i<Category;i++)
	{
		for (j=0;j<8;j++)
		{
			if(((int)c1[i][j]) != ((int)c2[i][j]))
				return 0;
		}
	}
	return 1;
}

void CClassifyDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_Inputpath=="")
	{
		AfxMessageBox("������Ӱ��");
		return;
	}
	memset(Num,0,sizeof(Num));
//	long (*Center1)[8]=new long [m_Category][8];
//	long (*Center2)[8]=new long [m_Category][8];
	double (*Center1)[8]=new double [m_Category][8];
	double (*Center2)[8]=new double [m_Category][8];
	memset(Center1,0,sizeof(Center1));//��ʼ��
	memset(Center2,0,sizeof(Center2));
	int *d=new int [m_Category];
	int sum=0;//�������
//	double sum =0;

	int i,j,k,l;

/*
	for(j=0,k=0;j<m_Category;j++,k++)//��ʼ����������
	{
		for(i=0;i<nBands;i++)
		{
			while(poBandBlock[0][k]==0||poBandBlock[0][k]==255)
			{
				k++;
			}
     		Center1[j][i] = poBandBlock[i][k];
			Center2[j][i] = 0;
		}

	}*/


	for(j=0,k=0;j<m_Category;j++,k++)//��ʼ����������
	{
		for(i=0;i<nBands;i++)
		{
			Center1[j][i] = poBandBlock[i][k*1000];
			Center2[j][i] = 0;
		}	
	}

	int nIndex = 0;//�����������
	BeginWaitCursor();
	while(nIndex<m_Interation)
	{
		for(k=0;k<nXsize*nYsize;k++)
		{
			for(j=0;j<m_Category;j++)
			{
				for(i=0;i<nBands;i++)
					sum+=(Center1[j][i]-poBandBlock[i][k])*(Center1[j][i]-poBandBlock[i][k]);
				d[j]=sum;
				sum = 0;
			}
			for(i=0;i<nBands;i++)
			{
				Center2[Minimum(d)][i]+=poBandBlock[i][k];
				if(i==0)Num[Minimum(d)]++;
			}
		}		
		for(j=0;j<m_Category;j++)
		{
			for(i=0;i<nBands;i++)
			{
				if(Num[j]!=0)
				{
			    	Center2[j][i]=Center2[j][i]/Num[j];//�õ��������µľ�������	
				}	
			}
			Num[j]=0;
		}

		if(Compare(Center1,Center2,m_Category)==0)//Compare����0������������1��������
		{
			for(j=0;j<m_Category;j++)
			{
				for(i=0;i<nBands;i++)
				{
					Center1[j][i] = Center2[j][i];
					Center2[j][i] = 0;
				}
			}
		}
		else
			break;
		nIndex++;
	}

	//���仺��ռ�
	int *Gray = new int[m_Category];
	int Min=255,Max=0;
	for(j=0;j<m_Category;j++)//���ÿ���������ĸ�����ƽ��ֵ
	{
		Gray[j] = 0;
		for(i=0;i<nBands;i++)
		{
			Gray[j] +=Center1[j][i];
		}
		Gray[j] /= nBands;
		if(Min>Gray[j])
			Min = Gray[j];
		if(Max<Gray[j])
			Max = Gray[j];
	}
	for(j=0;j<m_Category;j++)
	{
		Gray[j] = 255.0/(Max-Min)*(Gray[j]-Min);
	}

	CImageProcessDoc Doc;
	BITMAPINFO *pBitmapInfo=(BITMAPINFO*)new char[sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(256)]; 
	Doc.CreateBitmapInfo(pBitmapInfo,nXsize,nYsize,3);
	LONG LineBytes = (nXsize*8+31)/32*4;
	HDB=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*nYsize);
	LPSTR pDB=(LPSTR)LocalLock(HDB);
	memcpy(pDB,pBitmapInfo,40+256*4);
	LPBYTE pData = (LPBYTE)pDB+40+256*4;
	//Ϊ�����ظ�ֵ
	for(l=0;l<nYsize;l++)
	{
		for(k=0;k<nXsize;k++)
		{
			for(j=0;j<m_Category;j++)
			{
				for(i=0;i<nBands;i++)
				{
					sum+=(Center1[j][i]-poBandBlock[i][l*nXsize+k])*(Center1[j][i]-poBandBlock[i][l*nXsize+k]);
				}
				d[j]=sum;
				sum = 0;
			}
			pData[(nYsize-l-1)*LineBytes + k] = Minimum(d)*255.0/(m_Category-1);
			//poBandFcolor[k] = Gray[Minimum(d)];//���������������ɫ��
		}
	}
	::LocalUnlock((HLOCAL)HDB);
	//�ͷſռ�
	for(i=0;i<nBands;i++)
    	CPLFree(poBandBlock[i]);

	if(m_Outputpath!="")
		Save(m_Outputpath,HDB);
	EndWaitCursor();
	UpdateData(TRUE);
	CDialog::OnOK();
}
