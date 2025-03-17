#include "ColliderManager.h"

ColliderManager::ColliderManager()
{
	m_CollisionMapping[std::make_pair(COLLIDER_RECTANGLE, COLLIDER_RECTANGLE)] = RECTANGLE_TO_RECTANGLE;

	m_CollisionMapping[std::make_pair(COLLIDER_CIRCLE, COLLIDER_CIRCLE)] = CIRCLE_TO_CIRCLE;
	m_CollisionMapping[std::make_pair(COLLIDER_CIRCLE, COLLIDER_RECTANGLE)] = CIRCLE_TO_RECTANGLE;

	m_CollisionMapping[std::make_pair(COLLIDER_CAPSULE, COLLIDER_CAPSULE)] = CAPSULE_TO_CAPSULE;
	m_CollisionMapping[std::make_pair(COLLIDER_CAPSULE, COLLIDER_RECTANGLE)] = CAPSULE_TO_RECTANGLE;
	m_CollisionMapping[std::make_pair(COLLIDER_CAPSULE, COLLIDER_CIRCLE)] = CAPSULE_TO_CIRCLE;

	m_CollisionMapping[std::make_pair(COLLIDER_ORIENTED_RECTANGLE, COLLIDER_ORIENTED_RECTANGLE)] = ORIENTED_TO_ORIENTED;
	m_CollisionMapping[std::make_pair(COLLIDER_ORIENTED_RECTANGLE, COLLIDER_RECTANGLE)] = ORIENTED_TO_RECTANGLE;
	m_CollisionMapping[std::make_pair(COLLIDER_ORIENTED_RECTANGLE, COLLIDER_CIRCLE)] = ORIENTED_TO_CIRCLE;
	m_CollisionMapping[std::make_pair(COLLIDER_ORIENTED_RECTANGLE, COLLIDER_CAPSULE)] = ORIENTED_TO_CAPSULE;
}

CollisionManifold ColliderManager::CheckCollisions(Collider* colliderA, Collider* colliderB)
{
	CollisionManifold t_ColMani = CollisionManifold();
	auto collision_made_pair = std::make_pair(colliderA->GetColliderType(), colliderB->GetColliderType());

	// NOTE: Reverse pair if it is not within the collision map
	if (m_CollisionMapping.count(collision_made_pair) == 0)
	{
		ColliderType temp = collision_made_pair.first;
		collision_made_pair.first = collision_made_pair.second;
		collision_made_pair.second = temp;
	}

	switch (m_CollisionMapping[collision_made_pair])
	{
		case RECTANGLE_TO_RECTANGLE: return t_ColMani = RectangleToRectangle(colliderA, colliderB); break;

		case CIRCLE_TO_CIRCLE: return t_ColMani = CircleToCircle(colliderA, colliderB); break;
		case CIRCLE_TO_RECTANGLE: return t_ColMani = CircleToRectangle(colliderA, colliderB); break;

		case CAPSULE_TO_CAPSULE: return t_ColMani = CapsuleToCapsule(colliderA, colliderB); break;
		case CAPSULE_TO_RECTANGLE: return t_ColMani = CapsuleToRectangle(colliderA, colliderB); break;
		case CAPSULE_TO_CIRCLE: return t_ColMani = CapsuleToCircle(colliderA, colliderB); break;

		case ORIENTED_TO_ORIENTED: return t_ColMani = OrientedRectangleToOrientedRectangle(colliderA, colliderB); break;
		case ORIENTED_TO_RECTANGLE: return t_ColMani = OrientedRectangleToRectangle(colliderA, colliderB); break;
		case ORIENTED_TO_CIRCLE: return t_ColMani = OrientedRectangleToCircle(colliderA, colliderB); break;
		case ORIENTED_TO_CAPSULE: return t_ColMani = OrientedRectangleToCapsule(colliderA, colliderB); break;

		default: t_ColMani = CollisionManifold();
	}

	return t_ColMani;
}

