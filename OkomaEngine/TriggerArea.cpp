#include "TriggerArea.h"

//TriggerArea::TriggerArea(std::string tag, OKTransform2<float>* transform, bool IsCapsule, bool lockZRot)
//	: ColliderEntity(transform, IsCapsule, lockZRot)
//{
//	m_ObjectList.clear();
//}
//
//TriggerArea::TriggerArea(std::string tag, OKTransform2<float>* transform, float radius)
//	: ColliderEntity(transform, radius)
//{
//	m_ObjectList.clear();
//}

TriggerArea::~TriggerArea()
{
	//if (!m_ObjectList.empty())
	//{
	//	std::set<GameObject*>::iterator itr;
	//	for (itr = m_ObjectList.begin(); itr != m_ObjectList.end(); ++itr)
	//	{
	//		delete *itr;
	//	}

	//	m_ObjectList.clear();
	//}
}

void TriggerArea::Update(const float deltaTime)
{

}

void TriggerArea::Draw()
{
	// ColliderEntity::Draw();
}

void TriggerArea::TriggerEntered(GameObject* object, void (*func)())
{
	//if (m_IsActive == false) { return; }
	//if (m_ColliderManifest.CheckCollisions(this, physicsObject->GetCollider()).m_HasCollision)
	//{
	//	if (m_ObjectList.find(physicsObject) == m_ObjectList.end())
	//	{
	//		m_HasEntered = true;
	//		m_HasStayed = false;
	//		m_HasExited = false;

	//		m_ObjectList.insert(physicsObject);
	//		if (func != nullptr) { func(); }
	//	}
	//}
}

void TriggerArea::TriggerStayed(GameObject* object, void (*func)())
{
	//if (m_IsActive == false) { return; }
	//// TriggerEntered(physicsObject);
	//if (m_ColliderManifest.CheckCollisions(this, physicsObject->GetCollider()).m_HasCollision)
	//{
	//	if (m_ObjectList.empty()) { return; }

	//	if (!m_ObjectList.count(physicsObject) == 0)
	//	{
	//		m_HasEntered = true;
	//		m_HasStayed = true;
	//		m_HasExited = false;
	//		if (func != nullptr) { func(); }
	//	}
	//}
}

void TriggerArea::TriggerExited(GameObject* physicsObject, void (*func)())
{
	//if (m_IsActive == false) { return; }
	//// TriggerEntered(physicsObject);
	//// TriggerStayed(physicsObject);

	//if (m_HasStayed == true && m_HasEntered == true && !m_ColliderManifest.CheckCollisions(this, physicsObject->GetCollider()).m_HasCollision)
	//{
	//	if (m_ObjectList.empty()) { return; }
	//
	//	m_HasEntered = false;
	//	m_HasStayed = false;
	//	m_HasExited = true;

	//	m_ObjectList.erase(physicsObject);
	//	if (func != nullptr) { func(); }
	//}
}
