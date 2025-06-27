#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

// BASE INCLUDE(s)
#include "HeaderManager.h"

// CLASS(es) FOR DRAWING
#include "OKVector2.h"

class GameObjectEntity;

#include "GameObjectEntity.h"
#include "RectangleColliderComponent.h"
#include "OrientedRectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "CapsuleColliderComponent.h"

#include "PointColliderComponent.h"
#include "LineColliderComponent.h"
#include "ComplexColliderComponent.h"

#include "Rigidbody2DComponent.h"

// TODO: Finish this

namespace DebugDraw
{
	namespace Shape
	{
		void DebugCollider(GameObjectEntity* gameObject);

		void DebugRectangle(GameObjectEntity* gameObject);
		void DebugOrientedRectangle(GameObjectEntity* gameObject);
		void DebugCircle(GameObjectEntity* gameObject);
		void DebugCapsule(GameObjectEntity* gameObject);

		void DebugPoint(GameObjectEntity* gameObject);
		void DebugLines(GameObjectEntity* gameObject);
		void DebugComplexShape(GameObjectEntity* gameObject);
	}

	namespace Physics
	{
		void DebugGravityLine(GameObjectEntity* gameObject);
		void DebugVelocityLine(GameObjectEntity* gameObject);
		void DebugDirectionLine(GameObjectEntity* gameObject);
		void DebugLiftLine(GameObjectEntity* gameObject);
		void DebugDragLine(GameObjectEntity* gameObject);
		void DebugFrictionLine(GameObjectEntity* gameObject);
	}
};

#endif

