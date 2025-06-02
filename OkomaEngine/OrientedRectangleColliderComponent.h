#ifndef ORIENTED_RECTANGLE_COLLIDER_COMPONENT_H
#define ORIENTED_RECTANGLE_COLLIDER_COMPONENT_H

#include "ColliderEntity.h"
#include "OKTransform2.h"
#include "OKVector2.h"

class OrientedRectangleColliderComponent : public ColliderEntity
{
public:

	OKVector2<float> m_Offset;
	OKVector2<float> m_Scale;
	OKVector2<float> m_RotationPoints[4];
	float m_Rotation;

public:

	// CLASS FUNCTION(s) (General)
	OrientedRectangleColliderComponent(OKVector2<float> offset, OKVector2<float> scale, float rotation);
	OrientedRectangleColliderComponent(OKVector2<float> offset, float width, float height, float rotation);
	OrientedRectangleColliderComponent(float x, float y, OKVector2<float> scale, float rotation);
	OrientedRectangleColliderComponent(float x, float y, float width, float height, float rotation);
	OrientedRectangleColliderComponent(OKVector2<float> scale, float rotation);
	OrientedRectangleColliderComponent(float width, float height, float rotation);

	// CLASS FUNCTION(s) (Components)
	OrientedRectangleColliderComponent();

	void Construct(OKVector2<float> offset, OKVector2<float> scale, float rotation);
	void Construct(OKVector2<float> offset, float width, float height, float rotation);
	void Construct(float x, float y, OKVector2<float> scale, float rotation);
	void Construct(float x, float y, float width, float height, float rotation);
	void Construct(OKVector2<float> scale, float rotation);
	void Construct(float width, float height, float rotation);

	~OrientedRectangleColliderComponent() override;

	// GETTER FUNCTION(s) // NOT NEEDED

	// SETTER FUNCTION(s) // NOT NEEDED

};

#endif