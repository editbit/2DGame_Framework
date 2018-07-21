#pragma once
//==============================================================
//	## commonMacroFunction ## (�ʿ��� �κ��� ���� ���� �߰��� ��)
//==============================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

// �� �׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

// RECT �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

// Rectangle �Լ� �̿��ؼ� �׸���
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// Rectangle �Լ� �̿��ؼ� ������ �߽����� �׸���
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

// Ellipse �Լ� �̿��ؼ� �� �׸���
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// Ellipse �Լ� �̿��ؼ� ������ �߽����� �׸���
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void Rectangle(HDC hdc, const RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline float getDistance(float startX, float startY, float endX, float endY)
{
	return sqrtf((endX - startX)*(endX - startX) + (endY - startY)*(endY - startY));
}

inline float getDistance(float startX, float endX)
{
	if (startX - endX > 0)
		return startX - endX;
	else
		return endX - startX;
}

inline float getAnglef(float startX, float startY, float endX, float endY)
{
	//float _angle =  atan2(startY - endY, endX - startX);
	float _angle = atan2(startY - endY, endX - startX);

	if (startX == endX && startY == endY)
		return 0;

	if (_angle < 0)
	{
		_angle += 2 * 3.141592f;
	}

	return _angle;
}

inline void Ellipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

