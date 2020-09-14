// 2010302590054Doc.cpp : implementation of the CMy2010302590054Doc class
//

#include "stdafx.h"
#include "2010302590054.h"

#include "2010302590054Doc.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054Doc

IMPLEMENT_DYNCREATE(CMy2010302590054Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy2010302590054Doc, CDocument)
	//{{AFX_MSG_MAP(CMy2010302590054Doc)
	ON_COMMAND(ID_GRAPH_COLOR, OnGraphColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054Doc construction/destruction

CMy2010302590054Doc::CMy2010302590054Doc()
{
	// TODO: add one-time construction code here
    m_crColor=RGB(0,0,255);
	LineWide=1;
}

CMy2010302590054Doc::~CMy2010302590054Doc()
{
}

BOOL CMy2010302590054Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054Doc serialization

void CMy2010302590054Doc::Serialize(CArchive& ar)
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
// CMy2010302590054Doc diagnostics

#ifdef _DEBUG
void CMy2010302590054Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2010302590054Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054Doc commands
void CMy2010302590054Doc::DDALine(CClientDC *DCPoint)
{
/*
	CPen pen(0,0,RGB(0,0,255));
	CPen *pOldPen=DCPoint->SelectObject(&pen);
	DCPoint->SetROP2(R2_COPYPEN);
	DCPoint->MoveTo(group[0]);
	DCPoint->LineTo(group[1]);
	DCPoint->SelectObject(pOldPen);*/
	int x,x0,y0,x1,y1,flag;
	float m,y;
	DCPoint->SetROP2(R2_COPYPEN);
	x0=group[0].x;y0=group[0].y;
	x1=group[1].x;y1=group[1].y;
	if(x0==x1&&y0==y1)return;
	if(x0==x1){
		if(y0>y1){
			x=y0;y0=y1;y1=x;
		}
		for(x=y0;x<=y1;x++)
			DCPoint->SetPixel(x0,x,m_crColor);
		return;
	}
	if(y0==y1){
		if(x0>x1){
			x=x0;x0=x1;x1=x;
		}
		for(x=x0;x<=x1;x++)
			DCPoint->SetPixel(x,y0,m_crColor);
			return;
	}
	if(x0>x1){
		x=x0;x0=x1;x1=x;
		x=y0;y0=y1;y1=x;
	}
	flag=0;
	if(x1-x0>y1-y0&&y1-y0>0)flag=1;
	if(x1-x0>y0-y1&&y0-y1>0){
		flag=2;y0=-y0;y1=-y1;
	}
	if(y1-y0>x1-x0){
		flag=3;x=x0;x0=y0;y0=x;x=x1;x1=y1;y1=x;
	}
	if(y0-y1>x1-x0){
		flag=4;
		y0=-y0,y1=-y1;//以x轴为对称轴
		x=x0;x0=y0;y0=x;x=x1;x1=y1;y1=x;//以y=x为对称轴
	}
	m=(float)(y1-y0)/float(x1-x0);
	for(int i=(int)(-(float)LineWide/2+0.5);i<=LineWide/2;i++)
	for(x=x0,y=(float)y0;x<=x1;x++,y=y+m){
		if(flag==1)DCPoint->SetPixel(x,int(y+0.5)+i,m_crColor);
		if(flag==2)DCPoint->SetPixel(x,-int(y-0.5)+i,m_crColor);
		if(flag==3)DCPoint->SetPixel(int(y+0.5)+i,x,m_crColor);
		if(flag==4)DCPoint->SetPixel(int(y+0.5)+i,-x,m_crColor);
	}
}

void CMy2010302590054Doc::MidpointLine(CClientDC *DCPoint)
{
	int a,b,delta1,delta2,d,x,y;
	DCPoint->SetROP2(R2_COPYPEN);
	int x0,y0,x1,y1,flag;
	x0=group[0].x;y0=group[0].y;
	x1=group[1].x;y1=group[1].y;

	if(x0==x1&&y0==y1)return;
	if(x0==x1){
		if(y0>y1){
			x=y0;y0=y1;y1=x;
		}
		for(x=y0;x<=y1;x++)
			DCPoint->SetPixel(x0,x,m_crColor);
		return;
	}
	if(y0==y1){
		if(x0>x1){
			x=x0;x0=x1;x1=x;
		}
		for(x=x0;x<=x1;x++)
			DCPoint->SetPixel(x,y0,m_crColor);
		return;
	}
	if(x0>x1){
		x=x0;x0=x1;x1=x;
		x=y0;y0=y1;y1=x;
	}
	flag=0;
	if(x1-x0>y1-y0&&y1-y0>0)flag=1;
	if(x1-x0>y0-y1&&y0-y1>0){
		flag=2;y0=-y0;y1=-y1;
	}
	if(y1-y0>x1-x0){
		flag=3;x=x0;x0=y0;y0=x;x=x1;x1=y1;y1=x;
	}
	if(y0-y1>x1-x0){
		flag=4;
		y0=-y0,y1=-y1;//以x轴为对称轴
		x=x0;x0=y0;y0=x;x=x1;x1=y1;y1=x;//以y=x为对称轴
	}
	a=y0-y1;	b=x1-x0;
	d=2*a+b;
	delta1=2*a;	delta2=2*(a+b);
	x=x0;	y=y0;
	DCPoint->SetPixel(x,y,m_crColor);
	while(x<x1){
		if(d<0){
			x++,y++;d+=delta2;
		}
		else{
			x++;d+=delta1;
		}
		for(int i=(int)(-(float)LineWide/2+0.5);i<=LineWide/2;i++)
		{
		if(flag==1)DCPoint->SetPixel(x,int(y+0.5)+i,m_crColor);
		if(flag==2)DCPoint->SetPixel(x,-int(y-0.5)+i,m_crColor);
		if(flag==3)DCPoint->SetPixel(int(y+0.5)+i,x,m_crColor);
		if(flag==4)DCPoint->SetPixel(int(y+0.5)+i,-x,m_crColor);
		}
		}
}

void CMy2010302590054Doc::BLine(CClientDC *DCPoint)
{
	DCPoint->SetROP2(R2_COPYPEN);
	int x0,y0,x1,y1,flag;
	int x,y,dx,dy,e;
	x0=group[0].x;y0=group[0].y;
	x1=group[1].x;y1=group[1].y;
	if(x0==x1&&y0==y1)return;
	if(x0==x1){
		if(y0>y1){
			x=y0;y0=y1;y1=x;
		}
		for(x=y0;x<=y1;x++)
			DCPoint->SetPixel(x0,x,m_crColor);
		return;
	}
	if(y0==y1){
		if(x0>x1){
			x=x0;x0=x1;x1=x;
		}
		for(x=x0;x<=x1;x++)
			DCPoint->SetPixel(x,y0,m_crColor);
		return;
	}
	if(x0>x1){
		x=x0;x0=x1;x1=x;
		x=y0;y0=y1;y1=x;
	}
	flag=0;
	if(x1-x0>y1-y0&&y1-y0>0)flag=1;
	if(x1-x0>y0-y1&&y0-y1>0){
		flag=2;y0=-y0;y1=-y1;
	}
	if(y1-y0>x1-x0){
		flag=3;x=x0;x0=y0;y0=x;x=x1;x1=y1;y1=x;
	}
	if(y0-y1>x1-x0){
		flag=4;
		y0=-y0,y1=-y1;//以x轴为对称轴
		x=x0;x0=y0;y0=x;x=x1;x1=y1;y1=x;//以y=x为对称轴
	}
	dx=x1-x0;
	dy=y1-y0;
	e=-dx;x=x0;y=y0;
	for(int i=0;i<=dx;i++)
	{
//		DCPoint->SetPixel(x,y,m_crColor);
		for(int i=(int)(-(float)LineWide/2+0.5);i<=LineWide/2;i++)
		{
		if(flag==1)DCPoint->SetPixel(x,int(y)+i,m_crColor);
		if(flag==2)DCPoint->SetPixel(x,-int(y)+i,m_crColor);
		if(flag==3)DCPoint->SetPixel(int(y)+i,x,m_crColor);
		if(flag==4)DCPoint->SetPixel(int(y)+i,-x,m_crColor);
		}
		x=x+1;
		e=e+2*dy;
		if(e>=0)
		{
			y=y+1;
			e=e-2*dx;
		}
	}
}

void CMy2010302590054Doc::BCircle(CClientDC*DCPoint,CRect *rc,CPoint p1,CPoint p2)
{
	int r,d,x,y,x0,y0;
//	COLORREF m_crColor=RGB(255,0,0);
	DCPoint->SetROP2(R2_COPYPEN);
	r=(int)sqrt((double)(p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
	for(int i=(int)(-(float)LineWide/2+0.5);i<=LineWide/2;i++)//以线宽LineWide画圆
	{x=0;y=r+i;d=3-2*r;x0=p1.x;y0=p1.y;
	while(x<y||x==y){
		if(rc->PtInRect(CPoint(x+x0,y+y0)))//判断是否在矩形框内
     		DCPoint->SetPixel(x+x0,y+y0,m_crColor);
		if(rc->PtInRect(CPoint(-x+x0,y+y0)))//判断是否在矩形框内
    		DCPoint->SetPixel(-x+x0,y+y0,m_crColor);
		if(rc->PtInRect(CPoint(x+x0,-y+y0)))//判断是否在矩形框内
	    	DCPoint->SetPixel(x+x0,-y+y0,m_crColor);
		if(rc->PtInRect(CPoint(-x+x0,-y+y0)))//判断是否在矩形框内
	    	DCPoint->SetPixel(-x+x0,-y+y0,m_crColor);
		if(rc->PtInRect(CPoint(y+x0,x+y0)))//判断是否在矩形框内
	     	DCPoint->SetPixel(y+x0,x+y0,m_crColor);
		if(rc->PtInRect(CPoint(-y+x0,x+y0)))//判断是否在矩形框内
	     	DCPoint->SetPixel(-y+x0,x+y0,m_crColor);
		if(rc->PtInRect(CPoint(y+x0,-x+y0)))//判断是否在矩形框内
	     	DCPoint->SetPixel(y+x0,-x+y0,m_crColor);
		if(rc->PtInRect(CPoint(-y+x0,-x+y0)))//判断是否在矩形框内
	    	DCPoint->SetPixel(-y+x0,-x+y0,m_crColor);
		x=x+1;
		if(d<0||d==0){
			d=d+4*x+6;
		}//if
		else{
			y=y-1;d=d+4*(x-y)+10;
		}//else
	}//while
	}//for
}

void CMy2010302590054Doc::BCircle(CClientDC*DCPoint,CPoint p1,CPoint p2)
{
/*
	int r,d,x,y,x0,y0;
	DCPoint->SetROP2(R2_COPYPEN);
	r=(int)sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
	x=0;y=r;d=3-2*r;x0=p1.x;y0=p1.y;
	while(x<y||x==y){
		DCPoint->SetPixel(x+x0,y+y0,m_crColor);
		DCPoint->SetPixel(-x+x0,y+y0,m_crColor);
		DCPoint->SetPixel(x+x0,-y+y0,m_crColor);
		DCPoint->SetPixel(-x+x0,-y+y0,m_crColor);
		DCPoint->SetPixel(y+x0,x+y0,m_crColor);
		DCPoint->SetPixel(-y+x0,x+y0,m_crColor);
		DCPoint->SetPixel(y+x0,-x+y0,m_crColor);
		DCPoint->SetPixel(-y+x0,-x+y0,m_crColor);
		x=x+1;
		if(d<0||d==0){
			d=d+4*x+6;
		}
		else{
			y=y-1;d=d+4*(x-y)+10;
		}
	}*/

	CRect rc(0,0,1366,768);
//	bool a=DCPoint->GetBoundsRect(&rc,0);
	BCircle(DCPoint,&rc,p1,p2);
}

void CMy2010302590054Doc::PNCircle(CClientDC*DCPoint,CPoint p1,CPoint p2)
{
	int r,d,x,y,x0,y0;
	DCPoint->SetROP2(R2_COPYPEN);
	r=(int)sqrt((double)(p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
	for(int i=(int)(-(float)LineWide/2+0.5);i<=LineWide/2;i++)//以线宽LineWide画圆
	{d=0;x0=p1.x;y0=p1.y;x=x0;y=y0+r+i;
	while(y>y0){
		DCPoint->SetPixel(x,y,m_crColor);
		DCPoint->SetPixel(-x+2*x0,y,m_crColor);
		DCPoint->SetPixel(x,-y+2*y0,m_crColor);
		DCPoint->SetPixel(-x+2*x0,-y+2*y0,m_crColor);
		if(d<0){
			x++;d=d+2*(x-x0)+1;
		}
		else{
			y--,d=d-2*(y-y0)+1;
		}
	}//while
	}//for

}

void CMy2010302590054Doc::Bezier(CClientDC*pDC,int mode)
{
	CPoint p[1000];
	int i,j;
	i=0;j=0;
	p[i++]=group[j++];
	p[i++]=group[j++];
	while(j<=PointNum-2){//zhuyi
		p[i++]=group[j++];
		p[i].x=(group[j].x+group[j-1].x)/2;
		p[i++].y=(group[j].y+group[j-1].y)/2;
		p[i++]=group[j++];
	}
	for(j=0;j<i-3;j+=3){
		Bezier_4(pDC,mode,p[j],p[j+1],p[j+2],p[j+3]);
	}
}

void CMy2010302590054Doc::Bezier_4(CClientDC*pDC,int mode,CPoint p1,CPoint p2,CPoint p3,CPoint p4)
{
	int i,n;
	CPoint p;
	double t1,t2,t3,t4,dt;
	CPen pen;
	n=10;
	if(mode)//mode=1时，以异或方式画可擦除的黑色曲线
	{
		pDC->SetROP2(R2_NOT);
		pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	}
	else//mode=0时，画m_crColor色的正式曲线
	{
		pDC->SetROP2(R2_COPYPEN);
		pen.CreatePen(PS_SOLID,LineWide,m_crColor);
	}
	CPen*pOldPen=pDC->SelectObject(&pen);
	dt=1.0/n;
	pDC->MoveTo(p1);
	for(i=1;i<=n;i++){
		t1=(1.0-i*dt)*(1.0-i*dt)*(1.0-i*dt);
		t2=i*dt*(1.0-i*dt)*(1.0-i*dt);
		t3=i*dt*i*dt*(1.0-i*dt);
		t4=i*dt*i*dt*i*dt;
		p.x=(int)(t1*p1.x+3*t2*p2.x+3*t3*p3.x+t4*p4.x);
		p.y=(int)(t1*p1.y+3*t2*p2.y+3*t3*p3.y+t4*p4.y);
		pDC->LineTo(p);
	}
//	pDC->LineTo(p4);
	pDC->SelectObject(pOldPen);
}

void CMy2010302590054Doc::BSample(CClientDC*pDC,int mode)
{
	CPoint p[1000];
	int i,j;
	i=0;j=0;
	p[i++]=group[j++];
	p[i++]=group[j++];
	while(j<=PointNum-2){//zhuyi
		p[i++]=group[j++];
		p[i].x=(group[j].x+group[j-1].x)/2;
		p[i++].y=(group[j].y+group[j-1].y)/2;
		p[i++]=group[j++];
	}
	for(j=0;j<i-3;j+=3){
		BSample_4(pDC,mode,p[j],p[j+1],p[j+2],p[j+3]);
	}
}

void CMy2010302590054Doc::BSample_4(CClientDC*pDC,int mode,CPoint p1,CPoint p2,CPoint p3,CPoint p4)
{

	int i,n;
	CPoint p;
	double t1,t2,t3,t4,dt;
	CPen pen;
	n=100;
	if(mode)//mode=1时，以异或方式画可擦除的黑色曲线
	{
		pDC->SetROP2(R2_NOT);
		pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	}
	else//mode=0时，画m_crColor色的正式曲线
	{
		pDC->SetROP2(R2_COPYPEN);
		pen.CreatePen(PS_SOLID,LineWide,m_crColor);
	}
	CPen*pOldPen=pDC->SelectObject(&pen);
	dt=1.0/n;
	pDC->MoveTo(p1);
	for(i=1;i<=n;i++){
		t1=(-pow(i*dt,3)+3*pow(i*dt,2)-3*i*dt+1)/6;
		t2=(3*pow(i*dt,3)-6*pow(i*dt,2)+4)/6;
		t3=(-3*pow(i*dt,3)+3*pow(i*dt,2)+3*i*dt+1)/6;
		t4=pow(i*dt,3)/6;
		p.x=(int)(t1*p1.x+t2*p2.x+t3*p3.x+t4*p4.x);
		p.y=(int)(t1*p1.y+t2*p2.y+t3*p3.y+t4*p4.y);
		pDC->LineTo(p);
	}
	pDC->LineTo(p4);
	pDC->SelectObject(pOldPen);
}

void CMy2010302590054Doc::OnGraphColor() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg(m_crColor);
	if(dlg.DoModal()==IDOK)
		m_crColor=dlg.GetColor();
}

void CMy2010302590054Doc::GenerateGraph(CClientDC *pDC)//绘图形变换前的原始图形
{
	group[0].x=100;group[0].y=100;
	group[1].x=200;group[1].y=100;
	group[2].x=200;group[2].y=200;
	group[3].x=100;group[3].y=200;
	group[4].x=100;group[4].y=100;
	PointNum=5;
	DrawGraph(pDC);

}

void CMy2010302590054Doc::DrawGraph(CClientDC *pDC)//绘处理后图形
{
	int i;
	CPen pen,*pOldPen;
	pDC->SetROP2(R2_COPYPEN);
	pen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	pOldPen=pDC->SelectObject(&pen);
	pDC->MoveTo(group[0]);
	for(i=1;i<PointNum;i++)
		pDC->LineTo(group[i]);
	pDC->SelectObject(pOldPen);
}

void CMy2010302590054Doc::DrawGraph1(CClientDC *pDC)//绘处理后图形
{
	int i;
	CPen pen,*pOldPen;
	pDC->SetROP2(R2_COPYPEN);
	pen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	pOldPen=pDC->SelectObject(&pen);
	pDC->MoveTo(group[0]);
	for(i=1;i<PointNum;i++)
		pDC->LineTo(group[i]);
	pDC->SelectObject(pOldPen);
}

void CMy2010302590054Doc::TransRotate(CPoint p1,CPoint p2)//旋转、p1为基点、p2用来确定角度
{
	float a[3][3],b[3][3],c[3][3];
	float sa,ca,x,y;
	int i;
	CPoint p=group[0];//p为旋转体上一点
	float l1,l2,l;
	l=(float)(p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y);
	l1=(float)(p.x-p2.x)*(p.x-p2.x)+(p.y-p2.y)*(p.y-p2.y);
	l2=(float)(p.x-p1.x)*(p.x-p1.x)+(p.y-p1.y)*(p.y-p1.y);
	ca=(float)((l2+l-l1)/(2*sqrt(l2*l)));//旋转角的余弦
//	int pp=(p1.y-p.y)/(p1.x-p.x)*(p2.x-p.x)-(p2.y-p.y);
//	if(pp>=0&&p1.x>p.x)
		sa=(float)sqrt(1-ca*ca);
//	else
//		sa=-(float)sqrt(1-ca*ca);
	c[0][0]=1;c[0][1]=0;c[0][2]=(float)-p1.x;//矩阵一，平移矩阵
	c[1][0]=0;c[1][1]=1;c[1][2]=(float)-p1.y;
	c[2][0]=0;c[2][1]=0;c[2][2]=1;
	b[0][0]=ca;b[0][1]=-sa;b[0][2]=0;//矩阵二，旋转矩阵（顺）
	b[1][0]=sa;b[1][1]=ca;b[1][2]=0;
	b[2][0]=0;b[2][1]=0;b[2][2]=1;
	a[0][0]=b[0][0]*c[0][0]+b[0][1]*c[1][0]+b[0][2]*c[2][0];//矩阵一、二合并
	a[0][1]=b[0][0]*c[0][1]+b[0][1]*c[1][1]+b[0][2]*c[2][1];
	a[0][2]=b[0][0]*c[0][2]+b[0][1]*c[1][2]+b[0][2]*c[2][2];
	a[1][0]=b[1][0]*c[0][0]+b[1][1]*c[1][0]+b[1][2]*c[2][0];
	a[1][1]=b[1][0]*c[0][1]+b[1][1]*c[1][1]+b[1][2]*c[2][1];
	a[1][2]=b[1][0]*c[0][2]+b[1][1]*c[1][2]+b[1][2]*c[2][2];
	a[2][0]=b[2][0]*c[0][0]+b[2][1]*c[1][0]+b[2][2]*c[2][0];
	a[2][1]=b[2][0]*c[0][1]+b[2][1]*c[1][1]+b[2][2]*c[2][1];
	a[2][2]=b[2][0]*c[0][2]+b[2][1]*c[1][2]+b[2][2]*c[2][2];
	b[0][0]=1;b[0][1]=0;b[0][2]=(float)p1.x; //矩阵三
	b[1][0]=0;b[1][1]=1;b[1][2]=(float)p1.y;
	b[2][0]=0;b[2][1]=0;b[2][2]=1;
	c[0][0]=b[0][0]*a[0][0]+b[0][1]*a[1][0]+b[0][2]*a[2][0];//所有矩阵合并
	c[0][1]=b[0][0]*a[0][1]+b[0][1]*a[1][1]+b[0][2]*a[2][1];
	c[0][2]=b[0][0]*a[0][2]+b[0][1]*a[1][2]+b[0][2]*a[2][2];
	c[1][0]=b[1][0]*a[0][0]+b[1][1]*a[1][0]+b[1][2]*a[2][0];
	c[1][1]=b[1][0]*a[0][1]+b[1][1]*a[1][1]+b[1][2]*a[2][1];
	c[1][2]=b[1][0]*a[0][2]+b[1][1]*a[1][2]+b[1][2]*a[2][2];
	c[2][0]=b[2][0]*a[0][0]+b[2][1]*a[1][0]+b[2][2]*a[2][0];
	c[2][1]=b[2][0]*a[0][1]+b[2][1]*a[1][1]+b[2][2]*a[2][1];
    c[2][2]=b[2][0]*a[0][2]+b[2][1]*a[1][2]+b[2][2]*a[2][2];
	for(i=0;i<PointNum;i++)
	{
		x=c[0][0]*group[i].x+c[0][1]*group[i].y+c[0][2];
		y=c[1][0]*group[i].x+c[1][1]*group[i].y+c[1][2];
		group[i].x=(long)x;group[i].y=(long)y;
	}
}

void CMy2010302590054Doc::TransZoom(int xx,int yy,float zoomx,float zoomy)
{
	float a[3][3],b[3][3],c[3][3];
	float x,y;
	int i;

	c[0][0]=1;c[0][1]=0;c[0][2]=(float)-xx;//矩阵一，平移矩阵
	c[1][0]=0;c[1][1]=1;c[1][2]=(float)-yy;
	c[2][0]=0;c[2][1]=0;c[2][2]=1;
	b[0][0]=zoomx;b[0][1]=0;b[0][2]=0;//矩阵二，缩放矩阵
	b[1][0]=0;b[1][1]=zoomy;b[1][2]=0;
	b[2][0]=0;b[2][1]=0;b[2][2]=1;
	a[0][0]=b[0][0]*c[0][0]+b[0][1]*c[1][0]+b[0][2]*c[2][0];//矩阵一、二合并
	a[0][1]=b[0][0]*c[0][1]+b[0][1]*c[1][1]+b[0][2]*c[2][1];
	a[0][2]=b[0][0]*c[0][2]+b[0][1]*c[1][2]+b[0][2]*c[2][2];
	a[1][0]=b[1][0]*c[0][0]+b[1][1]*c[1][0]+b[1][2]*c[2][0];
	a[1][1]=b[1][0]*c[0][1]+b[1][1]*c[1][1]+b[1][2]*c[2][1];
	a[1][2]=b[1][0]*c[0][2]+b[1][1]*c[1][2]+b[1][2]*c[2][2];
	a[2][0]=b[2][0]*c[0][0]+b[2][1]*c[1][0]+b[2][2]*c[2][0];
	a[2][1]=b[2][0]*c[0][1]+b[2][1]*c[1][1]+b[2][2]*c[2][1];
	a[2][2]=b[2][0]*c[0][2]+b[2][1]*c[1][2]+b[2][2]*c[2][2];
	b[0][0]=1;b[0][1]=0;b[0][2]=(float)xx; //矩阵三，平移矩阵
	b[1][0]=0;b[1][1]=1;b[1][2]=(float)yy;
	b[2][0]=0;b[2][1]=0;b[2][2]=1;
	c[0][0]=b[0][0]*a[0][0]+b[0][1]*a[1][0]+b[0][2]*a[2][0];//所有矩阵合并
	c[0][1]=b[0][0]*a[0][1]+b[0][1]*a[1][1]+b[0][2]*a[2][1];
	c[0][2]=b[0][0]*a[0][2]+b[0][1]*a[1][2]+b[0][2]*a[2][2];
	c[1][0]=b[1][0]*a[0][0]+b[1][1]*a[1][0]+b[1][2]*a[2][0];
	c[1][1]=b[1][0]*a[0][1]+b[1][1]*a[1][1]+b[1][2]*a[2][1];
	c[1][2]=b[1][0]*a[0][2]+b[1][1]*a[1][2]+b[1][2]*a[2][2];
	c[2][0]=b[2][0]*a[0][0]+b[2][1]*a[1][0]+b[2][2]*a[2][0];
	c[2][1]=b[2][0]*a[0][1]+b[2][1]*a[1][1]+b[2][2]*a[2][1];
    c[2][2]=b[2][0]*a[0][2]+b[2][1]*a[1][2]+b[2][2]*a[2][2];
	for(i=0;i<PointNum;i++)
	{
		x=c[0][0]*group[i].x+c[0][1]*group[i].y+c[0][2];
		y=c[1][0]*group[i].x+c[1][1]*group[i].y+c[1][2];
		group[i].x=(long)x;group[i].y=(long)y;
	}
}

void CMy2010302590054Doc::Symmetry(CPoint p1,CPoint p2)//对称处理
{
	float a[3][3],b[3][3],c[3][3];
	float sa,ca,x,y;
	int i;
	ca=(float)((p2.x-p1.x)/sqrt((double)(p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)));
	sa=(float)((p2.y-p1.y)/sqrt((double)(p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)));
	c[0][0]=1;c[0][1]=0;c[0][2]=(float)-p1.x;
	c[1][0]=0;c[1][1]=1;c[1][2]=(float)-p1.y;
	c[2][0]=0;c[2][1]=0;c[2][2]=1;
	b[0][0]=ca;b[0][1]=sa;b[0][2]=0;
	b[1][0]=-sa;b[1][1]=ca;b[1][2]=0;
	b[2][0]=0;b[2][1]=0;b[2][2]=1;
	a[0][0]=b[0][0]*c[0][0]+b[0][1]*c[1][0]+b[0][2]*c[2][0];
	a[0][1]=b[0][0]*c[0][1]+b[0][1]*c[1][1]+b[0][2]*c[2][1];
	a[0][2]=b[0][0]*c[0][2]+b[0][1]*c[1][2]+b[0][2]*c[2][2];
	a[1][0]=b[1][0]*c[0][0]+b[1][1]*c[1][0]+b[1][2]*c[2][0];
	a[1][1]=b[1][0]*c[0][1]+b[1][1]*c[1][1]+b[1][2]*c[2][1];
	a[1][2]=b[1][0]*c[0][2]+b[1][1]*c[1][2]+b[1][2]*c[2][2];
	a[2][0]=b[2][0]*c[0][0]+b[2][1]*c[1][0]+b[2][2]*c[2][0];
	a[2][1]=b[2][0]*c[0][1]+b[2][1]*c[1][1]+b[2][2]*c[2][1];
	a[2][2]=b[2][0]*c[0][2]+b[2][1]*c[1][2]+b[2][2]*c[2][2];
	b[0][0]=1;b[0][1]=0;b[0][2]=0; //矩阵3
	b[1][0]=0;b[1][1]=-1;b[1][2]=0;
	b[2][0]=0;b[2][1]=0;b[2][2]=1;
	c[0][0]=b[0][0]*a[0][0]+b[0][1]*a[1][0]+b[0][2]*a[2][0]; //矩阵1、2、3合并
	c[0][1]=b[0][0]*a[0][1]+b[0][1]*a[1][1]+b[0][2]*a[2][1];
	c[0][2]=b[0][0]*a[0][2]+b[0][1]*a[1][2]+b[0][2]*a[2][2];
	c[1][0]=b[1][0]*a[0][0]+b[1][1]*a[1][0]+b[1][2]*a[2][0];
	c[1][1]=b[1][0]*a[0][1]+b[1][1]*a[1][1]+b[1][2]*a[2][1];
	c[1][2]=b[1][0]*a[0][2]+b[1][1]*a[1][2]+b[1][2]*a[2][2];
	c[2][0]=b[2][0]*a[0][0]+b[2][1]*a[1][0]+b[2][2]*a[2][0];
	c[2][1]=b[2][0]*a[0][1]+b[2][1]*a[1][1]+b[2][2]*a[2][1];
	c[2][2]=b[2][0]*a[0][2]+b[2][1]*a[1][2]+b[2][2]*a[2][2];
	b[0][0]=ca;b[0][1]=-sa;b[0][2]=0; //矩阵4
	b[1][0]=sa;b[1][1]=ca;b[1][2]=0;
	b[2][0]=0;b[2][1]=0;b[2][2]=1;
	a[0][0]=b[0][0]*c[0][0]+b[0][1]*c[1][0]+b[0][2]*c[2][0]; //矩阵1、2、3、4合并
	a[0][1]=b[0][0]*c[0][1]+b[0][1]*c[1][1]+b[0][2]*c[2][1];
	a[0][2]=b[0][0]*c[0][2]+b[0][1]*c[1][2]+b[0][2]*c[2][2];
	a[1][0]=b[1][0]*c[0][0]+b[1][1]*c[1][0]+b[1][2]*c[2][0];
	a[1][1]=b[1][0]*c[0][1]+b[1][1]*c[1][1]+b[1][2]*c[2][1];
	a[1][2]=b[1][0]*c[0][2]+b[1][1]*c[1][2]+b[1][2]*c[2][2];
	a[2][0]=b[2][0]*c[0][0]+b[2][1]*c[1][0]+b[2][2]*c[2][0];
	a[2][1]=b[2][0]*c[0][1]+b[2][1]*c[1][1]+b[2][2]*c[2][1];
	a[2][2]=b[2][0]*c[0][2]+b[2][1]*c[1][2]+b[2][2]*c[2][2];
	b[0][0]=1;b[0][1]=0;b[0][2]=(float)p1.x; //矩阵5
	b[1][0]=0;b[1][1]=1;b[1][2]=(float)p1.y;
	b[2][0]=0;b[2][1]=0;b[2][2]=1;
	c[0][0]=b[0][0]*a[0][0]+b[0][1]*a[1][0]+b[0][2]*a[2][0];//所有矩阵合并
	c[0][1]=b[0][0]*a[0][1]+b[0][1]*a[1][1]+b[0][2]*a[2][1];
	c[0][2]=b[0][0]*a[0][2]+b[0][1]*a[1][2]+b[0][2]*a[2][2];
	c[1][0]=b[1][0]*a[0][0]+b[1][1]*a[1][0]+b[1][2]*a[2][0];
	c[1][1]=b[1][0]*a[0][1]+b[1][1]*a[1][1]+b[1][2]*a[2][1];
	c[1][2]=b[1][0]*a[0][2]+b[1][1]*a[1][2]+b[1][2]*a[2][2];
	c[2][0]=b[2][0]*a[0][0]+b[2][1]*a[1][0]+b[2][2]*a[2][0];
	c[2][1]=b[2][0]*a[0][1]+b[2][1]*a[1][1]+b[2][2]*a[2][1];
    c[2][2]=b[2][0]*a[0][2]+b[2][1]*a[1][2]+b[2][2]*a[2][2];
	for(i=0;i<PointNum;i++)
	{
		x=c[0][0]*group[i].x+c[0][1]*group[i].y+c[0][2];
		y=c[1][0]*group[i].x+c[1][1]*group[i].y+c[1][2];
		group[i].x=(long)x;group[i].y=(long)y;
	}
}

void CMy2010302590054Doc::SeedFill(CClientDC*pDC,CPoint seedpoint)
{
	int savex,xleft,xright,pflag,x,y,num;
	CPoint stack_ptr[200];//堆栈
	COLORREF Color=pDC->GetPixel(group[0].x,group[0].y);
    pDC->SetROP2(R2_COPYPEN);
	num=0;
	stack_ptr[num++]=seedpoint;
	while(num>0){
		x=stack_ptr[--num].x;y=stack_ptr[num].y;
		pDC->SetPixel (x,y,m_crColor);
		savex=x;x++;
		while(pDC->GetPixel(x,y)==Color)//未到边界继续填充
		{
			pDC->SetPixel(x++,y,m_crColor);

		}
		xright=x-1;x=savex-1;
		while(pDC->GetPixel(x,y)==Color)//向左填充
		{
			pDC->SetPixel(x--,y,m_crColor);
		}
		xleft=x+1;x=xleft;y++;//在扫描线下一行搜索未填充区域
		pflag=1;
		while(x<xright)
		{
			if(pDC->GetPixel(x,y)==Color&&pflag==1)
			{
				stack_ptr[num].x=x;stack_ptr[num++].y=y;x++;
			}
			if(pDC->GetPixel(x,y)!=Color)
				pflag=1;//表示填充区域或边界
			else
				pflag=0;//表示未填充区域
			x++;
		}
		x=xleft;y-=2;pflag=1;
		while(x<xright)
		{
			if(pDC->GetPixel(x,y)==Color&&pflag==1)
			{
				stack_ptr[num].x=x;stack_ptr[num++].y=y;x++;
			}
			if(pDC->GetPixel(x,y)!=Color)
				pflag=1;//表示填充区域或边界
			else
				pflag=0;//表示未填充区域
			x++;
		}
	}
}

void CMy2010302590054Doc::EdgeFill(CClientDC*pDC)
{
	int i,xr,x1,y1,x2,y2,y;
	float m,x;
	CPen pen;
	COLORREF color;
	color=RGB(255,255,255)-m_crColor;//-RGB(255,255,255)+RGB(200,234,234)
	pen.CreatePen(PS_SOLID,1,color);//确定填充颜色
	pDC->SetROP2(R2_XORPEN);//绘图方法为异或
	CPen*pOldPen=pDC->SelectObject(&pen);
	xr=0;
	for(i=0;i<PointNum;i++)
	{
		if(xr<group[i].x)xr=group[i].x;
	}
	for(i=0;i<PointNum-1;i++)
	{
		x1=group[i].x;x2=group[i+1].x;
		y1=group[i].y;y2=group[i+1].y;
		if(y1!=y2)
		{
			if(y1>y2)//确保（x1，y1）为下端点
			{
				y=y1;y1=y2;y2=y;
				y=x1;x1=x2;x2=y;
			}
			m=(float)(x2-x1)/(float)(y2-y1);
			x=(float)x1;//m为相邻扫描线之间边的x增量
			for(y=y1+1;y<=y2;y++)
			{
				x+=m;//确定边缘点
				pDC->MoveTo((int)x,y);
				pDC->LineTo(xr,y);
			}
		}
	}
	pDC->SelectObject(pOldPen);
}

#define XMIN 100
#define XMAX 400
#define YMIN 100
#define YMAX 300
void CMy2010302590054Doc::DrawWindow(CClientDC*pDC)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *pOldPen=pDC->SelectObject(&pen);
	pDC->SetROP2(R2_COPYPEN);
	pDC->MoveTo(XMIN,YMIN);
	pDC->LineTo(XMAX,YMIN);
	pDC->LineTo(XMAX,YMAX);
	pDC->LineTo(XMIN,YMAX);
	pDC->LineTo(XMIN,YMIN);
	pDC->SelectObject(pOldPen);
}

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
void CMy2010302590054Doc::CohenSutherland(CClientDC*pDC,CPoint p1,CPoint p2)
{
	int code1,code2,code,x,y,x1,y1,x2,y2;
	pDC->SetROP2(R2_COPYPEN);
	CPen Pen;
	Pen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	CPen *OldPen=pDC->SelectObject(&Pen);

	x1=p1.x;y1=p1.y;
	x2=p2.x;y2=p2.y;
	code1=encode(x1,y1);
	code2=encode(x2,y2);
	while(code1!=0||code2!=0)
	{
		if((code1&code2)!=0)return;
		code=code1;
		if(code1==0)code=code2;
		if((LEFT&code)!=0)
		{
			x=XMIN;
			y=y1+(y2-y1)*(x-x1)/(x2-x1);

		}
		else if((RIGHT&code)!=0)
		{
			x=XMAX;
			y=y1+(y2-y1)*(x-x1)/(x2-x1);

		}
		else if((BOTTOM&code)!=0)
		{
			y=YMIN;
			x=x1+(x2-x1)*(y-y1)/(y2-y1);
		}
		else if((TOP&code)!=0)
		{
			y=YMAX;
			x=x1+(x2-x1)*(y-y1)/(y2-y1);
		}
		if(code==code1)
		{
			x1=x;y1=y;code1=encode(x,y);
		}
		else
		{
			x2=x;y2=y;code2=encode(x,y);
		}
	}
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
	pDC->SelectObject(OldPen);
}

int CMy2010302590054Doc::encode(int x,int y)
{
	int c;
	c=0;
	if(x<XMIN)
		c=c+LEFT;
	else if(x>XMAX)c=c+RIGHT;
	if(y<YMIN)
		c=c+BOTTOM;
	else if(y>YMAX)
		c=c+TOP;
	return c;
}

void CMy2010302590054Doc::PolygonCut(CClientDC*pDC)
{
	CPen pen;
	pen.CreatePen(0,2,RGB(255,0,0));
	CPen *OldPen=pDC->SelectObject(&pen);
	pDC->SetROP2(R2_COPYPEN);
	EdgeClipping(0);//用第一条窗口边裁剪
	EdgeClipping(1);
	EdgeClipping(2);
	EdgeClipping(3);
	pDC->MoveTo(group[0]);//绘制裁剪多边形
	for(int i=1;i<=PointNum;i++)
		pDC->LineTo(group[i]);
	pDC->SelectObject(OldPen);
}

void CMy2010302590054Doc::EdgeClipping(int linecode)
{
	float x,y;
	int n,i,number1;
	CPoint q[200];
	number1=0;
	if(linecode==0)//x=XMIN
	{
		for(n=0;n<PointNum;n++)
		{
			if(group[n].x<XMIN&&group[n+1].x<XMIN)//外外，不输出
			{

			}
			if(group[n].x>=XMIN&&group[n+1].x>=XMIN)//里里，输出后点
			{
				q[number1++]=group[n+1];
			}
			if(group[n].x>=XMIN&&group[n+1].x<XMIN)//里外，输出交点
			{
				y=group[n].y+(float)(group[n+1].y-group[n].y)/
					(float)(group[n+1].x-group[n].x)*(float)(XMIN-group[n].x);
				q[number1].x=XMIN;
				q[number1++].y=(int)y;
			}
			if(group[n].x<XMIN&&group[n+1].x>=XMIN)//外里，输出交点、后点
			{
				y=group[n].y+(float)(group[n+1].y-group[n].y)/
					(float)(group[n+1].x-group[n].x)*(float)(XMIN-group[n].x);
				q[number1].x=XMIN;
				q[number1++].y=(int)y;
				q[number1++]=group[n+1];
			}
		}
		for(i=0;i<number1;i++)
			group[i]=q[i];
		group[number1]=q[0];
		PointNum=number1;number1=0;
	}
	if(linecode==1)//y=YMAX
	{
		for(n=0;n<PointNum;n++)
		{
			if(group[n].y>=YMAX&&group[n+1].y>=YMAX)//外外，不输出
			{
				
			}
			if(group[n].y<YMAX&&group[n+1].y<YMAX)//里里，输出后点
			{
				q[number1++]=group[n+1];
			}
			if(group[n].y<YMAX&&group[n+1].y>=YMAX)//里外，输出交点
			{
				x=group[n].x+(float)(group[n+1].x-group[n].x)/
					(float)(group[n+1].y-group[n].y)*(float)(YMAX-group[n].y);
				q[number1].x=(int)x;
				q[number1++].y=YMAX;
			}
			if(group[n].y>=YMAX&&group[n+1].y<YMAX)//外里，输出交点、后点
			{
				x=group[n].x+(float)(group[n+1].x-group[n].x)/
					(float)(group[n+1].y-group[n].y)*(float)(YMAX-group[n].y);
				q[number1].x=(int)x;
				q[number1++].y=YMAX;
				q[number1++]=group[n+1];
			}
		}
		for(i=0;i<number1;i++)
			group[i]=q[i];
		group[number1]=q[0];
		PointNum=number1;number1=0;
	}
	if(linecode==2)//x=XMAX
	{
		for(n=0;n<PointNum;n++)
		{
			if(group[n].x>=XMAX&&group[n+1].x>=XMAX)//外外，不输出
			{
				
			}
			if(group[n].x<XMAX&&group[n+1].x<XMAX)//里里，输出后点
			{
				q[number1++]=group[n+1];
			}
			if(group[n].x<XMAX&&group[n+1].x>=XMAX)//里外，输出交点
			{
				y=group[n].y+(float)(group[n+1].y-group[n].y)/
					(float)(group[n+1].x-group[n].x)*(float)(XMAX-group[n].x);
				q[number1].x=XMAX;
				q[number1++].y=(int)y;
			}
			if(group[n].x>=XMAX&&group[n+1].x<XMAX)//外里，输出交点、后点
			{
				y=group[n].y+(float)(group[n+1].y-group[n].y)/
					(float)(group[n+1].x-group[n].x)*(float)(XMAX-group[n].x);
				q[number1].x=XMAX;
				q[number1++].y=(int)y;
				q[number1++]=group[n+1];
			}
		}
		for(i=0;i<number1;i++)
			group[i]=q[i];
		group[number1]=q[0];
		PointNum=number1;number1=0;
	}
	if(linecode==1)//y=YMIN
	{
		for(n=0;n<PointNum;n++)
		{
			if(group[n].y<YMIN&&group[n+1].y<YMIN)//外外，不输出
			{
				
			}
			if(group[n].y>=YMIN&&group[n+1].y>=YMIN)//里里，输出后点
			{
				q[number1++]=group[n+1];
			}
			if(group[n].y>=YMIN&&group[n+1].y<YMIN)//里外，输出交点
			{
				x=group[n].x+(float)(group[n+1].x-group[n].x)/
					(float)(group[n+1].y-group[n].y)*(float)(YMIN-group[n].y);
				q[number1].x=(int)x;
				q[number1++].y=YMIN;
			}
			if(group[n].y<YMIN&&group[n+1].y>=YMIN)//外里，输出交点、后点
			{
				x=group[n].x+(float)(group[n+1].x-group[n].x)/
					(float)(group[n+1].y-group[n].y)*(float)(YMIN-group[n].y);
				q[number1].x=(int)x;
				q[number1++].y=YMIN;
				q[number1++]=group[n+1];
			}
		}
		for(i=0;i<number1;i++)
			group[i]=q[i];
		group[number1]=q[0];
		PointNum=number1;number1=0;
	}
}

void CMy2010302590054Doc::CircleCut(CClientDC*DCPoint,CPoint p1,CPoint p2)
{
	CRect rc(XMIN,YMIN,XMAX,YMAX);
	BCircle(DCPoint,&rc,p1,p2);
}
