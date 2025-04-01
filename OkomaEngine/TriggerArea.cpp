#include "TriggerArea.h"
#include "PhysicsObject.h"

TriggerArea::TriggerArea(const char* tag, OKTransform2<float>* transform, bool IsCapsule, bool lockZRot)
	: Collider(tag, transform, IsCapsule, lockZRot)
{
	m_ColliderManifest = new ColliderManager();
	m_ObjectList.clear();
}

TriggerArea::TriggerArea(const char* tag, OKTransform2<float>* transform, float radius)
	: Collider(tag, transform, radius)
{
	m_ColliderManifest = new ColliderManager();
	m_ObjectList.clear();
}

TriggerArea::~TriggerArea()
{
	delete m_ColliderManifest;

	if (!m_ObjectList.empty())
	{
		std::set<PhysicsObject*>::iterator itr;
		for (itr = m_ObjectList.begin(); itr != m_ObjectList.end(); ++itr)
		{
			delete *itr;
		}

		m_ObjectList.clear();
	}
}

void TriggerArea::Draw()
{
	Collider::Draw();
}

void TriggerArea::TriggerEntered(PhysicsObject* physicsObject, void (*func)())
{
	if (m_IsActive == false) { return; }
	if (m_ColliderManifest->CheckCollisions(this, physicsObject->GetCollider()).m_HasCollision)
	{
		if (m_ObjectList.find(physicsObject) == m_ObjectList.end())
		{
			m_HasEntered = true;
			m_HasStayed = false;
			m_HasExited = false;

			m_ObjectList.insert(physicsObject);
			if (func != nullptr) { func(); }
		}
	}
}

void TriggerArea::TriggerStayed(PhysicsObject* physicsObject, void (*func)())
{
	if (m_IsActive == false) { return; }
	// TriggerEntered(physicsObject);
	if (m_ColliderManifest->CheckCollisions(this, physicsObject->GetCollider()).m_HasCollision)
	{
		if (m_ObjectList.empty()) { return; }

		if (!m_ObjectList.count(physicsObject) == 0)
		{
			m_HasEntered = true;
			m_HasStayed = true;
			m_HasExited = false;
			if (func != nullptr) { func(); }
		}
	}
}

void TriggerArea::TriggerExited(PhysicsObject* physicsObject, void (*func)())
{
	if (m_IsActive == false) { return; }
	// TriggerEntered(physicsObject);
	// TriggerStayed(physicsObject);

	if (m_HasStayed == true && m_HasEntered == true && !m_ColliderManifest->CheckCollisions(this, physicsObject->GetCollider()).m_HasCollision)
	{
		if (m_ObjectList.empty()) { return; }
	
		m_HasEntered = false;
		m_HasStayed = false;
		m_HasExited = true;

		m_ObjectList.erase(physicsObject);
		if (func != nullptr) { func(); }
	}
}
