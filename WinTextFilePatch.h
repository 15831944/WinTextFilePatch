// WinTextFilePatch.h : main header file for the WINTEXTFILEPATCH application
//

#if !defined(AFX_WINTEXTFILEPATCH_H__2F9AA110_6E21_4861_82B8_5C2086F36D9E__INCLUDED_)
#define AFX_WINTEXTFILEPATCH_H__2F9AA110_6E21_4861_82B8_5C2086F36D9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinTextFilePatchApp:
// See WinTextFilePatch.cpp for the implementation of this class
//

class CWinTextFilePatchApp : public CWinApp
{
public:
	CWinTextFilePatchApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinTextFilePatchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinTextFilePatchApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINTEXTFILEPATCH_H__2F9AA110_6E21_4861_82B8_5C2086F36D9E__INCLUDED_)
