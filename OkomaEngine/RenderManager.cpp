#include "RenderManager.h"

RenderManager::RenderManager()
{
	m_RenderObjects.clear();
}

RenderManager::~RenderManager()
{
	m_RenderObjects.clear();
}

void RenderManager::Update(const float deltaTime)
{
	

}

void RenderManager::Draw()
{
	if (!m_RenderObjects.empty())
	{
		for (auto& v : m_RenderObjects)
		{
			if (v->HasComponent<RenderComponent>())
			{
				v->Draw();
			}
		}
	}
}
