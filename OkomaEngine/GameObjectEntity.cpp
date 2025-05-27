#include "GameObjectEntity.h"

GameObjectEntity::GameObjectEntity()
{
	m_Components.clear();
}

GameObjectEntity::~GameObjectEntity()
{
	//std::unordered_map<std::type_index, ComponentEntity*>::iterator itr;

	//for (itr = m_Components.begin(); itr != m_Components.end(); ++itr)
	//{
	//	if ((*itr).second != nullptr)
	//	{
	//		delete (*itr).second;
	//	}
	//}

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


