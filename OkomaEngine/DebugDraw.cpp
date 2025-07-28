#include "DebugDraw.h"

namespace DebugDraw
{
	namespace Shape
	{
		void DebugCollider(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<RectangleColliderComponent>()) { DebugRectangle(gameObject); return; }
			if (gameObject->HasComponent<OrientedRectangleColliderComponent>()) { DebugOrientedRectangle(gameObject); return; }
			if (gameObject->HasComponent<CircleColliderComponent>()) { DebugCircle(gameObject); return; }
			if (gameObject->HasComponent<CapsuleColliderComponent>()) { DebugCapsule(gameObject); return; }
			if (gameObject->HasComponent<PointColliderComponent>()) { DebugPoint(gameObject); return; }
			if (gameObject->HasComponent<LineColliderComponent>()) { DebugLines(gameObject); return; }
			if (gameObject->HasComponent<ComplexColliderComponent>()) { DebugComplexShape(gameObject); return; }
		}

		void DebugRectangle(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<RectangleColliderComponent>())
			{
				DrawRectangleLines(
				(int)(gameObject->m_Transform.position.x + gameObject->GetComponent<RectangleColliderComponent>().m_Offset.x) - (int)(gameObject->GetComponent<RectangleColliderComponent>().m_Scale.x / 2.f), 
				(int)(gameObject->m_Transform.position.y + gameObject->GetComponent<RectangleColliderComponent>().m_Offset.y) - (int)(gameObject->GetComponent<RectangleColliderComponent>().m_Scale.y / 2.f), 
				(int)gameObject->GetComponent<RectangleColliderComponent>().m_Scale.x, 
				(int)gameObject->GetComponent<RectangleColliderComponent>().m_Scale.y, 
				GREEN
				);
			}
		}

		void DebugOrientedRectangle(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<OrientedRectangleColliderComponent>())
			{
				Rectangle t_tempRec = {
					(gameObject->m_Transform.position.x + gameObject->GetComponent<OrientedRectangleColliderComponent>().m_Offset.x),
					(gameObject->m_Transform.position.y + gameObject->GetComponent<OrientedRectangleColliderComponent>().m_Offset.y),
					gameObject->GetComponent<OrientedRectangleColliderComponent>().m_Scale.x,
					gameObject->GetComponent<OrientedRectangleColliderComponent>().m_Scale.y
				};

				DrawRectanglePro(
				t_tempRec, 
				OKVector2<float>(t_tempRec.width / 2.f, t_tempRec.height / 2.f).ConvertToVec2(), 
				gameObject->GetComponent<OrientedRectangleColliderComponent>().m_Rotation,
				GREEN
				);
			}
		}

		void DebugCircle(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<CircleColliderComponent>())
			{
				DrawCircleLinesV((gameObject->m_Transform.position + gameObject->GetComponent<CircleColliderComponent>().m_Offset).ConvertToVec2(), gameObject->GetComponent<CircleColliderComponent>().m_Radius, GREEN);
			}
		}

		void DebugCapsule(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<CapsuleColliderComponent>())
			{
				DrawCircleLines(
				(int)(gameObject->m_Transform.position.x + gameObject->GetComponent<CapsuleColliderComponent>().m_Offset.x), 
				(int)(gameObject->m_Transform.position.y + gameObject->GetComponent<CapsuleColliderComponent>().m_Height / 4.f) + (int)gameObject->GetComponent<CapsuleColliderComponent>().m_Offset.y,
				(gameObject->GetComponent<CapsuleColliderComponent>().m_Width / 2.f), 
				GREEN
				);

				DrawRectangleLines(
				(int)(gameObject->m_Transform.position.x + gameObject->GetComponent<CapsuleColliderComponent>().m_Offset.x) - (int)(gameObject->GetComponent<CapsuleColliderComponent>().m_Width / 2.f),
				(int)(gameObject->m_Transform.position.y + gameObject->GetComponent<CapsuleColliderComponent>().m_Offset.y) - (int)(gameObject->GetComponent<CapsuleColliderComponent>().m_Height / 4.f),
				(int)gameObject->GetComponent<CapsuleColliderComponent>().m_Width,
				(int)gameObject->GetComponent<CapsuleColliderComponent>().m_Height / 2,
				GREEN
				);
				
				DrawCircleLines(
				(int)(gameObject->m_Transform.position.x + gameObject->GetComponent<CapsuleColliderComponent>().m_Offset.x),
				(int)(gameObject->m_Transform.position.y - gameObject->GetComponent<CapsuleColliderComponent>().m_Height / 4.f) + (int)gameObject->GetComponent<CapsuleColliderComponent>().m_Offset.y,
				(gameObject->GetComponent<CapsuleColliderComponent>().m_Width / 2.f), 
				GREEN
				);
			}
		}

		void DebugPoint(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<PointColliderComponent>())
			{
				DrawCircleLinesV((gameObject->m_Transform.position + gameObject->GetComponent<PointColliderComponent>().m_Offset).ConvertToVec2(), gameObject->GetComponent<PointColliderComponent>().m_Radius, GREEN);
			}
		}

		void DebugLines(GameObjectEntity* gameObject)
		{
			if (gameObject->HasComponent<LineColliderComponent>())
			{
				DrawLineV(gameObject->GetComponent<LineColliderComponent>().m_LineStartPosition.ConvertToVec2(), gameObject->GetComponent<LineColliderComponent>().m_LineEndPosition.ConvertToVec2(), GREEN);
			}
		}

		void DebugComplexShape(GameObjectEntity* gameObject)
		{
			// DrawLineStrip(complexComponent.m_Vertices, complexComponent.m_Vertices.size(), GREEN);
		}
	}

	namespace Physics
	{
		void DebugGravityLine(GameObjectEntity* gameObject)
		{
			if (!gameObject->HasComponent<Rigidbody2DComponent>()) { return; }
			OKVector2<float> t_CurrentGravity = gameObject->GetComponent<Rigidbody2DComponent>().GetCurrentGravity().normalise();
			OKVector2<float> t_NewGravity = (t_CurrentGravity * 10.f) + gameObject->m_Transform.position;
			DrawLineV(gameObject->m_Transform.position.ConvertToVec2(), t_NewGravity.ConvertToVec2(), PURPLE);
		}

		void DebugVelocityLine(GameObjectEntity* gameObject)
		{
			if (!gameObject->HasComponent<Rigidbody2DComponent>()) { return; }
			OKVector2<float> t_CurrentVelocity = gameObject->GetComponent<Rigidbody2DComponent>().m_Velocity;
			OKVector2<float> t_NewVelocity = (t_CurrentVelocity / 10.f) + gameObject->m_Transform.position;
			DrawLineV(gameObject->m_Transform.position.ConvertToVec2(), t_NewVelocity.ConvertToVec2(), GREEN);

		}

		void DebugDirectionLine(GameObjectEntity* gameObject)
		{
			if (!gameObject->HasComponent<Rigidbody2DComponent>()) { return; }
			OKVector2<float> t_CurrentDirection = gameObject->GetComponent<Rigidbody2DComponent>().m_Velocity.normalise();
			OKVector2<float> t_NewDirection = (t_CurrentDirection * 10.f) + gameObject->m_Transform.position;
			DrawLineV(gameObject->m_Transform.position.ConvertToVec2(), t_NewDirection.ConvertToVec2(), RED);
		}

		void DebugLiftLine(GameObjectEntity* gameObject)
		{
			if (!gameObject->HasComponent<Rigidbody2DComponent>()) { return; }
			OKVector2<float> t_CurrentLift = gameObject->GetComponent<Rigidbody2DComponent>().GetCurrentLift();
			OKVector2<float> t_NewLift = (t_CurrentLift * 10.f) + gameObject->m_Transform.position;
			DrawLineV(gameObject->m_Transform.position.ConvertToVec2(), t_NewLift.ConvertToVec2(), BLUE);
		}

		void DebugDragLine(GameObjectEntity* gameObject)
		{
			if (!gameObject->HasComponent<Rigidbody2DComponent>()) { return; }
			OKVector2<float> t_CurrentDrag = gameObject->GetComponent<Rigidbody2DComponent>().GetCurrentDrag();
			OKVector2<float> t_NewDrag = (t_CurrentDrag * 10.f) + gameObject->m_Transform.position;
			DrawLineV(gameObject->m_Transform.position.ConvertToVec2(), t_NewDrag.ConvertToVec2(), YELLOW);
		}

		void DebugFrictionLine(GameObjectEntity* gameObject)
		{
			if (!gameObject->HasComponent<Rigidbody2DComponent>()) { return; }
			OKVector2<float> t_CurrentFriction = gameObject->GetComponent<Rigidbody2DComponent>().GetCurrentFriction();
			OKVector2<float> t_NewFriction = (t_CurrentFriction * 10.f) + gameObject->m_Transform.position;
			DrawLineV(gameObject->m_Transform.position.ConvertToVec2(), t_NewFriction.ConvertToVec2(), ORANGE);
		}
	}
};