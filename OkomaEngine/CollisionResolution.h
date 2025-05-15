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
	void ResolveCollision(Rigidbody2DComponent* rigidbodyA, Rigidbody2DComponent* rigidbodyB, float CoefRest, float penetration, OKVector2<float> collisionNormal, float deltaTime);
	// void ResolveCollisionsWithRotation(Rigidbody2DComponent* rigidbodyA, Rigidbody2DComponent* rigidbodyB, float CoefRest, float penetration, OKVector2<float> collisionNormal, float deltaTime);

private:

	OKVector2<float> CalculateSeperatingVelocity(Rigidbody2DComponent* rigidbodyA, Rigidbody2DComponent* rigidbodyB, OKVector2<float> contactNormal);
	void ResolveVelocity(Rigidbody2DComponent* rigidbodyA, Rigidbody2DComponent* rigidbodyB, float CoefRest, float deltaTime, OKVector2<float> collisionNormal);
	void ResolveInterpenetration(Rigidbody2DComponent* rigidbodyA, Rigidbody2DComponent* rigidbodyB, float penetration, OKVector2<float> collisionNormal);

};

#endif

