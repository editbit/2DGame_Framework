#pragma once
#include "SingletonBase.h"

class GameNode;

class RenderManager : public SingletonBase<RenderManager>
{
private:
	multimap<float, GameNode *> renderList;

public:
	HRESULT init();	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	void release();
	void render(HDC hdc);

	void addRender(GameNode *effectName, float z);

	RenderManager() {}
	~RenderManager() {}
};

