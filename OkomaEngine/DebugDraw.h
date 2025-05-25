#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

// BASE INCLUDE(s)
#include "HeaderManager.h"

// CLASS(es) FOR DRAWING
#include "OKVector2.h"

class GameObjectEntity;

// TODO: Finish this

namespace DebugDraw
{
	namespace Shape
	{
		void DebugRectangle(GameObjectEntity* gameObject);
		void DebugCircle(GameObjectEntity* gameObject);
		void DebugCapsule(GameObjectEntity* gameObject);
		void DebugLines(GameObjectEntity* gameObject);
		void DebugComplexShape(GameObjectEntity* gameObject);
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

