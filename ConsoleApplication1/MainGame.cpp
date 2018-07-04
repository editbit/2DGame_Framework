#include "stdafx.h"
#include "MainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	// 이곳에서 초기화를 한다.
	_bgImage = IMAGEMANAGER->addImage("배경", "resource\\stage1.bmp", WINSIZEX, WINSIZEY);

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
void MainGame::render()
{
	// 흰색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

//======================================================================================
	// 방법 1
	_bgImage->render(getMemDC());
	// 방법 2
	//IMAGEMANAGER->render("배경", getMemDC());
	// 방법 3
	//IMAGEMANAGER->findImage("배경")->render(getMemDC());
	


//======================================================================================
	// 백버퍼의 내용을 HDC에 그린다 
	this->getBackBuffer()->render(getHDC());
}