CollisionManifold ColliderManager::RectangleToRectangle(Collider* rectA, Collider* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	bool t_OverlapXLeft = rectA->GetPosition().x < (rectB->GetPosition().x + rectB->GetScale().x);
	bool t_OverlapXRight = (rectA->GetPosition().x + rectA->GetScale().x) > rectB->GetPosition().x;
	bool t_OverlapYTop = rectA->GetPosition().y < (rectB->GetPosition().y + rectB->GetScale().y);
	bool t_OverlapYBottom = (rectA->GetPosition().y + rectA->GetScale().y) > rectB->GetPosition().y;

	/*
		// Given point p, return the point q on or in AABB b that is closest to p
		void ClosestPtPointAABB(Point p, AABB b, Point &q)
		{
			// For each coordinate axis, if the point coordinate value is
			// outside box, clamp it to the box, else keep it as is
			for(inti=0;i<3;
				 float v = p[i];
				  if (v < b.min[i]) v = b.min[i]; // v = max(v, b.min[i])
				  if (v > b.max[i]) v = b.max[i]; // v = min(v, b.max[i])
				  q[i] = v;
			}
		}
	*/


	if (t_OverlapXLeft && t_OverlapXRight && t_OverlapYTop && t_OverlapYBottom)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = (rectA->GetTransform()->position + (rectA->GetScale() / 2)) - (rectB->GetTransform()->position + (rectB->GetScale() / 2));
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(rectA->GetTransform()->position - rectB->GetTransform()->position).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold ColliderManager::CircleToCircle(Collider* circA, Collider* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> distance = circA->GetTransform()->position - circB->GetTransform()->position;
	float radii_sum = circA->GetRadius() + circB->GetRadius();

	if (distance.magnitude() <= radii_sum)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = circA->GetTransform()->position - circB->GetTransform()->position;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(circA->GetTransform()->position - circB->GetTransform()->position).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold ColliderManager::CircleToRectangle(Collider* circA, Collider* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	float t_TestX = circA->GetPosition().x;
	float t_TestY = circA->GetPosition().y;

	if (circA->GetPosition().x < rectB->GetPosition().x)
	{
		t_TestX = rectB->GetPosition().x;
	}
	else if (circA->GetPosition().x > (rectB->GetPosition().x + rectB->GetScale().x))
	{
		t_TestX = rectB->GetPosition().x + rectB->GetScale().x;
	}

	if (circA->GetPosition().y < rectB->GetPosition().y)
	{
		t_TestY = rectB->GetPosition().y;
	}
	else if (circA->GetPosition().y > (rectB->GetPosition().y + rectB->GetScale().y))
	{
		t_TestY = rectB->GetPosition().y + rectB->GetScale().y;
	}

	float DistX = circA->GetPosition().x - t_TestX;
	float DistY = circA->GetPosition().y - t_TestY;
	float Distance = sqrt( (DistX * DistX) + (DistY * DistY));

	if (Distance <= circA->GetRadius())
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = circA->GetTransform()->position - rectB->GetTransform()->position;
	 	t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(circA->GetTransform()->position - rectB->GetTransform()->position).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold ColliderManager::CapsuleToCircle(Collider* capsuleA, Collider* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// NOTE: Capsule Position and Variable(s)
	OKVector2<float> tip_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y + (capsuleA->GetScale().y / 2) - (capsuleA->GetScale().x / 2));
	OKVector2<float> base_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y - (capsuleA->GetScale().y / 2) + (capsuleA->GetScale().x / 2));

	float t_DistanceX = tip_a.x - base_a.x;
	float t_DistanceY = tip_a.y - base_a.y;
	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	float dot = ((circB->GetPosition().x - tip_a.x) * (base_a.x - tip_a.x)) + ((circB->GetPosition().y - tip_a.y) * (base_a.y - tip_a.y)) / pow(len, 2);

	// NOTE: Closest Point
	OKVector2<float> closest_point;
	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x));
	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y));

	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	// DrawCircleV(closest_point.ConvertToVec2(), capsuleA->GetScale().x, PURPLE);

	// NOTE: Create the circle based of the capsule components
	OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(0, 0), OKVector2<float>(capsuleA->GetScale().x, capsuleA->GetScale().x));
	Collider circle_temp = Collider("temp rep", &circle_transform, capsuleA->GetScale().x / 2);

	DrawCircleV(closest_point.ConvertToVec2(), capsuleA->GetScale().x / 2, PURPLE);

	t_ColMani = CircleToCircle(&circle_temp, circB);

	return t_ColMani;
}

CollisionManifold ColliderManager::CapsuleToRectangle(Collider* capsuleA, Collider* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// Circles
	// NOTE: Capsule Position and Variable(s)
	OKVector2<float> tip_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y + (capsuleA->GetScale().y / 2) - (capsuleA->GetScale().x / 2));
	OKVector2<float> base_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y - (capsuleA->GetScale().y / 2) + (capsuleA->GetScale().x / 2));

	float t_DistanceX = tip_a.x - base_a.x;
	float t_DistanceY = tip_a.y - base_a.y;
	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	float dot = (((rectB->GetPosition().x + (rectB->GetScale().x / 2)) - tip_a.x) * (base_a.x - tip_a.x)) + ((rectB->GetPosition().y + (rectB->GetScale().y / 2) - tip_a.y) * (base_a.y - tip_a.y)) / pow(len, 2);

	// NOTE: Closest Point
	OKVector2<float> closest_point;
	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x));
	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y));

	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	// NOTE: Create the circle based of the capsule components
	OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(0, 0), OKVector2<float>(0, 0));
	Collider circle_temp = Collider("temp rep", &circle_transform, capsuleA->GetScale().x / 2);

	DrawCircleV(closest_point.ConvertToVec2(), capsuleA->GetScale().x / 2, PURPLE);

	t_ColMani = CircleToRectangle(&circle_temp, rectB);

	return t_ColMani;
}

