// VirtualCylinder.h: interface for the CVirtualCylinder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUALCYLINDER_H__4F592172_6FF4_4FF6_BA84_F3DF305F5C11__INCLUDED_)
#define AFX_VIRTUALCYLINDER_H__4F592172_6FF4_4FF6_BA84_F3DF305F5C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVirtualCylinder  
{
public:
	void Draw(CDC *pDC, int x, int y, int nWidth, int nHeight);
	void SetColor(BYTE byRed,BYTE byGreen,BYTE byBlue);
	
	CVirtualCylinder();
	virtual ~CVirtualCylinder();
private:
	BYTE m_byRed;
	BYTE m_byGreen;
	BYTE m_byBlue;
};

#endif // !defined(AFX_VIRTUALCYLINDER_H__4F592172_6FF4_4FF6_BA84_F3DF305F5C11__INCLUDED_)
