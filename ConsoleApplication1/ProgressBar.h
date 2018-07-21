#pragma once
#include "GameNode.h"
class ProgressBar :
	public GameNode
{
private:
	RECT rcProgress;	// ü�¹� ��Ʈ
	int x, y;			// ü�¹� ��ġ��ǥ
	float width;		// ü�¹� ���α���
	float height;		// ü�¹� ���α���

	Image *progressBarFront;	// ü�¹� �� �̹���
	Image *progressBarBack;		// ü�¹� �� �̹���


public:
	// ü�¹� �ʱ�ȭ(�� �̹��� Ű, �� �̹��� Ű, x, y, width, height)
	virtual HRESULT init(const char * frontImageKey, const char * backImageKey, int _x, int _y, int _width, int _height);
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// ü�¹� ������ ����
	void setGauge(float _currentHp, float _maxHp);

	// ü�¹� ��ġ ��ǥ ����
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	void setInfo(int _x, int _y, float _currentHp, float _maxHp);

	// ü�¹� ��Ʈ ��������
	RECT getRect() { return rcProgress; }

	ProgressBar() {}
	~ProgressBar() {}
};

