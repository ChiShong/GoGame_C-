#if !defined(AFX_PLAYSTATUSDLG_H__0A0636D9_DA98_4190_9227_056BB8427DDE__INCLUDED_)
#define AFX_PLAYSTATUSDLG_H__0A0636D9_DA98_4190_9227_056BB8427DDE__INCLUDED_

#include "board.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayStatusDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayStatusDlg dialog

class CPlayStatusDlg : public CDialog
{
// Construction
public:
	Rules m_rule;
	int m_board_size;
	BOOL OnInitDialog();
	CPlayStatusDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayStatusDlg)
	enum { IDD = IDD_PlayStatus };
	UINT	m_basic_time;
	UINT	m_CountDownTime;
	float	m_Handicap;
	UINT	m_NumCountDown;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayStatusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayStatusDlg)
	afx_msg void OnBlackStone();
	afx_msg void OnBoard13();
	afx_msg void OnBoard19();
	afx_msg void OnBoard9();
	afx_msg void OnChineseRule();
	afx_msg void OnIngRule();
	afx_msg void OnJapanRule();
	afx_msg void OnPsk();
	afx_msg void OnSsk();
	afx_msg void OnSystemDetermined();
	afx_msg void OnWhiteStone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYSTATUSDLG_H__0A0636D9_DA98_4190_9227_056BB8427DDE__INCLUDED_)
