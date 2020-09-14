// ISODATA.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "ISODATA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CISODATA dialog


CISODATA::CISODATA(CWnd* pParent /*=NULL*/)
	: CDialog(CISODATA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CISODATA)
	m_InputFileName = _T("");
	m_OutputFileName = _T("");
	m_K = 5;//����������
	m_PNum = 10000;//ÿ����С������
	m_Stdv = 25.00;//��׼����ֵ
	m_C = 25.0;//�������ľ�����ֵ���鲢ϵ��
	m_L = 2;//ÿ�ε������ϲ�������
	m_I = 5;//����������
	//}}AFX_DATA_INIT
	HDB=NULL;
}


void CISODATA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CISODATA)
	DDX_Text(pDX, IDC_INPUTFILEPATH, m_InputFileName);
	DDX_Text(pDX, IDC_OUTPUTFILEPATH, m_OutputFileName);
	DDX_Text(pDX, IDC_CENTERNUM, m_K);
	DDV_MinMaxInt(pDX, m_K, 1, 15);
	DDX_Text(pDX, IDC_MINPOINTNUM, m_PNum);
	DDV_MinMaxInt(pDX, m_PNum, 1, 99999999);
	DDX_Text(pDX, IDC_STDV, m_Stdv);
	DDX_Text(pDX, IDC_DISTENCE, m_C);
	DDX_Text(pDX, IDC_MAXMERCATE, m_L);
	DDX_Text(pDX, IDC_MAXINTER, m_I);
	DDV_MinMaxInt(pDX, m_I, 1, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CISODATA, CDialog)
	//{{AFX_MSG_MAP(CISODATA)
	ON_BN_CLICKED(IDC_SCANINPUTFILE, OnScaninputfile)
	ON_BN_CLICKED(IDC_SCANOUTPUTFILE, OnScanoutputfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CISODATA message handlers

BOOL CISODATA::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CISODATA::OnScaninputfile() 
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
		m_InputFileName = dlg.GetPathName();
	else
		return ;
	
	GDALDataset *poDadaset;
	GDALAllRegister();//ע������
    poDadaset = (GDALDataset *)GDALOpen(m_InputFileName,GA_ReadOnly);
	
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

void CISODATA::OnScanoutputfile() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|�����ļ�(*.*)|*.*||";
	CFileDialog dlg(FALSE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_OutputFileName = dlg.GetPathName();
	else
		return ;
	
	UpdateData(FALSE);
}

int CISODATA::Minimum(double *d,int m)
{
	int i=0,j=0;
	double n=d[0];
	for(i=0;i<m;i++)
		if(n>d[i])
		{
			n=d[i];
			j=i;
		}
	return j;
}

int CISODATA::Step234(double (*c)[8],double *D1,double D,double (*segma)[8])
{
	double *d=new double [C];//�������
	double (*cn)[8]=new double[C][8];
	int i,j,k;
	double sum=0;
	int flag=0;//����Ƿ���ĳ��������������ֵm_PNum
	do
	{
		memset(Num,0,sizeof(int)*C);
		memset(d,0,sizeof(double)*C);
		memset(D1,0,sizeof(double)*C);D=0;
		memset(cn,0,sizeof(double)*C*8);
		memset(segma,0,sizeof(double)*C*8);
		flag = 0;
//�ڶ���������С�������
		for(k=0;k<nXsize*nYsize;k++)
		{
			for(j=0;j<C;j++)
			{
				for(i=0;i<nBands;i++)
				{
					sum+=(c[j][i]-poBandBlock[i][k])*(c[j][i]-poBandBlock[i][k]);
					
				}
				d[j]=sqrt((float)sum);
				sum=0;
			} 
			for(i=0;i<nBands;i++)
			{
				segma[Minimum(d,C)][i]+=(c[j][i]-poBandBlock[i][k])*(c[j][i]-poBandBlock[i][k]);
				cn[Minimum(d,C)][i]+=poBandBlock[i][k];
				if(i==0)
				{
					D1[Minimum(d,C)]+=d[Minimum(d,C)];
					Num[Minimum(d,C)]++;
				}
			}
		}
//������������ÿ������������m_PNum���ж�ȥ��������С��m_C�����
		for(j=0;j<C;j++)
		{
			if(Num[j]<m_PNum)
			{
				flag=1;
				C=C-1;
				for(i=j;i<C;i++)
					for(k=0;k<nBands;k++)
						c[i][k]=c[i+1][k];
			}
		}
	}while(flag==1);

//���Ĳ�������������ġ�������ģʽ�������ľ����ֵ������ģʽ����Ӧ���ľ����ֵ
	for(j=0;j<C;j++)
	{
		if(Num[j]!=0)
		{
			for(i=0;i<nBands;i++)
				cn[j][i]=cn[j][i]/Num[j];
			D+=D1[j];
			D1[j]=D1[j]/Num[j];//���������ģʽ�������ľ����ֵ
		}
	}
	D=D/(nXsize*nYsize);//��������ģʽ����Ӧ�������ĵþ����ֵ
	
	for(j=0;j<C;j++)//���ำֵ
		for(i=0;i<nBands;i++)
		{
			c[j][i] = cn[j][i];
			cn[j][i]=0;
		}
	delete []d;delete []cn;
	return 5;
}
	
//���岽�����ݵ�������Ip�������C�ж���ת����һ����
//���Ip=I��ʹ������ֵ�����ϲ���ֵ��m_C=0����ת���ھŲ�������
//���C<=K/2,�������������ѣ����C>=2K�������ھŲ��ϲ���
//���K/2<C<2K����IpΪż��ת�ϲ���IpΪ����ת����
int CISODATA::Step5(int Ip)
{
	if(Ip==m_I)
	{
		m_C=0;
		return 9;
	}
	else if(C<=m_K/2 || (m_K/2<=C && C<=2*m_K && Ip%2==1))
		return 6;
	else if(C>=2*m_K || (m_K/2<=C && C<=2*m_K && Ip%2==0))
		return 9;
	return 0;
}

int CISODATA::Step678(double (*c)[8],double *D1,double D,double (*segma)[8])
{
//������������ÿһ����������������ľ���ı�׼��ʸ��segma[j]
	int i,j;
	for(j=0;j<C;j++)
	{
		for(i=0;i<nBands;i++)
		{
			if(Num[j]!=0)
			{
			segma[j][i]/=Num[j];
			segma[j][i]=sqrt((float)segma[j][i]);
			}
		}	
	}
//���߲�����ÿһ��׼������segma[j]����������������segma[j]max��ʾ����S����Ϊ�ڼ�����
	double *max=new double[C];//��¼������
	int *S=new int[C];//��¼������Ϊ�ڼ�����������¼�±꣩
	for(j=0;j<C;j++)
	{
		max[j]=0;S[j]=0;
		for(i=0;i<nBands;i++)
			if(max[j]<segma[j][i])
			{
				max[j]=segma[j][i];
				S[j]=i;
			}
	}
//�ڰ˲�������������
	int n=C;
	for(j=0;j<n;j++)
	{
		if(max[j]>m_Stdv && ((D1[j]>D && Num[j]>2*(m_PNum+1)) || C<=m_K/2))
		{
			C=C+1;
			for(i=0;i<nBands;i++)
				c[C-1][i]=c[j][i];
			c[j][S[j]]+=0.5*max[j];
			c[C-1][S[j]]-=0.5*max[j];
		}
	}
	delete []max;delete []S;
	return 2;
}

struct CDistance{
	int c1;
	int c2;
	double d;
	};
int CISODATA::Step9_11(double (*c)[8])
{
//�ھŲ�������������ļ����d[i][j]=zi-zj;
//��ʮ������d[i][j]���򲢺�m_C�Ƚϣ���d[i][j]<m_C�������кϲ�
	CDistance *d=new CDistance[200];
	CDistance d1={0,0,0};
	double sum=0;
	int i,j,k,l,n;
	i=j=k=l=n=0;
	for(l=0;l<m_L;l++)
	{
		n=0;
		for(i=0;i<C-1;i++)//�������
		{
			for(j=i+1;j<C;j++)
			{
				for(k=0;k<nBands;k++)
					sum+=(c[i][k]-c[j][k])*(c[i][k]-c[j][k]);
				d[n].c1=i;
				d[n].c2=j;
				d[n++].d=sqrt((float)sum);
				sum=0;
			}
		}
		d1=d[0];
		for(j=1;j<n;j++)//����С����
		{
			if(d1.d>d[j].d)
				d1=d[j];
		}
		if(d1.d<m_C)//���ϲ�
		{
			for(k=0;k<nBands;k++)
			{
				c[d1.c1][k]=(Num[d1.c1]*c[d1.c1][k]+Num[d1.c2]*c[d1.c2][k])/(Num[d1.c1]+Num[d1.c2]);
			}
			C=C-1;
			for(i=d1.c2;i<C;i++)
				for(k=0;k<nBands;k++)
					c[i][k]=c[i+1][k];
		}
		else if(d1.d>=m_C)
			break;
	}//end of l
	delete []d;

//��ʮһ�������һ�����ж�Ip<m_I�Ƿ������������ת�ڶ���������һ�ε�����
//��������˵����������������ѭ�������㷨
	return 2;
}

void CISODATA::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_PNum=max(m_PNum,nXsize*nYsize/m_K/5);
	m_Stdv=max(m_Stdv,255*sqrt((float)nBands)/m_K/2);
	m_C=max(m_C,255*sqrt((float)nBands)/m_K/2);
	m_L=max(m_L,m_K/3);
	if(m_InputFileName=="")
	{
		AfxMessageBox("������Ӱ��");
		return;
	}
	memset(Num,0,sizeof(Num));
	double (*Center)[8]=new double[50][8];
	memset(Center,0,sizeof(double)*50*8);
	int i,j,k,l,In=0,step=2;//InΪ��ǰ����������stepΪ��ǰִ�в�����
	//��һ�������ó�ʼ��������ȷ��������������ͼ��ȷ���������ģ�
	for(j=0,k=0;j<m_K;j++,k++)//��ʼ����������
	{
		for(i=0;i<nBands;i++)
			Center[j][i] = poBandBlock[i][k*1000];
	}
	
	double (*Segma)[8]=new double [50][8];
	memset(Segma,0,sizeof(double)*50*8);
	double Dd=0;
	double *Dd1=new double[50];
	memset(Dd1,0,sizeof(double)*50);
	C=m_K;//CΪ��ǰ�����
	BeginWaitCursor();
	while(In<m_I)
	{
		switch(step)
		{
		case 2:step=Step234(Center,Dd1,Dd,Segma);
			break;
		case 5:step=Step5(In);
			break;
		case 6:step=Step678(Center,Dd1,Dd,Segma);
			In++;
			break;
		case 9:step=Step9_11(Center);
			In++;
			break;
		default:
			break;
		}
	}
	//�������ͼ��
	CImageProcessDoc Doc;
	BITMAPINFO *pBitmapInfo=(BITMAPINFO*)new char[sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(256)]; 
	Doc.CreateBitmapInfo(pBitmapInfo,nXsize,nYsize,3);
	LONG LineByte = (nXsize*8+31)/32*4;
	HDB=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineByte*nYsize);
	LPSTR pDB=(LPSTR)LocalLock(HDB);
	memcpy(pDB,pBitmapInfo,40+256*4);
	LPBYTE pData = (LPBYTE)pDB+40+256*4;
	int sum;double *d=new double[C];
	//Ϊ�����ظ�ֵ
	for(l=0;l<nYsize;l++)
	{
		for(k=0;k<nXsize;k++)
		{
			for(j=0;j<C;j++)
			{
				for(i=0;i<nBands;i++)
				{
					sum+=(Center[j][i]-poBandBlock[i][l*nXsize+k])*(Center[j][i]-poBandBlock[i][l*nXsize+k]);
				}
				d[j]=sum;
				sum = 0;
			}
			pData[(nYsize-l-1)*LineByte + k] = Minimum(d,C)*255.0/(C-1);
			//poBandFcolor[k] = Gray[Minimum(d)];//���������������ɫ��
		}
	}
	EndWaitCursor();
	::LocalUnlock((HLOCAL)HDB);
	delete []Center;delete []Segma;delete []Dd1;
	//�ͷſռ�
	for(i=0;i<nBands;i++)
		CPLFree(poBandBlock[i]);
	//�����ļ�
	if(m_OutputFileName!="")
		Save(m_OutputFileName,HDB);
	CDialog::OnOK();
}
