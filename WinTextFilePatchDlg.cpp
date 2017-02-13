// WinTextFilePatchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinTextFilePatch.h"
#include "WinTextFilePatchDlg.h"

#include "SkinProgress.h"
#include "PathDialog.h"
#include "CPathSplit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinTextFilePatchDlg dialog

CWinTextFilePatchDlg::CWinTextFilePatchDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CWinTextFilePatchDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CWinTextFilePatchDlg)
  m_bChkTxtCrlf = FALSE;
  m_oChkTxtInclude = FALSE;
  m_oStrEncEnd = _T("");
  m_oStrEncStart = _T("");
  m_oStrFileDst = _T("");
  m_oStrFileSrc = _T("");
  m_oStrFileType = _T("");
  m_oStrTxtBody = _T("");
  m_oStrTxtEnd = _T("");
  m_oStrTxtEx = _T("");
  m_oStrTxtRmp = _T("");
  m_oStrTxtStart = _T("");
	//}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinTextFilePatchDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWinTextFilePatchDlg)
	DDX_Control(pDX, IDC_STA_WRK_TOT_PROG, m_oWndWrkTotProg);
  DDX_Control(pDX, IDC_ED_TXT_RMP, m_oEditTxtRmp);
  DDX_Control(pDX, IDC_ED_FILE_DST, m_oEditFileDst);
  DDX_Control(pDX, IDC_STA_WRK_TOT_TXT, m_oWndWrkTotTxt);
  DDX_Control(pDX, IDC_STA_WRK_FILE_TXT, m_oWndWrkFileTxt);
  DDX_Control(pDX, IDC_STA_WRK_FILE_PROG, m_oWndWrkFileProg);
  DDX_Control(pDX, IDC_BUT_WRK_RUN, m_oButWrkRun);
  DDX_Control(pDX, IDC_BUT_FILE_SRC, m_oButFileSrc);
  DDX_Control(pDX, IDC_BUT_FILE_DST, m_oButFileDst);
  DDX_Control(pDX, IDC_BUT_ENC_START_HTML, m_oButEncStartHtml);
  DDX_Control(pDX, IDC_BUT_ENC_START_CPP, m_oButEncStartCpp);
  DDX_Control(pDX, IDC_BUT_ENC_END_HTML, m_oButEncEndHtml);
  DDX_Control(pDX, IDC_BUT_ENC_END_CPP, m_oButEncEndCpp);
  DDX_Check(pDX, IDC_CHK_TXT_CRLF, m_bChkTxtCrlf);
  DDX_Check(pDX, IDC_CHK_TXT_INC, m_oChkTxtInclude);
  DDX_Text(pDX, IDC_ED_ENC_END, m_oStrEncEnd);
  DDX_Text(pDX, IDC_ED_ENC_START, m_oStrEncStart);
  DDX_Text(pDX, IDC_ED_FILE_DST, m_oStrFileDst);
  DDX_Text(pDX, IDC_ED_FILE_SRC, m_oStrFileSrc);
  DDX_Text(pDX, IDC_ED_FILE_TYPE, m_oStrFileType);
  DDX_Text(pDX, IDC_ED_TXT_BODY, m_oStrTxtBody);
  DDX_Text(pDX, IDC_ED_TXT_END, m_oStrTxtEnd);
  DDX_Text(pDX, IDC_ED_TXT_EX, m_oStrTxtEx);
  DDX_Text(pDX, IDC_ED_TXT_RMP, m_oStrTxtRmp);
  DDX_Text(pDX, IDC_ED_TXT_START, m_oStrTxtStart);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinTextFilePatchDlg, CDialog)
  //{{AFX_MSG_MAP(CWinTextFilePatchDlg)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BUT_FILE_SRC, OnButFileSrc)
  ON_BN_CLICKED(IDC_BUT_FILE_DST, OnButFileDst)
  ON_BN_CLICKED(IDC_BUT_ENC_START_HTML, OnButEncStartHtml)
  ON_BN_CLICKED(IDC_BUT_ENC_START_CPP, OnButEncStartCpp)
  ON_BN_CLICKED(IDC_BUT_ENC_END_HTML, OnButEncEndHtml)
  ON_BN_CLICKED(IDC_BUT_ENC_END_CPP, OnButEncEndCpp)
  ON_BN_CLICKED(IDC_BUT_WRK_RUN, OnButWrkRun)
  ON_EN_CHANGE(IDC_ED_TXT_START, OnChangeEdTxtStart)
  ON_EN_CHANGE(IDC_ED_TXT_BODY, OnChangeEdTxtBody)
  ON_EN_CHANGE(IDC_ED_TXT_END, OnChangeEdTxtEnd)
  ON_EN_CHANGE(IDC_ED_TXT_RMP, OnChangeEdTxtRmp)
	ON_EN_CHANGE(IDC_ED_FILE_DST, OnChangeEdFileDst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinTextFilePatchDlg message handlers

BOOL CWinTextFilePatchDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);      // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon
  
  // TODO: Add extra initialization here
  m_oButFileSrc.EnableWindow(TRUE);
  m_oButFileDst.EnableWindow(TRUE);
  m_oButWrkRun.EnableWindow(FALSE);

  m_oEditFileDst.SetBkColor(RGB(255, 255, 255));
  m_oEditTxtRmp.SetBkColor(RGB(255, 255, 255));
  
  m_bTestDestination = FALSE;
  m_bTestFile = FALSE;
  m_bTestReplace = FALSE;

  m_oStrAppPath = AfxGetApp()->m_pszHelpFilePath;
  m_oStrAppPath = m_oStrAppPath.Left(m_oStrAppPath.ReverseFind('\\')+1);

  m_oStrFileSrc  = m_oStrAppPath;
  m_oStrFileType = "htm;html";
  m_oStrFileDst  = m_oStrAppPath+"concate.htm";

  m_bChkTxtCrlf = TRUE;

  m_oStrTxtStart = "URL=";
  m_oStrTxtBody  = "body";
  m_oStrTxtEnd   = ">Click me !</";
  m_oStrTxtRmp   = "<a href=\"%body\">%body</a><br>";

  UpdateData(FALSE); // Put first data set into GUI

  VerifyDst();

  OnButEncStartHtml();
  OnButEncEndHtml();

  VerifyText();

  return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinTextFilePatchDlg::OnPaint() 
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialog::OnPaint();
  }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinTextFilePatchDlg::OnQueryDragIcon()
{
  return (HCURSOR) m_hIcon;
}

