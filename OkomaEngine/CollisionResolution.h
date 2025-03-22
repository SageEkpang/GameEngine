#ifndef COLLISION_RESOLUTION_H
#define COLLISION_RESOLUTION_H

#include "OKVector2.h"
#include "OKTransform2.h"
#include "Rigidbody.h"
#include "PhysicsObject.h"

class CollisionResolution
{
public:

	// CLASS FUNCTION(s)
	CollisionResolution();
	~CollisionResolution();

	// BASE FUNCTION(s)
	void ResolveCollision(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, float CoefRest, float penetration, OKVector2<float> collisionNormal, float deltaTime);
	void ResolveCollisionsWithRotation(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, float CoefRest, float penetration, OKVector2<float> collisionNormal, float deltaTime);

private:

	void ResolveVelocity(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, float CoefRest, float deltaTime, OKVector2<float> collisionNormal);
	void ResolveInterpenetration(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, float penetration, OKVector2<float> collisionNormal);
	OKVector2<float> CalculateSeperatingVelocity(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, OKVector2<float> contactNormal) const;

};

#endif

