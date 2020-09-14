// CubeSpinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "2010302590054.h"
#include "CubeSpinDlg.h"

#define  DU 3.14159/180
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCubeSpinDlg dialog


CCubeSpinDlg::CCubeSpinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCubeSpinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCubeSpinDlg)
	//}}AFX_DATA_INIT
}


void CCubeSpinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCubeSpinDlg)
	DDX_Control(pDX, IDC_SCROLLBAR3, m_Scroll3);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_Scroll2);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_Scroll1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCubeSpinDlg, CDialog)
	//{{AFX_MSG_MAP(CCubeSpinDlg)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCubeSpinDlg message handlers
void CCubeSpinDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CWnd *pWnd=GetDlgItem(IDC_DRAW);
	pWnd->UpdateWindow();
	Draw();
}

void CCubeSpinDlg::Draw()
{
	CWnd *pWnd=GetDlgItem(IDC_DRAW);
	pWnd->UpdateWindow();
	CDC *pDC=pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(rect);
	int cx=(int)((rect.right-rect.left)/2);
	int cy=(int)((rect.bottom-rect.top)/2);

	D v[8]={
		{-50,-50,50},{-50,50,50},{50,50,50},{50,-50,50},{-50,-50,-50},{-50,50,-50},{50,50,-50},{50,-50,-50}
	},d[8];
	
	POINT p0[4],p1[4],p2[4],p3[4],p4[4],p5[4],w[8];
	int z[8];
	
	for (int i=0; i<8; i++)
	{		

		d[i].x=v[i].x;
		d[i].y=(int)(v[i].y*cos(a*DU)-v[i].z*sin(a*DU));
		d[i].z=(int)(v[i].y*sin(a*DU)+v[i].z*cos(a*DU));

		v[i].x=(int)(d[i].x*cos(b*DU)+d[i].z*sin(b*DU));
  	    v[i].y=d[i].y;
		v[i].z=(int)(d[i].z*cos(b*DU)-d[i].x*sin(b*DU));
		
		d[i].x=(int)(v[i].x*cos(c*DU)-v[i].y*sin(c*DU));
	    d[i].y=(int)(v[i].x*sin(c*DU)+v[i].y*cos(c*DU));
		d[i].z=v[i].z;
		
		w[i].x=d[i].x+cx;
		w[i].y=d[i].y+cy;
		z[i]=d[i].z;
	}

	p0[0]=w[0];p0[1]=w[1];p0[2]=w[2];p0[3]=w[3];
	p1[0]=w[4];p1[1]=w[5];p1[2]=w[6];p1[3]=w[7];
    p2[0]=w[0];p2[1]=w[1];p2[2]=w[5];p2[3]=w[4];
	p3[0]=w[1];p3[1]=w[2];p3[2]=w[6];p3[3]=w[5];
	p4[0]=w[2];p4[1]=w[3];p4[2]=w[7];p4[3]=w[6];
	p5[0]=w[0];p5[1]=w[3];p5[2]=w[7];p5[3]=w[4];
	switch (Maxnum(z,7))
	{
		case 0:fill(p0,p2,p5,0,2,5);break;
		case 1:fill(p0,p2,p3,0,2,3);break;
		case 2:fill(p0,p3,p4,0,3,4);break;
		case 3:fill(p0,p4,p5,0,4,5);break;
		case 4:fill(p1,p2,p5,1,2,5);break;
		case 5:fill(p1,p2,p3,1,2,3);break;
		case 6:fill(p1,p3,p4,1,3,4);break;
		case 7:fill(p1,p4,p5,1,4,5);break;
	}
}
int CCubeSpinDlg::Maxnum(int *p, int n)
{
	int max=p[0];
	int x;
	for (int i=0; i<=n;i++)
	{		
		if (max<=p[i])
		{	
			max=p[i];
			x=i;
		}
	}
	return x;
}

