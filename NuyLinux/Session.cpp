#include "Session.h"
#include "math.h"

#define Rad(d) (d*2*3.141592/360)

void Game::InitalizeNuytPlat()
{
	Node* pNode;
	int offset_x = 700;
	int offset_y = 700;
	int radial = 600;


	pNode = addHomeNode();
	pNode->setLocation(offset_x+sin(Rad(0))* radial, offset_y+ cos(Rad(0)) * radial);
	pHomeNode = pNode;
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(18)) * radial, offset_y + cos(Rad(18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(2*18)) * radial, offset_y + cos(Rad(2*18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(3*18)) * radial, offset_y + cos(Rad(3*18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(4*18)) * radial, offset_y + cos(Rad(4*18)) * radial);
	pNode = addBranch(pNode);
	pNode->setLocation(offset_x + sin(Rad(5*18)) * radial, offset_y + cos(Rad(5*18)) * radial);
	pBranchNode[0] = pNode; // Righ wing

	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(6 * 18)) * radial, offset_y + cos(Rad(6 * 18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(7 * 18)) * radial, offset_y + cos(Rad(7 * 18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(8 * 18)) * radial, offset_y + cos(Rad(8 * 18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(9 * 18)) * radial, offset_y + cos(Rad(9 * 18)) * radial);
	pNode = addBranch(pNode);
	pNode->setLocation(offset_x + sin(Rad(10 * 18)) * radial, offset_y + cos(Rad(10 * 18)) * radial);
	pBranchNode[1] = pNode;     //North pole

	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(11 * 18)) * radial, offset_y + cos(Rad(11 * 18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(12 * 18)) * radial, offset_y + cos(Rad(12 * 18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(13 * 18)) * radial, offset_y + cos(Rad(13 * 18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(14 * 18)) * radial, offset_y + cos(Rad(14 * 18)) * radial);
	pNode = addBranch(pNode);
	pNode->setLocation(offset_x + sin(Rad(15 * 18)) * radial, offset_y + cos(Rad(15 * 18)) * radial);
	pBranchNode[2] = pNode; // Left wing

	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(16 * 18)) * radial, offset_y + cos(Rad(16 * 18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(17 * 18)) * radial, offset_y + cos(Rad(17 * 18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(18 * 18)) * radial, offset_y + cos(Rad(18 * 18)) * radial);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x + sin(Rad(19 * 18)) * radial, offset_y + cos(Rad(19 * 18)) * radial);
	pNode = addBranch(pNode);
	pBranchNode[3] = pNode;
	pNode->setLocation(offset_x + sin(Rad(20 * 18)) * radial, offset_y + cos(Rad(20 * 18)) * radial);

	pNode = addOut(pNode);
	pNode->setLocation(offset_x, offset_y - radial + radial * 2 * 13 / 12);
	pOutNode = pNode;

	// Left wing <--------Cross--------> Right wing
	pNode = pBranchNode[0]->addSingle();
	pNode->setLocation(offset_x - radial + radial * 2 * 5 / 6, offset_y);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x - radial + radial * 2 * 4 / 6, offset_y);
	pNode = addCross(pNode);
	pCrossNode = pNode;
	pNode->setLocation(offset_x - radial + radial * 2 * 3 / 6, offset_y);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x - radial + radial * 2 * 2 / 6, offset_y);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x - radial + radial * 2 * 1 / 6, offset_y);
	pNode->SetNextNode(pBranchNode[2]);
	
	// Top  <--------Cross---------> Out
	pNode = pBranchNode[1]->addSingle();
	pNode->setLocation(offset_x , offset_y - radial + radial * 2 * 1 / 6);
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x , offset_y - radial + radial * 2 * 2 / 6);

	pNode->SetNextNode(pCrossNode);
	
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x , offset_y - radial + radial * 2 * 4 / 6);
	pCrossNode->SetNextNode(pNode);
	
	pNode = addSingle(pNode);
	pNode->setLocation(offset_x , offset_y - radial + radial * 2 * 5 / 6);
	pNode->SetNextNode(pBranchNode[3]);


	pNode = addReadyNode(pNode);
	pNode->setLocation(offset_x+400, offset_y - radial + radial * 2 * 13 / 12);
	pReadyNode = pNode;

}

