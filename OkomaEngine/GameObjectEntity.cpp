#include "GameObjectEntity.h"

GameObjectEntity::GameObjectEntity()
{
	m_Components.clear();
	// m_Components.reserve(MAX_COMPONENTS);
}

GameObjectEntity::~GameObjectEntity()
{
	// std::unordered_set<std::unique_ptr<ComponentEntity*>>::iterator itr;

	//for (itr = m_Components.begin(); itr != m_Components.end(); ++itr)
	//{
	//	if ((*itr).get() != nullptr)
	//	{
	//		delete (*itr).get();

	//	}
	//}

	// m_Components.clear();
}

void GameObjectEntity::Update(const float deltaTime)
{
	//if (!m_Components.empty())
	//{
	//	for (auto& [ComponentType, Component] : m_Components)
	//	{
	//		Component.get()->Update(deltaTime);
	//	}
	//}
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


