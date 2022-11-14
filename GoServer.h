#if !defined(AFX_GOSERVER_H__511191ED_FE4C_4F9C_9E54_8A0A203C1CEE__INCLUDED_)
#define AFX_GOSERVER_H__511191ED_FE4C_4F9C_9E54_8A0A203C1CEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GoServer.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CGoServer command target

class CGoServer : public CSocket
{
// Attributes
public:

// Operations
public:
	CGoServer();
	virtual ~CGoServer();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoServer)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CGoServer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOSERVER_H__511191ED_FE4C_4F9C_9E54_8A0A203C1CEE__INCLUDED_)
