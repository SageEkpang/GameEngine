#ifndef POINT_COLLIDER_COMPONENT_H
#define POINT_COLLIDER_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"
#include "OKVector2.h"

class PointColliderComponent : public ColliderEntity
{
public:

	OKVector2<float> m_Offset;
	float m_Radius = 1.f;

public:

	// CLASS FUNCTION(s) (General)
	PointColliderComponent(float radius);
	PointColliderComponent(OKVector2<float> offset, float radius = 1.f);
	PointColliderComponent(float x, float y, float radius = 1.f);

	// CLASS FUNCTION(s) (Components)
	PointColliderComponent();

	void Construct(float radius);
	void Construct(OKVector2<float> offset, float radius = 1.f);
	void Construct(float x, float y, float radius = 1.f);

	~PointColliderComponent() override;

	// GETTER FUNCTION(s) // NOT NEEDED

	// SETTER FUNCTION(s) // NOT NEEDED

};

#endif