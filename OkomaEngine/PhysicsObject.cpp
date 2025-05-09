#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(std::string tag, OKTransform2<float> transform, float mass, RigidbodyMovementType rigidbodyMovementType, bool IsCapsule, bool lockZRot)
{
	m_Tag = tag;
	m_transform = transform;
	m_Collider = Collider(&m_transform, IsCapsule, lockZRot);
	m_Rigidbody = Rigidbody(&m_transform, mass, rigidbodyMovementType, IsCapsule, lockZRot);
}

PhysicsObject::PhysicsObject(std::string tag, OKTransform2<float> transform, float mass, float radius, RigidbodyMovementType rigidbodyMovementType)
{
	m_Tag = tag;
	m_transform = transform;
	m_Collider = Collider(&m_transform, radius);
	m_Rigidbody = Rigidbody(&m_transform, mass, radius, rigidbodyMovementType);
}

PhysicsObject::~PhysicsObject()
{

}

void PhysicsObject::Update(const float deltaTime)
{
	m_Collider.Update(deltaTime);
	m_Rigidbody.Update(deltaTime);
}

void PhysicsObject::Draw()
{
	m_Rigidbody.Draw();
	// m_Collider->Draw();
}

