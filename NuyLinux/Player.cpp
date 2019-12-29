#include "Player.h"
#include "Session.h"
#include <stdlib.h>
#include <string.h>


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
				(*iter)->mpDestNode = mpSession->getReadyNode();
				(*iter)->mpMalLocation = mpSession->getReadyNode();
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
		Mal* pNewMal = new Mal(this,mpSession);
		pNewMal->setMalLocation(mpSession->getHomeNode());
		mMalList.push_back(pNewMal);
		theMalCountOnTheBoard++;
	}

	if (theMalCountOnTheBoard > 0)
	{
		// Ask Register or Go
		list<Mal*>::iterator  iter = mMalList.begin();
		while (iter != mMalList.end())
		{
			if ((*iter)->mpMalLocation == mpSession->getReadyNode() || 
				(*iter)->mpMalLocation->getType() ==NODE_TYPE_OUT)
				(*iter)->mpMalLocation = mpSession->getHomeNode();
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
		
		char *NyutStr[7] = { "Back do","Nack", "DO", "Ge", "girl", "luyt", "mo" };
		//printf(DebugMessage, "%s", NyutStr[Count + 1]);
		return LastMoveNode;
	}
		
}