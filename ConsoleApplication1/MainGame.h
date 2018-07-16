#pragma once
#include "GameNode.h"




class MainGame : public GameNode
{
private:
	Image * _bgImage;


public:
	virtual HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	virtual void release();
	virtual void update();
	virtual void render();

	MainGame() {}
	virtual ~MainGame() {}
};
