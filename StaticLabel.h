#if !defined(AFX_STATICLABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
#define AFX_STATICLABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StaticLabel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticLabel window
enum FlashType {None, Text, Background };

class CStaticLabel : public CStatic
{
// Construction
public:
	CStaticLabel();
	CStaticLabel& SetBkColor(COLORREF crBkgnd);
	CStaticLabel& SetTextColor(COLORREF crText);
	CStaticLabel& SetText(const CString& strText);
	CStaticLabel& SetFontBold(BOOL bBold);
	CStaticLabel& SetFontName(const CString& strFont);
	CStaticLabel& SetFontUnderline(BOOL bSet);
	CStaticLabel& SetFontItalic(BOOL bSet);
	CStaticLabel& SetFontSize(int nSize);
	CStaticLabel& SetFontStrikeOut(BOOL bSet);
	CStaticLabel& SetSunken(BOOL bSet);
	CStaticLabel& SetBorder(BOOL bSet);
	CStaticLabel& FlashText(BOOL bActivate);
	CStaticLabel& FlashBackground(BOOL bActivate);
	CStaticLabel& SetLink(BOOL bLink);
	CStaticLabel& SetLinkCursor(HCURSOR hCursor);

	void SetAutoRedraw(BOOL bSet) { m_bAutoRedraw=bSet; }
	void SetAutoFont(BOOL bSet) { m_bAutoFont=bSet; }
	void CreateFont(void) { ReconstructFont(); }
	void Refresh(void) { RedrawWindow(); }

// Attributes
public:
protected:
	void ReconstructFont();
	COLORREF	m_crText;
	HBRUSH		m_hBrush;
	HBRUSH		m_hwndBrush;
	LOGFONT		m_lf;
	CFont		m_font;
	CString		m_strText;
	BOOL		m_bState;
	BOOL		m_bTimer;
	BOOL		m_bLink;
	BOOL		m_bAutoRedraw,m_bAutoFont;
	FlashType	m_Type;
	HCURSOR		m_hCursor;
			// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticLabel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticLabel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticLabel)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICLABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
