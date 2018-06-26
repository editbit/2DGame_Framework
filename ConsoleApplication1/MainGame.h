#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	Image * _bgImage;			// 백그라운드 이미지
	Image * _face;				// 얼굴 이미지
	RECT _rc;					// 렉트

public:
	virtual HRESULT init(void);	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	MainGame() {}
	virtual ~MainGame() {}
};
