#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	Image * _bgImage;			// ��׶��� �̹���

	Image* _bgI;
	Image* _face;

	int _alpha;
	int _count;


	Image* _playerImage;
	int _imgCount;
	int _imgIndex;
	bool _isLeft;

public:
	virtual HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	MainGame() {}
	virtual ~MainGame() {}
};
