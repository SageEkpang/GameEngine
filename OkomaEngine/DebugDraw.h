#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

// BASE INCLUDE(s)
#include "HeaderManager.h"

// CLASS(es) FOR DRAWING
#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "ComplexColliderComponent.h"
#include "LineColliderComponent.h"

#include "OKVector2.h"

// TODO: Finish this

namespace DebugDraw
{
	namespace Shape
	{
		void DebugRectangle(RectangleColliderComponent rectangleComponent);
		void DebugCircle(CircleColliderComponent circleComponent);
		void DebugCapsule(CapsuleColliderComponent capsuleComponent);
		void DebugLines(LineColliderComponent lineComponent);
		void DebugComplexShape(ComplexColliderComponent complexComponent);
	}

	namespace Physics
	{
		void DebugGravityLine(OKVector2<float> gravity);
		void DebugVelocityLine(OKVector2<float> velocity);
		void DebugDirectionLine(OKVector2<float> direction, float lengthMultiplier = 1.f);
		void DebugLiftLine(OKVector2<float> lift);
		void DebugDragLine(OKVector2<float> drag);
		void DebugFrictionLine(OKVector2<float> friction);
	}
};

#endif

