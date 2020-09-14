// 2010302590054View.cpp : implementation of the CMy2010302590054View class
//

#include "stdafx.h"
#include "2010302590054.h"

#include "2010302590054Doc.h"
#include "2010302590054View.h"
#include "DRAWCHARDLG.h"
#include "CubeSpindlg.h"
#include "GlobeLightDlg.h"
#include "LineWideDlg.h"
#include "ZoomDlg.h"
#include "VirtualCylinder.h"
#include "VirtualSphere.h"
#include "Brick.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char* const CMy2010302590054View::_ErrorStrings[]= {
				{"No Error"},					// 0
				{"Unable to get a DC"},			// 1
				{"ChoosePixelFormat failed"},	// 2
				{"SelectPixelFormat failed"},	// 3
				{"wglCreateContext failed"},	// 4
				{"wglMakeCurrent failed"},		// 5
				{"wglDeleteContext failed"},	// 6
				{"SwapBuffers failed"},			// 7
				
};

extern CStatusBar m_wndStatusBar;
/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054View

IMPLEMENT_DYNCREATE(CMy2010302590054View, CScrollView)

BEGIN_MESSAGE_MAP(CMy2010302590054View, CScrollView)
	//{{AFX_MSG_MAP(CMy2010302590054View)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_DRAW_DDALINE, OnDrawDdaline)
	ON_COMMAND(ID_DRAW_BCIRCLE, OnDrawBcircle)
	ON_COMMAND(ID_CURVE_BEZIER, OnCurveBezier)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DRAW_PNCIRCLE, OnDrawPncircle)
	ON_COMMAND(ID_DRAW_CHAR, OnDrawChar)
	ON_COMMAND(ID_TRANS_MOVE, OnTransMove)
	ON_COMMAND(ID_TRANS_SYMMETRY, OnTransSymmetry)
	ON_COMMAND(ID_FILL_SEED, OnFillSeed)
	ON_COMMAND(ID_DRAW_POLYGON, OnDrawPolygon)
	ON_COMMAND(ID_CUT_CS, OnCutCs)
	ON_COMMAND(ID_FILL_EDGE, OnFillEdge)
	ON_COMMAND(ID_FILL_SCANLINE, OnFillScanline)
	ON_COMMAND(ID_CUT_POLYGON, OnCutPolygon)
	ON_COMMAND(ID_CUT_CIRCLE, OnCutCircle)
	ON_COMMAND(ID_DRAW_MIDLINE, OnDrawMidline)
	ON_COMMAND(ID_DRAW_BLINE, OnDrawBline)
	ON_COMMAND(ID_GLOBE_LIGHT, OnGlobeLight)
	ON_COMMAND(ID_LINEWIDE, OnLinewide)
	ON_COMMAND(ID_TRANS_ROTATE, OnTransRotate)
	ON_COMMAND(ID_TRANS_ZOOM, OnTransZoom)
	ON_COMMAND(ID_CURVE_BSAMPLE, OnCurveBsample)
	ON_COMMAND(ID_CUBESPIN, OnCubespin)
	ON_WM_CHAR()
	ON_COMMAND(ID_DRAW_CHAR2, OnDrawChar2)
	ON_COMMAND(ID_FILL, OnFill)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_3DSPIN, On3dspin)
	ON_WM_TIMER()
	ON_COMMAND(ID_START, OnStart)
	ON_COMMAND(ID_RESTART, OnRestart)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_END, OnEnd)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054View construction/destruction

CMy2010302590054View::CMy2010302590054View():
	m_hRC(0), m_pDC(0), m_ErrorString(_ErrorStrings[0])
{
	// TODO: add construction code here
		m_Brush.CreateSolidBrush(RGB(200,234,234));

		//小球初始坐标、速度、状态
		x= 5; 
		y= 10;
		m_nSpeedX = 8;
		m_nSpeedY = 2;
		m_bPlay = FALSE;
		
     	m_flag = 0;
}

CMy2010302590054View::~CMy2010302590054View()
{
}

BOOL CMy2010302590054View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054View drawing

void CMy2010302590054View::OnDraw(CDC* pDC)
{
	CMy2010302590054Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(MenuID==30)
	{
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	PreRenderScene();
	
	::glPushMatrix();
	RenderStockScene();
	::glPopMatrix();
	
	::glPushMatrix();
	RenderScene();
	::glPopMatrix();
	
	::glFinish();
	
	if ( FALSE == ::SwapBuffers( m_pDC->GetSafeHdc() ) )
	{
		SetError(7);
	}
	}
	::glClearColor( 0.2f, 0.5f, 1.0f, 0.0f );//更改三维物体的背景色
	
	
	/****************************小球碰撞场景生成******************************/
	
	if(m_bPlay==TRUE)
	{
		CRect rect;
		GetClientRect(&rect);
		int nClientWidth = rect.Width();
		int nClientHeight =rect.Height(); //生成矩形场景，并获取高宽
		
		CDC memDC;
		memDC.CreateCompatibleDC(pDC); //载入当前DC
		
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(pDC,nClientWidth,nClientHeight);
		CBitmap *pOldBitmap = memDC.SelectObject(&bitmap);
		CBrush *pBrush = new CBrush(RGB(128,128,0));
		memDC.FillRect(rect,pBrush);
		delete pBrush;  //用指定颜色画刷填充矩形场景
		
		//调用CView类自定义函数绘制图形
		DrawSphere(&memDC,x,y);  //绘制小球
		DrawGlider(&memDC,x-17,nClientHeight-61);  //绘制滑块
		DrawBase(&memDC);  //绘制基座
		Drawpillar(&memDC);  //绘制圆柱
		
		pDC->BitBlt(0,0,nClientWidth,nClientHeight,&memDC,0,0,SRCCOPY);  //像素进行位块转换,使窗口扩大时仍正常显示
		
		memDC.SelectObject(pOldBitmap);
		bitmap.DeleteObject();
	}
	// TODO: add draw code for native data here
}

