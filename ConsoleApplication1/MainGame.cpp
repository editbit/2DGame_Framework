#include "stdafx.h"
#include "MainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	// 이곳에서 초기화를 한다.
	//_bgImage = IMAGEMANAGER->addImage("배경", "resource\\stage1.bmp", WINSIZEX, WINSIZEY);
	//stage = IMAGEMANAGER->addImage("stage1", "resource\\stage1.bmp", 1000, 800, true, RGB(255, 0, 255));
	//CAM->setRange(stage->getWidth(), stage->getHeight());

	bgImage = IMAGEMANAGER->addImage("background", "resource\\cloud_1500x600.bmp", 1500, 600);
	miniBgImage = IMAGEMANAGER->addImage("minimountain", "resource\\map_2000x800.bmp", 200, 80, true, RGB(255, 0, 255));
	_mountain = IMAGEMANAGER->addImage("mountain", "resource\\map_2000x800.bmp", 2000, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("explode1", "resource\\ex_4356x200_16x1.bmp", 4356, 200, 16, 1);
	IMAGEMANAGER->addFrameImage("explode2", "resource\\explosion_832x62_26x1.bmp", 832, 62, 26, 1);

	tank = new Tank[2];
	tank[0].init();
	tank[1].init();

	// 공 위치 초기화
	tank[0].setX(WINSIZEX / 2);
	tank[0].setY(WINSIZEY / 2);
	tank[0].setCurTurn(&curTurn);

	tank[1].setX(WINSIZEX / 2 - 100);
	tank[1].setY(WINSIZEY / 2);
	tank[1].setCurTurn(&curTurn);


	cam = CAM;
	cam->setRange(_mountain->getWidth(), _mountain->getHeight());
	cam->setPosition(tank->getX(), tank->getY());

	winsize = { 0, 0, WINSIZEX, WINSIZEY };

	loopX = loopY = 0;
	curTurn = 0;

	effectCount = 0;
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

	tank[0].release();
	tank[1].release();
	SAFE_DELETE_ARRAY(tank);
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void MainGame::update(void)
{
	GameNode::update();
	///////////

	effectCount = (effectCount + 1) % 5;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if(effectCount == 0)
			EFFECT->generateEffect("explode2", tank[curTurn].getX(), tank[curTurn].getY());
		tank[curTurn].setX(tank[curTurn].getX() - 3.0f);
		tank[curTurn].setAngle(PI);
		if (tank[curTurn].getDir() == RIGHT)
		{
			tank[curTurn].setCanonAngle(PI - tank[curTurn].getCanonAngle());
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (effectCount == 0)
			EFFECT->generateEffect("explode2", tank[curTurn].getX(), tank[curTurn].getY());
		tank[curTurn].setX(tank[curTurn].getX() + 3.0f);
		tank[curTurn].setAngle(0);
		if (tank[curTurn].getDir() == LEFT)
		{
			tank[curTurn].setCanonAngle(PI - tank[curTurn].getCanonAngle());
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (tank[curTurn].getDir() == RIGHT)
		{
			tank[curTurn].setCanonAngle(tank[curTurn].getCanonAngle() + 0.05f);
			if (tank[curTurn].getCanonAngle() > PI / 2)
				tank[curTurn].setCanonAngle(PI / 2);
		}
		else
		{
			tank[curTurn].setCanonAngle(tank[curTurn].getCanonAngle() - 0.05f);
			if (tank[curTurn].getCanonAngle() < PI / 2)
				tank[curTurn].setCanonAngle(PI / 2);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{

		if (tank[curTurn].getDir() == RIGHT)
		{
			tank[curTurn].setCanonAngle(tank[curTurn].getCanonAngle() - 0.05f);
			if (tank[curTurn].getCanonAngle() <0)
				tank[curTurn].setCanonAngle(0);
		}
		else
		{
			tank[curTurn].setCanonAngle(tank[curTurn].getCanonAngle() + 0.05f);
			if (tank[curTurn].getCanonAngle() > PI)
				tank[curTurn].setCanonAngle(PI);
		}
	}

	if (KEYMANAGER->isStayKeyDown(' '))
	{
		tank[curTurn].setShootingPower(tank[curTurn].getShootingPower() + 0.3f);
	}
	if (KEYMANAGER->isOnceKeyUp(' '))
	{
		tank[curTurn].fireBullet();
		tank[curTurn].setShootingPower(0);
	}



	tank[0].update();
	tank[1].update();



	/* 이 부분이 픽셀충돌의 핵심 */
	// 탐지할 y값의 범위를 위아래로 원하는 만큼 검사를 한다.

	//bool isFall = true;
	//for (int i = _probeY - 20; i < _probeY + 20; i++)
	//{
	//	COLORREF color = GetPixel(_mountain->getMemDC(), _x, i);
	//	int r = GetRValue(color);
	//	int g = GetGValue(color);
	//	int b = GetBValue(color);

	//	if (!(r == 255 && g == 0 && b == 255)) // (r == 255 && g == 0 && b == 255)
	//	{
	//		isFall = false;
	//		_y = i - _ball->getHeight() / 2;
	//		break;
	//	}
	//}
	//if (isFall)
	//{
	//	_y++;
	//}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		HBRUSH brush, oBrush;
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		SelectObject(_mountain->getMemDC(), pen);
		brush = CreateSolidBrush(RGB(255, 0, 255));
		oBrush = (HBRUSH)SelectObject(_mountain->getMemDC(), brush);
		Ellipse(_mountain->getMemDC(), RectMakeCenter(_ptMouse.x, _ptMouse.y, 50, 50));
		SelectObject(_mountain->getMemDC(), oBrush);
		DeleteObject(brush);
		DeleteObject(pen);
	}


	if (!tank[curTurn].getBullet()->getIsFire())
	{
		cam->videoShooting(tank[curTurn].getX(), tank[curTurn].getY());
	}
	else
	{
		cam->videoShooting(tank[curTurn].getBullet()->getX(), tank[curTurn].getBullet()->getY());
	}
	loopX = (loopX + 1) % bgImage->getWidth();
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void MainGame::render()
{
	// 흰색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

//======================================================================================
	bgImage->loopRender(getMemDC(), &winsize, loopX, loopY);

	//bgImage->render(getMemDC());
	_mountain->render(getMemDC(), cam->getSX(), cam->getSY(), cam->getX(), cam->getY(), WINSIZEX, WINSIZEY);
	//_mountain->render(getMemDC(), 0, 0, 100, 100, WINSIZEX, WINSIZEY);
	//miniBgImage->render(getMemDC(), 10, 10);
	_mountain->stretchRender(getMemDC(), 0, 0, 0.1f);

	for (int i = 0; i<2; ++i)
		Rectangle(getMemDC(), RectMakeCenter(tank[i].getX() / 10, tank[i].getY() / 10, 5, 5));


	if (tank[curTurn].getBullet()->getIsFire())
	{
		Rectangle(getMemDC(), RectMakeCenter(tank[curTurn].getBullet()->getX() / 10, tank[curTurn].getBullet()->getY() / 10, 5, 5));
	}


	//tank[0].render();
	//tank[1].render();
	RENDER->addRender(&tank[curTurn], 1);
	RENDER->addRender(&tank[(curTurn + 1) % 2], 0);

	RENDER->render(getMemDC());
	EFFECT->render(getMemDC());
//======================================================================================
	// 백버퍼의 내용을 HDC에 그린다 
	this->getBackBuffer()->render(getHDC());
}


/*
font = CreateFont(
문자 크기, 문자 폭, 문자 기울기, 문자 방향, 문자 굵기,
기울기(bool), 밑줄(bool), 취소선(bool),
문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
)
*/
// 문자 폭은 문자크기에 따라 비례하게 표시. 0으로 두는 것이 좋음

/* 폰트 사용법
HFONT font;
HFONT oldFont;

font = CreateFont(70, 0, 0, 0, 600, false, false, true, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림"));
oldFont = (HFONT)SelectObject(getMemDC(), font);

char str[128];
sprintf_s(str, "폰트 사용법");
TextOut(getMemDC(), 100, 300, str, strlen(str));
SelectObject(getMemDC(), oldFont);
DeleteObject(font);
*/
// 방법 1
//_bgImage->render(getMemDC());
// 방법 2
//IMAGEMANAGER->render("배경", getMemDC());
// 방법 3
//IMAGEMANAGER->findImage("배경")->render(getMemDC());

//RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
//_bgImage->loopRender(getMemDC(), &rc, _loopX, _loopY);
//_bgImage->loopAlphaRender(getMemDC(), &rc, _loopX, _loopY, _alpha);


//SCENEMANAGER->getCurrentScene()->render();