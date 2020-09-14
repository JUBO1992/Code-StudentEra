// Brick.h: interface for the CBrick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRICK_H__FE3E2184_3BC6_4976_9E9F_B4668B6A3D0F__INCLUDED_)
#define AFX_BRICK_H__FE3E2184_3BC6_4976_9E9F_B4668B6A3D0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBrick  
{
public:
	void RightCutted(CDC *pDC, int x, int y, int nWidth, int nHeight);
	void LeftCutted(CDC *pDC,int x,int y,int nWidth,int nHeight);
	void Whole(CDC *pDC,int x,int y, int nWidth, int nHeight);
	void SetColor(BYTE byRed,BYTE byGreen,BYTE byBlue);
	CBrick();
	virtual ~CBrick();
	
private:
	BYTE m_byRed;
	BYTE m_byGreen;
	BYTE m_byBlue;
};

#endif // !defined(AFX_BRICK_H__FE3E2184_3BC6_4976_9E9F_B4668B6A3D0F__INCLUDED_)
