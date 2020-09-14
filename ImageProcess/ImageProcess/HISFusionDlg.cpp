// HISFusionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "HISFusionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHISFusionDlg dialog


CHISFusionDlg::CHISFusionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHISFusionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHISFusionDlg)
	m_MultPath = _T("");
	m_PanchPath = _T("");
	//}}AFX_DATA_INIT
	fusion=0;
	HDB1=HDB2=NULL;
}


void CHISFusionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHISFusionDlg)
	DDX_Text(pDX, IDC_MULTPATH, m_MultPath);
	DDX_Text(pDX, IDC_PANCHPATH, m_PanchPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHISFusionDlg, CDialog)
	//{{AFX_MSG_MAP(CHISFusionDlg)
	ON_BN_CLICKED(IDC_BUTTON_PANCH, OnButtonPanch)
	ON_BN_CLICKED(IDC_BUTTON_MULT, OnButtonMult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHISFusionDlg message handlers

void CHISFusionDlg::OnButtonPanch() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|所有文件(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_PanchPath = dlg.GetPathName();
	else
		return ;
	CFile file;
	file.Open(m_PanchPath,CFile::modeRead);
	HDB1=ReadDIBFile(file);
	LPSTR pDb=(LPSTR)LocalLock(HDB1);
	BITMAPINFO *pBIH = (LPBITMAPINFO)pDb;
	DWORD bits=pBIH->bmiHeader.biBitCount;
	if(bits!=8)
	{
		AfxMessageBox("请输入8位单波段全色影像");
		m_PanchPath="";
		UpdateData(FALSE);
		return;
	}
	UpdateData(FALSE);
}

void CHISFusionDlg::OnButtonMult() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="BMP Files(*.BMP)|*.bmp|所有文件(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_MultPath = dlg.GetPathName();
	else
		return ;
	CFile file;
	file.Open(m_MultPath,CFile::modeRead);
	HDB2=ReadDIBFile(file);
	LPSTR pDb=(LPSTR)LocalLock(HDB2);
	BITMAPINFO *pBIH = (LPBITMAPINFO)pDb;
	DWORD bits=pBIH->bmiHeader.biBitCount;
	if(bits!=24)
	{
		AfxMessageBox("请输入24位三波段真彩色影像");
		m_MultPath="";
		UpdateData(FALSE);
		return;
	}
	UpdateData(FALSE);
}

void CHISFusionDlg::OnHisPositive(float *Intensity,float *Hue,float *Saturation) 
{
		HDIB hDB=HDB2;
		LPSTR pDb=(LPSTR)LocalLock(hDB);
		int Width=DIBWidth(pDb);
    	int Height=DIBHeight(pDb);
		LPBYTE pData=(LPBYTE)FindDIBBits(pDb);
		int LineBytes=(Width*24+31)/32*4;//注意灰度图像每个像素一字节，彩色图像每个像素三字节
		
		float r,g,b,I,H,S;

		for(int i=0;i<Height;i++)
			for (int j=0;j<Width;j++)
			{
				r=pData[i*LineBytes+j*3+2];
				g=pData[i*LineBytes+j*3+1];
				b=pData[i*LineBytes+j*3];
				double V1,V2;
				V1=(2*r-g-b)/sqrt((float)6);
				V2=(g-b)/sqrt((float)2);
				I=float((r+g+b)/sqrt((float)3));
				float m=min(min(r,g),b);
				S=float(1-sqrt((float)3)*m/I);
				double f=0.5*(2*r-g-b)/sqrt((float)(r-g)*(r-g)+(r-b)*(g-b));
				if (g>=b) H=float(acos(f));
				else H=float(2*3.14159265359-acos(f));
				
				Intensity[i*Width+j]=I;
				Hue[i*Width+j]=H;
				Saturation[i*Width+j]=S;
			}
}

