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
