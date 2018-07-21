#include "stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(const char * frontImageKey, const char * backImageKey, int _x, int _y, int _width, int _height)
{
	// 체력바 위치 초기화
	x = _x;
	y = _y;

	// 체력바 가로, 세로 길이 초기화
	width = _width;
	height = _height;

	// 체력바 렉트 위치 및 크기 초기화
	rcProgress = RectMake(x, y, width, height);

	// 키값으로 이미지 이름(~.bmp)으로 바로 초기화
	char frontImage[128];
	char backImage[128];

	// 메모리 0로 초기화
	memset(frontImage, 0, sizeof(frontImage));
	memset(backImage, 0, sizeof(backImage));

	// ~.bmp로 만들기
	// 키, 파일이름 IMAGEMANAGER->addImage("키값", "파일이름", ... );
	sprintf_s(frontImage, "%s.bmp", frontImageKey);
	sprintf_s(backImage, "%s.bmp", backImageKey);

	// 체력바 이미지 초기화
	progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImage, x, y, width, height, true, RGB(255, 0, 255));
	progressBarBack = IMAGEMANAGER->addImage(backImageKey, backImage, x, y, width, height, true, RGB(255, 0, 255));


	return S_OK;
}

HRESULT ProgressBar::init()
{
	return S_OK;
}

void ProgressBar::release()
{

}

void ProgressBar::update()
{
	rcProgress = RectMake(x, y, progressBarBack->getWidth(), progressBarBack->getHeight());
}

void ProgressBar::render()
{
	progressBarBack->render(getMemDC(), rcProgress.left, y);
	progressBarFront->render(getMemDC(), rcProgress.left, y, 0, 0, width, progressBarFront->getHeight());
}

void ProgressBar::setGauge(float _currentHp, float _maxHp)
{
	width = (_currentHp / _maxHp) * progressBarBack->getWidth();
}

void ProgressBar::setInfo(int _x, int _y, float _currentHp, float _maxHp)
{
	x = _x;
	y = _y;
	width = (_currentHp / _maxHp) * progressBarBack->getWidth();
}
