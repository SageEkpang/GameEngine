#ifndef RECTANGLE_COLLIDER_COMPONENT_H
#define RECTANGLE_COLLIDER_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"
#include "OKTransform2.h"
#include "OKVector2.h"

class RectangleColliderComponent : public ColliderEntity
{
public: // PUBLIC VARIABLE(s)

	OKVector2<float> m_Position;
	OKVector2<float> m_Scale;

public:

	// CLASS FUNCTION(s)
	RectangleColliderComponent();

	// NOTE: Axis Aligned Constructor
	void Construct(OKVector2<float> position, OKVector2<float> scale);
	void Construct(OKVector2<float> position, float width, float height);
	void Construct(float x, float y, OKVector2<float> scale);
	void Construct(float x, float y, float width, float height);

	~RectangleColliderComponent();

	// GETTER FUNCTION(s) // NOT NEEDED

	// SETTER FUNCTION(s) // NOT NEEDED

};

#endif