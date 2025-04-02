#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(std::string tag, std::unique_ptr<OKTransform2<float>>& transform, float mass, RigidbodyMovementType rigidbodyMovementType, bool IsCapsule, bool lockZRot)
{
	m_Tag = tag;
	m_transform = transform.get();
	m_Collider = new Collider(m_transform, IsCapsule, lockZRot);
	m_Rigidbody = new Rigidbody(m_transform, mass, rigidbodyMovementType, IsCapsule, lockZRot);
}

PhysicsObject::PhysicsObject(std::string tag, std::unique_ptr<OKTransform2<float>>& transform, float mass, float radius, RigidbodyMovementType rigidbodyMovementType)
{
	m_Tag = tag;
	m_transform = transform.get();
	m_Collider = new Collider(m_transform, radius);
	m_Rigidbody = new Rigidbody(m_transform, mass, radius, rigidbodyMovementType);
}

PhysicsObject::~PhysicsObject()
{
	delete m_Collider;
	delete m_Rigidbody;
}

void PhysicsObject::Update(const float deltaTime)
{
	m_Collider->Update(deltaTime);
	m_Rigidbody->Update(deltaTime);
}

void PhysicsObject::Draw()
{
	m_Rigidbody->Draw();
	// m_Collider->Draw();
}

