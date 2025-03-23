#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(const char* tag, OKTransform2<float>* transform, float mass, RigidbodyMovementType rigidbodyMovementType, bool IsCapsule, bool lockZRot)
{
	m_Collider = new Collider(tag, transform, IsCapsule, lockZRot);
	m_Rigidbody = new Rigidbody(tag, transform, mass, rigidbodyMovementType, IsCapsule, lockZRot);
}

PhysicsObject::PhysicsObject(const char* tag, OKTransform2<float>* transform, float mass, float radius, RigidbodyMovementType rigidbodyMovementType)
{
	m_Collider = new Collider(tag, transform, radius);
	m_Rigidbody = new Rigidbody(tag, transform, mass, radius, rigidbodyMovementType);
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

