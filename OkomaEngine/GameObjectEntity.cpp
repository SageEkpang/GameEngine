#include "GameObjectEntity.h"

GameObjectEntity::GameObjectEntity()
{
	// m_Transform.position = OKVector2<float>(0.f, 0.f);
	m_Transform.scale = OKVector2<float>(1.f, 1.f);
	//m_Transform.rotation = 0.f;
	//m_Components.clear();
}

GameObjectEntity::~GameObjectEntity()
{
	if (!m_Components.empty())
	{
		for (auto& [ComponentType, Component] : m_Components)
		{
			if (Component == nullptr) { continue; }

			delete Component;
			Component = nullptr;
		}
	}

	 m_Components.clear();
}

void GameObjectEntity::Update(const float deltaTime)
{
	if (!m_Components.empty())
	{
		for (auto& [ComponentType, Component] : m_Components)
		{
			Component->Update(deltaTime);
		}
	}
}

void GameObjectEntity::Draw()
{
	//if (!m_Components.empty())
	//{
	//	for (auto& c : m_Components)
	//	{
	//		// c->Draw();
	//	}
	//}
}


