#include "stdafx.h"
#include "Tank.h"


HRESULT Tank::init()
{
	map = IMAGEMANAGER->addImage("mountain", "resource\\map_2000x800.bmp", 2000, 800, true, RGB(255, 0, 255));
	shape[IDLE] = IMAGEMANAGER->addFrameImage("basic", "resource\\tank_52x92_1x2.bmp", 52, 92, 1, 2);
	bulletImage = IMAGEMANAGER->addFrameImage("basicbullet", "resource\\bullet_50x400_1x8.bmp", 50, 400, 1, 8);
	state = IDLE;
	
	angle = 0;



	x = y = oldX = oldY = dirX = dirY = angle = 0;
	speed = 5.0f;
	canonAngle = 0;
	shootingPower = 0;
	state = 0;
	dir = RIGHT;
	probeY = 0;

	bullet = new Bullet[MAX_BULLET];
	memset(bullet, 0, sizeof(Bullet)*MAX_BULLET);

	return S_OK;
}

void Tank::release()
{
}

void Tank::update()
{
	inputProcess();

	collisionBox = RectMakeCenter(x, y, shape[state]->getFrameWidth(), shape[state]->getFrameHeight());
	probeY = y + shape[state]->getFrameHeight() / 2;
	//probeY = collisionBox.bottom;

	for (int i = 0; i < MAX_BULLET; ++i)
	{
		if (bullet[i].getIsFire())
		{
			bullet[i].move();
		}
	}

	collision();

	dir = convertDir(angle);
}

void Tank::render()
{	
	Camera* cam = CAM;

	shape[state]->frameRender(getMemDC(), collisionBox.left - cam->getX(), collisionBox.top - cam->getY(), 0, dir);

	LineMake(getMemDC(), x - cam->getX(), y - cam->getY(), x - cam->getX() + cos(canonAngle) * 50, y - cam->getY() + -sin(canonAngle) * 50);


	for (int i = 0; i < MAX_BULLET; ++i)
	{
		if (bullet[i].getIsFire())
		{
			bulletImage->setFrameY(bullet[i].getDir());
			bulletImage->frameRender(getMemDC(), bullet[i].getX() - bulletImage->getFrameWidth()/2 - cam->getX(), bullet[i].getY() - bulletImage->getFrameWidth()/2 - cam->getY());


			char str1[128];
			sprintf_s(str1, "%.3f", bullet[i].getAngle() * 180 / PI);
			TextOut(getMemDC(), 10, 10, str1, strlen(str1));
		}
	}


	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		//shape[state]->setCenter(x, y);
		//Rectangle(getMemDC(), shape[state]->boundingBoxWidthFrame());
		Rectangle(getMemDC(), collisionBox.left - cam->getX(), collisionBox.top - cam->getY(), collisionBox.right - cam->getX(), collisionBox.bottom - cam->getY());
		RectangleMakeCenter(getMemDC(), x - cam->getX(), probeY - cam->getY(), 10, 10);

		char str[128];
		sprintf_s(str, "%.3f %.3f : %.3f %.3f", x, y, cam->getX(), cam->getY());
		TextOut(getMemDC(), 10, 10, str, strlen(str));
	}
}

void Tank::inputProcess()
{
	

}

void Tank::fireBullet()
{
	for (int i = 0; i < MAX_BULLET; ++i)
	{
		if (!bullet[i].getIsFire())
		{
			bullet[i].fire(x, y, canonAngle, shootingPower, curTurn);
		}
	}
}

void Tank::collision()
{
	bool isFall = true;
	for (int i = probeY - 20; i < probeY + 20; i++)
	{
		COLORREF color = GetPixel(map->getMemDC(), x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255)) // (r == 255 && g == 0 && b == 255)
		{
			isFall = false;
			y = i - shape[state]->getFrameHeight()/2;
			break;
		}
	}
	if (isFall)
	{
		y++;
	}


	//for (int i = 0; i < MAX_BULLET; ++i)
	//{
	//	if (!bullet[i].getIsFire() || bullet[i].getY() < 0 ) continue;

	//	COLORREF color = GetPixel(map->getMemDC(), bullet[i].getX(), bullet[i].getY());

	//	if (!(color == RGB(255, 0, 255))) // (r == 255 && g == 0 && b == 255)
	//	{
	//		HBRUSH brush, oBrush;
	//		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	//		SelectObject(map->getMemDC(), pen);
	//		brush = CreateSolidBrush(RGB(255, 0, 255));
	//		SelectObject(map->getMemDC(), brush);
	//		Ellipse(map->getMemDC(), bullet[i].getHitRange());
	//		DeleteObject(brush);
	//		DeleteObject(pen);

	//		*curTurn = (*curTurn + 1) % 2;
	//		
	//		bullet[i].setIsFire(false);

	//		break;
	//	}
	//}
}
