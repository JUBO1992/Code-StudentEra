// KLTransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "KLTransDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKLTransDlg dialog


CKLTransDlg::CKLTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKLTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKLTransDlg)
	m_InputFile = _T("");
	m_OutputFile = _T("");
	//}}AFX_DATA_INIT
	HDB=HDBN=NULL;
}


void CKLTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKLTransDlg)
	DDX_Text(pDX, IDC_INPUTFILE, m_InputFile);
	DDX_Text(pDX, IDC_OUTPUTFILE, m_OutputFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKLTransDlg, CDialog)
	//{{AFX_MSG_MAP(CKLTransDlg)
	ON_BN_CLICKED(IDC_SCANINPUT, OnScaninput)
	ON_BN_CLICKED(IDC_SCANOUTPUT, OnScanoutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKLTransDlg message handlers

BOOL CKLTransDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKLTransDlg::OnScaninput() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|所有文件(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_InputFile = dlg.GetPathName();
	else
		return ;
	CFile file;
// 	file.Open(m_InputFile,CFile::modeRead);
// 	HDB=ReadDIBFile(file);
	HDB = Open(m_InputFile);
	LPSTR pDb=(LPSTR)LocalLock(HDB);
	BITMAPINFO *pBIH = (LPBITMAPINFO)pDb;
	DWORD bits=pBIH->bmiHeader.biBitCount;
	if(bits!=24)
	{
		AfxMessageBox("请输入24位三波段真彩色影像");
		m_InputFile="";
		UpdateData(FALSE);
		return;
	}

	UpdateData(FALSE);
}

void CKLTransDlg::OnScanoutput() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|所有文件(*.*)|*.*||";
	CFileDialog dlg(FALSE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_OutputFile = dlg.GetPathName();
	else
		return ;
	
	UpdateData(FALSE);
}

void CKLTransDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(HDB==NULL||m_InputFile=="")
	{
		AfxMessageBox("请输入影像路径");
		return;
	}
	LPSTR pDb=(LPSTR)LocalLock(HDB);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
	LPBYTE pData=(LPBYTE)FindDIBBits(pDb);
	LONG LineBytes=(Width*24+31)/32*4;
	int i=0,j=0,k=0;
	double *rgb=new double[Width*Height*3];//n*3
	memset(rgb,0,sizeof(double)*Width*Height*3);
	for(i=0;i<Height;i++)
	{
		for(j=0;j<Width;j++)
		{
			rgb[i*3*Width+3*j+0]=pData[i*LineBytes+3*j+0];//b
			rgb[i*3*Width+3*j+1]=pData[i*LineBytes+3*j+1];//g
			rgb[i*3*Width+3*j+2]=pData[i*LineBytes+3*j+2];//r
			if(i==Height-1)
			TRACE("%d\n",pData[i*LineBytes+3*j+0]);
		}
	}
	double *cov=new double[3*3];
	memset(cov,0,sizeof(double)*3*3);
	double *eig=new double[3*3];
	memset(eig,0,sizeof(double)*3*3);
	Covariance(rgb,Width*Height,3,cov);
	eejcb(cov,3,eig,0.01,10);
	double *RGB=new double[Width*Height*3];
	memset(RGB,0,sizeof(double)*Width*Height*3);
	Multiply(rgb,Width*Height,3,3,eig,RGB);
	
	HDBN=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
	LPSTR pDbN=(LPSTR)LocalLock(HDBN);
	memcpy(pDbN,pDb,40);
	LPBYTE pDataN=(LPBYTE)pDbN+40;
	for(i=0;i<Height;i++)
	{
		for(j=0;j<Width;j++)
		{
			pDataN[i*LineBytes+3*j+0]=min(max(RGB[i*3*Width+3*j+0],0),255);//b
			pDataN[i*LineBytes+3*j+1]=min(max(RGB[i*3*Width+3*j+1],0),255);//g
			pDataN[i*LineBytes+3*j+2]=min(max(RGB[i*3*Width+3*j+2],0),255);//r
		}
	}
	::LocalUnlock((HLOCAL)HDB);
	::LocalFree((HLOCAL)HDB);
	::LocalUnlock((HLOCAL)HDBN);
	delete []rgb;delete []cov;delete []eig;
	if(m_OutputFile!="")
		Save(m_OutputFile,HDBN);
	CDialog::OnOK();
}

