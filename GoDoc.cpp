// GoDoc.cpp : implementation of the CGoDoc class
//

#include "stdafx.h"
#include "Go.h"
#include "board.h"
#include "BoardSizeDialog.h"
#include "PlayStatusDlg.h"
#include "GoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGoDoc

IMPLEMENT_DYNCREATE(CGoDoc, CDocument)

BEGIN_MESSAGE_MAP(CGoDoc, CDocument)
	//{{AFX_MSG_MAP(CGoDoc)
	ON_COMMAND(ID_board_size, Onboardsize)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_PlayStatus, OnPlayStatus)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoDoc construction/destruction

CGoDoc::CGoDoc()
{
	// TODO: add one-time construction code here
	board = new Cboard();
}

CGoDoc::~CGoDoc()
{
	delete board;
}

BOOL CGoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGoDoc serialization

void CGoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGoDoc diagnostics

#ifdef _DEBUG
void CGoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG





void CGoDoc::Onboardsize() 
{
	// TODO: Add your command handler code here
	CBoardSizeDialog aDlg;
	
	aDlg.m_board_size = board->m_boardsize;

	if (aDlg.DoModal() == IDOK)
	{
		//board->m_boardsize = aDlg.m_board_size;
		switch(aDlg.m_board_size)
		{
		case 19:
			delete board;
			board = new Cboard(19);
			UpdateAllViews(0);
			break;
		case 13:
			delete board;
			board = new Cboard(13);
			UpdateAllViews(0);
			break;
		case 9:
			delete board;
			board = new Cboard(9);
			UpdateAllViews(0);
			break;
		default:
			delete board;
			board = new Cboard(19);
			UpdateAllViews(0);
			break;
		}
	}
}

void CGoDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	// szFilters is a text string that includes two file name filters:
   char szFilters[]="SGF Files (*.sgf)|*.sgf|All Files (*.*)|*.*||";

   // Create an Open dialog; the default file name extension is ".sgf".
   CFileDialog fileDlg (TRUE, "sgf", "*.sgf", OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters);
   
   // Display the file dialog. When user clicks OK, fileDlg.DoModal() 
   // returns IDOK.
   if( fileDlg.DoModal()==IDOK )
   {
      CString str, pathName = fileDlg.GetPathName();
   
      // Implement opening and reading file in here.
      CStdioFile f;
	  CFileException e;
      if( !f.Open( pathName, CFile::modeRead, &e ) )
	  {
		#ifdef _DEBUG
		afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif
	  }
	  while (f.ReadString(str)) {
		sgf_to_parse += str;
		sgf_to_parse += "\n";
	  }
	  f.Close();
	  doParse();
   }
	
}