void CMy2010302590054View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054View printing

BOOL CMy2010302590054View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy2010302590054View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy2010302590054View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054View diagnostics

#ifdef _DEBUG
void CMy2010302590054View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMy2010302590054View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMy2010302590054Doc* CMy2010302590054View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2010302590054Doc)));
	return (CMy2010302590054Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy2010302590054View message handlers

void CMy2010302590054View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC ht(this);
//	CPen Pen(0,0,RGB(0,0,255));
//	CPen *pOldPen=ht.SelectObject(&Pen);
	
	if(MenuID==1||MenuID==2||MenuID==8){//DDA画直线、中点画线、Bresenham画线
		m_hCross=AfxGetApp()->LoadCursor(IDC_LINE);
		::SetCursor(m_hCross);
		if(PressNum==0){
			pDoc->group[PressNum]=point;
			m_PointOrigin=point;m_PointOld=point;
			PressNum++;SetCapture();
		}
		else if(MenuID==1&&PressNum==1){
			ht.SetROP2(R2_NOT);//设置异或条件
			ht.MoveTo(m_PointOrigin);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->group[PressNum]=point;
			PressNum=0;
			pDoc->DDALine(&ht);
			ReleaseCapture();
		}
		else if(MenuID==2&&PressNum==1){
			ht.SetROP2(R2_NOT);//设置异或条件
			ht.MoveTo(m_PointOrigin);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->group[PressNum]=point;
			PressNum=0;
			pDoc->MidpointLine(&ht);
			ReleaseCapture();
		}
		else if(MenuID==8&&PressNum==1){
			ht.SetROP2(R2_NOT);//设置异或条件
			ht.MoveTo(m_PointOrigin);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->group[PressNum]=point;
			PressNum=0;
			pDoc->BLine(&ht);
			ReleaseCapture();
		}
	}
	if(MenuID==3||MenuID==4||MenuID==26){//Bresenham画圆、正负法画圆、圆裁剪
		m_hCross=AfxGetApp()->LoadCursor(IDC_CIRCLE);
		::SetCursor(m_hCross);
		if(PressNum==0){
			pDoc->group[PressNum]=point;
			PressNum++;
			m_PointOrigin=point;
			m_PointOld=point;
			SetCapture();
		}
		else if(PressNum==1&&MenuID==3){
			ht.SelectStockObject(NULL_BRUSH);
			ht.SetROP2(R2_NOT);//设置异或条件
			if(m_PointOld==point){//擦除橡皮筋??
				int r=(int)sqrt((double)(m_PointOrigin.x-m_PointOld.x)*(m_PointOrigin.x-m_PointOld.x)+(m_PointOrigin.y-m_PointOld.y)*(m_PointOrigin.y-m_PointOld.y));
				ht.Ellipse(m_PointOrigin.x-r,m_PointOrigin.y-r,m_PointOrigin.x+r,m_PointOrigin.y+r);}
			m_PointOld=point;
			PressNum=0;
			pDoc->BCircle(&ht,m_PointOrigin,point);
			ReleaseCapture();
		}
		else if(PressNum==1&&MenuID==4){
			ht.SelectStockObject(NULL_BRUSH);
			ht.SetROP2(R2_NOT);//设置异或条件
			m_PointOld=point;
			if(m_PointOld==point){//擦除橡皮筋??
				int r=(int)sqrt((double)(m_PointOrigin.x-m_PointOld.x)*(m_PointOrigin.x-m_PointOld.x)+(m_PointOrigin.y-m_PointOld.y)*(m_PointOrigin.y-m_PointOld.y));
				ht.Ellipse(m_PointOrigin.x-r,m_PointOrigin.y-r,m_PointOrigin.x+r,m_PointOrigin.y+r);}
			PressNum=0;
			pDoc->PNCircle(&ht,m_PointOrigin,point);
			ReleaseCapture();
		}
		else if(PressNum==1&&MenuID==26){//圆裁剪
			ht.SelectStockObject(NULL_BRUSH);
			ht.SetROP2(R2_NOT);//设置异或条件
			m_PointOld=point;
			if(m_PointOld==point){//擦除橡皮筋??
				int r=(int)sqrt((double)(m_PointOrigin.x-m_PointOld.x)*(m_PointOrigin.x-m_PointOld.x)+(m_PointOrigin.y-m_PointOld.y)*(m_PointOrigin.y-m_PointOld.y));
				ht.Ellipse(m_PointOrigin.x-r,m_PointOrigin.y-r,m_PointOrigin.x+r,m_PointOrigin.y+r);}
			pDoc->group[PressNum]=point;
			PressNum=0;
			pDoc->CircleCut(&ht,m_PointOrigin,point);
			ReleaseCapture();
		}
	}
	if(MenuID==5||MenuID==9){//Bezier/BSample
		m_hCross=AfxGetApp()->LoadCursor(IDC_LINE);
		::SetCursor(m_hCross);
		pDoc->group[pDoc->PointNum++]=point;
		ht.MoveTo(point.x-5,point.y);
		ht.LineTo(point.x+5,point.y);
		ht.MoveTo(point.x,point.y-5);
		ht.LineTo(point.x,point.y+5);
		SetCapture();PressNum=1;
	}
	if(MenuID==6&&PressNum==0){//Bezier
		m_hCross=AfxGetApp()->LoadCursor(IDC_LINE);
		::SetCursor(m_hCross);
		for(int i=0;i<pDoc->PointNum;i++)
		{
			if((point.x>=pDoc->group[i].x-5)&&(point.x<=pDoc->group[i].x+5)
				&&(point.y>=pDoc->group[i].y-5)&&(point.y<=pDoc->group[i].y+5))
			{
				SaveNumber=i;
				PressNum=1;
			}
		}
	}
	if(MenuID==10&&PressNum==0){//BSample
		m_hCross=AfxGetApp()->LoadCursor(IDC_LINE);
		::SetCursor(m_hCross);
		for(int i=0;i<pDoc->PointNum;i++)
		{
			if((point.x>=pDoc->group[i].x-5)&&(point.x<=pDoc->group[i].x+5)
				&&(point.y>=pDoc->group[i].y-5)&&(point.y<=pDoc->group[i].y+5))
			{
				SaveNumber=i;
				PressNum=1;
			}
		}
	}
	if(MenuID==11){//平移
		m_hCross=AfxGetApp()->LoadCursor(IDC_MOVE);
		::SetCursor(m_hCross);
		if(PressNum==0){
			PressNum++;
			m_PointOrigin=point;
			m_PointOld=point;
			SetCapture();
		}
		else if(PressNum==1){
			for(int i=0;i<pDoc->PointNum;i++){
				pDoc->group[i].x+=point.x-m_PointOrigin.x;
				pDoc->group[i].y+=point.y-m_PointOrigin.y;
			}
			ht.SetROP2(R2_NOT);//设置异或条件
			ht.MoveTo(m_PointOrigin);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->DrawGraph(&ht);
			ReleaseCapture();
			PressNum=0;
		}
	}
	if(MenuID==12){//旋转
		m_hCross=AfxGetApp()->LoadCursor(IDC_SPIN);
		::SetCursor(m_hCross);
		if(PressNum==0){
			ht.MoveTo(pDoc->group[0]);
			ht.LineTo(point);
			PressNum++;
			m_PointOrigin=point;
			m_PointOld=point;
			SetCapture();
		}
		else if(PressNum==1){
			ht.SetROP2(R2_NOT);//设置异或条件
			ht.MoveTo(pDoc->group[0]);
			ht.LineTo(m_PointOrigin);
			ht.MoveTo(m_PointOrigin);//擦除橡皮筋
			ht.LineTo(point);

			pDoc->TransRotate(m_PointOrigin,point);
			pDoc->DrawGraph(&ht);
			ReleaseCapture();
			PressNum=0;
		}
	}
	if(MenuID==13){//缩放
		if(PressNum==0){
			PressNum++;
			CZoomDlg dlg;
			dlg.m_Point_X=point.x;
			dlg.m_Point_Y=point.y;
			if(dlg.DoModal()==IDOK)
			{
				int x=dlg.m_Point_X;
				int y=dlg.m_Point_Y;
				float zoomx=dlg.m_Zoom_X;
				float zoomy=dlg.m_Zoom_Y;
				pDoc->TransZoom(x,y,zoomx,zoomy);
				pDoc->DrawGraph(&ht);
			}
		}
		PressNum=0;
	}
	if(MenuID==15)//对称变换
	{
		m_hCross=AfxGetApp()->LoadCursor(IDC_LINE);
		::SetCursor(m_hCross);
		if(PressNum==0)
		{
			PressNum++;
			m_PointOrigin=point;
			m_PointOld=point;
			SetCapture();
		}
		else if(PressNum==1)
		{
			pDoc->Symmetry(m_PointOrigin,point);
			ht.SetROP2(R2_NOT);//设置异或条件
			ht.MoveTo(m_PointOrigin);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->DrawGraph(&ht);
			ReleaseCapture();
			PressNum=0;
		}
	}
	if(MenuID==19){//填充
		pDoc->group[0]=point;
		pDoc->SeedFill(&ht,point);
		PressNum=0;
	}
	if(MenuID==7||MenuID==20){//多边形、种子填充
		m_hCross=AfxGetApp()->LoadCursor(IDC_LINE);
		::SetCursor(m_hCross);
		if(PressNum==0){
			m_PointOrigin=point;
			m_PointOld=point;
			m_PointOld1=point;
			PressNum++;
			SetCapture();
		}
		else{
			pDoc->group[0]=m_PointOrigin;
			pDoc->group[1]=point;
			pDoc->DDALine(&ht);
			m_PointOrigin=point;
			m_PointOld=point;
			PressNum++;
		}
	}
	if(MenuID==21){
		pDoc->group[0]=point;
		pDoc->SeedFill(&ht,point);
		PressNum=0;MenuID=20;
	}
	if(MenuID==22||MenuID==23||MenuID==25){//边缘填充选顶点/扫描线填充//多边形裁剪
		m_hCross=AfxGetApp()->LoadCursor(IDC_LINE);
		::SetCursor(m_hCross);
		pDoc->group[PressNum++]=point;
		pDoc->PointNum++;
		m_PointOrigin=point;
		m_PointOld=point;
		SetCapture();
	}
	if(MenuID==24){//Cohen-sutherland裁剪算法
		if(PressNum==0){
			m_PointOrigin=point;
			m_PointOld=point;
			PressNum++;
			SetCapture();
		}
		else{
			pDoc->CohenSutherland(&ht,m_PointOrigin,point);
			ReleaseCapture();
			PressNum=0;
		}
	}
	//字符插入
	if(MenuID==31)
	{		
		m_hCross=AfxGetApp()->LoadCursor(IDC_CHAR);
		::SetCursor(m_hCross);
		m_PointOrigin=point;
		
		TEXTMETRIC tm;
		ht.GetTextMetrics(&tm);
		CreateSolidCaret(tm.tmAveCharWidth/8,tm.tmHeight);//生成合适大小的插入符
		ShowCaret();
		SetCaretPos(point);  //设定插入符位置
		m_strLine="";		
	}

//	ht.SelectObject(pOldPen);
	CScrollView::OnLButtonDown(nFlags, point);
}

