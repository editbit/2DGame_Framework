#include "stdafx.h"
#include "Bullet.h"


//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들면 된다)
//=============================================================
void Bullet::fire(float _x, float _y, float _angle, float _speed, int *_curTurn)
{
	x = _x;
	y = _y;
	angle = _angle;
	speed = _speed;
	dirX = cos(angle);
	dirY = -sin(angle);
	gravity = 0;
	dir = 0;
	curTurn = _curTurn;
	isFire = true;

	ground = IMAGEMANAGER->findImage("mountain");
}

void Bullet::move()
{
	oldX = x;
	oldY = y;

	gravity += 0.2f;
	for (int i = 0; i < speed; ++i)
	{
		;
		x += dirX;
		y += dirY + gravity/speed;
		collision();
	}

	angle = getAnglef(oldX, oldY, x, y);

	dir = 7.9 - angle / (PI / 4);

	if (x < 0 || x > CAM->getMaxWidth() || y > CAM->getMaxHeight())
	{
		isFire = false;
		*curTurn = (*curTurn + 1) % 2;
	}
}

void Bullet::collision()
{
	if (!isFire || y < 0) return;

	COLORREF color = GetPixel(ground->getMemDC(), x, y);

	if (!(color == RGB(255, 0, 255))) // (r == 255 && g == 0 && b == 255)
	{
		HBRUSH brush, oBrush;
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		SelectObject(ground->getMemDC(), pen);
		brush = CreateSolidBrush(RGB(255, 0, 255));
		SelectObject(ground->getMemDC(), brush);
		Ellipse(ground->getMemDC(), getHitRange());
		DeleteObject(brush);
		DeleteObject(pen);

		*curTurn = (*curTurn + 1) % 2;

		isFire = false;

		EFFECT->generateEffect("explode1", x+20, y-50);
	}
}

