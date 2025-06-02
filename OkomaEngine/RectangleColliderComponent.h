#ifndef RECTANGLE_COLLIDER_COMPONENT_H
#define RECTANGLE_COLLIDER_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"
#include "OKTransform2.h"
#include "OKVector2.h"

class RectangleColliderComponent : public ColliderEntity
{
public: // PUBLIC VARIABLE(s)

	OKVector2<float> m_Offset;
	OKVector2<float> m_Scale;

public:

	// CLASS FUNCTION(s) (General)
	RectangleColliderComponent(OKVector2<float> offset, OKVector2<float> scale);
	RectangleColliderComponent(OKVector2<float> offset, float width, float height);
	RectangleColliderComponent(float x, float y, OKVector2<float> scale);
	RectangleColliderComponent(float x, float y, float width, float height);
	RectangleColliderComponent(OKVector2<float> scale);
	RectangleColliderComponent(float width, float height);


	// CLASS FUNCTION(s) (Components)
	RectangleColliderComponent();

	// NOTE: Axis Aligned Constructor
	void Construct(OKVector2<float> offset, OKVector2<float> scale);
	void Construct(OKVector2<float> offset, float width, float height);
	void Construct(float x, float y, OKVector2<float> scale);
	void Construct(float x, float y, float width, float height);
	void Construct(OKVector2<float> scale);
	void Construct(float width, float height);

	~RectangleColliderComponent() override;

	// GETTER FUNCTION(s) // NOT NEEDED

	// SETTER FUNCTION(s) // NOT NEEDED

};

#endif