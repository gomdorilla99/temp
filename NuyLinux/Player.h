#pragma once
#include <list>
#include <string.h>
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
	char DebugMessage[256];
	int mDeferedCount;
	int theMalCountOnTheBoard;
	int mSuccessCount;
public:

	int GetPlayerID()
	{
		return mPlayerID;
	}
	void ClearMessage()
	{
		strcpy(DebugMessage ,"");
	}
	void SetMessage(char *msg)
	{
		strcpy(DebugMessage, msg);
	}

	char *GetMessage()
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

#if 0
	CBrush* GetBrush()
	{
		return &mPlayerBrush;
	}
#endif
	Player(Session *Game, int playerID) {
		mpSession = Game;
		mPlayerID = playerID;
		theMalCountOnTheBoard = 0;
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