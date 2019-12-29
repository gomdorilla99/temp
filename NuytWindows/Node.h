#pragma once


enum NodeType
{
	NODE_TYPE_HOME,
	NODE_TYPE_SINGLE,
	NODE_TYPE_BRANCH,
	NODE_TYPE_CROSS,
	NODE_TYPE_READY,
	NODE_TYPE_OUT,
	NODE_TYPE_MAX
};



class Node
{
	int mUpdateNum;
	NodeType mType;
	POINT mLocation;
	Node* inputPort[2];
	Node* outputPort[2];
	CBrush mBlackNode;
public: 
	Node(enum NodeType type)
	{
		mType = type;
		inputPort[0] = NULL;
		inputPort[1] = NULL;
		outputPort[0] = NULL;
		outputPort[1] = NULL;
		mLocation.x = 0;
		mLocation.y = 0;
		mUpdateNum = -1;
		mBlackNode.CreateSolidBrush(RGB(200, 200, 200));
	}

	enum NodeType getType()
	{
		return mType;
	}
	
	void Draw(CDC* pDC, int UpdateNum)
	{
		CBrush* pOldBrush;
		pOldBrush = pDC->SelectObject(&mBlackNode);
		
		if(UpdateNum != mUpdateNum)
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
			pDC->Ellipse(mLocation.x - 10, mLocation.y - 10, mLocation.x + 10, mLocation.y + 10);

			if (mType == NODE_TYPE_CROSS ||
				mType == NODE_TYPE_HOME ||
				mType == NODE_TYPE_BRANCH)
			{
				pDC->Ellipse(mLocation.x - 15, mLocation.y - 15, mLocation.x + 15, mLocation.y + 15);
			}
		}

		pDC->SelectObject(pOldBrush);
	}

	void setLocation(int x, int y)
	{
		mLocation.x = x;
		mLocation.y = y;
	}

	POINT getLocation()
	{
		return mLocation;
	}

	Node* addSingle()
	{
		Node* pNewNode = new Node(NODE_TYPE_SINGLE);
		SetNextNode(pNewNode);
		return pNewNode;
	}

	void setInputNode(Node* pNode)
	{
		if (!inputPort[0])
			inputPort[0] = pNode;
		else if (!inputPort[1])
			inputPort[1] = pNode;
		else
			ASSERT(pNode);
	}

	Node* SetNextNode(Node* pNode)
	{
		if (!outputPort[0])
			outputPort[0] = pNode;
		else if (!outputPort[1])
			outputPort[1] = pNode;
		else
			ASSERT(outputPort[1]);

		pNode->setInputNode(this);

		return pNode;
	}

	Node * passThrough(int Count, Node* pPreviousNode, Node* pStart)
	{
		Node* pNodeNext = NULL;
		if (mType == NODE_TYPE_BRANCH)
		{
			if (this == pStart)
			{
				if(outputPort[1])
					pNodeNext = outputPort[1];
				else
					pNodeNext = outputPort[0];
			}
			else
			{
				pNodeNext = outputPort[0];
			}
		}
		else if (mType == NODE_TYPE_CROSS)
		{
			if (this == pStart)
			{
				pNodeNext = outputPort[1];
			}
			else
			{
				if (pPreviousNode == inputPort[0])
				{
					pNodeNext = outputPort[0];
				}
				else if (pPreviousNode == inputPort[1])
				{
					pNodeNext = outputPort[1];
				}
			}
		}
		else if (mType == NODE_TYPE_HOME)
		{
			if (pStart != this)
			{
				pNodeNext = this;
				return pNodeNext;
			}
			else
			{
				if (outputPort[0])
					pNodeNext = outputPort[0];
				else
					ASSERT(outputPort[0]);
			}
		}
		else if (mType == NODE_TYPE_CROSS)
		{
			return this;
		}
		else    // NODE_TYPE_SINGLE
		{
			if (outputPort[0])
				pNodeNext = outputPort[0];
			else
			{
				pNodeNext = this;
				//	ASSERT(outputPort[0]);
			}
		}

		if (pNodeNext && Count > 1)
		{
			return pNodeNext->passThrough(Count - 1, this, pStart);
		}
		return pNodeNext;
	}
	
};
