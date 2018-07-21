#include "stdafx.h"
#include "PixelCollision.h"


HRESULT PixelCollision::init()
{
	//// 백그라운드 이미지
	//bgImage = IMAGEMANAGER->addImage("background", "resource\\cloud_1500x600.bmp", 1500, 600);
	//miniBgImage = IMAGEMANAGER->addImage("minimountain", "resource\\map_2000x800.bmp", 200, 80, true, RGB(255, 0, 255));
	//_mountain = IMAGEMANAGER->addImage("mountain", "resource\\map_2000x800.bmp", 2000, 800, true, RGB(255, 0, 255));


	return S_OK;
}

void PixelCollision::release()
{
}

void PixelCollision::update()
{
	
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

}

void PixelCollision::render()
{
}
