#include "stdafx.h"
#include "Camera.h"

void Camera::videoShooting(int _x, int _y)
{
	x = _x - WINSIZEX / 2;
	y = _y - WINSIZEY / 2;
	videoShooting();
}

void Camera::videoShooting()
{
	if (x < 0)
	{
		x = 0;
	}
	else if (x + WINSIZEX > maxWidth)
	{
		x = maxWidth - WINSIZEX;
	}

	if (y < 0)
	{
		y = 0;
	}
	else if (y + WINSIZEY > maxHeight)
	{
		y = maxHeight - WINSIZEY;
	}

	sX = sY = 0;
	if (count > 0)
	{
		count--;
		sX = RND->getInt(shakingPower) - shakingPower / 2;
		sY = RND->getInt(shakingPower) - shakingPower / 2;
	}

}

HRESULT Camera::init()
{
	x = 0;
	y = 0;
	maxWidth = WINSIZEX;
	maxHeight = WINSIZEY;
	count = 0;
	sX = sY = shakingPower = 0;
	return S_OK;
}

void Camera::release()
{
}
