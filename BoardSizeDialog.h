#if !defined(AFX_BOARDSIZEDIALOG_H__4C93E79B_6734_4E4E_9B01_AE0829F5CB4A__INCLUDED_)
#define AFX_BOARDSIZEDIALOG_H__4C93E79B_6734_4E4E_9B01_AE0829F5CB4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoardSizeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBoardSizeDialog dialog

class CBoardSizeDialog : public CDialog
{
// Construction
public:
	BOOL OnInitDialog();
	CBoardSizeDialog(CWnd* pParent = NULL);   // standard constructor

	int m_board_size;

// Dialog Data
	//{{AFX_DATA(CBoardSizeDialog)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoardSizeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CBoardSizeDialog)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOARDSIZEDIALOG_H__4C93E79B_6734_4E4E_9B01_AE0829F5CB4A__INCLUDED_)
