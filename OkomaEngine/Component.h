#ifndef COMPONENT_H
#define COMPONENT_H

// NEEDED INCLUDE(s)
#include "HeaderManager.h"

// NOTE: INTERFACE
class Component
{
protected: // PROTECTED VARIABLE(s)

	uint16_t m_ID;

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	Component() { };
	virtual ~Component() { }

	// BASE FUNCTION(s)
	virtual void Update(const float deltaTime) = 0;
};

#endif