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
	std::set<PhysicsObject*> m_ObjectInTrigger;
	ColliderManager* m_ColliderManifest;

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
	void CheckCollisions(PhysicsObject* physicsObject);
	void Draw();

	// TRIGGER RESPONSE FUNCTION(s)
	void TriggerEntered(PhysicsObject* physicsObject, void (*func)() = nullptr);
	void TriggerStayed(PhysicsObject* physicsObject, void (*func)() = nullptr);
	void TriggerExited(PhysicsObject* physicsObject, void (*func)() = nullptr);


	// GETTER FUNCTION(s)
	std::set<PhysicsObject*>& GetObjects() { return m_ObjectList; }


	// SETTER FUNCTION(s)


};

#endif