void CWinTextFilePatchDlg::OnButFileSrc() 
{
  // Update variables
  UpdateData(TRUE);

  CString     l_oStrBoite(_T("Source folder"));
  CString     l_oStrTitre(_T("Locate the place where are the files to process..."));
  CPathDialog PathSelect(l_oStrBoite, l_oStrTitre, m_oStrFileSrc);
  CFile       l_oFileTempo;
  CString     l_oStrFileName;

  if(PathSelect.DoModal() == IDOK)
  { // If OK
    m_oStrFileSrc = PathSelect.GetPathName() + "\\"; // Get selected directory
    m_oStrFileSrc.Replace("\\\\", "\\");

    // If destination directory empty, use source directory
    if(m_oStrFileDst.IsEmpty())
    {
      m_oStrFileDst = m_oStrFileSrc;
    }else{}

    UpdateData(FALSE);
    VerifyDst();
  }else{}

  // Update GUI
  VerifyRun();
}

void CWinTextFilePatchDlg::OnButFileDst() 
{
  // Update variables
  UpdateData(TRUE);

  CString     l_oStrBoite(_T("Destination folder"));
  CString     l_oStrTitre(_T("Locate the place where to write files..."));
  CPathDialog PathSelect(l_oStrBoite, l_oStrTitre, m_oStrFileDst);
  CFile       l_oFileTempo;
  CString     l_oStrFileName;

  if(PathSelect.DoModal() == IDOK)
  { // If OK
    m_oStrFileDst = PathSelect.GetPathName() + "\\"; // Get selected directory
    m_oStrFileDst.Replace("\\\\", "\\");

    // If source directory empty, use destination directory
    if(m_oStrFileSrc.IsEmpty())
    {
      m_oStrFileSrc = m_oStrFileDst;
    }else{}

    UpdateData(FALSE);
    VerifyDst();
  }else{}

  // Update GUI
  VerifyRun();
}

