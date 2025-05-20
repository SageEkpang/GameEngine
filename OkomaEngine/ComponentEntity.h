#ifndef COMPONENT_H
#define COMPONENT_H

// NEEDED INCLUDE(s)
#include "HeaderManager.h"
#include <iostream>

// COMPONENT ENUM
enum class ComponentType : std::int8_t
{
	// BASE COMPONENT(s)
	COMPONENT_TYPE_BASE_COMPONENT,

	// CAMERA COMPONENT(s)
	COMPONENT_TYPE_CAMERA_COMPONENT,

	// PHYSICS COMPONENT(s)
	COMPONENT_TYPE_PARTICLE_EFFECT_COMPONENT,
	COMPONENT_TYPE_RIGIDBODY_2D_COMPONENT,

	// COLLIDER COMPONENT(s)
	COMPONENT_TYPE_RECTANGLE_COLLIDER_COMPONENT,
	COMPONENT_TYPE_CIRCLE_COLLIDER_COMPONENT,
	COMPONENT_TYPE_CAPUSLE_COLLIDER_COMPONENT,
	COMPONENT_TYPE_LINE_COLLIDER_COMPONENT,

	// UI COMPONENT(s)
	COMPONENT_TYPE_CANVAS_COMPONENT,
	COMPONENT_TYPE_BUTTON_COMPONENT,
	COMPONENT_TYPE_BACKGROUND,
};
// -------------------------------

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
};

#endif