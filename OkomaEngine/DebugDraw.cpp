#include "DebugDraw.h"

namespace DebugDraw
{
	namespace Shape
	{
		void DebugRectangle(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<RectangleColliderComponent>())
			{
				DrawRectangleLines(
				(int)(gameObject->m_Transform.position.x + gameObject->GetComponent<RectangleColliderComponent>()->m_Offset.x) - (int)(gameObject->GetComponent<RectangleColliderComponent>()->m_Scale.x / 2.f), 
				(int)(gameObject->m_Transform.position.y + gameObject->GetComponent<RectangleColliderComponent>()->m_Offset.y) - (int)(gameObject->GetComponent<RectangleColliderComponent>()->m_Scale.y / 2.f), 
				(int)gameObject->GetComponent<RectangleColliderComponent>()->m_Scale.x, 
				(int)gameObject->GetComponent<RectangleColliderComponent>()->m_Scale.y, 
				GREEN
				);
			}
		}

		void DebugCircle(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<CircleColliderComponent>())
			{
				DrawCircleLinesV((gameObject->m_Transform.position + gameObject->GetComponent<CircleColliderComponent>()->m_Offset).ConvertToVec2(), gameObject->GetComponent<CircleColliderComponent>()->m_Radius, GREEN);
			}
		}

		void DebugCapsule(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<CapsuleColliderComponent>())
			{
				DrawCircleLines(
				(int)(gameObject->m_Transform.position.x + gameObject->GetComponent<CapsuleColliderComponent>()->m_Offset.x), 
				(int)(gameObject->m_Transform.position.y + gameObject->GetComponent<CapsuleColliderComponent>()->m_Height / 4.f) + gameObject->GetComponent<CapsuleColliderComponent>()->m_Offset.y,
				(int)(gameObject->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f), 
				GREEN
				);

				DrawRectangleLines(
				(int)(gameObject->m_Transform.position.x + gameObject->GetComponent<CapsuleColliderComponent>()->m_Offset.x) - (int)(gameObject->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f),
				(int)(gameObject->m_Transform.position.y + gameObject->GetComponent<CapsuleColliderComponent>()->m_Offset.y) - (int)(gameObject->GetComponent<CapsuleColliderComponent>()->m_Height / 4.f),
				(int)gameObject->GetComponent<CapsuleColliderComponent>()->m_Width,
				(int)gameObject->GetComponent<CapsuleColliderComponent>()->m_Height / 2.f,
				GREEN
				);
				
				DrawCircleLines(
				(int)(gameObject->m_Transform.position.x + gameObject->GetComponent<CapsuleColliderComponent>()->m_Offset.x),
				(int)(gameObject->m_Transform.position.y - gameObject->GetComponent<CapsuleColliderComponent>()->m_Height / 4.f) + gameObject->GetComponent<CapsuleColliderComponent>()->m_Offset.y,
				(int)(gameObject->GetComponent<CapsuleColliderComponent>()->m_Width / 2.f), 
				GREEN
				);
			}
		}

		void DebugPoint(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<PointColliderComponent>())
			{
				DrawCircleLinesV((gameObject->m_Transform.position + gameObject->GetComponent<PointColliderComponent>()->m_Offset).ConvertToVec2(), gameObject->GetComponent<PointColliderComponent>()->m_Radius, GREEN);
			}
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