int CKLTransDlg::Covariance(double *M, int m, int n, double *Cov)
{
	double *M1=new double[m*n];
	memcpy(M1,M,sizeof(double)*m*n);
	double *avg=new double[n];
	memset(avg,0,sizeof(double)*n);
	int i=0,j=0,k=0;
	for(i=0;i<m*n;)
	{
		for(j=0;j<n;j++)
			avg[j]+=M1[i++];
	}
	for(j=0;j<n;j++)
		avg[j]/=m;
	for(i=0;i<m*n;)
	{
		for(j=0;j<n;j++)
			M1[i++]=M1[i]-avg[j];
	}
	double *M2=new double[m*n];
	MatrixTrans(M1,M2,m,n);
	Multiply(M2,n,m,n,M1,Cov);
	for(i=0;i<n*n;i++)
		Cov[i]/=(m*n);
	delete []M1;delete []M2;delete []avg;
	return 1;
}

//求实对称矩阵的特征值及特征向量的雅格比法 
//利用雅格比(Jacobi)方法求实对称矩阵的全部特征值及特征向量 
//返回值小于0表示超过迭代jt次仍未达到精度要求 
//返回值大于0表示正常返回 
//a-长度为n*n的数组，存放实对称矩阵，返回时对角线存放n个特征值 
//n-矩阵的阶数 
//u-长度为n*n的数组，返回特征向量(按列存储) 
//eps-控制精度要求 
//jt-整型变量，控制最大迭代次数 
int CKLTransDlg::eejcb(double a[],int n,double v[],double eps,int jt) 
{ 
	int i,j,p,q,u,w,t,s,l; 
	double fm,cn,sn,omega,x,y,d; 
	l=1; 
	for (i=0; i<=n-1; i++) 
	{ 
		v[i*n+i]=1.0; 
		for (j=0; j<=n-1; j++) 
		{ 
			if (i!=j) 
			{ 
				v[i*n+j]=0.0; 
			} 
		} 
	} 
	while (1==1) 
	{ 
		fm=0.0; 
		for (i=0; i<=n-1; i++) 
		{ 
			for (j=0; j<=n-1; j++) 
			{ 
				d=(int)fabs((float)a[i*n+j]); 
				if ((i!=j)&&(d>fm)) 
				{ 
					fm=d; 
					p=i; 
					q=j; 
				} 
			} 
		} 
		if (fm<eps) 
		{ 
			return(1); 
		} 
		if (l>jt) 
		{ 
			return(-1); 
		} 
		l=l+1; 
		u=p*n+q; 
		w=p*n+p; 
		t=q*n+p; 
		s=q*n+q; 
		x=-a[u]; 
		y=(a[s]-a[w])/2.0; 
		omega=x/sqrt((float)x*x+y*y); 
		if (y<0.0) 
		{ 
			omega=-omega; 
		} 
		sn=1.0+sqrt((float)1.0-omega*omega); 
		sn=omega/sqrt((float)2.0*sn); 
		cn=sqrt((float)1.0-sn*sn); 
		fm=a[w]; 
		a[w]=fm*cn*cn+a[s]*sn*sn+a[u]*omega; 
		a[s]=fm*sn*sn+a[s]*cn*cn-a[u]*omega; 
		a[u]=0.0; 
		a[t]=0.0; 
		for (j=0; j<=n-1; j++) 
		{ 
			if ((j!=p)&&(j!=q)) 
			{ 
				u=p*n+j; 
				w=q*n+j; 
				fm=a[u]; 
				a[u]=fm*cn+a[w]*sn; 
				a[w]=-fm*sn+a[w]*cn; 
			} 
		} 
		for (i=0; i<=n-1; i++) 
		{ 
			if ((i!=p)&&(i!=q)) 
			{ 
				u=i*n+p; 
				w=i*n+q; 
				fm=a[u]; 
				a[u]=fm*cn+a[w]*sn; 
				a[w]=-fm*sn+a[w]*cn; 
			} 
		} 
		for (i=0; i<=n-1; i++) 
		{ 
			u=i*n+p; 
			w=i*n+q; 
			fm=v[u]; 
			v[u]=fm*cn+v[w]*sn; 
			v[w]=-fm*sn+v[w]*cn; 
		} 
	} 
	return(1); 
}

int CKLTransDlg::Multiply(double *M1, int m1, int n, int m2, double *M2,double *Out)
{
	int i,j,k;
	for(i=0;i<m1;i++)
		for(j=0;j<m2;j++)
		{
			double temp = 0;
			for(k=0;k<n;k++)
				temp += *(M1+i*n+k) * *(M2+k*m2+j);
			*(Out+i*m2+j) = temp;
		}
	return 1;
}
int CKLTransDlg::MatrixTrans(double *In,double*Out,int m,int n)//矩阵转置
//m,n分别为In矩阵的行列号
{
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			*(Out+j*m+i) = *(In+i*n+j);
		return 1;
}