#pragma once
#include "SingletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:
	int maxWidth, maxHeight;
	int x, y;
	int sX, sY, shakingPower;
	int count;

public:
	void setRange(int width, int height) { maxWidth = width; maxHeight = height; }
	void setPosition(int _x, int _y) { x = _x; y = _y; }
	void setShakeInfo(int shakingTime, int _shakingPower) { count = shakingTime; shakingPower = _shakingPower; }
	void videoShooting(int _x, int _y);
	void videoShooting();

	int getMaxWidth() { return maxWidth; }
	int getMaxHeight() { return maxHeight; }
	int getX() { return x; }
	int getY() { return y; }
	int getSX() { return sX; }
	int getSY() { return sY; }


	HRESULT init();
	void release();

	Camera() {}
	~Camera() {}
};

