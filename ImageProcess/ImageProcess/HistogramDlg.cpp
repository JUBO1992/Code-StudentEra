// HistogramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "HistogramDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramDlg dialog


CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistogramDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHistogramDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	HDB=NULL;bits=0;
}


void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistogramDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialog)
	//{{AFX_MSG_MAP(CHistogramDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistogramDlg message handlers

void CHistogramDlg::HistogramEqual(HDIB hdb)
{
	LPSTR pDb=(LPSTR)LocalLock(hdb);
	int Width=DIBWidth(pDb);
	int Height=DIBHeight(pDb);
	int bits=((BITMAPINFOHEADER*)pDb)->biBitCount;
	int LineBytes=(Width*bits+31)/32*4;
	LPBYTE pData=(LPBYTE)FindDIBBits(pDb);	
	int i,j,k;
	int nBandsShow=bits/8;
	for(k=0;k<nBandsShow;k++)//逐波段进行处理，对于灰度图像只有一个波段，即nBandsShow=1
	{
		int r[256]={0};
		int nMaxPixel=0;
		for(i=0;i<Height;i++)// 计算图像最大灰度级
		{
			for(j=0;j<Width;j++)
			{
				if(nBandsShow==1)
				{
					if(pData[i*LineBytes+j]>nMaxPixel)
						nMaxPixel=pData[i*LineBytes+j];
				}
				else if(nBandsShow==3)
				{
					if(pData[i*LineBytes+3*j+k]>nMaxPixel)
						nMaxPixel=pData[i*LineBytes+j];
				}
			} 
		}
		nMaxPixel=(nMaxPixel+1<256)?256:nMaxPixel+1;
		for(i=0;i<Height;i++)
		{
			for(j=0;j<Width;j++)
			{
				if(nBandsShow==1)
					r[(int)(pData[i*LineBytes+j]*256/nMaxPixel)]+=1;
				else if(nBandsShow==3)
					r[(int)(pData[i*LineBytes+3*j+k]*256/nMaxPixel)]+=1;
			}
		}		
		double percentile[256];
		for(i=0;i<256;i++)//计算均衡后各亮度的新值
		{
			percentile[i]=0.0;
			for(j=0;j<=i;j++)
				percentile[i]+=r[j];
			percentile[i]*=(255.0/(double)(Width*Height));
		}	 
		for(i=0;i<Height;i++)
		{
			for(j=0;j<Width;j++)
			{
				if(nBandsShow==1)
					pData[i*LineBytes+j]=(unsigned char)percentile[(int)pData[i*LineBytes+j]*256/nMaxPixel];
				else if(nBandsShow==3)
					pData[i*LineBytes+3*j+k]=(unsigned char)percentile[(int)pData[i*LineBytes+3*j+k]*256/nMaxPixel];
			}
		}
	}
}

void CHistogramDlg::OnPaint() 
{	
	if(bits==8)
		PaintGray();
	else if(bits==24)
	{
		PaintR();
		PaintG();
		PaintB();
	}
}

void CHistogramDlg::PaintGray()
{
	CRect rect;
	CWnd *pwnd;
	pwnd=GetDlgItem(IDC_GRAY_HIST);// IDC_GRAY_HIST是我们在对话框中添加的图片控件的ID号
	pwnd->GetClientRect(&rect);
	int i;
	CClientDC dc(pwnd);//注意
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *pPenOld;
	pPenOld=dc.SelectObject(&PenNew);
	int d=-1;
	dc.MoveTo(0,rect.Height()+d);
	dc.LineTo (rect.Width (),rect.Height ()+d);
	dc.MoveTo (0,rect.Height ()+d);
	dc.LineTo (0,0);
	for (i=0;i<256;i++)
	{
		dc.MoveTo(i+1,rect.Height ()+d);
		dc.LineTo(i+1,(rect.Height ()-(int)(GrayRatio[i]*2500))+d);
		//乘以2500是为了增强显示效果其中的num[i]存放的是图像各个灰度级出现的概率
	}
	dc.SelectObject(pPenOld);
	PenNew.DeleteObject();
}

void CHistogramDlg::PaintR()
{
	CRect rect;
	CWnd *pwnd;
	pwnd=GetDlgItem(IDC_R_HIST);// IDC_GRAY_HIST是我们在对话框中添加的图片控件的ID号
	pwnd->GetClientRect(&rect);
	int i;
	CClientDC dc(pwnd);//注意
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *pPenOld;
	pPenOld=dc.SelectObject(&PenNew);
	int d=-1;
	dc.MoveTo(0,rect.Height()+d);
	dc.LineTo (rect.Width (),rect.Height ()+d);
	dc.MoveTo (0,rect.Height ()+d);
	dc.LineTo (0,0);
	for (i=0;i<256;i++)
	{
		dc.MoveTo(i+1,rect.Height ()+d);
		dc.LineTo(i+1,(rect.Height ()-(int)(RRatio[i]*2500))+d);
		//乘以2500是为了增强显示效果其中的num[i]存放的是图像各个灰度级出现的概率
	}
	dc.SelectObject(pPenOld);
	PenNew.DeleteObject();
}

void CHistogramDlg::PaintG()
{
	CRect rect;
	CWnd *pwnd;
	pwnd=GetDlgItem(IDC_G_HIST);// IDC_GRAY_HIST是我们在对话框中添加的图片控件的ID号
	pwnd->GetClientRect(&rect);
	int i;
	CClientDC dc(pwnd);//注意
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *pPenOld;
	pPenOld=dc.SelectObject(&PenNew);
	int d=-1;
	dc.MoveTo(0,rect.Height()+d);
	dc.LineTo (rect.Width (),rect.Height ()+d);
	dc.MoveTo (0,rect.Height ()+d);
	dc.LineTo (0,0);
	for (i=0;i<256;i++)
	{
		dc.MoveTo(i+1,rect.Height ()+d);
		dc.LineTo(i+1,(rect.Height ()-(int)(GRatio[i]*2500))+d);
		//乘以2500是为了增强显示效果其中的num[i]存放的是图像各个灰度级出现的概率
	}
	dc.SelectObject(pPenOld);
	PenNew.DeleteObject();
}

void CHistogramDlg::PaintB()
{
	CRect rect;
	CWnd *pwnd;
	pwnd=GetDlgItem(IDC_B_HIST);// IDC_GRAY_HIST是我们在对话框中添加的图片控件的ID号
	pwnd->GetClientRect(&rect);
	int i;
	CClientDC dc(pwnd);//注意
	CPen PenNew;
	PenNew.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *pPenOld;
	pPenOld=dc.SelectObject(&PenNew);
	int d=-1;
	dc.MoveTo(0,rect.Height()+d);
	dc.LineTo (rect.Width (),rect.Height ()+d);
	dc.MoveTo (0,rect.Height ()+d);
	dc.LineTo (0,0);
	for (i=0;i<256;i++)
	{
		dc.MoveTo(i+1,rect.Height ()+d);
		dc.LineTo(i+1,(rect.Height ()-(int)(BRatio[i]*2500))+d);
		//乘以2500是为了增强显示效果其中的num[i]存放的是图像各个灰度级出现的概率
	}
	dc.SelectObject(pPenOld);
	PenNew.DeleteObject();
}
