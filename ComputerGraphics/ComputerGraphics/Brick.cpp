// Brick.cpp: implementation of the CBrick class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "2010302590054.h"
#include "Brick.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//��ʼ�����Ա
CBrick::CBrick()
{
	m_byRed = 160;
	m_byGreen = 24;
	m_byBlue = 10;

}

CBrick::~CBrick()
{

}

void CBrick::SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue)
{
	m_byRed = byRed;
	m_byGreen = byGreen;
	m_byBlue = byBlue;

}

//������ש�飬���ɲ�ͬ��ɫ�Ļ��ʣ�����ש���ϵ�λ�ò�ͬ��������ͬ�ĻҶ�ֵ���Ӷ�����3DЧ��
void CBrick::Whole(CDC *pDC, int x, int y, int nWidth, int nHeight)
{
	//���ɾ��β���䣬��ש���ɫ
	CBrush brush(RGB(m_byRed,m_byGreen,m_byBlue));
	CRect rect(x+1,y+1,x+nWidth-2,y+nHeight-2);
	pDC->FillRect(&rect,&brush);
	brush.DeleteObject();

	//ש��ϸ����ɫ����
	CPen whitePen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen = pDC->SelectObject(&whitePen);
	pDC->MoveTo(x+nWidth-1,y);
	pDC->LineTo(x,y);
	pDC->LineTo(x,y+nHeight);
	pDC->SelectObject(pOldPen);
	whitePen.DeleteObject();

	CPen grayPen(PS_SOLID,1,RGB(128,128,128));
	CPen *pOldPen_1 = pDC->SelectObject(&grayPen);
	pDC->MoveTo(x+1,y+nHeight-2);
	pDC->LineTo(x+nWidth-2,y+nHeight-2);
	pDC->LineTo(x+nWidth-2,y);
	pDC->SelectObject(pOldPen_1);
	grayPen.DeleteObject();

	CPen blackPen(PS_SOLID,1,RGB(0,0,0));
	CPen *pOldPen_2 = pDC->SelectObject(&grayPen);
	pDC->MoveTo(x,y+nHeight-1);
	pDC->LineTo(x+nWidth-1,y+nHeight-1);
	pDC->LineTo(x+nWidth-1,y-1);
	pDC->SelectObject(pOldPen_2);
	grayPen.DeleteObject();
}

//������ש������ͬ��
void CBrick::LeftCutted(CDC *pDC, int x, int y, int nWidth, int nHeight)
{
	CBrush brush(RGB(m_byRed,m_byGreen,m_byBlue));
	CRect rect(x,y,x+nWidth-2,y+nHeight-2);
	pDC->FillRect(&rect,&brush);
	brush.DeleteObject();
	
	CPen whitePen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen = pDC->SelectObject(&whitePen);
	pDC->MoveTo(x,y);
	pDC->LineTo(x+nWidth,y);
	pDC->SelectObject(pOldPen);
	whitePen.DeleteObject();
	
	CPen grayPen(PS_SOLID,1,RGB(128,128,128));
	CPen *pOldPen_1 = pDC->SelectObject(&grayPen);
	pDC->MoveTo(x,y+nHeight-2);
	pDC->LineTo(x+nWidth-2,y+nHeight-2);
	pDC->LineTo(x+nWidth-2,y);
	pDC->SelectObject(pOldPen_1);
	grayPen.DeleteObject();
	
	CPen blackPen(PS_SOLID,1,RGB(0,0,0));
	CPen *pOldPen_2 = pDC->SelectObject(&grayPen);
	pDC->MoveTo(x,y+nHeight-1);
	pDC->LineTo(x+nWidth-1,y+nHeight-1);
	pDC->LineTo(x+nWidth-1,y-1);
	pDC->SelectObject(pOldPen_2);
	grayPen.DeleteObject();

}

//���Ұ��ש
void CBrick::RightCutted(CDC *pDC, int x, int y, int nWidth, int nHeight)
{
	CBrush brush(RGB(m_byRed,m_byGreen,m_byBlue));
	CRect rect(x+1,y+1,x+nWidth-1,y+nHeight-1);
	pDC->FillRect(&rect,&brush);
	brush.DeleteObject();
	
	CPen whitePen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen = pDC->SelectObject(&whitePen);
	pDC->MoveTo(x+nWidth-1,y);
	pDC->LineTo(x,y);
	pDC->LineTo(x,y+nHeight);
	pDC->SelectObject(pOldPen);
	whitePen.DeleteObject();
	
	CPen grayPen(PS_SOLID,1,RGB(128,128,128));
	CPen *pOldPen_1 = pDC->SelectObject(&grayPen);
	pDC->MoveTo(x+1,y+nHeight-2);
	pDC->LineTo(x+nWidth-2,y+nHeight-2);
	pDC->SelectObject(pOldPen_1);
	grayPen.DeleteObject();
	
	CPen blackPen(PS_SOLID,1,RGB(0,0,0));
	CPen *pOldPen_2 = pDC->SelectObject(&grayPen);
	pDC->MoveTo(x,y+nHeight-1);
	pDC->LineTo(x+nWidth-1,y+nHeight-1);
	pDC->SelectObject(pOldPen_2);
	grayPen.DeleteObject();
}