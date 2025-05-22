#include "ColliderEntity.h"

ColliderEntity::ColliderEntity()
	: m_HasCollided(false), m_IsActivated(true), m_IsTrigger(false), m_ColliderType(ColliderType::COLLIDER_TYPE_NONE)
{
	m_ObjectList.clear();
}

ColliderEntity::~ColliderEntity()
{
	if (!m_ObjectList.empty())
	{
		std::unordered_set<GameObjectEntity*>::iterator itr;
		for (itr = m_ObjectList.begin(); itr != m_ObjectList.end(); ++itr)
		{
			delete *itr;
		}

		m_ObjectList.clear();
	}
}

void ColliderEntity::TriggerEntered(GameObjectEntity* gameObject, void(*func)())
{
	if (m_IsActivated == false) { return; }

	if (m_ObjectList.find(gameObject) == m_ObjectList.end())
	{
		m_HasEntered = true;
		m_HasStayed = false;
		m_HasExited = false;

		m_ObjectList.insert(gameObject);
		if (func != nullptr) { func(); }
	}
}

void ColliderEntity::TriggerStayed(GameObjectEntity* gameObject, void(*func)())
{
	if (m_IsActivated == false) { return; }
	if (m_ObjectList.empty()) { return; }

	if (!m_ObjectList.count(gameObject) == 0)
	{
		m_HasEntered = true;
		m_HasStayed = true;
		m_HasExited = false;
		if (func != nullptr) { func(); }
	}
}

void ColliderEntity::TriggerExited(GameObjectEntity* gameObject, void(*func)())
{
	if (m_IsActivated == false) { return; }

	if (m_HasStayed == true && m_HasEntered == true && !m_ObjectList.count(gameObject) == 0)
	{
		if (m_ObjectList.empty()) { return; }
	
		m_HasEntered = false;
		m_HasStayed = false;
		m_HasExited = true;

		m_ObjectList.erase(gameObject);
		if (func != nullptr) { func(); }
	}
}
