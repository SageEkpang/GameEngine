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

				// NOTE: Temp bounce variable for the Coef of Rest
				float t_BounceAmount = 0.5f;

				// NOTE: Assign a Coefficient of Restituion via the Physics Material on whatever object is static
				// FURTHER_NOTE: If both items are static, it will not matter
				// if (t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->m_RigidbodyMovementType == RIGIDBODY_MOVEMENT_TYPE_STATIC)
				// { t_BounceAmount = t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->m_PhysicsMaterial; }

				// if (t_PhysicsObjects[j]->GetComponent<Rigidbody2DComponent>()->m_RigidbodyMovementType == RIGIDBODY_MOVEMENT_TYPE_STATIC)
				// { t_BounceAmount = t_PhysicsObjects[j]->GetComponent<Rigidbody2DComponent>()->m_PhysicsMaterial; }

				// NOTE: Resolve the Collisions between two game objects when they have a collider and a physics component on them
				m_CollisionResolutionManager.ResolveCollision
				(
					t_PhysicsObjects[i],
					t_PhysicsObjects[j],
					float(t_BounceAmount),
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
			//if (t_PhysicsObjects[i]->FindChildComponent<PhysicsEntity>() == nullptr) 
			//{ 
			//	continue; 
			//}

			//// NOTE: Check if any of the colliders are any trigger areas
			//if (t_PhysicsObjects[i]->FindChildComponent<ColliderEntity>()->m_IsTrigger == true)
			//{
			//	t_PhysicsObjects[i]->FindChildComponent<ColliderEntity>()->TriggerQueryExecute();
			//	continue;
			//}

			//// NOTE: Check if there has been a collision]
			//if (t_PhysicsObjects[i]->FindChildComponent<ColliderEntity>()->m_HasCollided)
			//{

			//	//if (t_PhysicsObjects[i]->HasComponent<Rigidbody2DComponent>())
			//	//{
			//	//	// NOTE: If the game object is not a trigger area, simulate the required physics for it 
			//	//	t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateDrag(false);
			//	//	t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateLift(false);

			//	//	t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->m_Friction = t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->m_FrictionMaterial;
			//	//	t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateFriction(true);
			//	//}
			//}
			//else
			//{
			//	//if (t_PhysicsObjects[i]->HasComponent<Rigidbody2DComponent>())
			//	//{
			//	//	t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateDrag(true);
			//	//	t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateLift(true);
			//	//	t_PhysicsObjects[i]->GetComponent<Rigidbody2DComponent>()->SimulateFriction(false);
			//	//}
			//}

			// NOTE: Update the physics objects
			t_PhysicsObjects[i]->Update(deltaTime);
		}

		// NOTE: Gain a list of indexes to remove the physics entity from the physics list,
		// if any game object does not have a physics component any more
		//for (auto itr = m_PhysicsObjects.begin(); itr != m_PhysicsObjects.end();)
		//{
		//	// NOTE: Delete the physics object if no physics component can be found on the game object
		//	if ((*itr)->FindChildComponent<PhysicsEntity>()  == nullptr)
		//	{
		//		// NOTE: swap the current index to the start
		//		if (itr != m_PhysicsObjects.begin())
		//		{
		//			std::swap(*m_PhysicsObjects.end(), *itr);
		//		}

		//		m_PhysicsObjects.erase(m_PhysicsObjects.end());
		//	}
		//	else
		//	{
		//		// NOTE: if it does have the component, move to the next itr position
		//		++itr;
		//	}
		//}
	}
}

void PhysicsManager::Draw()
{
	if (!m_PhysicsObjects.empty())
	{
		for (auto& v : m_PhysicsObjects)
		{
			// NOTE: Draw the Shape Collider
			if (m_DrawDebugColliders == true && v->FindChildComponent<ColliderEntity>() != nullptr) { DebugDraw::Shape::DebugCollider(v); }

			// NOTE: Skip iterations if no derived physics entities are in the component list
			if (v->FindChildComponent<PhysicsEntity>() == nullptr) { continue; }

			// NOTE: Draw Physics Lines
			if (m_DrawDebugVelocity == true) { DebugDraw::Physics::DebugVelocityLine(v); }
			if (m_DrawDebugDirection == true) { DebugDraw::Physics::DebugDirectionLine(v); }

			if (m_DrawDebugGravity == true) { DebugDraw::Physics::DebugGravityLine(v); }
			if (m_DrawDebugFriction == true) { DebugDraw::Physics::DebugFrictionLine(v); }
			if (m_DrawDebugDrag == true) { DebugDraw::Physics::DebugDragLine(v); }
			if (m_DrawDebugLift == true) { DebugDraw::Physics::DebugLiftLine(v); }
		}
	}
}
