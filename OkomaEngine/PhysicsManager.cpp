#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Update(const float deltaTime)
{
	for (unsigned int i = 0; i < m_PhysicsObjects.size(); ++i)
	{
		for (unsigned int j = 0; j < m_PhysicsObjects.size(); ++j)
		{
			if (i == j) { continue; }


			// m_CollisionManifold = m_ColliderManager.CheckCollisions();

			if (m_CollisionManifold.m_HasCollision == true)
			{
				// m_CollisionResolution.ResolveCollision();

			}
		}
	}

	if (!m_PhysicsObjects.empty())
	{
		for (auto& v : m_PhysicsObjects)
		{
			// trigger stuff
			if (true)
			{

			}
			else
			{

			}
		}
	}
}

void PhysicsManager::Draw()
{

}
