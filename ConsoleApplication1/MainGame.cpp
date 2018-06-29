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

	_playerImage = new Image;
	//_playerImage->init("resource\\run.bmp", 320, 90, 8, 2);
	_playerImage->init("resource\\run.bmp", 400.0f, 400.0f, 320, 90, 8, 2);
	_imgCount = 0;
	_imgIndex = 0;
	_isLeft = true;

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
	SAFE_DELETE(_playerImage);
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

	// ������������ �� �ε��� �����ϱ�( �ִϸ��̼� )
	if (_isLeft)	// ���� ������
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
	else			// ������ ������
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

	_playerImage->frameRender(memDC, _playerImage->getX(), _playerImage->getY());

//======================================================================================
	// ������� ������ HDC�� �׸��� 
	this->getBackBuffer()->render(hdc);
}
