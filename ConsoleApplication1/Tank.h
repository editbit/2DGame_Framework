#pragma once
#include "GameNode.h"
#include "Bullet.h"

#define MAX_SHAPE 1
#define MAX_BULLET 1


class Tank :
	public GameNode
{
	Image * map;
	Image * shape[MAX_SHAPE];

	int * curTurn;

	float x, y;
	float oldX, oldY;
	float dirX, dirY;
	float speed;
	float angle;
	float canonAngle;
	float shootingPower;
	int state;
	int dir;
	int probeY;

	RECT collisionBox;

	Bullet * bullet;
	Image * bulletImage;

public:
	virtual HRESULT init();	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	virtual void release();
	virtual void update();
	virtual void render();

	void inputProcess();
	void fireBullet();
	void collision();

	int getProbeY() { return probeY; }

	Bullet * getBullet() { return bullet; }

	void setCurTurn(int * c) { curTurn = c; }

	float *getXPtr() { return &x; }
	float *getYPtr() { return &y; }
	int getDir() { return dir; }
	int getState() { return state; }
	float getShootingPower() { return shootingPower; }
	float getX() { return x; }
	float getY() { return y; }
	float getSpeed() const { return speed; }
	float getAngle() const { return angle; }
	float getCanonAngle() const { return canonAngle; }

	void setShootingPower(float _power) { shootingPower = _power; }
	void setDir(int _dir) { dir = _dir; }
	void setState(int _state) { state = _state; }
	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
	void setSpeed(float _speed) { speed = _speed; }
	void setAngle(float _angle) { angle = _angle; }
	void setCanonAngle(float _angle) { canonAngle = _angle; }

	int convertDir(float _angle)
	{
		if (_angle >= 2 * 3.141592f)
			_angle -= 2 * 3.141592f;

		if (3.141592f / 2 <= _angle && _angle < 3 * 3.141592f / 2)
			return LEFT;
		else
			return RIGHT;
	}

	Tank() {}
	~Tank() {}
};

