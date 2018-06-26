#include "stdafx.h"
#include "MainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT MainGame::init(void)
{
	GameNode::init();
	// 이곳에서 초기화를 한다.
	
	// 백그라운드 이미지 초기화
	_bgImage = new Image;
	_bgImage->init("라이언.bmp", WINSIZEX, WINSIZEY);

	_face = new Image;
	_face->init("라이언몸.bmp", 150, 150, true, RGB(255, 0, 255));

	//렉트 초기화
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 150, 150);

	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void MainGame::release(void)
{
	GameNode::release();
	// 이미지 클래스 나갈 때까진 사용 X
	// init함수에서 동적할당한 메모리만 delete로 해제해준다.

	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_face);
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void MainGame::update(void)
{
	GameNode::update();
	// 이곳에서 계산식, 키보드, 마우스 등등 업데이트를 한다
	// 간단한게 이곳에서 코딩한다고 생각하면 된다.

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_rc.left -= 5.0f;
		_rc.right -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_rc.left += 5.0f;
		_rc.right += 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_rc.top -= 5.0f;
		_rc.bottom -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_rc.top += 5.0f;
		_rc.bottom += 5.0f;
	}
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void MainGame::render(HDC hdc)
{


	/*SetDCBrushColor(hdc, RGB(100, 0, 0));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	int r = RND->getFromIntTo(200, 256), g = RND->getFromIntTo(100, 256), b = RND->getFromIntTo(100, 256);*/


	/*
	char str[10];
	sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(hdc, 10, 10, str, strlen(str));
	*/

	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 흰색 빈 비트맵
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

//======================================================================================
	// 백 그라운드 이미지 렌더

	_bgImage->render(memDC);
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(memDC, _rc);
	}
	_face->render(memDC, _rc.left, _rc.top);


//======================================================================================

	// 백버퍼의 내용을 HDC에 그린다 
	this->getBackBuffer()->render(hdc);
}
