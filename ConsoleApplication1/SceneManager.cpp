#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

HRESULT SceneManager::init()
{
	return S_OK;
}

void SceneManager::release()
{
	// �������� ���
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
	// ���� ���� �����ϸ� �ش��ϴ� ���� ���� ������Ʈ
	if (currentScene) currentScene->update();
}

void SceneManager::render()
{
	if (currentScene) currentScene->render();
}

GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	//���� ������ �׳� �� ����
	if (!scene) return NULL;

	// ���� ������ �ʿ� ���
	mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::loadScene(string sceneName)
{
	MiSceneIter find = mSceneList.find(sceneName);

	// �� ã�Ҵٸ� E_FAIL
	if (find == mSceneList.end()) return E_FAIL;

	// �ٲٷ��� ���� ���� ���� ���ٸ� E_FAIL
	if (find->second == currentScene) return E_FAIL;

	currentScene->release();

	// �� �ֱ�ȭ �� ����
	if (SUCCEEDED(find->second->init()))
	{
		currentScene = find->second;
		return S_OK;
	}
	return E_FAIL;
}
