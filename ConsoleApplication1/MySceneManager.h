#pragma once
#include "SingletonBase.h"
class GameNode;

class MySceneManager : public SingletonBase<MySceneManager>
{
	typedef map<string, GameNode*> mapSceneList;				// 맵으로 만든 이미지 목록
	typedef map<string, GameNode*>::iterator mapSceneIter;		// 맵으로 만든 이미지목록의 반복자

private:
	GameNode * currentScene;
	mapSceneList _mSceneList;		// 실제 이미지 클래스를 담을 STL 맵

public:
	HRESULT init();
	void release();

	GameNode* addScene(string strKey, GameNode* scene);

	GameNode* getCurrentScene() { return currentScene; }
	void setCurrentScene(GameNode * curScene) { currentScene = curScene; }
	GameNode* setCurrentScene(string strkey);

	GameNode* findScene(string strKey);
	BOOL deleteScene(string strKey);
	bool deleteAll();

	MySceneManager() {}
	~MySceneManager() {}
};

