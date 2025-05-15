#ifndef RECTANGLE_COMPONENT_H
#define RECTANGLE_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"

class RectangleComponent : public ColliderEntity
{
private:

	OKVector2<float> m_Position;
	OKVector2<float> m_Scale;
	float m_Rotation;

public:

	// CLASS FUNCTION(s)
	RectangleComponent();

	// NOTE: Axis Aligned Constructor
	RectangleComponent(OKVector2<float> position, OKVector2<float> scale);
	RectangleComponent(OKVector2<float> position, float width, float height);

	RectangleComponent(float x, float y, OKVector2<float> scale);
	RectangleComponent(float x, float y, float width, float height);


	// NOTE: Oriented Constructor
	RectangleComponent(OKVector2<float> position, OKVector2<float> scale, float rotation);
	RectangleComponent(OKVector2<float> position, float width, float height, float rotation);

	RectangleComponent(float x, float y, OKVector2<float> scale, float rotation);
	RectangleComponent(float x, float y, float width, float height, float rotation);

	~RectangleComponent();
};

#endif