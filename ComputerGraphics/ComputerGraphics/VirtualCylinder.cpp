// VirtualCylinder.cpp: implementation of the CVirtualCylinder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "2010302590054.h"
#include "VirtualCylinder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVirtualCylinder::CVirtualCylinder()
{
	m_byRed = 128;
	m_byGreen =128;
	m_byBlue = 128;
	
}

CVirtualCylinder::~CVirtualCylinder()
{
	
}

//设定圆柱颜色，可用于与对话框相接
void CVirtualCylinder::SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue)
{
	m_byRed = byRed;
	m_byGreen = byGreen;
	m_byBlue = byBlue;
	
}


//绘制圆柱，根据圆柱上点位不同置不同颜色
void CVirtualCylinder::Draw(CDC *pDC, int x, int y, int nWidth, int nHeight)
{
	if(nWidth<1) 
		return;
	
	float fRed = m_byRed;
	float fGreen = m_byGreen;
	float fBlue = m_byBlue;
	
	float fIncR = (2.0f*(255-m_byRed))/nWidth;
	float fIncG = (2.0f*(255-m_byGreen))/nWidth;
	float fIncB = (2.0f*(255-m_byBlue))/nWidth;
	int i;
	for(i=0;i<nWidth/2;i++)
	{
		CPen pen(PS_SOLID,1,RGB((BYTE)fRed,(BYTE)fGreen,(BYTE)fBlue));
		CPen *pOldPen = pDC->SelectObject(&pen);
		
		pDC->MoveTo(x+i,y);
		pDC->LineTo(x+i,y+nHeight);
		pDC->MoveTo(x+nWidth-i-1,y);
		pDC->LineTo(x+nWidth-i-1,y+nHeight);
		
        fRed+=fIncR;
		fGreen+=fIncG;
		fBlue+=fIncB;
		
		pDC->SelectObject(pOldPen);
		pen.DeleteObject();
		
	}
	
	CPen pen(PS_SOLID,1,RGB(255,255,255));
	CPen *pOldPen = pDC->SelectObject(&pen);
	
	pDC->MoveTo(x+i,y);
	pDC->LineTo(x+i,y+nHeight);
	
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	
}
