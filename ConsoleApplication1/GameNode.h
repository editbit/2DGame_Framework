#pragma once
#include "Image.h"

class GameNode
{
private:
	Image * _backBuffer;	// ����� �̹���
	void setBackBuffer();	// ����� �����ϱ�
	
public:
	virtual HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	// ����� �̹��� ���
	Image* getBackBuffer() { return _backBuffer; }

	// ���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {} // �Ҹ��ڿ� virtual Ű���带 ���̴� ���� ������ �ܰ�����
};

