#include "Player.h"
#include "Session.h"




void Player::Draw(CDC* pDC)
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
			if ((*iter)->mpMalLocation && (*iter)->getMalStatus()==MAL_ON_BOARD)
			{
				(*iter)->Draw(pDC);
				
			}
			else if ((*iter)->mpMalLocation && (*iter)->getMalStatus() == MAL_READYTOGO)
			{

			}

			iter++;
		}
	}
	pDC->SelectObject(pOldBrush);

}

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
		Mal* pNewMal = new Mal(this,mpGame);
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
			if ((*iter)->mpMalLocation == mpGame->getReadyNode() || 
				(*iter)->mpMalLocation->getType() ==NODE_TYPE_OUT)
				(*iter)->mpMalLocation = mpGame->getHomeNode();
			Node* pCurrentNode = (*iter)->mpMalLocation;
		
			if ((*iter)->mpMalLocation)
			{
				(*iter)->mpStartNode = pCurrentNode;
				(*iter)->mpStartNode->CheckOut((*iter)); // check Out Mal.

				if (Count > 0)
				{
					(*iter)->mpBackNode = pCurrentNode->passThrough(Count - 1, pCurrentNode, pCurrentNode);
					(*iter)->mpMalLocation = pCurrentNode->passThrough(Count, pCurrentNode, pCurrentNode);
					if ((*iter)->mpMalLocation->getType() == NODE_TYPE_OUT)
					{
						mSuccessCount++;
						(*iter)->mpDestNode = pCurrentNode;
						//(*iter)->setMalStatus(MAL_ON_BOARD);
						SetDeferedCount(0);
					}
					else
					{
						(*iter)->mpDestNode = pCurrentNode;
						(*iter)->setMalStatus(MAL_ON_BOARD);

					}
					
				}
				else if(Count==-1 && pCurrentNode->getType() != NODE_TYPE_OUT && pCurrentNode->getType() != NODE_TYPE_READY)
				{
					(*iter)->mpStartNode = pCurrentNode;
					(*iter)->mpMalLocation = (*iter)->mpBackNode;
					(*iter)->mpDestNode = (*iter)->mpBackNode;
					(*iter)->mpBackNode = pCurrentNode;			
					(*iter)->setMalStatus(MAL_ON_BOARD);
				}
				else
				{
					//What is this case? 
					//(*iter)->mpBackNode = (*iter)->mpMalLocation;
					//(*iter)->mpDestNode = pCurrentNode;
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