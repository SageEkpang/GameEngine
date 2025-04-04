#ifndef TRIGGER_AREA_H
#define TRIGGER_AREA_H

// PARENT CLASS
#include "Collider.h"
#include "ColliderManager.h"
#include <set>
#include <bitset>

class PhysicsObject;

class TriggerArea : public Collider
{
private:

	std::string m_Tag;
	bool m_IsActive = true;
	bool m_HasEntered = false;
	bool m_HasStayed = false;
	bool m_HasExited = false;

	std::set<PhysicsObject*> m_ObjectList;
	ColliderManager m_ColliderManifest;

public:

	// CLASS FUNCTION(s)

	// RECTANGLE
	/// @brief Rectangle Collider Constructor
	TriggerArea(std::string tag, OKTransform2<float>* transform, bool IsCapsule = false, bool lockZRot = true);

	// CIRCLE
	/// @brief Circle Collider Constructor
	TriggerArea(std::string tag, OKTransform2<float>* transform, float radius);


	// DESTRUCTOR
	~TriggerArea();

	// BASE FUNCTION(s)
	void Draw();

	// TRIGGER RESPONSE FUNCTION(s)
	void TriggerEntered(PhysicsObject* physicsObject, void (*func)() = nullptr);
	void TriggerStayed(PhysicsObject* physicsObject, void (*func)() = nullptr);
	void TriggerExited(PhysicsObject* physicsObject, void (*func)() = nullptr);


	// GETTER FUNCTION(s)
	inline std::string GetTag() const { return m_Tag; }
	std::set<PhysicsObject*>& GetObjects() { return m_ObjectList; }
	inline bool GetActiveState() const { return m_IsActive; }
	inline bool GetHasEntered() const { return m_HasEntered; }
	inline bool GetHasStayed() const { return m_HasStayed; }
	inline bool GetHasExited() const { return m_HasExited; }

	// SETTER FUNCTION(s)
	inline void SetActiveState(bool active) { m_IsActive = active; }
	inline void SetTag(std::string tag) { m_Tag = tag; }

};

#endif