void CMy2010302590054View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMy2010302590054Doc*pDoc=GetDocument();
	int xx,yy;
	char p1[20];
	
	xx=point.x;
	yy=point.y;
	sprintf(p1,"%4d",xx);
	m_wndStatusBar.SetPaneText(2,p1,TRUE);
	sprintf(p1,"%4d",yy);
	m_wndStatusBar.SetPaneText(3,p1,TRUE);


/*
	CPen pen(0,0,RGB(0,0,255));
	CPen *pOldPen=pDC.SelectObject(&pen);
	CPen NewPen,*pPenOld;
	NewPen.CreatePen(PS_DASH,1,RGB(0,0,255));
	pPenOld=pDC.SelectObject(&NewPen);*/

	CClientDC pDC(this);
	OnPrepareDC(&pDC);//??
	pDC.DPtoLP(&point);//??
	pDC.SetROP2(R2_NOT);//设置异或条件

	if((MenuID==1||MenuID==2||MenuID==8||MenuID==7||MenuID==11
		||MenuID==12||MenuID==15||MenuID==20||MenuID==22||
		MenuID==23||MenuID==24||MenuID==25)&&PressNum>0){//DDA
		if(m_PointOld!=point){
			pDC.MoveTo(m_PointOrigin);pDC.LineTo(m_PointOld);
			pDC.MoveTo(m_PointOrigin);pDC.LineTo(point);
			m_PointOld=point;
		}
	}
	if((MenuID==3||MenuID==4||MenuID==26)&&PressNum==1){//Bresenham画圆、正负法画圆
		pDC.SelectStockObject(NULL_BRUSH);
		if(m_PointOld!=point){
			int r=(int)sqrt((double)(m_PointOrigin.x-m_PointOld.x)*(m_PointOrigin.x-m_PointOld.x)+(m_PointOrigin.y-m_PointOld.y)*(m_PointOrigin.y-m_PointOld.y));
			pDC.Ellipse(m_PointOrigin.x-r,m_PointOrigin.y-r,m_PointOrigin.x+r,m_PointOrigin.y+r);
            r=(int)sqrt((double)(m_PointOrigin.x-point.x)*(m_PointOrigin.x-point.x)+(m_PointOrigin.y-point.y)*(m_PointOrigin.y-point.y));
			pDC.Ellipse(m_PointOrigin.x-r,m_PointOrigin.y-r,m_PointOrigin.x+r,m_PointOrigin.y+r);
			m_PointOld=point;
		}
	}
	if(MenuID==6&&PressNum>0){//Bezier
		if(pDoc->group[SaveNumber]!=point)
		{
			pDC.MoveTo(pDoc->group[SaveNumber].x-5,pDoc->group[SaveNumber].y);
			pDC.LineTo(pDoc->group[SaveNumber].x+5,pDoc->group[SaveNumber].y);
			pDC.MoveTo(pDoc->group[SaveNumber].x,pDoc->group[SaveNumber].y-5);
			pDC.LineTo(pDoc->group[SaveNumber].x,pDoc->group[SaveNumber].y+5);
			pDoc->Bezier(&pDC,1);
			pDC.MoveTo(point.x-5,point.y);
			pDC.LineTo(point.x+5,point.y);
			pDC.MoveTo(point.x,point.y-5);
			pDC.LineTo(point.x,point.y+5);
			pDoc->group[SaveNumber]=point;
			pDoc->Bezier(&pDC,1);
		}
	}
	if(MenuID==10&&PressNum>0){//BSample
		if(pDoc->group[SaveNumber]!=point)
		{
			pDC.MoveTo(pDoc->group[SaveNumber].x-5,pDoc->group[SaveNumber].y);
			pDC.LineTo(pDoc->group[SaveNumber].x+5,pDoc->group[SaveNumber].y);
			pDC.MoveTo(pDoc->group[SaveNumber].x,pDoc->group[SaveNumber].y-5);
			pDC.LineTo(pDoc->group[SaveNumber].x,pDoc->group[SaveNumber].y+5);
			pDoc->BSample(&pDC,1);
			pDC.MoveTo(point.x-5,point.y);
			pDC.LineTo(point.x+5,point.y);
			pDC.MoveTo(point.x,point.y-5);
			pDC.LineTo(point.x,point.y+5);
			pDoc->group[SaveNumber]=point;
			pDoc->BSample(&pDC,1);
		}
	}
	if(MenuID==12&&PressNum==1)//图形变换旋转
	{
/*		if(m_PointOld!=point)
//		{
			pDoc->TransRotate(m_PointOrigin,m_PointOld);
			pDoc->DrawGraph(&pDC);
			pDoc->TransRotate(m_PointOrigin,point);
			pDoc->DrawGraph(&pDC);
		}*/
	}

	if(MenuID==31)
	{
		m_hCross=AfxGetApp()->LoadCursor(IDC_CHAR);
		::SetCursor(m_hCross);

	}
