#pragma once
#include "SingletonBase.h"

class GameNode;

class RenderManager : public SingletonBase<RenderManager>
{
private:
	multimap<float, GameNode *> renderList;

public:
	HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	void release();
	void render(HDC hdc);

	void addRender(GameNode *effectName, float z);

	RenderManager() {}
	~RenderManager() {}
};

