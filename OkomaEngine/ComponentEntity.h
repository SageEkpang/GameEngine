#ifndef COMPONENT_H
#define COMPONENT_H

// NEEDED INCLUDE(s)
#include "HeaderManager.h"

enum class ComponentTypes : std::int8_t
{
	COMPONENT_TYPE_RECTANGLE_COLLIDER_COMPONENT,
	COMPONENT_TYPE_SPHERE_COLLIDER_COMPONENT,
	COMPONENT_TYPE_CAPUSLE_COLLIDER_COMPONENT,
	COMPONENT_TYPE_LINE_COLLIDER_COMPONENT,
	COMPONENT_TYPE_PARTICLE_EFFECT_COMPONENT,
	COMPONENT_TYPE_RIGIDBODY_2D_COMPONENT,
	COMPONENT_TYPE_CAMERA_COMPONENT
};

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