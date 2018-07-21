#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

HRESULT SceneManager::init()
{
	return S_OK;
}

void SceneManager::release()
{
	// 정상적인 방법
	MiSceneIter iter = mSceneList.begin();
	for (; iter != mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = mSceneList.erase(iter);
		}
		else
		{
			iter++;
		}

	}
	mSceneList.clear();

	/*for each(auto scene in mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}*/

}

void SceneManager::update()
{
	// 현재 씬이 존재하면 해당하는 현재 씬을 업데이트
	if (currentScene) currentScene->update();
}

void SceneManager::render()
{
	if (currentScene) currentScene->render();
}

GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	//씬이 없으면 그냥 널 리턴
	if (!scene) return NULL;

	// 씬이 있으면 맵에 담기
	mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::loadScene(string sceneName)
{
	MiSceneIter find = mSceneList.find(sceneName);

	// 못 찾았다면 E_FAIL
	if (find == mSceneList.end()) return E_FAIL;

	// 바꾸려는 씬과 현재 씬이 같다면 E_FAIL
	if (find->second == currentScene) return E_FAIL;

	currentScene->release();

	// 씬 최기화 후 변경
	if (SUCCEEDED(find->second->init()))
	{
		currentScene = find->second;
		return S_OK;
	}
	return E_FAIL;
}
