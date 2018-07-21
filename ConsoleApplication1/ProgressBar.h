#pragma once
#include "GameNode.h"
class ProgressBar :
	public GameNode
{
private:
	RECT rcProgress;	// 체력바 렉트
	int x, y;			// 체력바 위치좌표
	float width;		// 체력바 가로길이
	float height;		// 체력바 세로길이

	Image *progressBarFront;	// 체력바 앞 이미지
	Image *progressBarBack;		// 체력바 뒤 이미지


public:
	// 체력바 초기화(앞 이미지 키, 뒤 이미지 키, x, y, width, height)
	virtual HRESULT init(const char * frontImageKey, const char * backImageKey, int _x, int _y, int _width, int _height);
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// 체력바 게이지 세팅
	void setGauge(float _currentHp, float _maxHp);

	// 체력바 위치 좌표 세팅
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	void setInfo(int _x, int _y, float _currentHp, float _maxHp);

	// 체력바 렉트 가져오기
	RECT getRect() { return rcProgress; }

	ProgressBar() {}
	~ProgressBar() {}
};

