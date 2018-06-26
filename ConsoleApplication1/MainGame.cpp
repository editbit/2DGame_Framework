#include "stdafx.h"
#include "MainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT MainGame::init(void)
{
	GameNode::init();
	// �̰����� �ʱ�ȭ�� �Ѵ�.
	

	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void MainGame::release(void)
{
	GameNode::release();
	// �̹��� Ŭ���� ���� ������ ��� X
	// init�Լ����� �����Ҵ��� �޸𸮸� delete�� �������ش�.

}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void MainGame::update(void)
{
	GameNode::update();
	// �̰����� ����, Ű����, ���콺 ��� ������Ʈ�� �Ѵ�
	// �����Ѱ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�.

	
}

//=============================================================
//	## ���� ## render(HDC hdc)
//=============================================================
void MainGame::render(HDC hdc)
{


	/*SetDCBrushColor(hdc, RGB(100, 0, 0));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	int r = RND->getFromIntTo(200, 256), g = RND->getFromIntTo(100, 256), b = RND->getFromIntTo(100, 256);*/

	char str[10];
	sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(hdc, 10, 10, str, strlen(str));
	
}
