#pragma once
#include "SingletonBase.h"

class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, GameNode *> MSceneList;
	typedef map<string, GameNode *>::iterator MiSceneIter;

private:
	MSceneList mSceneList;
	GameNode* currentScene;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	// �� �߰�
	GameNode* addScene(string sceneName, GameNode * scene);
	// �� ����
	HRESULT loadScene(string sceneName);

	SceneManager() : currentScene(0) {}
	~SceneManager() {}
};

