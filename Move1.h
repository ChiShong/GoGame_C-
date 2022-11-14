// Move1.h: interface for the CMove class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVE1_H__72DB812F_73A9_4258_9645_14D5B1AEC617__INCLUDED_)
#define AFX_MOVE1_H__72DB812F_73A9_4258_9645_14D5B1AEC617__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <list>
using namespace std; 

class CMove  
{
public:
	Turn stone;
	int m_num_moves;
	int m_black_captured;
	int m_white_captured;
	int m_stones_on_board;
	int x, y;
	//__int64 *p_board_position;
	list<pair<int, int> > alt_moves;
	vector<pair<int,int> > captured;
	Turn dead_color;

	CMove(const CMove & rhs);

	CMove& operator= (const CMove & rhs);

	CMove();

	~CMove() {
		alt_moves.clear();
		captured.clear();
		//if (p_board_position)
			//delete [] p_board_position;
	}
};

class CMoveTree  
{
public:
	CMoveTree();
	CMoveTree(const CMoveTree & rhs);
	CMoveTree& operator= (const CMoveTree & rhs);
	virtual ~CMoveTree();

	list<CMove> moves_sequence;
	list<CMove>::iterator current_moves_index;
};

#endif // !defined(AFX_MOVE1_H__72DB812F_73A9_4258_9645_14D5B1AEC617__INCLUDED_)
