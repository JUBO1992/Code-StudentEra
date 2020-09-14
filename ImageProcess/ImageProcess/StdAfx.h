// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include <SDKDDKVer.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

// #ifdef _UNICODE 
#if defined _M_IX86  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#elif defined _M_X64  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#else  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#endif  
// #endif

#include "math.h"
//GDAL
#include "gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

//skin sharp  ./Skin/
#pragma comment(lib,"SkinH.lib")
#include "SkinH.h"

//DIB
DECLARE_HANDLE(HDIB);
#define PALVERSION   0x300
#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')
extern "C" _declspec(dllimport) BOOL PaintDIB (HDC, LPRECT, HDIB, LPRECT, CPalette* pPal);
extern "C" _declspec(dllimport) BOOL CreateDIBPalette(HDIB hDIB, CPalette* cPal);
extern "C" _declspec(dllimport) LPSTR FindDIBBits (LPSTR lpbi);
extern "C" _declspec(dllimport) DWORD DIBWidth (LPSTR lpDIB);
extern "C" _declspec(dllimport) DWORD DIBHeight (LPSTR lpDIB);
extern "C" _declspec(dllimport) DWORD PaletteSize (LPSTR lpbi);
extern "C" _declspec(dllimport) DWORD DIBNumColors (LPSTR lpbi);
extern "C" _declspec(dllimport) void HGLOBALCopyHandle (HGLOBAL h);
extern "C" _declspec(dllimport) BOOL SaveDIB (HDIB hDib, CFile& file);
extern "C" _declspec(dllimport) HDIB ReadDIBFile(CFile& file);
/**********************************************************************/
extern "C" _declspec(dllimport) void InitDIBData(HDIB m_hDIB);
extern "C" _declspec(dllimport) HDIB Open(LPCTSTR lpszPathName);
extern "C" _declspec(dllimport) BOOL Save(LPCTSTR lpszPathName,HDIB m_hDIB);
extern "C" _declspec(dllimport) void Draw(CDC* pDC,HDIB hDIB);
#pragma comment(lib,"dib.lib")

#include "ImageProcess.h"
#include "ImageProcessDoc.h"
#include "ImageProcessView.h"

#include "ClassifyDlg.h"
#include "PeakDetectDlg.h"
#include "ChanMoniDlg.h"
#include "LadarPointDlg.h"
#include "ISODATA.h"
#include "KLTransDlg.h"
#include "NDVIDlg.h"
#include "HISFusionDlg.h"
#include "ZoomDlg.h"
#include "RotateDlg.h"
#include "LinearEnhanceDlg.h"
#include "HistogramDlg.h"
#include "PointTrans.h"
