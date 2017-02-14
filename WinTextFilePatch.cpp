// WinTextFilePatch.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WinTextFilePatch.h"
#include "WinTextFilePatchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinTextFilePatchApp

BEGIN_MESSAGE_MAP(CWinTextFilePatchApp, CWinApp)
	//{{AFX_MSG_MAP(CWinTextFilePatchApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinTextFilePatchApp construction

CWinTextFilePatchApp::CWinTextFilePatchApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWinTextFilePatchApp object

CWinTextFilePatchApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWinTextFilePatchApp initialization

BOOL CWinTextFilePatchApp::InitInstance()
{
	SetRegistryKey(_T("Kochise"));
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	CWinTextFilePatchDlg dlg;
	m_pMainWnd = &dlg;
	
  int nResponse = dlg.DoModal();

	if(nResponse == IDOK)
	{
	}
	else if(nResponse == IDCANCEL)
	{
	}else{}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
