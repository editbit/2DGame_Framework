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
	//_bgImage = new Image;
	//_bgImage->init("라이언.bmp", WINSIZEX, WINSIZEY);

	_bgI = new Image;
	_bgI->init("resource\\라이언배경.bmp", WINSIZEX, WINSIZEY, true, RGB(0, 0, 0));

	_face = new Image;
	_face->init("resource\\라이언.bmp", 150, 150, true, RGB(255, 0, 255));

	_alpha = 0;
	_count = 0;

	_playerImage = new Image;
	//_playerImage->init("resource\\run.bmp", 320, 90, 8, 2);
	_playerImage->init("resource\\run.bmp", 400.0f, 400.0f, 320, 90, 8, 2);
	_imgCount = 0;
	_imgIndex = 0;
	_isLeft = true;

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
	SAFE_DELETE(_bgI);
	SAFE_DELETE(_face);
	SAFE_DELETE(_playerImage);
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void MainGame::update(void)
{
	GameNode::update();
	// 이곳에서 계산식, 키보드, 마우스 등등 업데이트를 한다
	// 간단한게 이곳에서 코딩한다고 생각하면 된다.

	_count = (_count + 1) % 10;
	if (_count == 0)
	{
		_alpha += 10;
		if (_alpha > 256) _alpha = 255;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		_playerImage->setX(_playerImage->getX() - 2.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		_playerImage->setX(_playerImage->getX() + 2.0f);
	}

	// 왼쪽프레임일 때 인덱스 변경하기( 애니메이션 )
	if (_isLeft)	// 왼쪽 프레임
	{
		_imgCount = (_imgCount + 1) % 5;
		_playerImage->setFrameY(0);
		if(_imgCount == 0)
		{
			_imgIndex++;
			if (_imgIndex > _playerImage->getMaxFrameX())
			{
				_imgIndex = 0;
			}
			_playerImage->setFrameX(_imgIndex);
		}
	}
	else			// 오른쪽 프레임
	{
		_imgCount = (_imgCount + 1) % 5;
		_playerImage->setFrameY(1);
		if (_imgCount == 0)
		{
			_imgIndex--;
			if (_imgIndex < 0)
			{
				_imgIndex = _playerImage->getMaxFrameX();
			}
			_playerImage->setFrameX(_imgIndex);
		}
	}
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void MainGame::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 흰색 빈 비트맵
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

//======================================================================================
	// 백 그라운드 이미지 렌더


	//_bgImage->render(memDC, 0, 0);
	_bgI->render(memDC);
	_bgI->alphaRender(memDC, 100, 110, 500, 200, 400, 500, _alpha);
	_face->alphaRender(memDC, 10, 20, _alpha);


	char str[128];
	wsprintf(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(memDC, 10, 10, str, strlen(str));

	_playerImage->frameRender(memDC, _playerImage->getX(), _playerImage->getY());

//======================================================================================
	// 백버퍼의 내용을 HDC에 그린다 
	this->getBackBuffer()->render(hdc);
}
