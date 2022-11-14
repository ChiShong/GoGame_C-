#if !defined(AFX_REVIEWBOARD_H__CCE3ECBA_C117_49D1_B6B2_D370F1681E0A__INCLUDED_)
#define AFX_REVIEWBOARD_H__CCE3ECBA_C117_49D1_B6B2_D370F1681E0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReviewBoard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ReviewBoard dialog

class ReviewBoard : public CDialog
{
// Construction
public:
	ReviewBoard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ReviewBoard)
	enum { IDD = IDD_Review };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ReviewBoard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ReviewBoard)
	afx_msg void Onbackmove1();
	afx_msg void Onbackmove5();
	afx_msg void Onforwardmove1();
	afx_msg void Onforwardmove5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REVIEWBOARD_H__CCE3ECBA_C117_49D1_B6B2_D370F1681E0A__INCLUDED_)
