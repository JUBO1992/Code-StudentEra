// PeakDetectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imageprocess.h"
#include "PeakDetectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPeakDetectDlg dialog


CPeakDetectDlg::CPeakDetectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPeakDetectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPeakDetectDlg)
	m_FilePath = _T("");
	m_WaveNumber = 0;
	//}}AFX_DATA_INIT
}


void CPeakDetectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPeakDetectDlg)
	DDX_Text(pDX, IDC_FILEPATH, m_FilePath);
	DDX_Text(pDX, IDC_WAVENUMBER, m_WaveNumber);
	DDV_MinMaxInt(pDX, m_WaveNumber, 1, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPeakDetectDlg, CDialog)
	//{{AFX_MSG_MAP(CPeakDetectDlg)
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenfile)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_COUNTPEAK, OnCountpeak)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPeakDetectDlg message handlers

BOOL CPeakDetectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i,j;
	for(i=0;i<16;i++)
		for(j=0;j<128;j++)
			Wave[i][j]=0;
	m_WaveNumber = 5;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 void CPeakDetectDlg::OnPaint() 
 { 
	 //	CPaintDC dc(this); // device context for painting
    CRect rect;
 	CWnd *pwnd;
 	pwnd=GetDlgItem(IDC_WAVESHOW);// IDC_WAVESHOW是我们在对话框中添加的图片控件的ID号
 	pwnd->GetClientRect(&rect);
 	CClientDC dc(pwnd);//注意 	
	CPen PenNew;
 	PenNew.CreatePen(PS_SOLID,1,RGB(0,0,255));
 	CPen *pPenOld;
 	pPenOld=dc.SelectObject(&PenNew);
 	int d=-1;
 	dc.MoveTo(0,rect.Height()+d); 	
	dc.LineTo (rect.Width (),rect.Height ()+d);
 	dc.MoveTo (0,rect.Height ()+d);
	dc.LineTo (0,0);
 	int h = m_WaveNumber-1;
 	int i;
	for(i=0;i<9;i++)//刻画纵坐标刻度
	{
		dc.MoveTo(0,rect.Height()-32*i+d);
		dc.LineTo(5,rect.Height()-32*i+d);
		CString str;
		str.Format("%d",8*i);
//		TextOut(dc,-10,rect.Height()-32*i-10,str,2);
		dc.TextOut(-20,rect.Height()-32*i-10,str);
	}

 	for (i=0;i<127;i++)
 	{
 		dc.MoveTo(4*i+1,(rect.Height ()-4*Wave[h][i])+d);
 		dc.LineTo(4*(i+1)+1,(rect.Height ()-4*Wave[h][i+1])+d);
		if((i+1)%8 == 0)//刻画横坐标刻度
		{
			dc.MoveTo(4*i+1,rect.Height()+d);
			dc.LineTo(4*i+1,rect.Height()-6);
			CString str;
			str.Format("%d",i+1);
	    	dc.TextOut(4*i-8,rect.Height()+5,str);
		}
 	}
 	dc.SelectObject(pPenOld);
 	PenNew.DeleteObject();
 	// TODO: Add your message handler code here
 	
 	// Do not call CDialog::OnPaint() for painting messages
 }

void CPeakDetectDlg::OnOpenfile() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE filetype[]="TXT Files(*.TXT)|*.txt|所有文件(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filetype,NULL );
	if(dlg.DoModal()==IDOK)
		m_FilePath = dlg.GetPathName();
	else
		return ;
	FILE *fp;
	fp=fopen(m_FilePath,"r");
	int i,j;
	for(i=0;i<16;i++)
		for(j=0;j<128;j++)
			fscanf(fp,"%d,",&Wave[i][j]);
	UpdateData(FALSE);
}

void CPeakDetectDlg::OnUpdate() 
{
	// TODO: Add your control notification handler code here
	Invalidate(FALSE);
	UpdateData(TRUE);
	if((1<=m_WaveNumber)&&(m_WaveNumber<=16))
		OnPaint();

}

void CPeakDetectDlg::OnCountpeak() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int Num = m_WaveNumber-1;//下标比波段号小1
	int W[128];
	int i,j,k=0;
	int avg = 0;
	for(i=0;i<128;i++)//求波平均值
	{
		W[i] = Wave[Num][i];
		avg += W[i];
	}
	avg = avg/128;

	int flag=0,n,f=0;
	int PeakNum=0,PeakWidth =0;
	POINT V[10];
	for(i=8;i<120;i++)
	{			
		if(i>=15)//波峰判断准则一：波峰高于周围15个点
		{
			for(n=1;n<16;n++)
				if(W[i]>W[i-n]&&W[i]>W[i+n])
					f++;
				else
					break;
		}
		for(j=0;j<6;j++)//波峰判断准则二：波峰向两边辐射，前一个点依次高于后一个点
		{

			if(W[i+j]>=W[i+j+1]&&W[i-j]>=W[i-j-1])
				flag++;
			else
				break;
		}
		if((flag == 6||f == 15) && W[i]>avg)//波峰判断准则三：波峰高于平均值
		{
			PeakNum++;
			V[k].x=i;
    		V[k].y=W[i];
			k++;
			i=i+6;
		}
		flag = 0;
		f=0;
	}
	CRect rect;
	CWnd *pwnd;
	pwnd=GetDlgItem(IDC_WAVESHOW);// IDC_WAVESHOW是我们在对话框中添加的图片控件的ID号
	pwnd->GetClientRect(&rect);
 	CClientDC dc(pwnd);//注意 
	CString str;
	str.Format("%d",PeakNum);
	dc.TextOut(rect.Width()+65,rect.Height()-80,str);
	str.Format("%d",PeakWidth);
	dc.TextOut(rect.Width()+65,rect.Height()-52,str);
	for(i=0;i<PeakNum;i++)
	{
		POINT p;
		p.x = 4*V[i].x+1;
		p.y = (rect.Height ()-4*V[i].y);
		dc.Ellipse(p.x-5,p.y-5,p.x+5,p.y+5);

	}
	UpdateData(FALSE);

	CString tmp;
	tmp.Format(_T("波峰数目是%d，宽度%d"),PeakNum,PeakWidth);
	AfxMessageBox(tmp,MB_OKCANCEL);

//	AfxMessageBox("波峰数目是%d，宽度%d,Num,Num",MB_OK);
}

void CPeakDetectDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	Invalidate(TRUE);
}
