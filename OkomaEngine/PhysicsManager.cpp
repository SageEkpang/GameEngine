#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{
	std::vector<GameObjectEntity*>::iterator itr;
}

void PhysicsManager::Update(const float deltaTime)
{
	std::vector<GameObjectEntity*> t_PhysicsObjects = m_PhysicsObjects;

	// NOTE: Collision Code
	// NOTE: Iterate through ALL the physics components
	for (unsigned int i = 0; i < t_PhysicsObjects.size(); ++i)
	{
		for (unsigned int j = 0; j < t_PhysicsObjects.size(); ++j)
		{
			if (i == j) { continue; }

			// NOTE: Check Collisions between the two physics components
			m_CollisionManifold = m_ColliderManager.CheckCollisions(t_PhysicsObjects[i], t_PhysicsObjects[j]);
			if (m_CollisionManifold.m_HasCollision == true)
			{
				// NOTE: Checks if the physics components actually have rigid bodies on them
				if (!t_PhysicsObjects[i]->HasComponent<Rigidbody2DComponent>() || !t_PhysicsObjects[j]->HasComponent<Rigidbody2DComponent>()) { continue; }

				// NOTE: Resolve the Collisions
				m_CollisionResolutionManager.ResolveCollision
				(
					t_PhysicsObjects[i],
					t_PhysicsObjects[j],
					float(0.1f),
					m_CollisionManifold
				);
			}
		}
	}

	// NOTE: Physics Code
	if (!t_PhysicsObjects.empty())
	{
		for (auto& v : t_PhysicsObjects)
		{
			// NOTE: Check if there has been a collision]
			if (v->FindChildComponent<ColliderEntity>()->m_HasCollided)
			{
				// NOTE: Check if any of the colliders are any trigger areas
				if (v->FindChildComponent<ColliderEntity>()->m_IsTrigger == true)
				{
					v->FindChildComponent<ColliderEntity>()->TriggerQueryExecute();
					continue;
				}

				if (v->HasComponent<Rigidbody2DComponent>())
				{
					// NOTE: If the game object is not a trigger area, simulate the required physics for it 
					v->GetComponent<Rigidbody2DComponent>()->SimulateDrag(false);
					v->GetComponent<Rigidbody2DComponent>()->SimulateLift(false);

					v->GetComponent<Rigidbody2DComponent>()->m_Friction = 0.5f;
					v->GetComponent<Rigidbody2DComponent>()->SimulateFriction(true);
				}
			}
			else
			{
				if (v->HasComponent<Rigidbody2DComponent>())
				{
					v->GetComponent<Rigidbody2DComponent>()->SimulateDrag(true);
					v->GetComponent<Rigidbody2DComponent>()->SimulateLift(true);
					v->GetComponent<Rigidbody2DComponent>()->SimulateFriction(false);
				}
			}

			v->Update(deltaTime);
		}
	}
}

void PhysicsManager::Draw()
{
	if (!m_PhysicsObjects.empty())
	{
		for (auto& v : m_PhysicsObjects)
		{
			// NOTE: Check if the Physics Components has a collider to show, if not...SKIP
			if (v->FindChildComponent<ColliderEntity>() == nullptr) { continue; }

			// NOTE: Draw the Shape Collider
			DebugDraw::Shape::DebugCollider(v);

			// NOTE: Draw the Different Physics Components
			//DebugDraw::Physics::DebugGravityLine(v->GetComponent<Rigidbody2DComponent>()->GetCurrentGravity());
			//DebugDraw::Physics::DebugDragLine(v->GetComponent<Rigidbody2DComponent>()->GetCurrentDrag());
			//DebugDraw::Physics::DebugLiftLine(v->GetComponent<Rigidbody2DComponent>()->GetCurrentLift());
			//DebugDraw::Physics::DebugFrictionLine(v->GetComponent<Rigidbody2DComponent>()->GetCurrentFriction());
			//DebugDraw::Physics::DebugVelocityLine(v->GetComponent<Rigidbody2DComponent>()->GetVelocity());
			//DebugDraw::Physics::DebugVelocityLine(v->GetComponent<Rigidbody2DComponent>()->GetDirection());
		}
	}
}
