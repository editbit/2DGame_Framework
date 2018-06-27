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
	_bgImage = new Image;
	_bgImage->init("���̾�.bmp", WINSIZEX, WINSIZEY);

	_face = new Image;
	_face->init("���̾��.bmp", 150, 150, true, RGB(255, 0, 255));

	//��Ʈ �ʱ�ȭ
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 150, 150);

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
//	## ���� ## render(HDC hdc)
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

	// ����� ��������
	HDC memDC = this->getBackBuffer()->getMemDC();
	// ��� �� ��Ʈ��
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

//======================================================================================
	// �� �׶��� �̹��� ����

	_bgImage->render(memDC, 50, 50, 280 + _rc.left, 220, 500, 520);
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(memDC, _rc);
	}
	_face->render(memDC, _rc.left, _rc.top);


//======================================================================================

	// ������� ������ HDC�� �׸��� 
	this->getBackBuffer()->render(hdc);
}