//	pDC.SelectObject(pPenOld);
	CScrollView::OnMouseMove(nFlags, point);
}

void CMy2010302590054View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC ht(this);
	OnPrepareDC(&ht);
    ht.DPtoLP(&point);//?
	int i;

	if((MenuID==1||MenuID==2||MenuID==8)&&PressNum==1)//右击取消画直线
	{
		ht.SetROP2(R2_NOT);
		ht.MoveTo(m_PointOrigin);
		ht.LineTo(point);
		PressNum=0;
		ReleaseCapture();
	}
	if((MenuID==3||MenuID==4||MenuID==26)&&PressNum==1)//右击取消画圆
	{
		ht.SelectStockObject(NULL_BRUSH);
		ht.SetROP2(R2_NOT);
		int r=(int)sqrt((double)(m_PointOrigin.x-m_PointOld.x)*(m_PointOrigin.x-m_PointOld.x)+(m_PointOrigin.y-m_PointOld.y)*(m_PointOrigin.y-m_PointOld.y));
		ht.Ellipse(m_PointOrigin.x-r,m_PointOrigin.y-r,m_PointOrigin.x+r,m_PointOrigin.y+r);
		PressNum=0;
		ReleaseCapture();
	}
	if(MenuID==5&&pDoc->PointNum>3){
		pDoc->Bezier(&ht,1);
		MenuID=6;
		PressNum=0;
	}
	if(MenuID==6&&PressNum==1){
		PressNum=0;
	}
	if(MenuID==9&&pDoc->PointNum>3){
		pDoc->BSample(&ht,1);
		MenuID=10;
		PressNum=0;
	}
	if(MenuID==10&&PressNum==1){
		PressNum=0;
	}
	if(MenuID==7&&PressNum>0){//闭合多边形
		ht.SetROP2(R2_NOT);//设置异或条件，擦除橡皮筋
		ht.MoveTo(m_PointOrigin);// 擦除橡皮筋
		ht.LineTo(point);
		pDoc->group[0]=m_PointOld1;
		pDoc->group[1]=m_PointOrigin;
		pDoc->DDALine(&ht);
		PressNum=0;
		ReleaseCapture();
	}
	if((MenuID==11||MenuID==15)&&PressNum==1){//取消平移、旋转、对称变换
		ht.SetROP2(R2_NOT);//设置异或条件，擦除橡皮筋
		ht.MoveTo(m_PointOrigin);// 擦除橡皮筋
		ht.LineTo(point);
		PressNum=0;ReleaseCapture();
	}
	if(MenuID==12&&PressNum==1)
	{
		ht.SetROP2(R2_NOT);//设置异或条件，擦除橡皮筋
		ht.MoveTo(pDoc->group[0]);
		ht.LineTo(m_PointOrigin);
		ht.MoveTo(m_PointOrigin);// 擦除橡皮筋
		ht.LineTo(point);
		PressNum=0;ReleaseCapture();
	}
	if(MenuID==20&&PressNum>0){//种子填充

		ht.SetROP2(R2_NOT);//设置异或条件，擦除橡皮筋
		ht.MoveTo(m_PointOrigin);// 擦除橡皮筋
		ht.LineTo(point);

		pDoc->group[0]=m_PointOld1;
		pDoc->group[1]=m_PointOrigin;
		pDoc->DDALine(&ht);
		PressNum=0;MenuID=21;//改变操作方式为种子点选取
		ReleaseCapture();
	}
	if(MenuID==22){//边缘填充选点结束
		ht.SetROP2(R2_NOT);//消除边界
		ht.MoveTo(m_PointOrigin);
		ht.LineTo(point);

		pDoc->group[PressNum]=pDoc->group[0];//最后一点为第一点，即封闭图形
		pDoc->PointNum++;
		ht.MoveTo(pDoc->group[PressNum-1]);
		ht.LineTo(pDoc->group[0]);
		for(i=0;i<PressNum;i++)
			ht.LineTo(pDoc->group[i+1]);
		pDoc->EdgeFill(&ht);
		PressNum=0;pDoc->PointNum=0;//MenuID=0;
		ReleaseCapture();
	}
	if(MenuID==23){
		pDoc->group[PressNum]=pDoc->group[0];//封闭多边形
		ht.SetROP2(R2_NOT);//设置异或条件
		ht.MoveTo(m_PointOrigin);
		ht.LineTo(point);
		ht.MoveTo(pDoc->group[PressNum-1]);//擦除
		ht.LineTo(pDoc->group[0]);
		for(i=0;i<PressNum;i++)//擦除边缘
			ht.LineTo(pDoc->group[i+1]);
		CPen pen(PS_SOLID,1,pDoc->m_crColor);//设置多边形边界颜色即画笔
		CPen *pOldPen=ht.SelectObject(&pen);
		CBrush brush(pDoc->m_crColor);//设置多边形填充颜色即画刷
		CBrush*pOldBrush=ht.SelectObject(&brush);
		ht.SetROP2(R2_COPYPEN);//设置直接画方式
		ht.Polygon(pDoc->group,PressNum);//调用多边形扫描线填充函数
		ht.SelectObject(pOldPen);
		ht.SelectObject(pOldBrush);
		PressNum=0;pDoc->PointNum=0;//MenuID=0;
		ReleaseCapture();
	}
	if(MenuID==25){//多边形裁剪
		ht.SetROP2(R2_NOT);//设置异或条件
		ht.MoveTo(m_PointOrigin);
		ht.LineTo(point);
		pDoc->group[PressNum]=pDoc->group[0];//将第一个顶点作为最后一个
		pDoc->PointNum=PressNum;//记录顶点数量
		ht.MoveTo(pDoc->group[PressNum-1]);
		ht.LineTo(pDoc->group[0]);
		pDoc->PolygonCut(&ht);
		PressNum=0;pDoc->PointNum=0;
		ReleaseCapture();
	}

	CScrollView::OnRButtonDown(nFlags, point);
}