void CHISFusionDlg::Histogrammatch(float *Intensity,BYTE *pImg)
{
	
	HDIB hDB=HDB2;
	LPSTR pDb=(LPSTR)LocalLock(hDB);
	int Width=DIBWidth(pDb);
	int Height=DIBHeight(pDb);
	int LineBytes=(Width*8+31)/32*4;//图像pImg每行字节数

    LPBYTE HighpDibBits=pImg;
	float MinHigh,MaxHigh,MinI,MaxI;
	MinHigh=MinI=100000;
	MaxHigh=MaxI=0;
	float Panch,PrinciPal;
	int i;
	for (i=0;i<Height;i++)
	{
		for (int j=0;j<Width;j++)
		{
			LPBYTE pData=HighpDibBits+i*LineBytes+j;
			
			Panch=(float)*pData;
			
			if(Panch>MaxHigh) MaxHigh=Panch;
			if(Panch<MinHigh) MinHigh=Panch;
			
			PrinciPal=Intensity[i*Width+j];
			
			if(PrinciPal>MaxI) MaxI=PrinciPal;
			if(PrinciPal<MinI) MinI=PrinciPal;
		}
	}
	for(i=0;i<Height;i++)
	{
		for ( int j=0;j<Width;j++)
		{
			LPBYTE pData=HighpDibBits+i*LineBytes+j;
			Panch=(float)*pData;
			Panch=float((Panch-MinHigh)*(MaxI-MinI)/(MaxHigh-MinHigh)+MinI);
			Intensity[i*Width+j]=Panch;
		}
	}
}

void CHISFusionDlg::OnHisNegative(float *Intensity,float *Hue,float *Saturation)
{
		HDIB hDB=HDB2;
		LPSTR pDb=(LPSTR)LocalLock(hDB);
		int Width=DIBWidth(pDb);
		int Height=DIBHeight(pDb);
		int LineBytes=(Width*24+31)/32*4;//注意灰度图像每个像素一字节，彩色图像每个像素三字节
		LPBYTE pData=(LPBYTE)FindDIBBits(pDb);
	
		if (Intensity==NULL)
			{
				AfxMessageBox("无正交变换，错误",0,0);
				return;
			}
		float I,H,S;
		double R,G,B;
		
		for(int i=0;i<Height;i++)
			for(int j=0;j<Width;j++)
			{
				I=Intensity[i*Width+j];
				H=Hue[i*Width+j];
				S=Saturation[i*Width+j];
				
				if (H>=0&&H<2*3.1415926/3)
				{
					R=I*(1+S*cos(H)/cos(3.1415926/3-H))/sqrt((float)3);
					B=I*(1-S)/sqrt((float)3);
					G=sqrt((float)3)*I-R-B;
				}
				else if (H>2*3.1415926/3&&H<4*3.1415926/3)
				{
					G=I*(1+S*cos(H-2*3.1415926/3)/cos(3.1415926-H))/sqrt((float)3);
					R=I*(1-S)/sqrt((float)3);
					B=sqrt((float)3)*I-R-G;
				}
				else if (H>4*3.1415926/3&&H<2*3.1415926)
				{
					B=I*(1+S*cos(H-4*3.1415926/3)/cos(5*3.1415926/3-H))/sqrt((float)3);
					G=I*(1-S)/sqrt((float)3);
					R=sqrt((float)3)*I-G-B;
				}
				int r=int((max(0,min(255,R+0.5))));
				int g=int((max(0,min(255,G+0.5))));
				int b=int((max(0,min(255,B+0.5))));
				
				pData[i*LineBytes+j*3]=b;
				pData[i*LineBytes+j*3+1]=g;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
				pData[i*LineBytes+j*3+2]=r;
		  }
}

void CHISFusionDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(fusion==0)
		HisFusion();
	else if(fusion==1)
		NonWeightFusion();
	else if(fusion==2)
		WeightFusion();
	UpdateData(FALSE);
	CDialog::OnOK();
}

