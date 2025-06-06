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
	float t_tempRotation = orRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Rotation;

	OKVector2<float> MaxB;
	MaxB.x = t_tempPosition.x + (t_tempScale.x / 2.f);
	MaxB.y = t_tempPosition.y + (t_tempScale.y / 2.f);

	OKVector2<float> MinB;
	MinB.x = t_tempPosition.x - (t_tempScale.x / 2.f);
	MinB.y = t_tempPosition.y - (t_tempScale.y / 2.f);

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

	OKVector2<float> Max;
	Max.x = t_tempPosition.x + (t_tempScale.x / 2.f);
	Max.y = t_tempPosition.y + (t_tempScale.y / 2.f);

	OKVector2<float> Min;
	Min.x = t_tempPosition.x - (t_tempScale.x / 2.f);
	Min.y = t_tempPosition.y - (t_tempScale.y / 2.f);

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
	auto collision_made_pair = std::make_pair(tempA->FindChildComponentID<ColliderEntity>(), tempB->FindChildComponentID<ColliderEntity>());

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
		case COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_RECTANGLE: return t_ColMani = OrientedRectangleToRectangle(tempA, tempB); break;
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

CollisionManifold CollisionManager::RectangleToRectangle(GameObjectEntity* rectA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	rectA->GetComponent<RectangleColliderComponent>()->m_HasCollided = false;
	rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> RectCentreA = rectA->m_Transform.position + rectA->GetComponent<RectangleColliderComponent>()->m_Offset - (rectA->GetComponent<RectangleColliderComponent>()->m_Scale / 2.f); // Centre A
	OKVector2<float> RectScaleA = rectA->GetComponent<RectangleColliderComponent>()->m_Scale;// ; // Full Extents
	OKVector2<float> RectScaleHalfA = RectScaleA / 2.f;
	OKVector2<float> NearPointA = OKVector2<float>(0, 0);
	
	OKVector2<float> RectCentreB = rectB->m_Transform.position + rectB->GetComponent<RectangleColliderComponent>()->m_Offset - (rectB->GetComponent<RectangleColliderComponent>()->m_Scale / 2.f); // Centre B
	OKVector2<float> RectScaleB = rectB->GetComponent<RectangleColliderComponent>()->m_Scale;// ; // Half Extents
	OKVector2<float> RectScaleHalfB = RectScaleB / 2.f;
	OKVector2<float> NearPointB = OKVector2<float>(0, 0);

	if (RectCentreA.x < RectCentreB.x)
	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x, RectCentreB.y),
			OKVector2<float>(RectCentreB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(0, 1)
		);

		NearPointB.y = LeftSide.y;
	}
	else if (RectCentreA.x > RectCentreB.x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y),
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(0, 1)
		);

		NearPointB.y = RightSide.y;
	}

	if (RectCentreA.y < RectCentreB.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x, RectCentreB.y),
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y),
			OKVector2<float>(1, 0)
		);

		NearPointB.x = TopSide.x;
	}
	else if (RectCentreA.y > RectCentreB.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(1, 0)
		);

		NearPointB.x = BottomSide.x;
	}

	if (RectCentreB.x < RectCentreA.x)

	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x, RectCentreA.y),
			OKVector2<float>(RectCentreA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(0, 1)
		);

		NearPointA.y = LeftSide.y;
	}
	else if (RectCentreB.x > RectCentreA.x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y),
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(0, 1)
		);

		NearPointA.y = RightSide.y;
	}

	if (RectCentreB.y < RectCentreA.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x, RectCentreA.y),
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y),
			OKVector2<float>(1, 0)
		);

		NearPointA.x = TopSide.x;
	}
	else if (RectCentreB.y > RectCentreA.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(1, 0)
		);

		NearPointA.x = BottomSide.x;
	}

	CollisionManifold t_tempMani = S_CircleToCircle(NearPointA, 0.5f, NearPointB, 0.5f);

	if (t_tempMani.m_HasCollision)
	{
		rectA->GetComponent<RectangleColliderComponent>()->m_HasCollided = true;
		rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = true;

		if (rectA->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true && rectB->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true)
		{
			rectA->GetComponent<RectangleColliderComponent>()->TriggerQuery(rectB);
			rectB->GetComponent<RectangleColliderComponent>()->TriggerQuery(rectA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (rectA->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true)
		{
			rectA->GetComponent<RectangleColliderComponent>()->TriggerQuery(rectB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (rectB->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true)
		{
			rectB->GetComponent<RectangleColliderComponent>()->TriggerQuery(rectA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		return t_tempMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::CircleToCircle(GameObjectEntity* circA, GameObjectEntity* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();
	circA->GetComponent<CircleColliderComponent>()->m_HasCollided = false;
	circB->GetComponent<CircleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> distance = (circA->m_Transform.position + circA->GetComponent<CircleColliderComponent>()->m_Offset) - (circB->m_Transform.position + circB->GetComponent<CircleColliderComponent>()->m_Offset);
	float radii_sum = circA->GetComponent<CircleColliderComponent>()->m_Radius + circB->GetComponent<CircleColliderComponent>()->m_Radius; 

	if (distance.magnitude() <= radii_sum)
	{
		circA->GetComponent<CircleColliderComponent>()->m_HasCollided = true;
		circB->GetComponent<CircleColliderComponent>()->m_HasCollided = true;

		if (circA->GetComponent<CircleColliderComponent>()->m_IsTrigger == true && circB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			circA->GetComponent<CircleColliderComponent>()->TriggerQuery(circB);
			circB->GetComponent<CircleColliderComponent>()->TriggerQuery(circA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (circA->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			circA->GetComponent<CircleColliderComponent>()->TriggerQuery(circB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (circB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			circB->GetComponent<CircleColliderComponent>()->TriggerQuery(circA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = distance.normalise();
		t_ColMani.m_PenetrationDepth = distance.magnitude() - radii_sum;
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::CircleToRectangle(GameObjectEntity* circA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	circA->GetComponent<CircleColliderComponent>()->m_HasCollided = false;
	rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_tempRectPosition = (rectB->m_Transform.position + rectB->GetComponent<RectangleColliderComponent>()->m_Offset);
	OKVector2<float> t_tempRectScale = rectB->GetComponent<RectangleColliderComponent>()->m_Scale;
	OKVector2<float> t_tempRectHalfScale = t_tempRectScale / 2.f;

	OKVector2<float> t_tempCircPositionA = circA->m_Transform.position + circA->GetComponent<CircleColliderComponent>()->m_Offset;
	float t_tempCircRadius = circA->GetComponent<CircleColliderComponent>()->m_Radius;

	OKVector2<float> RectCentre = (rectB->m_Transform.position + rectB->GetComponent<RectangleColliderComponent>()->m_Offset);
	OKVector2<float> RectScale = rectB->GetComponent<RectangleColliderComponent>()->m_Scale;
	OKVector2<float> TopLeftCorner = RectCentre - (RectScale / 2.f);

	OKVector2<float> NearPoint = OKVector2<float>(0, 0);

	if (circA->m_Transform.position.x < TopLeftCorner.x)
	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			TopLeftCorner,
			circA->m_Transform.position,
			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y),
			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y + RectScale.y),
			OKVector2<float>(0, 1)
		);

		NearPoint.y = LeftSide.y;
	}
	else if (circA->m_Transform.position.x > TopLeftCorner.x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			TopLeftCorner,
			circA->m_Transform.position,
			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y),
			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y + RectScale.y),
			OKVector2<float>(0, 1)
		);

		NearPoint.y = RightSide.y;
	}

	if (circA->m_Transform.position.y < RectCentre.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			TopLeftCorner,
			circA->m_Transform.position,
			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y),
			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y),
			OKVector2<float>(1, 0)
		);

		NearPoint.x = TopSide.x;
	}
	else if (circA->m_Transform.position.y > RectCentre.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			TopLeftCorner,
			circA->m_Transform.position,
			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y + RectScale.y),
			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y + RectScale.y),
			OKVector2<float>(1, 0)
		);

		NearPoint.x = BottomSide.x;
	}

	return S_CircleToCircle(circA->m_Transform.position, circA->GetComponent<CircleColliderComponent>()->m_Radius, NearPoint, 1.f);
}

CollisionManifold CollisionManager::CapsuleToCircle(GameObjectEntity* capsuleA, GameObjectEntity* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	capsuleA->GetComponent<CapsuleColliderComponent>()->m_HasCollided = false;
	circB->GetComponent<CircleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_tempCirclePositionB = circB->m_Transform.position + circB->GetComponent<CircleColliderComponent>()->m_Offset;
	float t_tempCircleRadiusB = circB->GetComponent<CircleColliderComponent>()->m_Radius;

	// Circles
	// NOTE: Capsule Position and Variable(s)
	OKVector2<float> tip_a = OKVector2<float>(capsuleA->m_Transform.position.x, capsuleA->m_Transform.position.y + (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f) - (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));
	OKVector2<float> base_a = OKVector2<float>(capsuleA->m_Transform.position.x, capsuleA->m_Transform.position.y - (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f) + (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));

	float t_DistanceX = tip_a.x - base_a.x;
	float t_DistanceY = tip_a.y - base_a.y;
	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	float dot = ((t_tempCirclePositionB.x - tip_a.x) * (base_a.x - tip_a.x)) + ((t_tempCirclePositionB.y - tip_a.y) * (base_a.y - tip_a.y)) / powf(len, 2);

	// NOTE: Closest Point
	OKVector2<float> closest_point;
	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x) / 2);
	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y) / 2);

	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	return t_ColMani  = S_CircleToCircle(closest_point, capsuleA->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f, circB->m_Transform.position, t_tempCircleRadiusB);
}

CollisionManifold CollisionManager::CapsuleToRectangle(GameObjectEntity* capsuleA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	capsuleA->GetComponent<CapsuleColliderComponent>()->m_HasCollided = false;
	rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_tempRectPositionB = rectB->m_Transform.position + rectB->GetComponent<RectangleColliderComponent>()->m_Offset;
	OKVector2<float> t_tempRectScaleB = rectB->GetComponent<RectangleColliderComponent>()->m_Scale;

	// Circles
	// NOTE: Capsule Position and Variable(s)
	OKVector2<float> tip_a = OKVector2<float>(capsuleA->m_Transform.position.x, capsuleA->m_Transform.position.y + (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f) - (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));
	OKVector2<float> base_a = OKVector2<float>(capsuleA->m_Transform.position.x, capsuleA->m_Transform.position.y - (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f) + (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));

	float t_DistanceX = tip_a.x - base_a.x;
	float t_DistanceY = tip_a.y - base_a.y;
	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));

	float dot = (((t_tempRectPositionB.x + (t_tempRectScaleB.x / 2)) - tip_a.x) * (base_a.x - tip_a.x)) + ((t_tempRectPositionB.y + (t_tempRectScaleB.y / 2) - tip_a.y) * (base_a.y - tip_a.y)) / powf(len, 2);

	// NOTE: Closest Point
	OKVector2<float> closest_point;
	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x));
	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y));

	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);

	return t_ColMani = S_CircleToRectangle(closest_point, capsuleA->GetComponent<CapsuleColliderComponent>()->m_Width * 0.5f, t_tempRectPositionB, t_tempRectScaleB);
}

