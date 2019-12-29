#include "Session.h"

// NyutView.cpp: CNyutView 클래스의 구현
//
int main(int argc, char **argv)
{

	game.Draw(pDC);

	while (1)
	{
		int number;
		Node *pNode;
		if (mTurn == 0)
		{
			number = GetNyutNumber();
			pNode = game.Player1.run(number, 0);
			if (pNode)
			{
				game.Player2.checkout(pNode);
				game.Player3.checkout(pNode);
			}
			mTurn = 1;
		}

		else if (mTurn == 1)
		{
			number = GetNyutNumber();
			pNode = game.Player2.run(number, 0);
			if (pNode)
			{
				game.Player1.checkout(pNode);
				game.Player3.checkout(pNode);
			}
			mTurn = 2;
		}
		else if (mTurn == 2)
		{
			number = GetNyutNumber();
			pNode = game.Player3.run(number, 0);
			if (pNode)
			{
				game.Player1.checkout(pNode);
				game.Player2.checkout(pNode);
			}
			mTurn = 0;
		}
	}
}
