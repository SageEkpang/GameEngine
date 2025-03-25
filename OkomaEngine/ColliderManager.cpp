#include "ColliderManager.h"

OKVector2<float> ColliderManager::ProjectPointOntoLine(OKVector2<float> point, OKVector2<float> positionReference, OKVector2<float> lineStart, OKVector2<float> lineEnd, OKVector2<float> offsetLine)
{
	// NOTE: Capsule Position and Variable(s)

	OKVector2<float> LineStart = lineStart;
	OKVector2<float> LineEnd = lineEnd;

	OKVector2<float> Normal = offsetLine;
	float NormalDot = Normal.dot(point);
	OKVector2<float> ClosestPoint = point - (Normal * NormalDot) + positionReference;

	ClosestPoint.x = Clamp(ClosestPoint.x, LineStart.x, LineEnd.x);
	ClosestPoint.y = Clamp(ClosestPoint.y, LineStart.y, LineEnd.y);

	return ClosestPoint;
}

bool ColliderManager::Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols)
{
	if (aCols != bRows) { return false; }

	for (int i = 0; i < aRows; ++i) 
	{
		for (int j = 0; j < bCols; ++j) 
		{
			out[bCols * i + j] = 0.0f;

			for (int k = 0; k < bRows; ++k) 
			{
				int a = aCols * i + k;
				int b = bCols * k + j;
				out[bCols * i + j] += matA[a] * matB[b];
			}
		}
	}

	return true;
}

Interval2D ColliderManager::GetOrientedRectangleInterval(Collider* orRectA, OKVector2<float>& axis)
{
	OKTransform2<float> lRect = OKTransform2<float>(orRectA->GetPosition() - (orRectA->GetScale() / 2), orRectA->GetScale(), 0);
	Collider rectangle_temp = Collider("rect rep", &lRect);

	OKVector2<float> MaxB = orRectA->GetPosition() - orRectA->GetScale();
	OKVector2<float> MinB = orRectA->GetPosition() + orRectA->GetScale();

	OKVector2<float> verts[] = {
		MinB, MaxB,
		OKVector2<float>(MinB.x, MaxB.y),  OKVector2<float>(MaxB.x, MinB.y)
	};

	float theta = orRectA->GetRotation() * DEG2RAD;

	float zRotation2x2[] = {
		std::cosf(theta), std::sinf(theta),
		-std::sinf(theta), std::cosf(theta)
	};

	for (int i = 0; i < 4; ++i)
	{
		OKVector2<float> r = verts[i] - orRectA->GetPosition();
		Multiply(r.asArray(), OKVector2<float>(r.x, r.y).asArray(), 1, 2, zRotation2x2, 2, 2);
		verts[i] = r + orRectA->GetPosition();
	}

	Interval2D res;
	res.min = res.max = verts[0].dot(axis);

	for (int i = 1; i < 4; ++i)
	{
		float proj = verts[i].dot(axis);
		res.min = (proj < res.min) ? proj : res.min;
		res.max = (proj > res.max) ? proj : res.max;
	}

	return res;
}

Interval2D ColliderManager::GetRectangleInterval(Collider* rectA, OKVector2<float>& axis)
{
	Interval2D result;

	OKVector2<float> Max = rectA->GetPosition() - rectA->GetScale();
	OKVector2<float> Min = rectA->GetPosition() + rectA->GetScale();

	OKVector2<float> verts[] =
	{
		OKVector2<float>(Min.x, Min.y), OKVector2<float>(Min.x, Max.y),
		OKVector2<float>(Max.x, Max.y), OKVector2<float>(Max.x, Min.y)
	};

	result.min = result.max = verts[0].dot(axis);

	for (int i = 1; i < 4; ++i) {
		float projection = verts[i].dot(axis);

		if (projection < result.min) 
		{
			result.min = projection;
		}

		if (projection > result.max) 
		{
			result.max = projection;
		}
	}

	return result;
}

