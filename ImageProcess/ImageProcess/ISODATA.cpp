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
	m_K = 5;//聚类中心数
	m_PNum = 10000;//每类最小样本数
	m_Stdv = 25.00;//标准差阈值
	m_C = 25.0;//聚类中心距离阈值、归并系数
	m_L = 2;//每次迭代最大合并类别对数
	m_I = 5;//最大迭代次数
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
	for(i=0;i<8;i++)//置空
	{
		poBandBlock[i]=NULL;
	}
	
	static char BASED_CODE filetype[]="所有文件(*.*)|*.*|TIF Files(*.TIF;*.TIFF)|*.tif;*.tiff|BMP Files(*.BMP)|*.bmp|JPG Files(*.JPG;*.JPEG;*.JPE)|*.jpg;*.jpeg;*.jpe|IMG Files(*.img)|*.img||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_InputFileName = dlg.GetPathName();
	else
		return ;
	
	GDALDataset *poDadaset;
	GDALAllRegister();//注册驱动
    poDadaset = (GDALDataset *)GDALOpen(m_InputFileName,GA_ReadOnly);
	
	if(poDadaset == NULL)
	{
		AfxMessageBox("影像打开失败！",MB_OK);
		return;
	}
	//获取影像信息
	nBands = poDadaset->GetRasterCount();//获取波段总数
	GDALRasterBand **poBand;//定义波段指针数组
	poBand = new GDALRasterBand *[nBands];
	
	if(poBand == NULL)
	{
		AfxMessageBox("创建各波段数据集失败！",MB_ICONWARNING);
		return;
	}
	
	for(i=0;i<nBands;i++)
	{
		poBand[i] = poDadaset->GetRasterBand(i+1);
		if(poBand[i] == NULL)
		{
			AfxMessageBox("创建i波段数据集失败！",MB_ICONWARNING);
			return;
		}
	}
	
	nXsize = poBand[0]->GetXSize();
	nYsize = poBand[0]->GetYSize();
	BeginWaitCursor();
	for(i =0 ;i<nBands; i++)
	{
		//分配缓存空间
		poBandBlock[i] = (BYTE *)CPLMalloc(sizeof(BYTE)*(nXsize*nYsize));
		//一次性读取RasterIO
		poBand[i]->RasterIO(GF_Read,0,0,nXsize,nYsize,
			poBandBlock[i],nXsize,nYsize,poBand[i]->GetRasterDataType(),0,0);
	}
	EndWaitCursor();

	UpdateData(FALSE);
}

void CISODATA::OnScanoutputfile() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|所有文件(*.*)|*.*||";
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
	double *d=new double [C];//定义距离
	double (*cn)[8]=new double[C][8];
	int i,j,k;
	double sum=0;
	int flag=0;//标记是否有某类像素数少于阈值m_PNum
	do
	{
		memset(Num,0,sizeof(int)*C);
		memset(d,0,sizeof(double)*C);
		memset(D1,0,sizeof(double)*C);D=0;
		memset(cn,0,sizeof(double)*C*8);
		memset(segma,0,sizeof(double)*C*8);
		flag = 0;
//第二步：按最小距离分类
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
//第三步：根据每类最少像素数m_PNum，判断去除像素数小于m_C的类别
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

//第四步：计算各类中心、各类内模式与类中心距离均值、所有模式到相应中心距离均值
	for(j=0;j<C;j++)
	{
		if(Num[j]!=0)
		{
			for(i=0;i<nBands;i++)
				cn[j][i]=cn[j][i]/Num[j];
			D+=D1[j];
			D1[j]=D1[j]/Num[j];//计算各类内模式与类中心距离均值
		}
	}
	D=D/(nXsize*nYsize);//计算所有模式到相应聚类中心得距离均值
	
	for(j=0;j<C;j++)//新类赋值
		for(i=0;i<nBands;i++)
		{
			c[j][i] = cn[j][i];
			cn[j][i]=0;
		}
	delete []d;delete []cn;
	return 5;
}
	
//第五步：根据迭代次数Ip，类别数C判断跳转到哪一步；
//如果Ip=I则使类间距阈值（即合并阈值）m_C=0，跳转至第九步结束，
//如果C<=K/2,跳至第六步分裂，如果C>=2K，跳至第九步合并，
//如果K/2<C<2K，则Ip为偶数转合并，Ip为奇数转分裂
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
//第六步：计算每一类样本中与聚类中心距离的标准差矢量segma[j]
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
//第七步：对每一标准差向量segma[j]，求其最大分量，以segma[j]max表示，用S记下为第几分量
	double *max=new double[C];//记录最大分量
	int *S=new int[C];//记录最大分量为第几分量（即记录下标）
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
//第八步：按条件分裂
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
//第九步：计算各类中心间距离d[i][j]=zi-zj;
//第十步：对d[i][j]排序并和m_C比较，若d[i][j]<m_C则对其进行合并
	CDistance *d=new CDistance[200];
	CDistance d1={0,0,0};
	double sum=0;
	int i,j,k,l,n;
	i=j=k=l=n=0;
	for(l=0;l<m_L;l++)
	{
		n=0;
		for(i=0;i<C-1;i++)//计算距离
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
		for(j=1;j<n;j++)//求最小距离
		{
			if(d1.d>d[j].d)
				d1=d[j];
		}
		if(d1.d<m_C)//类别合并
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

//第十一步：最后一步，判断Ip<m_I是否成立，成立则转第二步继续下一次迭代，
//不成了则说明迭代结束，跳出循环结束算法
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
		AfxMessageBox("请输入影像");
		return;
	}
	memset(Num,0,sizeof(Num));
	double (*Center)[8]=new double[50][8];
	memset(Center,0,sizeof(double)*50*8);
	int i,j,k,l,In=0,step=2;//In为当前迭代次数，step为当前执行步骤数
	//第一步：设置初始化参数（确定六参数，读入图像，确定聚类中心）
	for(j=0,k=0;j<m_K;j++,k++)//初始化聚类中心
	{
		for(i=0;i<nBands;i++)
			Center[j][i] = poBandBlock[i][k*1000];
	}
	
	double (*Segma)[8]=new double [50][8];
	memset(Segma,0,sizeof(double)*50*8);
	double Dd=0;
	double *Dd1=new double[50];
	memset(Dd1,0,sizeof(double)*50);
	C=m_K;//C为当前类别数
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
	//下面输出图像
	CImageProcessDoc Doc;
	BITMAPINFO *pBitmapInfo=(BITMAPINFO*)new char[sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(256)]; 
	Doc.CreateBitmapInfo(pBitmapInfo,nXsize,nYsize,3);
	LONG LineByte = (nXsize*8+31)/32*4;
	HDB=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineByte*nYsize);
	LPSTR pDB=(LPSTR)LocalLock(HDB);
	memcpy(pDB,pBitmapInfo,40+256*4);
	LPBYTE pData = (LPBYTE)pDB+40+256*4;
	int sum;double *d=new double[C];
	//为各像素赋值
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
			//poBandFcolor[k] = Gray[Minimum(d)];//分类结果像素如何着色？
		}
	}
	EndWaitCursor();
	::LocalUnlock((HLOCAL)HDB);
	delete []Center;delete []Segma;delete []Dd1;
	//释放空间
	for(i=0;i<nBands;i++)
		CPLFree(poBandBlock[i]);
	//保存文件
	if(m_OutputFileName!="")
		Save(m_OutputFileName,HDB);
	CDialog::OnOK();
}