void CMy2010302590054View::OnDrawDdaline() 
{
	// TODO: Add your command handler code here
	PressNum=0;MenuID=1;
}

void CMy2010302590054View::OnDrawMidline() 
{
	// TODO: Add your command handler code here
	PressNum=0;MenuID=2;
}

void CMy2010302590054View::OnDrawBline() 
{
	// TODO: Add your command handler code here
	PressNum=0;MenuID=8;
}

void CMy2010302590054View::OnDrawBcircle() 
{
	// TODO: Add your command handler code here
	PressNum=0;MenuID=3;
}

void CMy2010302590054View::OnDrawPncircle() 
{
	// TODO: Add your command handler code here
	PressNum=0;MenuID=4;
}

void CMy2010302590054View::OnCurveBezier() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	pDoc->PointNum=0;
	PressNum=0;MenuID=5;
}

void CMy2010302590054View::OnDrawPolygon() 
{
	// TODO: Add your command handler code here
	PressNum=0;MenuID=7;
}

void CMy2010302590054View::OnCurveBsample() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	pDoc->PointNum=0;
	PressNum=0;MenuID=9;
}

void CMy2010302590054View::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDC.DPtoLP(&point);
	pDC.SetROP2(R2_NOT);
	if(MenuID==6){
		for(int i=0;i<pDoc->PointNum;i++){
			pDC.MoveTo(pDoc->group[i].x-5,pDoc->group[i].y);
			pDC.LineTo(pDoc->group[i].x+5,pDoc->group[i].y);
			pDC.MoveTo(pDoc->group[i].x,pDoc->group[i].y-5);
			pDC.LineTo(pDoc->group[i].x,pDoc->group[i].y+5);
		}
		pDoc->Bezier(&pDC,0);
		MenuID=5;
		PressNum=0;
		pDoc->PointNum=0;
		ReleaseCapture();
	}
	if(MenuID==10){
		for(int i=0;i<pDoc->PointNum;i++){
			pDC.MoveTo(pDoc->group[i].x-5,pDoc->group[i].y);
			pDC.LineTo(pDoc->group[i].x+5,pDoc->group[i].y);
			pDC.MoveTo(pDoc->group[i].x,pDoc->group[i].y-5);
			pDC.LineTo(pDoc->group[i].x,pDoc->group[i].y+5);
		}
		pDoc->BSample(&pDC,0);
		MenuID=9;
		PressNum=0;
		pDoc->PointNum=0;
		ReleaseCapture();
	}
	if(MenuID==30)
	{
		MenuID=0;
		Invalidate(TRUE);
	}

	CScrollView::OnLButtonDblClk(nFlags, point);
}


