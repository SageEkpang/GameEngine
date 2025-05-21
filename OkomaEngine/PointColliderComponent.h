#ifndef POINT_COLLIDER_COMPONENT_H
#define POINT_COLLIDER_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"
#include "ComponentEntity.h"
#include "OKVector2.h"

class PointColliderComponent : public ColliderEntity, public ComponentEntity
{
public:

	OKVector2<float> m_Position;
	float m_Radius = 1.f;

public:

	PointColliderComponent();

	PointColliderComponent(OKVector2<float> position, float radius = 1.f);
	PointColliderComponent(float x, float y, float radius = 1.f);

	~PointColliderComponent();
};

#endif