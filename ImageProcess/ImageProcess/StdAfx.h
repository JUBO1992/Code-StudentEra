// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include <SDKDDKVer.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

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
