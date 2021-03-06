#pragma once
#include "GameNode.h"
#include "PixelCollision.h"
#include "Tank.h"

class MainGame : public GameNode
{
private:
	Image * _bgImage;
	Image * stage;


	Image *bgImage;
	Image *miniBgImage;
	Image* _mountain;			// 백그라운드 이미지

	Tank * tank;

	Camera * cam;

	RECT winsize;

	int curTurn;

	int effectCount;

	int loopX, loopY;
public:
	virtual HRESULT init();	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	virtual void release();
	virtual void update();
	virtual void render();

	MainGame() {}
	virtual ~MainGame() {}
};
