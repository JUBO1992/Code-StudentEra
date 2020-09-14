// PointTrans.cpp: implementation of the CPointTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "imageprocess.h"
#include "PointTrans.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPointTrans::CPointTrans()
{

}

CPointTrans::~CPointTrans()
{

}

HDIB CPointTrans::MeanFilter(HDIB HOld, int m, int n)//均值滤波
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	int i,j,k,l;
	i=j=k=l=0;
	double gray,r,g,b;
	gray=r=g=b=0;
	for (i=m/2;i<Height-m/2;i++)
	{
		for (j=n/2;j<Width-n/2;j++)	
		{	
			if(bits==8)
			{
				for(k=-m/2;k<=m/2;k++)
					for(l=-n/2;l<=n/2;l++)
						gray+=pData[(i+k)*LineBytes+j+l];
					gray/=(m*n);
					pDataN[i*LineBytes+j]=min(255,max(gray,0));
					gray=0;
			}
			else if(bits==24)
			{
				for(k=-m/2;k<=m/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						r+=pData[(i+k)*LineBytes+3*(j+l)+0];
						g+=pData[(i+k)*LineBytes+3*(j+l)+1];
						b+=pData[(i+k)*LineBytes+3*(j+l)+2];
					}
					r/=(m*n);
					g/=(m*n);
					b/=(m*n);
					pDataN[i*LineBytes+3*j+0]=min(255,max(r,0));
					pDataN[i*LineBytes+3*j+1]=min(255,max(g,0));
					pDataN[i*LineBytes+3*j+2]=min(255,max(b,0));
					r=g=b=0;
			}
		}
	}
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

HDIB CPointTrans::MedianFilter(HDIB HOld, int m, int n)//中值滤波
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	int i,j,k,l;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	unsigned char *gray=new unsigned char[m*n];
	unsigned char *r=new unsigned char[m*n];
	unsigned char *g=new unsigned char[m*n];
	unsigned char *b=new unsigned char[m*n];
	for (i=m/2;i<Height-m/2;i++)
	{
		for (j=n/2;j<Width-n/2;j++)	
		{	
			if(bits==8)
			{
				for(k=0;k<m;k++)
					for(l=0;l<n;l++)
						gray[k*n+l]=pData[(i+k-m/2)*LineBytes+j+l-n/2];
				pDataN[i*LineBytes+j]=GetMediaNum(gray,m*n);
			}
			else if(bits==24)
			{
				for(k=-m/2;k<=m/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						r[(k+m/2)*n+l+n/2]=pData[(i+k)*LineBytes+3*(j+l)+0];
						g[(k+m/2)*n+l+n/2]=pData[(i+k)*LineBytes+3*(j+l)+1];
						b[(k+m/2)*n+l+n/2]=pData[(i+k)*LineBytes+3*(j+l)+2];
					}
				pDataN[i*LineBytes+3*j+0]=GetMediaNum(r,m*n);
				pDataN[i*LineBytes+3*j+1]=GetMediaNum(g,m*n);
				pDataN[i*LineBytes+3*j+2]=GetMediaNum(b,m*n);
			}
		}
	}
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

unsigned char CPointTrans::GetMediaNum(unsigned char *bArray, int iFilterLen)
{
	// 循环变量
	int		i;
	int		j;
	
	// 中间变量
	unsigned char bTemp;
	
	// 用冒泡法对数组进行排序
	for (j = 0; j < iFilterLen - 1; j ++)
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	
	// 计算中值
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
	
	// 返回中值
	return bTemp;
}

