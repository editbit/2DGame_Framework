#include "stdafx.h"
#include "MainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT MainGame::init(void)
{
	GameNode::init();
	// 이곳에서 초기화를 한다.
	

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

}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void MainGame::update(void)
{
	GameNode::update();
	// 이곳에서 계산식, 키보드, 마우스 등등 업데이트를 한다
	// 간단한게 이곳에서 코딩한다고 생각하면 된다.

	
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void MainGame::render(HDC hdc)
{


	/*SetDCBrushColor(hdc, RGB(100, 0, 0));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	int r = RND->getFromIntTo(200, 256), g = RND->getFromIntTo(100, 256), b = RND->getFromIntTo(100, 256);*/

	char str[10];
	sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(hdc, 10, 10, str, strlen(str));
	
}
