#ifndef COMPLEX_COLLIDER_COMPONENT_H
#define COMPLEX_COLLIDER_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"

// NOTE: File Loading
#include "OKVector2.h"
#include <fstream>
#include <vector>

// NOTE: Resource notes
// https://www.geeksforgeeks.org/area-of-a-polygon-with-given-n-ordered-vertices/

class ComplexColliderComponent : public ColliderEntity
{
public:

	OKVector2<float> m_Scale;
	float m_Rotation;

	std::vector<OKVector2<float>> m_Vertices;

public:

	// CLASS FUNCTION(s)
	ComplexColliderComponent();

	ComplexColliderComponent(const char* fileName);
	ComplexColliderComponent(const char* fileName, float sizeOffset);
	ComplexColliderComponent(const char* fileName, OKVector2<float> positionOffset);
	ComplexColliderComponent(const char* fileName, OKVector2<float> positionOffset, float sizeOffset);

	~ComplexColliderComponent();


	// BASE FUNCTION(s)
	float PolygonArea();

};

#endif