void CCubeSpinDlg::fill(POINT *x, POINT *y, POINT *z, int i,int j,int q)
{
	CWnd *pWnd=GetDlgItem(IDC_DRAW);
	pWnd->UpdateWindow();
	CDC  *pDC=pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(rect);

	CDC dcmem;
	dcmem.CreateCompatibleDC(pDC);
	CBitmap bmp,*oldbmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	oldbmp=dcmem.SelectObject(&bmp);

	CBrush brush[6];
	brush[0].CreateSolidBrush(RGB(255,255,0));
	brush[1].CreateSolidBrush(RGB(0,255,255));
	brush[2].CreateSolidBrush(RGB(0,255,0));
	brush[3].CreateSolidBrush(RGB(255,0,0));
	brush[4].CreateSolidBrush(RGB(0,0,255));
	brush[5].CreateSolidBrush(RGB(255,0,255));

	CBrush *oldbrush=dcmem.SelectObject(&brush[i]);
	dcmem.FillSolidRect(rect,RGB(255,255,255));
	dcmem.Polygon(x,4);
	dcmem.SelectObject(&brush[j]);
	dcmem.Polygon(y,4);
	dcmem.SelectObject(&brush[q]);
	dcmem.Polygon(z,4);
	dcmem.SelectObject(oldbrush);
	for (int b=0; b<6;b++)
	brush[b].DeleteObject();
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),
		&dcmem,0,0,SRCCOPY);
	dcmem.SelectObject(oldbmp);
	bmp.DeleteObject();
	dcmem.DeleteDC();

}

void CCubeSpinDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nID=pScrollBar->GetDlgCtrlID();
	switch(nID)
	{
	case IDC_SCROLLBAR1: a=pScrollBar->GetScrollPos();
		switch (nSBCode)
		{
		case SB_LINELEFT: a--;break;
		case SB_LINERIGHT: a++;break;
		case SB_PAGELEFT: a-=10;break;
		case SB_PAGERIGHT: a+=10;break;
		case SB_THUMBTRACK: a=nPos;break;
		}
		if (a<-180)a=180;
		if (a>180)a=-180;
		pScrollBar->SetScrollPos(a);
		break;
		case IDC_SCROLLBAR2: b=pScrollBar->GetScrollPos();
			switch (nSBCode)
			{
			case SB_LINELEFT: b--;break;
			case SB_LINERIGHT: b++;break;
			case SB_PAGELEFT: b-=10;break;
			case SB_PAGERIGHT: b+=10;break;
			case SB_THUMBTRACK: b=nPos;break;
			}
			if (b<-180)b=180;
			if (b>180)b=-180;
			pScrollBar->SetScrollPos(b);
			break;
			case IDC_SCROLLBAR3: c=pScrollBar->GetScrollPos();
				switch (nSBCode)
				{
				case SB_LINELEFT: c--;break;
				case SB_LINERIGHT: c++;break;
				case SB_PAGELEFT: c-=10;break;
				case SB_PAGERIGHT: c+=10;break;
				case SB_THUMBTRACK: c=nPos;break;
				}
				if (c<-180)c=180;
				if (c>180)c=-180;
				pScrollBar->SetScrollPos(c);
				break;
	}
	Draw();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CCubeSpinDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Scroll1.SetScrollRange(-180,180);
	m_Scroll1.SetScrollPos(0);
	m_Scroll2.SetScrollRange(-180,180);
	m_Scroll2.SetScrollPos(0);
	m_Scroll3.SetScrollRange(-180,180);
	m_Scroll3.SetScrollPos(0);
	a=b=c=0;
	SetTimer(1,10,NULL);	
	Ctrl=0;
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCubeSpinDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (1==Ctrl)
	{
		CScrollBar *pscrolla=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR1);
		a--;
		if (a<-180)a=180;
		pscrolla->SetScrollPos(a);
		Draw();
	}
	if (2==Ctrl)
	{
		
		CScrollBar *pscrollb=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR2);
		b--;
		if (b<-180)b=180;
		pscrollb->SetScrollPos(b);
		Draw();
	}
	if (3==Ctrl)
	{
		CScrollBar *pscrollc=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR3);
		c--;
		if (c<-180)c=180;
		pscrollc->SetScrollPos(c);
		Draw();
	}
	CDialog::OnTimer(nIDEvent);
}

void CCubeSpinDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	SetTimer(1,10,NULL);
	Ctrl=1;
}

void CCubeSpinDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	SetTimer(1,10,NULL);
	Ctrl=2;
}

void CCubeSpinDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	SetTimer(1,10,NULL);
	Ctrl=3;
}

void CCubeSpinDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
}
