#pragma once
#include "SingletonBase.h"

class SceneManager : public SingletonBase<SceneManager>
{
	typedef map<string, GameNode*> mapSceneList;				// ������ ���� �̹��� ���
	typedef map<string, GameNode*>::iterator mapSceneIter;		// ������ ���� �̹�������� �ݺ���

private:
	GameNode * currentScene;
	mapSceneList _mSceneList;		// ���� �̹��� Ŭ������ ���� STL ��

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

	SceneManager() {}
	~SceneManager() {}
};