void CHISFusionDlg::HisFusion()
{
	if(HDB1==NULL||HDB2==NULL)
	{
		AfxMessageBox("请选择影像路径");
		return;
	}
	LPSTR pDb=(LPSTR)LocalLock(HDB2);
	int Width=DIBWidth(pDb);
	int Height=DIBHeight(pDb);
	LPSTR pDb1=(LPSTR)LocalLock(HDB1);
	BYTE *pImg=(LPBYTE)FindDIBBits(pDb1);
	
	float *Intensity=new float[Height*Width];
	float *Hue=new float[Height*Width];
	float *Saturation=new float[Height*Width];
	BeginWaitCursor();
	OnHisPositive(Intensity,Hue,Saturation);//转化为HIS
	Histogrammatch(Intensity,pImg);//匹配
	OnHisNegative(Intensity,Hue,Saturation);//转化为RGB	
	EndWaitCursor();
	::LocalUnlock((HLOCAL)HDB1);
	::LocalFree((HLOCAL)HDB1);
	::LocalUnlock((HLOCAL)HDB2);
	delete []Intensity;
	delete []Hue;
	delete []Saturation;
}

void CHISFusionDlg::NonWeightFusion()
{
	if(HDB1==NULL||HDB2==NULL)
	{
		AfxMessageBox("请选择影像路径");
		return;
	}
	LPSTR pDb1=(LPSTR)LocalLock(HDB1);//全色
	int Width1=DIBWidth(pDb1);
	int Height1=DIBHeight(pDb1);
	int LineBytes1=(Width1*8+31)/32*4;
	LPBYTE pData1=(LPBYTE)FindDIBBits(pDb1);
	LPSTR pDb2=(LPSTR)LocalLock(HDB2);//多波段
	int Width2=DIBWidth(pDb2);
	int Height2=DIBHeight(pDb2);
	int LineBytes2=(Width2*24+31)/32*4;
	LPBYTE pData2=(LPBYTE)FindDIBBits(pDb2);
	int r=0,g=0,b=0;
	for(int i=0;i<Height1;i++)
	{
		for(int j=0;j<Width1;j++)
		{
			r=pData1[i*LineBytes1+j]*0.7+pData2[i*LineBytes2+3*j+0]*0.5;
			g=pData1[i*LineBytes1+j]*0.7+pData2[i*LineBytes2+3*j+1]*0.5;
			b=pData1[i*LineBytes1+j]*0.7+pData2[i*LineBytes2+3*j+2]*0.5;
			pData2[i*LineBytes2+3*j+0]=min(r/1.2,255);
			pData2[i*LineBytes2+3*j+1]=min(g/1.2,255);
			pData2[i*LineBytes2+3*j+2]=min(b/1.2,255);
		}
	}
}