void CMy2010302590054View::OnDrawChar() 
{
	// TODO: Add your command handler code here
	CDC *pDC=GetDC();
	CDRAWCHARDLG dlg;
	if(dlg.DoModal()==IDOK)
	{
		CFont *pfntOld=pDC->SelectObject(&dlg.m_fnt);//保存旧字体
		pDC->SetTextColor(dlg.m_clrText);//设置颜色
		pDC->TextOut(dlg.m_nX,dlg.m_nY,dlg.m_strString);//画到屏幕上
		pDC->SelectObject(pfntOld);//还原旧字体
	}
	ReleaseDC(pDC);
	PressNum=0;MenuID=0;
}

void CMy2010302590054View::OnTransMove() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph(&pDC);
	PressNum=0;MenuID=11;
}

void CMy2010302590054View::OnTransRotate() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph(&pDC);
	PressNum=0;MenuID=12;
}

void CMy2010302590054View::OnTransZoom() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph(&pDC);
	PressNum=0;MenuID=13;
}

void CMy2010302590054View::OnTransSymmetry() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph(&pDC);
	PressNum=0;MenuID=15;
}

void CMy2010302590054View::OnFillSeed() 
{
	// TODO: Add your command handler code here
	PressNum=0;MenuID=20;
}

void CMy2010302590054View::OnCutCs() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum=0;MenuID=24;
	
}

void CMy2010302590054View::OnFillEdge() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	pDoc->PointNum=0;
	PressNum=0;MenuID=22;
}

void CMy2010302590054View::OnFillScanline() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	pDoc->PointNum=0;
	PressNum=0;MenuID=23;
}

void CMy2010302590054View::OnCutPolygon() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum=0;MenuID=25;
}

void CMy2010302590054View::OnCutCircle() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->DrawWindow(&pDC);
	PressNum=0;MenuID=26;
}

void CMy2010302590054View::OnCubespin() 
{
	// TODO: Add your command handler code here
	CCubeSpinDlg dlg;
	dlg.DoModal();
}

void CMy2010302590054View::OnGlobeLight() 
{
	// TODO: Add your command handler code here
	CGlobeLightDlg dlg;
	if(dlg.DoModal()==IDOK)
	{

	}
}

void CMy2010302590054View::OnLinewide() 
{
	// TODO: Add your command handler code here
	CMy2010302590054Doc*pDoc=GetDocument();
	CLineWideDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		pDoc->LineWide=dlg.m_LineWide;
	}
}

void CMy2010302590054View::OnDrawChar2() 
{
	// TODO: Add your command handler code here
	PressNum=0;
	MenuID=31;
	CFontDialog dlg;
	if(IDOK==dlg.DoModal())
	{
		if(m_font.m_hObject)
			m_font.DeleteObject();
		LOGFONT LogFnt;
		dlg.GetCurrentFont(&LogFnt);
		m_font.CreateFontIndirect(dlg.m_cf.lpLogFont);
		m_color=dlg.GetColor();
	}
	m_hCross=AfxGetApp()->LoadCursor(IDC_CHAR);
		::SetCursor(m_hCross);
}

void CMy2010302590054View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(MenuID==31)
	{
		CClientDC dc(this);
		CFont *pOldFont=dc.SelectObject(&m_font);
		TEXTMETRIC tm;
		dc.GetTextMetrics(&tm);  //获取当前字体结构，
		
		if(0x0d==nChar)  //响应回车键
		{
			m_strLine.Empty();
			m_PointOrigin.y+=tm.tmHeight;
		}
		
		else if(0x08==nChar) //响应退格键
		{
			COLORREF clr=dc.SetTextColor(dc.GetBkColor());
			dc.TextOut(m_PointOrigin.x,m_PointOrigin.y,m_strLine);
			m_strLine=m_strLine.Left(m_strLine.GetLength()-1);
			dc.SetTextColor(m_color);
		}
		else
		{
			m_strLine += (char)nChar;
		}
		
		CSize sz=dc.GetTextExtent(m_strLine);
		CPoint pt;
		pt.x=m_PointOrigin.x+sz.cx;
		pt.y=m_PointOrigin.y;
		SetCaretPos(pt);  //设定插入符位置
		dc.SetTextColor(m_color);
		dc.TextOut(m_PointOrigin.x,m_PointOrigin.y,m_strLine);  //输出字符串
//		nchar.m_strLine=m_strLine; 
	 }
	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}

