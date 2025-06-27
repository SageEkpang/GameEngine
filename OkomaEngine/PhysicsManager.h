#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "GameObjectEntity.h"
#include "CollisionManifold.h"
#include "CollisionManager.h"
#include "CollisionResolutionManager.h"
#include "DebugDraw.h"

class PhysicsManager
{
private: // PRIVATE MANAGER VARIABLE(s)

	CollisionManifold m_CollisionManifold;
	CollisionManager m_ColliderManager;
	CollisionResolutionManager m_CollisionResolutionManager;

private: // PRIVATE VECTOR VARIABLE(s)

	std::vector<GameObjectEntity*> m_PhysicsObjects;

	// NOTE: Drawing Debug Information 
	bool m_DrawDebugColliders = false;

	bool m_DrawDebugGravity = false;
	bool m_DrawDebugDrag = false;
	bool m_DrawDebugLift = false;
	bool m_DrawDebugFriction = false;
	bool m_DrawDebugVelocity = false;
	bool m_DrawDebugDirection = false;

public:

	// CLASS FUNCTION(s)
	PhysicsManager();
	~PhysicsManager();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();

	// HELPER FUNCTION(s)
	inline void AddPhysicsObject(GameObjectEntity* gameObject) { m_PhysicsObjects.push_back(gameObject); }


	// GETTER FUNCTION(s)


	// SETTER FUNCTION(s)
	inline void SetDrawColliders(bool drawDebug) { m_DrawDebugColliders = drawDebug; }

	// TODO: Add line multipliers to these
	inline void SetDrawDebugVelocity(bool drawDebug) { m_DrawDebugVelocity = drawDebug; }
	inline void SetDrawDebugDirection(bool drawDebug) { m_DrawDebugDirection = drawDebug; }
	inline void SetDrawDebugGravity(bool drawDebug) { m_DrawDebugGravity = drawDebug; }
	inline void SetDrawDebugDrag(bool drawDebug) { m_DrawDebugDrag = drawDebug; }
	inline void SetDrawDebugLift(bool drawDebug) { m_DrawDebugLift = drawDebug; }
	inline void SetDrawDebugFriction(bool drawDebug) { m_DrawDebugFriction = drawDebug; }

};

#endif