#include "stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(const char * frontImageKey, const char * backImageKey, int _x, int _y, int _width, int _height)
{
	// ü�¹� ��ġ �ʱ�ȭ
	x = _x;
	y = _y;

	// ü�¹� ����, ���� ���� �ʱ�ȭ
	width = _width;
	height = _height;

	// ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	rcProgress = RectMake(x, y, width, height);

	// Ű������ �̹��� �̸�(~.bmp)���� �ٷ� �ʱ�ȭ
	char frontImage[128];
	char backImage[128];

	// �޸� 0�� �ʱ�ȭ
	memset(frontImage, 0, sizeof(frontImage));
	memset(backImage, 0, sizeof(backImage));

	// ~.bmp�� �����
	// Ű, �����̸� IMAGEMANAGER->addImage("Ű��", "�����̸�", ... );
	sprintf_s(frontImage, "%s.bmp", frontImageKey);
	sprintf_s(backImage, "%s.bmp", backImageKey);

	// ü�¹� �̹��� �ʱ�ȭ
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