bool ColliderManager::OverlapOnAxis(Collider* rectA, Collider* orRectB, OKVector2<float> axis)
{
	Interval2D A = GetRectangleInterval(rectA, axis);
	Interval2D B = GetOrientedRectangleInterval(orRectB, axis);
	return ((B.min <= A.max) && (A.min <= B.max));
}

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

	Collider* tempA = colliderA;
	Collider* tempB = colliderB;

	// NOTE: Reverse pair if it is not within the collision map
	if (m_CollisionMapping.count(collision_made_pair) == 0)
	{
		// std::swap()
		ColliderType temp = collision_made_pair.first;
		collision_made_pair.first = collision_made_pair.second;
		collision_made_pair.second = temp;

		tempA = colliderB;
		tempB = colliderA;
	}

	switch (m_CollisionMapping[collision_made_pair])
	{
		case RECTANGLE_TO_RECTANGLE: return t_ColMani = RectangleToRectangle(tempA, tempB); break;

		case CIRCLE_TO_CIRCLE: return t_ColMani = CircleToCircle(tempA, tempB); break;
		case CIRCLE_TO_RECTANGLE: return t_ColMani = CircleToRectangle(tempA, tempB); break;

		case CAPSULE_TO_CAPSULE: return t_ColMani = CapsuleToCapsule(tempA, tempB); break;
		case CAPSULE_TO_RECTANGLE: return t_ColMani = CapsuleToRectangle(tempA, tempB); break;
		case CAPSULE_TO_CIRCLE: return t_ColMani = CapsuleToCircle(tempA, tempB); break;

		case ORIENTED_TO_ORIENTED: return t_ColMani = OrientedRectangleToOrientedRectangle(tempA, tempB); break;
		case ORIENTED_TO_RECTANGLE: return t_ColMani = OrientedRectangleToRectangle(tempA, tempB); break;
		case ORIENTED_TO_CIRCLE: return t_ColMani = OrientedRectangleToCircle(tempA, tempB); break;
		case ORIENTED_TO_CAPSULE: return t_ColMani = OrientedRectangleToCapsule(tempA, tempB); break;

		default: t_ColMani = CollisionManifold();
	}

	return t_ColMani;
}

