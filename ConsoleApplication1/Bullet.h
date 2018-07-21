#pragma once

class Bullet
{
private:
	RECT rc;
	float x, y;
	float oldX, oldY;
	float dirX, dirY;
	int dir;
	float angle;
	float speed;
	float gravity;
	float radius;
	float power;
	bool isFire;

	int *curTurn;

	int count, curFrameX, curFrameY;

	Image * ground;

public:
	Bullet() {}
	~Bullet() {}

	void setCurTurn(int * c) { curTurn = c;}
	//ÃÑ¾Ë¹ß»ç
	void fire(float x, float y, float angle, float speed, int *curTurn);
	//ÃÑ¾Ë¹«ºê
	void move();
	void collision();
	
	RECT getHitRange() { return RectMakeCenter(x, y, 100, 50); }

	bool getIsFire() { return isFire; }
	float getPower() { return power; }
	float getGravity() { return gravity; }
	float getX() { return x; }
	float getY() { return y; }
	float getSpeed() const { return speed; }
	float getAngle() const { return angle; }
	int getDir() { return dir; }

	void setIsFire(bool _isFire) { isFire = _isFire; }
	void setPower(float _power) { power = _power; }
	void setGravity(float _gravity) { gravity = _gravity; }
	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
	void setSpeed(float _speed) { speed = _speed; }
	void setAngle(float _angle) { angle = _angle; }
};

