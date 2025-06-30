#include "CollisionResolutionManager.h"

CollisionResolutionManager::CollisionResolutionManager()
{

}

CollisionResolutionManager::~CollisionResolutionManager()
{

}

void CollisionResolutionManager::ResolveCollision(GameObjectEntity* rigidbodyA, GameObjectEntity* rigidbodyB, float coefRest, CollisionManifold collisionManifold)
{
	// NOTE: Move the object out of the other object first and then apply the force to the object
	OKVector2<float> t_SeperatingVelocity = CalculateSeperatingVelocity(rigidbodyA, rigidbodyB);

	// If there is no need for seperating velocity, then we do not need to run the function
	if (t_SeperatingVelocity > OKVector2<float>(0, 0)) { return; }

	float t_TotalInverseMass = rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetInverseMass();
	t_TotalInverseMass += rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetInverseMass();

	if (t_TotalInverseMass == 0) { return; }

	// Find by how much to move the entity
	OKVector2<float> t_MovePerMass = collisionManifold.m_CollisionNormal * (collisionManifold.m_PenetrationDepth / t_TotalInverseMass);
	OKVector2<float> t_MoveOutA = t_MovePerMass * rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetInverseMass();
	OKVector2<float> t_MoveOutB = -t_MovePerMass * rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetInverseMass();

	float InverseA = rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetInverseMass();
	float InverseB = rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetInverseMass();

	// NOTE: See if the objects are moving into each other
	float t_VelocityAlongNormal = t_SeperatingVelocity.x * collisionManifold.m_CollisionNormal.x + t_SeperatingVelocity.y * collisionManifold.m_CollisionNormal.y;

	// NOTE: Calculate the bounce of the objects based off their inverse mass and normal
	float impMag = (-(1 + coefRest) * t_VelocityAlongNormal) / (InverseA + InverseB);

	// NOTE: Velocity Solving
	if (rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetRigidbodyMovementType() == RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
	{
		// NOTE: Seperate the 2 objects away from each other if they are still interpentrating
		if (collisionManifold.m_PenetrationDepth != 0) { rigidbodyA->m_Transform.position += t_MoveOutA; }

		// NOTE: If velocity along the normal is greater than 0, we want to resolve the collision
		if (t_VelocityAlongNormal > 0) { return; }
		float impulseX = impMag * collisionManifold.m_CollisionNormal.x;
		float impulseY = impMag * collisionManifold.m_CollisionNormal.y;

		// NOTE: Apply calculation to the new objects
		rigidbodyA->GetComponent<Rigidbody2DComponent>()->ApplyImpulseX(impulseX / rigidbodyA->GetComponent<Rigidbody2DComponent>()->m_Mass);
		rigidbodyA->GetComponent<Rigidbody2DComponent>()->ApplyImpulseY(impulseY / rigidbodyA->GetComponent<Rigidbody2DComponent>()->m_Mass);
	}

	if (rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetRigidbodyMovementType() == RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
	{
		if (collisionManifold.m_PenetrationDepth != 0) { rigidbodyB->m_Transform.position += t_MoveOutB; }
		
		// NOTE: If velocity along the normal is greater than 0, we want to resolve the collision
		if (t_VelocityAlongNormal > 0) { return; }
		float impulseX = impMag * collisionManifold.m_CollisionNormal.x;
		float impulseY = impMag * collisionManifold.m_CollisionNormal.y;

		// NOTE: Apply calculation to the new objects
		rigidbodyB->GetComponent<Rigidbody2DComponent>()->ApplyImpulseX(-1 * impulseX / rigidbodyB->GetComponent<Rigidbody2DComponent>()->m_Mass);
		rigidbodyB->GetComponent<Rigidbody2DComponent>()->ApplyImpulseY(-1 * impulseY / rigidbodyB->GetComponent<Rigidbody2DComponent>()->m_Mass);
	}
}

OKVector2<float> CollisionResolutionManager::CalculateSeperatingVelocity(GameObjectEntity* rigidbodyA, GameObjectEntity* rigidbodyB)
{
	OKVector2<float> t_RelativeVelocity = rigidbodyA->GetComponent<Rigidbody2DComponent>()->m_Velocity;
	t_RelativeVelocity -= rigidbodyB->GetComponent<Rigidbody2DComponent>()->m_Velocity;
	return t_RelativeVelocity;
}
