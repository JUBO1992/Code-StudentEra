// PointTrans.h: interface for the CPointTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTTRANS_H__F74CE4F0_207B_4F39_81F2_F79C882706E3__INCLUDED_)
#define AFX_POINTTRANS_H__F74CE4F0_207B_4F39_81F2_F79C882706E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPointTrans  
{
public:
	//�״��˲�
	HDIB EPOSFilter(HDIB HOld,int n);//n*nΪ���ڴ�С
	HDIB MAPFilter(HDIB HOld,int m,int n);//���ڴ�СΪm*n
	HDIB SigmaFilter(HDIB HOld,int m,int n);
	HDIB FrostFilter(HDIB HOld,int m,int n);
	HDIB KuanFilter(HDIB HOld,int m,int n,int flag);
	HDIB LeeFilter(HDIB HOld,int m,int n,int flag);
	//��Ե���ģ��
	HDIB EdgeDetectTemplate(HDIB HOld,int *X,int *Y,int n);//���ڴ�СΪn*n
	//��
	HDIB GradSharp(HDIB HOld,int flag);
	//ģ�������ArrayΪģ�����m��nΪģ��������
	HDIB TemplateOperations(HDIB HOld,int *Array,int m,int n);

	unsigned char GetMediaNum(unsigned char *bArray,int iFilterLen);
	//��ֵ�˲�
	HDIB MeanFilter(HDIB HOld,int m,int n);
	//��ֵ�˲�
	HDIB MedianFilter(HDIB HOld,int m,int n);
	CPointTrans();
	virtual ~CPointTrans();

};

#endif // !defined(AFX_POINTTRANS_H__F74CE4F0_207B_4F39_81F2_F79C882706E3__INCLUDED_)
