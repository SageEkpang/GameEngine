#include "DebugDraw.h"

namespace DebugDraw
{
	namespace Shape
	{
		void DebugRectangle(RectangleColliderComponent rectangleComponent)
		{
			DrawRectangleLines((int)rectangleComponent.m_Position.x - (int)(rectangleComponent.m_Scale.x / 2.f), (int)rectangleComponent.m_Position.y - (int)(rectangleComponent.m_Scale.y / 2.f), (int)rectangleComponent.m_Scale.x, (int)rectangleComponent.m_Scale.y, GREEN);
		}

		void DebugCircle(CircleColliderComponent circleComponent)
		{
			DrawCircleLinesV(circleComponent.m_Position.ConvertToVec2(), circleComponent.m_Radius, GREEN);
		}

		void DebugCapsule(CapsuleColliderComponent capsuleComponent)
		{


		}

		void DebugLines(LineColliderComponent lineComponent)
		{
			DrawLineV(lineComponent.m_LineStartPosition.ConvertToVec2(), lineComponent.m_LineEndPosition.ConvertToVec2(), GREEN);
		}

		void DebugComplexShape(ComplexColliderComponent complexComponent)
		{
			// DrawLineStrip(complexComponent.m_Vertices, complexComponent.m_Vertices.size(), GREEN);
		}
	}

	namespace Physics
	{
		void DebugGravityLine(OKVector2<float> gravity)
		{
			// Vector2 t_GravityVec = Vector2Add(pm_CalculatedGravity.ConvertToVec2(), m_Position.ConvertToVec2());
			// DrawLineV(m_Position.ConvertToVec2(), t_GravityVec, PURPLE);

		}

		void DebugVelocityLine(OKVector2<float> velocity)
		{
			// Vector2 t_VecEnd = Vector2Multiply(m_Velocity.normalise().ConvertToVec2(), Vector2{ m_Velocity.magnitude(), m_Velocity.magnitude() });
			//    t_VecEnd = Vector2Add(t_VecEnd, m_Position.ConvertToVec2());
			//    DrawLineV(m_Position.ConvertToVec2(), t_VecEnd, GREEN);

		}

		void DebugDirectionLine(OKVector2<float> direction, float lengthMultiplier)
		{


		}

		void DebugLiftLine(OKVector2<float> lift)
		{


		}

		void DebugDragLine(OKVector2<float> drag)
		{
			//    Vector2 t_DragVec = Vector2Add(pm_CalculatedDrag.ConvertToVec2(), m_Transform->position.ConvertToVec2());
			//    DrawLineV(m_Transform->position.ConvertToVec2(), t_DragVec, BLUE);

		}

		void DebugFrictionLine(OKVector2<float> friction)
		{


		}
	}
};