void CMy2010302590054View::OnFill() 
{
	// TODO: Add your command handler code here
	PressNum=0;MenuID=19;
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void CMy2010302590054View::On3dspin() 
{
	// TODO: Add your command handler code here
	MenuID=30;
	Invalidate(TRUE);
}

int CMy2010302590054View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	InitializeOpenGL();
	return 0;
}

void CMy2010302590054View::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	if ( FALSE == ::wglDeleteContext( m_hRC ) )
	{
		SetError(6);
	}
	
    if ( m_pDC )
	{
        delete m_pDC;
	}
	if(m_bPlay)
		KillTimer(1);
}

BOOL CMy2010302590054View::OnEraseBkgnd(CDC* pDC) //更改文档背景
{
	// TODO: Add your message handler code here and/or call default
	   CBrush* oldBrush;
	   //m_brush可以在我们的类CMySkinView中进行定义
	   //并在CMySkinView初始化的时候创建该刷子
	   oldBrush=pDC->SelectObject(&m_Brush);  //选择新的刷子作为刷应用背景的刷子
	   CRect rcClip;
	   pDC->GetClipBox(&rcClip);  //得到背景需要刷新的区域
	   //用新的刷子刷背景区域
	   pDC->PatBlt(rcClip.left,rcClip.top,rcClip.Width(),rcClip.Height(),PATCOPY);
	   pDC->SelectObject(oldBrush);
	return TRUE;
	return CScrollView::OnEraseBkgnd(pDC);
}

void CMy2010302590054View::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	GLdouble aspect_ratio; // width/height ratio
	
	if ( 0 >= cx || 0 >= cy )
	{
		return;
	}
	
	
	SetupViewport( cx, cy );
	
	// select the projection matrix and clear it
    ::glMatrixMode( GL_PROJECTION );
    ::glLoadIdentity();
	
	// compute the aspect ratio
	// this will keep all dimension scales equal
	aspect_ratio = (GLdouble)cx/(GLdouble)cy;
	
	// select the viewing volumn
	SetupViewingFrustum( aspect_ratio );
	
	// switch back to the modelview matrix
    ::glMatrixMode( GL_MODELVIEW );
    ::glLoadIdentity();
	
	// now perform any viewing transformations
	SetupViewingTransform();
}

void CMy2010302590054View::SetError( int e )
{
	// if there was no previous error,
	// then save this one
	if ( _ErrorStrings[0] == m_ErrorString ) 
	{
		m_ErrorString = _ErrorStrings[e];
	}
}

BOOL CMy2010302590054View::InitializeOpenGL()
{
	// Can we put this in the constructor?
    m_pDC = new CClientDC(this);
	
    if ( NULL == m_pDC ) // failure to get DC
	{
		SetError(1);
		return FALSE;
	}
	
	if (!SetupPixelFormat())
	{
        return FALSE;
	}
	
    //n = ::GetPixelFormat(m_pDC->GetSafeHdc());
    //::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	
	//  CreateRGBPalette();
	
    if ( 0 == (m_hRC = ::wglCreateContext( m_pDC->GetSafeHdc() ) ) )
	{
		SetError(4);
		return FALSE;
	}
	
    if ( FALSE == ::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
	{
		SetError(5);
		return FALSE;
	}	
	
	// specify black as clear color

    ::glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	// specify the back of the buffer as clear depth
    ::glClearDepth( 1.0f );
	// enable depth testing
    ::glEnable( GL_DEPTH_TEST );
	
	return TRUE;
}

BOOL CMy2010302590054View::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
			1,                              // version number
			PFD_DRAW_TO_WINDOW |            // support window
			PFD_SUPPORT_OPENGL |          // support OpenGL
			PFD_DOUBLEBUFFER,             // double buffered
			PFD_TYPE_RGBA,                  // RGBA type
			24,                             // 24-bit color depth
			0, 0, 0, 0, 0, 0,               // color bits ignored
			0,                              // no alpha buffer
			0,                              // shift bit ignored
			0,                              // no accumulation buffer
			0, 0, 0, 0,                     // accum bits ignored
			//        32,                             // 32-bit z-buffer
			16,	// NOTE: better performance with 16-bit z-buffer
			0,                              // no stencil buffer
			0,                              // no auxiliary buffer
			PFD_MAIN_PLANE,                 // main layer
			0,                              // reserved
			0, 0, 0                         // layer masks ignored
    };
    int pixelformat;
	
    if ( 0 == (pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) )
	{
		SetError(2);
        return FALSE;
	}
	
    if ( FALSE == ::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) )
	{
       	SetError(3);
        return FALSE;
	}
	
    return TRUE;
}

BOOL CMy2010302590054View::SetupViewport( int cx, int cy )
{
	// select the full client area
    ::glViewport(0, 0, cx, cy);

	return TRUE;
}

BOOL CMy2010302590054View::SetupViewingFrustum( GLdouble aspect_ratio )
{
	// select a default viewing volumn
    ::gluPerspective( 40.0f, aspect_ratio, .1f, 20.0f );
	return TRUE;
}


BOOL CMy2010302590054View::SetupViewingTransform()
{
	// select a default viewing transformation
	// of a 20 degree rotation about the X axis
	// then a -5 unit transformation along Z
	::glTranslatef( 0.0f, 0.0f, -5.0f );
	::glRotatef( 20.0f, 1.0f, 0.0f, 0.0f );
    return TRUE;
}


