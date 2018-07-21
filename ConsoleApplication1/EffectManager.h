#pragma once
#include "SingletonBase.h"
#include "Image.h"

struct Effect
{
	Image * eImage;
	float x, y;
	int index, count;
};

class EffectManager : public SingletonBase<EffectManager>
{
private:
	list<Effect> effectList;

public:
	HRESULT init();	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	void release();
	void render(HDC hdc);

	void generateEffect(const char *effectName, float x, float y);

	EffectManager();
	~EffectManager();
};

