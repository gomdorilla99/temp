
// NyutView.h: CNyutView 클래스의 인터페이스
//

#pragma once
#include "Game.h"
#include "Player.h"

class Game;

class CNyutView : public CView
{
protected: // serialization에서만 만들어집니다.
	CNyutView() noexcept;
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_DYNCREATE(CNyutView)

// 특성입니다.
public:
	CNyutDoc* GetDocument() const;

// 작업입니다.
public:
	CString DebugMessage;

// 재정의입니다.
public:
	virtual void OnTimer(UINT_PTR nIDEven);
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo); 
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CNyutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int mTurn;
	
	int GetNyutNumber()
	{
		int number;
		srand(time(NULL));
		number = rand() % 16;
		
			switch (number)
			{
			case 0:
				number = 5;    //Mo
				break;
			case 1:
				number = 4;    //Lyut
				break;
			case 2:
				number = -1;
				break;
			case 3:
			case 4:
			case 5:
				number = 1;    //Do
				break;
			case 6:
			case 7:
			case 8:
			case 9:
				number = 3;    //Gual
				break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				number = 2;    //개
				break;
			default:
				number = 0;
			}
		return number;
	}

	Game game;
	


// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // NyutView.cpp의 디버그 버전
inline CNyutDoc* CNyutView::GetDocument() const
   { return reinterpret_cast<CNyutDoc*>(m_pDocument); }
#endif

