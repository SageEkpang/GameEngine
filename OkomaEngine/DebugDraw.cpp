#include "DebugDraw.h"
#include "GameObjectEntity.h"
#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "ComplexColliderComponent.h"
#include "LineColliderComponent.h"

#include "Rigidbody2DComponent.h"

namespace DebugDraw
{
	namespace Shape
	{
		void DebugRectangle(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<RectangleColliderComponent>())
			{
				DrawRectangleLines((int)gameObject->m_Transform.position.x - (int)(gameObject->GetComponent<RectangleColliderComponent>()->m_Scale.x / 2.f), (int)gameObject->m_Transform.position.y - (int)(gameObject->GetComponent<RectangleColliderComponent>()->m_Scale.y / 2.f), (int)gameObject->GetComponent<RectangleColliderComponent>()->m_Scale.x, (int)gameObject->GetComponent<RectangleColliderComponent>()->m_Scale.y, GREEN);
			}
		}

		void DebugCircle(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<CircleColliderComponent>())
			{
				DrawCircleLinesV(gameObject->m_Transform.position.ConvertToVec2(), gameObject->GetComponent<CircleColliderComponent>()->m_Radius, GREEN);
			}
		}

		void DebugCapsule(GameObjectEntity* gameObject)
		{


		}

		void DebugLines(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<LineColliderComponent>())
			{
				DrawLineV(gameObject->GetComponent<LineColliderComponent>()->m_LineStartPosition.ConvertToVec2(), gameObject->GetComponent<LineColliderComponent>()->m_LineEndPosition.ConvertToVec2(), GREEN);
			}
		}

		void DebugComplexShape(GameObjectEntity* gameObject)
		{
			// DrawLineStrip(complexComponent.m_Vertices, complexComponent.m_Vertices.size(), GREEN);
		}
	}

	namespace Physics
	{
		void DebugGravityLine(OKVector2<float> gravity)
		{
			// Vector2 t_GravityVec = Vector2Add(gravity.ConvertToVec2(), m_Position.ConvertToVec2());
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