HDIB CPointTrans::TemplateOperations(HDIB HOld, int *Array, int m, int n)
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	int i,j,k,l;
	i=j=k=l=0;
	double gray,r,g,b;
	gray=r=g=b=0;
	int Ratio=0;
	for(i=0;i<m*n;i++)
		Ratio+=Array[i];
	for (i=(m-1)/2;i<Height-m/2;i++)
	{
		for (j=(n-1)/2;j<Width-n/2;j++)	
		{	
			if(bits==8)
			{
				for(k=-(m-1)/2;k<=m/2;k++)
					for(l=-(n-1)/2;l<=n/2;l++)
						gray+=Array[(k+m/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+j+l];
					gray/=Ratio;
					pDataN[i*LineBytes+j]=min(255,max(gray,0));
					gray=0;
			}
			else if(bits==24)
			{
				for(k=-(m-1)/2;k<=m/2;k++)
					for(l=-(n-1)/2;l<=n/2;l++)
					{
						r+=Array[(k+m/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+3*(j+l)+0];
						g+=Array[(k+m/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+3*(j+l)+1];
						b+=Array[(k+m/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+3*(j+l)+2];
					}
					r/=Ratio;
					g/=Ratio;
					b/=Ratio;
					pDataN[i*LineBytes+3*j+0]=min(255,max(r,0));
					pDataN[i*LineBytes+3*j+1]=min(255,max(g,0));
					pDataN[i*LineBytes+3*j+2]=min(255,max(b,0));
					r=g=b=0;
			}
		}
	}
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

HDIB CPointTrans::GradSharp(HDIB HOld,int flag)//flag=0执行梯度算子，flag=1执行Robert算子
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	int i,j,k,l;
	i=j=k=l=0;
	int gray,r,g,b;
	gray=r=g=b=0;
	int Ratio=0;
	for (i=0;i<Height-1;i++)
	{
		for (j=0;j<Width-1;j++)	
		{	
			if(bits==8)
			{
				if(flag==0)
				{
					gray=(int)fabs((float)pData[i*LineBytes+j+1]-pData[i*LineBytes+j]);
					gray+=(int)fabs((float)pData[(i+1)*LineBytes+j]-pData[i*LineBytes+j]);
				}
				else if(flag==1)
				{
					gray=(int)fabs((float)pData[(i+1)*LineBytes+j+1]-pData[i*LineBytes+j]);
					gray+=(int)fabs((float)pData[(i+1)*LineBytes+j]-pData[i*LineBytes+j+1]);
				}
				pDataN[i*LineBytes+j]=min(255,max(gray,0));
				gray=0;
			}
			else if(bits==24)
			{
				if(flag==0)
				{
					r=abs(pData[i*LineBytes+3*(j+1)+0]-pData[i*LineBytes+3*j+0]);
					r+=abs(pData[(i+1)*LineBytes+3*j+0]-pData[i*LineBytes+3*j+0]);
					g=abs(pData[i*LineBytes+3*(j+1)+1]-pData[i*LineBytes+3*j+1]);
					g+=abs(pData[(i+1)*LineBytes+3*j+0]-pData[i*LineBytes+3*j+1]);
					b=abs(pData[i*LineBytes+3*(j+1)+2]-pData[i*LineBytes+3*j+2]);
					b+=abs(pData[(i+1)*LineBytes+3*j+0]-pData[i*LineBytes+3*j+2]);
				}
				else if(flag==1)
				{
					r=abs(pData[(i+1)*LineBytes+3*(j+1)+0]-pData[i*LineBytes+3*j+0]);
					r+=abs(pData[(i+1)*LineBytes+3*j+0]-pData[i*LineBytes+3*(j+1)+0]);
					g=abs(pData[(i+1)*LineBytes+3*(j+1)+1]-pData[i*LineBytes+3*j+1]);
					g+=abs(pData[(i+1)*LineBytes+3*j+0]-pData[i*LineBytes+3*(j+1)+1]);
					b=abs(pData[(i+1)*LineBytes+3*(j+1)+2]-pData[i*LineBytes+3*j+2]);
					b+=abs(pData[(i+1)*LineBytes+3*j+0]-pData[i*LineBytes+3*(j+1)+2]);
				}
				pDataN[i*LineBytes+3*j+0]=min(255,max(r,0));
				pDataN[i*LineBytes+3*j+1]=min(255,max(g,0));
				pDataN[i*LineBytes+3*j+2]=min(255,max(b,0));
				r=g=b=0;
			}
		}
	}
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

HDIB CPointTrans::EdgeDetectTemplate(HDIB HOld, int *X, int *Y, int n)
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	int i,j,k,l;
	i=j=k=l=0;
	int grayx,grayy,rx,ry,gx,gy,bx,by;
	grayx=grayy=rx=ry=gx=gy=bx=by=0;
	for (i=n/2;i<Height-n/2;i++)
	{
		for (j=n/2;j<Width-n/2;j++)	
		{	
			if(bits==8)
			{
				for(k=-n/2;k<=n/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						grayx+=X[(k+n/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+j+l];
						grayy+=Y[(k+n/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+j+l];
					}
					grayx=abs(grayx)+abs(grayy);
					pDataN[i*LineBytes+j]=min(255,max(grayx,0));
					grayx=grayy=0;
			}
			else if(bits==24)
			{
				for(k=-n/2;k<=n/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						rx+=X[(k+n/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+3*(j+l)+0];
						ry+=Y[(k+n/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+3*(j+l)+0];
						gx+=X[(k+n/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+3*(j+l)+1];
						gy+=Y[(k+n/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+3*(j+l)+1];
						bx+=X[(k+n/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+3*(j+l)+2];
						by+=Y[(k+n/2)*n+(l+n/2)]*pData[(i+k)*LineBytes+3*(j+l)+2];
					}
					rx=abs(rx)+abs(ry);
					bx=abs(bx)+abs(by);
					gx=abs(gx)+abs(gy);
					pDataN[i*LineBytes+3*j+0]=min(255,max(rx,0));
					pDataN[i*LineBytes+3*j+1]=min(255,max(gx,0));
					pDataN[i*LineBytes+3*j+2]=min(255,max(bx,0));
					rx=ry=gx=gy=bx=by=0;
			}
		}
	}
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

//下面的Lee、Kuan、Forst算子为雷达图像滤波算子
HDIB CPointTrans::LeeFilter(HDIB HOld, int m, int n, int flag)//flag=0为Lee滤波，flag=1为增强的Lee滤波
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	int i,j,k,l;
	i=j=k=l=0;
	double gray,r,g,b;//定义均值
	double sigmagray,sigmar,sigmag,sigmab;//定义方差
	gray=r=g=b=0;sigmagray=sigmar=sigmag=sigmab=0;
	for (i=m/2;i<Height-m/2;i++)
	{
		for (j=n/2;j<Width-n/2;j++)	
		{	
			if(bits==8)
			{
				for(k=-m/2;k<=m/2;k++)//计算均值
					for(l=-n/2;l<=n/2;l++)
						gray+=pData[(i+k)*LineBytes+j+l];
					gray/=(m*n);
				for(k=-m/2;k<=m/2;k++)//计算方差
					for(l=-n/2;l<=n/2;l++)
						sigmagray+=(pData[(i+k)*LineBytes+j+l]-gray)*(pData[(i+k)*LineBytes+j+l]-gray);
					sigmagray/=(m*n);
				float Cu,Ci,Cmax;
				Cu=(float)0.5227;
				Ci=sqrt((float)sigmagray)/gray;//注意标准差与方差的区别
				//Ci=sigmagray/gray;
				Cmax=1.732*Cu;
				//计算权值
				float w=1-pow((float)Cu,2)/pow((float)Ci,2);
				if(flag==0)//Lee
					gray=gray*w+pData[i*LineBytes+j]*(1-w);
				else if(flag==1)// 增强的Lee
				{
					if(Ci<Cu)
					{
						gray=gray;
					}
					else if(Ci>=Cu&&Ci<=Cmax)
					{
						gray=gray*w+pData[i*LineBytes+j]*(1-w);
					}
					else if(Ci>Cmax)
					{
						gray=pData[i*LineBytes+j];
					}
				}
				pDataN[i*LineBytes+j]=(BYTE)min(255,max(gray,0));
				gray=0;sigmagray=0;
			}
			else if(bits==24)
			{
				for(k=-m/2;k<=m/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						r+=pData[(i+k)*LineBytes+3*(j+l)+0];
						g+=pData[(i+k)*LineBytes+3*(j+l)+1];
						b+=pData[(i+k)*LineBytes+3*(j+l)+2];
					}
					r/=(m*n);
					g/=(m*n);
					b/=(m*n);
					pDataN[i*LineBytes+3*j+0]=min(255,max(r,0));
					pDataN[i*LineBytes+3*j+1]=min(255,max(g,0));
					pDataN[i*LineBytes+3*j+2]=min(255,max(b,0));
					r=g=b=0;
			}
		}
	}
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

HDIB CPointTrans::KuanFilter(HDIB HOld, int m, int n,int flag)//flag=0为Lee滤波，flag=1为增强的Lee滤波
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	int i,j,k,l;
	i=j=k=l=0;
	double gray,r,g,b;//定义均值
	double sigmagray,sigmar,sigmag,sigmab;//定义方差
	gray=r=g=b=0;sigmagray=sigmar=sigmag=sigmab=0;
	for (i=m/2;i<Height-m/2;i++)
	{
		for (j=n/2;j<Width-n/2;j++)	
		{	
			if(bits==8)
			{
				for(k=-m/2;k<=m/2;k++)//计算均值
					for(l=-n/2;l<=n/2;l++)
						gray+=pData[(i+k)*LineBytes+j+l];
					gray/=(m*n);
				for(k=-m/2;k<=m/2;k++)//计算方差
					for(l=-n/2;l<=n/2;l++)
						sigmagray+=(pData[(i+k)*LineBytes+j+l]-gray)*(pData[(i+k)*LineBytes+j+l]-gray);
					sigmagray/=(m*n);
				//计算权值
				float Cu,Ci,Cmax;
				Cu=1;
				Ci=sqrt((float)sigmagray)/gray;
				//Ci=sigmagray/gray;
				Cmax=(float)1.732;
				float w=-(1-pow((float)Cu,2)/pow((float)Ci,2))/(1+pow((float)Cu,2));
				if(flag==0)
					gray=gray*w+pData[i*LineBytes+j]*(1-w);
				else if(flag==1)
				{
					if(Ci<Cu)
					{
						gray=gray;
					}
					else if(Ci>=Cu&&Ci<=Cmax)
					{
						gray=gray*w+pData[i*LineBytes+j]*(1-w);
					}
					else if(Ci>Cmax)
					{
						gray=pData[i*LineBytes+j];
					}
				}
				pDataN[i*LineBytes+j]=min(255,max(gray,0));
				gray=0;sigmagray=0;
			}
			else if(bits==24)
			{
				for(k=-m/2;k<=m/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						r+=pData[(i+k)*LineBytes+3*(j+l)+0];
						g+=pData[(i+k)*LineBytes+3*(j+l)+1];
						b+=pData[(i+k)*LineBytes+3*(j+l)+2];
					}
					r/=(m*n);
					g/=(m*n);
					b/=(m*n);
					pDataN[i*LineBytes+3*j+0]=min(255,max(r,0));
					pDataN[i*LineBytes+3*j+1]=min(255,max(g,0));
					pDataN[i*LineBytes+3*j+2]=min(255,max(b,0));
					r=g=b=0;
			}
		}
	}
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

HDIB CPointTrans::FrostFilter(HDIB HOld, int m, int n)
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	int i,j,k,l;
	i=j=k=l=0;
	double gray,r,g,b;//定义均值
	double sigmagray,sigmar,sigmag,sigmab;//定义方差
	gray=r=g=b=0;sigmagray=sigmar=sigmag=sigmab=0;
	AfxGetApp()->DoWaitCursor(1);//same as BeginWaitCursor
	for (i=m/2;i<Height-m/2;i++)
	{
		AfxGetApp()->DoWaitCursor(0);//same as RestoreWaitCursor
		for (j=n/2;j<Width-n/2;j++)	
		{	
			if(bits==8)
			{
				for(k=-m/2;k<=m/2;k++)//计算均值
					for(l=-n/2;l<=n/2;l++)
						gray+=pData[(i+k)*LineBytes+j+l];
					gray/=(m*n);
				for(k=-m/2;k<=m/2;k++)//计算方差
					for(l=-n/2;l<=n/2;l++)
						sigmagray+=(pData[(i+k)*LineBytes+j+l]-gray)*(pData[(i+k)*LineBytes+j+l]-gray);
					sigmagray/=(m*n);
					//计算权值
					double A=sigmagray/gray/gray;
					double *T=new double[m*n];
				for(k=0;k<m;k++)
					for(l=0;l<n;l++)
					{
						T[k*n+l]=sqrt((float)pow((float)k,2)+pow((float)l,2));
						T[k*n+l]=exp(-A*T[k*n+l]);
					}
				double MG=0,M=0,G=0;
				for(k=-m/2;k<=m/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						MG+=pData[(i+k)*LineBytes+j+l]*T[(k+m/2)*n+l+n/2];
						M+=T[(k+m/2)*n+l+n/2];
					}
				if(M!=0)
				{
					G=MG/M;
					pDataN[i*LineBytes+j]=min(255,max(G,0));
				}
				else
					pDataN[i*LineBytes+j]=min(255,max(gray,0));
				delete []T;
				gray=0;sigmagray=0;
			}
			else if(bits==24)
			{
				for(k=-m/2;k<=m/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						r+=pData[(i+k)*LineBytes+3*(j+l)+0];
						g+=pData[(i+k)*LineBytes+3*(j+l)+1];
						b+=pData[(i+k)*LineBytes+3*(j+l)+2];
					}
					r/=(m*n);
					g/=(m*n);
					b/=(m*n);
					pDataN[i*LineBytes+3*j+0]=min(255,max(r,0));
					pDataN[i*LineBytes+3*j+1]=min(255,max(g,0));
					pDataN[i*LineBytes+3*j+2]=min(255,max(b,0));
					r=g=b=0;
			}
		}
	}
	AfxGetApp()->DoWaitCursor(-1);//same as EndWaitCursor
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

HDIB CPointTrans::SigmaFilter(HDIB HOld, int m, int n)
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	int i,j,k,l;
	i=j=k=l=0;
	double gray,r,g,b;//定义均值
	double sigmagray,sigmar,sigmag,sigmab;//定义方差
	gray=r=g=b=0;sigmagray=sigmar=sigmag=sigmab=0;
	AfxGetApp()->DoWaitCursor(1);
	//BeginWaitCursor();
	for (i=m/2;i<Height-m/2;i++)
	{
		for (j=n/2;j<Width-n/2;j++)	
		{	
			if(bits==8)
			{
				for(k=-m/2;k<=m/2;k++)//计算均值
					for(l=-n/2;l<=n/2;l++)
						gray+=pData[(i+k)*LineBytes+j+l];
					gray/=(m*n);
				for(k=-m/2;k<=m/2;k++)//计算方差
					for(l=-n/2;l<=n/2;l++)
						sigmagray+=(pData[(i+k)*LineBytes+j+l]-gray)*(pData[(i+k)*LineBytes+j+l]-gray);
				sigmagray/=(m*n);
				//计算权值
				float sigmaf=sqrt((float)sigmagray)/gray;
				float a=gray*2*sigmaf;
				int *delta=new int[m*n];
				for(k=0;k<m;k++)
					for(l=0;l<n;l++)
					{
						if(pData[(i+k-m/2)*LineBytes+j+l-n/2]>=gray-a&&pData[(i+k-m/2)*LineBytes+j+l-n/2]<=gray+a)
							delta[k*n+l]=1;
						else
							delta[k*n+l]=0;
					}
					float R1=0,R2=0,R;
					for(k=-m/2;k<=m/2;k++)
						for(l=-n/2;l<=n/2;l++)
						{
							R1+=pData[(i+k)*LineBytes+j+l]*delta[(k+m/2)*n+l+n/2];
							R2+=delta[(k+m/2)*n+l+n/2];
						}
						if(R2!=0)
						{
							R=R1/R2;
							pDataN[i*LineBytes+j]=(BYTE)min(255,max(R,0));
						}
						else
							pDataN[i*LineBytes+j]=(BYTE)min(255,max(gray,0));
						delete []delta;//注意释放内存，否则会产生难以想象的内存增长
						gray=0;sigmagray=0;
			}
			else if(bits==24)
			{
				for(k=-m/2;k<=m/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						r+=pData[(i+k)*LineBytes+3*(j+l)+0];
						g+=pData[(i+k)*LineBytes+3*(j+l)+1];
						b+=pData[(i+k)*LineBytes+3*(j+l)+2];
					}
					r/=(m*n);
					g/=(m*n);
					b/=(m*n);
					pDataN[i*LineBytes+3*j+0]=min(255,max(r,0));
					pDataN[i*LineBytes+3*j+1]=min(255,max(g,0));
					pDataN[i*LineBytes+3*j+2]=min(255,max(b,0));
					r=g=b=0;
			}
		}
	}
	//EndWaitCursor();
	AfxGetApp()->DoWaitCursor(-1);
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

HDIB CPointTrans::MAPFilter(HDIB HOld, int m, int n)
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40;
	}
	int i,j,k,l;
	i=j=k=l=0;
	double gray,r,g,b;//定义均值
	double sigmagray,sigmar,sigmag,sigmab;//定义方差
	gray=r=g=b=0;sigmagray=sigmar=sigmag=sigmab=0;
	for (i=m/2;i<Height-m/2;i++)
	{
		for (j=n/2;j<Width-n/2;j++)	
		{	
			if(bits==8)
			{
				for(k=-m/2;k<=m/2;k++)//计算均值
				{
					for(l=-n/2;l<=n/2;l++)
						gray+=pData[(i+k)*LineBytes+j+l];
				}
				gray/=(m*n);
				for(k=-m/2;k<=m/2;k++)//计算方差
				{
					for(l=-n/2;l<=n/2;l++)
						sigmagray+=(pData[(i+k)*LineBytes+j+l]-gray)*(pData[(i+k)*LineBytes+j+l]-gray);
				}
				sigmagray/=(m*n);
				float Cu,Ci,Cmax;
				Cu=1;Ci=sigmagray/gray;Cmax=(float)1.732;
				float alpha=(1+pow((float)Cu,2))/(pow((float)Ci,2)-pow((float)Cu,2));
				if(Ci<Cu)
				{
					gray=gray;
				}
				else if(Ci>=Cu&&Ci<=Cmax)
				{
					float fenzi,fenmu;
					fenzi=gray*(alpha-1-1)+sqrt((float)pow((float)gray,2)*pow((float)alpha-1-1,2)+4*alpha*1*gray*pData[i*LineBytes+j]);
					fenmu=2*alpha;
					gray=fenzi/fenmu;
				}
				else if(Ci>Cmax)
				{
					gray=pData[i*LineBytes+j];
				}
				pDataN[i*LineBytes+j]=min(255,max(gray,0));
				gray=0;sigmagray=0;
			}
			else if(bits==24)
			{
				for(k=-m/2;k<=m/2;k++)
					for(l=-n/2;l<=n/2;l++)
					{
						r+=pData[(i+k)*LineBytes+3*(j+l)+0];
						g+=pData[(i+k)*LineBytes+3*(j+l)+1];
						b+=pData[(i+k)*LineBytes+3*(j+l)+2];
					}
					r/=(m*n);
					g/=(m*n);
					b/=(m*n);
					pDataN[i*LineBytes+3*j+0]=min(255,max(r,0));
					pDataN[i*LineBytes+3*j+1]=min(255,max(g,0));
					pDataN[i*LineBytes+3*j+2]=min(255,max(b,0));
					r=g=b=0;
			}
		}
	}
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}

HDIB CPointTrans::EPOSFilter(HDIB HOld,int n)
{
	if(HOld==NULL)
	{
		AfxMessageBox("请先打开图像");
		return 0;
	}
	LPSTR pDb=(LPSTR)LocalLock(HOld);
	LONG Width=DIBWidth(pDb);
	LONG Height=DIBHeight(pDb);
    LPBYTE pData=(LPBYTE)FindDIBBits (pDb);
	DWORD bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	LONG LineBytes=(Width*bits+31)/32*4;
	HDIB HNew;LPSTR pDbN;LPBYTE pDataN;
	if(bits==8)
	{
		HNew=(HDIB)LocalAlloc(LMEM_MOVEABLE,40+256*4+LineBytes*Height);
		pDbN=(LPSTR)LocalLock(HNew);
		memcpy(pDbN,pDb,40+256*4+LineBytes*Height);
		pDataN=(LPBYTE)pDbN+40+256*4;
	}
	else if(bits==24)//只处理灰度图像，不处理彩色图像
		return HOld;
	int i,j,k,l;
	i=j=k=l=0;
	double gray;//定义均值
	double sigmagray;//定义方差
	gray=0;sigmagray=0;
	AfxGetApp()->DoWaitCursor(1);
	for (i=n/2;i<Height-n/2;i++)
	{
		for (j=n/2;j<Width-n/2;j++)	
		{	
			int z=0,KMax;
			for(int m=n;m>=3;m-=2)//窗口缩小循环,m为窗口大小
			{
				for(k=-m/2;k<=m/2;k++)//计算均值
				{
					for(l=-m/2;l<=m/2;l++)
						gray+=pData[(i+k)*LineBytes+j+l];
				}
				gray/=(m*m);
				for(k=-m/2;k<=m/2;k++)//计算方差
				{
					for(l=-m/2;l<=m/2;l++)
						sigmagray+=(pData[(i+k)*LineBytes+j+l]-gray)*(pData[(i+k)*LineBytes+j+l]-gray);
				}
				sigmagray/=(m*m);
				float yuzhi=(float)(0.5227*0.5227);
				if(sigmagray<yuzhi*gray*gray||m<=3)
				{
					pDataN[i*LineBytes+j]=min(255,max(gray,0));//赋值跳出窗口缩小循环
					break;
				}
				//下面计算八块区域的均值和方差
				float avg[8]={0},std[8]={0};
				///////////////////////
				for(k=-m/2+1;k<1;k++)
				{for(l=-m/2;l<k;l++)
				avg[0]+=pData[(i+k)*LineBytes+j+l];}
				avg[0]=avg[0]/m/m*8;
				for(k=-m/2;k<0;k++)
				{for(l=k;l<0;l++)
				std[0]+=pow((float)pData[(i+k)*LineBytes+j+l]-avg[0],2);}
				std[0]=std[0]/m/m*8;
				///////////////////////
				for(k=-m/2;k<0;k++)
				{for(l=k;l<0;l++)
				avg[1]+=pData[(i+k)*LineBytes+j+l];}
				avg[1]=avg[1]/m/m*8;
				for(k=-m/2;k<0;k++)
				{for(l=k;l<0;l++)
				std[1]+=pow((float)pData[(i+k)*LineBytes+j+l]-avg[1],2);}
				std[1]=std[1]/m/m*8;
				///////////////////////
				for(k=-m/2;k<0;k++)
				{for(l=0;l<-k;l++)
				avg[2]+=pData[(i+k)*LineBytes+j+l];}
				avg[2]=avg[2]/m/m*8;
				for(k=-m/2;k<0;k++)
				{for(l=0;l<-k;l++)
				std[2]+=pow((float)pData[(i+k)*LineBytes+j+l]-avg[2],2);}
				std[2]=std[2]/m/m*8;
				///////////////////////
				for(k=-m/2;k<0;k++)
				{for(l=-k;l<m/2+1;l++)
				avg[3]+=pData[(i+k)*LineBytes+j+l];}
				avg[3]=avg[3]/m/m*8;
				for(k=-m/2;k<0;k++)
				{for(l=-k;l<m/2+1;l++)
				std[3]+=pow((float)pData[(i+k)*LineBytes+j+l]-avg[3],2);}
				std[3]=std[3]/m/m*8;
				///////////////////////
				for(k=0;k<m/2;k++)
				{for(l=k+1;l<m/2+1;l++)
				avg[4]+=pData[(i+k)*LineBytes+j+l];}
				avg[4]=avg[4]/m/m*8;
				for(k=0;k<m/2;k++)
				{for(l=k;l<m/2+1;l++)
				std[4]+=pow((float)pData[(i+k)*LineBytes+j+l]-avg[4],2);}
				std[4]=std[4]/m/m*8;
				///////////////////////
				for(k=1;k<m/2+1;k++)
				{for(l=1;l<k+1;l++)
				avg[5]+=pData[(i+k)*LineBytes+j+l];}
				avg[5]=avg[5]/m/m*8;
				for(k=1;k<m/2+1;k++)
				{for(l=1;l<k+1;l++)
				std[5]+=pow((float)pData[(i+k)*LineBytes+j+l]-avg[5],2);}
				std[5]=std[5]/m/m*8;
				///////////////////////
				for(k=1;k<m/2+1;k++)
				{for(l=1-k;l<1;l++)
				avg[6]+=pData[(i+k)*LineBytes+j+l];}
				avg[6]=avg[6]/m/m*8;
				for(k=1;k<m/2+1;k++)
				{for(l=1-k;l<1;l++)
				std[6]+=pow((float)pData[(i+k)*LineBytes+j+l]-avg[6],2);}
				std[6]=std[6]/m/m*8;
				///////////////////////
				for(k=1;k<m/2+1;k++)
				{for(l=-m/2;l<1-k;l++)
				avg[7]+=pData[(i+k)*LineBytes+j+l];}
				avg[7]=avg[7]/m/m*8;
				for(k=1;k<m/2+1;k++)
				{for(l=-m/2;l<1-k;l++)
				std[7]+=pow((float)pData[(i+k)*LineBytes+j+l]-avg[7],2);}
				std[7]=std[7]/m/m*8;
				int K[7]={0};//记录方差大小顺序
				while(z<7)//执行区域删减循环
				{
					float stdMax=0,stdMin=65535;
					//计算方差最大最小
					for(k=0;k<8;k++)
					{
						for(l=0;l<z;l++)
						{
							if(std[k]>stdMax&&k!=K[l])
								stdMax=std[k],KMax=k;
							if(std[k]<stdMin)
								stdMin=std[k];
						}
					}
					if(stdMin<=yuzhi*gray*gray)
						break;//跳出进入缩小窗口循环
					//////////////////计算删减后总保留区均值
					K[z++]=KMax;
					gray=0;
					int count=0;
					for(k=0;k<z;k++)
						for(l=0;l<8;l++)
						{
							if(k!=K[k])
								gray+=avg[k];
							count++;
						}
					gray/=count;
					///////////////计算删减后总保留方差
					float d[8]={0};
					///////////////////////
					for(k=-m/2;k<0;k++)
					{for(l=k;l<0;l++)
					d[0]+=pow((float)pData[(i+k)*LineBytes+j+l]-gray,2);}
					d[0]=d[0]/m/m*8;
					///////////////////////
					for(k=-m/2;k<0;k++)
					{for(l=k;l<0;l++)
					d[1]+=pow((float)pData[(i+k)*LineBytes+j+l]-gray,2);}
					d[1]=d[1]/m/m*8;
					///////////////////////
					for(k=-m/2;k<0;k++)
					{for(l=0;l<-k;l++)
					d[2]+=pow((float)pData[(i+k)*LineBytes+j+l]-gray,2);}
					d[2]=d[2]/m/m*8;
					///////////////////////
					for(k=-m/2;k<0;k++)
					{for(l=-k;l<m/2+1;l++)
					d[3]+=pow((float)pData[(i+k)*LineBytes+j+l]-gray,2);}
					d[3]=d[3]/m/m*8;
					///////////////////////
					for(k=0;k<m/2;k++)
					{for(l=k;l<m/2+1;l++)
					d[4]+=pow((float)pData[(i+k)*LineBytes+j+l]-gray,2);}
					d[4]=d[4]/m/m*8;
					///////////////////////
					for(k=1;k<m/2+1;k++)
					{for(l=1;l<k+1;l++)
					d[5]+=pow((float)pData[(i+k)*LineBytes+j+l]-gray,2);}
					d[5]=d[5]/m/m*8;
					///////////////////////
					for(k=1;k<m/2+1;k++)
					{for(l=1-k;l<1;l++)
					d[6]+=pow((float)pData[(i+k)*LineBytes+j+l]-gray,2);}
					d[6]=d[6]/m/m*8;
					///////////////////////
					for(k=1;k<m/2+1;k++)
					{for(l=-m/2;l<1-k;l++)
					d[7]+=pow((float)pData[(i+k)*LineBytes+j+l]-gray,2);}
					d[7]=d[7]/m/m*8;

					sigmagray=0;
					for(k=0;k<z;k++)
					{
						for(l=0;l<8;l++)
							if(l!=K[k])
								sigmagray+=d[k];
					}
					sigmagray=sigmagray/count;
					if(sigmagray<yuzhi*gray*gray)
					{
						pDataN[i*LineBytes+j]=BYTE(gray+0.5);
						break;
					}
				}
				
			}
			
			gray=0;sigmagray=0;
		}
	}
	AfxGetApp()->DoWaitCursor(-1);
	::LocalUnlock((HLOCAL)HOld);
	::LocalFree((HLOCAL)HOld);
	::LocalUnlock((HLOCAL)HNew);
	return HNew;
}