CollisionManifold CollisionManager::CapsuleToCapsule(GameObjectEntity* capsuleA, GameObjectEntity* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	capsuleA->GetComponent<CapsuleColliderComponent>()->m_HasCollided = false;
	capsuleB->GetComponent<CapsuleColliderComponent>()->m_HasCollided = false;

	// Capsule (A)
	// NOTE: Capsule Position and Variable(s)
	OKVector2<float> tip_a = OKVector2<float>(capsuleA->m_Transform.position.x, capsuleA->m_Transform.position.y + (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f) - (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));
	OKVector2<float> base_a = OKVector2<float>(capsuleA->m_Transform.position.x, capsuleA->m_Transform.position.y - (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f) + (capsuleA->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));
	float t_DistanceXA = tip_a.x - base_a.x;
	float t_DistanceYA = tip_a.y - base_a.y;
	float lenA = sqrt((t_DistanceXA * t_DistanceXA) + (t_DistanceYA * t_DistanceYA));
	float dotA = ((capsuleB->m_Transform.position.x - tip_a.x) * (base_a.x - tip_a.x)) + ((capsuleB->m_Transform.position.y - tip_a.y) * (base_a.y - tip_a.y)) / powf(lenA, 2);

	// Capsule (B)
	OKVector2<float> tip_b = OKVector2<float>(capsuleB->m_Transform.position.x, capsuleB->m_Transform.position.y + (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f) - (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));
	OKVector2<float> base_b = OKVector2<float>(capsuleB->m_Transform.position.x, capsuleB->m_Transform.position.y - (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f) + (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f));
	float t_DistanceXB = tip_b.x - base_b.x;
	float t_DistanceYB = tip_b.y - base_b.y;
	float lenB = sqrt((t_DistanceXB * t_DistanceXB) + (t_DistanceYB * t_DistanceYB));
	float dotB = ((capsuleA->m_Transform.position.x - tip_b.x) * (base_b.x - tip_b.x)) + ((capsuleA->m_Transform.position.y - tip_b.y) * (base_b.y - tip_b.y)) / powf(lenB, 2);

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

	t_ColMani = S_CircleToCircle(closest_point_A, capsuleA->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f, closest_point_B, capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f);
	
	if (t_ColMani.m_HasCollision)
	{
		capsuleA->GetComponent<CapsuleColliderComponent>()->m_HasCollided = true;
		capsuleB->GetComponent<CapsuleColliderComponent>()->m_HasCollided = true;

		if (capsuleA->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true && capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true)
		{
			capsuleA->GetComponent<CapsuleColliderComponent>()->TriggerQuery(capsuleB);
			capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(capsuleA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (capsuleA->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true)
		{
			capsuleA->GetComponent<CapsuleColliderComponent>()->TriggerQuery(capsuleB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true)
		{
			capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(capsuleA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		return t_ColMani;
	}

	return CollisionManifold();
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

CollisionManifold CollisionManager::OrientedRectangleToRectangle(GameObjectEntity* OrRectA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = false;
	rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_tempRectanglePosition = rectB->m_Transform.position + rectB->GetComponent<RectangleColliderComponent>()->m_Offset;
	OKVector2<float> t_tempRectangleScale = rectB->m_Transform.scale + rectB->GetComponent<RectangleColliderComponent>()->m_Scale;

	OKVector2<float> t_tempOrRectPosition = OrRectA->m_Transform.position + OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Offset;
	OKVector2<float> t_tempOrRectScale = OrRectA->m_Transform.scale * OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Scale;

	OKVector2<float> Rad = t_tempRectanglePosition - t_tempOrRectPosition;

	OKVector2<float> t_TestingAxis[] = {
		OKVector2<float>(1.f, 0.f), OKVector2<float>(0.f, 1.f),
		OKVector2<float>(0.f, 0.f), OKVector2<float>(0.f, 0.f)
	};

	float theta = OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Rotation * DEG2RAD;

	float zRotation2x2[] = {
	std::cosf(theta), std::sinf(theta),
	-std::sinf(theta), std::cosf(theta)
	};

	OKVector2<float> t_tempAxis = OKVector2<float>(t_tempOrRectScale.x, 0).normalise();
	Multiply(t_TestingAxis[2].asArray(), t_tempAxis.asArray(), 1, 2, zRotation2x2, 2, 2);

	t_tempAxis = OKVector2<float>(0.f, t_tempOrRectScale.y).normalise();
	Multiply(t_TestingAxis[3].asArray(), t_tempAxis.asArray(), 1, 2, zRotation2x2, 2, 2);

	for (int i = 0; i < 4; ++i) {
		if (!OverlapOnAxis(rectB, OrRectA, t_TestingAxis[i])) 
		{
			return CollisionManifold(); // No collision has taken place
		}
	}

	// NOTE: Collision Has Taken Place
	OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = true;
	rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = true;

	if (OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true && rectB->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true)
	{
		OrRectA->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(rectB);
		rectB->GetComponent<RectangleColliderComponent>()->TriggerQuery(OrRectA);
		t_ColMani.m_HasCollision = true;
		return t_ColMani;
	}

	if (OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
	{
		OrRectA->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(rectB);
		t_ColMani.m_HasCollision = true;
		return t_ColMani;
	}

	if (rectB->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true)
	{
		rectB->GetComponent<RectangleColliderComponent>()->TriggerQuery(OrRectA);
		t_ColMani.m_HasCollision = true;
		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::OrientedRectangleToCircle(GameObjectEntity* OrRectA, GameObjectEntity* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = false;
	circB->GetComponent<CircleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_tempCirclePosition = circB->m_Transform.position + circB->GetComponent<CircleColliderComponent>()->m_Offset;
	OKVector2<float> t_tempOrRectPosition = OrRectA->m_Transform.position + OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Offset;
	OKVector2<float> t_tempOrRectScale = OrRectA->m_Transform.scale * OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Scale;

	OKVector2<float> Rad = t_tempCirclePosition - t_tempOrRectPosition;

	float theta = -DEG2RAD * OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Rotation;
	
	float zRotation2x2[] = {
		std::cosf(theta), std::sinf(theta),
		-std::sinf(theta), std::cosf(theta)
	};

	Multiply(Rad.asArray(), OKVector2<float>(Rad.x, Rad.y).asArray(), 1, 2, zRotation2x2, 2, 2);

	t_ColMani = S_CircleToRectangle(Rad + (OrRectA->m_Transform.scale / 2.f), circB->GetComponent<CircleColliderComponent>()->m_Radius, OKVector2<float>(0.f, 0.f), t_tempOrRectScale);
	
	if (t_ColMani.m_HasCollision)
	{
		OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = true;
		circB->GetComponent<CircleColliderComponent>()->m_HasCollided = true;

		if (OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true && circB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			OrRectA->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(circB);
			circB->GetComponent<CircleColliderComponent>()->TriggerQuery(OrRectA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			OrRectA->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(circB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (circB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			circB->GetComponent<CircleColliderComponent>()->TriggerQuery(OrRectA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::OrientedRectangleToCapsule(GameObjectEntity* OrRectA, GameObjectEntity* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	//OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = false;
	//capsuleB->GetComponent<CircleColliderComponent>()->m_HasCollided = false;

	//OKVector2<float> t_tempCirclePosition = circB->m_Transform.position + circB->GetComponent<CircleColliderComponent>()->m_Offset;

	//OKVector2<float> t_tempOrRectPosition = OrRectA->m_Transform.position + OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Offset;
	//OKVector2<float> t_tempOrRectScale = OrRectA->m_Transform.scale * OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Scale;

	//OKVector2<float> Rad = t_tempCirclePosition - t_tempOrRectPosition;

	//float theta = -DEG2RAD * OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_Rotation;

	//float zRotation2x2[] = {
	//	std::cosf(theta), std::sinf(theta),  
	//	-std::sinf(theta), std::cosf(theta)
	//};

	//Multiply(Rad.asArray(), OKVector2<float>(Rad.x, Rad.y).asArray(), 1, 2, zRotation2x2, 2, 2);

	//t_ColMani = S_CircleToRectangle(Rad + (OrRectA->m_Transform.scale / 2.f), circB->GetComponent<CircleColliderComponent>()->m_Radius, OKVector2<float>(0.f, 0.f), t_tempOrRectScale);

	//if (t_ColMani.m_HasCollision)
	//{
	//	OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = true;
	//	circB->GetComponent<CircleColliderComponent>()->m_HasCollided = true;

	//	if (OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true && circB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
	//	{
	//		OrRectA->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(circB);
	//		circB->GetComponent<CircleColliderComponent>()->TriggerQuery(OrRectA);
	//		t_ColMani.m_HasCollision = true;
	//		return t_ColMani;
	//	}

	//	if (OrRectA->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
	//	{
	//		OrRectA->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(circB);
	//		t_ColMani.m_HasCollision = true;
	//		return t_ColMani;
	//	}

	//	if (circB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
	//	{
	//		circB->GetComponent<CircleColliderComponent>()->TriggerQuery(OrRectA);
	//		t_ColMani.m_HasCollision = true;
	//		return t_ColMani;
	//	}

	//	return t_ColMani;
	//}

	return t_ColMani;
}

CollisionManifold CollisionManager::PointToPoint(GameObjectEntity* pointA, GameObjectEntity* pointB)
{
	CollisionManifold t_ColMani = CollisionManifold();
	pointA->GetComponent<PointColliderComponent>()->m_HasCollided = false;
	pointB->GetComponent<PointColliderComponent>()->m_HasCollided = false;

	if ((pointA->m_Transform.position + pointA->GetComponent<PointColliderComponent>()->m_Offset) == (pointB->m_Transform.position + pointB->GetComponent<PointColliderComponent>()->m_Offset))
	{
		pointA->GetComponent<PointColliderComponent>()->m_HasCollided = true;
		pointB->GetComponent<PointColliderComponent>()->m_HasCollided = true;

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true && pointB->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(pointB);
			pointB->GetComponent<PointColliderComponent>()->TriggerQuery(pointA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(pointB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (pointB->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointB->GetComponent<PointColliderComponent>()->TriggerQuery(pointA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = (pointA->m_Transform.position + pointA->GetComponent<PointColliderComponent>()->m_Offset) - (pointB->m_Transform.position + pointB->GetComponent<PointColliderComponent>()->m_Offset);
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>((pointA->m_Transform.position + pointA->GetComponent<PointColliderComponent>()->m_Offset) - (pointB->m_Transform.position + pointB->GetComponent<PointColliderComponent>()->m_Offset)).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PointToLine(GameObjectEntity* pointA, GameObjectEntity* lineB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	pointA->GetComponent<PointColliderComponent>()->m_HasCollided = false;
	lineB->GetComponent<LineColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_LineBStart = lineB->GetComponent<LineColliderComponent>()->m_LineStartPosition;
	OKVector2<float> t_LineBEnd = lineB->GetComponent<LineColliderComponent>()->m_LineEndPosition;

	// NOTE: Distance Point from Start of Line
	float PointOneDistX = pointA->m_Transform.position.x - t_LineBStart.x;
	float PointOneDistY = pointA->m_Transform.position.y - t_LineBStart.y;
	float distanceOne = OKVector2<float>(PointOneDistX, PointOneDistY).magnitude();

	// NOTE: Distance Point from End of Line
	float PointTwoDistX = pointA->m_Transform.position.x - t_LineBEnd.x;
	float PointTwoDistY = pointA->m_Transform.position.y - t_LineBEnd.y;
	float distanceTwo = OKVector2<float>(PointTwoDistX, PointTwoDistY).magnitude();

	// NOTE: Distance from Start to End
	float distX = t_LineBStart.x - t_LineBEnd.x;
	float distY = t_LineBStart.y - t_LineBEnd.y;
	float LineLength = OKVector2<float>(distX, distY).magnitude();

	// NOTE: Accuracy of colliding line
	float LineBuffer = 0.01f;

	// NOTE: Collision Check
	if ((distanceOne + distanceTwo) >= LineLength - LineBuffer && (distanceOne + distanceTwo) <= LineLength + LineBuffer)
	{
		pointA->GetComponent<PointColliderComponent>()->m_HasCollided = true;
		lineB->GetComponent<LineColliderComponent>()->m_HasCollided = true;

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true && lineB->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(lineB);
			lineB->GetComponent<LineColliderComponent>()->TriggerQuery(pointA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(lineB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (lineB->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			lineB->GetComponent<LineColliderComponent>()->TriggerQuery(pointA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		// FIXME
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = pointA->m_Transform.position - t_LineBEnd;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointA->m_Transform.position - t_LineBEnd).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PointToCircle(GameObjectEntity* pointA, GameObjectEntity* circleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	pointA->GetComponent<PointColliderComponent>()->m_HasCollided = false;
	circleB->GetComponent<CircleColliderComponent>()->m_HasCollided = false;

	// NOTE: Work out Distance between colliders
	float distX = (pointA->m_Transform.position.x + pointA->GetComponent<PointColliderComponent>()->m_Offset.x) - (circleB->m_Transform.position.x + circleB->GetComponent<CircleColliderComponent>()->m_Offset.x);
	float distY = (pointA->m_Transform.position.y + pointA->GetComponent<PointColliderComponent>()->m_Offset.y) - (circleB->m_Transform.position.y + circleB->GetComponent<CircleColliderComponent>()->m_Offset.y);
	float distance = OKVector2<float>(distX, distY).magnitude();

	if (distance <= circleB->GetComponent<CircleColliderComponent>()->m_Radius)
	{
		pointA->GetComponent<PointColliderComponent>()->m_HasCollided = true;
		circleB->GetComponent<CircleColliderComponent>()->m_HasCollided = true;

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true && circleB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(circleB);
			circleB->GetComponent<CircleColliderComponent>()->TriggerQuery(pointA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(circleB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (circleB->GetComponent<CircleColliderComponent>()->m_IsTrigger == true)
		{
			t_ColMani.m_HasCollision = true;
			circleB->GetComponent<CircleColliderComponent>()->TriggerQuery(pointA);
			return t_ColMani;
		}

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = (pointA->m_Transform.position + pointA->GetComponent<PointColliderComponent>()->m_Offset) - (circleB->m_Transform.position + circleB->GetComponent<CircleColliderComponent>()->m_Offset);
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>((pointA->m_Transform.position + pointA->GetComponent<PointColliderComponent>()->m_Offset) - (circleB->m_Transform.position + circleB->GetComponent<CircleColliderComponent>()->m_Offset)).magnitude();

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PointToRectangle(GameObjectEntity* pointA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	pointA->GetComponent<PointColliderComponent>()->m_HasCollided = false;
	rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = false;

	const OKVector2<float> t_tempPointPosition = pointA->m_Transform.position + pointA->GetComponent<PointColliderComponent>()->m_Offset;

	const OKVector2<float> t_tempRecPosition = rectB->m_Transform.position + rectB->GetComponent<RectangleColliderComponent>()->m_Offset - (rectB->GetComponent<RectangleColliderComponent>()->m_Scale / 2.f);
	const OKVector2<float> t_tempRecScale = rectB->GetComponent<RectangleColliderComponent>()->m_Scale;


	if (t_tempPointPosition.x >= t_tempRecPosition.x &&
		t_tempPointPosition.x <= t_tempRecPosition.x + t_tempRecScale.x &&
		t_tempPointPosition.y >= t_tempRecPosition.y &&
		t_tempPointPosition.y <= t_tempRecPosition.y + t_tempRecScale.y)
	{
		pointA->GetComponent<PointColliderComponent>()->m_HasCollided = true;
		rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = true;

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true && rectB->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(rectB);
			rectB->GetComponent<RectangleColliderComponent>()->TriggerQuery(pointA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(rectB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (rectB->GetComponent<RectangleColliderComponent>()->m_IsTrigger == true)
		{
			rectB->GetComponent<RectangleColliderComponent>()->TriggerQuery(pointA);
			t_ColMani.m_HasCollision = true;
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

	capsuleB->GetComponent<CapsuleColliderComponent>()->m_HasCollided = false;
	pointA->GetComponent<PointColliderComponent>()->m_HasCollided = false;

	const OKVector2<float> t_tempPointPositionA = pointA->m_Transform.position + pointA->GetComponent<PointColliderComponent>()->m_Offset;

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capsuleB->m_Transform.position.x + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.x - (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f);
		t_tempMiddleRectPosition.y = capsuleB->m_Transform.position.y + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.y - (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 4.f);

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width;
		t_tempMiddleRectScale.y = capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f;

		t_ColMani = S_PointToRectangle(t_tempPointPositionA, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			capsuleB->GetComponent<CapsuleColliderComponent>()->m_HasCollided = true;
			pointA->GetComponent<PointColliderComponent>()->m_HasCollided = true;

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true && pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(pointA);
				pointA->GetComponent<PointColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(pointA);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
			{
				pointA->GetComponent<PointColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capsuleB->m_Transform.position.x + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.x;
		t_tempTopCirclePosition.y = (capsuleB->m_Transform.position.y + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 4.f) + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.y;

		const float t_tempTopCircleRadius = capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f;

		t_ColMani = S_PointToCircle(t_tempPointPositionA, t_tempTopCirclePosition, t_tempTopCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			capsuleB->GetComponent<CapsuleColliderComponent>()->m_HasCollided = true;
			pointA->GetComponent<PointColliderComponent>()->m_HasCollided = true;

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true && pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(pointA);
				pointA->GetComponent<PointColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(pointA);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
			{
				pointA->GetComponent<PointColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = capsuleB->m_Transform.position.x + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.x;
		t_tempBottomCirclePosition.y = (capsuleB->m_Transform.position.y - capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 4.f) + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.y;

		const float t_tempBottomCircleRadius = capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f;

		t_ColMani = S_PointToCircle(t_tempPointPositionA, t_tempBottomCirclePosition, t_tempBottomCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			capsuleB->GetComponent<CapsuleColliderComponent>()->m_HasCollided = true;
			pointA->GetComponent<PointColliderComponent>()->m_HasCollided = true;

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true && pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(pointA);
				pointA->GetComponent<PointColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(pointA);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
			{
				pointA->GetComponent<PointColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::PointToOrientedRectangle(GameObjectEntity* pointA, GameObjectEntity* OrRectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	pointA->GetComponent<PointColliderComponent>()->m_HasCollided = false;
	OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_tempPointPosition = pointA->m_Transform.position + pointA->GetComponent<PointColliderComponent>()->m_Offset;

	OKVector2<float> t_tempOrRectPosition = OrRectB->m_Transform.position + OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_Offset;
	OKVector2<float> t_tempOrRectScale = OrRectB->m_Transform.scale * OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_Scale;

	OKVector2<float> Rad = t_tempPointPosition - t_tempOrRectPosition;
	float theta = -DEG2RAD * OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_Rotation;

	float zRotation2x2[] = {
		std::cosf(theta), std::sinf(theta),
		-std::sinf(theta), std::cosf(theta)
	};

	Multiply(Rad.asArray(), OKVector2<float>(Rad.x, Rad.y).asArray(), 1, 2, zRotation2x2, 2, 2);

	t_ColMani = S_PointToRectangle(Rad + (OrRectB->m_Transform.scale / 2.f), OKVector2<float>(0.f, 0.f), t_tempOrRectScale);

	if (t_ColMani.m_HasCollision)
	{
		pointA->GetComponent<PointColliderComponent>()->m_HasCollided = true;
		OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = true;

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true && OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(OrRectB);
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(pointA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (pointA->GetComponent<PointColliderComponent>()->m_IsTrigger == true)
		{
			pointA->GetComponent<PointColliderComponent>()->TriggerQuery(OrRectB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(pointA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::LineToLine(GameObjectEntity* lineA, GameObjectEntity* lineB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	lineA->GetComponent<LineColliderComponent>()->m_HasCollided = false;
	lineB->GetComponent<LineColliderComponent>()->m_HasCollided = false;

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
		lineA->GetComponent<LineColliderComponent>()->m_HasCollided = true;
		lineB->GetComponent<LineColliderComponent>()->m_HasCollided = true;

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true && lineB->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(lineB);
			lineB->GetComponent<LineColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(lineB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (lineB->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			lineB->GetComponent<LineColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionPoints[0] = OKVector2<float>(intersectionX, intersectionY);
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionPoints[0];
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = t_ColMani.m_CollisionPoints[0].magnitude();

		return t_ColMani;
	};

	return t_ColMani;
}

CollisionManifold CollisionManager::LineToCircle(GameObjectEntity* lineA, GameObjectEntity* circB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	lineA->GetComponent<LineColliderComponent>()->m_HasCollided = false;
	circB->GetComponent<CircleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_tempLineStartA = lineA->GetComponent<LineColliderComponent>()->m_LineStartPosition;
	OKVector2<float> t_tempLineEndA = lineA->GetComponent<LineColliderComponent>()->m_LineEndPosition;

	OKVector2<float> t_tempCircPositionB = circB->m_Transform.position + circB->GetComponent<CircleColliderComponent>()->m_Offset;
	float t_tempCircRadiusB = circB->GetComponent<CircleColliderComponent>()->m_Radius;

	// NOTE: Check if its already inside the circle

	bool insideOne = S_PointToCircle(t_tempLineStartA, t_tempCircPositionB, t_tempCircRadiusB).m_HasCollision;
	bool insideTwo = S_PointToCircle(t_tempLineEndA, t_tempCircPositionB, t_tempCircRadiusB).m_HasCollision;

	if (insideOne || insideTwo)
	{
		lineA->GetComponent<LineColliderComponent>()->m_HasCollided = true;
		circB->GetComponent<CircleColliderComponent>()->m_HasCollided = true;

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempLineStartA - t_tempCircPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempLineStartA - t_tempCircPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}


	// NOTE: Get Length of Circle
	float distX = t_tempLineStartA.x - t_tempLineEndA.x;
	float distY = t_tempLineStartA.y - t_tempLineEndA.y;
	float length = sqrt((distX * distX) + (distY * distY));

	float dot = ( ((t_tempCircPositionB.x - t_tempLineStartA.x) * (t_tempLineEndA.x - t_tempLineStartA.x)) +  ((t_tempCircPositionB.y - t_tempLineStartA.y) * (t_tempLineEndA.y - t_tempLineStartA.y))) / (length * length);

	float closestX = t_tempLineStartA.x + (dot * (t_tempLineEndA.x - t_tempLineStartA.x));
	float closestY = t_tempLineStartA.y + (dot * (t_tempLineEndA.y - t_tempLineStartA.y));

	CollisionManifold onSegment = S_PointToLine(OKVector2<float>(closestX, closestY), t_tempLineStartA, t_tempLineEndA);

	if (!onSegment.m_HasCollision)
	{
		lineA->GetComponent<LineColliderComponent>()->m_HasCollided = false;
		circB->GetComponent<CircleColliderComponent>()->m_HasCollided = false;

		return t_ColMani;
	}

	distX = closestX - t_tempCircPositionB.x;
	distY = closestY - t_tempCircPositionB.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	DrawCircle(closestX, closestY, 2.f, ORANGE);

	if (distance <= t_tempCircRadiusB)
	{
		lineA->GetComponent<LineColliderComponent>()->m_HasCollided = true;
		circB->GetComponent<CircleColliderComponent>()->m_HasCollided = true;

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = OKVector2<float>(closestX, closestY) - t_tempCircPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise() / t_tempCircRadiusB;
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(OKVector2<float>(closestX, closestY) - t_tempCircPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = OKVector2<float>(closestX, closestY);

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::LineToRectangle(GameObjectEntity* lineA, GameObjectEntity* rectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	lineA->GetComponent<LineColliderComponent>()->m_HasCollided = false;
	rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_tempRectPosition = rectB->m_Transform.position + rectB->GetComponent<RectangleColliderComponent>()->m_Offset;
	OKVector2<float> t_tempRectHalfScale = rectB->GetComponent<RectangleColliderComponent>()->m_Scale / 2.f;

	OKVector2<float> t_tempLineStartA = lineA->GetComponent<LineColliderComponent>()->m_LineStartPosition;
	OKVector2<float> t_tempLineEndA = lineA->GetComponent<LineColliderComponent>()->m_LineEndPosition;

	// NOTE: Left Line
	OKVector2<float> tempLeftPosStart = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempLeftPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	CollisionManifold t_Left = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempLeftPosStart, tempLeftPosEnd);

	// NOTE: Right Line
	OKVector2<float> tempRightPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempRightPosEnd = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	CollisionManifold t_Right = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempRightPosStart, tempRightPosEnd);

	// NOTE: Top Line
	OKVector2<float> tempTopPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempTopPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	CollisionManifold t_Top = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempTopPosStart, tempTopPosEnd);

	// NOTE: Bottom Line
	OKVector2<float> tempBottomPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	OKVector2<float> tempBottomPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	CollisionManifold t_Bottom = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempBottomPosStart, tempBottomPosEnd);


	if (t_Left.m_HasCollision == true ||
		t_Right.m_HasCollision == true ||
		t_Top.m_HasCollision == true ||
		t_Bottom.m_HasCollision == true)
	{
		lineA->GetComponent<LineColliderComponent>()->m_HasCollided = true;
		rectB->GetComponent<RectangleColliderComponent>()->m_HasCollided = true;

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempLineStartA - t_tempRectPosition;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempLineStartA - t_tempRectPosition).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::LineToOrientedRectangle(GameObjectEntity* lineA, GameObjectEntity* OrRectB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	lineA->GetComponent<LineColliderComponent>()->m_HasCollided = false;
	OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = false;

	OKVector2<float> t_tempLineStart = lineA->m_Transform.position + lineA->GetComponent<LineColliderComponent>()->m_LineStartPosition;
	OKVector2<float> t_tempLineEnd = lineA->m_Transform.position + lineA->GetComponent<LineColliderComponent>()->m_LineEndPosition;

	OKVector2<float> t_tempOrRectPosition = OrRectB->m_Transform.position + OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_Offset;
	OKVector2<float> t_tempOrRectScale = OrRectB->m_Transform.scale * OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_Scale;

	float t_tempOrRectRotation = OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_Rotation * DEG2RAD;
	OKVector2<float> t_tempOrRectHalfExtents = t_tempOrRectScale / 2.f;

	// NOTE: Point Generationb
	#pragma region NewPointsCalculations

	OKVector2<float> t_AnglePointOne;
	OKVector2<float> t_tempPointOne = OKVector2<float>(t_tempOrRectPosition.x - t_tempOrRectHalfExtents.x, t_tempOrRectPosition.y + t_tempOrRectHalfExtents.y); // Top Left
	t_AnglePointOne.x = t_tempPointOne.x * cosf(t_tempOrRectRotation) - t_tempPointOne.y * sinf(t_tempOrRectRotation);
	t_AnglePointOne.y = t_tempPointOne.x * sinf(t_tempOrRectRotation) + t_tempPointOne.y * cosf(t_tempOrRectRotation);

	OKVector2<float> t_AnglePointTwo;
	OKVector2<float> t_tempPointTwo = OKVector2<float>(t_tempOrRectPosition.x + t_tempOrRectHalfExtents.x, t_tempOrRectPosition.y + t_tempOrRectHalfExtents.y); // Top Right
	t_AnglePointTwo.x = t_tempPointTwo.x * cosf(t_tempOrRectRotation) - t_tempPointTwo.y * sinf(t_tempOrRectRotation);
	t_AnglePointTwo.y = t_tempPointTwo.x * sinf(t_tempOrRectRotation) + t_tempPointTwo.y * cosf(t_tempOrRectRotation);
	
	OKVector2<float> t_AnglePointThree;
	OKVector2<float> t_tempPointThree = OKVector2<float>(t_tempOrRectPosition.x - t_tempOrRectHalfExtents.x, t_tempOrRectPosition.y - t_tempOrRectHalfExtents.y); // Bottom Left
	t_AnglePointThree.x = t_tempPointThree.x * cosf(t_tempOrRectRotation) - t_tempPointThree.y * sinf(t_tempOrRectRotation);
	t_AnglePointThree.y = t_tempPointThree.x * sinf(t_tempOrRectRotation) + t_tempPointThree.y * cosf(t_tempOrRectRotation);
	
	OKVector2<float> t_AnglePointFour;
	OKVector2<float> t_tempPointFour = OKVector2<float>(t_tempOrRectPosition.x + t_tempOrRectHalfExtents.x, t_tempOrRectPosition.y - t_tempOrRectHalfExtents.y); // Bottom Right
	t_AnglePointFour.x = t_tempPointFour.x * cosf(t_tempOrRectRotation) - t_tempPointFour.y * sinf(t_tempOrRectRotation);
	t_AnglePointFour.y = t_tempPointFour.x * sinf(t_tempOrRectRotation) + t_tempPointFour.y * cosf(t_tempOrRectRotation);
	
	#pragma endregion

	// Top left & Top Right
	t_ColMani = S_LineToLine(t_tempLineStart, t_tempLineEnd, t_AnglePointOne + t_tempOrRectScale, t_AnglePointTwo + t_tempOrRectScale);
	DrawLineV(t_AnglePointOne.ConvertToVec2(), t_AnglePointTwo.ConvertToVec2(), GREEN);
	if (t_ColMani.m_HasCollision)
	{
		lineA->GetComponent<LineColliderComponent>()->m_HasCollided = false;
		OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = false;

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true && OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(OrRectB);
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(OrRectB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		return t_ColMani;
	}
	
	// Top Right & Bottom Right
	t_ColMani = S_LineToLine(t_tempLineStart, t_tempLineEnd, t_AnglePointTwo + t_tempOrRectScale, t_AnglePointFour + t_tempOrRectScale);
	DrawLineV(t_AnglePointTwo.ConvertToVec2(), t_AnglePointFour.ConvertToVec2(), GREEN);
	if (t_ColMani.m_HasCollision)
	{
		lineA->GetComponent<LineColliderComponent>()->m_HasCollided = false;
		OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = false;

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true && OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(OrRectB);
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(OrRectB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		return t_ColMani;
	}

	// Bottom Right & Bottom Left
	t_ColMani = S_LineToLine(t_tempLineStart, t_tempLineEnd, t_AnglePointFour + t_tempOrRectScale, t_AnglePointThree + t_tempOrRectScale);
	DrawLineV(t_AnglePointFour.ConvertToVec2(), t_AnglePointThree.ConvertToVec2(), GREEN);
	if (t_ColMani.m_HasCollision)
	{
		lineA->GetComponent<LineColliderComponent>()->m_HasCollided = false;
		OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = false;

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true && OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(OrRectB);
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(OrRectB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		return t_ColMani;
	}

	// Bottom Left & Top Left
	t_ColMani = S_LineToLine(t_tempLineStart, t_tempLineEnd, t_AnglePointThree + t_tempOrRectScale, t_AnglePointOne + t_tempOrRectScale);
	DrawLineV(t_AnglePointThree.ConvertToVec2(), t_AnglePointOne.ConvertToVec2(), GREEN);
	if (t_ColMani.m_HasCollision)
	{
		lineA->GetComponent<LineColliderComponent>()->m_HasCollided = false;
		OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_HasCollided = false;

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true && OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(OrRectB);
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
		{
			lineA->GetComponent<LineColliderComponent>()->TriggerQuery(OrRectB);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		if (OrRectB->GetComponent<OrientedRectangleColliderComponent>()->m_IsTrigger == true)
		{
			OrRectB->GetComponent<OrientedRectangleColliderComponent>()->TriggerQuery(lineA);
			t_ColMani.m_HasCollision = true;
			return t_ColMani;
		}

		return t_ColMani;
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::LineToCapsule(GameObjectEntity* lineA, GameObjectEntity* capsuleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempLineStartA = lineA->GetComponent<LineColliderComponent>()->m_LineStartPosition;
	const OKVector2<float> t_tempLineEndA = lineA->GetComponent<LineColliderComponent>()->m_LineEndPosition;

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capsuleB->m_Transform.position.x + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.x - (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f);
		t_tempMiddleRectPosition.y = capsuleB->m_Transform.position.y + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.y - (capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 4.f);

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width;
		t_tempMiddleRectScale.y = capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f;

		t_ColMani = S_LineToRectangle(t_tempLineStartA, t_tempLineEndA, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			capsuleB->GetComponent<CapsuleColliderComponent>()->m_HasCollided = true;
			lineA->GetComponent<LineColliderComponent>()->m_HasCollided = true;

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true && lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(lineA);
				lineA->GetComponent<LineColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(lineA);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
			{
				lineA->GetComponent<LineColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capsuleB->m_Transform.position.x + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.x;
		t_tempTopCirclePosition.y = (capsuleB->m_Transform.position.y + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 4.f) + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.y;

		const float t_tempTopCircleRadius = capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f;

		t_ColMani = S_LineToCircle(t_tempLineStartA, t_tempLineEndA, t_tempTopCirclePosition, t_tempTopCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			capsuleB->GetComponent<CapsuleColliderComponent>()->m_HasCollided = true;
			lineA->GetComponent<LineColliderComponent>()->m_HasCollided = true;

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true && lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(lineA);
				lineA->GetComponent<LineColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(lineA);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
			{
				lineA->GetComponent<LineColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = capsuleB->m_Transform.position.x + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.x;
		t_tempBottomCirclePosition.y = (capsuleB->m_Transform.position.y - capsuleB->GetComponent<CapsuleColliderComponent>()->m_Height / 4.f) + capsuleB->GetComponent<CapsuleColliderComponent>()->m_Offset.y;

		const float t_tempBottomCircleRadius = capsuleB->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f;

		t_ColMani = S_LineToCircle(t_tempLineStartA, t_tempLineEndA, t_tempBottomCirclePosition, t_tempBottomCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			capsuleB->GetComponent<CapsuleColliderComponent>()->m_HasCollided = true;
			lineA->GetComponent<LineColliderComponent>()->m_HasCollided = true;

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true && lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(lineA);
				lineA->GetComponent<LineColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (capsuleB->GetComponent<CapsuleColliderComponent>()->m_IsTrigger == true)
			{
				capsuleB->GetComponent<CapsuleColliderComponent>()->TriggerQuery(lineA);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			if (lineA->GetComponent<LineColliderComponent>()->m_IsTrigger == true)
			{
				lineA->GetComponent<LineColliderComponent>()->TriggerQuery(capsuleB);
				t_ColMani.m_HasCollision = true;
				return t_ColMani;
			}

			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::S_RectangleToRectangle(OKVector2<float> recPositionA, OKVector2<float> recScaleA, OKVector2<float> recPositionB, OKVector2<float> recScaleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> RectCentreA = recPositionA - (recScaleA / 2.f); // Centre A
	OKVector2<float> RectScaleA = recScaleA;
	OKVector2<float> RectScaleHalfA = RectScaleA / 2.f;
	OKVector2<float> NearPointA = OKVector2<float>(0, 0);

	OKVector2<float> RectCentreB = recPositionB - (recScaleB / 2.f); // Centre B
	OKVector2<float> RectScaleB = recScaleB;
	OKVector2<float> RectScaleHalfB = RectScaleB / 2.f;
	OKVector2<float> NearPointB = OKVector2<float>(0, 0);

	if (RectCentreA.x < RectCentreB.x)
	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x, RectCentreB.y),
			OKVector2<float>(RectCentreB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(0, 1)
		);

		NearPointB.y = LeftSide.y;
	}
	else if (RectCentreA.x > RectCentreB.x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y),
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(0, 1)
		);

		NearPointB.y = RightSide.y;
	}

	if (RectCentreA.y < RectCentreB.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x, RectCentreB.y),
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y),
			OKVector2<float>(1, 0)
		);

		NearPointB.x = TopSide.x;
	}
	else if (RectCentreA.y > RectCentreB.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(1, 0)
		);

		NearPointB.x = BottomSide.x;
	}

	if (RectCentreB.x < RectCentreA.x)

	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x, RectCentreA.y),
			OKVector2<float>(RectCentreA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(0, 1)
		);

		NearPointA.y = LeftSide.y;
	}
	else if (RectCentreB.x > RectCentreA.x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y),
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(0, 1)
		);

		NearPointA.y = RightSide.y;
	}

	if (RectCentreB.y < RectCentreA.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x, RectCentreA.y),
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y),
			OKVector2<float>(1, 0)
		);

		NearPointA.x = TopSide.x;
	}
	else if (RectCentreB.y > RectCentreA.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(1, 0)
		);

		NearPointA.x = BottomSide.x;
	}

	DrawCircleV(NearPointB.ConvertToVec2(), 1.f, YELLOW);
	DrawCircleV(NearPointA.ConvertToVec2(), 1.f, YELLOW);

	CollisionManifold t_tempMani = S_CircleToCircle(NearPointA, 0.5f, NearPointB, 0.5f);

	if (t_tempMani.m_HasCollision)
	{
		return t_tempMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_RectangleToRectangle(float recXA, float recYA, float recWidthA, float recHeightA, float recXB, float recYB, float recWidthB, float recHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> RectCentreA = OKVector2<float>(recXA, recYA) - (OKVector2<float>(recWidthA, recHeightA) / 2.f); // Centre A
	OKVector2<float> RectScaleA = OKVector2<float>(recWidthA, recHeightA);
	OKVector2<float> RectScaleHalfA = RectScaleA / 2.f;
	OKVector2<float> NearPointA = OKVector2<float>(0, 0);

	OKVector2<float> RectCentreB = OKVector2<float>(recXB, recYB) - (OKVector2<float>(recWidthB, recHeightB) / 2.f); // Centre B
	OKVector2<float> RectScaleB = OKVector2<float>(recWidthB, recHeightB);
	OKVector2<float> RectScaleHalfB = RectScaleB / 2.f;
	OKVector2<float> NearPointB = OKVector2<float>(0, 0);

	if (RectCentreA.x < RectCentreB.x)
	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x, RectCentreB.y),
			OKVector2<float>(RectCentreB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(0, 1)
		);

		NearPointB.y = LeftSide.y;
	}
	else if (RectCentreA.x > RectCentreB.x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y),
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(0, 1)
		);

		NearPointB.y = RightSide.y;
	}

	if (RectCentreA.y < RectCentreB.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x, RectCentreB.y),
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y),
			OKVector2<float>(1, 0)
		);

		NearPointB.x = TopSide.x;
	}
	else if (RectCentreA.y > RectCentreB.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			RectCentreB,
			RectCentreA,
			OKVector2<float>(RectCentreB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(RectCentreB.x + RectScaleB.x, RectCentreB.y + RectScaleB.y),
			OKVector2<float>(1, 0)
		);

		NearPointB.x = BottomSide.x;
	}

	if (RectCentreB.x < RectCentreA.x)

	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x, RectCentreA.y),
			OKVector2<float>(RectCentreA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(0, 1)
		);

		NearPointA.y = LeftSide.y;
	}
	else if (RectCentreB.x > RectCentreA.x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y),
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(0, 1)
		);

		NearPointA.y = RightSide.y;
	}

	if (RectCentreB.y < RectCentreA.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x, RectCentreA.y),
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y),
			OKVector2<float>(1, 0)
		);

		NearPointA.x = TopSide.x;
	}
	else if (RectCentreB.y > RectCentreA.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			RectCentreA,
			RectCentreB,
			OKVector2<float>(RectCentreA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(RectCentreA.x + RectScaleA.x, RectCentreA.y + RectScaleA.y),
			OKVector2<float>(1, 0)
		);

		NearPointA.x = BottomSide.x;
	}

	CollisionManifold t_tempMani = S_CircleToCircle(NearPointA, 0.5f, NearPointB, 0.5f);

	if (t_tempMani.m_HasCollision)
	{
		return t_tempMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_CircleToCircle(OKVector2<float> circPositionA, float circRadiusA, OKVector2<float> circPositionB, float circRadiusB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> distance = circPositionA - circPositionB;
	float radii_sum = circRadiusA + circRadiusB;

	if (distance.magnitude() <= radii_sum)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = distance.normalise() * -1;// / radii_sum;
		t_ColMani.m_PenetrationDepth = distance.magnitude() - radii_sum;
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		DrawCircleV(circPositionB.ConvertToVec2(), 1.f, YELLOW);

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_CircleToCircle(float circXA, float circYA, float circRadiusA, float circXB, float circYB, float circRadiusB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> distance = OKVector2<float>(circXA, circYA) - OKVector2<float>(circXB, circYB);
	float radii_sum = circRadiusA + circRadiusB;

	if (distance.magnitude() <= radii_sum)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = distance.normalise() * -1;
		t_ColMani.m_PenetrationDepth = distance.magnitude() - radii_sum;
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_CircleToRectangle(OKVector2<float> circPositionA, float circRadiusA, OKVector2<float> recPositionB, OKVector2<float> recScaleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> t_tempCircPositionA = circPositionA;
	float t_tempCircRadius = circRadiusA;

	OKVector2<float> RectCentre = recPositionB;
	OKVector2<float> RectScale = recScaleB;
	OKVector2<float> TopLeftCorner = RectCentre - (RectScale / 2.f);

	OKVector2<float> NearPoint = OKVector2<float>(0, 0);

	if (t_tempCircPositionA.x < TopLeftCorner.x)
	{
		OKVector2<float> LeftSide = ProjectPointOntoLine(
			TopLeftCorner,
			t_tempCircPositionA,
			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y),
			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y + RectScale.y),
			OKVector2<float>(0, 1)
		);

		NearPoint.y = LeftSide.y;
	}
	else if (t_tempCircPositionA.x > TopLeftCorner.x)
	{
		OKVector2<float> RightSide = ProjectPointOntoLine(
			TopLeftCorner,
			t_tempCircPositionA,
			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y),
			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y + RectScale.y),
			OKVector2<float>(0, 1)
		);

		NearPoint.y = RightSide.y;
	}

	if (t_tempCircPositionA.y < RectCentre.y)
	{
		OKVector2<float> TopSide = ProjectPointOntoLine(
			TopLeftCorner,
			t_tempCircPositionA,
			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y),
			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y),
			OKVector2<float>(1, 0)
		);

		NearPoint.x = TopSide.x;
	}
	else if (t_tempCircPositionA.y > RectCentre.y)
	{
		OKVector2<float> BottomSide = ProjectPointOntoLine(
			TopLeftCorner,
			t_tempCircPositionA,
			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y + RectScale.y),
			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y + RectScale.y),
			OKVector2<float>(1, 0)
		);

		NearPoint.x = BottomSide.x;
	}

	return S_CircleToCircle(t_tempCircPositionA, circRadiusA, NearPoint, 1.f);
}

CollisionManifold CollisionManager::S_CircleToRectangle(float circXA, float circYA, float circRadiusA, float recXB, float recYB, float recWidthB, float recHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> t_tempRectPosition = OKVector2<float>(recXB, recYB);
	OKVector2<float> t_tempRectScale = OKVector2<float>(recWidthB, recHeightB);
	OKVector2<float> t_tempRectHalfScale = t_tempRectScale / 2.f;

	OKVector2<float> t_tempCircPositionA = OKVector2<float>(circXA, circYA);
	float t_tempCircRadius = circRadiusA;

	// NOTE: Check if the object is just in the rectangle
	#pragma region Check If In EachOther
	if (t_tempCircPositionA.x >= t_tempRectPosition.x - t_tempRectHalfScale.x &&
		t_tempCircPositionA.x <= t_tempRectPosition.x + t_tempRectScale.x - t_tempRectHalfScale.x &&
		t_tempCircPositionA.y >= t_tempRectPosition.y - t_tempRectHalfScale.y &&
		t_tempCircPositionA.y <= t_tempRectPosition.y + t_tempRectScale.y - t_tempRectHalfScale.y)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempCircPositionA - t_tempRectPosition;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempCircPositionA - t_tempRectPosition).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
		return t_ColMani;
	}
	#pragma endregion

	// NOTE: Top Line
	#pragma region TOP LINE COLLISION DETECTION
	{
		OKVector2<float> tempTopPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
		OKVector2<float> tempTopPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
		CollisionManifold t_TopLine = S_LineToCircle(tempTopPosStart, tempTopPosEnd, t_tempCircPositionA, t_tempCircRadius);

		if (t_TopLine.m_HasCollision)
		{
			t_ColMani.m_HasCollision = true;
			t_ColMani.m_CollisionNormal = t_tempCircPositionA - t_TopLine.m_CollisionPoints[0];
			t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
			t_ColMani.m_ContactPointAmount = 1;
			t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempCircPositionA - t_TopLine.m_CollisionPoints[0]).magnitude();
			t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
			return t_ColMani;
		}
	}
	#pragma endregion

	// NOTE: Bottom Line
	#pragma region BOTTOM LINE COLLISION DETECTION
	{
		OKVector2<float> tempBottomPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
		OKVector2<float> tempBottomPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
		CollisionManifold t_BottomLine = S_LineToCircle(tempBottomPosStart, tempBottomPosEnd, t_tempCircPositionA, t_tempCircRadius);

		if (t_BottomLine.m_HasCollision)
		{
			t_ColMani.m_HasCollision = true;
			t_ColMani.m_CollisionNormal = t_tempCircPositionA - t_BottomLine.m_CollisionPoints[0];
			t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
			t_ColMani.m_ContactPointAmount = 1;
			t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempCircPositionA - t_BottomLine.m_CollisionPoints[0]).magnitude();
			t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
			return t_ColMani;
		}
	}
	#pragma endregion

	// NOTE: Left Line
	#pragma region	LEFT LINE COLLISION DETECTION
	{
		OKVector2<float> tempLeftPosStart = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
		OKVector2<float> tempLeftPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
		CollisionManifold t_LeftLine = S_LineToCircle(tempLeftPosStart, tempLeftPosEnd, t_tempCircPositionA, t_tempCircRadius);

		if (t_LeftLine.m_HasCollision)
		{
			t_ColMani.m_HasCollision = true;
			t_ColMani.m_CollisionNormal = t_tempCircPositionA - t_LeftLine.m_CollisionPoints[0];
			t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
			t_ColMani.m_ContactPointAmount = 1;
			t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempCircPositionA - t_LeftLine.m_CollisionPoints[0]).magnitude();
			t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
			return t_ColMani;
		}
	}
	#pragma endregion

	// NOTE: Right Line
	#pragma region RIGHT LINE COLLISION DETECTION
	{
		OKVector2<float> tempRightPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
		OKVector2<float> tempRightPosEnd = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
		CollisionManifold t_RightLine = S_LineToCircle(tempRightPosStart, tempRightPosEnd, t_tempCircPositionA, t_tempCircRadius);

		if (t_RightLine.m_HasCollision)
		{
			t_ColMani.m_HasCollision = true;
			t_ColMani.m_CollisionNormal = t_tempCircPositionA - t_RightLine.m_CollisionPoints[0];
			t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
			t_ColMani.m_ContactPointAmount = 1;
			t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempCircPositionA - t_RightLine.m_CollisionPoints[0]).magnitude();
			t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
			return t_ColMani;

		}
	}
	#pragma endregion

	return t_ColMani;
}

CollisionManifold CollisionManager::S_CapsuleToCircle(OKVector2<float> capPositionA, float capWidthA, float capHeightA, OKVector2<float> circPositionB, float circRadiusB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempCirclePositionB = circPositionB;
	const float t_tempCircleRadiusB = circRadiusB;

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capPositionA.x;
		t_tempMiddleRectPosition.y = capPositionA.y;

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capWidthA;
		t_tempMiddleRectScale.y = capHeightA / 2.f;

		t_ColMani = S_CircleToRectangle(t_tempCirclePositionB, t_tempCircleRadiusB, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capPositionA.x;
		t_tempTopCirclePosition.y = (capPositionA.y + capHeightA / 4.f);

		const float t_tempTopCircleRadius = capWidthA / 2.f;

		t_ColMani = S_CircleToCircle(t_tempTopCirclePosition, t_tempTopCircleRadius, t_tempCirclePositionB, t_tempCircleRadiusB);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = circPositionB.x;
		t_tempBottomCirclePosition.y = (circPositionB.y - capHeightA / 4.f);

		const float t_tempBottomCircleRadius = capWidthA / 2.f;

		t_ColMani = S_CircleToCircle(t_tempBottomCirclePosition, t_tempBottomCircleRadius, t_tempCirclePositionB, t_tempCircleRadiusB);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::S_CapsuleToCircle(float capXA, float capYA, float capWidthA, float capHeightA, float circXB, float circYB, float circRadiusB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempCirclePositionB = OKVector2<float>(circXB, circYB);
	const float t_tempCircleRadiusB = circRadiusB;

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capXA;
		t_tempMiddleRectPosition.y = capYA;

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capWidthA;
		t_tempMiddleRectScale.y = capHeightA / 2.f;

		t_ColMani = S_CircleToRectangle(t_tempCirclePositionB, t_tempCircleRadiusB, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capXA;
		t_tempTopCirclePosition.y = capYA + capHeightA / 4.f;

		const float t_tempTopCircleRadius = capWidthA / 2.f;

		t_ColMani = S_CircleToCircle(t_tempTopCirclePosition, t_tempTopCircleRadius, t_tempCirclePositionB, t_tempCircleRadiusB);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = circXB;
		t_tempBottomCirclePosition.y = circYB - capHeightA / 4.f;

		const float t_tempBottomCircleRadius = capWidthA / 2.f;

		t_ColMani = S_CircleToCircle(t_tempBottomCirclePosition, t_tempBottomCircleRadius, t_tempCirclePositionB, t_tempCircleRadiusB);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::S_CapsuleToRectangle(OKVector2<float> capPositionA, float capWidthA, float capHeightA, OKVector2<float> recPositionB, OKVector2<float> recScaleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempRectPositionB = recPositionB;
	const OKVector2<float> t_tempRectScaleB = recScaleB;

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capPositionA.x;
		t_tempMiddleRectPosition.y = capPositionA.y;

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capWidthA;
		t_tempMiddleRectScale.y = capHeightA / 2.f;

		t_ColMani = S_RectangleToRectangle(t_tempRectPositionB, t_tempRectScaleB, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capPositionA.x;
		t_tempTopCirclePosition.y = (capPositionA.y + capHeightA / 4.f);

		const float t_tempTopCircleRadius = capWidthA / 2.f;

		t_ColMani = S_CircleToRectangle(t_tempTopCirclePosition, t_tempTopCircleRadius, t_tempRectPositionB, t_tempRectScaleB);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = capPositionA.x;
		t_tempBottomCirclePosition.y = (capPositionA.y - capHeightA / 4.f);

		const float t_tempBottomCircleRadius = capWidthA / 2.f;

		t_ColMani = S_CircleToRectangle(t_tempBottomCirclePosition, t_tempBottomCircleRadius, t_tempRectPositionB, t_tempRectScaleB);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::S_CapsuleToRectangle(float capXA, float capYA, float capWidthA, float capHeightA, float recXB, float recYB, float recWidthB, float recHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempRectPositionB = OKVector2<float>(recXB, recYB);
	const OKVector2<float> t_tempRectScaleB = OKVector2<float>(recWidthB, recHeightB);

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capXA;
		t_tempMiddleRectPosition.y = capYA;

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capWidthA;
		t_tempMiddleRectScale.y = capHeightA / 2.f;

		t_ColMani = S_RectangleToRectangle(t_tempRectPositionB, t_tempRectScaleB, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capXA;
		t_tempTopCirclePosition.y = (capYA + capHeightA / 4.f);

		const float t_tempTopCircleRadius = capWidthA / 2.f;

		t_ColMani = S_CircleToRectangle(t_tempTopCirclePosition, t_tempTopCircleRadius, t_tempRectPositionB, t_tempRectScaleB);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = capXA;
		t_tempBottomCirclePosition.y = (capYA - capHeightA / 4.f);

		const float t_tempBottomCircleRadius = capWidthA / 2.f;

		t_ColMani = S_CircleToRectangle(t_tempBottomCirclePosition, t_tempBottomCircleRadius, t_tempRectPositionB, t_tempRectScaleB);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::S_CapsuleToCapsule(OKVector2<float> capPositionA, float capWidthA, float capHeightA, OKVector2<float> capPositionB, float capWidthB, float capHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// Capsule (A)
	// NOTE: Capsule Position and Variable(s)
	OKVector2<float> tip_a = OKVector2<float>(capPositionA.x, capPositionA.y + (capHeightA / 2.f) - (capWidthA / 2.f));
	OKVector2<float> base_a = OKVector2<float>(capPositionA.x, capPositionA.y - (capHeightA / 2.f) + (capWidthA / 2.f));
	float t_DistanceXA = tip_a.x - base_a.x;
	float t_DistanceYA = tip_a.y - base_a.y;
	float lenA = sqrt((t_DistanceXA * t_DistanceXA) + (t_DistanceYA * t_DistanceYA));
	float dotA = ((capPositionB.x - tip_a.x) * (base_a.x - tip_a.x)) + ((capPositionB.y - tip_a.y) * (base_a.y - tip_a.y)) / powf(lenA, 2);

	// Capsule (B)
	OKVector2<float> tip_b = OKVector2<float>(capPositionB.x, capPositionB.y + (capHeightB / 2.f) - (capWidthB / 2.f));
	OKVector2<float> base_b = OKVector2<float>(capPositionB.x, capPositionB.y - (capHeightB / 2.f) + (capWidthB / 2.f));
	float t_DistanceXB = tip_b.x - base_b.x;
	float t_DistanceYB = tip_b.y - base_b.y;
	float lenB = sqrt((t_DistanceXB * t_DistanceXB) + (t_DistanceYB * t_DistanceYB));
	float dotB = ((capPositionA.x - tip_b.x) * (base_b.x - tip_b.x)) + ((capPositionA.y - tip_b.y) * (base_b.y - tip_b.y)) / powf(lenB, 2);

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

	return t_ColMani = S_CircleToCircle(closest_point_A, capWidthA / 2.f, closest_point_B, capWidthB / 2.f);
}

CollisionManifold CollisionManager::S_CapsuleToCapsule(float capXA, float capYA, float capWidthA, float capHeightA, float capXB, float capYB, float capWidthB, float capHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// Capsule (A)
	// NOTE: Capsule Position and Variable(s)
	OKVector2<float> tip_a = OKVector2<float>(capXA, capYA + (capHeightA / 2.f) - (capWidthA / 2.f));
	OKVector2<float> base_a = OKVector2<float>(capXA, capYA - (capHeightA / 2.f) + (capWidthA / 2.f));
	float t_DistanceXA = tip_a.x - base_a.x;
	float t_DistanceYA = tip_a.y - base_a.y;
	float lenA = sqrt((t_DistanceXA * t_DistanceXA) + (t_DistanceYA * t_DistanceYA));
	float dotA = ((capXB - tip_a.x) * (base_a.x - tip_a.x)) + ((capYB - tip_a.y) * (base_a.y - tip_a.y)) / powf(lenA, 2);

	// Capsule (B)
	OKVector2<float> tip_b = OKVector2<float>(capXB, capYB + (capHeightB / 2.f) - (capWidthB / 2.f));
	OKVector2<float> base_b = OKVector2<float>(capXB, capYB - (capHeightB / 2.f) + (capWidthB / 2.f));
	float t_DistanceXB = tip_b.x - base_b.x;
	float t_DistanceYB = tip_b.y - base_b.y;
	float lenB = sqrt((t_DistanceXB * t_DistanceXB) + (t_DistanceYB * t_DistanceYB));
	float dotB = ((capXA - tip_b.x) * (base_b.x - tip_b.x)) + ((capYA - tip_b.y) * (base_b.y - tip_b.y)) / powf(lenB, 2);

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

	return t_ColMani = S_CircleToCircle(closest_point_A, capWidthA / 2.f, closest_point_B, capWidthB / 2.f);
}

CollisionManifold CollisionManager::S_PointToPoint(OKVector2<float> pointPositionA, OKVector2<float> pointPositionB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	if (pointPositionA == pointPositionB)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = pointPositionA - pointPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointPositionA - pointPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = pointPositionA;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_PointToPoint(float pointXA, float pointYA, float pointXB, float pointYB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> t_tempPositionA = OKVector2<float>(pointXA, pointYA);
	OKVector2<float> t_tempPositionB = OKVector2<float>(pointXB, pointYB);

	if (t_tempPositionA == t_tempPositionB)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempPositionA - t_tempPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempPositionA - t_tempPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_tempPositionA;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_PointToLine(OKVector2<float> pointPositionA, OKVector2<float> lineStartPositionB, OKVector2<float> lineEndPositionB)
{
	CollisionManifold t_ColMani;

	// NOTE: Distance Point from Start of Line
	float PointOneDistX = pointPositionA.x - lineStartPositionB.x;
	float PointOneDistY = pointPositionA.y - lineStartPositionB.y;
	float distanceOne = OKVector2<float>(PointOneDistX, PointOneDistY).magnitude();

	// NOTE: Distance Point from End of Line
	float PointTwoDistX = pointPositionA.x - lineEndPositionB.x;
	float PointTwoDistY = pointPositionA.y - lineEndPositionB.y;
	float distanceTwo = OKVector2<float>(PointTwoDistX, PointTwoDistY).magnitude();

	// NOTE: Distance from Start to End
	float distX = lineStartPositionB.x - lineEndPositionB.x;
	float distY = lineStartPositionB.y - lineEndPositionB.y;
	float LineLength = OKVector2<float>(distX, distY).magnitude();

	// NOTE: Accuracy of colliding line
	float LineBuffer = 0.1f;
	// float LineBuffer = 0.1f;

	// NOTE: Collision Check
	if ((distanceOne + distanceTwo) >= LineLength - LineBuffer && (distanceOne + distanceTwo) <= LineLength + LineBuffer)
	{
		// FIXME
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = pointPositionA;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointPositionA).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_PointToLine(float pointXA, float pointYA, float lineStartXB, float lineStartYB, float lineEndXB, float lineEndYB)
{
	CollisionManifold t_ColMani;

	OKVector2<float> t_tempPointPosition = OKVector2<float>(pointXA, pointYA);
	OKVector2<float> t_tempLineStart = OKVector2<float>(lineStartXB, lineStartYB);
	OKVector2<float> t_tempLineEnd = OKVector2<float>(lineEndXB, lineEndYB);

	// NOTE: Distance Point from Start of Line
	float PointOneDistX = t_tempPointPosition.x - t_tempLineStart.x;
	float PointOneDistY = t_tempPointPosition.y - t_tempLineStart.y;
	float distanceOne = OKVector2<float>(PointOneDistX, PointOneDistY).magnitude();

	// NOTE: Distance Point from End of Line
	float PointTwoDistX = t_tempPointPosition.x - t_tempLineEnd.x;
	float PointTwoDistY = t_tempPointPosition.y - t_tempLineEnd.y;
	float distanceTwo = OKVector2<float>(PointTwoDistX, PointTwoDistY).magnitude();

	// NOTE: Distance from Start to End
	float distX = t_tempLineStart.x - t_tempLineEnd.x;
	float distY = t_tempLineStart.y - t_tempLineEnd.y;
	float LineLength = OKVector2<float>(distX, distY).magnitude();

	// NOTE: Accuracy of colliding line
	float LineBuffer = 0.1f;

	// NOTE: Collision Check
	if ((distanceOne + distanceTwo) >= LineLength - LineBuffer && (distanceOne + distanceTwo) <= LineLength + LineBuffer)
	{
		// FIXME
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempPointPosition;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempPointPosition).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_PointToCircle(OKVector2<float> pointPositionA, OKVector2<float> circPositionB, float circRadiusB)
{
	CollisionManifold t_ColMani;

	// NOTE: Work out Distance between colliders
	float distX = pointPositionA.x - circPositionB.x;
	float distY = pointPositionA.y - circPositionB.y;
	float distance = OKVector2<float>(distX, distY).magnitude();

	if (distance <= circRadiusB)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = pointPositionA - circPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointPositionA - circPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_PointToCircle(float pointXA, float pointYA, float circXB, float circYB, float circRadiusB)
{
	CollisionManifold t_ColMani;

	// NOTE: Work out Distance between colliders
	float distX = pointXA - circXB;
	float distY = pointYA - circYB;
	float distance = OKVector2<float>(distX, distY).magnitude();

	if (distance <= circRadiusB)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = OKVector2<float>(pointXA, pointYA) - OKVector2<float>(circXB, circYB);
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(OKVector2<float>(pointXA, pointYA) - OKVector2<float>(circXB, circYB)).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;

	return CollisionManifold();
}

CollisionManifold CollisionManager::S_PointToRectangle(OKVector2<float> pointPositionA, OKVector2<float> recPositionB, OKVector2<float> recScaleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempPointPosition = pointPositionA;

	const OKVector2<float> t_tempRecPosition = recPositionB - (recScaleB / 2.f);
	const OKVector2<float> t_tempRecScale = recScaleB;

	if (t_tempPointPosition.x >= t_tempRecPosition.x &&
		t_tempPointPosition.x <= t_tempRecPosition.x + t_tempRecScale.x &&
		t_tempPointPosition.y >= t_tempRecPosition.y &&
		t_tempPointPosition.y <= t_tempRecPosition.y + t_tempRecScale.y)
	{
		
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = pointPositionA - recPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointPositionA - recPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_PointToRectangle(float pointXA, float pointYA, float recXB, float recYB, float recWidthB, float recHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempPointPosition = OKVector2<float>(pointXA, pointYA);

	const OKVector2<float> t_tempRecPosition = OKVector2<float>(recXB, recYB) - (OKVector2<float>(recWidthB, recHeightB) / 2.f);
	const OKVector2<float> t_tempRecScale = OKVector2<float>(recWidthB, recHeightB);

	if (t_tempPointPosition.x >= t_tempRecPosition.x &&
		t_tempPointPosition.x <= t_tempRecPosition.x + t_tempRecScale.x &&
		t_tempPointPosition.y >= t_tempRecPosition.y &&
		t_tempPointPosition.y <= t_tempRecPosition.y + t_tempRecScale.y)
	{

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = OKVector2<float>(pointXA, pointYA) - OKVector2<float>(recXB, recYB);
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(OKVector2<float>(pointXA, pointYA) - OKVector2<float>(recXB, recYB)).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_PointToCapsule(OKVector2<float> pointPositionA, OKVector2<float> capPositionB, float capWidthB, float capHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempPointPositionA = pointPositionA;

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capPositionB.x;
		t_tempMiddleRectPosition.y = capPositionB.y;

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capWidthB;
		t_tempMiddleRectScale.y = capHeightB / 2.f;

		t_ColMani = S_PointToRectangle(t_tempPointPositionA, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capPositionB.x;
		t_tempTopCirclePosition.y = (capPositionB.y + capHeightB / 4.f);

		const float t_tempTopCircleRadius = capWidthB / 2.f;

		t_ColMani = S_PointToCircle(t_tempPointPositionA, t_tempTopCirclePosition, t_tempTopCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = capPositionB.x;
		t_tempBottomCirclePosition.y = (capPositionB.y - capHeightB / 4.f);

		const float t_tempBottomCircleRadius = capWidthB / 2.f;

		t_ColMani = S_PointToCircle(t_tempPointPositionA, t_tempBottomCirclePosition, t_tempBottomCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::S_PointToCapsule(float pointXA, float pointYA, float capXB, float capYB, float capWidthB, float capHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempPointPositionA = OKVector2<float>(pointXA, pointYA);

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capXB;
		t_tempMiddleRectPosition.y = capYB;

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capWidthB;
		t_tempMiddleRectScale.y = capHeightB / 2.f;

		t_ColMani = S_PointToRectangle(t_tempPointPositionA, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capXB;
		t_tempTopCirclePosition.y = (capYB + capHeightB / 4.f);

		const float t_tempTopCircleRadius = capWidthB / 2.f;

		t_ColMani = S_PointToCircle(t_tempPointPositionA, t_tempTopCirclePosition, t_tempTopCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = capXB;
		t_tempBottomCirclePosition.y = (capYB - capHeightB / 4.f);

		const float t_tempBottomCircleRadius = capWidthB / 2.f;

		t_ColMani = S_PointToCircle(t_tempPointPositionA, t_tempBottomCirclePosition, t_tempBottomCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::S_LineToLine(OKVector2<float> lineStartPositionA, OKVector2<float> lineEndPositionA, OKVector2<float> lineStartPositionB, OKVector2<float> lineEndPositionB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const float x1 = lineStartPositionA.x;
	const float y1 = lineStartPositionA.y;

	const float x2 = lineEndPositionA.x;
	const float y2 = lineEndPositionA.y;

	const float x3 = lineStartPositionB.x;
	const float y3 = lineStartPositionB.y;

	const float x4 = lineEndPositionB.x;
	const float y4 = lineEndPositionB.y;

	// NOTE: Calculate Distance
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = OKVector2<float>(intersectionX, intersectionY);
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(intersectionX, intersectionY).magnitude();
		t_ColMani.m_CollisionPoints[0] = OKVector2<float>(intersectionX, intersectionY);

		return t_ColMani;
	};

	return t_ColMani;
}

CollisionManifold CollisionManager::S_LineToLine(float lineStartXA, float lineStartYA, float lineEndXA, float lineEndYA, float lineStartXB, float lineStartYB, float lineEndXB, float lineEndYB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const float x1 = lineStartXA;
	const float y1 = lineStartYA;

	const float x2 = lineEndXA;
	const float y2 = lineEndYA;

	const float x3 = lineStartXB;
	const float y3 = lineStartYB;

	const float x4 = lineEndXB;
	const float y4 = lineEndYB;

	// NOTE: Calculate Distance
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = OKVector2<float>(intersectionX, intersectionY);
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(intersectionX, intersectionY).magnitude();
		t_ColMani.m_CollisionPoints[0] = OKVector2<float>(intersectionX, intersectionY);

		return t_ColMani;
	};

	return t_ColMani;
}

CollisionManifold CollisionManager::S_LineToCircle(OKVector2<float> lineStartPositionA, OKVector2<float> lineEndPositionA, OKVector2<float> circPositionB, float circRadiusB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> t_tempLineStartA = lineStartPositionA;
	OKVector2<float> t_tempLineEndA = lineEndPositionA;

	OKVector2<float> t_tempCircPositionB = circPositionB;
	float t_tempCircRadiusB = circRadiusB;

	// NOTE: Check if its already inside the circle

	bool insideOne = S_PointToCircle(t_tempLineStartA, t_tempCircPositionB, t_tempCircRadiusB).m_HasCollision;
	bool insideTwo = S_PointToCircle(t_tempLineEndA, t_tempCircPositionB, t_tempCircRadiusB).m_HasCollision;

	if (insideOne || insideTwo)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempLineStartA - t_tempCircPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempLineStartA - t_tempCircPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	//// NOTE: Get Length of Circle
	float distX = t_tempLineStartA.x - t_tempLineEndA.x;
	float distY = t_tempLineStartA.y - t_tempLineEndA.y;
	float length = sqrt((distX * distX) + (distY * distY));

	float dot = (((t_tempCircPositionB.x - t_tempLineStartA.x) * (t_tempLineEndA.x - t_tempLineStartA.x)) + ((t_tempCircPositionB.y - t_tempLineStartA.y) * (t_tempLineEndA.y - t_tempLineStartA.y))) / (length * length);

	float closestX = t_tempLineStartA.x + (dot * (t_tempLineEndA.x - t_tempLineStartA.x));
	float closestY = t_tempLineStartA.y + (dot * (t_tempLineEndA.y - t_tempLineStartA.y));

	CollisionManifold onSegment = S_PointToLine(OKVector2<float>(closestX, closestY), t_tempLineStartA, t_tempLineEndA);

	if (!onSegment.m_HasCollision)
	{
		return t_ColMani;
	}

	distX = closestX - t_tempCircPositionB.x;
	distY = closestY - t_tempCircPositionB.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= t_tempCircRadiusB)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = OKVector2<float>(closestX, closestY) - t_tempCircPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise() * -1;
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(OKVector2<float>(closestX, closestY) - t_tempCircPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = OKVector2<float>(closestX, closestY);

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_LineToCircle(float lineStartXA, float lineStartYA, float lineEndXA, float lineEndYA, float circXB, float circYB, float circRadiusB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> t_tempLineStartA = OKVector2<float>(lineStartXA, lineStartYA);
	OKVector2<float> t_tempLineEndA = OKVector2<float>(lineEndXA, lineEndYA);

	OKVector2<float> t_tempCircPositionB = OKVector2<float>(circXB, circYB);
	float t_tempCircRadiusB = circRadiusB;

	// NOTE: Check if its already inside the circle

	bool insideOne = S_PointToCircle(t_tempLineStartA, t_tempCircPositionB, t_tempCircRadiusB).m_HasCollision;
	bool insideTwo = S_PointToCircle(t_tempLineEndA, t_tempCircPositionB, t_tempCircRadiusB).m_HasCollision;

	if (insideOne || insideTwo)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempLineStartA - t_tempCircPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempLineStartA - t_tempCircPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	//// NOTE: Get Length of Circle
	float distX = t_tempLineStartA.x - t_tempLineEndA.x;
	float distY = t_tempLineStartA.y - t_tempLineEndA.y;
	float length = sqrt((distX * distX) + (distY * distY));

	float dot = (((t_tempCircPositionB.x - t_tempLineStartA.x) * (t_tempLineEndA.x - t_tempLineStartA.x)) + ((t_tempCircPositionB.y - t_tempLineStartA.y) * (t_tempLineEndA.y - t_tempLineStartA.y))) / (length * length);

	float closestX = t_tempLineStartA.x + (dot * (t_tempLineEndA.x - t_tempLineStartA.x));
	float closestY = t_tempLineStartA.y + (dot * (t_tempLineEndA.y - t_tempLineStartA.y));

	CollisionManifold onSegment = S_PointToLine(OKVector2<float>(closestX, closestY), t_tempLineStartA, t_tempLineEndA);

	if (!onSegment.m_HasCollision)
	{
		return t_ColMani;
	}

	distX = closestX - t_tempCircPositionB.x;
	distY = closestY - t_tempCircPositionB.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= t_tempCircRadiusB)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempLineStartA - t_tempCircPositionB;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempLineStartA - t_tempCircPositionB).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_LineToRectangle(OKVector2<float> lineStartPositionA, OKVector2<float> lineEndPositionA, OKVector2<float> recPositionB, OKVector2<float> recScaleB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> t_tempRectPosition = recPositionB;
	OKVector2<float> t_tempRectHalfScale = recScaleB / 2.f;

	OKVector2<float> t_tempLineStartA = lineStartPositionA;
	OKVector2<float> t_tempLineEndA = lineEndPositionA;

	// NOTE: Left Line
	OKVector2<float> tempLeftPosStart = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempLeftPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	CollisionManifold t_Left = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempLeftPosStart, tempLeftPosEnd);

	// NOTE: Right Line
	OKVector2<float> tempRightPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempRightPosEnd = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	CollisionManifold t_Right = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempRightPosStart, tempRightPosEnd);

	// NOTE: Top Line
	OKVector2<float> tempTopPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempTopPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	CollisionManifold t_Top = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempTopPosStart, tempTopPosEnd);

	// NOTE: Bottom Line
	OKVector2<float> tempBottomPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	OKVector2<float> tempBottomPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	CollisionManifold t_Bottom = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempBottomPosStart, tempBottomPosEnd);

	if (t_Left.m_HasCollision == true ||
		t_Right.m_HasCollision == true ||
		t_Top.m_HasCollision == true ||
		t_Bottom.m_HasCollision == true)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempLineStartA - t_tempRectPosition;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempLineStartA - t_tempRectPosition).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_LineToRectangle(float lineStartXA, float lineStartYA, float lineEndXA, float lineEndYA, float recXB, float recYB, float recWidthB, float recHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	OKVector2<float> t_tempRectPosition = OKVector2<float>(recXB, recYB);
	OKVector2<float> t_tempRectHalfScale = OKVector2<float>(recWidthB, recHeightB) / 2.f;

	OKVector2<float> t_tempLineStartA = OKVector2<float>(lineStartXA, lineStartYA);
	OKVector2<float> t_tempLineEndA = OKVector2<float>(lineEndXA, lineEndXA);

	// NOTE: Left Line
	OKVector2<float> tempLeftPosStart = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempLeftPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	CollisionManifold t_Left = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempLeftPosStart, tempLeftPosEnd);

	// NOTE: Right Line
	OKVector2<float> tempRightPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempRightPosEnd = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	CollisionManifold t_Right = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempRightPosStart, tempRightPosEnd);

	// NOTE: Top Line
	OKVector2<float> tempTopPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	OKVector2<float> tempTopPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y + t_tempRectHalfScale.y);
	CollisionManifold t_Top = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempTopPosStart, tempTopPosEnd);

	// NOTE: Bottom Line
	OKVector2<float> tempBottomPosStart = OKVector2<float>(t_tempRectPosition.x + t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	OKVector2<float> tempBottomPosEnd = OKVector2<float>(t_tempRectPosition.x - t_tempRectHalfScale.x, t_tempRectPosition.y - t_tempRectHalfScale.y);
	CollisionManifold t_Bottom = S_LineToLine(t_tempLineStartA, t_tempLineEndA, tempBottomPosStart, tempBottomPosEnd);

	if (t_Left.m_HasCollision == true ||
		t_Right.m_HasCollision == true ||
		t_Top.m_HasCollision == true ||
		t_Bottom.m_HasCollision == true)
	{
		t_ColMani.m_HasCollision = true;
		t_ColMani.m_CollisionNormal = t_tempLineStartA - t_tempRectPosition;
		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
		t_ColMani.m_ContactPointAmount = 1;
		t_ColMani.m_PenetrationDepth = OKVector2<float>(t_tempLineStartA - t_tempRectPosition).magnitude();
		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;

		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_LineToCapsule(OKVector2<float> lineStartPositionA, OKVector2<float> lineEndPositionA, OKVector2<float> capPositionB, float capWidthB, float capHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempLineStartA = lineStartPositionA;
	const OKVector2<float> t_tempLineEndA = lineEndPositionA;

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capPositionB.x;
		t_tempMiddleRectPosition.y = capPositionB.y;

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capWidthB;
		t_tempMiddleRectScale.y = capHeightB / 2.f;

		t_ColMani = S_LineToRectangle(t_tempLineStartA, t_tempLineEndA, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capPositionB.x;
		t_tempTopCirclePosition.y = (capPositionB.y + capHeightB / 4.f);

		const float t_tempTopCircleRadius = capWidthB / 2.f;

		t_ColMani = S_LineToCircle(t_tempLineStartA, t_tempLineEndA, t_tempTopCirclePosition, t_tempTopCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = capPositionB.x;
		t_tempBottomCirclePosition.y = (capPositionB.y - capHeightB / 4.f);

		const float t_tempBottomCircleRadius = capWidthB / 2.f;

		t_ColMani = S_LineToCircle(t_tempLineStartA, t_tempLineEndA, t_tempBottomCirclePosition, t_tempBottomCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::S_LineToCapsule(float lineStartXA, float lineStartYA, float lineEndXA, float lineEndYA, float capXB, float capYB, float capWidthB, float capHeightB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	const OKVector2<float> t_tempLineStartA = OKVector2<float>(lineStartXA, lineStartYA);
	const OKVector2<float> t_tempLineEndA = OKVector2<float>(lineEndXA, lineEndYA);

	// NOTE: Check Middle Rectangle
	{
		OKVector2<float> t_tempMiddleRectPosition;
		t_tempMiddleRectPosition.x = capXB;
		t_tempMiddleRectPosition.y = capYB;

		OKVector2<float> t_tempMiddleRectScale;
		t_tempMiddleRectScale.x = capWidthB;
		t_tempMiddleRectScale.y = capHeightB / 2.f;

		t_ColMani = S_LineToRectangle(t_tempLineStartA, t_tempLineEndA, t_tempMiddleRectPosition, t_tempMiddleRectScale);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Top Circle
	{
		OKVector2<float> t_tempTopCirclePosition;
		t_tempTopCirclePosition.x = capXB;
		t_tempTopCirclePosition.y = (capYB + capHeightB / 4.f);

		const float t_tempTopCircleRadius = capWidthB / 2.f;

		t_ColMani = S_LineToCircle(t_tempLineStartA, t_tempLineEndA, t_tempTopCirclePosition, t_tempTopCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	// NOTE: Check Bottom Circle
	{
		OKVector2<float> t_tempBottomCirclePosition;
		t_tempBottomCirclePosition.x = capXB;
		t_tempBottomCirclePosition.y = (capYB - capHeightB / 4.f);

		const float t_tempBottomCircleRadius = capWidthB / 2.f;

		t_ColMani = S_LineToCircle(t_tempLineStartA, t_tempLineEndA, t_tempBottomCirclePosition, t_tempBottomCircleRadius);

		if (t_ColMani.m_HasCollision)
		{
			return t_ColMani;
		}
	}

	return CollisionManifold();
}
