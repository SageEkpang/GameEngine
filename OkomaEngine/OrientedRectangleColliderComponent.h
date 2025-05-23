#ifndef ORIENTED_RECTANGLE_COLLIDER_COMPONENT_H
#define ORIENTED_RECTANGLE_COLLIDER_COMPONENT_H

#include "ColliderEntity.h"
#include "OKTransform2.h"
#include "OKVector2.h"

class OrientedRectangleColliderComponent : public ColliderEntity
{
public:

	OKVector2<float> m_Position;
	OKVector2<float> m_Scale;
	float m_Rotation;

public:

	OrientedRectangleColliderComponent();

	void Construct(OKVector2<float> position, OKVector2<float> scale, float rotation);
	void Construct(OKVector2<float> position, float width, float height, float rotation);
	void Construct(float x, float y, OKVector2<float> scale, float rotation);
	void Construct(float x, float y, float width, float height, float rotation);

	~OrientedRectangleColliderComponent();

	// GETTER FUNCTION(s) // NOT NEEDED

	// SETTER FUNCTION(s) // NOT NEEDED

};

#endif