#pragma once
#include "SingletonBase.h"
class SaveData : public SingletonBase<SaveData>
{
private:
	int hp;

public:
	HRESULT init();
	void release();

	int getHp() { return hp; }
	void setHp(int _hp) { hp = _hp; }

	SaveData() {}
	~SaveData() {}
};

