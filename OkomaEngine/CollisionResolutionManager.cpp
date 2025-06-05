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
	ResolveInterpenetration(rigidbodyA, rigidbodyB, collisionManifold.m_PenetrationDepth, collisionManifold.m_CollisionNormal);
	ResolveVelocity(rigidbodyA, rigidbodyB, coefRest, collisionManifold.m_CollisionNormal);
}

void CollisionResolutionManager::ResolveVelocity(GameObjectEntity* rigidbodyA, GameObjectEntity* rigidbodyB, float coefRest, OKVector2<float> collisionNormal)
{
	OKVector2<float> t_SeperatingVelocity = CalculateSeperatingVelocity(rigidbodyA, rigidbodyB, collisionNormal);

	// If there is no need for seperating velocity, then we do not need to run the function
	if (t_SeperatingVelocity > OKVector2<float>(0, 0)) { return; }

	OKVector2<float> t_NewSeperatingVelocity = t_SeperatingVelocity * coefRest * -1;

	OKVector2<float> t_AccumulatedVelocity = rigidbodyA->GetComponent<Rigidbody2DComponent>()->m_Acceleration;
	t_AccumulatedVelocity -= rigidbodyB->GetComponent<Rigidbody2DComponent>()->m_Acceleration;

	OKVector2<float> t_AccumulatedSeperatingVelocity = t_AccumulatedVelocity * collisionNormal; // Delta time may not need to be here

	if (t_AccumulatedSeperatingVelocity < OKVector2<float>(0, 0))
	{
		t_NewSeperatingVelocity += coefRest * t_AccumulatedSeperatingVelocity;

		if (t_NewSeperatingVelocity < OKVector2<float>(0, 0))
		{
			t_NewSeperatingVelocity = 0;
		}
	}

	OKVector2<float> t_DeltaVelocity = t_NewSeperatingVelocity - t_SeperatingVelocity;
	float t_TotalInverseMass = rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetInverseMass();
	t_TotalInverseMass += rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetInverseMass();

	if (t_TotalInverseMass == 0) { return; }

	OKVector2<float> t_Impulse = t_DeltaVelocity / t_TotalInverseMass;
	OKVector2<float> t_ImpulsePerMass = collisionNormal * t_Impulse;

	if (rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetRigidbodyMovementType() == RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
	{
		rigidbodyA->GetComponent<Rigidbody2DComponent>()->ApplyImpulse(t_ImpulsePerMass * rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetInverseMass());
	}

	if (rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetRigidbodyMovementType() == RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
	{
		rigidbodyB->GetComponent<Rigidbody2DComponent>()->ApplyImpulse(t_ImpulsePerMass * -rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetInverseMass());
	}
}

// NOTE: This Collision Function can only be for collisions that have no rotations to them
void CollisionResolutionManager::ResolveInterpenetration(GameObjectEntity* rigidbodyA, GameObjectEntity* rigidbodyB, float penetration, OKVector2<float> collisionNormal)
{
	// No Penetration, so no need for it
	if (penetration <= 0) { return; }

	float t_TotalInverseMass = rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetInverseMass() + rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetInverseMass();

	// If infinite mass, return (more so for stationary / static objects)
	if (t_TotalInverseMass == 0) { return; }

	// Find by how much to move the entity
	OKVector2<float> t_MovePerMass = collisionNormal * (penetration / t_TotalInverseMass);
	OKVector2<float> t_MoveOutA = t_MovePerMass * rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetInverseMass();
	OKVector2<float> t_MoveOutB = t_MovePerMass * -rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetInverseMass();

	// NOTE:
	if (rigidbodyA->GetComponent<Rigidbody2DComponent>()->GetRigidbodyMovementType() == RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
	{
		rigidbodyA->m_Transform.position += t_MoveOutA;
	}

	if (rigidbodyB->GetComponent<Rigidbody2DComponent>()->GetRigidbodyMovementType() == RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
	{
		rigidbodyB->m_Transform.position += t_MoveOutB;
	}
}

OKVector2<float> CollisionResolutionManager::CalculateSeperatingVelocity(GameObjectEntity* rigidbodyA, GameObjectEntity* rigidbodyB, OKVector2<float> contactNormal)
{
	OKVector2<float> t_RelativeVelocity = rigidbodyA->GetComponent<Rigidbody2DComponent>()->m_Velocity;
	t_RelativeVelocity -= rigidbodyB->GetComponent<Rigidbody2DComponent>()->m_Velocity;
	return t_RelativeVelocity * contactNormal;
}
