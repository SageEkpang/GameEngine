#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

// NEEDED INCLUDE(s)
#include "Collider.h"
#include "Rigidbody.h"
#include <string>

class PhysicsObject
{
private:

	std::string m_Tag;
	OKTransform2<float>* m_transform;
	Collider* m_Collider;
	Rigidbody* m_Rigidbody;

public:

	// Rectangle Collider Constructor
	PhysicsObject(std::string tag, std::unique_ptr<OKTransform2<float>>& transform, float mass, RigidbodyMovementType rigidbodyMovementType, bool IsCapsule = false, bool lockZRot = true);
	PhysicsObject(std::string tag, std::unique_ptr<OKTransform2<float>>& transform, float mass, float radius, RigidbodyMovementType rigidbodyMovementType);
	
	~PhysicsObject();


	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();

	// GETTER FUNCTION(s)
	inline std::string GetTag() const { return m_Tag; }
	inline OKTransform2<float> GetTransform() const { m_transform; }
	inline Collider* GetCollider() const { return m_Collider; }
	inline Rigidbody* GetRigidbody() const { return m_Rigidbody; }


	// SETTER FUNCTION(s)

};

#endif
