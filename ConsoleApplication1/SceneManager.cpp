#include "stdafx.h"
#include "SceneManager.h"

HRESULT SceneManager::init()
{
	return S_OK;
}

void SceneManager::release()
{
	this->deleteAll();
}

GameNode * SceneManager::addScene(string strKey, GameNode * scene)
{
	GameNode * s = findScene(strKey);

	if (s) return s;

	if (!scene)
	{
		return NULL;
	}

	_mSceneList.insert(make_pair(strKey, scene));

	return scene;
}


GameNode * SceneManager::setCurrentScene(string strkey)
{
	mapSceneIter key = _mSceneList.find(strkey);

	if (key != _mSceneList.end())
	{
		currentScene = key->second;
		return key->second;
	}

	return NULL;
}

GameNode * SceneManager::findScene(string strKey)
{
	mapSceneIter key = _mSceneList.find(strKey);

	if (key != _mSceneList.end())
	{
		return key->second;
	}

	return NULL;
}

BOOL SceneManager::deleteScene(string strKey)
{
	mapSceneIter key = _mSceneList.find(strKey);

	if (key != _mSceneList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);

		_mSceneList.erase(key);

		return TRUE;
	}

	return FALSE;
}

bool SceneManager::deleteAll()
{
	mapSceneIter iter = _mSceneList.begin();

	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);

			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mSceneList.clear();

	return TRUE;
}
