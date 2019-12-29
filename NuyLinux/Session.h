#pragma once
#include "Node.h"
#include "Mal.h"
#include "Player.h"

class Session
{

	Node *addNode(NodeType type, Node *pNode = nullptr)
	{
		Node *pNewNode = new Node(type);
		if (pNode)
			pNode->SetNextNode(pNewNode);
		return pNewNode;
	}
	Node *pHomeNode;
	Node *pCrossNode;
	Node *pOutNode;
	Node *pBranchNode[4];
	Node *pReadyNode;

	int mUpdateNumber;
	int mTurn;

public:
	Player Player1;
	Player Player2;
	Player Player3;

	Node *getHomeNode()
	{
		return pHomeNode;
	};

	Node *getReadyNode()
	{
		return pReadyNode;
	};

	Session() : Player1(this, 1), Player2(this, 2), Player3(this, 3)
	{
		pHomeNode = NULL;
		pCrossNode = NULL;
		InitalizeNuytPlat();
	}

	int GetNyutNumber();
	void Run();
	void InitalizeNuytPlat();
};
