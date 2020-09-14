// GlobeLightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "2010302590054.h"
#include "GlobeLightDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlobeLightDlg dialog


CGlobeLightDlg::CGlobeLightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGlobeLightDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGlobeLightDlg)
	m_lightX = 0;
	m_colorR = 0;
	m_colorG = 0;
	m_colorB = 0;
	m_lightY = 0;
	m_lightZ = 0;
	m_R = 0;
	m_man = 0.0;
	m_jing = 0.0;
	m_hjgq = 0.0;
	m_gdgq = 0.0;
	m_tt = 0;
	//}}AFX_DATA_INIT
}


void CGlobeLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGlobeLightDlg)
	DDX_Text(pDX, IDC_EDIT1, m_lightX);
	DDX_Text(pDX, IDC_EDIT10, m_colorR);
	DDX_Text(pDX, IDC_EDIT11, m_colorG);
	DDX_Text(pDX, IDC_EDIT12, m_colorB);
	DDX_Text(pDX, IDC_EDIT2, m_lightY);
	DDX_Text(pDX, IDC_EDIT3, m_lightZ);
	DDX_Text(pDX, IDC_EDIT4, m_R);
	DDX_Text(pDX, IDC_EDIT5, m_man);
	DDX_Text(pDX, IDC_EDIT6, m_jing);
	DDX_Text(pDX, IDC_EDIT7, m_hjgq);
	DDX_Text(pDX, IDC_EDIT8, m_gdgq);
	DDX_Text(pDX, IDC_EDIT9, m_tt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGlobeLightDlg, CDialog)
	//{{AFX_MSG_MAP(CGlobeLightDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobeLightDlg message handlers

void CGlobeLightDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CWnd *pWnd=GetDlgItem(IDC_DRAW);
	pWnd->UpdateWindow();
	Draw();
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CGlobeLightDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_R=50;
	m_lightX=100;
	m_lightY=0;
	m_lightZ=95;
	m_man=0.6;
	m_jing=0.8;
	m_hjgq=0.3;
	m_gdgq=0.9;
	m_colorR=50;
	m_colorG=50;
	m_colorB=50;
	m_tt=135;
	UpdateData(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGlobeLightDlg::Draw()
{

	CWnd *pWnd=GetDlgItem(IDC_DRAW);
	pWnd->UpdateWindow();
	CDC *pDC=pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(rect);
	CBrush brush(RGB(127,127,200));
	CBrush *oldbrush=pDC->SelectObject(&brush);

	pDC->Rectangle(rect);
	pDC->SelectObject(oldbrush);
	brush.DeleteObject();

	POINT p;
	p=rect.CenterPoint();
	int t1,t2,t3;
	for(int k=0;k<=m_R;k+=2)
		for(int i=-m_R;i<=m_R;i+=2)
			for(int j=-m_R;j<=m_R;j++)
			{
				t1=(int)(m_colorR+guangqiang(i,j,k));
				t2=(int)(m_colorG+guangqiang(i,j,k));
				t3=(int)(m_colorB+guangqiang(i,j,k));

				if(t1>255)t1=255;
				if(t2>255)t2=255;
				if(t3>255)t3=255;

				pDC->SetPixel((int)(i*m_R/sqrt((double)i*i+j*j+k*k))+p.x,
					(int)(j*m_R/sqrt((double)i*i+j*j+k*k))+p.y,
         			RGB(t1,t2,t3));
			}
	ReleaseDC(pDC);
}

double CGlobeLightDlg::CalculateCos(int a,int b,int c)
{
	double x,xn,yn,zn;
	xn=a*60/sqrt((double)a*a+b*b+c*c);
	yn=b*60/sqrt((double)a*a+b*b+c*c);
	zn=c*60/sqrt((double)a*a+b*b+c*c);
	x=(double)((m_lightX-xn)*xn+(m_lightY-yn)*yn+(m_lightZ-zn)*zn)/(sqrt(xn*xn+yn*yn+zn*zn)*sqrt((m_lightX-xn)*(m_lightX-xn)+
		(m_lightY-yn)*(m_lightY-yn)+(m_lightZ-zn)*(m_lightZ-zn)));
	if (x<0)x=0;
	return x;
}

double CGlobeLightDlg::CalculateCosi(int a,int b,int c)
{
	double x,xn,yn,zn;
	xn=a*60/sqrt((double)a*a+b*b+c*c);
	yn=b*60/sqrt((double)a*a+b*b+c*c);
	zn=c*60/sqrt((double)a*a+b*b+c*c);
	x=(double)((m_lightX+0-2*xn)*xn+(m_lightY+0-2*yn)*yn+(m_lightZ+90-2*zn)*zn)/(sqrt((m_lightX+0-2*xn)*(m_lightX+0-2*xn)
		+(m_lightY+0-2*yn)*(m_lightY+0-2*yn)+(m_lightZ+90-2*zn)*(m_lightZ+90-2*zn))*sqrt(xn*xn+yn*yn+zn*zn));
	if (x<0)x=0;
	return x;
}

double CGlobeLightDlg::guangqiang(int a,int b,int c)
{
	double x;
	x=m_man*m_hjgq*m_tt+m_man*m_gdgq*m_tt*CalculateCos(a,b,c)+
		m_jing*m_gdgq*m_tt*CalculateCosi(a,b,c)*CalculateCosi(a,b,c)*CalculateCosi(a,b,c);
	if (x>255)x=255;
	return x;
}

void CGlobeLightDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Draw();
}

void CGlobeLightDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	OnInitDialog();
	Draw();
}
