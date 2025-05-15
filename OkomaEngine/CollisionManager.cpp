#include "CollisionManager.h"
//
//OKVector2<float> CollisionManager::ProjectPointOntoLine(OKVector2<float> point, OKVector2<float> positionReference, OKVector2<float> lineStart, OKVector2<float> lineEnd, OKVector2<float> offsetLine)
//{
//	// NOTE: Capsule Position and Variable(s)
//
//	OKVector2<float> LineStart = lineStart;
//	OKVector2<float> LineEnd = lineEnd;
//
//	OKVector2<float> Normal = offsetLine;
//	float NormalDot = Normal.dot(point);
//	OKVector2<float> ClosestPoint = point - (Normal * NormalDot) + positionReference;
//
//	ClosestPoint.x = Clamp(ClosestPoint.x, LineStart.x, LineEnd.x);
//	ClosestPoint.y = Clamp(ClosestPoint.y, LineStart.y, LineEnd.y);
//
//	return ClosestPoint;
//}
//
//bool CollisionManager::Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols)
//{
//	if (aCols != bRows) { return false; }
//
//	for (int i = 0; i < aRows; ++i) 
//	{
//		for (int j = 0; j < bCols; ++j) 
//		{
//			out[bCols * i + j] = 0.0f;
//
//			for (int k = 0; k < bRows; ++k) 
//			{
//				int a = aCols * i + k;
//				int b = bCols * k + j;
//				out[bCols * i + j] += matA[a] * matB[b];
//			}
//		}
//	}
//
//	return true;
//}
//
//Interval2D CollisionManager::GetOrientedRectangleInterval(ColliderEntity* orRectA, OKVector2<float>& axis)
//{
//	OKTransform2<float> lRect = OKTransform2<float>(orRectA->GetPosition() - (orRectA->GetScale() / 2), orRectA->GetScale(), 0);
//	ColliderEntity rectangle_temp = ColliderEntity(&lRect);
//
//	OKVector2<float> MaxB = orRectA->GetPosition() - orRectA->GetScale();
//	OKVector2<float> MinB = orRectA->GetPosition() + orRectA->GetScale();
//
//	OKVector2<float> verts[] = {
//		MinB, MaxB,
//		OKVector2<float>(MinB.x, MaxB.y),  OKVector2<float>(MaxB.x, MinB.y)
//	};
//
//	float theta = orRectA->GetRotation() * DEG2RAD;
//
//	float zRotation2x2[] = {
//		std::cosf(theta), std::sinf(theta),
//		-std::sinf(theta), std::cosf(theta)
//	};
//
//	for (int i = 0; i < 4; ++i)
//	{
//		OKVector2<float> r = verts[i] - orRectA->GetPosition();
//		Multiply(r.asArray(), OKVector2<float>(r.x, r.y).asArray(), 1, 2, zRotation2x2, 2, 2);
//		verts[i] = r + orRectA->GetPosition();
//	}
//
//	Interval2D res;
//	res.min = res.max = verts[0].dot(axis);
//
//	for (int i = 1; i < 4; ++i)
//	{
//		float proj = verts[i].dot(axis);
//		res.min = (proj < res.min) ? proj : res.min;
//		res.max = (proj > res.max) ? proj : res.max;
//	}
//
//	return res;
//}
//
//Interval2D CollisionManager::GetRectangleInterval(ColliderEntity* rectA, OKVector2<float>& axis)
//{
//	Interval2D result;
//
//	OKVector2<float> Max = rectA->GetPosition() - rectA->GetScale();
//	OKVector2<float> Min = rectA->GetPosition() + rectA->GetScale();
//
//	OKVector2<float> verts[] =
//	{
//		OKVector2<float>(Min.x, Min.y), OKVector2<float>(Min.x, Max.y),
//		OKVector2<float>(Max.x, Max.y), OKVector2<float>(Max.x, Min.y)
//	};
//
//	result.min = result.max = verts[0].dot(axis);
//
//	for (int i = 1; i < 4; ++i) {
//		float projection = verts[i].dot(axis);
//
//		if (projection < result.min) 
//		{
//			result.min = projection;
//		}
//
//		if (projection > result.max) 
//		{
//			result.max = projection;
//		}
//	}
//
//	return result;
//}
//
//bool CollisionManager::OverlapOnAxis(ColliderEntity* rectA, ColliderEntity* orRectB, OKVector2<float> axis)
//{
//	Interval2D A = GetRectangleInterval(rectA, axis);
//	Interval2D B = GetOrientedRectangleInterval(orRectB, axis);
//	return ((B.min <= A.max) && (A.min <= B.max));
//}
//
//CollisionManager::CollisionManager()
//{
//	m_CollisionMapping[std::make_pair(COLLIDER_RECTANGLE, COLLIDER_RECTANGLE)] = RECTANGLE_TO_RECTANGLE;
//
//	m_CollisionMapping[std::make_pair(COLLIDER_CIRCLE, COLLIDER_CIRCLE)] = CIRCLE_TO_CIRCLE;
//	m_CollisionMapping[std::make_pair(COLLIDER_CIRCLE, COLLIDER_RECTANGLE)] = CIRCLE_TO_RECTANGLE;
//
//	m_CollisionMapping[std::make_pair(COLLIDER_CAPSULE, COLLIDER_CAPSULE)] = CAPSULE_TO_CAPSULE;
//	m_CollisionMapping[std::make_pair(COLLIDER_CAPSULE, COLLIDER_RECTANGLE)] = CAPSULE_TO_RECTANGLE;
//	m_CollisionMapping[std::make_pair(COLLIDER_CAPSULE, COLLIDER_CIRCLE)] = CAPSULE_TO_CIRCLE;
//
//	m_CollisionMapping[std::make_pair(COLLIDER_ORIENTED_RECTANGLE, COLLIDER_ORIENTED_RECTANGLE)] = ORIENTED_TO_ORIENTED;
//	m_CollisionMapping[std::make_pair(COLLIDER_ORIENTED_RECTANGLE, COLLIDER_RECTANGLE)] = ORIENTED_TO_RECTANGLE;
//	m_CollisionMapping[std::make_pair(COLLIDER_ORIENTED_RECTANGLE, COLLIDER_CIRCLE)] = ORIENTED_TO_CIRCLE;
//	m_CollisionMapping[std::make_pair(COLLIDER_ORIENTED_RECTANGLE, COLLIDER_CAPSULE)] = ORIENTED_TO_CAPSULE;
//
//	m_CollisionMapping[std::make_pair(COLLIDER_LINE, COLLIDER_LINE)] = LINE_TO_LINE;
//	m_CollisionMapping[std::make_pair(COLLIDER_LINE, COLLIDER_CIRCLE)] = LINE_TO_CIRCLE;
//	m_CollisionMapping[std::make_pair(COLLIDER_LINE, COLLIDER_RECTANGLE)] = LINE_TO_RECTANGLE;
//	m_CollisionMapping[std::make_pair(COLLIDER_LINE, COLLIDER_CAPSULE)] = LINE_TO_CAPSULE;
//	m_CollisionMapping[std::make_pair(COLLIDER_LINE, COLLIDER_ORIENTED_RECTANGLE)] = LINE_TO_ORIENTED;
//
//	m_CollisionMapping[std::make_pair(COLLIDER_POINT, COLLIDER_POINT)] = POINT_TO_POINT;
//	m_CollisionMapping[std::make_pair(COLLIDER_POINT, COLLIDER_LINE)] = POINT_TO_LINE;
//	m_CollisionMapping[std::make_pair(COLLIDER_POINT, COLLIDER_CIRCLE)] = POINT_TO_CIRCLE;
//	m_CollisionMapping[std::make_pair(COLLIDER_POINT, COLLIDER_RECTANGLE)] = POINT_TO_RECTANGLE;
//	m_CollisionMapping[std::make_pair(COLLIDER_POINT, COLLIDER_CAPSULE)] = POINT_TO_CAPSULE;
//	m_CollisionMapping[std::make_pair(COLLIDER_POINT, COLLIDER_ORIENTED_RECTANGLE)] = POINT_TO_ORIENTED;
//}
//
//CollisionManifold CollisionManager::CheckCollisions(ColliderEntity* colliderA, ColliderEntity* colliderB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//	auto collision_made_pair = std::make_pair(colliderA->GetColliderType(), colliderB->GetColliderType());
//
//	ColliderEntity* tempA = colliderA;
//	ColliderEntity* tempB = colliderB;
//
//	// NOTE: Reverse pair if it is not within the collision map
//	if (m_CollisionMapping.count(collision_made_pair) == 0)
//	{
//		std::swap(collision_made_pair.first, collision_made_pair.second);
//		std::swap(tempA, tempB);
//	}
//
//	switch (m_CollisionMapping[collision_made_pair])
//	{
//		case RECTANGLE_TO_RECTANGLE: return t_ColMani = RectangleToRectangle(tempA, tempB); break;
//
//		case CIRCLE_TO_CIRCLE: return t_ColMani = CircleToCircle(tempA, tempB); break;
//		case CIRCLE_TO_RECTANGLE: return t_ColMani = CircleToRectangle(tempA, tempB); break;
//
//		case CAPSULE_TO_CAPSULE: return t_ColMani = CapsuleToCapsule(tempA, tempB); break;
//		case CAPSULE_TO_RECTANGLE: return t_ColMani = CapsuleToRectangle(tempA, tempB); break;
//		case CAPSULE_TO_CIRCLE: return t_ColMani = CapsuleToCircle(tempA, tempB); break;
//
//		case ORIENTED_TO_ORIENTED: return t_ColMani = OrientedRectangleToOrientedRectangle(tempA, tempB); break;
//		case ORIENTED_TO_RECTANGLE: return t_ColMani = OrientedRectangleToRectangle(tempA, tempB); break;
//		case ORIENTED_TO_CIRCLE: return t_ColMani = OrientedRectangleToCircle(tempA, tempB); break;
//		case ORIENTED_TO_CAPSULE: return t_ColMani = OrientedRectangleToCapsule(tempA, tempB); break;
//
//		case LINE_TO_LINE: return t_ColMani = LineToLine(tempA, tempB); break;
//		case LINE_TO_CIRCLE: return t_ColMani = LineToCircle(tempA, tempB); break;
//		case LINE_TO_RECTANGLE: return t_ColMani = LineToRectangle(tempA, tempB); break;
//		case LINE_TO_ORIENTED: return t_ColMani = LineToOrientedRectangle(tempA, tempB); break;
//		case LINE_TO_CAPSULE: return t_ColMani = LineToCapsule(tempA, tempB); break;
//
//		case POINT_TO_POINT: return t_ColMani = PointToPoint(tempA, tempB); break;
//		case POINT_TO_LINE: return t_ColMani = PointToLine(tempA, tempB); break;
//		case POINT_TO_CIRCLE: return t_ColMani = PointToCircle(tempA, tempB); break;
//		case POINT_TO_RECTANGLE: return t_ColMani = PointToRectangle(tempA, tempB); break;
//		case POINT_TO_CAPSULE: return t_ColMani = PointToCapsule(tempA, tempB); break;
//		case POINT_TO_ORIENTED: return t_ColMani = PointToOrientedRectangle(tempA, tempB); break;
//
//		default: t_ColMani = CollisionManifold();
//	}
//
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::RectangleToRectangle(ColliderEntity* rectA, ColliderEntity* rectB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	OKVector2<float> RectCentreA = rectA->GetPosition() + rectA->GetScale() / 2;// +(rectA->GetScale() * 0.5f); // Centre A
//	OKVector2<float> TopLeftCornerA = RectCentreA - rectA->GetScale() / 2;
//	OKVector2<float> RectScaleA = rectA->GetScale(); // rectA->GetScale(); // Full Extents
//	OKVector2<float> NearPointA = OKVector2<float>(0, 0);
//	
//	OKVector2<float> RectCentreB = rectB->GetPosition() + rectB->GetScale() / 2;// +(rectB->GetScale() * 0.5f); // Centre B
//	OKVector2<float> TopLeftCornerB = RectCentreB - rectB->GetScale() / 2;
//	OKVector2<float> RectScaleB = rectB->GetScale(); // rectB->GetScale(); // Half Extents
//	OKVector2<float> NearPointB = OKVector2<float>(0, 0);
//
//	if (TopLeftCornerA.x < TopLeftCornerB.x)
//	{
//		OKVector2<float> LeftSide = ProjectPointOntoLine(
//			TopLeftCornerB,
//			TopLeftCornerA,
//			OKVector2<float>(TopLeftCornerB.x, TopLeftCornerB.y),
//			OKVector2<float>(TopLeftCornerB.x, TopLeftCornerB.y + RectScaleB.y),
//			OKVector2<float>(0, 1)
//		);
//
//		NearPointB.y = LeftSide.y;
//	}
//	else if (TopLeftCornerA.x > TopLeftCornerB.x)
//	{
//		OKVector2<float> RightSide = ProjectPointOntoLine(
//			TopLeftCornerB,
//			TopLeftCornerA,
//			OKVector2<float>(TopLeftCornerB.x + RectScaleB.x, TopLeftCornerB.y),
//			OKVector2<float>(TopLeftCornerB.x + RectScaleB.x, TopLeftCornerB.y + RectScaleB.y),
//			OKVector2<float>(0, 1)
//		);
//
//		NearPointB.y = RightSide.y;
//	}
//
//	if (TopLeftCornerA.y < RectCentreB.y)
//	{
//		OKVector2<float> TopSide = ProjectPointOntoLine(
//			TopLeftCornerB,
//			TopLeftCornerA,
//			OKVector2<float>(TopLeftCornerB.x, TopLeftCornerB.y),
//			OKVector2<float>(TopLeftCornerB.x + RectScaleB.x, TopLeftCornerB.y),
//			OKVector2<float>(1, 0)
//		);
//
//		NearPointB.x = TopSide.x;
//	}
//	else if (TopLeftCornerA.y > RectCentreB.y)
//	{
//		OKVector2<float> BottomSide = ProjectPointOntoLine(
//			TopLeftCornerB,
//			TopLeftCornerA,
//			OKVector2<float>(TopLeftCornerB.x, TopLeftCornerB.y + RectScaleB.y),
//			OKVector2<float>(TopLeftCornerB.x + RectScaleB.x, TopLeftCornerB.y + RectScaleB.y),
//			OKVector2<float>(1, 0)
//		);
//
//		NearPointB.x = BottomSide.x;
//	}
//
//	if (TopLeftCornerB.x < TopLeftCornerA.x)
//
//	{
//		OKVector2<float> LeftSide = ProjectPointOntoLine(
//			TopLeftCornerA,
//			TopLeftCornerB,
//			OKVector2<float>(TopLeftCornerA.x, TopLeftCornerA.y),
//			OKVector2<float>(TopLeftCornerA.x, TopLeftCornerA.y + RectScaleA.y),
//			OKVector2<float>(0, 1)
//		);
//
//		NearPointA.y = LeftSide.y;
//	}
//	else if (TopLeftCornerB.x > TopLeftCornerA.x)
//	{
//		OKVector2<float> RightSide = ProjectPointOntoLine(
//			TopLeftCornerA,
//			TopLeftCornerB,
//			OKVector2<float>(TopLeftCornerA.x + RectScaleA.x, TopLeftCornerA.y),
//			OKVector2<float>(TopLeftCornerA.x + RectScaleA.x, TopLeftCornerA.y + RectScaleA.y),
//			OKVector2<float>(0, 1)
//		);
//
//		NearPointA.y = RightSide.y;
//	}
//
//	if (TopLeftCornerB.y < RectCentreA.y)
//	{
//		OKVector2<float> TopSide = ProjectPointOntoLine(
//			TopLeftCornerA,
//			TopLeftCornerB,
//			OKVector2<float>(TopLeftCornerA.x, TopLeftCornerA.y),
//			OKVector2<float>(TopLeftCornerA.x + RectScaleA.x, TopLeftCornerA.y),
//			OKVector2<float>(1, 0)
//		);
//
//		NearPointA.x = TopSide.x;
//	}
//	else if (TopLeftCornerB.y > RectCentreA.y)
//	{
//		OKVector2<float> BottomSide = ProjectPointOntoLine(
//			TopLeftCornerA,
//			TopLeftCornerB,
//			OKVector2<float>(TopLeftCornerA.x, TopLeftCornerA.y + RectScaleA.y),
//			OKVector2<float>(TopLeftCornerA.x + RectScaleA.x, TopLeftCornerA.y + RectScaleA.y),
//			OKVector2<float>(1, 0)
//		);
//
//		NearPointA.x = BottomSide.x;
//	}
//
//	// DrawCircleV(NearPointA.ConvertToVec2(), 3, BLUE);
//	DrawCircleV(NearPointB.ConvertToVec2(), 1.f, YELLOW);
//	DrawCircleV(NearPointA.ConvertToVec2(), 1.f, YELLOW);
//
//	// REFACTOR: Fix the size of the circle  
//	OKTransform2<float> circle_transform_A = OKTransform2<float>(NearPointA, OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp_A = ColliderEntity(&circle_transform_A, 0.5f);
//
//	OKTransform2<float> circle_transform_B = OKTransform2<float>(NearPointB, OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp_B = ColliderEntity(&circle_transform_B, 0.5f);
//
//	return t_ColMani = CircleToCircle(&circle_temp_A, &circle_temp_B);
//}
//
//CollisionManifold CollisionManager::CircleToCircle(ColliderEntity* circA, ColliderEntity* circB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	OKVector2<float> distance = circA->GetTransform()->position - circB->GetTransform()->position;
//	float radii_sum = circA->GetRadius() + circB->GetRadius();
//
//	if (distance.magnitude() <= radii_sum)
//	{
//		t_ColMani.m_HasCollision = true;
//		t_ColMani.m_CollisionNormal = circA->GetTransform()->position - circB->GetTransform()->position;
//		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//		t_ColMani.m_ContactPointAmount = 1;
//		t_ColMani.m_PenetrationDepth = OKVector2<float>(circA->GetTransform()->position - circB->GetTransform()->position).magnitude();
//		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//		return t_ColMani;
//	}
//
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::CircleToRectangle(ColliderEntity* circA, ColliderEntity* rectB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	OKVector2<float> RectCentre = rectB->GetPosition() + (rectB->GetScale() / 2.f);
//	OKVector2<float> RectScale = rectB->GetScale();
//	OKVector2<float> TopLeftCorner = RectCentre - (RectScale / 2.f);
//
//	OKVector2<float> NearPoint = OKVector2<float>(0, 0);
//
//	if (circA->GetPosition().x < TopLeftCorner.x)
//	{
//		OKVector2<float> LeftSide = ProjectPointOntoLine(
//			TopLeftCorner,
//			circA->GetPosition(),
//			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y),
//			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y + RectScale.y),
//			OKVector2<float>(0, 1)
//		);
//
//		NearPoint.y = LeftSide.y;
//	}
//	else if (circA->GetPosition().x > TopLeftCorner.x)
//	{
//		OKVector2<float> RightSide = ProjectPointOntoLine(
//			TopLeftCorner,
//			circA->GetPosition(),
//			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y),
//			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y + RectScale.y),
//			OKVector2<float>(0, 1)
//		);
//
//		NearPoint.y = RightSide.y;
//	}
//
//	if (circA->GetPosition().y < RectCentre.y)
//	{
//		OKVector2<float> TopSide = ProjectPointOntoLine(
//			TopLeftCorner,
//			circA->GetPosition(),
//			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y),
//			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y),
//			OKVector2<float>(1, 0)
//		);
//
//		NearPoint.x = TopSide.x;
//	}
//	else if (circA->GetPosition().y > RectCentre.y)
//	{
//		OKVector2<float> BottomSide = ProjectPointOntoLine(
//			TopLeftCorner,
//			circA->GetPosition(),
//			OKVector2<float>(TopLeftCorner.x, TopLeftCorner.y + RectScale.y),
//			OKVector2<float>(TopLeftCorner.x + RectScale.x, TopLeftCorner.y + RectScale.y),
//			OKVector2<float>(1, 0)
//		);
//
//		NearPoint.x = BottomSide.x;
//	}
//
//	OKTransform2<float> circle_transform_A = OKTransform2<float>(NearPoint, OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp_A = ColliderEntity(&circle_transform_A, 1.f);
//
//	return t_ColMani = CircleToCircle(circA, &circle_temp_A);
//}
//
//CollisionManifold CollisionManager::CapsuleToCircle(ColliderEntity* capsuleA, ColliderEntity* circB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	// NOTE: Capsule Position and Variable(s)
//	OKVector2<float> tip_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y + (capsuleA->GetScale().y / 2) - (capsuleA->GetScale().x / 2));
//	OKVector2<float> base_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y - (capsuleA->GetScale().y / 2) + (capsuleA->GetScale().x / 2));
//
//	float t_DistanceX = tip_a.x - base_a.x;
//	float t_DistanceY = tip_a.y - base_a.y;
//	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));
//
//	float dot = ((circB->GetPosition().x - tip_a.x) * (base_a.x - tip_a.x)) + ((circB->GetPosition().y - tip_a.y) * (base_a.y - tip_a.y)) / pow(len, 2);
//
//	// NOTE: Closest Point
//	OKVector2<float> closest_point;
//	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x));
//	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y));
//
//	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
//	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);
//
//	// NOTE: Create the circle based of the capsule components
//	OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(capsuleA->GetScale().x, capsuleA->GetScale().x), 0);
//	ColliderEntity circle_temp = ColliderEntity(&circle_transform, capsuleA->GetScale().x / 2);
//
//	t_ColMani = CircleToCircle(&circle_temp, circB);
//
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::CapsuleToRectangle(ColliderEntity* capsuleA, ColliderEntity* rectB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	// Circles
//	// NOTE: Capsule Position and Variable(s)
//	OKVector2<float> tip_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y + (capsuleA->GetScale().y / 2) - (capsuleA->GetScale().x / 2));
//	OKVector2<float> base_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y - (capsuleA->GetScale().y / 2) + (capsuleA->GetScale().x / 2));
//
//	float t_DistanceX = tip_a.x - base_a.x;
//	float t_DistanceY = tip_a.y - base_a.y;
//	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));
//
//	float dot = (((rectB->GetPosition().x + (rectB->GetScale().x / 2)) - tip_a.x) * (base_a.x - tip_a.x)) + ((rectB->GetPosition().y + (rectB->GetScale().y / 2) - tip_a.y) * (base_a.y - tip_a.y)) / pow(len, 2);
//
//	// NOTE: Closest Point
//	OKVector2<float> closest_point;
//	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x) / 2);
//	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y) / 2);
//
//	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
//	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);
//
//	// NOTE: Create the circle based of the capsule components
//	OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp = ColliderEntity(&circle_transform, capsuleA->GetScale().x / 2);
//
//	return t_ColMani = CircleToRectangle(&circle_temp, rectB);
//}
//
//CollisionManifold CollisionManager::CapsuleToCapsule(ColliderEntity* capsuleA, ColliderEntity* capsuleB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	// Capsule (A)
//	// NOTE: Capsule Position and Variable(s)
//	OKVector2<float> tip_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y + (capsuleA->GetScale().y / 2) - (capsuleA->GetScale().x / 2));
//	OKVector2<float> base_a = OKVector2<float>(capsuleA->GetPosition().x, capsuleA->GetPosition().y - (capsuleA->GetScale().y / 2) + (capsuleA->GetScale().x / 2));
//	float t_DistanceXA = tip_a.x - base_a.x;
//	float t_DistanceYA = tip_a.y - base_a.y;
//	float lenA = sqrt((t_DistanceXA * t_DistanceXA) + (t_DistanceYA * t_DistanceYA));
//	float dotA = ((capsuleB->GetPosition().x - tip_a.x) * (base_a.x - tip_a.x)) + ((capsuleB->GetPosition().y - tip_a.y) * (base_a.y - tip_a.y)) / pow(lenA, 2);
//
//	// Capsule (B)
//	OKVector2<float> tip_b = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y + (capsuleB->GetScale().y / 2) - (capsuleB->GetScale().x / 2));
//	OKVector2<float> base_b = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y - (capsuleB->GetScale().y / 2) + (capsuleB->GetScale().x / 2));
//	float t_DistanceXB = tip_b.x - base_b.x;
//	float t_DistanceYB = tip_b.y - base_b.y;
//	float lenB = sqrt((t_DistanceXB * t_DistanceXB) + (t_DistanceYB * t_DistanceYB));
//	float dotB = ((capsuleA->GetPosition().x - tip_b.x) * (base_b.x - tip_b.x)) + ((capsuleA->GetPosition().y - tip_b.y) * (base_b.y - tip_b.y)) / pow(lenB, 2);
//
//	// NOTE: Closest Point (A)
//	OKVector2<float> closest_point_A;
//	closest_point_A.x = tip_a.x + (dotA * (base_a.x - tip_a.x)) / 2;
//	closest_point_A.y = tip_a.y + (dotA * (base_a.y - tip_a.y)) / 2;
//	closest_point_A.x = Clamp(closest_point_A.x, base_a.x, tip_a.x);
//	closest_point_A.y = Clamp(closest_point_A.y, base_a.y, tip_a.y);
//
//	// NOTE: Closest Point (B)
//	OKVector2<float> closest_point_B;
//	closest_point_B.x = tip_b.x + (dotB * (base_b.x - tip_b.x)) / 2;
//	closest_point_B.y = tip_b.y + (dotB * (base_b.y - tip_b.y)) / 2;
//	closest_point_B.x = Clamp(closest_point_B.x, base_b.x, tip_b.x);
//	closest_point_B.y = Clamp(closest_point_B.y, base_b.y, tip_b.y);
//
//	DrawCircleV(closest_point_A.ConvertToVec2(), 10.f, RED);
//	DrawCircleV(closest_point_B.ConvertToVec2(), 10.f, PURPLE);
//
//	// NOTE: Circle Construction (A)
//	OKTransform2<float> circle_transform_A = OKTransform2<float>(closest_point_A, OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp_A = ColliderEntity(&circle_transform_A, capsuleA->GetScale().x / 2);
//
//	// NOTE: Circle Construction (B)
//	OKTransform2<float> circle_transform_B = OKTransform2<float>(closest_point_B, OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp_B = ColliderEntity(&circle_transform_B, capsuleB->GetScale().x / 2);
//
//	t_ColMani = CircleToCircle(&circle_temp_A, &circle_temp_B);
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::OrientedRectangleToOrientedRectangle(ColliderEntity* OrRectA, ColliderEntity* OrRectB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	OKVector2<float> AxisToTest[] = {
//		OKVector2<float>(1, 0),
//		OKVector2<float>(0, 1)
//	};
//	
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::OrientedRectangleToRectangle(ColliderEntity* OrRectA, ColliderEntity* rectB) // rect2 = OrRectA
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	OKVector2<float> AxisToTest[]{
//		OKVector2<float>(1, 0), OKVector2<float>(0, 1),
//		OKVector2<float>(0, 0), OKVector2<float>(0, 0)
//	};
//
//	float theta = DEG2RAD * OrRectA->GetRotation();
//
//	float zRotation2x2[] = {
//		std::cosf(theta), std::sinf(theta),
//		-std::sinf(theta), std::cosf(theta)
//	};
//
//	OKVector2<float> axis = OKVector2<float>(OrRectA->GetScale().x / 2, 0).normalise();
//	Multiply(AxisToTest[2].asArray(), axis.asArray(), 1, 2, zRotation2x2, 2, 2);
//
//	axis = OKVector2<float>(0, OrRectA->GetScale().y / 2).normalise();
//	Multiply(AxisToTest[3].asArray(), axis.asArray(), 1, 2, zRotation2x2, 2, 2);
//
//	for (int i = 0; i < 4; ++i)
//	{
//		if (!OverlapOnAxis(rectB, OrRectA, AxisToTest[i]))
//		{
//			return t_ColMani;
//		}
//	}
//
//	t_ColMani.m_HasCollision = true;
//	t_ColMani.m_CollisionNormal = OrRectA->GetTransform()->position - rectB->GetTransform()->position;
//	t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//	t_ColMani.m_ContactPointAmount = 1;
//	t_ColMani.m_PenetrationDepth = OKVector2<float>(OrRectA->GetTransform()->position - rectB->GetTransform()->position).magnitude();
//	t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::OrientedRectangleToCircle(ColliderEntity* OrRectA, ColliderEntity* circB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	OKVector2<float> Rad = circB->GetPosition() - OrRectA->GetPosition();
//	float theta = -DEG2RAD * OrRectA->GetRotation();
//	
//	float zRotation2x2[] = {
//		std::cosf(theta), std::sinf(theta),
//		-std::sinf(theta), std::cosf(theta)
//	};
//
//	Multiply(Rad.asArray(), OKVector2<float>(Rad.x, Rad.y).asArray(), 1, 2, zRotation2x2, 2, 2);
//
//	OKTransform2<float> lcircle = OKTransform2<float>(Rad + (OrRectA->GetScale() / 2), OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp = ColliderEntity(&lcircle, circB->GetRadius());
//
//	OKTransform2<float> lRect = OKTransform2<float>(OKVector2<float>(0, 0), OrRectA->GetScale(), 0);
//	ColliderEntity rectangle_temp = ColliderEntity(&lRect);
//
//	return t_ColMani = CircleToRectangle(&circle_temp, &rectangle_temp);
//}
//
//CollisionManifold CollisionManager::OrientedRectangleToCapsule(ColliderEntity* OrRectA, ColliderEntity* capsuleB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	// NEAREST POINT FOR CAPSULE
//	// Circles
//	// NOTE: Capsule Position and Variable(s)
//	OKVector2<float> tip_a = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y + (capsuleB->GetScale().y / 2) - (capsuleB->GetScale().x / 2));
//	OKVector2<float> base_a = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y - (capsuleB->GetScale().y / 2) + (capsuleB->GetScale().x / 2));
//
//	float t_DistanceX = tip_a.x - base_a.x;
//	float t_DistanceY = tip_a.y - base_a.y;
//	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));
//
//	float dot = (((OrRectA->GetPosition().x + (OrRectA->GetScale().x / 2)) - tip_a.x) * (base_a.x - tip_a.x)) + ((OrRectA->GetPosition().y + (OrRectA->GetScale().y / 2) - tip_a.y) * (base_a.y - tip_a.y)) / pow(len, 2);
//
//	// NOTE: Closest Point
//	OKVector2<float> closest_point;
//	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x) / 2);
//	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y) / 2);
//
//	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
//	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);
//
//	// NOTE: Create the circle based of the capsule components
//	OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp = ColliderEntity(&circle_transform, capsuleB->GetScale().x / 2);
//
//	
//	// ROTATED BOX TO CIRCLE
//	OKVector2<float> Rad = circle_temp.GetPosition() - OrRectA->GetPosition();
//	float theta = -DEG2RAD * OrRectA->GetRotation();
//
//	float zRotation2x2[] = {
//		std::cosf(theta), std::sinf(theta),
//		-std::sinf(theta), std::cosf(theta)
//	};
//
//	Multiply(Rad.asArray(), OKVector2<float>(Rad.x, Rad.y).asArray(), 1, 2, zRotation2x2, 2, 2);
//
//	OKTransform2<float> lcircle = OKTransform2<float>(Rad + (OrRectA->GetScale() / 2), OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp_or = ColliderEntity(&lcircle, circle_temp.GetRadius());
//
//	OKTransform2<float> lRect = OKTransform2<float>(OKVector2<float>(0, 0), OrRectA->GetScale(), 0);
//	ColliderEntity rectangle_temp = ColliderEntity(&lRect);
//
//	return t_ColMani = CircleToRectangle(&circle_temp_or, &rectangle_temp);
//}
//
//CollisionManifold CollisionManager::PointToPoint(ColliderEntity* pointA, ColliderEntity* pointB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	if (pointA->GetPosition() == pointB->GetPosition())
//	{
//		t_ColMani.m_HasCollision = true;
//		t_ColMani.m_CollisionNormal = pointA->GetTransform()->position - pointB->GetTransform()->position;
//		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//		t_ColMani.m_ContactPointAmount = 1;
//		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointA->GetTransform()->position - pointB->GetTransform()->position).magnitude();
//		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//		return t_ColMani;
//	}
//
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::PointToLine(ColliderEntity* pointA, ColliderEntity* lineB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	// NOTE: Distance Point from Start of Line
//	float PointOneDistX = pointA->GetPosition().x - lineB->GetLineStart().x;
//	float PointOneDistY = pointA->GetPosition().y - lineB->GetLineStart().y;
//	float distanceOne = sqrt((PointOneDistX * PointOneDistX) + (PointOneDistY * PointOneDistY));
//
//	// NOTE: Distance Point from End of Line
//	float PointTwoDistX = pointA->GetPosition().x - lineB->GetLineEnd().x;
//	float PointTwoDistY = pointA->GetPosition().y - lineB->GetLineEnd().y;
//	float distanceTwo = sqrt((PointTwoDistX * PointTwoDistX) + (PointTwoDistY * PointTwoDistY));
//
//	// NOTE: Distance from Start to End
//	float distX = lineB->GetLineStart().x - lineB->GetLineEnd().x;
//	float distY = lineB->GetLineStart().y - lineB->GetLineEnd().y;
//	float LineLength = sqrt((distX * distX) + (distY * distY));
//
//	// NOTE: Accuracy of colliding line
//	float LineBuffer = pointA->GetRadius();
//
//	// NOTE: Collision Check
//	if ((distanceOne + distanceTwo) >= LineLength - LineBuffer && distanceOne + distanceTwo <= LineLength + LineBuffer)
//	{
//		t_ColMani.m_HasCollision = true;
//		t_ColMani.m_CollisionNormal = pointA->GetTransform()->position - lineB->GetTransform()->position;
//		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//		t_ColMani.m_ContactPointAmount = 1;
//		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointA->GetTransform()->position - lineB->GetTransform()->position).magnitude();
//		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//		return t_ColMani;
//	}
//
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::PointToCircle(ColliderEntity* pointA, ColliderEntity* circleB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	// NOTE: Work out Distance between colliders
//	float distX = pointA->GetPosition().x - circleB->GetPosition().x;
//	float distY = pointA->GetPosition().y - circleB->GetPosition().y;
//	float distance = sqrt(  (distX * distX) + (distY * distY));
//
//	if (distance <= circleB->GetRadius())
//	{
//		t_ColMani.m_HasCollision = true;
//		t_ColMani.m_CollisionNormal = pointA->GetTransform()->position - circleB->GetTransform()->position;
//		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//		t_ColMani.m_ContactPointAmount = 1;
//		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointA->GetTransform()->position - circleB->GetTransform()->position).magnitude();
//		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//		return t_ColMani;
//	}
//
//	return t_ColMani;
//}
//
//// TODO: Change this when transferring to the project
//CollisionManifold CollisionManager::PointToRectangle(ColliderEntity* pointA, ColliderEntity* rectB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	OKVector2<float> t_CentrePosition = rectB->GetPosition() - (rectB->GetScale() / 2);
//
//	if (pointA->GetPosition().x >= rectB->GetPosition().x &&
//		pointA->GetPosition().x <= rectB->GetPosition().x + rectB->GetScale().x &&
//		pointA->GetPosition().y >= rectB->GetPosition().y &&
//		pointA->GetPosition().y <= rectB->GetPosition().y + rectB->GetScale().y)
//	{
//		t_ColMani.m_HasCollision = true;
//		t_ColMani.m_CollisionNormal = pointA->GetTransform()->position - rectB->GetTransform()->position;
//		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//		t_ColMani.m_ContactPointAmount = 1;
//		t_ColMani.m_PenetrationDepth = OKVector2<float>(pointA->GetTransform()->position - rectB->GetTransform()->position).magnitude();
//		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//		return t_ColMani;
//	}
//
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::PointToCapsule(ColliderEntity* pointA, ColliderEntity* capsuleB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	OKVector2<float> tip_a = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y + (capsuleB->GetScale().y / 2) - (capsuleB->GetScale().x / 2));
//	OKVector2<float> base_a = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y - (capsuleB->GetScale().y / 2) + (capsuleB->GetScale().x / 2));
//
//	float t_DistanceX = tip_a.x - base_a.x;
//	float t_DistanceY = tip_a.y - base_a.y;
//	float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));
//
//	float dot = ((pointA->GetPosition().x - tip_a.x) * (base_a.x - tip_a.x)) + ((pointA->GetPosition().y - tip_a.y) * (base_a.y - tip_a.y)) / pow(len, 2);
//
//	// NOTE: Closest Point
//	OKVector2<float> closest_point;
//	closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x));
//	closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y));
//
//	closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
//	closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);
//
//
//	// NOTE: Create the circle based of the capsule components
//	OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(capsuleB->GetScale().x, capsuleB->GetScale().x), 0);
//	ColliderEntity circle_temp = ColliderEntity(&circle_transform, capsuleB->GetScale().x / 2);
//
//	return t_ColMani = PointToCircle(pointA, &circle_temp);
//}
//
//CollisionManifold CollisionManager::PointToOrientedRectangle(ColliderEntity* pointA, ColliderEntity* OrRectB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	return CollisionManifold();
//}
//
//CollisionManifold CollisionManager::LineToLine(ColliderEntity* lineA, ColliderEntity* lineB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	const float x1 = lineA->GetLineStart().x;
//	const float y1 = lineA->GetLineStart().y;
//
//	const float x2 = lineA->GetLineEnd().x;
//	const float y2 = lineA->GetLineEnd().y;
//
//	const float x3 = lineB->GetLineStart().x;
//	const float y3 = lineB->GetLineStart().y;
//
//	const float x4 = lineB->GetLineEnd().x;
//	const float y4 = lineB->GetLineEnd().y;
//
//	// NOTE: Calculate Distance
//	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
//	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
//
//	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
//	{
//		t_ColMani.m_HasCollision = true;
//		t_ColMani.m_CollisionNormal = lineA->GetTransform()->position - lineB->GetTransform()->position;
//		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//		t_ColMani.m_ContactPointAmount = 1;
//		t_ColMani.m_PenetrationDepth = OKVector2<float>(lineA->GetTransform()->position - lineB->GetTransform()->position).magnitude();
//		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//		return t_ColMani;
//	};
//
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::LineToCircle(ColliderEntity* lineA, ColliderEntity* circB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	// NOTE: Check if its already inside the circle
//	OKTransform2<float> PointOneTrans = OKTransform2<float>(OKVector2<float>(lineA->GetLineStart()), OKVector2<float>(1.f, 1.f), 0.f);
//	ColliderEntity PointOne = ColliderEntity(&PointOneTrans, 1.f, true);
//
//	OKTransform2<float> PointTwoTrans = OKTransform2<float>(OKVector2<float>(lineA->GetLineEnd()), OKVector2<float>(1.f, 1.f), 0.f);
//	ColliderEntity PointTwo = ColliderEntity(&PointTwoTrans, 1.f, true);
//
//	bool insideOne = PointToCircle(&PointOne, circB).m_HasCollision;
//	bool insideTwo = PointToCircle(&PointTwo, circB).m_HasCollision;
//
//	if (insideOne || insideTwo)
//	{
//		t_ColMani.m_HasCollision = true;
//		t_ColMani.m_CollisionNormal = lineA->GetTransform()->position - circB->GetTransform()->position;
//		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//		t_ColMani.m_ContactPointAmount = 1;
//		t_ColMani.m_PenetrationDepth = OKVector2<float>(lineA->GetTransform()->position - circB->GetTransform()->position).magnitude();
//		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//		return t_ColMani;
//	}
//
//
//	// NOTE: Get Length of Circle
//	float distX = lineA->GetLineStart().x - lineA->GetLineEnd().x;
//	float distY = lineA->GetLineStart().y - lineA->GetLineEnd().y;
//	float length = sqrt((distX * distX) + (distY * distY));
//
//	float dot = ( ((circB->GetPosition().x - lineA->GetLineStart().x) * (lineA->GetLineEnd().x - lineA->GetLineStart().x)) +  ((circB->GetPosition().y - lineA->GetLineStart().y) * (lineA->GetLineEnd().y - lineA->GetLineStart().y))) / (length * length);
//
//	float closestX = lineA->GetLineStart().x + (dot * (lineA->GetLineEnd().x - lineA->GetLineStart().x));
//	float closestY = lineA->GetLineStart().y + (dot * (lineA->GetLineEnd().y - lineA->GetLineStart().y));
//
//	OKTransform2<float> tempPoint = OKTransform2<float>(circB->GetPosition(), OKVector2<float>(1.f, 1.f), 0.f);
//	ColliderEntity tempCollider = ColliderEntity(&tempPoint, circB->GetRadius(), true);
//	CollisionManifold onSegment = PointToLine(&tempCollider, lineA);
//
//	if (!onSegment.m_HasCollision)
//	{
//		return t_ColMani;
//	}
//
//	distX = closestX - circB->GetPosition().x;
//	distY = closestY - circB->GetPosition().y;
//	float distance = sqrt((distX * distX) + (distY * distY));
//
//	if (distance <= circB->GetRadius())
//	{
//		t_ColMani.m_HasCollision = true;
//		t_ColMani.m_CollisionNormal = lineA->GetTransform()->position - circB->GetTransform()->position;
//		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//		t_ColMani.m_ContactPointAmount = 1;
//		t_ColMani.m_PenetrationDepth = OKVector2<float>(lineA->GetTransform()->position - circB->GetTransform()->position).magnitude();
//		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//		return t_ColMani;
//	}
//
//	return t_ColMani;
//}
//
//// Change for the project (this assumes that the coordinate of the rectangle starts at the top left)
//CollisionManifold CollisionManager::LineToRectangle(ColliderEntity* lineA, ColliderEntity* rectB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	OKTransform2<float> tempTransform = OKTransform2<float>();
//
//	// NOTE: Left Line
//	OKVector2<float> tempLeftPosStart = OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y);
//	OKVector2<float> tempLeftPosEnd = OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y + rectB->GetScale().y);
//	ColliderEntity t_LineLeft = ColliderEntity(&tempTransform, tempLeftPosStart, tempLeftPosEnd);
//
//	// NOTE: Right Line
//	OKVector2<float> tempRightPosStart = OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y);
//	OKVector2<float> tempRightPosEnd = OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y + rectB->GetScale().y);
//	ColliderEntity t_LineRight = ColliderEntity(&tempTransform, tempRightPosStart, tempRightPosEnd);
//
//	// NOTE: Top Line
//	OKVector2<float> tempTopPosStart = OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y);
//	OKVector2<float> tempTopPosEnd = OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y);
//	ColliderEntity t_LineTop = ColliderEntity(&tempTransform, tempTopPosStart, tempTopPosEnd);
//
//	// NOTE: Bottom Line
//	OKVector2<float> tempBottomPosStart = OKVector2<float>(rectB->GetPosition().x, rectB->GetPosition().y + rectB->GetScale().y);
//	OKVector2<float> tempBottomPosEnd = OKVector2<float>(rectB->GetPosition().x + rectB->GetScale().x, rectB->GetPosition().y + rectB->GetScale().y);
//	ColliderEntity t_LineBottom = ColliderEntity(&tempTransform, tempBottomPosStart, tempBottomPosEnd);
//
//	CollisionManifold t_Left = LineToLine(lineA, &t_LineLeft);
//	CollisionManifold t_Right = LineToLine(lineA, &t_LineRight);
//	CollisionManifold t_Top = LineToLine(lineA, &t_LineTop);
//	CollisionManifold t_Bottom = LineToLine(lineA, &t_LineBottom);
//
//	if (t_Left.m_HasCollision == true ||
//		t_Right.m_HasCollision == true ||
//		t_Top.m_HasCollision == true ||
//		t_Bottom.m_HasCollision == true)
//	{
//		t_ColMani.m_HasCollision = true;
//		t_ColMani.m_CollisionNormal = lineA->GetTransform()->position - rectB->GetTransform()->position;
//		t_ColMani.m_CollisionNormal = t_ColMani.m_CollisionNormal.normalise();
//		t_ColMani.m_ContactPointAmount = 1;
//		t_ColMani.m_PenetrationDepth = OKVector2<float>(lineA->GetTransform()->position - rectB->GetTransform()->position).magnitude();
//		t_ColMani.m_CollisionPoints[0] = t_ColMani.m_CollisionNormal;
//
//		return t_ColMani;
//	}
//
//	return t_ColMani;
//}
//
//CollisionManifold CollisionManager::LineToOrientedRectangle(ColliderEntity* lineA, ColliderEntity* OrRectB)
//{
//	return CollisionManifold();
//}
//
//CollisionManifold CollisionManager::LineToCapsule(ColliderEntity* lineA, ColliderEntity* capsuleB)
//{
//	CollisionManifold t_ColMani = CollisionManifold();
//
//	//OKVector2<float> tip_a = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y + (capsuleB->GetScale().y / 2) - (capsuleB->GetScale().x / 2));
//	//OKVector2<float> base_a = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y - (capsuleB->GetScale().y / 2) + (capsuleB->GetScale().x / 2));
//
//	//float t_DistanceX = tip_a.x - base_a.x;
//	//float t_DistanceY = tip_a.y - base_a.y;
//	//float len = sqrt((t_DistanceX * t_DistanceX) + (t_DistanceY * t_DistanceY));
//
//	//float dot = ((lineA->GetLineEnd().x - tip_a.x) * (base_a.x - tip_a.x)) + ((lineA->GetLineEnd().y - tip_a.y) * (base_a.y - tip_a.y)) / pow(len, 2);
//	//
//	//// NOTE: Closest Point
//	//OKVector2<float> closest_point;
//	//
//	//// NOTE: Calculating the Y Position
//	//// NOTE: New calculation with the line start and end in mind
//	//float LineYCalculation = ((lineA->GetLineStart().y - (capsuleB->GetPosition().y - capsuleB->GetScale().y / 2)) * 0.5f) - ((lineA->GetLineEnd().y - (capsuleB->GetPosition().y - capsuleB->GetScale().y / 2)) * 0.5f);
//	//closest_point.y = tip_a.y + (dot * (base_a.y - tip_a.y)) + LineYCalculation;
//
//	//// NOTE: Calculating the Position
//	//closest_point.x = tip_a.x + (dot * (base_a.x - tip_a.x));
//	//closest_point.x = Clamp(closest_point.x, base_a.x, tip_a.x);
//	//closest_point.y = Clamp(closest_point.y, base_a.y, tip_a.y);
//
//	//DrawCircle(closest_point.x, closest_point.y, capsuleB->GetScale().x / 2, RED);
//
//	//// NOTE: Create the circle based of the capsule components
//	//OKTransform2<float> circle_transform = OKTransform2<float>(closest_point, OKVector2<float>(capsuleB->GetScale().x, capsuleB->GetScale().x), 0);
//	//ColliderEntitycircle_temp = Collider(&circle_transform, capsuleB->GetScale().x / 2.f);
//
//	//return t_ColMani = LineToCircle(lineA, &circle_temp);
//
//	// Capsule (A)
//	// NOTE: Capsule Position and Variable(s)
//	OKVector2<float> tip_a = OKVector2<float>(lineA->GetLineStart().x, lineA->GetLineStart().y);
//	OKVector2<float> base_a = OKVector2<float>(lineA->GetLineEnd().x, lineA->GetLineEnd().y);
//	float t_DistanceXA = tip_a.x - base_a.x;
//	float t_DistanceYA = tip_a.y - base_a.y;
//	float lenA = sqrt((t_DistanceXA * t_DistanceXA) + (t_DistanceYA * t_DistanceYA));
//	float dotA = ((capsuleB->GetPosition().x - tip_a.x) * (base_a.x - tip_a.x)) + ((capsuleB->GetPosition().y - tip_a.y) * (base_a.y - tip_a.y)) / pow(lenA, 2);
//
//	// Capsule (B)
//	OKVector2<float> tip_b = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y + (capsuleB->GetScale().y / 2) - (capsuleB->GetScale().x / 2));
//	OKVector2<float> base_b = OKVector2<float>(capsuleB->GetPosition().x, capsuleB->GetPosition().y - (capsuleB->GetScale().y / 2) + (capsuleB->GetScale().x / 2));
//	float t_DistanceXB = tip_b.x - base_b.x;
//	float t_DistanceYB = tip_b.y - base_b.y;
//	float lenB = sqrt((t_DistanceXB * t_DistanceXB) + (t_DistanceYB * t_DistanceYB));
//
//	OKVector2<float> MiddlePosition;
//	MiddlePosition.x = (lineA->GetLineStart().x + lineA->GetLineEnd().x) / 2.f;
//	MiddlePosition.y = (lineA->GetLineStart().y + lineA->GetLineEnd().y) / 2.f;
//
//	float dotB = ((MiddlePosition.x - tip_b.x) * (base_b.x - tip_b.x)) + ((MiddlePosition.y - tip_b.y) * (base_b.y - tip_b.y)) / pow(lenB, 2);
//
//	// NOTE: Closest Point (A)
//	OKVector2<float> closest_point_A;
//	closest_point_A.x = tip_a.x + (dotA * (base_a.x - tip_a.x)) / 2;
//	closest_point_A.y = tip_a.y + (dotA * (base_a.y - tip_a.y)) / 2;
//	closest_point_A.x = Clamp(closest_point_A.x, base_a.x, tip_a.x);
//	closest_point_A.y = Clamp(closest_point_A.y, base_a.y, tip_a.y);
//
//	// NOTE: Closest Point (B)
//	OKVector2<float> closest_point_B;
//	closest_point_B.x = tip_b.x + (dotB * (base_b.x - tip_b.x)) / 2;
//	closest_point_B.y = tip_b.y + (dotB * (base_b.y - tip_b.y)) / 2;
//	closest_point_B.x = Clamp(closest_point_B.x, base_b.x, tip_b.x);
//	closest_point_B.y = Clamp(closest_point_B.y, base_b.y, tip_b.y);
//
//	DrawCircleV(closest_point_A.ConvertToVec2(), 10.f, RED);
//	DrawCircleV(closest_point_B.ConvertToVec2(), 10.f, PURPLE);
//
//	// NOTE: Circle Construction (A)
//	OKTransform2<float> point_transform_A = OKTransform2<float>(closest_point_A, OKVector2<float>(0, 0), 0);
//	ColliderEntity point_temp_A = ColliderEntity(&point_transform_A, 1.f, true);
//
//	// NOTE: Circle Construction (B)
//	OKTransform2<float> circle_transform_B = OKTransform2<float>(closest_point_B, OKVector2<float>(0, 0), 0);
//	ColliderEntity circle_temp_B = ColliderEntity(&circle_transform_B, capsuleB->GetScale().x / 2);
//
//	t_ColMani = PointToCircle(&point_temp_A, &circle_temp_B);
//	return t_ColMani;
//}
