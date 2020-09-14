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
	//雷达滤波
	HDIB EPOSFilter(HDIB HOld,int n);//n*n为窗口大小
	HDIB MAPFilter(HDIB HOld,int m,int n);//窗口大小为m*n
	HDIB SigmaFilter(HDIB HOld,int m,int n);
	HDIB FrostFilter(HDIB HOld,int m,int n);
	HDIB KuanFilter(HDIB HOld,int m,int n,int flag);
	HDIB LeeFilter(HDIB HOld,int m,int n,int flag);
	//边缘检测模版
	HDIB EdgeDetectTemplate(HDIB HOld,int *X,int *Y,int n);//窗口大小为n*n
	//锐化
	HDIB GradSharp(HDIB HOld,int flag);
	//模板操作，Array为模板矩阵，m、n为模板行列数
	HDIB TemplateOperations(HDIB HOld,int *Array,int m,int n);

	unsigned char GetMediaNum(unsigned char *bArray,int iFilterLen);
	//均值滤波
	HDIB MeanFilter(HDIB HOld,int m,int n);
	//中值滤波
	HDIB MedianFilter(HDIB HOld,int m,int n);
	CPointTrans();
	virtual ~CPointTrans();

};

#endif // !defined(AFX_POINTTRANS_H__F74CE4F0_207B_4F39_81F2_F79C882706E3__INCLUDED_)
