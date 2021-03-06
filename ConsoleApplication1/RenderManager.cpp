#include "stdafx.h"
#include "RenderManager.h"
#include "GameNode.h"

HRESULT RenderManager::init()
{
	return S_OK;
}

void RenderManager::release()
{
	renderList.clear();
}

void RenderManager::render(HDC hdc)
{
	multimap<float, GameNode *>::iterator iter;

	if (!renderList.empty())
	{
		for (iter = renderList.begin(); iter != renderList.end(); ++iter)
		{
			iter->second->render();
		}
	}

	renderList.clear();
}

void RenderManager::addRender(GameNode * effectName, float z)
{
	renderList.insert(make_pair(z, effectName));
}
