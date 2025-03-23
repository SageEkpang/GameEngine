#ifndef TRIGGER_AREA_H
#define TRIGGER_AREA_H

// PARENT CLASS
#include "Collider.h"
#include "ColliderManager.h"
#include <set>

class PhysicsObject;

class TriggerArea : public Collider
{
private:

	bool m_IsActive = true;
	bool m_HasEntered = false;
	bool m_HasStayed = false;
	bool m_HasExited = false;

	std::set<PhysicsObject*> m_ObjectList;
	ColliderManager* m_ColliderManifest;

	//std::set<std::unique_ptr<PhysicsObject>> thing;

public:

	// CLASS FUNCTION(s)

	// RECTANGLE
	/// @brief Rectangle Collider Constructor
	TriggerArea(const char* tag, OKTransform2<float>* transform, bool IsCapsule = false, bool lockZRot = true);

	// CIRCLE
	/// @brief Circle Collider Constructor
	TriggerArea(const char* tag, OKTransform2<float>* transform, float radius);


	// DESTRUCTOR
	~TriggerArea();

	// BASE FUNCTION(s)
	void Draw();

	// TRIGGER RESPONSE FUNCTION(s)
	void TriggerEntered(PhysicsObject* physicsObject, void (*func)() = nullptr);
	void TriggerStayed(PhysicsObject* physicsObject, void (*func)() = nullptr);
	void TriggerExited(PhysicsObject* physicsObject, void (*func)() = nullptr);


	// GETTER FUNCTION(s)
	std::set<PhysicsObject*>& GetObjects() { return m_ObjectList; }
	inline bool GetActiveState() const { return m_IsActive; }

	// SETTER FUNCTION(s)
	inline bool SetActiveState(bool active) { m_IsActive = active; }

};

#endif