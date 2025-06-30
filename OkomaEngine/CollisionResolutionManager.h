#ifndef COLLISION_RESOLUTION_H
#define COLLISION_RESOLUTION_H

#include "OKVector2.h"
#include "OKTransform2.h"
#include "Rigidbody2DComponent.h"
#include "CollisionManifold.h"

#include "GameObjectEntity.h"

class CollisionResolutionManager
{
public:

	// CLASS FUNCTION(s)
	CollisionResolutionManager();
	~CollisionResolutionManager();

	// BASE FUNCTION(s)
	void ResolveCollision(GameObjectEntity* rigidbodyA, GameObjectEntity* rigidbodyB, float coefRest, CollisionManifold collisionManifold);

private:

	OKVector2<float> CalculateSeperatingVelocity(GameObjectEntity* rigidbodyA, GameObjectEntity* rigidbodyB);
};

#endif

