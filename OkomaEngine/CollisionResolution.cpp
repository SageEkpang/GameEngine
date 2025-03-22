#include "CollisionResolution.h"

CollisionResolution::CollisionResolution()
{

}

CollisionResolution::~CollisionResolution()
{

}

void CollisionResolution::ResolveCollision(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, float CoefRest, float penetration, OKVector2<float> collisionNormal, float deltaTime)
{
	// NOTE: Move the object out of the other object first and then apply the force to the object
	ResolveVelocity(rigidbodyA, rigidbodyB, CoefRest, deltaTime, collisionNormal);
	ResolveInterpenetration(rigidbodyA, rigidbodyB, CoefRest, collisionNormal);
}

void CollisionResolution::ResolveCollisionsWithRotation(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, float CoefRest, float penetration, OKVector2<float> collisionNormal, float deltaTime)
{







}

void CollisionResolution::ResolveVelocity(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, float CoefRest, float deltaTime, OKVector2<float> collisionNormal)
{
	OKVector2<float> t_SeperatingVelocity = CalculateSeperatingVelocity(rigidbodyA, rigidbodyB, collisionNormal);

	// If there is no need for seperating velocity, then we do not need to run the function
	if (t_SeperatingVelocity > OKVector2<float>(0, 0)) { return; }

	OKVector2<float> t_NewSeperatingVelocity = -t_SeperatingVelocity * CoefRest;

	OKVector2<float> t_AccumulatedVelocity = rigidbodyA->GetAcceleration();
	t_AccumulatedVelocity -= rigidbodyB->GetAcceleration();

	OKVector2<float> t_AccumulatedSeperatingVelocity = t_AccumulatedVelocity * collisionNormal; // Delta time may not need to be here

	if (t_AccumulatedSeperatingVelocity < OKVector2<float>(0, 0))
	{
		t_NewSeperatingVelocity += CoefRest * t_AccumulatedSeperatingVelocity;

		if (t_NewSeperatingVelocity < OKVector2<float>(0, 0))
		{
			t_NewSeperatingVelocity = 0;
		}
	}

	OKVector2<float> t_DeltaVelocity = t_NewSeperatingVelocity - t_SeperatingVelocity;
	float t_TotalInverseMass = rigidbodyA->GetInverseMass();
	t_TotalInverseMass += rigidbodyB->GetInverseMass();

	if (t_TotalInverseMass == 0) { return; }

	OKVector2<float> t_Impulse = t_DeltaVelocity / t_TotalInverseMass;
	OKVector2<float> t_ImpulsePerMass = collisionNormal * t_Impulse;

	rigidbodyA->AddImpulse(t_ImpulsePerMass * rigidbodyA->GetInverseMass() * 2);
	rigidbodyB->AddImpulse(t_ImpulsePerMass * -rigidbodyB->GetInverseMass() * 2);
}

// NOTE: This Collision Function can only be for collisions that have no rotations to them
void CollisionResolution::ResolveInterpenetration(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, float penetration, OKVector2<float> collisionNormal)
{
	// No Penetration, so no need for it
	if (penetration <= 0) { return; }

	float t_TotalInverseMass = rigidbodyA->GetInverseMass() + rigidbodyB->GetInverseMass();

	// If infinite mass, return (more so for stationary / static objects)
	if (t_TotalInverseMass == 0) { return; }

	// Find by how much to move the entity
	OKVector2<float> t_MovePerMass = collisionNormal * (penetration / t_TotalInverseMass);
	OKVector2<float> t_MoveOutA = t_MovePerMass * rigidbodyA->GetInverseMass();
	OKVector2<float> t_MoveOutB = t_MovePerMass * -rigidbodyB->GetInverseMass();

	// NOTE:
	rigidbodyA->GetTransform()->position += t_MoveOutA;
	rigidbodyB->GetTransform()->position += t_MoveOutB;
}

OKVector2<float> CollisionResolution::CalculateSeperatingVelocity(Rigidbody* rigidbodyA, Rigidbody* rigidbodyB, OKVector2<float> contactNormal) const
{
	OKVector2<float> t_RelativeVelocity = rigidbodyA->GetVelocity();
	t_RelativeVelocity -= rigidbodyB->GetVelocity();
	return t_RelativeVelocity * contactNormal;
}
