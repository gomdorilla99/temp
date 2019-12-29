
// NyutView.cpp: CNyutView 클래스의 구현
//

// CNyutView 그리기

void CNyutView::OnDraw(CDC* pDC)
{
	CNyutDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	game.Draw(pDC);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CNyutView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	int number;
	Node* pNode;
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

	else if( mTurn == 1)
	{
		number = GetNyutNumber();
		pNode = game.Player2.run(number, 0);
		if (pNode)
		{
			game.Player1.checkout(pNode);
			game.Player3.checkout(pNode);
		}
		mTurn =2;
	}
	else if(mTurn == 2)
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
	Invalidate(false);

}



