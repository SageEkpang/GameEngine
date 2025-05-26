#include "ColliderEntity.h"

ColliderEntity::ColliderEntity()
	: m_HasCollided(false), m_IsActivated(true), m_IsTrigger(false)
{
	m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_NONE;
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

	m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_NONE;
}

void ColliderEntity::TriggerQuery(GameObjectEntity* gameObject)
{
	if (m_IsActivated == false) { return; }

	// NOTE: Game Object has entered trigger
	if (m_ObjectList.find(gameObject) == m_ObjectList.end())
	{
		m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_ENTERED;
		m_ObjectList.insert(gameObject);
		return;
	}

	// NOTE: Check if the Object List is there
	if (m_ObjectList.empty()) { return; }
	
	// NOTE: Game Object has stayed in the trigger
	//if (m_ObjectList.find(gameObject) != m_ObjectList.end() && m_TriggerState == TriggerAreaState::TRIGGER_AREA_STATE_ENTERED)
	//{
	//	m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_STAYED;
	//	return;
	//}

	// Make sure to add the has collided function
	// NOTE: Game Object has exited the trigger
	if ((m_TriggerState == TriggerAreaState::TRIGGER_AREA_STATE_ENTERED || m_TriggerState == TriggerAreaState::TRIGGER_AREA_STATE_STAYED) && m_ObjectList.count(gameObject) != 0)
	{
		m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_EXITED;
		m_ObjectList.erase(gameObject);
		return;
	}
}

void ColliderEntity::TriggerEnteredExecute(void(*func)())
{
	m_TriggerEnteredLambda = func;
}

void ColliderEntity::TriggerStayedExecute(void(*func)())
{
	m_TriggerStayedLambda = func;
}

void ColliderEntity::TriggerExitedExecute(void(*func)())
{
	m_TriggerExitedLambda = func;
}

void ColliderEntity::TriggerQueryExecute()
{
	switch (m_TriggerState)
	{
		case TriggerAreaState::TRIGGER_AREA_STATE_ENTERED: if (m_TriggerEnteredLambda != nullptr) { m_TriggerEnteredLambda(); } break;
		case TriggerAreaState::TRIGGER_AREA_STATE_STAYED: if (m_TriggerStayedLambda != nullptr) { m_TriggerStayedLambda(); } break;
		case TriggerAreaState::TRIGGER_AREA_STATE_EXITED: if (m_TriggerExitedLambda != nullptr) { m_TriggerExitedLambda(); } break;
		case TriggerAreaState::TRIGGER_AREA_STATE_NONE: break;
		default: break;
	}
}

void ColliderEntity::TriggerEntered(GameObjectEntity* gameObject, void(*func)())
{


	
}

void ColliderEntity::TriggerStayed(GameObjectEntity* gameObject, void(*func)())
{
	
}

void ColliderEntity::TriggerExited(GameObjectEntity* gameObject, void(*func)())
{
	
}
