// GoView.h : interface of the CGoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOVIEW_H__5C84A25F_B110_4D7B_8A80_2A96242D91D7__INCLUDED_)
#define AFX_GOVIEW_H__5C84A25F_B110_4D7B_8A80_2A96242D91D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGoView : public CView
{
protected: // create from serialization only
	CGoView();
	DECLARE_DYNCREATE(CGoView)

// Attributes
public:
	CGoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT BlackNumCountDown, WhiteNumCountDown;
	UINT BlackCountDownTime, WhiteCountDownTime;
	void display_photos();
	void DisplayTime();
	void IniCountDownTime();
	BOOL StopTimer (UINT TimerVal);
	UINT StartTimer (UINT TimerID, UINT TimerDuration);
	void draw_territory_mark(int x, int y, int color);
	CButton DoneButton, ContinueButton;
	CButton ResignButton;
	CButton PassButton;
	int previous_y;
	int previous_x;
	UINT black_time, black_base_time;
	UINT white_time, white_base_time;
	void draw_mark(int x, int y);
	void draw_stone(int x, int y, Turn stone);
	void Draw_Board(CDC* pDC);
	int get_board_position(int x, int y, __int64 *p);
	void Simulated_Draw(CMove *current_move);
	void display_prompts(int m_stones_on_board, int m_num_moves, int m_black_captured, int m_white_captured);
	virtual ~CGoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGoView)
	afx_msg void OnMenu1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void Onbackward1();
	afx_msg void Onbackward5();
	afx_msg void Onforward1();
	afx_msg void Onforward5();
	afx_msg void Ontothebegin();
	afx_msg void Ontotheend();
	afx_msg void OnPassButton();
	afx_msg void OnResignButton();
	afx_msg void OnDoneButton();
	afx_msg void OnContinueButton();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GoView.cpp
inline CGoDoc* CGoView::GetDocument()
   { return (CGoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOVIEW_H__5C84A25F_B110_4D7B_8A80_2A96242D91D7__INCLUDED_)
