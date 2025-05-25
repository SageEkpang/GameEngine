#include "CollisionManager.h"

// FORWARD DEC INCLUDE(s)
#include "RectangleColliderComponent.h"
#include "OrientedRectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "LineColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "ComplexColliderComponent.h"
#include "PointColliderComponent.h"

OKVector2<float> CollisionManager::ProjectPointOntoLine(OKVector2<float> point, OKVector2<float> positionReference, OKVector2<float> lineStart, OKVector2<float> lineEnd, OKVector2<float> offsetLine)
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

bool CollisionManager::Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols)
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

Interval2D CollisionManager::GetOrientedRectangleInterval(GameObjectEntity* orRectA, OKVector2<float>& axis)
{
	OKVector2<float> t_tempPosition = orRectA->m_Transform.position;
	OKVector2<float> t_tempScale = orRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Scale;
	float t_tempRotation = orRectA->m_Transform.rotation;

	OKVector2<float> MaxB = t_tempPosition + t_tempScale;
	OKVector2<float> MinB = t_tempPosition - t_tempScale;

	OKVector2<float> verts[] = {
		MinB, MaxB,
		OKVector2<float>(MinB.x, MaxB.y),  OKVector2<float>(MaxB.x, MinB.y)
	};

	float theta = t_tempRotation * DEG2RAD;

	float zRotation2x2[] = {
		std::cosf(theta), std::sinf(theta),
		-std::sinf(theta), std::cosf(theta)
	};

	for (int i = 0; i < 4; ++i)
	{
		OKVector2<float> r = verts[i] - t_tempPosition;
		Multiply(r.asArray(), OKVector2<float>(r.x, r.y).asArray(), 1, 2, zRotation2x2, 2, 2);
		verts[i] = r + t_tempPosition;
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

Interval2D CollisionManager::GetRectangleInterval(GameObjectEntity* rectA, OKVector2<float>& axis)
{
	Interval2D result;

	OKVector2<float> t_tempPosition = rectA->m_Transform.position;
	OKVector2<float> t_tempScale = rectA->GetComponent<RectangleColliderComponent>()->m_Scale;

	OKVector2<float> Max = t_tempPosition + t_tempScale;
	OKVector2<float> Min = t_tempPosition - t_tempScale;

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

bool CollisionManager::OverlapOnAxis(GameObjectEntity* rectA, GameObjectEntity* orRectB, OKVector2<float> axis)
{
	Interval2D A = GetRectangleInterval(rectA, axis);
	Interval2D B = GetOrientedRectangleInterval(orRectB, axis);
	return ((B.min <= A.max) && (A.min <= B.max));
}

CollisionManager::CollisionManager()
{
	// NOTE: Potential Collision Mapping Init
	m_CollisionMapping[std::make_pair(std::type_index(typeid(RectangleColliderComponent)), std::type_index(typeid(RectangleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_RECTANGLE_TO_RECTANGLE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(CircleColliderComponent)), std::type_index(typeid(CircleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_CIRCLE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(CircleColliderComponent)), std::type_index(typeid(RectangleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_RECTANGLE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(CapsuleColliderComponent)), std::type_index(typeid(CapsuleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CAPSULE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(CapsuleColliderComponent)), std::type_index(typeid(RectangleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_RECTANGLE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(CapsuleColliderComponent)), std::type_index(typeid(CircleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CIRCLE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(OrientedRectangleColliderComponent)), std::type_index(typeid(OrientedRectangleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_ORIENTED;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(OrientedRectangleColliderComponent)), std::type_index(typeid(RectangleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_RECTANGLE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(OrientedRectangleColliderComponent)), std::type_index(typeid(CircleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CIRCLE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(OrientedRectangleColliderComponent)), std::type_index(typeid(CapsuleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CAPSULE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(LineColliderComponent)), std::type_index(typeid(LineColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_LINE_TO_LINE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(LineColliderComponent)), std::type_index(typeid(CircleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_LINE_TO_CIRCLE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(LineColliderComponent)), std::type_index(typeid(RectangleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_LINE_TO_RECTANGLE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(LineColliderComponent)), std::type_index(typeid(CapsuleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_LINE_TO_CAPSULE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(LineColliderComponent)), std::type_index(typeid(OrientedRectangleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_LINE_TO_ORIENTED;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(PointColliderComponent)), std::type_index(typeid(PointColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_POINT_TO_POINT;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PointColliderComponent)), std::type_index(typeid(LineColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_POINT_TO_LINE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PointColliderComponent)), std::type_index(typeid(CircleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_POINT_TO_CIRCLE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PointColliderComponent)), std::type_index(typeid(RectangleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_POINT_TO_RECTANGLE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PointColliderComponent)), std::type_index(typeid(CapsuleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_POINT_TO_CAPSULE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PointColliderComponent)), std::type_index(typeid(OrientedRectangleColliderComponent)))] = COLLIDER_TYPE_COLLISIONS_POINT_TO_ORIENTED;
}

CollisionManager::~CollisionManager()
{
	m_CollisionMapping.clear();
}

CollisionManifold CollisionManager::CheckCollisions(GameObjectEntity* gameObjectA, GameObjectEntity* gameObjectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// NOTE: Temp Collision Variables
	GameObjectEntity* tempA = nullptr;
	GameObjectEntity* tempB = nullptr;

	// NOTE: Check if the collider component exists within the game object
	if (gameObjectA->FindChildComponent<ColliderEntity>()) { tempA = gameObjectA; }
	if (gameObjectB->FindChildComponent<ColliderEntity>()) { tempB = gameObjectB; }

	if (tempA == nullptr || tempB == nullptr) { return CollisionManifold(); }

	// NOTE: Assign the static casted class to the Game Objects
	auto collision_made_pair = std::make_pair(std::type_index(typeid(gameObjectA->FindChildComponent<ColliderEntity>())), std::type_index(typeid(gameObjectB->FindChildComponent<ColliderEntity>())));

	// NOTE: Reverse pair if it is not within the collision map
	if (m_CollisionMapping.count(collision_made_pair) == 0)
	{
		std::swap(collision_made_pair.first, collision_made_pair.second);
		std::swap(tempA, tempB);
	}

	switch (m_CollisionMapping[collision_made_pair])
	{
		case COLLIDER_TYPE_COLLISIONS_RECTANGLE_TO_RECTANGLE: return t_ColMani = RectangleToRectangle(tempA, tempB); break;

		case COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_CIRCLE: return t_ColMani = CircleToCircle(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_RECTANGLE: return t_ColMani = CircleToRectangle(tempA, tempB); break;

		case COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CAPSULE: return t_ColMani = CapsuleToCapsule(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_RECTANGLE: return t_ColMani = CapsuleToRectangle(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CIRCLE: return t_ColMani = CapsuleToCircle(tempA, tempB); break;

		case COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_ORIENTED: return t_ColMani = OrientedRectangleToOrientedRectangle(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_RECTANGLE: return t_ColMani = OrientedRectangleToRectangle(tempA, tempA); break;
		case COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CIRCLE: return t_ColMani = OrientedRectangleToCircle(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CAPSULE: return t_ColMani = OrientedRectangleToCapsule(tempA, tempB); break;

		case COLLIDER_TYPE_COLLISIONS_LINE_TO_LINE: return t_ColMani = LineToLine(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_LINE_TO_CIRCLE: return t_ColMani = LineToCircle(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_LINE_TO_RECTANGLE: return t_ColMani = LineToRectangle(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_LINE_TO_ORIENTED: return t_ColMani = LineToOrientedRectangle(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_LINE_TO_CAPSULE: return t_ColMani = LineToCapsule(tempA, tempB); break;

		case COLLIDER_TYPE_COLLISIONS_POINT_TO_POINT: return t_ColMani = PointToPoint(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_POINT_TO_LINE: return t_ColMani = PointToLine(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_POINT_TO_CIRCLE: return t_ColMani = PointToCircle(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_POINT_TO_RECTANGLE: return t_ColMani = PointToRectangle(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_POINT_TO_CAPSULE: return t_ColMani = PointToCapsule(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_POINT_TO_ORIENTED: return t_ColMani = PointToOrientedRectangle(tempA, tempB); break;

		default: t_ColMani = CollisionManifold();
	}

	return t_ColMani;
}

// FIX ME: Fix how this works
CollisionManifold CollisionManager::RectangleToRectangle(GameObjectEntity* rectA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	//OKVector2<float> RectCentreA = rectA->m_Position; // Centre A
	//OKVector2<float> RectScaleA = rectA->m_Scale; // Full Extents
	//OKVector2<float> NearPointA = OKVector2<float>(0, 0);
	//
	//OKVector2<float> RectCentreB = rectB->m_Position; // Centre B
	//OKVector2<float> RectScaleB = rectB->m_Scale; // Half Extents
	//OKVector2<float> NearPointB = OKVector2<float>(0, 0);

	//if (TopLeftCornerA.x < TopLeftCornerB.x)
	//{
	//	OKVector2<float> LeftSide = ProjectPointOntoLine(
	//		TopLeftCornerB,
	//		TopLeftCornerA,
	//		OKVector2<float>(TopLeftCornerB.x, TopLeftCornerB.y),
	//		OKVector2<float>(TopLeftCornerB.x, TopLeftCornerB.y + RectScaleB.y),
	//		OKVector2<float>(0, 1)
	//	);

	//	NearPointB.y = LeftSide.y;
	//}
	//else if (TopLeftCornerA.x > TopLeftCornerB.x)
	//{
	//	OKVector2<float> RightSide = ProjectPointOntoLine(
	//		TopLeftCornerB,
	//		TopLeftCornerA,
	//		OKVector2<float>(TopLeftCornerB.x + RectScaleB.x, TopLeftCornerB.y),
	//		OKVector2<float>(TopLeftCornerB.x + RectScaleB.x, TopLeftCornerB.y + RectScaleB.y),
	//		OKVector2<float>(0, 1)
	//	);

	//	NearPointB.y = RightSide.y;
	//}

	//if (TopLeftCornerA.y < RectCentreB.y)
	//{
	//	OKVector2<float> TopSide = ProjectPointOntoLine(
	//		TopLeftCornerB,
	//		TopLeftCornerA,
	//		OKVector2<float>(TopLeftCornerB.x, TopLeftCornerB.y),
	//		OKVector2<float>(TopLeftCornerB.x + RectScaleB.x, TopLeftCornerB.y),
	//		OKVector2<float>(1, 0)
	//	);

	//	NearPointB.x = TopSide.x;
	//}
	//else if (TopLeftCornerA.y > RectCentreB.y)
	//{
	//	OKVector2<float> BottomSide = ProjectPointOntoLine(
	//		TopLeftCornerB,
	//		TopLeftCornerA,
	//		OKVector2<float>(TopLeftCornerB.x, TopLeftCornerB.y + RectScaleB.y),
	//		OKVector2<float>(TopLeftCornerB.x + RectScaleB.x, TopLeftCornerB.y + RectScaleB.y),
	//		OKVector2<float>(1, 0)
	//	);

	//	NearPointB.x = BottomSide.x;
	//}

	//if (TopLeftCornerB.x < TopLeftCornerA.x)

	//{
	//	OKVector2<float> LeftSide = ProjectPointOntoLine(
	//		TopLeftCornerA,
	//		TopLeftCornerB,
	//		OKVector2<float>(TopLeftCornerA.x, TopLeftCornerA.y),
	//		OKVector2<float>(TopLeftCornerA.x, TopLeftCornerA.y + RectScaleA.y),
	//		OKVector2<float>(0, 1)
	//	);

	//	NearPointA.y = LeftSide.y;
	//}
	//else if (TopLeftCornerB.x > TopLeftCornerA.x)
	//{
	//	OKVector2<float> RightSide = ProjectPointOntoLine(
	//		TopLeftCornerA,
	//		TopLeftCornerB,
	//		OKVector2<float>(TopLeftCornerA.x + RectScaleA.x, TopLeftCornerA.y),
	//		OKVector2<float>(TopLeftCornerA.x + RectScaleA.x, TopLeftCornerA.y + RectScaleA.y),
	//		OKVector2<float>(0, 1)
	//	);

	//	NearPointA.y = RightSide.y;
	//}

	//if (TopLeftCornerB.y < RectCentreA.y)
	//{
	//	OKVector2<float> TopSide = ProjectPointOntoLine(
	//		TopLeftCornerA,
	//		TopLeftCornerB,
	//		OKVector2<float>(TopLeftCornerA.x, TopLeftCornerA.y),
	//		OKVector2<float>(TopLeftCornerA.x + RectScaleA.x, TopLeftCornerA.y),
	//		OKVector2<float>(1, 0)
	//	);

	//	NearPointA.x = TopSide.x;
	//}
	//else if (TopLeftCornerB.y > RectCentreA.y)
	//{
	//	OKVector2<float> BottomSide = ProjectPointOntoLine(
	//		TopLeftCornerA,
	//		TopLeftCornerB,
	//		OKVector2<float>(TopLeftCornerA.x, TopLeftCornerA.y + RectScaleA.y),
	//		OKVector2<float>(TopLeftCornerA.x + RectScaleA.x, TopLeftCornerA.y + RectScaleA.y),
	//		OKVector2<float>(1, 0)
	//	);

	//	NearPointA.x = BottomSide.x;
	//}

	//// DrawCircleV(NearPointA.ConvertToVec2(), 3, BLUE);
	//DrawCircleV(NearPointB.ConvertToVec2(), 1.f, YELLOW);
	//DrawCircleV(NearPointA.ConvertToVec2(), 1.f, YELLOW);

	//// REFACTOR: Fix the size of the circle  
	//// CircleColliderComponent circle_temp_A = CircleColliderComponent(NearPointA, 0.5f);
	//// CircleColliderComponent circle_temp_B = CircleColliderComponent(NearPointB, 0.5f);

	return t_ColMani;// = CircleToCircle(&circle_temp_A, &circle_temp_B);
}

CollisionManifold CollisionManager::CircleToCircle(GameObjectEntity* circA, GameObjectEntity* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> distance = circA->m_Transform.position - circB->m_Transform.position;
	float radii_sum = circA->GetComponent<CircleColliderComponent>()->m_Radius + circB->GetComponent<CircleColliderComponent>()->m_Radius;

	if (distance.magnitude() <= radii_sum)
	{
		if (circA->GetComponent<CircleColliderComponent>()->m_IsTrigger == true && circB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			circA->GetComponent<CircleColliderComponent>()->TriggerQuery(circB);
			circB->GetComponent<CircleColliderComponent>()->TriggerQuery(circA);
			return t_ColMani;
		}

		if (circA->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			circA->GetComponent<CircleColliderComponent>()->TriggerQuery(circB);
			return t_ColMani;
		}

		if (circB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			circB->GetComponent<CircleColliderComponent>()->TriggerQuery(circA);
			return t_ColMani;
		}

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = circA->m_Transform.position - circB->m_Transform.position;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(circA->m_Transform.position - circB->m_Transform.position).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::CircleToRectangle(GameObjectEntity* circA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	//OKVector2<float> RectCentre = rectB->m_Position + (rectB->m_Scale / 2.f);
	//OKVector2<float> RectScale = rectB->m_Scale;
	//OKVector2<float> TopLeftCorner = RectCentre - (RectScale / 2.f);

	//OKVector2<float> NearPoint = OKVector2<float>(0, 0);

	//if (circA->m_Position.x < TopLeftCorner.x)
	//{
	//	OKVector2<float> LeftSide = ProjectPointOntoLine(
	//		TopLeftCorner,
	//		circA->m_Position,
	//		OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y),
	//		OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y + RectScale.y),
	//		OKVector2<float>(0, 1)
	//	);

	//	NearPoint.y = LeftSide.y;
	//}
	//else if (circA->m_Position.x > TopLeftCorner.x)
	//{
	//	OKVector2<float> RightSide = ProjectPointOntoLine(
	//		TopLeftCorner,
	//		circA->m_Position,
	//		OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y),
	//		OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y + RectScale.y),
	//		OKVector2<float>(0, 1)
	//	);

	//	NearPoint.y = RightSide.y;
	//}

	//if (circA->m_Position.y < RectCentre.y)
	//{
	//	OKVector2<float> TopSide = ProjectPointOntoLine(
	//		TopLeftCorner,
	//		circA->m_Position,
	//		OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y),
	//		OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y),
	//		OKVector2<float>(1, 0)
	//	);

	//	NearPoint.x = TopSide.x;
	//}
	//else if (circA->m_Position.y > RectCentre.y)
	//{
	//	OKVector2<float> BottomSide = ProjectPointOntoLine(
	//		TopLeftCorner,
	//		circA->m_Position,
	//		OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y + RectScale.y),
	//		OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y + RectScale.y),
	//		OKVector2<float>(1, 0)
	//	);

	//	NearPoint.x = BottomSide.x;
	//}

	//CircleColliderComponent circle_temp_A = CircleColliderComponent(NearPoint, 1.f);

	return t_ColMani; // = CircleToCircle(circA, &circle_temp_A);
}

CollisionManifold CollisionManager::CapsuleToCircle(GameObjectEntity* capsuleA, GameObjectEntity* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// NOTE: Capsule Position and Variable(s)
	//OKVector2<float> tip_a = OKVector2<float>(capsuleA->m_Position.x, capsuleA->m_Position.y + (capsuleA->m_Height / 2.f) - (capsuleA->m_Width / 2.f));
	//OKVector2<float> base_a = OKVector2<float>(capsuleA->m_Position.x, capsuleA->m_Position.y - (capsuleA->m_Height / 2.f) + (capsuleA->m_Width / 2.f));

	//float t_DistanceX = tip_a.x - base_a.x;
	//float t_DistanceY = tip_a.y - base_a.y;
	//float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	//float dot = ((circB->m_Position.x - tip_a.x) * (base_a.x - tip_a.x)) + ((circB->m_Position.y - tip_a.y) * (base_a.y - tip_a.y)) / powf(len, 2);

	//// NOTE: Closest Point
	//OKVector2<float> closest_point;
	//closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x));
	//closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y));

	//closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	//closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	// NOTE: Create the circle based of the capsule components
	//CircleColliderComponent circle_temp = CircleColliderComponent(closest_point, capsuleA->m_Width / 2.f);

	// t_ColMani = CircleToCircle(&circle_temp, circB);

	return t_ColMani;
}

CollisionManifold CollisionManager::CapsuleToRectangle(GameObjectEntity* capsuleA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	//// Circles
	//// NOTE: Capsule Position and Variable(s)
	//OKVector2<float> tip_a = OKVector2<float>(capsuleA->m_Position.x, capsuleA->m_Position.y + (capsuleA->m_Height / 2.f) - (capsuleA->m_Width / 2.f));
	//OKVector2<float> base_a = OKVector2<float>(capsuleA->m_Position.x, capsuleA->m_Position.y - (capsuleA->m_Height / 2.f) + (capsuleA->m_Width / 2.f));

	//float t_DistanceX = tip_a.x - base_a.x;
	//float t_DistanceY = tip_a.y - base_a.y;
	//float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	//float dot = (((rectB->m_Position.x + (rectB->m_Scale.x / 2)) - tip_a.x) * (base_a.x - tip_a.x)) + ((rectB->m_Position.y + (rectB->m_Scale.y / 2) - tip_a.y) * (base_a.y - tip_a.y)) / powf(len, 2);

	//// NOTE: Closest Point
	//OKVector2<float> closest_point;
	//closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x) / 2);
	//closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y) / 2);

	//closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	//closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	// NOTE: Create the circle based of the capsule components
	// CircleColliderComponent circle_temp = CircleColliderComponent(closest_point, capsuleA->m_Width / 2.f);

	return t_ColMani; // = CircleToRectangle(&circle_temp, rectB);
}

CollisionManifold CollisionManager::CapsuleToCapsule(GameObjectEntity* capsuleA, GameObjectEntity* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// Capsule (A)
	// NOTE: Capsule Position and Variable(s)
	//OKVector2<float> tip_a = OKVector2<float>(capsuleA->m_Position.x, capsuleA->m_Position.y + (capsuleA->m_Height / 2.f) - (capsuleA->m_Width / 2.f));
	//OKVector2<float> base_a = OKVector2<float>(capsuleA->m_Position.x, capsuleA->m_Position.y - (capsuleA->m_Height / 2.f) + (capsuleA->m_Width / 2.f));
	//float t_DistanceXA = tip_a.x - base_a.x;
	//float t_DistanceYA = tip_a.y - base_a.y;
	//float lenA = sqrt((t_DistanceXA * t_DistanceXA) + (t_DistanceYA * t_DistanceYA));
	//float dotA = ((capsuleB->m_Position.x - tip_a.x) * (base_a.x - tip_a.x)) + ((capsuleB->m_Position.y - tip_a.y) * (base_a.y - tip_a.y)) / powf(lenA, 2);

	//// Capsule (B)
	//OKVector2<float> tip_b = OKVector2<float>(capsuleB->m_Position.x, capsuleB->m_Position.y + (capsuleB->m_Height / 2.f) - (capsuleB->m_Width / 2.f));
	//OKVector2<float> base_b = OKVector2<float>(capsuleB->m_Position.x, capsuleB->m_Position.y - (capsuleB->m_Height / 2.f) + (capsuleB->m_Width / 2.f));
	//float t_DistanceXB = tip_b.x - base_b.x;
	//float t_DistanceYB = tip_b.y - base_b.y;
	//float lenB = sqrt((t_DistanceXB * t_DistanceXB) + (t_DistanceYB * t_DistanceYB));
	//float dotB = ((capsuleA->m_Position.x - tip_b.x) * (base_b.x - tip_b.x)) + ((capsuleA->m_Position.y - tip_b.y) * (base_b.y - tip_b.y)) / powf(lenB, 2);

	//// NOTE: Closest Point (A)
	//OKVector2<float> closest_point_A;
	//closest_point_A.x = tip_a.x + (dotA * (base_a.x - tip_a.x)) / 2;
	//closest_point_A.y = tip_a.y + (dotA * (base_a.y - tip_a.y)) / 2;
	//closest_point_A.x = Clamp(closest_point_A.x, base_a.x, tip_a.x);
	//closest_point_A.y = Clamp(closest_point_A.y, base_a.y, tip_a.y);

	//// NOTE: Closest Point (B)
	//OKVector2<float> closest_point_B;
	//closest_point_B.x = tip_b.x + (dotB * (base_b.x - tip_b.x)) / 2;
	//closest_point_B.y = tip_b.y + (dotB * (base_b.y - tip_b.y)) / 2;
	//closest_point_B.x = Clamp(closest_point_B.x, base_b.x, tip_b.x);
	//closest_point_B.y = Clamp(closest_point_B.y, base_b.y, tip_b.y);

	//DrawCircleV(closest_point_A.ConvertToVec2(), 10.f, RED);
	//DrawCircleV(closest_point_B.ConvertToVec2(), 10.f, PURPLE);

	// NOTE: Circle Construction (A)
	// CircleColliderComponent circle_temp_A = CircleColliderComponent(closest_point_A, capsuleA->m_Width / 2.f);

	// NOTE: Circle Construction (B)
	// CircleColliderComponent circle_temp_B = CircleColliderComponent(closest_point_B, capsuleB->m_Width / 2.f);

	// t_ColMani = CircleToCircle(&circle_temp_A, &circle_temp_B);
	return t_ColMani;
}

CollisionManifold CollisionManager::OrientedRectangleToOrientedRectangle(GameObjectEntity* OrRectA, GameObjectEntity* OrRectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> AxisToTest[] = {
		OKVector2<float>(1, 0),
		OKVector2<float>(0, 1)
	};
	
	return t_ColMani;
}

CollisionManifold CollisionManager::OrientedRectangleToRectangle(GameObjectEntity* OrRectA, GameObjectEntity* rectB) // rect2 = OrRectA
{
	CollisionManifold t_ColMani = CollisionManifold();

	//OKVector2<float> AxisToTest[]{
	//	OKVector2<float>(1, 0), OKVector2<float>(0, 1),
	//	OKVector2<float>(0, 0), OKVector2<float>(0, 0)
	//};

	//float theta = DEG2RAD * OrRectA->m_Rotation;

	//float zRotation2x2[] = {
	//	std::cosf(theta), std::sinf(theta),
	//	-std::sinf(theta), std::cosf(theta)
	//};

	//OKVector2<float> axis = OKVector2<float>(OrRectA->m_Scale.x / 2, 0).normalise();
	//Multiply(AxisToTest[2].asArray(), axis.asArray(), 1, 2, zRotation2x2, 2, 2);

	//axis = OKVector2<float>(0, OrRectA->m_Scale.y / 2).normalise();
	//Multiply(AxisToTest[3].asArray(), axis.asArray(), 1, 2, zRotation2x2, 2, 2);

	//for (int i = 0; i < 4; ++i)
	//{
	//	if (!OverlapOnAxis(rectB, OrRectA, AxisToTest[i]))
	//	{
	//		return t_ColMani;
	//	}
	//}

	//t_ColMani.m_HasCollision = true;
	//t_ColMani.m_CollisionNormal = OrRectA->m_Position - rectB->m_Position;
	//t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
	//t_ColMani.m_ContactPointAmount = 1;
	//t_ColMani.m_PenetrationDepth = OKVector2<float>(OrRectA->m_Position - rectB->m_Position).magnitude();
	//t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

	return t_ColMani;
}

CollisionManifold CollisionManager::OrientedRectangleToCircle(GameObjectEntity* OrRectA, GameObjectEntity* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	//OKVector2<float> Rad = circB->m_Position - OrRectA->m_Position;
	//float theta = -DEG2RAD * OrRectA->m_Rotation;
	//
	//float zRotation2x2[] = {
	//	std::cosf(theta), std::sinf(theta),
	//	-std::sinf(theta), std::cosf(theta)
	//};

	//Multiply(Rad.asArray(), OKVector2<float>(Rad.x, Rad.y).asArray(), 1, 2, zRotation2x2, 2, 2);

	//OKTransform2<float> lcircle = OKTransform2<float>(Rad + (OrRectA->m_Scale / 2), OKVector2<float>(0, 0), 0);
	//// CircleColliderComponent circle_temp = CircleColliderComponent(Rad + (OrRectA->m_Scale / 2.f), circB->m_Radius);

	//OKTransform2<float> lRect = OKTransform2<float>(OKVector2<float>(0, 0), OrRectA->m_Scale, 0);
	// RectangleColliderComponent rectangle_temp = RectangleColliderComponent(OKVector2<float>(0, 0), OrRectA->m_Scale);

	return t_ColMani;
	// return t_ColMani = CircleToRectangle(&circle_temp, &rectangle_temp);
}

CollisionManifold CollisionManager::OrientedRectangleToCapsule(GameObjectEntity* OrRectA, GameObjectEntity* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// NEAREST POINT FOR CAPSULE
	// Circles
	// NOTE: Capsule Position and Variable(s)
	//OKVector2<float> tip_a = OKVector2<float>(capsuleB->m_Position.x, capsuleB->m_Position.y + (capsuleB->m_Height / 2.f) - (capsuleB->m_Width / 2.f));
	//OKVector2<float> base_a = OKVector2<float>(capsuleB->m_Position.x, capsuleB->m_Position.y - (capsuleB->m_Height / 2.f) + (capsuleB->m_Width / 2.f));

	//float t_DistanceX = tip_a.x - base_a.x;
	//float t_DistanceY = tip_a.y - base_a.y;
	//float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	//float dot = (((OrRectA->m_Position.x + (OrRectA->m_Scale.x / 2)) - tip_a.x) * (base_a.x - tip_a.x)) + ((OrRectA->m_Position.y + (OrRectA->m_Scale.y / 2) - tip_a.y) * (base_a.y - tip_a.y)) / powf(len, 2);

	//// NOTE: Closest Point
	//OKVector2<float> closest_point;
	//closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x) / 2);
	//closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y) / 2);

	//closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	//closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	//// NOTE: Create the circle based of the capsule components
	////CircleColliderComponent circle_temp = CircleColliderComponent(closest_point, capsuleB->m_Width / 2);

	//// ROTATED BOX TO CIRCLE
	//// OKVector2<float> Rad = circle_temp.m_Position - OrRectA->m_Position;
	//float theta = -DEG2RAD * OrRectA->m_Rotation;

	//float zRotation2x2[] = {
	//	std::cosf(theta), std::sinf(theta),
	//	-std::sinf(theta), std::cosf(theta)
	//};

	// Multiply(Rad.asArray(), OKVector2<float>(Rad.x, Rad.y).asArray(), 1, 2, zRotation2x2, 2, 2);

	//CircleColliderComponent circle_temp_or = CircleColliderComponent(Rad + (OrRectA->m_Scale / 2), circle_temp.m_Radius);
	// RectangleColliderComponent rectangle_temp = RectangleColliderComponent(OKVector2<float>(0, 0), OrRectA->m_Scale);

	return t_ColMani;
	// return t_ColMani = CircleToRectangle(&circle_temp_or, &rectangle_temp);
}

CollisionManifold CollisionManager::PointToPoint(GameObjectEntity* pointA, GameObjectEntity* pointB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	if (pointA->m_Transform.position == pointB->m_Transform.position)
	{
		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true && pointB->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(pointB);
			pointB->GetComponent<PointColliderComponent>()->TriggerQuery(pointA);
			return t_ColMani;
		}

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(pointB);
			return t_ColMani;
		}

		if (pointB->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointB->GetComponent<PointColliderComponent>()->TriggerQuery(pointA);
			return t_ColMani;
		}

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = pointA->m_Transform.position - pointB->m_Transform.position;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointA->m_Transform.position - pointB->m_Transform.position).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PointToLine(GameObjectEntity* pointA, GameObjectEntity* lineB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> t_LineBStart = lineB->GetComponent<LineColliderComponent>()->m_LineStartPosition;
	OKVector2<float> t_LineBEnd = lineB->GetComponent<LineColliderComponent>()->m_LineEndPosition;


	// NOTE: Distance Point from Start of Line
	float PointOneDistX = pointA->m_Transform.position.x - t_LineBStart.x;
	float PointOneDistY = pointA->m_Transform.position.y - t_LineBStart.y;
	float distanceOne = sqrt((PointOneDistX * PointOneDistX) + (PointOneDistY * PointOneDistY));

	// NOTE: Distance Point from End of Line
	float PointTwoDistX = pointA->m_Transform.position.x - t_LineBEnd.x;
	float PointTwoDistY = pointA->m_Transform.position.y - t_LineBEnd.y;
	float distanceTwo = sqrt((PointTwoDistX * PointTwoDistX) + (PointTwoDistY * PointTwoDistY));

	// NOTE: Distance from Start to End
	float distX = t_LineBStart.x - t_LineBEnd.x;
	float distY = t_LineBStart.y - t_LineBEnd.y;
	float LineLength = sqrt((distX * distX) + (distY * distY));

	// NOTE: Accuracy of colliding line
	float LineBuffer = pointA->GetComponent<PointColliderComponent>()->m_Radius;

	// NOTE: Collision Check
	if ((distanceOne + distanceTwo) >= LineLength - LineBuffer && distanceOne + distanceTwo <= LineLength + LineBuffer)
	{
		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true && lineB->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(lineB);
			lineB->GetComponent<LineColliderComponent>()->TriggerQuery(pointA);
			return t_ColMani;
		}

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(lineB);
			return t_ColMani;
		}

		if (lineB->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			lineB->GetComponent<LineColliderComponent>()->TriggerQuery(pointA);
			return t_ColMani;
		}

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = pointA->m_Transform.position - t_LineBStart;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointA->m_Transform.position - t_LineBStart).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PointToCircle(GameObjectEntity* pointA, GameObjectEntity* circleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// NOTE: Work out Distance between colliders
	float distX = pointA->m_Transform.position.x - circleB->m_Transform.position.x;
	float distY = pointA->m_Transform.position.y - circleB->m_Transform.position.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= circleB->GetComponent<CircleColliderComponent>()->m_Radius)
	{
		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true && circleB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(circleB);
			circleB->GetComponent<CircleColliderComponent>()->TriggerQuery(pointA);
			return t_ColMani;
		}

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(circleB);
			return t_ColMani;
		}

		if (circleB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			circleB->GetComponent<CircleColliderComponent>()->TriggerQuery(pointA);
			return t_ColMani;
		}

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = pointA->m_Transform.position - circleB->m_Transform.position;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointA->m_Transform.position - circleB->m_Transform.position).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PointToRectangle(GameObjectEntity* pointA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	if (pointA->m_Transform.position.x >= rectB->m_Transform.position.x &&
		pointA->m_Transform.position.x <= rectB->m_Transform.position.x + rectB->GetComponent<RectangleColliderComponent>()->m_Scale.x &&
		pointA->m_Transform.position.y >= rectB->m_Transform.position.y &&
		pointA->m_Transform.position.y <= rectB->m_Transform.position.y + rectB->GetComponent<RectangleColliderComponent>()->m_Scale.y)
	{
		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true && rectB->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(rectB);
			rectB->GetComponent<RectangleColliderComponent>()->TriggerQuery(pointA);
			return t_ColMani;
		}

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(rectB);
			return t_ColMani;
		}

		if (rectB->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true)
		{
			rectB->GetComponent<RectangleColliderComponent>()->TriggerQuery(pointA);
			return t_ColMani;
		}

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = pointA->m_Transform.position - rectB->m_Transform.position;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointA->m_Transform.position - rectB->m_Transform.position).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PointToCapsule(GameObjectEntity* pointA, GameObjectEntity* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> tip_a = OKVector2<float>(capsuleB->m_Transform.position.x, capsuleB->m_Transform.position.y + (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height/ 2.f) - (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));
	OKVector2<float> base_a = OKVector2<float>(capsuleB->m_Transform.position.x, capsuleB->m_Transform.position.y - (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f) + (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));

	float t_DistanceX = tip_a.x - base_a.x;
	float t_DistanceY = tip_a.y - base_a.y;
	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	float dot = ((pointA->m_Transform.position.x - tip_a.x) * (base_a.x - tip_a.x)) + ((pointA->m_Transform.position.y - tip_a.y) * (base_a.y - tip_a.y)) / powf(len, 2);

	// NOTE: Closest Point
	OKVector2<float> closest_point;
	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x));
	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y));

	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	// NOTE: Create the circle based of the capsule components
	// CircleColliderComponent circle_temp = CircleColliderComponent(closest_point, capsuleB->m_Width / 2);

	return t_ColMani;// = PointToCircle(pointA, &circle_temp);
}

CollisionManifold CollisionManager::PointToOrientedRectangle(GameObjectEntity* pointA, GameObjectEntity* OrRectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	return CollisionManifold();
}

CollisionManifold CollisionManager::LineToLine(GameObjectEntity* lineA, GameObjectEntity* lineB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const float x1 = lineA->GetComponent<LineColliderComponent>()->m_LineStartPosition.x;
	const float y1 = lineA->GetComponent<LineColliderComponent>()->m_LineStartPosition.y;

	const float x2 = lineA->GetComponent<LineColliderComponent>()->m_LineEndPosition.x;
	const float y2 = lineA->GetComponent<LineColliderComponent>()->m_LineEndPosition.y;

	const float x3 = lineB->GetComponent<LineColliderComponent>()->m_LineStartPosition.x;
	const float y3 = lineB->GetComponent<LineColliderComponent>()->m_LineStartPosition.y;

	const float x4 = lineB->GetComponent<LineColliderComponent>()->m_LineEndPosition.x;
	const float y4 = lineB->GetComponent<LineColliderComponent>()->m_LineEndPosition.y;

	// NOTE: Calculate Distance
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = lineA->m_Transform.position - lineB->m_Transform.position;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(lineA->m_Transform.position - lineB->m_Transform.position).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	};

	return t_ColMani;
}

CollisionManifold CollisionManager::LineToCircle(GameObjectEntity* lineA, GameObjectEntity* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// NOTE: Check if its already inside the circle
	// PointColliderComponent PointOne = PointColliderComponent(lineA->m_LineStartPosition, 1.f);
	// PointColliderComponent PointTwo = PointColliderComponent(lineA->m_LineEndPosition, 1.f);

	//bool insideOne = PointToCircle(&PointOne, circB).m_HasCollision;
	//bool insideTwo = PointToCircle(&PointTwo, circB).m_HasCollision;

	//if (insideOne || insideTwo)
	//{
	//	t_ColMani.m_HasCollision = true;
	//	t_ColMani.m_CollisionNormal = lineA->m_LineStartPosition - circB->m_Position;
	//	t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
	//	t_ColMani.m_ContactPointAmount = 1;
	//	t_ColMani.m_PenetrationDepth = OKVector2<float>(lineA->m_LineStartPosition - circB->m_Position).magnitude();
	//	t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

	//	return t_ColMani;
	//}


	//// NOTE: Get Length of Circle
	//float distX = lineA->m_LineStartPosition.x - lineA->m_LineEndPosition.x;
	//float distY = lineA->m_LineStartPosition.y - lineA->m_LineEndPosition.y;
	//float length = sqrt((distX * distX) + (distY * distY));

	//float dot = ( ((circB->m_Position.x - lineA->m_LineStartPosition.x) * (lineA->m_LineEndPosition.x - lineA->m_LineStartPosition.x)) +  ((circB->m_Position.y - lineA->m_LineStartPosition.y) * (lineA->m_LineEndPosition.y - lineA->m_LineStartPosition.y))) / (length * length);

	//float closestX = lineA->m_LineStartPosition.x + (dot * (lineA->m_LineEndPosition.x - lineA->m_LineStartPosition.x));
	//float closestY = lineA->m_LineStartPosition.y + (dot * (lineA->m_LineEndPosition.y - lineA->m_LineStartPosition.y));

	//PointColliderComponent tempCollider = PointColliderComponent(circB->m_Position, circB->m_Radius);
	//CollisionManifold onSegment = PointToLine(&tempCollider, lineA);

	//if (!onSegment.m_HasCollision)
	//{
	//	return t_ColMani;
	//}

	//distX = closestX - circB->m_Position.x;
	//distY = closestY - circB->m_Position.y;
	//float distance = sqrt((distX * distX) + (distY * distY));

	//if (distance <= circB->m_Radius)
	//{
	//	t_ColMani.m_HasCollision = true;
	//	t_ColMani.m_CollisionNormal = lineA->m_LineStartPosition - circB->m_Position;
	//	t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
	//	t_ColMani.m_ContactPointAmount = 1;
	//	t_ColMani.m_PenetrationDepth = OKVector2<float>(lineA->m_LineStartPosition - circB->m_Position).magnitude();
	//	t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

	//	return t_ColMani;
	//}

	return t_ColMani;
}

CollisionManifold CollisionManager::LineToRectangle(GameObjectEntity* lineA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> t_tempRectPosition = rectB->m_Transform.position;
	OKVector2<float> t_tempRectHalfScale = rectB->GetComponent<RectangleColliderComponent>()->m_Scale / 2.f;

	// NOTE: Left Line
	OKVector2<float> tempLeftPosStart = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempLeftPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	LineColliderComponent t_LineLeft = LineColliderComponent(tempLeftPosStart, tempLeftPosEnd);

	// NOTE: Right Line
	OKVector2<float> tempRightPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempRightPosEnd = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	LineColliderComponent t_LineRight = LineColliderComponent(tempRightPosStart, tempRightPosEnd);

	// NOTE: Top Line
	OKVector2<float> tempTopPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempTopPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	LineColliderComponent t_LineTop = LineColliderComponent(tempTopPosStart, tempTopPosEnd);

	// NOTE: Bottom Line
	OKVector2<float> tempBottomPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	OKVector2<float> tempBottomPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	LineColliderComponent t_LineBottom = LineColliderComponent(tempBottomPosStart, tempBottomPosEnd);

	//CollisionManifold t_Left = LineToLine(lineA, &t_LineLeft);
	//CollisionManifold t_Right = LineToLine(lineA, &t_LineRight);
	//CollisionManifold t_Top = LineToLine(lineA, &t_LineTop);
	//CollisionManifold t_Bottom = LineToLine(lineA, &t_LineBottom);

	//if (t_Left.m_HasCollision == true ||
	//	t_Right.m_HasCollision == true ||
	//	t_Top.m_HasCollision == true ||
	//	t_Bottom.m_HasCollision == true)
	//{
	//	t_ColMani.m_HasCollision = true;
	//	t_ColMani.m_CollisionNormal = lineA->m_LineStartPosition - rectB->m_Position;
	//	t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
	//	t_ColMani.m_ContactPointAmount = 1;
	//	t_ColMani.m_PenetrationDepth = OKVector2<float>(lineA->m_LineStartPosition - rectB->m_Position).magnitude();
	//	t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

	//	return t_ColMani;
	//}

	return t_ColMani;
}

CollisionManifold CollisionManager::LineToOrientedRectangle(GameObjectEntity* lineA, GameObjectEntity* OrRectB)
{
	return CollisionManifold();
}

CollisionManifold CollisionManager::LineToCapsule(GameObjectEntity* lineA, GameObjectEntity* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	//OKVector2<float> tip_a = OKVector2<float>(capsuleB->m_Position.x, capsuleB->m_Position.y + (capsuleB->m_Scale.y / 2) - (capsuleB->m_Scale.x / 2));
	//OKVector2<float> base_a = OKVector2<float>(capsuleB->m_Position.x, capsuleB->m_Position.y - (capsuleB->m_Scale.y / 2) + (capsuleB->m_Scale.x / 2));

	//float t_DistanceX = tip_a.x - base_a.x;
	//float t_DistanceY = tip_a.y - base_a.y;
	//float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	//float dot = ((lineA->m_LineEndPosition.x - tip_a.x) * (base_a.x - tip_a.x)) + ((lineA->m_LineEndPosition.y - tip_a.y) * (base_a.y - tip_a.y)) / pow(len, 2);
	//
	//// NOTE: Closest Point
	//OKVector2<float> closest_point;
	//
	//// NOTE: Calculating the Y Position
	//// NOTE: New calculation with the line start and end in mind
	//float LineYCalculation = ((lineA->m_LineStartPosition.y - (capsuleB->m_Position.y - capsuleB->m_Scale.y / 2)) * 0.5f) - ((lineA->m_LineEndPosition.y - (capsuleB->m_Position.y - capsuleB->m_Scale.y / 2)) * 0.5f);
	//closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y)) + LineYCalculation;

	//// NOTE: Calculating the Position
	//closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x));
	//closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	//closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	//DrawCircle(closest_point.x, closest_point.y, capsuleB->m_Scale.x / 2, RED);

	//// NOTE: Create the circle based of the capsule components
	//OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(capsuleB->m_Scale.x, capsuleB->m_Scale.x), 0);
	//GameObjectEntitycircle_temp = Collider(&circle_transform, capsuleB->m_Scale.x / 2.f);

	//return t_ColMani = LineToCircle(lineA, &circle_temp);

	// Capsule (A)
	// NOTE: Capsule Position and Variable(s)
	//OKVector2<float> tip_a = OKVector2<float>(lineA->m_LineStartPosition.x, lineA->m_LineStartPosition.y);
	//OKVector2<float> base_a = OKVector2<float>(lineA->m_LineEndPosition.x, lineA->m_LineEndPosition.y);
	//float t_DistanceXA = tip_a.x - base_a.x;
	//float t_DistanceYA = tip_a.y - base_a.y;
	//float lenA = sqrt((t_DistanceXA * t_DistanceXA) + (t_DistanceYA * t_DistanceYA));
	//float dotA = ((capsuleB->m_Position.x - tip_a.x) * (base_a.x - tip_a.x)) + ((capsuleB->m_Position.y - tip_a.y) * (base_a.y - tip_a.y)) / powf(lenA, 2);

	//// Capsule (B)
	//OKVector2<float> tip_b = OKVector2<float>(capsuleB->m_Position.x, capsuleB->m_Position.y + (capsuleB->m_Height / 2.f) - (capsuleB->m_Width / 2));
	//OKVector2<float> base_b = OKVector2<float>(capsuleB->m_Position.x, capsuleB->m_Position.y - (capsuleB->m_Height / 2.f) + (capsuleB->m_Width / 2));
	//float t_DistanceXB = tip_b.x - base_b.x;
	//float t_DistanceYB = tip_b.y - base_b.y;
	//float lenB = sqrt((t_DistanceXB * t_DistanceXB) + (t_DistanceYB * t_DistanceYB));

	//OKVector2<float> MiddlePosition;
	//MiddlePosition.x = (lineA->m_LineStartPosition.x + lineA->m_LineEndPosition.x) / 2.f;
	//MiddlePosition.y = (lineA->m_LineStartPosition.y + lineA->m_LineEndPosition.y) / 2.f;

	//float dotB = ((MiddlePosition.x - tip_b.x) * (base_b.x - tip_b.x)) + ((MiddlePosition.y - tip_b.y) * (base_b.y - tip_b.y)) / powf(lenB, 2);

	//// NOTE: Closest Point (A)
	//OKVector2<float> closest_point_A;
	//closest_point_A.x = tip_a.x + (dotA * (base_a.x - tip_a.x)) / 2;
	//closest_point_A.y = tip_a.y + (dotA * (base_a.y - tip_a.y)) / 2;
	//closest_point_A.x = Clamp(closest_point_A.x, base_a.x, tip_a.x);
	//closest_point_A.y = Clamp(closest_point_A.y, base_a.y, tip_a.y);

	//// NOTE: Closest Point (B)
	//OKVector2<float> closest_point_B;
	//closest_point_B.x = tip_b.x + (dotB * (base_b.x - tip_b.x)) / 2;
	//closest_point_B.y = tip_b.y + (dotB * (base_b.y - tip_b.y)) / 2;
	//closest_point_B.x = Clamp(closest_point_B.x, base_b.x, tip_b.x);
	//closest_point_B.y = Clamp(closest_point_B.y, base_b.y, tip_b.y);

	//DrawCircleV(closest_point_A.ConvertToVec2(), 10.f, RED);
	//DrawCircleV(closest_point_B.ConvertToVec2(), 10.f, PURPLE);

	// NOTE: Circle Construction (A)
	// PointColliderComponent point_temp_A = PointColliderComponent(closest_point_A);

	// NOTE: Circle Construction (B)
	// CircleColliderComponent circle_temp_B = CircleColliderComponent(closest_point_B, capsuleB->m_Width / 2.f);

	// t_ColMani = PointToCircle(&point_temp_A, &circle_temp_B);
	return t_ColMani;
}
