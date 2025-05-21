#ifndef COMPONENT_H
#define COMPONENT_H

// NEEDED INCLUDE(s)
#include "HeaderManager.h"
#include <iostream>
#include <optional>

// NOTE: INTERFACE
class ComponentEntity
{
protected: // PROTECTED VARIABLE(s)

	unsigned short m_ID;

public: // PUBLIC FUNCTION(s)

	// static constexpr auto m_Type = static_cast<std::size_t>(type);

	// CLASS FUNCTION(s)
	ComponentEntity() : m_ID(0) { };
	virtual ~ComponentEntity() { }

	// BASE FUNCTION(s)
	virtual void Update(const float deltaTime) = 0;
	virtual void Draw() = 0;
};

#endif