#include "Mal.h"
#include "Player.h"
#include "Session.h"


Node* Mal::kickoff(Node* pNode)
{
	Node* LastMoveNode = nullptr;

	if (pNode == mpMalLocation)
	{
		pNode->CheckOut(this);
		mpDestNode = mpGame->getReadyNode();
		mpMalLocation = mpGame->getReadyNode();
	}
	return mpMalLocation;

}

int Mal::GetPlayerID()
{
	return mpPlayer->GetPlayerID();
}

#if 0
void Mal::Draw(CDC *pDC)
{
	POINT Point1 = mpMalLocation->getLocation();
	POINT Point;
	getPhyical();
	Point.x = x;
	Point.y = y;
	
	int radius;

	radius = 200 / sqrt(vx * vx + vy * vy);

	if (radius > 50)
		radius = 50;

	if (radius < 20)
		radius = 20;

	CRect rect(Point.x - radius, Point.y - radius, Point.x + radius, Point.y + radius);

	pDC->Ellipse(rect); // Draw Mal
	CString strMalID;
	strMalID.Format(_T("Player %d"), GetPlayerID());
	pDC->TextOutW(Point1.x + 35, Point1.y - 20, strMalID);
	
	CFont* pFont = pDC->SelectObject(&bigFont);

	if (mpMalLocation->getType() != NODE_TYPE_OUT)
	{
		pDC->TextOutW(Point1.x, Point1.y, mpPlayer->GetMessage());
	}
	else
	{
		mpPlayer->GetMessage().Format(_T("P%d 慨嬢!!"), mpPlayer->GetPlayerID());
		pDC->TextOutW(Point1.x, Point1.y, mpPlayer->GetMessage());
	}

	pDC->SelectObject(pFont);
}
#endif 

Phys* Mal::getPhyical()
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
		{
			mpDestNode = mpDestNode->passThrough(1, mpDestNode, mpStartNode);
		}
		else if(mpDestNode->GetCheckedMal() != this)
		{
			mpDestNode = mpMalLocation;
			if (mpDestNode->getType() != NODE_TYPE_OUT && mpDestNode->getType() != NODE_TYPE_READY)
			{
				if (!mpDestNode->CheckIn(this))
				{
					Mal* pMal;
					pMal = mpDestNode->GetCheckedMal();
					if (pMal != this)
					{
						pMal->kickoff(mpDestNode);
						pMal->vx = vx;
						pMal->vy = vy;
						mpPlayer->SetDeferedCount(1);
						mpPlayer->SetMessage(_T("説壱 廃腰希"));
					}
					//pMal->setMalStatus(MAL_READYTOGO);
				}
			}
			else if(mpDestNode->getType() == NODE_TYPE_OUT || mpDestNode->getType() == NODE_TYPE_READY)
			{
				setMalStatus(MAL_READYTOGO);
			}
		}
		ax *= 0.9;
		ay *= 0.9;
		vx *= 0.5;
		vy *= 0.5;


	}

	vx *= 0.9;
	vy *= 0.9;

	x += vx;
	y += vy;

	return (Phys*)this;
}
