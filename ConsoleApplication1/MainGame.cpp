#include "stdafx.h"
#include "MainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT MainGame::init(void)
{
	GameNode::init();
	// �̰����� �ʱ�ȭ�� �Ѵ�.
	
	// ��׶��� �̹��� �ʱ�ȭ
	//_bgImage = new Image;
	//_bgImage->init("���̾�.bmp", WINSIZEX, WINSIZEY);

	_bgI = new Image;
	_bgI->init("resource\\���̾���.bmp", WINSIZEX, WINSIZEY, true, RGB(0, 0, 0));

	_face = new Image;
	_face->init("resource\\���̾�.bmp", 150, 150, true, RGB(255, 0, 255));

	_alpha = 0;
	_count = 0;

	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void MainGame::release(void)
{
	GameNode::release();
	// �̹��� Ŭ���� ���� ������ ��� X
	// init�Լ����� �����Ҵ��� �޸𸮸� delete�� �������ش�.

	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_bgI);
	SAFE_DELETE(_face);
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void MainGame::update(void)
{
	GameNode::update();
	// �̰����� ����, Ű����, ���콺 ��� ������Ʈ�� �Ѵ�
	// �����Ѱ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�.

	_count = (_count + 1) % 10;
	if (_count == 0)
	{
		_alpha += 10;
		if (_alpha > 256) _alpha = 255;
	}
}

//=============================================================
//	## ���� ## render(HDC hdc)
//=============================================================
void MainGame::render(HDC hdc)
{
	// ����� ��������
	HDC memDC = this->getBackBuffer()->getMemDC();
	// ��� �� ��Ʈ��
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

//======================================================================================
	// �� �׶��� �̹��� ����


	//_bgImage->render(memDC, 0, 0);
	_bgI->render(memDC);
	_bgI->alphaRender(memDC, 100, 110, 500, 200, 400, 500, _alpha);
	_face->alphaRender(memDC, 10, 20, _alpha);


	char str[128];
	wsprintf(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(memDC, 10, 10, str, strlen(str));

//======================================================================================
	// ������� ������ HDC�� �׸��� 
	this->getBackBuffer()->render(hdc);
}
