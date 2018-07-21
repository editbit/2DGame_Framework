#pragma once
#include "GameNode.h"
class PixelCollision :
	public GameNode
{
	Image *bgImage;
	Image *miniBgImage;
	Image* _mountain;			// ��׶��� �̹���

	Camera * cam;

	RECT winsize;

	int curTurn;

	int loopX, loopY;
public:
	virtual HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	virtual void release();
	virtual void update();
	virtual void render();

	PixelCollision() {}
	~PixelCollision() {}
};

