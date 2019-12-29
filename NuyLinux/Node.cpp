#include "Node.h"

#include "Player.h"


bool Node::CheckIn(Mal* pMal)
{
	if (mpCheckedMal == nullptr)
	{
		mpCheckedMal = pMal;
		mpCheckedMal->setMalStatus(MAL_ON_BOARD);
		return true;
	}
	else
	{
		return false;
	}
}

bool Node::CheckOut(Mal* pMal)
{
	if (mpCheckedMal == pMal)
	{
		mpCheckedMal = nullptr;
		return true;
	}
	else
	{
		return false;
	}
}


void Node::Draw(CDC* pDC, int UpdateNum)
{
	CBrush* pOldBrush;
	pOldBrush = pDC->SelectObject(&mBlackNode);

	if (UpdateNum != mUpdateNum)
	{


		mUpdateNum = UpdateNum;
		if (outputPort[0])
		{
			//pDC->MoveTo(mLocation.x, mLocation.y);
			//pDC->LineTo(outputPort[0]->mLocation.x, outputPort[0]->mLocation.y);

			outputPort[0]->Draw(pDC, UpdateNum);

		}
		if (outputPort[1])
		{
			//pDC->MoveTo(mLocation.x, mLocation.y);
			//pDC->LineTo(outputPort[1]->mLocation.x, outputPort[1]->mLocation.y);

			outputPort[1]->Draw(pDC, UpdateNum);
		}

		if (mType == NODE_TYPE_CROSS ||
			mType == NODE_TYPE_HOME ||
			mType == NODE_TYPE_BRANCH)
		{
			pDC->Ellipse(mLocation.x - 40, mLocation.y - 40, mLocation.x + 40, mLocation.y + 40);
			pDC->SelectObject(pOldBrush);
			pDC->Ellipse(mLocation.x - 36, mLocation.y - 36, mLocation.x + 36, mLocation.y + 36);
		}
		else if (mType == NODE_TYPE_OUT || mType == NODE_TYPE_READY)
		{
		//	pDC->Rectangle(mLocation.x - 20, mLocation.y - 20, mLocation.x + 20, mLocation.y + 20);
		}
		else // NODE_TYPE_NORMAL
		{
			pDC->Ellipse(mLocation.x - 10, mLocation.y - 10, mLocation.x + 10, mLocation.y + 10);
		}
	}

	pDC->SelectObject(pOldBrush);
}