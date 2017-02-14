// WinTextFilePatchDlg.h : header file
//

#if !defined(AFX_WINTEXTFILEPATCHDLG_H__A44BAA2D_F890_4C9F_AE48_CA462D94AF5A__INCLUDED_)
#define AFX_WINTEXTFILEPATCHDLG_H__A44BAA2D_F890_4C9F_AE48_CA462D94AF5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EditLabel.h"

#define dCSD_2N_POWER
class CStringDicho : public CStringArray
{
  public :
    CStringDicho
    (
    )
    {
    }

    int AddDicho
    ( CString const& i_poString
    )
    {
      if(GetSize() > 0)
      {
        if(FindDicho(i_poString, TRUE) < 0)
        {
          InsertAt(m_nDichoMed + m_nDichoDlt, i_poString); 
        }else{}

        return m_nDichoMed;
      }
      else
      {
        Add(i_poString);
        return 0;
      }
    }

    int FindDicho
    ( CString const& i_poString
    , BOOL           i_bExactPlace = TRUE
    )
    {
      m_nDichoMax = GetSize();
      if(m_nDichoMax > 0)
      {
        m_nDichoMin = 0;
        m_nDichoDlt = 0;

#ifdef dCSD_2N_POWER
        m_nDichoMed = m_nDichoMax;
        for
        ( m_nDichoInt   = 0
        ; m_nDichoMed  >  0
        ; m_nDichoMed >>= 1
        )
        {
          m_nDichoInt += 1;
        };

        m_nDichoMed = (m_nDichoMin + m_nDichoMax) / 2;

        for
        (
        ; m_nDichoInt > 0
        ; m_nDichoInt -= 1
        )
        {
          m_oBuffer   = GetAt(m_nDichoMed);
          if(i_poString >= m_oBuffer)
          {
            m_nDichoMin = m_nDichoMed;
            m_nDichoDlt = 1;
          }
          else
          {
            m_nDichoMax = m_nDichoMed;
          }
          m_nDichoMed = (m_nDichoMin + m_nDichoMax) / 2;
        }
#else
        m_nDichoMed = (m_nDichoMin + m_nDichoMax) / 2;
        do
        {
          m_oBuffer   = GetAt(m_nDichoMed);
          if(i_poString >= m_oBuffer)
          {
            m_nDichoMin = m_nDichoMed;
            m_nDichoDlt = 1;
          }
          else
          {
            m_nDichoMax = m_nDichoMed;
          }
          m_nDichoMed = (m_nDichoMin + m_nDichoMax) / 2;
        }
        while
        (
          m_nDichoMax > (m_nDichoMed + m_nDichoDlt)
        );
#endif // dCSD_2N_POWER

        if
        (
             (i_bExactPlace == TRUE)
          && (i_poString    != GetAt(m_nDichoMed))
        )
        { // return (-1) un peu plus loin
        }
        else
        {
          return m_nDichoMed;
        }
      }else{};

      return (-1);
    }
    
  protected :
    int     m_nDichoMin;
    int     m_nDichoMed;
    int     m_nDichoMax;
    int     m_nDichoDlt;
#ifdef dCSD_2N_POWER
    int     m_nDichoInt;
#endif // dCSD_2N_POWER
    CString m_oBuffer;
};

/////////////////////////////////////////////////////////////////////////////
// CWinTextFilePatchDlg dialog

class CWinTextFilePatchDlg : public CDialog
{
// Construction
public:
  CWinTextFilePatchDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
  //{{AFX_DATA(CWinTextFilePatchDlg)
	enum { IDD = IDD_WINTEXTFILEPATCH_DIALOG };
	CStatic	m_oWndWrkTotProg;
  CEditLabel m_oEditTxtRmp;
  CEditLabel m_oEditFileDst;
  CStatic  m_oWndWrkTotTxt;
  CStatic  m_oWndWrkFileTxt;
  CStatic  m_oWndWrkFileProg;
  CButton  m_oButWrkRun;
  CButton  m_oButFileSrc;
  CButton  m_oButFileDst;
  CButton  m_oButEncStartHtml;
  CButton  m_oButEncStartCpp;
  CButton  m_oButEncEndHtml;
  CButton  m_oButEncEndCpp;
  BOOL  m_bChkTxtCrlf;
  BOOL  m_bChkTxtInclude;
  CString  m_oStrEncEnd;
  CString  m_oStrEncStart;
  CString  m_oStrFileDst;
  CString  m_oStrFileSrc;
  CString  m_oStrFileType;
  CString  m_oStrTxtBody;
  CString  m_oStrTxtEnd;
  CString  m_oStrTxtEx;
  CString  m_oStrTxtRmp;
  CString  m_oStrTxtStart;
	//}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CWinTextFilePatchDlg)
	protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
	//}}AFX_VIRTUAL

  void VerifyText(void);
  void VerifyRun(void);
  void VerifyDst(void);

  void SaveParams(void);

// Implementation
protected:
  HICON m_hIcon;
  BOOL  m_bTestDestination;
  BOOL  m_bTestFile;
  BOOL  m_bTestReplace;

  CString m_oStrAppPath;

  // Generated message map functions
  //{{AFX_MSG(CWinTextFilePatchDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg void OnButFileSrc();
  afx_msg void OnButFileDst();
  afx_msg void OnButEncStartHtml();
  afx_msg void OnButEncStartCpp();
  afx_msg void OnButEncEndHtml();
  afx_msg void OnButEncEndCpp();
  afx_msg void OnButWrkRun();
  afx_msg void OnChangeEdTxtStart();
  afx_msg void OnChangeEdTxtBody();
  afx_msg void OnChangeEdTxtEnd();
  afx_msg void OnChangeEdTxtRmp();
	afx_msg void OnChangeEdFileDst();
	afx_msg void OnDestroy();
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINTEXTFILEPATCHDLG_H__A44BAA2D_F890_4C9F_AE48_CA462D94AF5A__INCLUDED_)
