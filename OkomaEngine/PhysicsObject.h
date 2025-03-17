#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

// NEEDED INCLUDE(s)
#include "Collider.h"
#include "Rigidbody.h"

class PhysicsObject
{
private:

	Collider* m_Collider;
	Rigidbody* m_Rigidbody;

public:

	// Rectangle Collider Constructor
	PhysicsObject(const char* tag, OKTransform2<float>* transform, float mass, RigidbodyMovementType rigidbodyMovementType, bool IsCapsule = false, bool lockZRot = true);
	PhysicsObject(const char* tag, OKTransform2<float>* transform, float mass, float radius, RigidbodyMovementType rigidbodyMovementType);
	
	~PhysicsObject();


	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();



	// GETTER FUNCTION(s)
	inline Collider* GetCollider() const { return m_Collider; }
	inline Rigidbody* GetRigidbody() const { return m_Rigidbody; }


	// SETTER FUNCTION(s)

};

#endif
