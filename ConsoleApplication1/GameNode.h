#pragma once
#include "Image.h"

class GameNode
{
private:
	Image * _backBuffer;	// ����� �̹���
	void setBackBuffer();	// ����� �����ϱ�
	
public:
	virtual HRESULT init(void);	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	// ����� �̹��� ���
	Image* getBackBuffer(void) { return _backBuffer; }

	// ���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {} // �Ҹ��ڿ� virtual Ű���带 ���̴� ���� ������ �ܰ�����
};

