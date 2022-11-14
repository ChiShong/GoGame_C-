#if !defined(AFX_GODIALOG_H__139DCAD8_95D8_4388_AB90_788C149E20D2__INCLUDED_)
#define AFX_GODIALOG_H__139DCAD8_95D8_4388_AB90_788C149E20D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// goDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// goDialog dialog

class goDialog : public CDialog
{
// Construction
public:
	goDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(goDialog)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(goDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(goDialog)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GODIALOG_H__139DCAD8_95D8_4388_AB90_788C149E20D2__INCLUDED_)
