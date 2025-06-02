#ifndef COLLISION_RESOLUTION_H
#define COLLISION_RESOLUTION_H

#include "OKVector2.h"
#include "OKTransform2.h"
#include "Rigidbody2DComponent.h"
#include "CollisionManifold.h"

class CollisionResolutionManager
{
public:

	// CLASS FUNCTION(s)
	CollisionResolutionManager();
	~CollisionResolutionManager();

	// BASE FUNCTION(s)
	void ResolveCollision(Rigidbody2DComponent* rigidbodyA, Rigidbody2DComponent* rigidbodyB, float coefRest, CollisionManifold collisionManifold);

private:

	OKVector2<float> CalculateSeperatingVelocity(Rigidbody2DComponent* rigidbodyA, Rigidbody2DComponent* rigidbodyB, OKVector2<float> contactNormal);
	void ResolveVelocity(Rigidbody2DComponent* rigidbodyA, Rigidbody2DComponent* rigidbodyB, float coefRest, OKVector2<float> collisionNormal);
	void ResolveInterpenetration(Rigidbody2DComponent* rigidbodyA, Rigidbody2DComponent* rigidbodyB, float penetration, OKVector2<float> collisionNormal);

};

#endif