bool CGoDoc::doParse()
{
	Turn dead_color;
	vector<pair<int,int> > deads;

	if (sgf_to_parse.IsEmpty()) {
		AfxMessageBox("Failed loading from file. Is it empty?",MB_OK);
		return false;
	}
	
	CString *toParse = NULL;
	toParse = new CString(sgf_to_parse);

	int pos = 0, posVarBegin = 0, posVarEnd = 0, posNode = 0, moves = 0, x=-1, y=-1;
	unsigned int tmppos=0, pointer = 0, strLength = toParse->GetLength();

	do {
		if (toParse->GetAt(pos) == ';') {
			if (toParse->GetAt(pos+1) == 'B' && toParse->GetAt(pos+2) == '[') {
				x = toParse->GetAt(pos+3) - 'a' + 1;
				y = toParse->GetAt(pos+4) - 'a' + 1;
				if (x>19 || y>19) 
					return false;
				if (!board->mp_rule->move(BLACK, x, y, board, deads, dead_color)) {
					AfxMessageBox("Illegal Position!",MB_OK);
					return false;
				}
				board->p_current_board_position->player = WHITE;
				deads.clear();
			}
			else if (toParse->GetAt(pos+1) == 'W' && toParse->GetAt(pos+2) == '[') {
				x = toParse->GetAt(pos+3) - 'a' + 1;
				y = toParse->GetAt(pos+4) - 'a' + 1;
				if (x>19 || y>19) 
					return false;
				if (!board->mp_rule->move(WHITE, x, y, board, deads, dead_color)) {
					AfxMessageBox("Illegal Position!",MB_OK);
					return false;
				}
				board->p_current_board_position->player = BLACK;
				deads.clear();
			}
		}
		pos++;
	} while (pos < strLength);

	/*State state;
	state = stateVarBegin;
	do {
		posVarBegin = toParse->Find('(', pointer);
		posVarEnd = toParse->Find(')', pointer);
		posNode = toParse->Find(';', pointer);
		
		pos = minPos(posVarBegin, posVarEnd, posNode);
		// Switch states
		if (state == stateNode && pos == posVarEnd)
			state = stateVarEnd;
		
		if (state == stateNode && pos == posVarBegin)
			state = stateVarBegin;
		else if (state == stateVarBegin && pos == posNode)
			state = stateNode;
		else if (state == stateVarEnd && pos == posVarBegin)
			state = stateVarBegin;
		// Do the work
		switch (state) {
			case stateVarBegin:
				if (pos != posVarBegin) {
					delete toParse;
					AfxMessageBox("Parsing fail!",MB_OK);
					return false;
				}		
				pointer = pos + 1;
				break;
			
			case stateVarEnd:
				if (pos != posVarEnd) {
					delete toParse;
					AfxMessageBox("Parsing fail!",MB_OK);
					return false;
				}	
				pointer = pos + 1;
				break;
			
			case stateNode:
				if (pos != posNode) {
					delete toParse;
					AfxMessageBox("Parsing fail!",MB_OK);
					return false;
				}
				Property prop;
				pos ++;
				do {
					unsigned int tmppos=0;
			
					pos = next_nonspace(toParse, pos);
				
					if (toParse->GetAt(pos) == 'B' && toParse->GetAt(tmppos = next_nonspace(toParse, pos+1)) == '[') {
						prop = moveBlack;
						pos = tmppos;
					}
					// else if (toParse->find("W[", pos) == pos)
					else if (toParse->GetAt(pos) == 'W' && toParse->GetAt(tmppos = next_nonspace(toParse, pos+1)) == '[') {
						prop = moveWhite;
						pos = tmppos;
					}
					else {
						// handle like comment
						prop = unknownProp;
						pos = next_nonspace(toParse, pos);
					}
					// Next is one or more '[xx]'.
					// Only one in a move property, several in a setup propery
					do {
						if (toParse->GetAt(pos) != '[' && prop != unknownProp) {
							delete toParse;
							return false;
						}
						// Empty type
						if (toParse->GetAt(pos+1) == ']') {
							// stores pass as 'B[]' or 'W[]'
							if (prop == moveBlack || prop == moveWhite) {	
							}
							pos += 2;
							continue;
						}
						switch (prop) {
							case moveBlack:
								x = toParse->GetAt(pos+1) - 'a' + 1;
								y = toParse->GetAt(pos+2) - 'a' + 1;
								if (!board->mp_rule->move(BLACK, x, y, board, deads, dead_color)) {
									AfxMessageBox("Illegal Position!",MB_OK);
								}
								deads.clear();
								break;
							case moveWhite:
								x = toParse->GetAt(pos+1) - 'a' + 1;
								y = toParse->GetAt(pos+2) - 'a' + 1;
								if (!board->mp_rule->move(WHITE, x, y, board, deads, dead_color)) {
									AfxMessageBox("Illegal Position!",MB_OK);
								}
								deads.clear();
						}
					} while (toParse->GetAt(pos)=='[');	
			} while (toParse->GetAt(pos)!=';' && toParse->GetAt(pos)!='(' && toParse->GetAt(pos)!=')' && pos < strLength);
		} 
   } while (pointer < strLength && pos >= 0);*/
  
   delete toParse;
   return true;
}

int CGoDoc::minPos(int n1, int n2, int n3)
{
	int min;
	
	min = n1;
	
	if (n2 < min)
		min = n2;
	
	if (n3 < min)
		min = n3;
	
	return min;
}

int CGoDoc::next_nonspace(CString *s, int pos)
{
	char c;
	c = s->GetAt(pos);
	while (c==' ' || c=='\n' || c=='\t' || c=='\r' || c=='\f' || c=='\v' || (c >= 'a' && c <= 'z')) {
		pos++;
		c = s->GetAt(pos);
	}
	return pos;
}

void CGoDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	
   
}

void CGoDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
	/*this->UpdateData();
	CLoanEvalDoc *pDoc = GetDocument();*/
	CMove current_move;
	list<CMove>::iterator moves_index_tmp;
	char szFilters[]="SGF Files (*.sgf)|*.sgf|All Files (*.*)|*.*||";

	CFileDialog fileDlg (FALSE, "sgf", "*.sgf", 0, szFilters);

	if( fileDlg.DoModal()==IDOK )
	{
		CString pathName = fileDlg.GetPathName();
		char tmp;
		char buf[2] = "(";
   
		// Implement opening and writing file in here.
		CStdioFile f;
		CFileException e;
		if( !f.Open( pathName, CFile::modeCreate | CFile::modeWrite, &e ) )
		{
			#ifdef _DEBUG
			afxDump << "File could not be opened " << e.m_cause << "\n";
			#endif
		}
		
		if (!board->m_moves.moves_sequence.empty()) {
			f.WriteString(buf);
			for(moves_index_tmp=board->m_moves.moves_sequence.begin(); moves_index_tmp!=board->m_moves.moves_sequence.end(); moves_index_tmp++) {
				current_move = *moves_index_tmp;
				strcpy(buf, ";");
				f.WriteString(buf);
				if (current_move.stone==BLACK) {
					strcpy(buf, "B");
					f.WriteString(buf);
				}
				else if (current_move.stone==WHITE) {
					strcpy(buf, "W");
					f.WriteString(buf);
				}
				strcpy(buf, "[");
				f.WriteString(buf);
				tmp = current_move.x + 'a' - 1;
				buf[0] = (char)tmp;
				buf[1] = 0;
				f.WriteString(buf);
				tmp = current_move.y + 'a' - 1;
				buf[0] = (char)tmp;
				buf[1] = 0;
				f.WriteString(buf);
				strcpy(buf, "]");
				f.WriteString(buf);
			}
			strcpy(buf, ")");
			f.WriteString(buf);
		}
		f.Close();
	}
	else
		return;
	
}

void CGoDoc::OnPlayStatus() 
{
	// TODO: Add your command handler code here
	CPlayStatusDlg aDlg;
	
	aDlg.m_board_size = board->m_boardsize;
	aDlg.m_basic_time = board->m_basic_time;
	aDlg.m_CountDownTime = board->m_CountDownTime;
	aDlg.m_Handicap = board->komi;
	aDlg.m_NumCountDown = board->m_NumCountDown;
	aDlg.m_rule = board->m_rule;

	if (aDlg.DoModal() == IDOK)
	{
		switch(aDlg.m_board_size)
		{
		case 19:
			delete board;
			board = new Cboard(19);
			UpdateAllViews(0);
			break;
		case 13:
			delete board;
			board = new Cboard(13);
			UpdateAllViews(0);
			break;
		case 9:
			delete board;
			board = new Cboard(9);
			UpdateAllViews(0);
			break;
		default:
			delete board;
			board = new Cboard(19);
			UpdateAllViews(0);
			break;
		}
		board->m_basic_time = aDlg.m_basic_time;
		board->m_CountDownTime = aDlg.m_CountDownTime;
		board->komi = aDlg.m_Handicap;
		board->m_NumCountDown = aDlg.m_NumCountDown;
		board->m_rule = aDlg.m_rule;
		delete board->mp_rule;
		switch(board->m_rule)
		{
		case POSITIONAL_SUPER_KO:
			board->mp_rule = new CRulePSK;
			break;
		case SITUATIONAL_SUPER_KO:
			board->mp_rule = new CRulePSK; // temporary
			break;
		case NSSK:
			board->mp_rule = new CRulePSK; // temporary
			break;
		case CHINESE:
			board->mp_rule = new CRulePSK; // temporary
			break;
		case ING:
			board->mp_rule = new CRulePSK; // temporary
			break;
		case JAPANESE:
			board->mp_rule = new CRulePSK; // temporary
			break;
		default:
			board->mp_rule = new CRulePSK;
			break;
		}
	}
}
