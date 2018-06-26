#include "stdafx.h"
#include "GameNode.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT GameNode::init(void)
{
	SetTimer(_hWnd, 1, 10, NULL);			// 타이머 초기화
	KEYMANAGER->init();						// 키 매니저 초기화
	RND->init();
	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void GameNode::release(void)
{
	KillTimer(_hWnd, 1);
	// 키 매니저 싱글톤 해제
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	RND->release();
	RND->releaseSingleton();
	MYSOCKET->release();
	MYSOCKET->releaseSingleton();
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void GameNode::update(void)
{
	// 새로고침 (나중에 고성능 타이머를 만든 후에는 사용하지 않는다.)
	// 더블버퍼링 이후 사용하지 않는다(true => false)
	InvalidateRect(_hWnd, NULL, TRUE);		// ture == TRUE
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void GameNode::render(HDC hdc)
{

}

//=============================================================
//	## 메인프로시져 ##
//=============================================================
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;	

	static POINT pt = { 0, 0 };

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:	//esc 키를 누르면 화면종료
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
