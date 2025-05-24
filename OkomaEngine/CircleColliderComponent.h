#ifndef CIRCLE_COLLIDER_COMPONENT_H
#define CIRCLE_COLLIDER_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"
#include "OKVector2.h"

class CircleColliderComponent : public ColliderEntity
{
public:

	OKVector2<float> m_Position;
	float m_Radius;

public:

	// CLASS FUNCTION(s) (Components)
	CircleColliderComponent(OKVector2<float> position, float radius);
	CircleColliderComponent(float x, float y, float radius);

	// CLASS FUNCTION(s) (General)
	CircleColliderComponent();

	void Construct(OKVector2<float> position, float radius);
	void Construct(float x, float y, float radius);
	
	~CircleColliderComponent();

	// GETTER FUNCTION(s) // NOT NEEDED

	// SETTER FUNCTION(s) // NOT NEEDED

};

#endif