CollisionManifold ColliderManager::RectangleToRectangle(Collider* rectA, Collider* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> RectCentreB = rectB->GetPosition() + rectB->GetScale() / 2;
	OKVector2<float> NearPointB = OKVector2<float>(0, 0);

	if (rectA->GetPosition().x < rectB->GetPosition().x)
	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			rectB->GetPosition(),
			rectA->GetPosition(),
			OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y),
			OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y + rectB->GetScale().y),
			OKVector2<float>(0, 1)
		);

		NearPointB.y = LeftSide.y;
	}
	else if (rectA->GetPosition().x > rectB->GetPosition().x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			rectB->GetPosition(),
			rectA->GetPosition(),
			OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y),
			OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y + rectB->GetScale().y),
			OKVector2<float>(0, 1)
		);

		NearPointB.y = RightSide.y;
	}

	if (rectA->GetPosition().y < RectCentreB.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			rectB->GetPosition(),
			rectA->GetPosition(),
			OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y),
			OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y),
			OKVector2<float>(1, 0)
		);

		NearPointB.x = TopSide.x;
	}
	else if (rectA->GetPosition().y > RectCentreB.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			rectB->GetPosition(),
			rectA->GetPosition(),
			OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y + rectB->GetScale().y),
			OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y + rectB->GetScale().y),
			OKVector2<float>(1, 0)
		);

		NearPointB.x = BottomSide.x;
	}

	OKVector2<float> RectCentreA = rectA->GetPosition() + rectA->GetScale() / 2;
	OKVector2<float> NearPointA;

	if (rectB->GetPosition().x < rectA->GetPosition().x)
	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			rectA->GetPosition(),
			rectB->GetPosition(),
			OKVector2<float>(rectA->GetPosition().x, rectA->GetPosition().y),
			OKVector2<float>(rectA->GetPosition().x, rectA->GetPosition().y + rectA->GetScale().y),
			OKVector2<float>(0, 1)
		);

		NearPointA.y = LeftSide.y;
	}
	else if (rectB->GetPosition().x > rectA->GetPosition().x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			rectA->GetPosition(),
			rectB->GetPosition(),
			OKVector2<float>(rectA->GetPosition().x + rectA->GetScale().x, rectA->GetPosition().y),
			OKVector2<float>(rectA->GetPosition().x + rectA->GetScale().x, rectA->GetPosition().y + rectA->GetScale().y),
			OKVector2<float>(0, 1)
		);

		NearPointA.y = RightSide.y;
	}

	if (rectB->GetPosition().y < RectCentreA.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			rectA->GetPosition(),
			rectB->GetPosition(),
			OKVector2<float>(rectA->GetPosition().x, rectA->GetPosition().y),
			OKVector2<float>(rectA->GetPosition().x + rectA->GetScale().x, rectA->GetPosition().y),
			OKVector2<float>(1, 0)
		);

		NearPointA.x = TopSide.x;
	}
	else if (rectB->GetPosition().y > RectCentreA.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			rectA->GetPosition(),
			rectB->GetPosition(),
			OKVector2<float>(rectA->GetPosition().x, rectA->GetPosition().y + rectA->GetScale().y),
			OKVector2<float>(rectA->GetPosition().x + rectA->GetScale().x, rectA->GetPosition().y + rectA->GetScale().y),
			OKVector2<float>(1, 0)
		);

		NearPointA.x = BottomSide.x;
	}

	// DrawCircleV(NearPointA.ConvertToVec2(), 3, BLUE);

	// REFACTOR: Fix the size of the circle  
	OKTransform2<float> circle_transform_A = OKTransform2<float>(NearPointA, OKVector2<float>(0, 0), 0);
	Collider circle_temp_A = Collider("temp rep A", &circle_transform_A, 0.5f);

	OKTransform2<float> circle_transform_B = OKTransform2<float>(NearPointB, OKVector2<float>(0, 0), 0);
	Collider circle_temp_B = Collider("temp rep B", &circle_transform_B, 0.5f);

	return t_ColMani = CircleToCircle(&circle_temp_A, &circle_temp_B);
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
	OKVector2<float> RectCentre = rectB->GetPosition() + rectB->GetScale() / 2;
	OKVector2<float> NearPoint = OKVector2<float>(0, 0);

	if (circA->GetPosition().x < rectB->GetPosition().x)
	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			rectB->GetPosition(),
			circA->GetPosition(),
			OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y),
			OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y + rectB->GetScale().y),
			OKVector2<float>(0, 1)
		);

		NearPoint.y = LeftSide.y;
	}
	else if (circA->GetPosition().x > rectB->GetPosition().x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			rectB->GetPosition(),
			circA->GetPosition(),
			OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y),
			OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y + rectB->GetScale().y),
			OKVector2<float>(0, 1)
		);

		NearPoint.y = RightSide.y;
	}

	if (circA->GetPosition().y < RectCentre.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			rectB->GetPosition(),
			circA->GetPosition(),
			OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y),
			OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y),
			OKVector2<float>(1, 0)
		);

		NearPoint.x = TopSide.x;
	}
	else if (circA->GetPosition().y > RectCentre.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			rectB->GetPosition(),
			circA->GetPosition(),
			OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y + rectB->GetScale().y),
			OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y + rectB->GetScale().y),
			OKVector2<float>(1, 0)
		);

		NearPoint.x = BottomSide.x;
	}

	OKTransform2<float> circle_transform_A = OKTransform2<float>(NearPoint, OKVector2<float>(0, 0), 0);
	Collider circle_temp_A = Collider("temp rep A", &circle_transform_A, 1.f);

	return t_ColMani = CircleToCircle(circA, &circle_temp_A);
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

	// NOTE: Create the circle based of the capsule components
	OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(capsuleA->GetScale().x, capsuleA->GetScale().x), 0);
	Collider circle_temp = Collider("temp rep", &circle_transform, capsuleA->GetScale().x / 2);

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
	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x) / 2);
	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y) / 2);

	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	// NOTE: Create the circle based of the capsule components
	OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(0, 0), 0);
	Collider circle_temp = Collider("temp rep", &circle_transform, capsuleA->GetScale().x / 2);

	return t_ColMani = CircleToRectangle(&circle_temp, rectB);
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
	OKTransform2<float> circle_transform_A = OKTransform2<float>(closest_point_A, OKVector2<float>(0, 0), 0);
	Collider circle_temp_A = Collider("temp rep A", &circle_transform_A, capsuleA->GetScale().x / 2);

	// NOTE: Circle Construction (B)
	OKTransform2<float> circle_transform_B = OKTransform2<float>(closest_point_B, OKVector2<float>(0, 0), 0);
	Collider circle_temp_B = Collider("temp rep B", &circle_transform_B, capsuleB->GetScale().x / 2);

	t_ColMani = CircleToCircle(&circle_temp_A, &circle_temp_B);
	return t_ColMani;
}

CollisionManifold ColliderManager::OrientedRectangleToOrientedRectangle(Collider* OrRectA, Collider* OrRectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> AxisToTest[] = {
		OKVector2<float>(1, 0),
		OKVector2<float>(0, 1)
	};
	
	return t_ColMani;
}

