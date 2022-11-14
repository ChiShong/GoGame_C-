// Rules.h: interface for the CRules class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULES_H__4143E2AD_96B5_4CED_8E7E_62E446B70754__INCLUDED_)
#define AFX_RULES_H__4143E2AD_96B5_4CED_8E7E_62E446B70754__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <vector>
using namespace std;

class Cboard;

class CRules  
{
public:
	virtual void scoring(float &black_points, float &white_points, Cboard *board) = 0;
	virtual bool move(Turn t, int x, int y, Cboard *b, vector<pair<int,int> > &deads, Turn &dead_color) = 0;
	virtual pair<Turn,int> remove_deads(Turn t, int x, int y, Csituation *p, Cboard *board, vector<pair<int,int> > &deads) =0;
	CRules();
	virtual ~CRules();
	virtual bool LegalMove(Turn t, int x, int y, Cboard *board) = 0;
};

class CRulePSK : public CRules
{
public:
	void scoring(float &black_points, float &white_points, Cboard *board);
	bool move(Turn t, int x, int y, Cboard *b, vector<pair<int,int> > &deads, Turn &dead_color);
	pair<Turn,int> remove_deads(Turn t, int x, int y, Csituation *p, Cboard *board, vector<pair<int,int> > &deads);
	bool position_super_ko(Turn t, int x, int y, Csituation *p);
	CRulePSK();
	~CRulePSK();
	bool LegalMove(Turn t, int x, int y, Cboard *board);

	list<CountedPtr<Csituation> > p_situation_list[MAX_STONES];
};

#endif // !defined(AFX_RULES_H__4143E2AD_96B5_4CED_8E7E_62E446B70754__INCLUDED_)
