#include "GameObjectEntity.h"

GameObjectEntity::GameObjectEntity()
{
	// NOTE: Parent and Children Variable(s)
	m_Parent = nullptr;
	m_Children.clear();

	// NOTE: Transform Variable(s)
	m_Transform.position = OKVector2<float>(0.f, 0.f);
	m_Transform.scale = OKVector2<float>(1.f, 1.f);
	m_Transform.rotation = 0.f;
	m_Components.clear();
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

	m_Parent = nullptr;
	m_Children.clear();
	m_Components.clear();
}

void GameObjectEntity::Update(const float deltaTime)
{
	// NOTE: Transform / Parent	
	//if (m_Parent != nullptr)
	//{
	//	m_Transform.position += this->m_Parent->m_Transform.position;
	//	m_Transform.scale += this->m_Parent->m_Transform.scale;
	//	m_Transform.rotation += this->m_Parent->m_Transform.rotation;
	//}

	// NOTE: Update the Components
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
	// NOTE: Draw the Components
	if (!m_Components.empty())
	{
		for (auto& [ComponentType, Component] : m_Components)
		{
			Component->Draw();
		}
	}
}

GameObjectEntity* GameObjectEntity::GetChild(int index)
{
	// NOTE: Check if the index is bigger than the current amount of children in said list
	if (index + 1 > m_Children.size()) { return nullptr; }

	// NOTE: Set the iterator to the Beginning on the list
	std::list<GameObjectEntity*>::iterator itr = m_Children.begin();

	// NOTE: Iterate until we reach the index we want
	for (int i = 0; i < index; ++i) { ++itr; }

	// NOTE: Return the index that was found
	return *itr;
}

