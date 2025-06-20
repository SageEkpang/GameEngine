#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	m_PhysicsObjects.clear();
}

PhysicsManager::~PhysicsManager()
{
	std::vector<GameObjectEntity*>::iterator itr;
}

//TODO_GLOBAL: Need like a level structure or structure that adds the objects if they have a physics entity on them, when a level structure is added, that is when that happens

void PhysicsManager::Update(const float deltaTime)
{
	std::vector<GameObjectEntity*> t_PhysicsObjects = m_PhysicsObjects;

	// NOTE: Collision Code
	// NOTE: Iterate through ALL the physics components
	for (unsigned int i = 0; i < t_PhysicsObjects.size(); ++i)
	{
		for (unsigned int j = 0; j < t_PhysicsObjects.size(); ++j)
		{
			// NOTE: Check if the indexs are not the same
			if (i == j) { continue; }

			// NOTE: Check if the physics component does have a collider on it, if not, we do not want to do anything with it
			if (t_PhysicsObjects[i]->FindChildComponent<ComponentEntity>() == nullptr || t_PhysicsObjects[j]->FindChildComponent<ComponentEntity>() == nullptr) { continue; }

			// NOTE: Check Collisions between the two physics components
			m_CollisionManifold = m_ColliderManager.CheckCollisions(t_PhysicsObjects[i], t_PhysicsObjects[j]);
			if (m_CollisionManifold.m_HasCollision == true)
			{
				// NOTE: Checks if the physics components actually have rigid bodies on them
				if (!t_PhysicsObjects[i]->HasComponent<Rigidbody2DComponent>() || !t_PhysicsObjects[j]->HasComponent<Rigidbody2DComponent>()) { continue; }

				// NOTE: Resolve the Collisions between two game objects when they have a collider and a physics component on them
				m_CollisionResolutionManager.ResolveCollision
				(
					t_PhysicsObjects[i],
					t_PhysicsObjects[j],
					float(0.9f),
					m_CollisionManifold
				);
			}
		}
	}

	// NOTE: Physics Code
	if (!t_PhysicsObjects.empty())
	{
		for (int i = 0; i < t_PhysicsObjects.size(); ++i)
		{
			// NOTE: Check if there is a physics entity on the entity, if not, then continue and add to the physics index
			if (t_PhysicsObjects[i]->FindChildComponent<PhysicsEntity>() == nullptr)
			{
				continue;
			}

			// NOTE: Check if there has been a collision]
			if (t_PhysicsObjects[i]->FindChildComponent<ColliderEntity>()->m_HasCollided)
			{
				// NOTE: Check if any of the colliders are any trigger areas
				if (t_PhysicsObjects[i]->FindChildComponent<ColliderEntity>()->m_IsTrigger == true)
				{
					t_PhysicsObjects[i]->FindChildComponent<ColliderEntity>()->TriggerQueryExecute();
					continue;
				}

				if (t_PhysicsObjects[i]->HasComponent<Rigidbody2DComponent>())
				{
					// NOTE: If the game object is not a trigger area, simulate the required physics for it 
					t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateDrag(false);
					t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateLift(false);

					t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->m_Friction = 0.5f;
					t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateFriction(true);
				}
			}
			else
			{
				if (t_PhysicsObjects[i]->HasComponent<Rigidbody2DComponent>())
				{
					t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateDrag(true);
					t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateLift(true);
					t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateFriction(false);
				}
			}

			// NOTE: Update the physics objects
			t_PhysicsObjects[i]->Update(deltaTime);
		}

		// NOTE: Gain a list of indexes to remove the physics entity from the physics list,
		// if any game object does not have a physics component any more
		for (auto itr = m_PhysicsObjects.begin(); itr != m_PhysicsObjects.end();)
		{
			// NOTE: Delete the physics object if no physics component can be found on the game object
			if ((*itr)->FindChildComponent<PhysicsEntity>()  == nullptr)
			{
				// NOTE: swap the current index to the start
				if (itr != m_PhysicsObjects.begin())
				{
					std::swap(*m_PhysicsObjects.end(), *itr);
				}

				m_PhysicsObjects.erase(m_PhysicsObjects.end());
			}
			else
			{
				// NOTE: if it does have the component, move to the next itr position
				++itr;
			}
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
