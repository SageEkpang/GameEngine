#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "CollisionManifold.h"
#include "CollisionManager.h"
#include "CollisionResolution.h"
#include "PhysicsMaterialCoefficientManager.h"

#include "PhysicsObject.h"

class PhysicsManager
{
private: // PRIVATE MANAGER VARIABLE(s)

	CollisionManifold m_CollisionManifold;
	CollisionManager m_ColliderManager;
	CollisionResolution m_CollisionResolution;
	PhysicsMaterialCoefficientManager m_PhysicsMaterialCoefficientManager;

private: // PRIVATE VECTOR VARIABLE(s)

	// TODO: Need to change this to "entity" list
	std::vector<PhysicsObject*> m_PhysicsObjects;

public:

	// CLASS FUNCTION(s)
	PhysicsManager();
	~PhysicsManager();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();

};

#endif