BOOL CMy2010302590054View::RenderScene()
{
	GLfloat light_ambient[]={0.1f,0.1f,0.1f,1.0f};
	GLfloat light_diffuse[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat light_specular[]={1.0f,1.0f,1.0f,1.0f};


	GLfloat light_position[]={1.0f,1.0f,1.0f,0.0f};
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	
	glRotatef(20.0f,1.0f,0.0f,0.0f);
	glPushMatrix();
	glTranslatef(-0.75f,-0.5f,0.0f);
	glRotatef(239.0f,1.0f,0.0f,0.0f);
	auxSolidCone(1.0f,2.0f);
    


	glTranslatef(1.0,0.3f,1.0f);
	auxSolidSphere(0.5f);
	
    return TRUE;
}	

// Draw a square surface that looks like a
// black and white checkerboard
void CMy2010302590054View::RenderStockScene()
{
	// define all vertices   X     Y     Z
	GLfloat v0[3], v1[3], v2[3], v3[3], delta;
	int color = 0;

	delta = 0.5f;

	// define the two colors
	GLfloat color1[3] = { 0.9f, 0.9f, 0.9f };
 	GLfloat color2[3] = { 0.05f, 0.05f, 0.05f };

	v0[1] = v1[1] = v2[1] = v3[1] = 0.0f;

	::glBegin( GL_QUADS );

	for ( int x = -5 ; x <= 5 ; x++ )
		{
		for ( int z = -5 ; z <= 5 ; z++ )
			{
			::glColor3fv( (color++)%2 ? color1 : color2 );
		
			v0[0] = 0.0f+delta*z;
			v0[2] = 0.0f+delta*x;

			v1[0] = v0[0]+delta;
			v1[2] = v0[2];

			v2[0] = v0[0]+delta;
			v2[2] = v0[2]+delta;

			v3[0] = v0[0];
			v3[2] = v0[2]+delta;

			::glVertex3fv( v0 );
			::glVertex3fv( v1 );
			::glVertex3fv( v2 );
			::glVertex3fv( v3 );
			}
		}
	::glEnd();	
	
}


/******************************三维显示部分********************************/

 //绘制基座
void CMy2010302590054View::DrawBase(CDC *pDC)
{
	CRect rect;
	GetClientRect(&rect);
	int nClientWidth = rect.Width();
	int nClientHeight =rect.Height();
	
	int y =nClientHeight-20;
	int nBricks = nClientWidth/50;
	
	CBrick brick;
	
	int i = 0;
	//在指定区域布满“砖块”
	for(i=0;i<nBricks;i++)
		brick.Whole(pDC,(i*50),y,50,20);
	if((nClientWidth-50*nBricks)>0)
		brick.RightCutted(pDC,i*50,y,(nClientWidth-25*nBricks),20);
	
	y-=20;
	brick.LeftCutted(pDC,0,y,25,20);
	
	nBricks = (nClientWidth-25)/50;
	for(i=0;i<nBricks;i++)
		brick.Whole(pDC,25+(i*50),y,50,20);
	if((nClientWidth-50*nBricks-25)>0)
		brick.RightCutted(pDC,25+i*50,y,(nClientWidth-25*nBricks),20);
	
	y--;
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	
	pDC->MoveTo(9,y);
	pDC->LineTo(nClientWidth-9,y);
	
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

//绘制圆柱
void CMy2010302590054View::Drawpillar(CDC *pDC)
{
	CRect rect;
	GetClientRect(&rect);
	int nClientWidth = rect.Width();
	int nClientHeight =rect.Height();
	
	CVirtualCylinder vc;
	vc.SetColor(128,32,16);
	vc.Draw(pDC,0,0,9,nClientHeight-40);
	vc.Draw(pDC,nClientWidth-9,0,9,nClientHeight-40);
}

//绘制滑块
void CMy2010302590054View::DrawGlider(CDC *pDC, int x, int y)
{
	CBrick brick;
	brick.SetColor(50,128,255);
	brick.Whole(pDC,x,y,50,20);
}

//绘制小球
void CMy2010302590054View::DrawSphere(CDC *pDC, int x, int y)
{
	CVirtualSphere vs(30);
	vs.SetColor(255,255,255);
	vs.Draw(pDC,x,y);


}

/*
//设定计时器
int CMy2010302590054View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CMy2010302590054View::OnDestroy() 
{
	CView::OnDestroy();
	if(m_bPlay)
		KillTimer(1);
	// TODO: Add your message handler code here
	
}
*/

//响应计时器，显示动态场景
void CMy2010302590054View::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bPlay=TRUE)
	{
		CRect rect;
		GetClientRect(&rect);
		int nClientWidth = rect.Width();
		int nClientHeight =rect.Height();
		
		//碰壁反弹
		x+=m_nSpeedX;
		if(x>nClientWidth-25)
		{
			x = nClientWidth-25;
			m_nSpeedX = -m_nSpeedX;
		}
		
		else if(x<9)
		{
			
			x = 9;
			m_nSpeedX = -m_nSpeedX;
		}
		
		y+=m_nSpeedY;
		m_nSpeedY++;
		
		if(y>(nClientHeight-76))
		{
			y = 2*(nClientHeight-76)-y;
			m_nSpeedY = -m_nSpeedY;
		}
		
		else if(y<10)
			y = 10;
		
	Invalidate(FALSE);

	}
	
	CView::OnTimer(nIDEvent);
}


void CMy2010302590054View::OnStart() 
{
	// TODO: Add your command handler code here
	SetTimer(1,40,NULL);
	m_bPlay = TRUE;
	//Invalidate();
}


void CMy2010302590054View::OnStop() 
{
	// TODO: Add your command handler code here
	if(m_bPlay)
		KillTimer(1);
	
	
}



void CMy2010302590054View::OnRestart() 
{
	// TODO: Add your command handler code here
	x = 5;
	y = 10;
	m_nSpeedX = 8;
	m_nSpeedY = 2;
	SetTimer(1,40,NULL);
	m_bPlay = TRUE;

}

void CMy2010302590054View::OnEnd() 
{
	// TODO: Add your command handler code here
	if(m_bPlay)
		KillTimer(1);
	m_bPlay = FALSE;
	x = 5;
	y = 10;
	m_nSpeedX = 8;
	m_nSpeedY = 2;
	Invalidate();
}