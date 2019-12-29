#include "Player.h"
#include "Session.h"


Node* Player::checkout(Node* pNode)
{
	Node* LastMoveNode = nullptr;
	if (theMalCountOnTheBoard > 0)
	{
		// Ask Register or Go
		list<Mal*>::iterator  iter = mMalList.begin();
		while (iter != mMalList.end())
		{
			if(pNode == (*iter)->mpMalLocation)
			{
				(*iter)->mpStartNode = (*iter)->mpMalLocation;
				LastMoveNode = (*iter)->mpMalLocation;
				(*iter)->mpDestNode = mpGame->getReadyNode();
				(*iter)->mpMalLocation = mpGame->getReadyNode();
			}
			iter++;
		}
		return LastMoveNode;
	}
}

Node* Player::run(int Count, int MalID)
{
	Node* LastMoveNode = nullptr;
	if (theMalCountOnTheBoard == 0)
	{
		Mal* pNewMal = new Mal(this);
		pNewMal->setMalLocation(mpGame->getHomeNode());
		mMalList.push_back(pNewMal);
		theMalCountOnTheBoard++;
	}

	if (theMalCountOnTheBoard > 0)
	{
		// Ask Register or Go
		list<Mal*>::iterator  iter = mMalList.begin();
		while (iter != mMalList.end())
		{
			if ((*iter)->mpMalLocation == mpGame->getReadyNode())
				(*iter)->mpMalLocation = mpGame->getHomeNode();
			Node* pCurrentNode = (*iter)->mpMalLocation;
		
			if ((*iter)->mpMalLocation)
			{
				if (Count > 0)
				{
					(*iter)->mpBackNode = pCurrentNode->passThrough(Count - 1, pCurrentNode, pCurrentNode);
					(*iter)->mpMalLocation = pCurrentNode->passThrough(Count, pCurrentNode, pCurrentNode);
					(*iter)->mpStartNode = pCurrentNode;
					(*iter)->mpDestNode = pCurrentNode;
				}
				else if(Count==-1 && pCurrentNode->getType() != NODE_TYPE_OUT && pCurrentNode->getType() != NODE_TYPE_READY)
				{
					(*iter)->mpStartNode = pCurrentNode;
					(*iter)->mpMalLocation = (*iter)->mpBackNode;
					(*iter)->mpDestNode = (*iter)->mpBackNode;
					(*iter)->mpBackNode = pCurrentNode;
				}
				else
				{
					(*iter)->mpBackNode = (*iter)->mpMalLocation;
					(*iter)->mpStartNode = pCurrentNode;
					(*iter)->mpDestNode = pCurrentNode;
				}
				
				


				
				LastMoveNode = (*iter)->mpMalLocation;
			}
			iter++;
		}
		
		CString NyutStr[7] = { _T("����"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��") };
		DebugMessage.Format(_T("%s"), NyutStr[Count + 1]);
		return LastMoveNode;
	}
		
}