CollisionManifold ColliderManager::CapsuleToCapsule(Collider* capsuleA, Collider* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// Capsule (A)
	// NOTE: Capsule Position and Variable(s)
	OKVector2<float> tip_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y + (capsuleA->GetScale().y / 2) - (capsuleA->GetScale().x / 2));
	OKVector2<float> base_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y - (capsuleA->GetScale().y / 2) + (capsuleA->GetScale().x / 2));
	float t_DistanceXA = tip_a.x - base_a.x;
	float t_DistanceYA = tip_a.y - base_a.y;
	float lenA = sqrt((t_DistanceXA * t_DistanceXA) + (t_DistanceYA * t_DistanceYA));
	float dotA = ((capsuleB->GetPosition().x - tip_a.x) * (base_a.x - tip_a.x)) + ((capsuleB->GetPosition().y - tip_a.y) * (base_a.y - tip_a.y)) / pow(lenA, 2);

	// Capsule (B)
	OKVector2<float> tip_b = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y + (capsuleB->GetScale().y / 2) - (capsuleB->GetScale().x / 2));
	OKVector2<float> base_b = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y - (capsuleB->GetScale().y / 2) + (capsuleB->GetScale().x / 2));
	float t_DistanceXB = tip_b.x - base_b.x;
	float t_DistanceYB = tip_b.y - base_b.y;
	float lenB = sqrt((t_DistanceXB * t_DistanceXB) + (t_DistanceYB * t_DistanceYB));
	float dotB = ((capsuleA->GetPosition().x - tip_b.x) * (base_b.x - tip_b.x)) + ((capsuleA->GetPosition().y - tip_b.y) * (base_b.y - tip_b.y)) / pow(lenB, 2);

	// NOTE: Closest Point (A)
	OKVector2<float> closest_point_A;
	closest_point_A.x = tip_a.x + (dotA * (base_a.x - tip_a.x)) / 2;
	closest_point_A.y = tip_a.y + (dotA * (base_a.y - tip_a.y)) / 2;
	closest_point_A.x = Clamp(closest_point_A.x, base_a.x, tip_a.x);
	closest_point_A.y = Clamp(closest_point_A.y, base_a.y, tip_a.y);

	// NOTE: Closest Point (B)
	OKVector2<float> closest_point_B;
	closest_point_B.x = tip_b.x + (dotB * (base_b.x - tip_b.x)) / 2;
	closest_point_B.y = tip_b.y + (dotB * (base_b.y - tip_b.y)) / 2;
	closest_point_B.x = Clamp(closest_point_B.x, base_b.x, tip_b.x);
	closest_point_B.y = Clamp(closest_point_B.y, base_b.y, tip_b.y);

	// NOTE: Circle Construction (A)
	OKTransform2<float> circle_transform_A = OKTransform2<float>(closest_point_A, OKVector2<float>(0, 0), OKVector2<float>(0, 0));
	Collider circle_temp_A = Collider("temp rep A", &circle_transform_A, capsuleA->GetScale().x / 2);

	// NOTE: Circle Construction (B)
	OKTransform2<float> circle_transform_B = OKTransform2<float>(closest_point_B, OKVector2<float>(0, 0), OKVector2<float>(0, 0));
	Collider circle_temp_B = Collider("temp rep B", &circle_transform_B, capsuleB->GetScale().x / 2);

	DrawCircleV(closest_point_A.ConvertToVec2(), capsuleA->GetScale().x / 2, PURPLE);
	DrawCircleV(closest_point_B.ConvertToVec2(), capsuleB->GetScale().x / 2, PURPLE);

	t_ColMani = CircleToCircle(&circle_temp_A, &circle_temp_B);
	return t_ColMani;
}

CollisionManifold ColliderManager::OrientedRectangleToOrientedRectangle(Collider* OrRectA, Collider* OrRectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	return t_ColMani;
}

CollisionManifold ColliderManager::OrientedRectangleToRectangle(Collider* OrRectA, Collider* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	return t_ColMani;
}

CollisionManifold ColliderManager::OrientedRectangleToCircle(Collider* OrRectA, Collider* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	return t_ColMani;
}

CollisionManifold ColliderManager::OrientedRectangleToCapsule(Collider* OrRectA, Collider* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	return t_ColMani;
}
