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
	~RectangleComponent();





};

#endif