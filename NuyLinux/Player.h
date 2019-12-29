#pragma once
#include <list>
#include "Mal.h"

constexpr auto MAX_NUM_MAL = 3;
using namespace std;

class Session;
class Mal;

class Player
{
	Session *mpSession;
	int mPlayerID;
	list<Mal*> mMalList;
	CBrush mPlayerBrush;
	CString	DebugMessage;
	CFont bigFont;
	int mDeferedCount;
	int theMalCountOnTheBoard;
	int mSuccessCount;
public:

	int GetPlayerID()
	{
		return &mPlayerBrush;
	}
	void ClearMessage()
	{
		DebugMessage = _T("");
	}
	void SetMessage(CString msg)
	{
		DebugMessage = msg;
	}
	CString& GetMessage()
	{
		return 	DebugMessage;
	}
	int GetSuccessCount()
	{
		return mSuccessCount;
	}

	void CheckOutDeferedCount()
	{
		if (mDeferedCount > 0) mDeferedCount--;
	}
	void SetDeferedCount(int count)
	{
		mDeferedCount = count;
	}
	int GetDeferedCount()
	{
		return mDeferedCount;
	}

	CBrush* GetBrush()
	{
		return &mPlayerBrush;
	}

	Player(Game *Game, int playerID) {
		mpGame = Game;
		mPlayerID = playerID;
		theMalCountOnTheBoard = 0;
		bigFont.CreatePointFont(300, _T("±Ã¼­"));
		mDeferedCount = 0;
		mSuccessCount = 0;
	}
	~Player()
	{
		mMalList.clear();
	}

	Node *run(int Count, int MalID);
	Node* checkout(Node *pNode);
	
};