void CHISFusionDlg::WeightFusion()//加权融合
{
	if(HDB1==NULL||HDB2==NULL)
	{
		AfxMessageBox("请选择影像路径");
		return;
	}
	LPSTR pDb1=(LPSTR)LocalLock(HDB1);//全色
	int Width1=DIBWidth(pDb1);
	int Height1=DIBHeight(pDb1);
	int LineBytes1=(Width1*8+31)/32*4;
	LPBYTE pData1=(LPBYTE)FindDIBBits(pDb1);
	LPSTR pDb2=(LPSTR)LocalLock(HDB2);//多波段
	int Width2=DIBWidth(pDb2);
	int Height2=DIBHeight(pDb2);
	int LineBytes2=(Width2*24+31)/32*4;
	LPBYTE pData2=(LPBYTE)FindDIBBits(pDb2);

	//计算相关系数
	int i,j,k,l;
	i=j=k=l=0;
	double Gavg=0,RGBavg[3]={0,0,0};
	for(i=0;i<Height1;i++)
	{
		for(j=0;j<Width1;j++)
		{
			Gavg+=pData1[i*LineBytes1+j];
			RGBavg[0]+=pData2[i*LineBytes2+3*j+0];
			RGBavg[1]+=pData2[i*LineBytes2+3*j+1];
			RGBavg[2]+=pData2[i*LineBytes2+3*j+2];
		}
	}
	Gavg/=(Height1*Width1);
	RGBavg[0]/=(Height2*Width2);RGBavg[1]/=(Height2*Width2);RGBavg[2]/=(Height2*Width2);
	double Gsegma=0,RGBsegam[3]={0,0,0},GRGBsegma[3]={0,0,0};
	for(i=0;i<Height1;i++)
	{
		for(j=0;j<Width1;j++)
		{
			Gsegma+=(pData1[i*LineBytes1+j]-Gavg)*(pData1[i*LineBytes1+j]-Gavg);
			GRGBsegma[0]+=(pData1[i*LineBytes1+j]-Gavg)*(pData2[i*LineBytes2+3*j+0]-RGBavg[0]);
			GRGBsegma[1]+=(pData1[i*LineBytes1+j]-Gavg)*(pData2[i*LineBytes2+3*j+1]-RGBavg[1]);
			GRGBsegma[2]+=(pData1[i*LineBytes1+j]-Gavg)*(pData2[i*LineBytes2+3*j+2]-RGBavg[2]);
			RGBsegam[0]+=(pData2[i*LineBytes2+3*j+0]-RGBavg[0])*(pData2[i*LineBytes2+3*j+0]-RGBavg[0]);
			RGBsegam[1]+=(pData2[i*LineBytes2+3*j+1]-RGBavg[1])*(pData2[i*LineBytes2+3*j+1]-RGBavg[1]);
			RGBsegam[2]+=(pData2[i*LineBytes2+3*j+2]-RGBavg[2])*(pData2[i*LineBytes2+3*j+2]-RGBavg[2]);
		}
	}
	Gsegma=sqrt((float)Gsegma/(Height1*Width1));
	GRGBsegma[0]=sqrt((float)GRGBsegma[0]/(Height1*Width1));
	GRGBsegma[1]=sqrt((float)GRGBsegma[1]/(Height1*Width1));
	GRGBsegma[2]=sqrt((float)GRGBsegma[2]/(Height1*Width1));
	RGBsegam[0]=sqrt((float)RGBsegam[0]/(Height2*Width2));
	RGBsegam[1]=sqrt((float)RGBsegam[1]/(Height2*Width2));
	RGBsegam[2]=sqrt((float)RGBsegam[2]/(Height2*Width2));
	double Ratio[3]={0,0,0};//全色图像与多波段图像各波段的相关系数
	Ratio[0]=GRGBsegma[0]/(Gsegma*RGBsegam[0]);
	Ratio[1]=GRGBsegma[1]/(Gsegma*RGBsegam[1]);
	Ratio[2]=GRGBsegma[2]/(Gsegma*RGBsegam[2]);
	double Pi[3]={0},Pj[3]={0};
	for(i=0;i<3;i++)
	{
		Pi[i]=0.5*(1-Ratio[i]);
		Pj[i]=1-Pi[i];
	}
	int r=0,g=0,b=0;
	int A=1,B=0;
	for(i=0;i<Height1;i++)
	{
		for(j=0;j<Width1;j++)
		{
			r=A*(pData1[i*LineBytes1+j]*Pi[0]+pData2[i*LineBytes2+3*j+0]*Pj[0])+B;
			g=A*(pData1[i*LineBytes1+j]*Pi[1]+pData2[i*LineBytes2+3*j+1]*Pj[1])+B;
			b=A*(pData1[i*LineBytes1+j]*Pi[2]+pData2[i*LineBytes2+3*j+2]*Pj[2])+B;
			pData2[i*LineBytes2+3*j+0]=min(r,255);
			pData2[i*LineBytes2+3*j+1]=min(g,255);
			pData2[i*LineBytes2+3*j+2]=min(b,255);
		}
	}
}
