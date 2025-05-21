#ifndef TRIGGER_AREA_H
#define TRIGGER_AREA_H

// PARENT CLASS
#include "ColliderEntity.h"
#include "CollisionManager.h"

#include <set>
#include <bitset>

class GameObject;

// TODO AND TO CONSIDER: Can have an "is trigger" bool in the collider class and cast to this class when it has to do stuff

class TriggerArea : public ColliderEntity
{
private:

	std::string m_Tag;
	bool m_IsActive = true;
	bool m_HasEntered = false;
	bool m_HasStayed = false;
	bool m_HasExited = false;

	std::set<GameObject*> m_ObjectList;
	CollisionManager m_ColliderManifest;

public:

	// CLASS FUNCTION(s)

	// RECTANGLE
	/// @brief Rectangle Collider Constructor
	TriggerArea(std::string tag, OKTransform2<float>* transform, bool IsCapsule = false, bool lockZRot = true) { }

	// CIRCLE
	/// @brief Circle Collider Constructor
	TriggerArea(std::string tag, OKTransform2<float>* transform, float radius) { }


	// DESTRUCTOR
	~TriggerArea();


	// TRIGGER RESPONSE FUNCTION(s)
	void TriggerEntered(GameObject* physicsObject, void (*func)() = nullptr);
	void TriggerStayed(GameObject* physicsObject, void (*func)() = nullptr);
	void TriggerExited(GameObject* physicsObject, void (*func)() = nullptr);


	// GETTER FUNCTION(s)
	inline std::string GetTag() const { return m_Tag; }
	std::set<GameObject*>& GetObjects() { return m_ObjectList; }
	inline bool GetActiveState() const { return m_IsActive; }
	inline bool GetHasEntered() const { return m_HasEntered; }
	inline bool GetHasStayed() const { return m_HasStayed; }
	inline bool GetHasExited() const { return m_HasExited; }

	// SETTER FUNCTION(s)
	inline void SetActiveState(bool active) { m_IsActive = active; }
	inline void SetTag(std::string tag) { m_Tag = tag; }

};

#endif