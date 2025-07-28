#include "CollisionResolutionManager.h"

CollisionResolutionManager::CollisionResolutionManager()
{

}

CollisionResolutionManager::~CollisionResolutionManager()
{

}

void CollisionResolutionManager::ResolveCollision(GameObjectEntity* gameObjectA, GameObjectEntity* gameObjectB, float coefRest, CollisionManifold collisionManifold)
{
	// NOTE: Move the object out of the other object first and then apply the force to the object
	OKVector2<float> t_SeperatingVelocity = CalculateSeperatingVelocity(gameObjectA, gameObjectB);

	// If there is no need for seperating velocity, then we do not need to run the function
	if (t_SeperatingVelocity > OKVector2<float>(0, 0)) { return; }

	// NOTE: If the rigidbody 2D component is not on the object and they are colliding, treat it as if infinite mass is applied
	float m_RigidbodyObjectAMass = FLT_MAX;
	float m_RigidbodyObjectAInverseMass = 1.f / FLT_MAX;

	float m_RigidbodyObjectBMass = FLT_MAX;
	float m_RigidbodyObjectBInverseMass = 1.f / FLT_MAX;

	if (gameObjectA->HasComponent<Rigidbody2DComponent>())
	{
		m_RigidbodyObjectAMass = gameObjectA->GetComponent<Rigidbody2DComponent>().m_Mass;
		m_RigidbodyObjectAInverseMass = gameObjectA->GetComponent<Rigidbody2DComponent>().GetInverseMass();

		if (gameObjectA->GetComponent<Rigidbody2DComponent>().m_RigidbodyMovementType == RIGIDBODY_MOVEMENT_TYPE_STATIC)
		{
			m_RigidbodyObjectAMass = FLT_MAX;
			m_RigidbodyObjectAInverseMass = 1.f / FLT_MAX;
		}
	}

	if (gameObjectB->HasComponent<Rigidbody2DComponent>())
	{
		m_RigidbodyObjectBMass = gameObjectB->GetComponent<Rigidbody2DComponent>().m_Mass;
		m_RigidbodyObjectBInverseMass = gameObjectB->GetComponent<Rigidbody2DComponent>().GetInverseMass();

		if (gameObjectB->GetComponent<Rigidbody2DComponent>().m_RigidbodyMovementType == RIGIDBODY_MOVEMENT_TYPE_STATIC)
		{
			m_RigidbodyObjectBMass = FLT_MAX;
			m_RigidbodyObjectBInverseMass = 1.f / FLT_MAX;
		}
	}

	// NOTE: Resolution Calculations Starting
	float t_TotalInverseMass = m_RigidbodyObjectAInverseMass;
	t_TotalInverseMass += m_RigidbodyObjectBInverseMass;

	if (t_TotalInverseMass == 0) { return; }

	// Find by how much to move the entity
	OKVector2<float> t_MovePerMass = collisionManifold.m_CollisionNormal * (collisionManifold.m_PenetrationDepth / t_TotalInverseMass);
	OKVector2<float> t_MoveOutA = t_MovePerMass * m_RigidbodyObjectAInverseMass;
	OKVector2<float> t_MoveOutB = -t_MovePerMass * m_RigidbodyObjectBInverseMass;

	float InverseA = m_RigidbodyObjectAInverseMass;
	float InverseB = m_RigidbodyObjectBInverseMass;

	// NOTE: See if the objects are moving into each other
	float t_VelocityAlongNormal = t_SeperatingVelocity.x * collisionManifold.m_CollisionNormal.x + t_SeperatingVelocity.y * collisionManifold.m_CollisionNormal.y;

	// NOTE: Calculate the bounce of the objects based off their inverse mass and normal
	float impMag = (-(1 + coefRest) * t_VelocityAlongNormal) / (InverseA + InverseB);

	// NOTE: Velocity / Position Solving
	if (gameObjectA->HasComponent<Rigidbody2DComponent>() 
		&& gameObjectA->GetComponent<Rigidbody2DComponent>().GetRigidbodyMovementType() == RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
	{
		// NOTE: Seperate the 2 objects away from each other if they are still interpentrating
		if (collisionManifold.m_PenetrationDepth != 0) { gameObjectA->m_Transform.position += t_MoveOutA; }
		
		// NOTE: If velocity along the normal is greater than 0, we want to resolve the collision
		if (t_VelocityAlongNormal > 0) { return; }
		float impulseX = impMag * collisionManifold.m_CollisionNormal.x;
		float impulseY = impMag * collisionManifold.m_CollisionNormal.y;

		// NOTE: Apply calculation to the new objects
		gameObjectA->GetComponent<Rigidbody2DComponent>().ApplyImpulseX(impulseX / gameObjectA->GetComponent<Rigidbody2DComponent>().m_Mass);
		gameObjectA->GetComponent<Rigidbody2DComponent>().ApplyImpulseY(impulseY / gameObjectA->GetComponent<Rigidbody2DComponent>().m_Mass);
	}

	if (gameObjectB->HasComponent<Rigidbody2DComponent>() 
		&& gameObjectB->GetComponent<Rigidbody2DComponent>().GetRigidbodyMovementType() == RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
	{
		// NOTE: Seperate the 2 objects away from each other if they are still interpentrating
		if (collisionManifold.m_PenetrationDepth != 0) { gameObjectB->m_Transform.position += t_MoveOutB; }
		
		// NOTE: If velocity along the normal is greater than 0, we want to resolve the collision
		if (t_VelocityAlongNormal > 0) { return; }
		float impulseX = impMag * collisionManifold.m_CollisionNormal.x;
		float impulseY = impMag * collisionManifold.m_CollisionNormal.y;

		// NOTE: Apply calculation to the new objects
		gameObjectB->GetComponent<Rigidbody2DComponent>().ApplyImpulseX(-1 * impulseX / gameObjectB->GetComponent<Rigidbody2DComponent>().m_Mass);
		gameObjectB->GetComponent<Rigidbody2DComponent>().ApplyImpulseY(-1 * impulseY / gameObjectB->GetComponent<Rigidbody2DComponent>().m_Mass);
	}
}

OKVector2<float> CollisionResolutionManager::CalculateSeperatingVelocity(GameObjectEntity* gameObjectA, GameObjectEntity* gameobjectB)
{
	// NOTE: Calculate the Relative Velocity / Seperating Velocity
	OKVector2<float> t_RelativeVelocity = OKVector2<float>();

	if (!gameObjectA->HasComponent<Rigidbody2DComponent>())
	{
		t_RelativeVelocity = OKVector2<float>(0.f, 0.f);
	}
	else
	{
		t_RelativeVelocity = gameObjectA->GetComponent<Rigidbody2DComponent>().m_Velocity;
	}

	if (!gameobjectB->HasComponent<Rigidbody2DComponent>())
	{
		t_RelativeVelocity -= OKVector2<float>(0.f, 0.f);
	}
	else
	{
		t_RelativeVelocity -= gameobjectB->GetComponent<Rigidbody2DComponent>().m_Velocity;
	}

	return t_RelativeVelocity;
}
