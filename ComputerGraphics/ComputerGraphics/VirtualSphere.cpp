// VirtualSphere.cpp: implementation of the CVirtualSphere class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "2010302590054.h"
#include "VirtualSphere.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//��ʼ��Բ��
CVirtualSphere::CVirtualSphere(int nRadius)
{
	m_nRadius = nRadius;
	if(m_nRadius<1)
		m_nRadius = 20;
	m_byRed = 192;
	m_byGreen = 192;
	m_byBlue = 192;

	m_nDifPrecision = 20;
	m_nSpePresion = 5;

}

CVirtualSphere::~CVirtualSphere()
{

}

//�趨��ɫ������Ի������
void CVirtualSphere::SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue)
{
	m_byRed = byRed;
	m_byGreen = byGreen;
	m_byBlue = byBlue;
}


//�趨���������򡢾��淴������ıƽ�����
void CVirtualSphere::SetPrecision(int nDifPrecision, int nSpePrecision)
{
	m_nDifPrecision = nDifPrecision;
	m_nSpePresion = nSpePrecision;
	if(m_nDifPrecision<1)
		m_nDifPrecision = 1;
	if(m_nSpePresion<1)
		m_nSpePresion =1;
}


//����������ά��
void CVirtualSphere::Draw(CDC *pDC, int x, int y)
{
	pDC->SelectStockObject(NULL_PEN);

	//����������ĵ�λ����
	int nDifTimes = min(m_nDifPrecision,m_nRadius);
	int nDenominator = (7 * nDifTimes);
	int i = 0;
	for(i=0;i<nDifTimes;i++) //������������ɫֵ
	{
		BYTE byRed = (BYTE)(i*m_byRed*4)/nDenominator+3*(int)m_byRed/7;
		BYTE byGreen = (BYTE)(i*m_byGreen*4)/nDenominator+3*(int)m_byGreen/7;
		BYTE byBlue = (BYTE)(i*m_byBlue*4)/nDenominator+3*(int)m_byBlue/7;

		CBrush brush;
		brush.CreateSolidBrush(RGB(byRed, byGreen, byBlue));
		CBrush *pOldBrush = pDC->SelectObject(&brush);
        
		//����Բ����ĸ���λ������
		int xLT = x + i; 
		int yLT = y +(i*2)/5;

		int nSize = m_nRadius -(5*i)/4+1;
		int xRB = xLT + nSize;
		int yRB = yLT + nSize;
		
		pDC->Ellipse(xLT, yLT, xRB, yRB);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
	}

	//���淴������
	int nSpeTimes = min(m_nSpePresion ,(m_nRadius-nDifTimes));
	if(nSpeTimes<1)
		return;

	nDenominator = 2*nSpeTimes;

	
	for(i=0;i<nSpeTimes;i++)
	{
	    int nIndex = i+nDifTimes;
		
		BYTE byRed = (BYTE)(m_byRed+((255-m_byRed)*i)/nDenominator);
		BYTE byGreen = (BYTE)(m_byGreen+((255-m_byGreen)*i)/nDenominator);
		BYTE byBlue = (BYTE)(m_byBlue+((255-m_byBlue)*i)/nDenominator);
		
		CBrush brush;
		brush.CreateSolidBrush(RGB(byRed, byGreen, byBlue));
		CBrush *pOldBrush = pDC->SelectObject(&brush);
        
		int xLT = x + nIndex; 
		int yLT = y + (nIndex*2)/5;
		
		int nSize = m_nRadius -(5*nIndex)/4+1;
		int xRB = xLT + nSize;
		int yRB = yLT + nSize;
		
		pDC->Ellipse(xLT, yLT, xRB, yRB);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
	}   


}
