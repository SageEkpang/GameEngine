#include "RenderManager.h"

RenderManager::SavedTextureMap RenderManager::m_SavedTextures = 
{ 
	
};

RenderManager::RenderManager()
{
	RenderManager::m_SavedTextures["Blank"] = LoadTexture("Resources/Images/Blank.png");
	RenderManager::m_SavedTextures["NULL"] = LoadTexture("Resources/Images/NULL.png");
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
