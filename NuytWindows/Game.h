#pragma once
#include "Node.h"
#include "Mal.h"
#include "Player.h"

static Node* addHomeNode()
{
	Node* pNewNode = new Node(NODE_TYPE_HOME);
	return pNewNode;
}

static Node* addBranch(Node* pNode)
{
	Node* pNewNode = new Node(NODE_TYPE_BRANCH);
	pNode->SetNextNode(pNewNode);
	return pNewNode;
}

static Node* addSingle(Node* pNode)
{
	Node* pNewNode = new Node(NODE_TYPE_SINGLE);
	pNode->SetNextNode(pNewNode);
	return pNewNode;
}


static Node* addReadyNode(Node* pNode)
{
	Node* pNewNode = new Node(NODE_TYPE_READY);
	pNode->SetNextNode(pNewNode);
	return pNewNode;
}



static Node* addOut(Node* pNode)
{
	Node* pNewNode = new Node(NODE_TYPE_SINGLE);
	pNode->SetNextNode(pNewNode);
	return pNewNode;
}

static Node* addCross(Node* pNode)
{
	Node* pNewNode = new Node(NODE_TYPE_CROSS);
	pNode->SetNextNode(pNewNode);
	return pNewNode;
}


class Game
{
	Node* pHomeNode;
	Node* pCrossNode;
	Node* pOutNode;
	Node* pBranchNode[4];
	Node* pReadyNode;
	
	int mUpdateNumber;
public:
	Player Player1;
	Player Player2;
	Player Player3;

	Node* getHomeNode()
	{
		return	pHomeNode;
	};

	Node* getReadyNode()
	{
		return pReadyNode;
	};

	Game() : Player1(this), Player2(this), Player3(this)
	{
		pHomeNode = NULL;
		pCrossNode = NULL;

		Player1.GetBrush()->CreateSolidBrush(RGB(100, 0, 0));
		Player2.GetBrush()->CreateSolidBrush(RGB(00, 100,100));
		Player3.GetBrush()->CreateSolidBrush(RGB(200, 150, 0));


		InitalizeNuytPlat();
	}

	void Draw(CDC* pDC)
	{

		DrawPlat(pDC);
		DrawMal(pDC);
	}

	void DrawPlat(CDC* pDC)
	{
		mUpdateNumber++;
		if(pHomeNode)
			pHomeNode->Draw(pDC, mUpdateNumber);
		
	}

	void DrawMal(CDC* pDC)
	{
		Player1.Draw(pDC);
		Player2.Draw(pDC);
		Player3.Draw(pDC);
	}
	void InitalizeNuytPlat();
};
