#ifndef COMPONENT_H
#define COMPONENT_H

// NEEDED INCLUDE(s)
#include <iostream>
#include <optional>

class GameObjectEntity;

// NOTE: INTERFACE
class ComponentEntity
{
public:

	GameObjectEntity* m_Owner = nullptr;

protected: // PROTECTED VARIABLE(s)

	unsigned short m_ID;

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	ComponentEntity() : m_ID(0) {};
	virtual ~ComponentEntity() { m_Owner = nullptr; }

	// BASE FUNCTION(s)
	virtual void Update(const float deltaTime) { }
	virtual void Draw() { }
};

#endif