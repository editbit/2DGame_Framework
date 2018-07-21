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
	HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	void release();
	void render(HDC hdc);

	void generateEffect(const char *effectName, float x, float y);

	EffectManager();
	~EffectManager();
};

