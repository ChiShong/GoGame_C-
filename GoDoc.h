// GoDoc.h : interface of the CGoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GODOC_H__D04325CF_3735_4B9C_9749_BC860AD379F2__INCLUDED_)
#define AFX_GODOC_H__D04325CF_3735_4B9C_9749_BC860AD379F2__INCLUDED_

#include "board.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SGF parser definitions
enum State { stateVarBegin, stateNode, stateVarEnd };
enum Property { moveBlack, moveWhite, editBlack, editWhite, editErase, comment, editMark, unknownProp, nodeName, timeLeft, openMoves, nextMove};
enum TimeSystem { none, absolute, byoyomi, canadian };
struct Position { int x, y; };
struct MoveNum {int n; };

class CGoDoc : public CDocument
{
protected: // create from serialization only
	CGoDoc();
	DECLARE_DYNCREATE(CGoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	static int next_nonspace(CString *s, int pos);
	int minPos(int n1, int n2, int n3);
	bool doParse();
	CString sgf_to_parse;
	Cboard *board;
	virtual ~CGoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGoDoc)
	afx_msg void Onboardsize();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSave();
	afx_msg void OnPlayStatus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GODOC_H__D04325CF_3735_4B9C_9749_BC860AD379F2__INCLUDED_)