CollisionManifold ColliderManager::OrientedRectangleToRectangle(Collider* OrRectA, Collider* rectB) // rect2 = OrRectA
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> AxisToTest[]{
		OKVector2<float>(1, 0), OKVector2<float>(0, 1),
		OKVector2<float>(0, 0), OKVector2<float>(0, 0)
	};

	float theta = DEG2RAD * OrRectA->GetRotation();

	float zRotation2x2[] = {
		std::cosf(theta), std::sinf(theta),
		-std::sinf(theta), std::cosf(theta)
	};

	OKVector2<float> axis = OKVector2<float>(OrRectA->GetScale().x / 2, 0).normalise();
	Multiply(AxisToTest[2].asArray(), axis.asArray(), 1, 2, zRotation2x2, 2, 2);

	axis = OKVector2<float>(0, OrRectA->GetScale().y / 2).normalise();
	Multiply(AxisToTest[3].asArray(), axis.asArray(), 1, 2, zRotation2x2, 2, 2);

	for (int i = 0; i < 4; ++i)
	{
		if (!OverlapOnAxis(rectB, OrRectA, AxisToTest[i]))
		{
			return t_ColMani;
		}
	}

	t_ColMani.m_HasCollision = true;
	t_ColMani.m_CollisionNormal = OrRectA->GetTransform()->position - rectB->GetTransform()->position;
	t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
	t_ColMani.m_ContactPointAmount = 1;
	t_ColMani.m_PenetrationDepth = OKVector2<float>(OrRectA->GetTransform()->position - rectB->GetTransform()->position).magnitude();
	t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

	return t_ColMani;
}

CollisionManifold ColliderManager::OrientedRectangleToCircle(Collider* OrRectA, Collider* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> Rad = circB->GetPosition() - OrRectA->GetPosition();
	float theta = -DEG2RAD * OrRectA->GetRotation();
	
	float zRotation2x2[] = {
		std::cosf(theta), std::sinf(theta),
		-std::sinf(theta), std::cosf(theta)
	};

	Multiply(Rad.asArray(), OKVector2<float>(Rad.x, Rad.y).asArray(), 1, 2, zRotation2x2, 2, 2);

	OKTransform2<float> lcircle = OKTransform2<float>(Rad + (OrRectA->GetScale() / 2), OKVector2<float>(0, 0), 0);
	Collider circle_temp = Collider("circ rep", &lcircle, circB->GetRadius());

	OKTransform2<float> lRect = OKTransform2<float>(OKVector2<float>(0, 0), OrRectA->GetScale(), 0);
	Collider rectangle_temp = Collider("rect rep", &lRect);

	return t_ColMani = CircleToRectangle(&circle_temp, &rectangle_temp);
}

CollisionManifold ColliderManager::OrientedRectangleToCapsule(Collider* OrRectA, Collider* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// NEAREST POINT FOR CAPSULE
	// Circles
	// NOTE: Capsule Position and Variable(s)
	OKVector2<float> tip_a = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y + (capsuleB->GetScale().y / 2) - (capsuleB->GetScale().x / 2));
	OKVector2<float> base_a = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y - (capsuleB->GetScale().y / 2) + (capsuleB->GetScale().x / 2));

	float t_DistanceX = tip_a.x - base_a.x;
	float t_DistanceY = tip_a.y - base_a.y;
	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	float dot = (((OrRectA->GetPosition().x + (OrRectA->GetScale().x / 2)) - tip_a.x) * (base_a.x - tip_a.x)) + ((OrRectA->GetPosition().y + (OrRectA->GetScale().y / 2) - tip_a.y) * (base_a.y - tip_a.y)) / pow(len, 2);

	// NOTE: Closest Point
	OKVector2<float> closest_point;
	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x) / 2);
	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y) / 2);

	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	// NOTE: Create the circle based of the capsule components
	OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(0, 0), 0);
	Collider circle_temp = Collider("temp rep", &circle_transform, capsuleB->GetScale().x / 2);

	
	// ROTATED BOX TO CIRCLE
	OKVector2<float> Rad = circle_temp.GetPosition() - OrRectA->GetPosition();
	float theta = -DEG2RAD * OrRectA->GetRotation();

	float zRotation2x2[] = {
		std::cosf(theta), std::sinf(theta),
		-std::sinf(theta), std::cosf(theta)
	};

	Multiply(Rad.asArray(), OKVector2<float>(Rad.x, Rad.y).asArray(), 1, 2, zRotation2x2, 2, 2);

	OKTransform2<float> lcircle = OKTransform2<float>(Rad + (OrRectA->GetScale() / 2), OKVector2<float>(0, 0), 0);
	Collider circle_temp_or = Collider("circ rep", &lcircle, circle_temp.GetRadius());

	OKTransform2<float> lRect = OKTransform2<float>(OKVector2<float>(0, 0), OrRectA->GetScale(), 0);
	Collider rectangle_temp = Collider("rect rep", &lRect);

	return t_ColMani = CircleToRectangle(&circle_temp_or, &rectangle_temp);
}
