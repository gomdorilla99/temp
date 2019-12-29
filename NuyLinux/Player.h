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
	list<Mal*> mMalList;
	CBrush mPlayerBrush;
	CString	DebugMessage;
	CFont bigFont;
	int theMalCountOnTheBoard;
public:

	CBrush* GetBrush()
	{
		return &mPlayerBrush;
	}

	Player(Session *Session) {
		mpSession = Session;
		theMalCountOnTheBoard = 0;
		bigFont.CreatePointFont(300, _T("�ü�"));
	}
	~Player()
	{
		mMalList.clear();
	}

	void Draw(CDC* pDC)
	{
		CBrush* pOldBrush;
		pOldBrush = pDC->SelectObject(&mPlayerBrush);
		if (theMalCountOnTheBoard > 0)
		{
			pDC->SetBkMode(TRANSPARENT);
			// Ask Register or Go
			list<Mal*>::iterator  iter = mMalList.begin();
			while (iter != mMalList.end())
			{
				if ((*iter)->mpMalLocation)
				{
					POINT Point1 = (*iter)->mpMalLocation->getLocation();
					POINT Point;
					Point.x = (*iter)->getPhyical()->x;
					Point.y = (*iter)->getPhyical()->y;
					pDC->MoveTo(Point1.x, Point1.y);
					pDC->LineTo(Point.x, Point.y);

					CRect rect(Point.x-50, Point.y-50, Point.x+50, Point.y+50);
					
					pDC->Ellipse(rect);
					CFont* pFont = pDC->SelectObject(&bigFont);
					pDC->TextOutW(Point1.x, Point1.y, DebugMessage);
					pDC->SelectObject(pFont);
				}
				iter++;
			}
		}
		pDC->SelectObject(pOldBrush);

	}

	Node *run(int Count, int MalID);
	Node* checkout(Node *pNode);
	
};