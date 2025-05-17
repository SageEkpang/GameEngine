#include "GameObjectEntity.h"

GameObjectEntity::GameObjectEntity()
{
	m_Components.clear();
}

GameObjectEntity::~GameObjectEntity()
{
	std::vector<ComponentEntity*>::iterator itr;

	for (itr = m_Components.begin(); itr != m_Components.end(); ++itr)
	{
		delete* itr;
		*itr = nullptr;
	}

	m_Components.clear();
}

void GameObjectEntity::Update(const float deltaTime)
{








}

void GameObjectEntity::Draw()
{





}
