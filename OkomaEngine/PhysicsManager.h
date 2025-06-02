#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "GameObjectEntity.h"
#include "CollisionManifold.h"
#include "CollisionManager.h"
#include "CollisionResolutionManager.h"
#include "PhysicsMaterialCoefficientManager.h"

class PhysicsManager
{
private: // PRIVATE MANAGER VARIABLE(s)

	CollisionManifold m_CollisionManifold;
	CollisionManager m_ColliderManager;
	CollisionResolutionManager m_CollisionResolutionManager;
	PhysicsMaterialCoefficientManager m_PhysicsMaterialCoefficientManager;

private: // PRIVATE VECTOR VARIABLE(s)

	std::vector<GameObjectEntity*> m_PhysicsObjects;

public:

	// CLASS FUNCTION(s)
	PhysicsManager();
	~PhysicsManager();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();

};

#endif