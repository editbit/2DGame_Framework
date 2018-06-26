#pragma once
class GameNode
{
public:
	virtual HRESULT init(void);	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	// 메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {} // 소멸자에 virtual 키워드를 붙이는 이유 면접시 단골질문
};