void CWinTextFilePatchDlg::OnButEncStartHtml()
{
  UpdateData(TRUE);
  m_oStrEncStart = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\r\n  <html>\r\n    <head>\r\n      <title>\r\n        Titre\r\n      </title>\r\n    </head>\r\n  <body>\r\n";
  UpdateData(FALSE);
}

void CWinTextFilePatchDlg::OnButEncStartCpp()
{
  UpdateData(TRUE);
  m_oStrEncStart = "/* Title */ \r\n\r\n#include \"stdafx.h\"\r\n\r\n";
  UpdateData(FALSE);
}

void CWinTextFilePatchDlg::OnButEncEndHtml()
{
  UpdateData(TRUE);
  m_oStrEncEnd = "  </body>\r\n</html>\r\n";
  UpdateData(FALSE);
}

void CWinTextFilePatchDlg::OnButEncEndCpp() 
{
  UpdateData(TRUE);
  m_oStrEncEnd = "/* End Title */\r\n";
  UpdateData(FALSE);
}

void CWinTextFilePatchDlg::OnButWrkRun() 
{
  CString      l_oStrTempo;
  CStringDicho l_oStrFileList;

  int          l_nTempo;
  int          l_nLoop;

  int          l_nPointerStart;
  int          l_nPointer;
  int          l_nPointerSize;

  CString      l_oStrFileNameDst;
  CString      l_oStrFolderDst;

  unsigned char* l_panDataIn = NULL;
  int            l_nDataInSize = 0;

  CString      l_oStrDataIn;
  CString      l_oStrDataTempo;
  CString      l_oStrDataReplace;
  CString      l_oStrDataOut;

  FILE*        l_hFileIn = NULL;
  FILE*        l_hFileOut = NULL;

  HANDLE          l_hFile;
  WIN32_FIND_DATA l_hFileFind;

//  CSkinProgress* l_oProgressFile; // Not yet currently used
  CSkinProgress* l_oProgressTotal;  

  //

  UpdateData(TRUE);

  m_oButFileSrc.EnableWindow(FALSE);
  m_oButFileDst.EnableWindow(FALSE);
  m_oButEncStartHtml.EnableWindow(FALSE);
  m_oButEncStartCpp.EnableWindow(FALSE);
  m_oButEncEndHtml.EnableWindow(FALSE);
  m_oButEncEndCpp.EnableWindow(FALSE);
  m_oButWrkRun.EnableWindow(FALSE);

  // Get file list according to extensions
  l_oStrTempo = m_oStrFileType;
  do
  {
    l_nTempo = l_oStrTempo.Find(';');
    if(l_nTempo < 0)
    {
      l_nTempo = l_oStrTempo.GetLength();
    }else{}

    l_oStrDataTempo = l_oStrTempo.Left(l_nTempo);
    if(l_oStrDataTempo.IsEmpty() == TRUE)
    {
      l_oStrDataTempo = "*";
    }
    else
    {
      l_oStrDataTempo.Remove('*');
      l_oStrDataTempo.Remove('.');
      l_oStrDataTempo.TrimLeft();
      l_oStrDataTempo.TrimRight();
    }

    l_oStrTempo = l_oStrTempo.Mid(l_nTempo);
    while(l_oStrTempo.Left(1) == ";")
    {
      l_oStrTempo = l_oStrTempo.Mid(1);
    }

    l_oStrDataTempo = m_oStrFileSrc+"\\*."+l_oStrDataTempo;
    while(l_oStrDataTempo.Replace("\\\\", "\\") != 0); // Erase double slash

    l_hFile = FindFirstFile(l_oStrDataTempo, &l_hFileFind);
    do
    {
      if
      (
           (l_hFile != INVALID_HANDLE_VALUE)
        && ((l_hFileFind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) 
      )
      {
        l_oStrDataTempo = m_oStrFileSrc+"\\"+l_hFileFind.cFileName;
        while(l_oStrDataTempo.Replace("\\\\", "\\") != 0); // Erase double slash
        l_oStrFileList.AddDicho(l_oStrDataTempo);
      }else{}
    }
    while(FindNextFile(l_hFile, &l_hFileFind));

    FindClose(l_hFile);
  }
  while(l_oStrTempo.IsEmpty() == FALSE);

  // Get the optional destination file name
  l_nTempo = m_oStrFileDst.ReverseFind('\\');
  if(l_nTempo >= 0)
  {
    l_oStrFileNameDst = m_oStrFileDst.Mid(l_nTempo+1);
    l_oStrFolderDst   = m_oStrFileDst.Left(l_nTempo+1);
  }else{}

  // Convert files
  l_nTempo = l_oStrFileList.GetSize();
  if(l_nTempo > 0)
  {
    l_oStrTempo.Format("1/%d ", l_nTempo);

#ifdef dCSP_DIALOG_PROGRESS
    l_oProgressTotal
    = new CSkinProgress
      ( &m_oWndWrkTotProg
      , l_nTempo
      , NULL
#ifdef dCSP_SLIDERBAR_METHOD
      , false
#endif // dCSP_SLIDERBAR_METHOD
      , &m_oWndWrkTotTxt
      , l_oStrTempo.GetBuffer(0)
      , -cSPT_TIMED
      )
    ;
#endif // dCSP_DIALOG_PROGRESS

    for
    ( l_nLoop = 0
    ; l_nLoop < l_nTempo
    ; l_nLoop += 1
    )
    {
      // Change the bar's text and progress it
      l_oStrTempo.Format("%d/%d ", l_nLoop+1, l_nTempo);
      l_oProgressTotal->SetText(l_oStrTempo);

      // Loading file
      l_oStrTempo = l_oStrFileList.GetAt(l_nLoop); // File to read
      if((l_hFileIn = fopen(l_oStrTempo, "rb")) != NULL)
      { // If opening OK
        fseek(l_hFileIn, 0, SEEK_END);
        l_nPointerSize = ftell(l_hFileIn);
        fseek(l_hFileIn, 0, SEEK_SET);

        if(l_nPointerSize > l_nDataInSize)
        {
          if(l_panDataIn != NULL)
          {
            delete [] l_panDataIn;
          }else{}
        }else{}

        l_nDataInSize = l_nPointerSize;
        l_panDataIn = new unsigned char[l_nDataInSize+2];

        l_panDataIn[l_nDataInSize+0] = 0; // For Unicode
        l_panDataIn[l_nDataInSize+1] = 0;
      }else{}

      if
      (
           (l_nDataInSize > 0)
        && (l_panDataIn != NULL)
      )
      {
        fread(l_panDataIn, 1, l_nDataInSize, l_hFileIn);
        fclose(l_hFileIn);

        // Creation of the output folder
        if(l_oStrFileNameDst.IsEmpty() == TRUE)
        { // If no destination file, create DataOut file
          l_nPointer = l_oStrTempo.ReverseFind('\\');
          if(l_nPointer >= 0)
          {
            l_oStrTempo = l_oStrTempo.Mid(l_nPointer+1);
          }else{}

          l_nPointer = l_oStrTempo.ReverseFind('.');
          if(l_nPointer < 0)
          {
            l_nPointer = l_oStrTempo.GetLength();
          }else{}

          l_oStrTempo = l_oStrTempo.Left(l_nPointer)+"_modified"+l_oStrTempo.Mid(l_nPointer); // New file
	        if((l_hFileOut = fopen(l_oStrFolderDst+l_oStrTempo, "wb")) != NULL)
          { // If opening of the destination file
            l_oStrDataOut = m_oStrEncStart;
          }else{}
        }
        else
        { // If destination file
          if(l_hFileOut == NULL)
          { // If not yet openend
	          if((l_hFileOut = fopen(l_oStrFolderDst+l_oStrFileNameDst, "wb")) != NULL)
            { // If opening of the destination file
              l_oStrDataOut = m_oStrEncStart;
            }else{}
          }else{}
        }

        // Process of the file
        l_oStrDataIn = l_panDataIn; // Loading data in a CString (can be very very huge)
        l_nPointerStart = 0;

        do
        {
          l_nPointer = l_oStrDataIn.Find(m_oStrTxtStart, l_nPointerStart);
          if(l_nPointer < 0)
          { // I not found anything else
            if(m_oChkTxtInclude == TRUE)
            {
              l_oStrDataOut += l_oStrDataIn.Mid(l_nPointerStart);
            }else{}
            l_nPointer = l_nDataInSize;
          }
          else
          { // I found the start
            if(m_oChkTxtInclude == TRUE)
            {
              l_oStrDataOut += l_oStrDataIn.Mid(l_nPointerStart, l_nPointer-l_nPointerStart);
            }else{}

            // Looking for the end AFTER the beginning
            l_nPointer += m_oStrTxtStart.GetLength(); // Start of the text to fetch
            l_nPointerSize = l_oStrDataIn.Find(m_oStrTxtEnd, l_nPointer);
            if(l_nPointerSize < 0)
            { // I not found anything else
              if(m_oChkTxtInclude == TRUE)
              {
                l_oStrDataOut += l_oStrDataIn.Mid(l_nPointer);
              }else{}
              l_nPointer = l_nDataInSize;
            }
            else
            { // I found the end
              l_oStrTempo = l_oStrDataIn.Mid(l_nPointer, l_nPointerSize-l_nPointer);

              l_oStrDataTempo   = "%"+m_oStrTxtBody;
              l_oStrDataReplace = m_oStrTxtRmp;
              l_oStrDataReplace.Replace(l_oStrDataTempo, l_oStrTempo);

              l_oStrDataOut += l_oStrDataReplace;

              // Place ourself AFTER the end
              l_nPointer = l_nPointerSize + m_oStrTxtEnd.GetLength(); // Start of the following stuff
            }
          }

          l_nPointerStart = l_nPointer;

          if(m_bChkTxtCrlf == TRUE)
          {
            l_oStrDataOut += "\r\n"; // Next line
          }else{}
        }
        while(l_nPointerStart < l_nDataInSize);
      }else{}

      // Close file
      if(l_hFileOut != NULL)
      {
        if(l_oStrFileNameDst.IsEmpty() == TRUE)
        { // If no destination file, close DataOut
          l_oStrDataOut += m_oStrEncEnd;
          fwrite(l_oStrDataOut.GetBuffer(0), 1, l_oStrDataOut.GetLength(), l_hFileOut);
          fclose(l_hFileOut);
        }
        else
        { // Write buffer in the destination file
          fwrite(l_oStrDataOut.GetBuffer(0), 1, l_oStrDataOut.GetLength(), l_hFileOut);
          fflush(l_hFileOut);
        }
      }else{}

      // Output buffer
      l_oStrDataOut.Empty();

      l_oProgressTotal->StepIt();
      PeekAndPump(); // Allow Windows to process messages and redraw the screen :)
    }

    if
    (
         (l_oStrFileNameDst.IsEmpty() == FALSE)
      && (l_hFileOut != NULL)
    )
    { // If destination file, colse it now
      l_oStrDataOut += m_oStrEncEnd;
      fwrite(l_oStrDataOut.GetBuffer(0), 1, l_oStrDataOut.GetLength(), l_hFileOut);
      fclose(l_hFileOut);
    }else{}

    if(l_oProgressTotal != NULL)
    {
      delete l_oProgressTotal;
    }else{}

    if(l_panDataIn != NULL)
    {
      delete [] l_panDataIn;
    }else{}
  }else{} // If files to process

  // Refresh all buttons
  m_oButFileSrc.EnableWindow(TRUE);
  m_oButFileDst.EnableWindow(TRUE);
  m_oButEncStartHtml.EnableWindow(TRUE);
  m_oButEncStartCpp.EnableWindow(TRUE);
  m_oButEncEndHtml.EnableWindow(TRUE);
  m_oButEncEndCpp.EnableWindow(TRUE);
  m_oButWrkRun.EnableWindow(TRUE);
}

void CWinTextFilePatchDlg::OnChangeEdTxtStart()
{
  VerifyText();
}

void CWinTextFilePatchDlg::OnChangeEdTxtBody()
{
  m_oStrTxtBody.Replace("%", "");
  VerifyText();
}

void CWinTextFilePatchDlg::OnChangeEdTxtEnd() 
{
  VerifyText();
}

void CWinTextFilePatchDlg::OnChangeEdTxtRmp() 
{
  VerifyText();
}

void CWinTextFilePatchDlg::VerifyText(void)
{
  CString l_oStrTempo;
  CString l_oStrReplace;
  int l_nPos;

  UpdateData(TRUE);

  //

  l_oStrTempo = "EXAMPLE";

  l_oStrReplace = "%"+m_oStrTxtBody;
  l_nPos = m_oStrTxtRmp.Find(l_oStrReplace);

  if
  (
       (m_oStrTxtRmp.IsEmpty() == TRUE)
    || (
       
            (m_oStrTxtRmp.IsEmpty() == FALSE)
         && (l_nPos >= 0)
       )
  )
  {
    m_oStrTxtEx = "Replace : " + m_oStrTxtStart + l_oStrTempo + m_oStrTxtEnd + "\r\nWith : " + m_oStrTxtRmp;
    m_oStrTxtEx.Replace(l_oStrReplace, l_oStrTempo);

    m_oEditTxtRmp.SetBkColor(RGB(255, 255, 255));
    m_bTestReplace = TRUE;
  }
  else
  {
    m_oStrTxtEx = "No body found !";
    m_oEditTxtRmp.SetBkColor(RGB(255, 191, 191));
    m_bTestReplace = FALSE;
  }

  VerifyRun();
}

void CWinTextFilePatchDlg::VerifyRun(void)
{
  if
  (
       (m_bTestDestination == TRUE)
    && (m_bTestFile == TRUE)
    && (m_bTestReplace == TRUE)
  )
  {
    m_oButWrkRun.EnableWindow(TRUE);
  }
  else
  {
    m_oButWrkRun.EnableWindow(FALSE);
  }

  UpdateData(FALSE);
}

void CWinTextFilePatchDlg::VerifyDst(void)
{
  CFile      l_oFileTempo;
  CString    l_oStrFileName;
  CPathSplit l_oPathSplitter;

  UpdateData(TRUE);

  if
  (
       (m_oStrFileDst.IsEmpty() == TRUE)
    || (m_oStrFileDst == " (READ ONLY FOLDER !)")
  )
  {
    m_oStrFileDst = m_oStrFileSrc;
  }else{}

  l_oPathSplitter.Split(m_oStrFileDst);

  // Test if we can write in the destination folder
  l_oStrFileName = l_oPathSplitter.GetPath(ePATHEL_DIRECTORY) + "test.tmp";

  if(l_oFileTempo.Open(l_oStrFileName, CFile::modeWrite|CFile::modeCreate))
  { // If file created/open, writing is possible
    l_oFileTempo.Close();
    l_oFileTempo.Remove(l_oStrFileName);

    m_bTestDestination = TRUE;
  }
  else
  {
    m_bTestDestination = FALSE;
  }

  if(
         !(m_oStrFileSrc.IsEmpty())   // If something to read
      && !(m_oStrFileDst.IsEmpty())   // If somewhere to write
      && (m_bTestDestination == TRUE) // If writing possible
    )
  { // Allow conversion
    m_oEditFileDst.SetBkColor(RGB(255, 255, 255));
    m_bTestFile = TRUE;
  }
  else
  {
    m_oStrFileDst += " (READ ONLY FOLDER !)";
    m_oEditFileDst.SetBkColor(RGB(255, 191, 191));
    m_bTestFile = FALSE;
  }
}

void CWinTextFilePatchDlg::OnChangeEdFileDst() 
{
  VerifyDst();

  UpdateData(FALSE);
}
