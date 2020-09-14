// VirtualSphere.h: interface for the CVirtualSphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUALSPHERE_H__7D4D7AAE_05FA_4E57_B9CF_C4373BB25D73__INCLUDED_)
#define AFX_VIRTUALSPHERE_H__7D4D7AAE_05FA_4E57_B9CF_C4373BB25D73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVirtualSphere  
{
public:
	void Draw(CDC *pDC,int x,int y);
	void SetPrecision(int nDifPrecision, int nSpePrecision);
	void SetColor(BYTE byRed,BYTE byGreen,BYTE byBlue);
	
	CVirtualSphere(int nRadius);
	virtual ~CVirtualSphere();
	
private:
	int m_nRadius;
	BYTE m_byRed;
	BYTE m_byGreen;
	BYTE m_byBlue;
	int m_nDifPrecision;
	int m_nSpePresion;
};

#endif // !defined(AFX_VIRTUALSPHERE_H__7D4D7AAE_05FA_4E57_B9CF_C4373BB25D73__INCLUDED_)
