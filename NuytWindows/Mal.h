#pragma once
#include "Node.h"

enum MALStatus
{
	MAL_ON_BOARD,
	MAL_ON_BOARD_DOUBLE,
	MAL_ON_BOARD_TRIPLE,
	MAL_SUCCESS_TRIP,
	MAL_READYTOGO,
	MAL_STATE_MAX
};
class Player;
class Phys
{
public:
	double x;
	double y;
	double vx;
	double vy;
	double ax;
	double ay;

};

class Mal:public Phys
{
	Player* mpPlayer;
	enum MALStatus mStatus;


public:
	Node* mpMalLocation;
	Node* mpDestNode;
	Node* mpStartNode;
	Node* mpBackNode;
	bool isDouble;
	bool isTriple;

	Mal(Player * pPlayer)
	{
		mpPlayer = pPlayer;
		setMalStatus(MAL_READYTOGO);
		isDouble = false;
		isTriple = false;
		mpMalLocation = NULL;
	}

	void setMalLocation(Node * pNode)
	{
		mpMalLocation = pNode;
		x = pNode->getLocation().x;
		y = pNode->getLocation().y;

		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
	}

	Node* getMalLocation(Node * pNode)
	{
		if (pNode->getType() == NODE_TYPE_HOME)
		{
			x = mpMalLocation->getLocation().x;
			y = mpMalLocation->getLocation().y;
			vx = 0;
			vy = 0;
			ax = 0;
			ay = 0;
		};
		return mpMalLocation;
	}

	Phys* getPhyical()
	{
		POINT dest;
		double distance;
		if (!mpDestNode)
			mpDestNode = mpMalLocation;
		dest = mpDestNode->getLocation();
		distance = (((double)dest.x - x) * ((double)dest.x - x) + ((double)dest.y - y) * ((double)dest.y - y));

		if (distance > 1000)
		{
			ax = 10 * (dest.x - x) / sqrt(distance);
			ay = 10 * (dest.y - y) / sqrt(distance);
			vx += ax;
			vy += ay;

		}
		else
		{
			if (mpMalLocation != mpDestNode)
				mpDestNode = mpDestNode->passThrough(1, mpDestNode, mpStartNode);
			else
				mpDestNode = mpMalLocation;
			ax *= 0.9;
			ay *= 0.9;
			vx *= 0.5;
			vy *= 0.5;

			
		}

		/*
		if (vx * vx + vy * vy > 10000)
		{
			vx *= 100 / sqrt(vx * vx + vy * vy);
			vy *= 100 / sqrt(vx * vx + vy * vy);
		}
		*/
		vx *= 0.9;
		vy *= 0.9;

		x += vx;
		y += vy;

		return (Phys * )this;
	}


	void setMalStatus(enum MALStatus status)
	{
		mStatus = status;
	}
};